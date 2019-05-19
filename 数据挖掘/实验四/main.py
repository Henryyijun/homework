
import pandas as pd
from scipy.interpolate import lagrange
import warnings
from random import shuffle
from sklearn.tree import DecisionTreeClassifier  #导入决策树模型
from sklearn.metrics import confusion_matrix  #导入混淆矩阵函数
from sklearn.externals import joblib
import matplotlib.pyplot as plt  #导入作图库
from sklearn.metrics import roc_curve  #导入 ROC 曲线函数
from keras.models import Sequential #导入神经网络初始化函数
from keras.layers.core import Dense,Activation #导入神经网络层函数、激活函数
warnings.filterwarnings("ignore")


def lagrange_interp(vec, n, k = 5):
    y = vec[list(range(n - k, n)) + list(range(n + 1, n + 1 + k))]
    y = y[y.notnull()]
    return lagrange(y.index, list(y))(n)


def fill_null(df):
    for i in df.columns:
        for j in range(len(df)):
            if (df[i].isnull())[j]:
                df[i][j] = lagrange_interp(df[i], j)

    df.to_excel('fill_data.xls', header=None, index=False)


def nn_train(df, p=0.8):
    data = df.as_matrix()[1:]
    shuffle(data)
    tra = data[: (int)(len(data) * p), :]

    test = data[(int)(len(data) * p):, :]
    net = Sequential()  # 建立神经网络

    net.add(Dense(input_dim=3, units=10))
    net.add(Activation('relu'))
    net.add(Dense(input_dim=10, units=1))
    net.add(Activation("sigmoid"))
    net.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])
    net.fit(tra[:, :3], tra[:, 3], nb_epoch=1000, batch_size=1)  # 训练模型，循环 1000 次
    net.save_weights('nn.h5')  # 保存模型

    cm = confusion_matrix(tra[:, 3].astype('int'), net.predict_classes(tra[:, :3]).reshape(len(tra)))  # 混淆矩阵
    plt.matshow(cm, cmap=plt.cm.Greens)  # 画混淆矩阵图，配色风格使用 cm.Greens
    plt.colorbar()  # 颜色标签
    for x in range(len(cm)):  # 数据标签
        for y in range(len(cm)):
            plt.annotate(cm[x, y], xy=(x, y), horizontalalignment='center', verticalalignment='center')
    plt.show()
    fpr, tpr, thresholds = roc_curve(test[:, 3], net.predict(test[:,:3]).reshape(len(test)), pos_label=1)
    plt.plot(fpr, tpr, linewidth=2, label='ROC of CART', color='green')  # 作出 ROC 曲线
    plt.show()


def train(df, p = 0.8):
    data = df.as_matrix()[1:]
    shuffle(data)
    tra = data[: (int)(len(data) * p),:]
    print(tra)
    test = data[(int)(len(data) * p):,:]
    tree = DecisionTreeClassifier()
    tree.fit(tra[:, :3], tra[:, 3].astype('int'))
    joblib.dump(tree, 'tree.pkl')

    cm = confusion_matrix(tra[:, 3].astype('int'), tree.predict(tra[:, :3]))  # 混淆矩阵
    plt.matshow(cm, cmap=plt.cm.Greens)  # 画混淆矩阵图，配色风格使用 cm.Greens
    plt.colorbar()  # 颜色标签
    for x in range(len(cm)):  # 数据标签
        for y in range(len(cm)):
            plt.annotate(cm[x, y], xy=(x, y), horizontalalignment='center', verticalalignment='center')
    plt.show()
    fpr, tpr, thresholds = roc_curve(test[:, 3], tree.predict_proba(test[:, :3])[:, 1], pos_label=1)
    plt.plot(fpr, tpr, linewidth=2, label='ROC of CART', color='green')  # 作出 ROC 曲线
    plt.show()


if __name__ == '__main__':
    #missingdata = pd.read_excel('missing_data.xls', header=None)
    model = pd.read_excel('model.xls', header=None)
    #fill_null(missingdata)
    train(model)
    #nn_train(model)




