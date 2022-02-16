import numpy as np
from scipy.linalg import sqrtm 
from scipy.special import softmax
import networkx as nx
from networkx.algorithms.community.modularity_max import greedy_modularity_communities
import matplotlib.pyplot as plt
from matplotlib import animation
from IPython.display import HTML

# 邻接矩阵，row 表示当前结点, col 表示邻居结点
A = np.array(
    [[0, 1, 0, 0, 0], 
     [1, 0, 1, 0, 0], 
     [0, 1, 0, 1, 1], 
     [0, 0, 1, 0, 0], 
     [0, 0, 1, 0, 0]])

# 结点特征，这是一个假设值
feats = np.arange(A.shape[0]).reshape((-1,1))+1

# 根据邻接矩阵创建图
g = nx.from_numpy_array(A)
node_labels = {i: i+1 for i in range(g.number_of_nodes())}
pos = nx.planar_layout(g)
fig, ax = plt.subplots(figsize=(10,10))
nx.draw(
    g, pos, with_labels=True, 
    labels=node_labels, 
    node_color='#83C167', 
    ax=ax, edge_color='gray', node_size=1500, font_size=30, font_family='serif'
)
plt.savefig('simple_graph.png', bbox_inches='tight', transparent=True)

H = A @ feats   # 将与当前节点相连的节点的feature进行sum
D = np.zeros(A.shape)
np.fill_diagonal(D, A.sum(axis=0))  # 填充对角线
D_inv = np.linalg.inv(D)    # 求逆矩阵，数量为A中每行1的个数的倒数，用于求平均
H_avg = D_inv @ H

A_tilde= A + np.eye(A.shape[0])

# D for A_tilde:
D_tilde = np.zeros_like(A_tilde)
np.fill_diagonal(D_tilde, A_tilde.sum(axis=1).flatten())

# Inverse square root of D:
D_tilde_invroot = np.linalg.inv(sqrtm(D_tilde))

# A_hat
A_hat = D_tilde_invroot @ A_tilde @ D_tilde_invroot

H = np.zeros((g.number_of_nodes(), 1))
H[0,0] = 1 # 只有一个结点存在信息
iters = 10
results = [H.flatten()]
for i in range(iters):
    H = A_hat @ H
    results.append(H.flatten())


# 绘制动图
fig, ax = plt.subplots(figsize=(10, 10))

kwargs = {'cmap': 'hot', 'node_size': 1500, 'edge_color': 'gray', 
          'vmin': np.array(results).min(), 'vmax': np.array(results).max()*1.1}

def update(idx):
    ax.clear()
    colors = results[idx]
    nx.draw(g, pos, node_color=colors, ax=ax, **kwargs)
    ax.set_title(f"Iter={idx}", fontsize=20)

anim = animation.FuncAnimation(fig, update, frames=len(results), interval=1000, repeat=True)

writergif = animation.PillowWriter()
anim.save('test.gif',writer=writergif)
HTML(anim.to_html5_video())