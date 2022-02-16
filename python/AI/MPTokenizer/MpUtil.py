import multiprocessing as mp
from tqdm import tqdm


# https://stackoverflow.com/questions/845058/how-to-get-line-count-of-a-large-file-cheaply-in-python
def count_line(path):
    return sum(1 for _ in open(path))


def data_generator(path):
    with open(path, 'rt', encoding="utf8") as f:
        while 1:
            line = f.readline()
            if line:
                yield line[:-1]
            else:
                break


class MpUtil:
    def __init__(self):
        self.total = None

    def _set_total(self, total):
        self.total = total
        # print("total is ",self.total)

    def __call__(self, input_path, output_path, func, worker=10, initializer=None, initargs=None):
        dataset = data_generator(input_path)
        with mp.Pool(worker, initializer=initializer, initargs=initargs) as pool:
            pool.apply_async(count_line, (input_path,),
                             callback=self._set_total)
            with tqdm(pool.imap(func, dataset)) as pbar, open(output_path, 'wt', encoding="utf8") as f:
                for res in pbar:
                    f.write(res + '\n')
                    if self.total:
                        pbar.total = self.total
