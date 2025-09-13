from sklearn.neighbors import KNeighborsClassifier
import numpy as np
from sklearn.model_selection import train_test_split

import pandas as pd

target_name_map  = {0: "Action", 1: "Love"}

src_df = pd.read_csv("test_data.csv")

train_data = src_df.filter(['beat_count', 'kiss_count'], axis=1)
print(train_data.head(5))
label = src_df.filter(['class'], axis=1)
print(label.head(5))

x_train, x_test, y_train, y_test = train_test_split(train_data.to_numpy(), label.to_numpy(), \
    test_size=0.2, random_state=0)

knn = KNeighborsClassifier(n_neighbors=3)
knn.fit(x_train, y_train)

score = knn.score(x_test, y_test)
print(score)

# The first one is action film, the second one is love film 
x_film_test = np.array([[103, 2], [1, 105]])
predict_res = knn.predict(x_film_test)

print(predict_res)
for res in predict_res:
    print(target_name_map[res])
