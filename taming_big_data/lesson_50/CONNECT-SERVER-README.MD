# Spark Connect Server 架构详解

## 目录
- [概述](#概述)
- [架构组件关系](#架构组件关系)
- [与 Spark Submit 的关系](#与-spark-submit-的关系)
- [与 Spark Standalone 集群的关系](#与-spark-standalone-集群的关系)
- [与 Spark on YARN 集群的关系](#与-spark-on-yarn-集群的关系)
- [启动方式对比](#启动方式对比)
- [实际使用示例](#实际使用示例)

---

## 概述

**Spark Connect Server** 是 Apache Spark 3.4+ 引入的一个新特性，它提供了一个基于 gRPC 的远程访问接口，允许客户端应用通过网络协议与 Spark 集群交互。

### 核心特点
- 📡 **客户端-服务器架构**：解耦客户端和 Spark 驱动程序
- 🔌 **轻量级客户端**：客户端不需要完整的 Spark 依赖
- 🌐 **远程访问**：支持跨网络、跨语言的 Spark 访问
- 🔒 **更好的资源隔离**：多个客户端可以共享同一个 Spark 会话

---

## 架构组件关系

```
┌─────────────────────────────────────────────────────────────────┐
│                         完整架构图                                │
└─────────────────────────────────────────────────────────────────┘

┌──────────────────┐
│   客户端应用      │  Python/Scala/Java 应用
│                  │  使用 spark.remote("sc://host:port")
└────────┬─────────┘
         │ gRPC (端口 15002)
         │
         ▼
┌──────────────────────────────────────┐
│   Spark Connect Server               │
│   ┌────────────────────────────────┐ │
│   │ gRPC 服务接口                   │ │
│   │ - 接收客户端请求                │ │
│   │ - 序列化/反序列化查询计划        │ │
│   │ - 管理 SparkSession             │ │
│   └────────────────────────────────┘ │
│                                      │
│   本质上是一个特殊的 Spark 应用       │
│   (由 spark-submit 启动)             │
└───────────────┬──────────────────────┘
                │
                │ Spark RPC
                │
                ▼
┌────────────────────────────────────────────┐
│         集群资源管理器                      │
│  ┌──────────────┐  ┌──────────────────┐   │
│  │  Standalone  │  │      YARN        │   │
│  │   Master     │  │  ResourceManager │   │
│  └──────────────┘  └──────────────────┘   │
│         或               或                 │
│  ┌──────────────┐  ┌──────────────────┐   │
│  │ Kubernetes   │  │   Local Mode     │   │
│  └──────────────┘  └──────────────────┘   │
└───────────────┬────────────────────────────┘
                │
                │ 分配资源
                │
                ▼
┌────────────────────────────────────────────┐
│            Spark Executors                 │
│  ┌─────────┐  ┌─────────┐  ┌─────────┐   │
│  │Worker 1 │  │Worker 2 │  │Worker 3 │   │
│  └─────────┘  └─────────┘  └─────────┘   │
│                                            │
│  实际执行计算任务                           │
└────────────────────────────────────────────┘
```

### 关键理解
- **Connect Server ≠ 集群管理器**
- **Connect Server = 应用层网关**
- 它本身就是一个 Spark 应用，需要运行在某个集群上

---

## 与 Spark Submit 的关系

### Spark Connect Server 实际上是由 spark-submit 启动的

#### 启动脚本调用链

```bash
start-connect-server.sh --master yarn --deploy-mode client
    ↓
spark-daemon.sh submit $CLASS 1 --name "Spark Connect server" "$@"
    ↓
spark-submit \
  --class org.apache.spark.sql.connect.service.SparkConnectServer \
  --name "Spark Connect server" \
  --master yarn \
  --deploy-mode client \
  spark-connect_2.12-3.5.0.jar
```

### 关键点

1. **Connect Server 是一个 Spark 应用**
   ```bash
   # 等价于手动运行
   spark-submit \
     --class org.apache.spark.sql.connect.service.SparkConnectServer \
     --master yarn \
     spark-connect_2.12-3.5.0.jar
   ```

2. **所有 spark-submit 的参数都适用**
   - `--master`: 指定集群管理器
   - `--deploy-mode`: client 或 cluster
   - `--conf`: Spark 配置参数
   - `--driver-memory`, `--executor-memory`: 资源配置
   - 等等...

3. **参数透传机制**
   ```bash
   # start-connect-server.sh 中的 "$@" 会把所有参数传递给 spark-submit
   exec "${SPARK_HOME}"/sbin/spark-daemon.sh submit $CLASS 1 \
        --name "Spark Connect server" "$@"
   ```

### 对比表

| 特性 | 普通 Spark 应用 | Spark Connect Server |
|------|----------------|---------------------|
| 启动方式 | `spark-submit MyApp.jar` | `start-connect-server.sh` |
| 本质 | Spark 应用 | 特殊的 Spark 应用 |
| 主类 | 用户自定义 | `SparkConnectServer` |
| 生命周期 | 任务完成即退出 | 长期运行（守护进程） |
| 作用 | 执行数据处理任务 | 提供 gRPC 接口服务 |

---

## 与 Spark Standalone 集群的关系

### 架构说明

Spark Standalone 是 Spark 自带的集群管理器，包括：
- **Master**: 管理集群资源、调度任务
- **Worker**: 提供计算资源、运行 Executor

```
┌──────────────────────────────────────────────────────────┐
│              Spark Standalone 集群架构                     │
└──────────────────────────────────────────────────────────┘

第一步：启动 Standalone 集群
─────────────────────────────
┌─────────────────┐
│ Spark Master    │  (管理资源，端口 7077)
│ spark://master:7077
└────────┬────────┘
         │
    ┌────┴────┬────────┐
    ▼         ▼        ▼
┌────────┐ ┌────────┐ ┌────────┐
│Worker 1│ │Worker 2│ │Worker 3│
└────────┘ └────────┘ └────────┘


第二步：在集群上启动 Connect Server
──────────────────────────────────
$ start-connect-server.sh --master spark://master:7077

┌──────────────────────────┐
│  Spark Connect Server    │  向 Master 注册为一个应用
│  (Driver 进程)            │
└────────┬─────────────────┘
         │ 请求资源
         ▼
┌─────────────────┐
│ Spark Master    │  分配 Executors
└────────┬────────┘
         │ 启动 Executors
    ┌────┴────┬────────┐
    ▼         ▼        ▼
┌────────┐ ┌────────┐ ┌────────┐
│Worker 1│ │Worker 2│ │Worker 3│
│ ┌────┐ │ │ ┌────┐ │ │ ┌────┐ │
│ │Exec│ │ │ │Exec│ │ │ │Exec│ │
│ └────┘ │ │ └────┘ │ │ └────┘ │
└────────┘ └────────┘ └────────┘


第三步：客户端连接 Connect Server
────────────────────────────────
┌──────────────┐
│ 客户端应用    │  spark.remote("sc://connect-server:15002")
└──────┬───────┘
       │ gRPC
       ▼
┌──────────────────────────┐
│  Spark Connect Server    │
│  ↕                       │
│  Executors in Workers    │
└──────────────────────────┘
```

### 完整启动流程

```bash
# 1. 启动 Standalone Master
$SPARK_HOME/sbin/start-master.sh
# Master WebUI: http://localhost:8080
# Master URL: spark://localhost:7077

# 2. 启动 Workers (在各个节点上)
$SPARK_HOME/sbin/start-worker.sh spark://localhost:7077

# 3. 启动 Connect Server，指定连接到 Standalone 集群
$SPARK_HOME/sbin/start-connect-server.sh \
  --master spark://localhost:7077 \
  --conf spark.executor.instances=3 \
  --conf spark.executor.memory=2g \
  --conf spark.executor.cores=2

# 4. 客户端连接
# Python 代码:
from pyspark.sql import SparkSession
spark = SparkSession.builder \
    .remote("sc://localhost:15002") \
    .appName("MyApp") \
    .getOrCreate()
```

### 关键点

1. **集群必须先启动**：Connect Server 需要一个运行中的 Standalone 集群
2. **Master URL 必须正确**：`--master spark://host:7077`
3. **资源分配**：Connect Server 作为一个应用，会从集群请求 Executors
4. **独立生命周期**：Connect Server 不管理 Worker，只使用它们的资源

---

## 与 Spark on YARN 集群的关系

### 架构说明

YARN (Yet Another Resource Negotiator) 是 Hadoop 生态系统的资源管理器。

```
┌──────────────────────────────────────────────────────────┐
│               Spark on YARN 架构                          │
└──────────────────────────────────────────────────────────┘

YARN 集群（由 Hadoop 管理，独立于 Spark）
─────────────────────────────────────────
┌─────────────────────────┐
│  YARN ResourceManager   │  (管理集群资源，端口 8032)
└────────┬────────────────┘
         │
    ┌────┴────┬────────┐
    ▼         ▼        ▼
┌──────────┐┌──────────┐┌──────────┐
│NodeMgr 1 ││NodeMgr 2 ││NodeMgr 3 │
└──────────┘└──────────┘└──────────┘


在 YARN 上启动 Connect Server (Client Mode)
─────────────────────────────────────────
$ start-connect-server.sh \
    --master yarn \
    --deploy-mode client

┌────────────────────────────────────────┐
│  本地主机                               │
│  ┌──────────────────────────┐         │
│  │ Spark Connect Server     │         │
│  │ (Driver 运行在客户端)     │         │
│  └────────┬─────────────────┘         │
└───────────┼────────────────────────────┘
            │ 请求资源
            ▼
┌─────────────────────────┐
│  YARN ResourceManager   │
└────────┬────────────────┘
         │ 分配 Containers
    ┌────┴────┬────────┐
    ▼         ▼        ▼
┌──────────┐┌──────────┐┌──────────┐
│NodeMgr 1 ││NodeMgr 2 ││NodeMgr 3 │
│┌────────┐││┌────────┐││┌────────┐│
││Executor│││Executor│││Executor││
││Container│││Container│││Container││
│└────────┘││└────────┘││└────────┘│
└──────────┘└──────────┘└──────────┘


在 YARN 上启动 Connect Server (Cluster Mode)
─────────────────────────────────────────
$ start-connect-server.sh \
    --master yarn \
    --deploy-mode cluster

┌─────────────────────────┐
│  YARN ResourceManager   │
└────────┬────────────────┘
         │ 启动 ApplicationMaster
         ▼
┌──────────────────────────────────┐
│  NodeManager 1                   │
│  ┌────────────────────────────┐  │
│  │ ApplicationMaster          │  │
│  │ ┌────────────────────────┐ │  │
│  │ │ Spark Connect Server   │ │  │
│  │ │ (Driver 运行在集群中)   │ │  │
│  │ └────────────────────────┘ │  │
│  └────────────────────────────┘  │
└──────────────────────────────────┘
         │ 请求更多 Containers
    ┌────┴────┬────────┐
    ▼         ▼        ▼
┌──────────┐┌──────────┐┌──────────┐
│NodeMgr 2 ││NodeMgr 3 ││NodeMgr 4 │
│┌────────┐││┌────────┐││┌────────┐│
││Executor│││Executor│││Executor││
│└────────┘││└────────┘││└────────┘│
└──────────┘└──────────┘└──────────┘
```

### 两种部署模式对比

#### Client Mode (客户端模式)

```bash
start-connect-server.sh \
  --master yarn \
  --deploy-mode client \
  --conf spark.executor.instances=5 \
  --conf spark.executor.memory=4g
```

**特点**：
- ✅ Driver (Connect Server) 运行在启动脚本的机器上
- ✅ 适合开发和调试
- ✅ 可以直接查看日志
- ❌ 启动机器必须保持运行
- ❌ 网络延迟可能较高

#### Cluster Mode (集群模式)

```bash
start-connect-server.sh \
  --master yarn \
  --deploy-mode cluster \
  --conf spark.executor.instances=5 \
  --conf spark.executor.memory=4g
```

**特点**：
- ✅ Driver 运行在 YARN 集群中的某个节点
- ✅ 适合生产环境
- ✅ 资源利用率高，网络延迟低
- ❌ 日志查看需要通过 YARN WebUI
- ❌ 启动后客户端机器可以断开

### 完整启动流程

```bash
# 前提：YARN 集群已经在运行
# (由 Hadoop 的 start-yarn.sh 启动)

# 1. 启动 Connect Server (Client Mode)
$SPARK_HOME/sbin/start-connect-server.sh \
  --master yarn \
  --deploy-mode client \
  --name "Production Connect Server" \
  --conf spark.executor.instances=10 \
  --conf spark.executor.memory=4g \
  --conf spark.executor.cores=4 \
  --conf spark.dynamicAllocation.enabled=false

# 2. 查看 YARN 应用状态
yarn application -list

# 3. 客户端连接
# Python 代码:
from pyspark.sql import SparkSession
spark = SparkSession.builder \
    .remote("sc://connect-server-host:15002") \
    .appName("MyApp") \
    .getOrCreate()

# 4. 停止 Connect Server
$SPARK_HOME/sbin/stop-connect-server.sh
```

### 与 Standalone 的对比

| 特性 | Standalone | YARN |
|------|-----------|------|
| **集群管理** | Spark 自己管理 | Hadoop YARN 管理 |
| **资源隔离** | 较弱 | 强（支持多租户） |
| **生态整合** | Spark 专用 | 整合 Hadoop 生态 |
| **启动集群** | `start-master.sh` + `start-worker.sh` | Hadoop 的 `start-yarn.sh` |
| **Master URL** | `spark://host:7077` | `yarn` |
| **适用场景** | Spark 专用集群 | 多框架共享集群 |

---

## 启动方式对比

### 1. 本地模式 (开发/测试)

```bash
# 不需要任何集群
start-connect-server.sh --master "local[*]"
```

**适用场景**：
- 本地开发
- 快速测试
- 学习 Spark

**限制**：
- 只使用单机资源
- 没有分布式特性

---

### 2. Standalone 集群模式

```bash
# 第一步：启动集群
$SPARK_HOME/sbin/start-master.sh
$SPARK_HOME/sbin/start-worker.sh spark://localhost:7077

# 第二步：启动 Connect Server
start-connect-server.sh \
  --master spark://localhost:7077 \
  --conf spark.executor.memory=2g
```

**适用场景**：
- Spark 专用集群
- 小型到中型部署
- 快速部署需求

**优势**：
- 简单易用
- Spark 原生支持
- 部署快速

---

### 3. YARN 集群模式

```bash
# 前提：YARN 集群已运行
# 启动 Connect Server
start-connect-server.sh \
  --master yarn \
  --deploy-mode client \
  --conf spark.executor.instances=10
```

**适用场景**：
- 企业级 Hadoop 环境
- 多框架共享资源
- 需要强资源隔离

**优势**：
- 多租户支持
- 与 Hadoop 生态整合
- 企业级资源管理

---

## 实际使用示例

### 示例 1：本地开发环境

```bash
# 启动本地 Connect Server
$SPARK_HOME/sbin/start-connect-server.sh --master "local[4]"
```

```python
# Python 客户端
from pyspark.sql import SparkSession

spark = SparkSession.builder \
    .remote("sc://localhost:15002") \
    .appName("LocalDev") \
    .getOrCreate()

df = spark.read.csv("data.csv", header=True)
df.show()
```

---

### 示例 2：Standalone 集群生产环境

```bash
# 1. 启动集群 (在 master 节点)
$SPARK_HOME/sbin/start-master.sh

# 2. 启动 workers (在各 worker 节点)
$SPARK_HOME/sbin/start-worker.sh spark://master-node:7077

# 3. 启动 Connect Server (在 master 或专用节点)
$SPARK_HOME/sbin/start-connect-server.sh \
  --master spark://master-node:7077 \
  --conf spark.executor.instances=8 \
  --conf spark.executor.memory=8g \
  --conf spark.executor.cores=4 \
  --conf spark.sql.shuffle.partitions=200
```

```python
# Python 客户端 (可以在任何机器上)
from pyspark.sql import SparkSession

spark = SparkSession.builder \
    .remote("sc://master-node:15002") \
    .appName("ProductionApp") \
    .getOrCreate()

# 执行数据处理
df = spark.sql("SELECT * FROM large_table")
result = df.groupBy("category").count()
result.show()
```

---

### 示例 3：YARN 集群 (Cluster Mode)

```bash
# 启动 Connect Server (Cluster Mode - 生产推荐)
$SPARK_HOME/sbin/start-connect-server.sh \
  --master yarn \
  --deploy-mode cluster \
  --name "Production-Connect-Server" \
  --conf spark.executor.instances=20 \
  --conf spark.executor.memory=16g \
  --conf spark.executor.cores=8 \
  --conf spark.dynamicAllocation.enabled=true \
  --conf spark.dynamicAllocation.minExecutors=5 \
  --conf spark.dynamicAllocation.maxExecutors=50 \
  --conf spark.sql.adaptive.enabled=true
```

```python
# Python 客户端
from pyspark.sql import SparkSession

# 连接到运行在 YARN 中的 Connect Server
spark = SparkSession.builder \
    .remote("sc://yarn-connect-host:15002") \
    .appName("BigDataProcessing") \
    .getOrCreate()

# 读取 HDFS 数据
df = spark.read.parquet("hdfs:///data/warehouse/sales")

# 复杂查询
result = df.filter(df.amount > 1000) \
    .groupBy("region", "product") \
    .agg({"amount": "sum", "quantity": "avg"}) \
    .orderBy("sum(amount)", ascending=False)

# 写回 HDFS
result.write.mode("overwrite").parquet("hdfs:///output/sales_summary")
```

---

## 总结

### 核心概念

1. **Spark Connect Server 是什么？**
   - 一个长期运行的 Spark 应用
   - 提供 gRPC 接口供客户端远程访问
   - 由 `spark-submit` 启动

2. **它不是什么？**
   - ❌ 不是集群管理器
   - ❌ 不能启动集群
   - ❌ 不替代 Master/ResourceManager

3. **正确的启动顺序**
   ```
   集群管理器 (Standalone Master / YARN)
       ↓ 先启动
   Spark Connect Server (通过 spark-submit)
       ↓ 再启动
   客户端应用 (通过 gRPC 连接)
   ```

### 选择建议

| 场景 | 推荐方案 |
|------|---------|
| 本地开发 | `--master local[*]` |
| Spark 专用小集群 | Standalone + Client Mode |
| 企业 Hadoop 环境 | YARN + Cluster Mode |
| 云原生环境 | Kubernetes |

### 参数传递链

```
start-connect-server.sh [所有 spark-submit 的参数]
    ↓
spark-daemon.sh submit ... "$@"
    ↓
spark-submit --class SparkConnectServer [参数]
    ↓
向集群管理器提交应用
```

**关键理解**：所有能传给 `spark-submit` 的参数，都能传给 `start-connect-server.sh`！

---

## 参考资源

- [Spark Connect 官方文档](https://spark.apache.org/docs/latest/spark-connect-overview.html)
- [Spark Standalone 集群文档](https://spark.apache.org/docs/latest/spark-standalone.html)
- [Spark on YARN 文档](https://spark.apache.org/docs/latest/running-on-yarn.html)
- [spark-submit 参数详解](https://spark.apache.org/docs/latest/submitting-applications.html)

