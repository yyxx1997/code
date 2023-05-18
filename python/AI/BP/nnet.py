import numpy as np
import matplotlib.pyplot as plt
np.random.seed = 42

def LoadData(fName:str) -> np.array:
    fh = open(fName,'r')
    n = 0
    rawData = []
    for line in fh.readlines():
        n += 1
        rawData.append(line)
    dataSet = np.zeros([n,3])
    for i in range(n):
        dataSet[i] = np.fromstring(rawData[i],sep=' ')
    fh.close()
    return dataSet


def Sigmoid(x:np.array) -> np.array:
    return 1/(1 + np.exp(-x))

def init_network(layers: list) -> tuple:
    l = len(layers)
    weights = []
    bias = []
    delta = []
    beta = []
    accuW = []
    accuO = []
    for i in range(l-1):
        weights.append(np.random.random([layers[i+1],layers[i]]))
        bias.append(np.random.random([layers[i+1]]))
        accuW.append(np.zeros([layers[i+1],layers[i]]))
        accuO.append(np.zeros([layers[i+1]]))
        delta.append(np.zeros(layers[i+1]))
        beta.append(np.zeros([layers[i+1]]))
    return (weights,bias)


class Net:

    def __init__(self, layers: list) -> None:
        
        self.init_network(layers)
        self.actions = []

    def init_network(self, layers: list):
        self.layers=len(layers)
        self.weights = []
        self.bias = []
        self.delta = []
        self.accuW = []
        self.accuO = []
        for i in range(self.layers-1):
            self.weights.append(np.random.random([layers[i+1],layers[i]]))
            self.bias.append(np.random.random([layers[i+1]]))
            self.accuW.append(np.zeros([layers[i+1],layers[i]]))
            self.accuO.append(np.zeros([layers[i+1]]))
            self.delta.append(np.zeros(layers[i+1]))

    def ForwardPropagation(self, input:np.array) -> float:

        loss = 0
        m = len(input)
        for data in input:
            self.actions.append(data[:-1])
            for i in range(self.layers-1):
                a = self.actions[-1]
                z = self.weights[i].dot(a) + self.bias[i]
                self.actions.append(Sigmoid(z))
            yh = self.actions[-1]
            y = data[-1]
            loss += -(y*np.log(yh) + (1-y)*np.log(1-yh))
            self.delta[-1] = yh - y
            for i in range(self.layers-3,-1,-1):
                prime = self.actions[i+1] * (1-self.actions[i+1])
                self.delta[i] = self.weights[i+1].T.dot(self.delta[i+1]) * prime
            for i in range(self.layers-1):
                self.accuW[i] += np.outer(self.delta[i], self.actions[i])
                self.accuO[i] += self.delta[i]
        
        for i in range(self.layers-1):
            self.accuW[i] += self.accuW[i] / m
            self.accuO[i] += self.accuO[i] / m
        loss = loss / m
        return loss
    
    def BackPropagation(self,alpha=0.1):            
        for i in range(self.layers-1):
            self.weights[i] -= alpha * self.accuW[i]
            self.bias[i] -= alpha * self.accuO[i]
        self.accuW[i] = np.zeros(self.accuW[i].shape)
        self.accuO[i] = np.zeros(self.accuO[i].shape)

    def predict(self, input:np.array):
        actions = input
        for i in range(self.layers-1):
            a = actions
            z = self.weights[i].dot(a) + self.bias[i]
            actions = Sigmoid(z)
        yh = actions
        return yh

if __name__ == '__main__':
    trainSet = LoadData('./data/train.txt')
    testSet = LoadData('./data/val.txt')
    size = len(testSet)

    train_loss = []
    test_loss = []
    accuracy= []

    steps = 100
    net = Net([2,4,5,4,1])
    learing_rate = 1e-2
    for i in range(1,steps+1):
        loss = net.ForwardPropagation(input=trainSet)
        net.BackPropagation(alpha=learing_rate)
        train_loss.append(loss)
        
        correct = 0
        lossTst = 0
        for data in testSet:
            y = data[-1]
            yHat = net.predict(data[:-1])
            lossTst += -(y*np.log(yHat) + (1-y)*np.log(1-yHat))
            if yHat > 0.5:
                ans = 1
            else:
                ans = 0
            if ans == y:
                correct += 1
        accuracy.append(correct/size)
        test_loss.append(lossTst/size)

    # plt.plot(np.arange(steps), train_loss, 'b')
    # plt.plot(np.arange(steps), test_loss, 'r')
    plt.subplot(3,1,1)
    plt.plot(np.arange(steps), train_loss, c='b')
    plt.subplot(3,1,2)
    plt.plot(np.arange(steps), test_loss,  c='r')
    plt.subplot(3,1,3)
    plt.plot(np.arange(steps), accuracy,  c='y')
    plt.savefig('实验结果.jpg')
