from sklearn.neighbors import KNeighborsRegressor
import numpy as np
from sklearn.model_selection import train_test_split, cross_val_score
from matplotlib import pyplot as plt
import seaborn as sns
import pandas as pd

# Data generation step
def create_src_data():
    X1 = np.arange(1,71)
    Y1= [11.31,10.94,11.37,11.49,12.03,12.73,13.07,13.29,13.56,18.73,22.24,24.76,24.45,25.52,25.08,25.87,26.56,26.96,26.57,27.39,31.54,35.60,38.41,38.44,39.08,39.26,39.52,40.31,39.87,40.32,40.65,41.16,41.49,45.02,46.98,47.92,47.53,48.41,48.94,48.89,49.22,49.41,49.53,50.24,50.72,50.71,50.83,51.25,52.30,51.84,49.92,48.31,48.15,48.25,48.99,49.08,49.08,49.45,50.34,48.15,42.39,41.38,41.17,42.06,42.30,42.26,42.51,42.93,43.09,41.76]

    data_dict = {
        "x": X1,
        "y": Y1
    }
    test_data = pd.DataFrame(data_dict)
    print(test_data.head(5))
    test_data.to_csv("test_regress.csv", index=False)


test_data_ = pd.read_csv('test_regress.csv')
x = test_data_['x'].to_numpy().reshape(-1, 1)
y = test_data_['y'].to_numpy().reshape(-1, 1)

knn = KNeighborsRegressor(3, weights='uniform')
model = knn.fit(x, y)

# Regress for the current value
predict = knn.predict(x)

# Get mean square error of the model
score = np.mean(-cross_val_score(knn, x, y, cv=5, scoring='neg_mean_squared_error'))
print("Average mean square error: " + str(score))


predict_f = pd.DataFrame(predict, columns=['predict'])
data = pd.merge(test_data_, predict_f, how='inner', left_index=True, right_index=True)


fig = plt.figure(figsize=[18, 6])
ax = fig.add_subplot(111)
ax.set_title('KNN Regression')
sns.scatterplot(x='x', y='y', data=data, ax=ax, color='r')
sns.lineplot(x='x', y='predict', data=data, ax=ax)
plt.show()

