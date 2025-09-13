import matplotlib.pyplot as plt
from sklearn.tree import DecisionTreeRegressor
import seaborn as sns
import numpy as np


N = 100
np.random.seed(1)
# 100 uniform distribution floating point numbers [0 - 1]
x = np.random.rand(N) * 6 - 3 
x.sort()
# Construct a sin curve here but add some noise confronts to normal distribution
y = np.sin(x) + np.random.randn(N) * 0.05

x = x.reshape(-1, 1)

dt = DecisionTreeRegressor(criterion='friedman_mse', max_depth=9)

dt.fit(x, y)

x_test = np.linspace(-3, 3, 50).reshape(-1, 1)
y_predict = dt.predict(x_test)

# Here the reshape operation is for seaborn plotting
x = x.reshape(-1)
y = y.reshape(-1)
x_test = x_test.reshape(-1)
y_predict = y_predict.reshape(-1)

fig = plt.figure(figsize=[18, 6])
ax = fig.add_subplot(111)
ax.set_title('Decision Tree Regression')
sns.scatterplot(x=x, y=y, ax=ax, color='r', marker='+')
sns.lineplot(x=x_test, y=y_predict, ax=ax, color='b')
plt.show()