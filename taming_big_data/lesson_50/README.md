# Spark Connect 模式运行指南

本文档说明如何在 WSL 中启动 Spark Connect Server，并从本地客户端连接运行电影相似度分析脚本。

## 架构说明

```
┌─────────────────────┐         gRPC (port 15002)        ┌──────────────────────┐
│  Windows 客户端      │  ◄──────────────────────────────► │   WSL 环境           │
│  - Python 脚本      │                                   │  - Spark Connect     │
│  - PySpark Connect  │                                   │    Server            │
│                     │                                   │  - 数据文件          │
└─────────────────────┘                                   └──────────────────────┘
```

**关键概念**：
- **客户端**：运行 Python 脚本，发送查询指令（可以在 Windows 或 WSL）
- **服务器**：Spark Connect Server，执行实际计算（运行在 WSL）
- **数据文件**：必须在服务器端（WSL）可访问的位置

---

## 第一步：WSL 环境准备

### 1.1 确保 WSL 已安装

```powershell
# 在 Windows PowerShell 中检查
wsl --list --verbose

# 如果没有安装，执行：
wsl --install -d Ubuntu
```

### 1.2 安装 Java（在 WSL 中）

```bash
# 进入 WSL
wsl

# 更新包管理器
sudo apt update

# 安装 Java 11
sudo apt install openjdk-11-jdk -y

# 验证安装
java -version
```

### 1.3 下载并配置 Spark（在 WSL 中）

```bash
# 下载 Spark 3.5.0
cd ~
wget https://archive.apache.org/dist/spark/spark-3.5.0/spark-3.5.0-bin-hadoop3.tgz

# 解压
tar -xzf spark-3.5.0-bin-hadoop3.tgz

# 设置环境变量（添加到 ~/.bashrc）
echo 'export SPARK_HOME=~/spark-3.5.0-bin-hadoop3' >> ~/.bashrc
echo 'export PATH=$SPARK_HOME/bin:$SPARK_HOME/sbin:$PATH' >> ~/.bashrc

# 使配置生效
source ~/.bashrc

# 验证安装
spark-submit --version
```

---

## 第二步：准备数据文件

### 2.1 下载 MovieLens 数据集（在 WSL 中）

```bash
# 创建数据目录
sudo mkdir -p /SparkCourse/ml-100k
sudo chown $USER:$USER /SparkCourse

# 下载数据集
cd /SparkCourse
wget https://files.grouplens.org/datasets/movielens/ml-100k.zip

# 解压
unzip ml-100k.zip

# 移动文件到正确位置
mv ml-100k/* ml-100k/ 2>/dev/null || true
cd ml-100k

# 验证文件
ls -lh u.item u.data
```

### 2.2 数据文件说明

- **u.item**: 电影信息（电影ID | 电影名称 | 其他信息）
- **u.data**: 评分数据（用户ID  电影ID  评分  时间戳）

---

## 第三步：启动 Spark Connect Server

### 3.1 启动服务器（在 WSL 中）

```bash
# 方式 1：前台运行（推荐用于调试）
$SPARK_HOME/sbin/start-connect-server.sh \
  --packages org.apache.spark:spark-connect_2.12:3.5.0 \
  --conf spark.connect.grpc.binding.port=15002 \
  --conf spark.driver.memory=2g

# 方式 2：后台运行
nohup $SPARK_HOME/sbin/start-connect-server.sh \
  --packages org.apache.spark:spark-connect_2.12:3.5.0 \
  --conf spark.connect.grpc.binding.port=15002 \
  --conf spark.driver.memory=2g > /tmp/spark-connect.log 2>&1 &
```

### 3.2 验证服务器运行

```bash
# 检查进程
jps | grep ConnectServer

# 检查端口
netstat -tuln | grep 15002

# 查看日志（如果是后台运行）
tail -f /tmp/spark-connect.log
```

### 3.3 停止服务器

```bash
# 如果使用 start-connect-server.sh 启动
$SPARK_HOME/sbin/stop-connect-server.sh

# 或者直接杀进程
jps | grep ConnectServer | awk '{print $1}' | xargs kill
```

---

## 第四步：客户端配置

### 4.1 安装 Python 依赖

#### 选项 A：在 Windows 上运行客户端

```powershell
# 在 Windows PowerShell 中
pip install "pyspark[connect]==3.5.0"
```

#### 选项 B：在 WSL 中运行客户端

```bash
# 在 WSL 中
pip3 install "pyspark[connect]==3.5.0"

# 如果没有 pip，先安装
sudo apt install python3-pip -y
```

### 4.2 验证安装

```python
# 创建测试脚本 test-connection.py
from pyspark.sql import SparkSession

try:
    spark = SparkSession.builder \
        .remote("sc://localhost:15002") \
        .appName("ConnectionTest") \
        .getOrCreate()
    
    # 简单测试
    df = spark.range(10)
    print(f"✅ 连接成功！数据行数: {df.count()}")
    df.show()
    
    spark.stop()
except Exception as e:
    print(f"❌ 连接失败: {e}")
```

运行测试：
```bash
python test-connection.py
```

---

## 第五步：运行电影相似度分析

### 5.1 运行脚本

```bash
# 在 Windows PowerShell 中
cd "C:\code\Taming Big Data with Apache Spark and Python\lesson 50"
python movie-similarities-dataframe-connect.py 50

# 或在 WSL 中（如果脚本和客户端都在 WSL）
cd /mnt/c/code/Taming\ Big\ Data\ with\ Apache\ Spark\ and\ Python/lesson\ 50
python3 movie-similarities-dataframe-connect.py 50
```

### 5.2 参数说明

脚本接受一个参数：电影ID

```bash
# 查找电影 ID 为 50 的相似电影
python movie-similarities-dataframe-connect.py 50

# 查找电影 ID 为 1 的相似电影
python movie-similarities-dataframe-connect.py 1
```

### 5.3 预期输出

```
Top 10 similar movies for Star Wars (1977)
Empire Strikes Back, The (1980)    score: 0.9895522    strength: 345.0
Return of the Jedi (1983)          score: 0.9857230    strength: 480.0
...
```

---

## 故障排除

### 问题 1：连接超时

**错误信息**：
```
Failed to connect to localhost:15002
```

**解决方案**：
1. 检查 Spark Connect Server 是否运行：
   ```bash
   jps | grep ConnectServer
   ```

2. 检查端口是否监听：
   ```bash
   netstat -tuln | grep 15002
   ```

3. 检查防火墙设置（WSL 通常不需要）

### 问题 2：找不到数据文件

**错误信息**：
```
Path does not exist: file:/SparkCourse/ml-100k/u.item
```

**解决方案**：
1. 在 WSL 中验证文件存在：
   ```bash
   ls -l /SparkCourse/ml-100k/u.item
   ```

2. 检查文件权限：
   ```bash
   sudo chmod 644 /SparkCourse/ml-100k/*
   ```

### 问题 3：内存不足

**错误信息**：
```
java.lang.OutOfMemoryError
```

**解决方案**：
1. 增加 Spark 内存配置：
   ```bash
   $SPARK_HOME/sbin/start-connect-server.sh \
     --packages org.apache.spark:spark-connect_2.12:3.5.0 \
     --conf spark.driver.memory=4g \
     --conf spark.executor.memory=4g
   ```

2. 或者在 WSL 设置中增加内存限制（`.wslconfig`）：
   ```ini
   [wsl2]
   memory=8GB
   ```

### 问题 4：字符编码问题

**错误信息**：
```
UnicodeDecodeError
```

**解决方案**：
脚本已经设置了 `ISO-8859-1` 编码，如果仍有问题，检查：
```python
.option("charset", "ISO-8859-1")
```

### 问题 5：Python 版本不兼容

**错误信息**：
```
requires Python 3.7+
```

**解决方案**：
```bash
# 检查 Python 版本
python --version

# 升级 Python（在 WSL）
sudo apt install python3.10 -y
```

---

## 性能优化建议

### 1. 缓存数据

```python
# 在脚本中已使用
moviePairSimilarities = computeCosineSimilarity(spark, moviePairs).cache()
```

### 2. 调整并行度

```bash
$SPARK_HOME/sbin/start-connect-server.sh \
  --packages org.apache.spark:spark-connect_2.12:3.5.0 \
  --conf spark.default.parallelism=8 \
  --conf spark.sql.shuffle.partitions=8
```

### 3. 使用本地 SSD

将数据放在 WSL 2 内部文件系统（不要放在 `/mnt/c/`），性能会更好。

---

## 架构对比

### Local 模式 (lesson 48)
```python
spark = SparkSession.builder \
    .appName("MovieSimilarities") \
    .master("local[*]") \
    .getOrCreate()
```
- ✅ 简单，无需额外配置
- ❌ 客户端和 Spark 在同一进程
- ❌ 无法多客户端共享

### Connect 模式 (lesson 50)
```python
spark = SparkSession.builder \
    .remote("sc://localhost:15002") \
    .appName("MovieSimilarities") \
    .getOrCreate()
```
- ✅ 客户端轻量级
- ✅ 支持多客户端连接
- ✅ 更好的资源隔离
- ❌ 需要单独启动服务器

---

## 参考资源

- [Spark Connect 官方文档](https://spark.apache.org/docs/latest/spark-connect-overview.html)
- [MovieLens 数据集](https://grouplens.org/datasets/movielens/)
- [PySpark API 文档](https://spark.apache.org/docs/latest/api/python/)

---

## 常用命令速查

```bash
# 启动服务器
$SPARK_HOME/sbin/start-connect-server.sh --packages org.apache.spark:spark-connect_2.12:3.5.0

# 停止服务器
$SPARK_HOME/sbin/stop-connect-server.sh

# 查看运行的 Spark 进程
jps | grep -i spark

# 查看端口
netstat -tuln | grep 15002

# 查看日志
tail -f $SPARK_HOME/logs/spark-*.out

# 清理日志
rm -rf $SPARK_HOME/logs/*
```

---

## 文件清单

```
lesson 50/
├── README.md                              # 本文档
├── movie-similarities-dataframe-connect.py # 主脚本
└── test-connection.py                      # 连接测试脚本（可选）

/SparkCourse/ml-100k/
├── u.item                                  # 电影信息
├── u.data                                  # 评分数据
└── README                                  # 数据集说明
```

---

**最后更新**: 2025-11-08

