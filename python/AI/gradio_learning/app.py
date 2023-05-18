import gradio as gr
from transformers import *

title = "抽取式问答"

description = "输入上下文与问题后，点击submit按钮，可从上下文中抽取出答案，赶快试试吧！"

examples = [
    ["普希金从那里学习人民的语言，吸取了许多有益的养料，这一切对普希金后来的创作产生了很大的影响。这两年里，普希金创作了不少优秀的作品，如《囚徒》、《致大海》、《致凯恩》和《假如生活欺骗了你》等几十首抒情诗，叙事诗《努林伯爵》，历史剧《鲍里斯·戈都诺夫》，以及《叶甫盖尼·奥涅金》前六章。", "著名诗歌《假如生活欺骗了你》的作者是"],
    ["普希金从那里学习人民的语言，吸取了许多有益的养料，这一切对普希金后来的创作产生了很大的影响。这两年里，普希金创作了不少优秀的作品，如《囚徒》、《致大海》、《致凯恩》和《假如生活欺骗了你》等几十首抒情诗，叙事诗《努林伯爵》，历史剧《鲍里斯·戈都诺夫》，以及《叶甫盖尼·奥涅金》前六章。", "普希金创作的叙事诗叫什么"]
    ]

article = "感兴趣的小伙伴可以阅读[Transformers实用指南](https://zhuanlan.zhihu.com/p/548336726)"


# 预测函数
qa = pipeline("question-answering", model="uer/roberta-base-chinese-extractive-qa")
def custom_predict(context, question):
    answer_result = qa(context=context, question=question)
    answer = question + ": " + answer_result["answer"]
    score = answer_result["score"]
    return answer, score

# 清除输入输出
def clear_input():
    return "", "", "", ""

# 构建Blocks上下文
with gr.Blocks() as demo:
    gr.Markdown("# 抽取式问答")
    gr.Markdown("输入上下文与问题后，点击submit按钮，可从上下文中抽取出答案，赶快试试吧！")
    with gr.Column():    # 列排列
        context = gr.Textbox(label="context")
        question = gr.Textbox(label="question")
    with gr.Row():       # 行排列
        clear = gr.Button("clear")
        submit = gr.Button("submit")
    with gr.Column():    # 列排列
        answer = gr.Textbox(label="答案")
        score = gr.Label(label="score")
    # 绑定submit点击函数
    submit.click(fn=custom_predict, inputs=[context, question], outputs=[answer, score])
    # 绑定clear点击函数
    clear.click(fn=clear_input, inputs=[], outputs=[context, question, answer, score])
    gr.Examples(examples, inputs=[context, question])
    gr.Markdown("感兴趣的小伙伴可以阅读[Transformers实用指南](https://zhuanlan.zhihu.com/p/548336726)")

demo.launch(server_name="127.0.0.1", server_port=7861)