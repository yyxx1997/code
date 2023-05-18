# -*- coding:utf-8 -*-
'''本文件用于测试pytorch学习率调整策略'''

__author__ = 'puxitong from UESTC'

import torch
import torch.optim as optim
from torch.optim import lr_scheduler
from torchvision.models import AlexNet
import matplotlib.pyplot as plt 


model = AlexNet(num_classes=2)
optimizer = optim.SGD(params=model.parameters(), lr=0.1)

# 等间隔调整学习率，每训练step_size个epoch，lr*gamma
# scheduler = lr_scheduler.StepLR(optimizer, step_size=30, gamma=0.1)

# 多间隔调整学习率，每训练至milestones中的epoch，lr*gamma
scheduler = lr_scheduler.MultiStepLR(optimizer, milestones=[10, 30, 80], gamma=0.1)

# 指数学习率衰减，lr*gamma**epoch
# scheduler = lr_scheduler.ExponentialLR(optimizer, gamma=0.9)

# 余弦退火学习率衰减，T_max表示半个周期，lr的初始值作为余弦函数0处的极大值逐渐开始下降，
# 在epoch=T_max时lr降至最小值，即pi/2处，然后进入后半个周期，lr增大
# scheduler = lr_scheduler.CosineAnnealingLR(optimizer, T_max=100, eta_min=0)

plt.figure()
x = list(range(100))
y = []
for epoch in range(100):
    optimizer.step()
    scheduler.step()
    y.append(scheduler.get_lr()[0])

plt.plot(x, y)
plt.show()