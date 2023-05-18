import json
import tiktoken
import requests


INITIAL_SYSTEM_PROMPT = "You are a helpful assistant."
ERROR_MESSAGE_PREFIX = "Error occur: "

def count_token(message):
    encoding = tiktoken.get_encoding("cl100k_base")
    input_str = f"role: {message['role']}, content: {message['content']}"
    length = len(encoding.encode(input_str))
    return length

def construct_text(role, text):
    return {"role": role, "content": text}


def construct_user(text):
    return construct_text("user", text)


def construct_system(text):
    return construct_text("system", text)


def construct_assistant(text):
    return construct_text("assistant", text)

class OpenAIClient_Azure:
    def __init__(
        self,
        model_name,
        api_key,
        system_prompt=INITIAL_SYSTEM_PROMPT,
        temperature=1.0,
        top_p=1.0,
        n_choices=1,
        max_generation_token=4096,
        presence_penalty=0,
        frequency_penalty=0
    ) -> None:
        self.all_token_counts = []
        self.max_generation_token = max_generation_token
        self.presence_penalty = presence_penalty
        self.frequency_penalty = frequency_penalty
        self.n_choices = n_choices
        self.model_name = model_name
        self.temperature = temperature
        self.top_p = top_p
        self.system_prompt = system_prompt
        self.api_key = api_key
        self.engine = "gpt4-new-7" if "gpt-4" in model_name else "gpt35-8"
        self.need_api_key = True
        self._refresh_header()

    def get_answer_stream_iter(self, history):
        response = self._get_response(history, stream=True)
        if response is not None:
            iter = self._decode_chat_response(response)
            partial_text = ""
            for partial_text in iter:
                # partial_text += i
                yield partial_text
        else:
            yield ERROR_MESSAGE_PREFIX + "Response is none"

    def get_answer_at_once(self, history):
        response = self._get_response(history)
        if response is not None:
            response = json.loads(response.text)
            content = response["choices"][0]["message"]["content"]
            total_token_count = response["usage"]["total_tokens"]
            return content
        else:
            return ERROR_MESSAGE_PREFIX + "Response is none"

    def count_token(self, user_input):
        input_token_count = count_token(construct_user(user_input))
        if self.system_prompt is not None and len(self.all_token_counts) == 0:
            system_prompt_token_count = count_token(
                construct_system(self.system_prompt)
            )
            return input_token_count + system_prompt_token_count
        return input_token_count

    def _get_response(self, history, stream=False):
        history = self.convert_bot2client(history)
        print(history)
        system_prompt = self.system_prompt

        if system_prompt is not None:
            history = [construct_system(system_prompt), *history]

        payload = json.dumps({
            "messages": history,
            "temperature": self.temperature,
            "top_p": self.top_p,
            "n": self.n_choices,
            "stream": stream,
            "presence_penalty": self.presence_penalty,
            "frequency_penalty": self.frequency_penalty
        })

        final_url = f"https://community-openai-8.openai.azure.com//openai/deployments/{self.engine}/chat/completions?api-version=2023-03-15-preview"
        try:
            response = requests.request("POST", final_url, headers=self.headers, data=payload, stream=stream, timeout=10)
        except Exception as e:
            print(e)
            return None
        return response

    def _refresh_header(self):
        self.headers = {
            "Content-Type": "application/json",
            "api-key": f"{self.api_key}",
            # 'User-Agent': 'OpenAI/v1 PythonBindings/0.27.0',
            # 'X-OpenAI-Client-User-Agent': '{"bindings_version": "0.27.0", "httplib": "requests", "lang": "python", "lang_version": "3.8.10", "platform": "Linux-5.4.0-42-generic-x86_64-with-glibc2.17", "publisher": "openai", "uname": "Linux 5.4.0-42-generic #46-Ubuntu SMP Fri Jul 10 00:24:02 UTC 2020 x86_64 x86_64"}'
        }

    def _decode_chat_response(self, response):
        error_msg = ""
        for chunk in response.iter_lines():
            if chunk:
                chunk = chunk.decode()
                chunk_length = len(chunk)
                try:
                    chunk = json.loads(chunk[6:])
                except json.JSONDecodeError:
                    print("JSON解析错误,收到的内容: " + f"{chunk}")
                    error_msg += chunk
                    continue
                if chunk_length > 6 and "delta" in chunk["choices"][0]:
                    if chunk["choices"][0]["finish_reason"] == "stop":
                        break
                    try:
                        yield chunk["choices"][0]["delta"]["content"]
                    except Exception as e:
                        continue
        if error_msg:
            raise Exception(error_msg)

    def set_key(self, new_access_key):
        ret = super().set_key(new_access_key)
        self._refresh_header()
        return ret
    
    def convert_bot2client(self, history):
        format_history = []
        for user, bot in history:
            if ERROR_MESSAGE_PREFIX in user:
                continue
            if bot:
                format_history.extend([construct_user(user), construct_system(bot)])
            else:
                format_history.append(construct_user(user))
        return format_history
    
if __name__ == "__main__":
    import os
    import time
    os.environ['https_proxy'] = "http://127.0.0.1:1081"
    os.environ['http_proxy'] = "http://127.0.0.1:1081"
    client = OpenAIClient_Azure("gpt35", "23b25494297749f4893efd953007dc70")
    last_conversation = [['123','qqqq'],['234',None]]
    msg = client.get_answer_stream_iter(last_conversation)
    last_conversation[-1][1] = ""
    for character in msg:
        last_conversation[-1][1] += character
        time.sleep(0.05)
        print(last_conversation)