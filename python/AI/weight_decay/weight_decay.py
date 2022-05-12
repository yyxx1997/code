import torch
import torch.nn as nn
import matplotlib.pyplot as plt
from regular import Regularization
from torch.utils.tensorboard import SummaryWriter
from tqdm import tqdm
torch.manual_seed(42)
n_hidden = 200
max_iter = 2000
disp_interval = 100
lr_init = 1e-2
num_data = 10
mean = 0
squard = 0.5


def gen_data(num_data=10, x_range=(-1, 1), mean=0, squard=0.5):

    w = 1.5
    train_x = torch.linspace(*x_range, num_data).unsqueeze_(1)
    train_y = w*train_x + torch.normal(mean, squard, size=train_x.size())
    test_x = torch.linspace(*x_range, num_data).unsqueeze_(1)
    test_y = w*test_x + torch.normal(mean, squard, size=test_x.size())

    return train_x, train_y, test_x, test_y


train_x, train_y, test_x, test_y = gen_data(
    num_data=num_data, x_range=(-1, 1), mean=mean, squard=squard)


class MLP(nn.Module):
    def __init__(self, neural_num):
        super(MLP, self).__init__()
        self.linears = nn.Sequential(
            nn.Linear(1, neural_num),
            nn.ReLU(inplace=True),
            nn.Linear(neural_num, neural_num),
            nn.ReLU(inplace=True),
            nn.Linear(neural_num, neural_num),
            nn.ReLU(inplace=True),
            nn.Linear(neural_num, 1),
        )

    def forward(self, x):
        return self.linears(x)


net_normal = MLP(neural_num=n_hidden)
net_weight_decay = MLP(neural_num=n_hidden)
net_weight_decay_L1 = MLP(neural_num=n_hidden)

regular_L1 = Regularization(weight_decay=1e-2, p=1)

def add_weight_decay(model, weight_decay=1e-2, skip_list=()):
    decay = []
    no_decay = []
    for name, param in model.named_parameters():
        if not param.requires_grad:
            continue  # frozen weights
        if len(param.shape) == 1 or name.endswith(".bias") or name in skip_list:
            no_decay.append(param)
        else:
            decay.append(param)
    return [
        {'params': no_decay, 'weight_decay': 0.},
        {'params': decay, 'weight_decay': weight_decay}]

params_without_bias = add_weight_decay(net_weight_decay, weight_decay=1e-2)


# 优化器
optim_normal = torch.optim.SGD(
    net_normal.parameters(), lr=lr_init, momentum=0.9)
optim_wdecay = torch.optim.SGD(
    params_without_bias, lr=lr_init, momentum=0.9)
optim_wdecay_L1 = torch.optim.SGD(
    net_weight_decay_L1.parameters(), lr=lr_init, momentum=0.9)

# 损失函数
loss_func = torch.nn.MSELoss()

writer = SummaryWriter(log_dir="./output/tb_logs_{}_{}/".format(mean, squard),
                       comment='_test_tensorboard', filename_suffix="12345678")

sample = train_x[0]
writer.add_graph(net_normal, sample)
for epoch in tqdm(range(max_iter), desc="training...", total=max_iter):

    # forward
    pred_normal, pred_wdecay, pred_wdecay_L1 = net_normal(
        train_x), net_weight_decay(train_x), net_weight_decay_L1(train_x)
    loss_normal, loss_wdecay, loss_wdecay_L1 = loss_func(pred_normal, train_y), loss_func(
        pred_wdecay, train_y), loss_func(pred_wdecay_L1, train_y) + regular_L1(net_weight_decay_L1)

    optim_normal.zero_grad()
    optim_wdecay.zero_grad()
    optim_wdecay_L1.zero_grad()

    loss_normal.backward()
    loss_wdecay.backward()
    loss_wdecay_L1.backward()

    optim_normal.step()
    optim_wdecay.step()
    optim_wdecay_L1.step()

    if (epoch+1) % disp_interval == 0:

        # 可视化
        for name, layer in net_normal.named_parameters():
            writer.add_histogram(name + '_grad/normal', layer.grad, epoch)
            writer.add_histogram(name + '_data/normal', layer, epoch)

        for name, layer in net_weight_decay.named_parameters():
            writer.add_histogram(
                name + '_grad/weight_decay', layer.grad, epoch)
            writer.add_histogram(name + '_data/weight_decay', layer, epoch)

        for name, layer in net_weight_decay_L1.named_parameters():
            writer.add_histogram(
                name + '_grad/weight_decay/L1', layer.grad, epoch)
            writer.add_histogram(name + '_data/weight_decay/L1', layer, epoch)

        with torch.no_grad():
            test_pred_normal, test_pred_wdecay, test_pred_wdecay_L1 = net_normal(
                test_x), net_weight_decay(test_x), net_weight_decay_L1(test_x)
            loss_normal_test, loss_wdecay_test, loss_wdecay_L1_test = loss_func(
                test_pred_normal, test_y), loss_func(test_pred_wdecay, test_y), loss_func(test_pred_wdecay_L1, test_y)
        
        writer.add_scalar("train_loss/normal",
                              loss_normal.item(), epoch)
        writer.add_scalar("train_loss/wdecay",
                            loss_wdecay.item(), epoch)
        writer.add_scalar("train_loss/wdecay_L1",
                            loss_wdecay_L1.item(), epoch)
        writer.add_scalar("eval_loss/normal",
                            loss_normal_test.item(), epoch)
        writer.add_scalar("eval_loss/wdecay",
                            loss_wdecay_test.item(), epoch)
        writer.add_scalar("eval_loss/wdecay_L1",
                            loss_wdecay_L1_test.item(), epoch)

        # 绘图
        plt.scatter(train_x.data.numpy(), train_y.data.numpy(),
                    c='blue', s=50, alpha=0.3, label='train')
        plt.scatter(test_x.data.numpy(), test_y.data.numpy(),
                    c='red', s=50, alpha=0.3, label='test')
        plt.plot(test_x.data.numpy(), test_pred_normal.data.numpy(),
                 'r-', lw=3, label='no weight decay')
        plt.plot(test_x.data.numpy(), test_pred_wdecay.data.numpy(),
                 'b--', lw=3, label='weight decay')
        plt.plot(test_x.data.numpy(), test_pred_wdecay_L1.data.numpy(),
                 'g--', lw=3, label='weight decay')
        plt.text(-0.25, -1.5, 'no weight decay loss={:.6f}'.format(
            loss_normal_test.item()), fontdict={'size': 15, 'color': 'red'})
        plt.text(-0.25, -2, 'weight decay loss={:.6f}'.format(
            loss_wdecay_test.item()), fontdict={'size': 15, 'color': 'blue'})
        plt.text(-0.25, -2.5, 'weight decay L1 loss={:.6f}'.format(
            loss_wdecay_L1_test.item()), fontdict={'size': 15, 'color': 'green'})

        plt.ylim((-2.5, 2.5))
        plt.legend(loc='upper left')
        plt.title("Epoch: {}".format(epoch+1))
        plt.savefig("./output/Epoch_{}.png".format(epoch+1))
        # plt.show()
        plt.close()
