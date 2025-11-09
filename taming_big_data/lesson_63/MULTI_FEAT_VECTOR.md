# Spark MLlib 多特征向量完全指南

## 目录
- [概述](#概述)
- [单特征 vs 多特征](#单特征-vs-多特征)
- [三种创建方式](#三种创建方式)
- [实战示例](#实战示例)
- [VectorAssembler 详解](#vectorassembler-详解)
- [常见问题](#常见问题)

---

## 概述

在 Spark MLlib 中，**所有机器学习算法都要求特征必须是 Vector 类型**。无论是单个特征还是多个特征，都必须封装成向量。

### 核心要点

✅ **支持多特征**：可以有任意数量的特征  
✅ **必须是 Vector 类型**：不能是普通的 list 或 array  
✅ **DataFrame 格式**：必须有 `label` 和 `features` 两列  
✅ **灵活性**：可以动态组合不同的特征列

---

## 单特征 vs 多特征

### 数据对比

```python
# 单特征数据
# 特征: 房屋面积
# 标签: 价格
(200000, Vectors.dense([1500]))
# label,  features (只有一个特征)

# 多特征数据
# 特征: 房屋面积, 卧室数, 楼层, 建造年份
# 标签: 价格
(200000, Vectors.dense([1500, 3, 2, 2010]))
# label,  features (有 4 个特征)
```

### 线性回归方程对比

**单特征：**
```
价格 = β₀ + β₁ × 面积
```

**多特征：**
```
价格 = β₀ + β₁×面积 + β₂×卧室数 + β₃×楼层 + β₄×建造年份
```

---

## 三种创建方式

### 方式 1: 直接使用 Vectors.dense()

适用于数据量小或已有向量格式的场景。

```python
from pyspark.ml.linalg import Vectors

# 单特征
data1 = [
    (200000, Vectors.dense([1500])),
    (180000, Vectors.dense([1200])),
]

# 多特征 (3个特征)
data2 = [
    (200000, Vectors.dense([1500, 3, 2])),     # [面积, 卧室, 楼层]
    (180000, Vectors.dense([1200, 2, 1])),
    (250000, Vectors.dense([2000, 4, 3])),
]

# 创建 DataFrame
df = spark.createDataFrame(data2, ["label", "features"])
```

**优点**：简单直接  
**缺点**：手动构造，不够灵活

---

### 方式 2: 从文本文件解析

适用于从文件读取数据的场景。

```python
# 假设文件格式: feature1,feature2,feature3,label
# 例如: 1500,3,2,200000

inputLines = spark.sparkContext.textFile("data.txt")

# 解析并创建向量
data = inputLines.map(lambda x: x.split(",")) \
    .map(lambda fields: (
        float(fields[3]),                               # label (价格)
        Vectors.dense([float(fields[0]),                # feature1 (面积)
                       float(fields[1]),                # feature2 (卧室)
                       float(fields[2])])               # feature3 (楼层)
    ))

df = data.toDF(["label", "features"])
```

**优点**：灵活处理文件数据  
**缺点**：需要手动解析和组装

---

### 方式 3: VectorAssembler (★ 推荐)

**最常用、最灵活的方式**，适用于实际生产环境。

```python
from pyspark.ml.feature import VectorAssembler

# 原始数据（每个特征是独立的列）
rawData = [
    (200000, 1500, 3, 2, 2010),
    (180000, 1200, 2, 1, 2005),
    (250000, 2000, 4, 3, 2015),
]

df = spark.createDataFrame(rawData, 
    ["price", "sqft", "bedrooms", "floor", "year"])

# 使用 VectorAssembler 组装特征
assembler = VectorAssembler(
    inputCols=["sqft", "bedrooms", "floor", "year"],  # 选择哪些列作为特征
    outputCol="features"                               # 输出列名
)

# 转换数据
assembled = assembler.transform(df)

# 重命名 price 为 label
final = assembled.select("price", "features") \
                .withColumnRenamed("price", "label")
```

**优点**：
- 灵活选择特征列
- 易于维护和修改
- 支持动态特征选择
- 生产环境标准做法

---

## 实战示例

### 示例 1: 房价预测（多特征线性回归）

```python
from pyspark.sql import SparkSession
from pyspark.ml.regression import LinearRegression
from pyspark.ml.feature import VectorAssembler

spark = SparkSession.builder.appName("HousePrice").getOrCreate()

# 房屋数据：面积、卧室数、楼层、建造年份、距离市中心(km)
rawData = [
    (150000, 1000, 2, 1, 2000, 15),
    (200000, 1500, 3, 2, 2005, 10),
    (180000, 1200, 2, 1, 2003, 12),
    (250000, 2000, 4, 3, 2010, 8),
    (220000, 1800, 3, 2, 2008, 9),
    (300000, 2500, 4, 3, 2015, 5),
    (160000, 1100, 2, 1, 2001, 14),
    (280000, 2200, 4, 2, 2012, 7),
    (190000, 1400, 3, 2, 2006, 11),
    (350000, 3000, 5, 4, 2018, 3),
]

df = spark.createDataFrame(rawData, 
    ["price", "sqft", "bedrooms", "floor", "year", "distance"])

print("原始数据:")
df.show()

# 组装特征向量
assembler = VectorAssembler(
    inputCols=["sqft", "bedrooms", "floor", "year", "distance"],
    outputCol="features"
)

assembled = assembler.transform(df) \
    .select("price", "features") \
    .withColumnRenamed("price", "label")

print("\n组装后的数据:")
assembled.show(truncate=False)

# 切分训练集和测试集
train, test = assembled.randomSplit([0.8, 0.2], seed=42)

# 训练线性回归模型
lr = LinearRegression(maxIter=100, regParam=0.01)
model = lr.fit(train)

# 输出模型参数
print("\n模型系数 (每个特征的权重):")
print(f"系数: {model.coefficients}")
print(f"解释: [面积权重, 卧室数权重, 楼层权重, 年份权重, 距离权重]")
print(f"截距: {model.intercept:.2f}")

# 构建回归方程
coeffs = model.coefficients
intercept = model.intercept
print("\n回归方程:")
print(f"价格 = {intercept:.2f}")
print(f"     + {coeffs[0]:.2f} × 面积")
print(f"     + {coeffs[1]:.2f} × 卧室数")
print(f"     + {coeffs[2]:.2f} × 楼层")
print(f"     + {coeffs[3]:.2f} × 建造年份")
print(f"     + {coeffs[4]:.2f} × 距离")

# 评估模型
summary = model.summary
print(f"\n训练集 RMSE: ${summary.rootMeanSquaredError:.2f}")
print(f"训练集 R²: {summary.r2:.4f}")

# 预测
predictions = model.transform(test)
print("\n测试集预测结果:")
predictions.select("label", "features", "prediction").show()

spark.stop()
```

### 输出示例

```
原始数据:
+------+----+--------+-----+----+--------+
| price|sqft|bedrooms|floor|year|distance|
+------+----+--------+-----+----+--------+
|150000|1000|       2|    1|2000|      15|
|200000|1500|       3|    2|2005|      10|
...

组装后的数据:
+------+---------------------------+
|label |features                   |
+------+---------------------------+
|150000|[1000.0,2.0,1.0,2000.0,15.0]|
|200000|[1500.0,3.0,2.0,2005.0,10.0]|
...

模型系数 (每个特征的权重):
系数: [89.23, 15000.45, 8500.12, 125.67, -3500.89]
解释: [面积权重, 卧室数权重, 楼层权重, 年份权重, 距离权重]
截距: -105234.56

回归方程:
价格 = -105234.56
     + 89.23 × 面积
     + 15000.45 × 卧室数
     + 8500.12 × 楼层
     + 125.67 × 建造年份
     + -3500.89 × 距离

训练集 RMSE: $12345.67
训练集 R²: 0.9523
```

---

### 示例 2: 动态特征选择

```python
# 场景：尝试不同的特征组合，找出最佳模型

feature_combinations = [
    ["sqft"],                                    # 只用面积
    ["sqft", "bedrooms"],                        # 面积 + 卧室
    ["sqft", "bedrooms", "floor"],               # 面积 + 卧室 + 楼层
    ["sqft", "bedrooms", "floor", "year"],       # 加上建造年份
    ["sqft", "bedrooms", "floor", "year", "distance"],  # 全部特征
]

results = []

for features in feature_combinations:
    # 组装当前特征组合
    assembler = VectorAssembler(inputCols=features, outputCol="features")
    data = assembler.transform(df).select("price", "features") \
                    .withColumnRenamed("price", "label")
    
    # 训练模型
    train, test = data.randomSplit([0.8, 0.2], seed=42)
    lr = LinearRegression(maxIter=100, regParam=0.01)
    model = lr.fit(train)
    
    # 评估
    summary = model.summary
    
    results.append({
        "features": features,
        "num_features": len(features),
        "rmse": summary.rootMeanSquaredError,
        "r2": summary.r2
    })
    
    print(f"\n特征组合: {features}")
    print(f"特征数量: {len(features)}")
    print(f"RMSE: ${summary.rootMeanSquaredError:.2f}")
    print(f"R²: {summary.r2:.4f}")

# 找出最佳模型
best = min(results, key=lambda x: x["rmse"])
print(f"\n最佳特征组合: {best['features']}")
print(f"最佳 RMSE: ${best['rmse']:.2f}")
print(f"最佳 R²: {best['r2']:.4f}")
```

---

## VectorAssembler 详解

### 基本用法

```python
from pyspark.ml.feature import VectorAssembler

assembler = VectorAssembler(
    inputCols=["col1", "col2", "col3"],  # 输入列（可以是任意多个）
    outputCol="features"                  # 输出列名
)

# 转换数据
result = assembler.transform(df)
```

### 参数说明

| 参数 | 类型 | 说明 |
|------|------|------|
| `inputCols` | List[String] | 要组装的输入列名列表 |
| `outputCol` | String | 输出的特征向量列名（通常用 "features"） |
| `handleInvalid` | String | 如何处理无效值：'error'(默认)、'skip'、'keep' |

### 高级用法

#### 1. 处理缺失值

```python
assembler = VectorAssembler(
    inputCols=["age", "income", "education"],
    outputCol="features",
    handleInvalid="skip"  # 跳过包含 NaN 的行
)
```

#### 2. 与 Pipeline 结合

```python
from pyspark.ml import Pipeline
from pyspark.ml.feature import StandardScaler

# 构建处理流程
assembler = VectorAssembler(inputCols=["f1", "f2", "f3"], outputCol="raw_features")
scaler = StandardScaler(inputCol="raw_features", outputCol="features")
lr = LinearRegression()

# 创建 Pipeline
pipeline = Pipeline(stages=[assembler, scaler, lr])

# 一次性完成所有转换和训练
model = pipeline.fit(train_data)
```

#### 3. 选择性特征工程

```python
# 对不同特征应用不同的转换
from pyspark.ml.feature import PolynomialExpansion

# 原始特征
assembler1 = VectorAssembler(
    inputCols=["sqft", "bedrooms"], 
    outputCol="basic_features"
)

# 多项式扩展（生成交互特征）
poly = PolynomialExpansion(
    degree=2, 
    inputCol="basic_features", 
    outputCol="poly_features"
)

# 添加其他特征
assembler2 = VectorAssembler(
    inputCols=["poly_features", "year", "distance"],
    outputCol="features"
)

# 链式转换
result = assembler1.transform(df)
result = poly.transform(result)
result = assembler2.transform(result)
```

---

## 常见问题

### Q1: 可以有多少个特征？

**A**: 理论上无限制，实际受限于：
- 内存大小
- 计算能力
- 样本数量（特征数不应超过样本数的 1/10）

```python
# 100 个特征也是可以的
features = [f"feature_{i}" for i in range(100)]
assembler = VectorAssembler(inputCols=features, outputCol="features")
```

---

### Q2: Vector.dense() vs Vector.sparse() 哪个好？

**A**: 根据数据稀疏性选择：

```python
# Dense Vector: 数据密集时使用
dense = Vectors.dense([1.0, 2.0, 3.0, 4.0, 5.0])

# Sparse Vector: 数据稀疏时使用（大部分是 0）
# 格式: Vectors.sparse(size, {index: value})
sparse = Vectors.sparse(1000, {5: 1.0, 127: 2.0, 999: 3.0})
# 表示: 第5、127、999位有值，其他998个位置都是0
```

**选择建议**：
- 特征值大部分非零 → `dense`
- 特征值大部分为零 (如文本词频) → `sparse`

---

### Q3: 特征需要归一化吗？

**A**: **强烈建议**进行特征标准化，尤其是特征量纲不同时。

```python
from pyspark.ml.feature import StandardScaler

# 先组装特征
assembler = VectorAssembler(inputCols=["sqft", "year"], outputCol="raw_features")
data = assembler.transform(df)

# 标准化特征
scaler = StandardScaler(
    inputCol="raw_features",
    outputCol="features",
    withMean=True,   # 减去均值
    withStd=True     # 除以标准差
)

scalerModel = scaler.fit(data)
normalized = scalerModel.transform(data)
```

**为什么需要？**
- `sqft` 范围: 1000-3000
- `year` 范围: 2000-2020
- 不标准化会导致 `sqft` 权重被低估

---

### Q4: 如何查看特征向量的内容？

```python
# 方法1: 直接显示
df.select("features").show(truncate=False)

# 方法2: 提取为数组
from pyspark.sql.functions import udf
from pyspark.sql.types import ArrayType, DoubleType

# 定义 UDF 将 Vector 转换为数组
vector_to_array = udf(lambda v: v.toArray().tolist(), ArrayType(DoubleType()))

df.withColumn("features_array", vector_to_array("features")).show()

# 方法3: 提取单个特征值
from pyspark.ml.linalg import VectorUDT

# 提取第一个特征
df.withColumn("first_feature", 
    udf(lambda v: float(v[0]), DoubleType())("features")
).show()
```

---

### Q5: 能混合数值和类别特征吗？

**A**: 可以！需要先对类别特征进行编码。

```python
from pyspark.ml.feature import StringIndexer, OneHotEncoder

# 原始数据包含类别特征
data = [
    (200000, 1500, "城北", "精装"),
    (180000, 1200, "城南", "简装"),
]

df = spark.createDataFrame(data, ["price", "sqft", "location", "decoration"])

# 1. 对类别特征进行索引
indexer1 = StringIndexer(inputCol="location", outputCol="location_idx")
indexer2 = StringIndexer(inputCol="decoration", outputCol="decoration_idx")

# 2. One-Hot 编码
encoder1 = OneHotEncoder(inputCol="location_idx", outputCol="location_vec")
encoder2 = OneHotEncoder(inputCol="decoration_idx", outputCol="decoration_vec")

# 3. 组装所有特征（数值 + 编码后的类别）
assembler = VectorAssembler(
    inputCols=["sqft", "location_vec", "decoration_vec"],
    outputCol="features"
)

# 4. Pipeline 执行
from pyspark.ml import Pipeline
pipeline = Pipeline(stages=[
    indexer1, indexer2, 
    encoder1, encoder2, 
    assembler
])

result = pipeline.fit(df).transform(df)
```

---

## 完整工作流程

```python
from pyspark.sql import SparkSession
from pyspark.ml.regression import LinearRegression
from pyspark.ml.feature import VectorAssembler, StandardScaler, StringIndexer
from pyspark.ml import Pipeline

# 1. 创建 SparkSession
spark = SparkSession.builder.appName("MLPipeline").getOrCreate()

# 2. 读取数据
df = spark.read.csv("data.csv", header=True, inferSchema=True)

# 3. 特征工程
# 3.1 处理类别特征
indexer = StringIndexer(inputCol="category", outputCol="category_idx")

# 3.2 组装数值特征
assembler = VectorAssembler(
    inputCols=["num_feature1", "num_feature2", "category_idx"],
    outputCol="raw_features"
)

# 3.3 特征标准化
scaler = StandardScaler(
    inputCol="raw_features",
    outputCol="features",
    withMean=True,
    withStd=True
)

# 4. 机器学习模型
lr = LinearRegression(
    featuresCol="features",
    labelCol="price",
    maxIter=100
)

# 5. 构建 Pipeline
pipeline = Pipeline(stages=[indexer, assembler, scaler, lr])

# 6. 切分数据
train, test = df.randomSplit([0.8, 0.2])

# 7. 训练模型
model = pipeline.fit(train)

# 8. 预测
predictions = model.transform(test)

# 9. 评估
from pyspark.ml.evaluation import RegressionEvaluator
evaluator = RegressionEvaluator(labelCol="price", metricName="rmse")
rmse = evaluator.evaluate(predictions)
print(f"Test RMSE: {rmse}")

# 10. 保存模型
model.save("model_path")
```

---

## 总结

### ✅ 核心要点

1. **Vector 是必须的**：所有特征必须封装成 Vector
2. **支持多特征**：可以有任意多个特征
3. **VectorAssembler 最常用**：灵活、易维护、生产标准
4. **特征工程很重要**：标准化、编码、选择
5. **Pipeline 提高效率**：串联所有步骤

### 📊 特征数量建议

| 样本数 | 建议最大特征数 |
|--------|--------------|
| 100 | 10 |
| 1,000 | 100 |
| 10,000 | 1,000 |
| 100,000+ | 10,000+ |

### 🔧 最佳实践

1. 使用 VectorAssembler 组装特征
2. 对特征进行标准化
3. 使用 Pipeline 管理工作流
4. 实验不同的特征组合
5. 监控特征重要性
6. 定期清理无用特征

---

## 参考资源

- [Spark MLlib 官方文档](https://spark.apache.org/docs/latest/ml-features.html)
- [VectorAssembler API](https://spark.apache.org/docs/latest/api/python/reference/api/pyspark.ml.feature.VectorAssembler.html)
- [线性回归示例](https://spark.apache.org/docs/latest/ml-classification-regression.html#linear-regression)

