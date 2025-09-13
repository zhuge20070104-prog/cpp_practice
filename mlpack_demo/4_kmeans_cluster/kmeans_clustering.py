from sklearn.cluster import KMeans
import numpy as np
from matplotlib import pyplot as plt
import seaborn as sns
import pandas as pd


def create_data_set():
    points = np.array([[1, 2], [1, 4], [1.5, 2], [1, 2.5], [4, 2], [4.5, 3], [4.5, 3.5], [4, 4], [4, 0]])
    df = pd.DataFrame(points, columns=['x', 'y'])
    df.to_csv('test_data.csv', index=False)

# create_data_set()
    
src_df = pd.read_csv('./test_data.csv')
data = src_df.to_numpy()

kmeans = KMeans(n_clusters=2, random_state=0).fit(data)

print(kmeans.labels_)

colors = [ 'r' if label == 0 else 'b'  for label  in kmeans.labels_]
print(colors)

predict_df = pd.read_csv('./predict.csv')
predict_data = predict_df.to_numpy()
predict_labels = kmeans.predict(predict_data)
predict_colors = ['r' if p_label == 0 else 'b' for p_label in predict_labels] 

fig = plt.figure(figsize=[18, 6])
ax = fig.add_subplot(111)
ax.set_title('KMeans Clustering')
sns.scatterplot(x='x', y='y', data=src_df, ax=ax, color=colors)
sns.scatterplot(x='x', y='y', data=predict_df, ax=ax, color=predict_colors, marker="+")
plt.show()

