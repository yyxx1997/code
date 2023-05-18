import gradio as gr
import random
import time
from chatgpt import OpenAIClient_Azure
import os

# os.environ['https_proxy'] = "http://127.0.0.1:1081"
# os.environ['http_proxy'] = "http://127.0.0.1:1081"

client = OpenAIClient_Azure("gpt35", "23b25494297749f4893efd953007dc70")


with gr.Blocks() as demo:
    chatbot = gr.Chatbot()
    msg = gr.Textbox()
    clear = gr.Button("Clear")
    submit = gr.Button("submit")

    def user(user_message, history):
        return "", history + [[user_message, None]]

    def bot(history):
        history[-1][1] = ""
        try:
            bot_message = client.get_answer_at_once(history)
            for character in bot_message:
                history[-1][1] += character
                time.sleep(0.01)
                yield history
        except Exception as e:
            history[-1][1] += "...Oops! Error occuring..." + str(e)
            yield history

    msg.submit(user, [msg, chatbot], [msg, chatbot], queue=False).then(
        bot, chatbot, chatbot
    )
    submit.click(lambda: None, None, chatbot, queue=False).then(user, [msg, chatbot], [msg, chatbot], queue=False).then(
        bot, chatbot, chatbot
    )
    clear.click(lambda: None, None, chatbot, queue=False)


if __name__ == "__main__":

    demo.queue()
    demo.launch()
