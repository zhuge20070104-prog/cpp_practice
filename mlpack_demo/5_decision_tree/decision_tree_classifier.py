import pandas as pd
import matplotlib.pyplot as plt
from sklearn.tree import DecisionTreeClassifier
from sklearn.model_selection import train_test_split
import seaborn as sns
import numpy as np


def create_data():
    src_df = pd.read_csv('iris.csv', index_col=False)
    src_df.drop(["No"], inplace=True, axis=1)
    print(src_df.head())
    src_df.to_csv("./data.csv", index=False, header=False)  


# create_data()
# When there's no specific-header, default header values are "0, 1, 2, 3, 4"
data = pd.read_csv('./data.csv', header=None)

# range(4) == [0, 1, 2, 3]
x = data[range(4)].to_numpy()
y = pd.Categorical(data[4]).codes

# random_state is used to produce the same output among different function calls
x_train, x_test, y_train, y_test = train_test_split(x, y, train_size=0.7, random_state=1)


model = DecisionTreeClassifier(criterion='entropy')

model.fit(x_train, y_train)

y_predict = model.predict(x_test)
ele_eq = (y_predict == y_test)
ele_eq_ints = ele_eq.astype(int)
corret_num = int(np.sum(ele_eq_ints))
total_num = len(y_test)

print("Accuracy is: " , corret_num* 1.0/ total_num)

err_indexes = np.argwhere(ele_eq_ints==0)
err_indexes = err_indexes.reshape(-1)


print("Error predictions in test set: ")
err_x = x_test[err_indexes]
err_y = y_test[err_indexes]

predict_y = y_predict[err_indexes]

print("Error x:", err_x)
print("Actual y:", err_y)
print("Precit y:", predict_y)

