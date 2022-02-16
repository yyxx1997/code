# -*- coding: utf-8 -*- 
# @Time : 2021/6/26 17:08 
# @Author : yx
# @File : binaryClassifier.py

import numpy as np
import matplotlib.pyplot as plt


# 分类器的分类（转换）函数
# https://www.cnblogs.com/zhhy236400/p/9873322.html
def sigmoid(inx):
    return 1.0/(1+np.exp(-inx))



def cross_entropy(a, y):
    a = np.float_(a)
    y = np.float_(y)
    return -np.sum(y * np.log(a + 1e-6) + (1 - y) * np.log(1 - a + 1e-6))


class Dataloader():

    def __init__(self, filename):
        self.loadDataSet(filename)

    # 加载数据集
    def loadDataSet(self, filename):
        dataMat = []
        labelMat = []
        fr = open(filename, 'r')  # 打开logistics regression 数据集
        for line in fr.readlines():  # 逐行读取
            lineArr = line.strip().split()
            dataMat.append([float(lineArr[0]), float(lineArr[1])])
            labelMat.append(int(lineArr[2]))
        fr.close()
        self.datas = dataMat
        self.labels = labelMat
        return

    def __len__(self):
        return self.datas.__len__()

    def dim(self):
        return self.datas[0].__len__()


class LogisticsModel():

    def __init__(self, train_set, val_set, learning_rate=1e-2, batch_size=10, epoch=100, activation=sigmoid):
        self.train_set = train_set
        self.val_set = val_set
        self.learing_rate = learning_rate
        self.batch_size = batch_size
        self.epoch = epoch
        self.activation = activation
        self.weights = np.ones((self.train_set.dim(), 1))
        self.bias = 0

    def forward(self, start, no_grad=False):
        X = self.train_set.datas[start:start + self.batch_size]
        X = np.matrix(X)
        X = np.transpose(X)
        Y = self.train_set.labels[start:start + self.batch_size]
        Y = np.matrix(Y)
        Y = np.transpose(Y)
        batch = len(X)
        Z = np.dot(np.transpose(self.weights), X) + self.bias
        Y_hat = self.activation(Z)
        Loss = cross_entropy(Y_hat, Y) / batch
        b=0.9
        if not no_grad:
            dZ = Y_hat - Y
            dW = np.sum(X * dZ, axis=1) / batch
            db = np.sum(dZ) / batch
            dW = b * self.dW + (1-b) * dW
            db = b * self.db + (1-b) * db
            self.dW=dW
            self.db=db
            self.weights = self.weights - self.learing_rate * dW
            self.bias = self.bias - self.learing_rate * db
        return Loss

    def loop(self):
        total_loss = []
        self.dW,self.db=0,0
        for i in range(self.epoch):
            for i in range(0, self.train_set.__len__(), self.batch_size):
                self.forward(i)
            loss = self.calcLoss()
            total_loss.append(loss)
        return total_loss

    def calcLoss(self):
        total = len(val_set)
        acc = 0
        for i in range(total):
            x = val_set.datas[i]
            label = val_set.labels[i]
            z = np.dot(np.transpose(self.weights), x) + self.bias
            Y_hat = 1 if self.activation(z) > 0.5 else 0
            acc += 1 if Y_hat == label else 0
        Acc = acc / total
        return Acc


if __name__ == '__main__':
    train_set = Dataloader('./train/train.txt')
    val_set = Dataloader('./val/val.txt')
    lm = LogisticsModel(train_set, val_set, batch_size=7, learning_rate=1e-2, epoch=50)
    loss = lm.loop()
    x = np.arange(len(loss))
    plt.plot(x, loss)
    plt.show()
