# 线性回归中的正则化详解

## 目录
- [什么是正则化？](#什么是正则化)
- [为什么需要正则化？](#为什么需要正则化)
- [正则化的数学原理](#正则化的数学原理)
- [三种正则化方法](#三种正则化方法)
- [Spark MLlib 中的参数](#spark-mllib-中的参数)
- [实战示例](#实战示例)
- [参数调优建议](#参数调优建议)

---

## 什么是正则化？

**正则化（Regularization）** 是机器学习中防止模型过拟合的重要技术。它通过在损失函数中添加惩罚项，约束模型的复杂度，使模型更加简单和稳健。

### 核心思想
- 不仅要让模型在训练数据上表现好
- 还要防止模型过于复杂，提高泛化能力
- 通过"惩罚"过大的系数来实现简化

---

## 为什么需要正则化？

### 问题：过拟合（Overfitting）

```
训练误差很小 ✓
测试误差很大 ✗
```

**过拟合的表现：**
- 模型在训练数据上表现完美
- 在新数据上预测效果很差
- 模型过于复杂，记住了训练数据的噪声

**正则化如何解决：**
- 限制模型复杂度
- 减小系数的大小
- 让模型更加平滑和稳定

---

## 正则化的数学原理

### 标准线性回归的损失函数

```
损失 = MSE = 1/n × Σ(y_actual - y_predicted)²
```

### 加入正则化后的损失函数

```
总损失 = MSE + λ × 正则化项

其中：
- λ (lambda) 就是 Spark 中的 regParam
- 正则化项取决于使用哪种正则化方法
```

---

## 三种正则化方法

### 1. Ridge 回归（L2 正则化）

**公式：**
```
损失 = MSE + λ × Σ(β²)
```

**特点：**
- ✅ 所有系数都会缩小，但不会变为 0
- ✅ 适合特征之间有多重共线性的情况
- ✅ 稳定性好，数值计算友好
- ❌ 不会自动进行特征选择

**何时使用：**
- 所有特征都可能是有用的
- 特征之间存在相关性
- 需要稳定的预测结果

**Spark 设置：**
```python
elasticNetParam = 0.0  # 纯 L2 正则化
```

---

### 2. Lasso 回归（L1 正则化）

**公式：**
```
损失 = MSE + λ × Σ|β|
```

**特点：**
- ✅ 会将不重要的特征系数压缩为 0
- ✅ 自动进行特征选择
- ✅ 产生稀疏模型（很多系数为 0）
- ❌ 在特征高度相关时可能不稳定

**何时使用：**
- 特征数量很多，但只有少数重要
- 希望模型自动选择特征
- 需要解释性强的简单模型

**Spark 设置：**
```python
elasticNetParam = 1.0  # 纯 L1 正则化
```

---

### 3. Elastic Net（弹性网络）

**公式：**
```
损失 = MSE + λ × [α × Σ|β| + (1-α) × Σ(β²)]

其中 α 就是 Spark 中的 elasticNetParam
```

**特点：**
- ✅ 结合了 L1 和 L2 的优点
- ✅ 既能进行特征选择，又保持稳定性
- ✅ 最灵活，适用范围最广
- 在实践中通常表现最好

**何时使用：**
- 不确定用 L1 还是 L2 时的首选
- 特征数量多，且存在相关性
- 需要平衡特征选择和模型稳定性

**Spark 设置：**
```python
elasticNetParam = 0.5  # 平衡 L1 和 L2
elasticNetParam = 0.8  # 偏向 L1（更多特征选择）
elasticNetParam = 0.2  # 偏向 L2（更稳定）
```

---

## Spark MLlib 中的参数

### LinearRegression 参数详解

```python
from pyspark.ml.regression import LinearRegression

lir = LinearRegression(
    maxIter=10,           # 最大迭代次数
    regParam=0.3,         # 正则化强度 λ
    elasticNetParam=0.8   # 弹性网络混合比例 α
)
```

### regParam（正则化参数）

| 取值 | 含义 | 效果 |
|------|------|------|
| 0 | 无正则化 | 可能过拟合 |
| 0.01-0.1 | 轻度正则化 | 轻微约束 |
| 0.1-1.0 | 中等正则化 | 平衡性能和复杂度 |
| > 1.0 | 强正则化 | 可能欠拟合 |

**推荐范围：** 0.01 - 1.0

### elasticNetParam（混合参数）

| 取值 | 正则化类型 | 特点 |
|------|------------|------|
| 0.0 | 纯 Ridge (L2) | 所有特征保留 |
| 0.0-0.5 | 偏向 Ridge | 稳定性优先 |
| 0.5 | 平衡混合 | L1 和 L2 各占一半 |
| 0.5-1.0 | 偏向 Lasso | 特征选择优先 |
| 1.0 | 纯 Lasso (L1) | 最强特征选择 |

**推荐配置：**
- 特征少（< 50）：`elasticNetParam=0.5`
- 特征多（> 100）：`elasticNetParam=0.8`
- 不确定：从 `0.5` 开始尝试

---

## 实战示例

### 示例 1：基本使用

```python
from pyspark.ml.regression import LinearRegression

# 创建模型（中等正则化，偏向 Lasso）
lir = LinearRegression(
    maxIter=10,
    regParam=0.3,
    elasticNetParam=0.8
)

# 训练模型
model = lir.fit(trainingDF)

# 查看模型系数
print("系数:", model.coefficients)
print("截距:", model.intercept)

# 查看有多少系数被压缩为 0
zero_coeffs = sum([1 for c in model.coefficients if abs(c) < 1e-10])
print(f"被压缩为0的系数数量: {zero_coeffs}")
```

### 示例 2：使用交叉验证寻找最佳参数

```python
from pyspark.ml.tuning import ParamGridBuilder, CrossValidator
from pyspark.ml.evaluation import RegressionEvaluator

# 创建基础模型
lir = LinearRegression(maxIter=10)

# 定义参数网格
paramGrid = ParamGridBuilder() \
    .addGrid(lir.regParam, [0.01, 0.1, 0.3, 1.0]) \
    .addGrid(lir.elasticNetParam, [0.0, 0.5, 0.8, 1.0]) \
    .build()

# 创建评估器
evaluator = RegressionEvaluator(
    labelCol="label",
    predictionCol="prediction",
    metricName="rmse"  # 使用 RMSE 作为评估指标
)

# 创建交叉验证器
crossval = CrossValidator(
    estimator=lir,
    estimatorParamMaps=paramGrid,
    evaluator=evaluator,
    numFolds=5  # 5折交叉验证
)

# 训练并找到最佳模型
cvModel = crossval.fit(trainingDF)

# 获取最佳模型
bestModel = cvModel.bestModel

# 查看最佳参数
print("最佳 regParam:", bestModel.getRegParam())
print("最佳 elasticNetParam:", bestModel.getElasticNetParam())

# 在测试集上评估
predictions = bestModel.transform(testDF)
rmse = evaluator.evaluate(predictions)
print("测试集 RMSE:", rmse)
```

### 示例 3：比较不同正则化方法

```python
# 准备不同配置
configs = [
    {"name": "无正则化", "regParam": 0.0, "elasticNetParam": 0.5},
    {"name": "Ridge", "regParam": 0.3, "elasticNetParam": 0.0},
    {"name": "Lasso", "regParam": 0.3, "elasticNetParam": 1.0},
    {"name": "Elastic Net", "regParam": 0.3, "elasticNetParam": 0.8}
]

results = []

for config in configs:
    # 创建并训练模型
    lir = LinearRegression(
        maxIter=10,
        regParam=config["regParam"],
        elasticNetParam=config["elasticNetParam"]
    )
    model = lir.fit(trainingDF)
    
    # 评估
    predictions = model.transform(testDF)
    evaluator = RegressionEvaluator(metricName="rmse")
    rmse = evaluator.evaluate(predictions)
    
    # 统计非零系数
    non_zero = sum([1 for c in model.coefficients if abs(c) >= 1e-10])
    
    results.append({
        "配置": config["name"],
        "RMSE": rmse,
        "非零系数数量": non_zero,
        "总系数数量": len(model.coefficients)
    })
    
    print(f"\n{config['name']}:")
    print(f"  RMSE: {rmse:.4f}")
    print(f"  非零系数: {non_zero}/{len(model.coefficients)}")
```

---

## 参数调优建议

### 调优流程

```
1. 从默认值开始
   ├─ regParam = 0.1
   └─ elasticNetParam = 0.5

2. 使用网格搜索
   ├─ regParam: [0.01, 0.1, 0.5, 1.0]
   └─ elasticNetParam: [0.0, 0.5, 0.8, 1.0]

3. 细化搜索范围
   └─ 在最佳值附近进行更细致的搜索

4. 评估最终模型
   ├─ 训练集性能
   ├─ 测试集性能
   └─ 模型复杂度（非零系数数量）
```

### 经验法则

| 场景 | 推荐配置 |
|------|----------|
| 特征少（< 20） | `regParam=0.1, elasticNetParam=0.0` (Ridge) |
| 特征中等（20-100） | `regParam=0.3, elasticNetParam=0.5` (平衡) |
| 特征多（> 100） | `regParam=0.5, elasticNetParam=0.8` (偏 Lasso) |
| 存在噪声特征 | 增大 `regParam`，增大 `elasticNetParam` |
| 特征相关性高 | 减小 `elasticNetParam`（更偏向 Ridge） |
| 需要特征选择 | 增大 `elasticNetParam`（更偏向 Lasso） |

### 诊断提示

**如果训练误差很大：**
- 可能是欠拟合
- 尝试减小 `regParam`
- 增加 `maxIter`

**如果训练误差很小但测试误差大：**
- 可能是过拟合
- 增大 `regParam`
- 考虑收集更多训练数据

**如果想要更简单的模型：**
- 增大 `elasticNetParam`（偏向 Lasso）
- 查看哪些特征的系数被压缩为 0

---

## 可视化理解

### 正则化如何约束系数

```
无正则化：
系数可以任意大 → β₁=100, β₂=-50, β₃=200 (过拟合)

有正则化：
系数被约束在合理范围 → β₁=2.5, β₂=-1.2, β₃=3.1 (泛化好)
```

### L1 vs L2 的几何解释

```
L2 (Ridge): 系数约束在一个圆形区域内
  - 所有方向都均匀压缩
  - 不会产生 0 值

L1 (Lasso): 系数约束在一个菱形区域内
  - 菱形的顶点在坐标轴上
  - 容易产生 0 值（特征选择）
```

---

## 常见问题

### Q1: regParam 应该设置多大？
**A:** 没有固定答案，需要通过交叉验证确定。一般从 0.1 开始尝试，观察模型性能。

### Q2: 什么时候用 Ridge，什么时候用 Lasso？
**A:** 
- 如果不确定，用 Elastic Net (`elasticNetParam=0.5`)
- 如果需要特征选择，偏向 Lasso (`elasticNetParam=0.8-1.0`)
- 如果特征都很重要，用 Ridge (`elasticNetParam=0.0`)

### Q3: 正则化会让模型性能变差吗？
**A:** 在训练集上可能会，但在测试集上通常会更好。正则化的目标是提高泛化能力，而不是训练集性能。

### Q4: 如何知道正则化是否合适？
**A:** 观察训练误差和测试误差的差距：
- 差距大：需要更强的正则化（增大 `regParam`）
- 差距小但两者都大：正则化可能过强（减小 `regParam`）

---

## 总结

- **正则化是防止过拟合的关键技术**
- **L1 (Lasso)** 用于特征选择
- **L2 (Ridge)** 用于稳定模型
- **Elastic Net** 结合两者优点，最常用
- **regParam** 控制正则化强度
- **elasticNetParam** 控制 L1/L2 混合比例
- **始终使用交叉验证来选择最佳参数**

---

## 参考资源

- [Spark MLlib 官方文档 - Linear Regression](https://spark.apache.org/docs/latest/ml-classification-regression.html#linear-regression)
- [Understanding Regularization in Machine Learning](https://towardsdatascience.com/regularization-in-machine-learning-76441ddcf99a)
- [Ridge vs Lasso vs Elastic Net](https://www.analyticsvidhya.com/blog/2016/01/ridge-lasso-regression-python-complete-tutorial/)

---

*本文档创建日期: 2025-11-09*

