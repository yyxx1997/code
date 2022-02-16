import hiddenlayer as h
from simple_transformer import Transformer
import torch
from torchviz import make_dot

if __name__ == "__main__":
    x = torch.tensor([[1, 5, 6, 4, 3, 9, 5, 2, 0], [1, 8, 7, 3, 4, 5, 6, 7, 2]])
    tgt = torch.tensor([[1, 7, 4, 3, 5, 9, 2, 0], [1, 5, 6, 2, 4, 7, 6, 2]])

    src_pad_idx = 0
    tgt_pad_idx = 0
    src_input_dim = 10
    tgt_input_dim = 10
    model = Transformer(src_input_dim, tgt_input_dim, src_pad_idx, tgt_pad_idx)
    out = model(x, tgt[:, :-1])   # 获取网络的预测值

    MyConvNetVis = make_dot(out, params=dict(list(model.named_parameters()) + [('x', x),('tgt',tgt[:, :-1])]))
    MyConvNetVis.format = "png"
    # 指定文件生成的文件夹
    MyConvNetVis.directory = "data"
    # 生成文件
    MyConvNetVis.view()