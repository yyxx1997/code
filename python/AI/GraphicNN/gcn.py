# refer to ：https://tkipf.github.io/graph-convolutional-networks/

import math
import torch
import torch.nn.functional as F
from torch.nn.parameter import Parameter
from torch.nn.modules.module import Module


class GraphConvolution(Module):
    """
    Simple GCN layer, similar to https://arxiv.org/abs/1609.02907
    """

    def __init__(self, in_features, out_features, bias=True):
        super(GraphConvolution, self).__init__()
        self.in_features = in_features
        self.out_features = out_features
        self.weight = Parameter(torch.FloatTensor(in_features, out_features))
        if bias:
            self.bias = Parameter(torch.FloatTensor(out_features))
        else:
            self.register_parameter('bias', None)
        self.reset_parameters()

    def reset_parameters(self):
        stdv = 1. / math.sqrt(self.weight.size(1))
        self.weight.data.uniform_(-stdv, stdv)
        if self.bias is not None:
            self.bias.data.uniform_(-stdv, stdv)

    def forward(self, input, adj):
        # message passing
        support = torch.mm(input, self.weight)  # (node_dim, in_dim)*(in_dim, out_dim)
        output = torch.spmm(adj, support) # 稀疏矩阵*密度矩阵
        if self.bias is not None:
            return output + self.bias
        else:
            return output

    def __repr__(self):
        return self.__class__.__name__ + ' (' \
               + str(self.in_features) + ' -> ' \
               + str(self.out_features) + ')'

class GCN(torch.nn.Module):
    def __init__(self, nfeat, nhid, nclass, dropout):
        super(GCN, self).__init__()

        self.gc1 = GraphConvolution(nfeat, nhid)
        self.gc2 = GraphConvolution(nhid, nclass)
        self.dropout = dropout

    def forward(self, x, adj):
        x = F.relu(self.gc1(x, adj))
        x = F.dropout(x, self.dropout, training=self.training)
        x = self.gc2(x, adj)
        return F.log_softmax(x, dim=1)

import numpy as np
if __name__ == '__main__':
    A = np.array(
        [[0, 1, 0, 0, 0],
        [1, 0, 1, 0, 0],
        [0, 1, 0, 1, 1],
        [0, 0, 1, 0, 0],
        [0, 0, 1, 0, 0]])

    X = np.arange(A.shape[0]).reshape((-1,1))+1
    node_labels = {i: i+1 for i in range(A.shape[0])}
    model = GCN( nfeat=1, nhid=10, nclass=4, dropout=0)
    Z = model(torch.Tensor(X), torch.Tensor(A))
    assert Z.size()==(5, 4)