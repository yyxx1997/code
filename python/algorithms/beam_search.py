import random
import copy
voc = ['<BOS>','<EOS>','test','beam','search'] # 假设词典就是这几个词
class model:
    def decoder(x,V=len(voc)):
        return [random.randint(1,9)/10.0 for _ in range(V)] # 输出维度维度是V*1 ，代表每个词出现的概率
    def fun(que,x,k=3):# 这块维持一个大小为k（Beam search的宽度）的小顶堆，使得复杂度降到log(k)
        que.append(x)
        def second(k):# 以序列出现的概率为依据进行排序
            return k[1]
        que.sort(key=second)
        if len(que)>k:
            que=que[-k:]
        return que
class beam_search_decoder:
    def __init__(self):
        self.decode = model.decoder # 假设我们已经训练好一个模型，这是他的解码器 
        self.topk = model.fun# 这是用于更新当前保留较大的K个备选项的函数
    def forward(self,x0,max_len=5):# 模型输入为初始向量，一般是编码器的输出
        beams = [([x0],1.0)]# 首先把初始向量填入beam中 第一值是输出的序列列表，第二值是该序列出现的概率
        for _ in range(max_len):# 自回归式迭代生成输出序列 最大输出序列长度为max_len
            que = [] # 临时beam缓存

            for x,score in beams:# 遍历Beam中所有备选项
                if x[-1]==1:#EOS id = 1 如果已经输出了结束字符 则该序列直接用于更新，不再进行解码
                    que = self.topk(que,(x,score))
                else:
                    output = self.decode(x) # 以Beam中已生成的序列为输入，生成下一token的概率分布
                    for i,o_score in enumerate(output):# 遍历词典中所有词
                        que = self.topk(que,(x+[i],score*o_score))# 假设改词为输出的词，那么可以得到一个新的序列以及该序列出现的概率
            beams = que # 更新Beam
        return beams
if __name__ == '__main__':
    beam = beam_search_decoder()
    b = beam.forward(0)# 假设以<sos>为开始 然后进行序列生成
    print(b)# 输出所有备选序列
    print([voc[x] for x in b[-1][0]])# 输出概率最高的句子
