# Introduction
This repo is about how to use the DDP framework for the inference phase of model implemented by pytorch.
# How to use 
Just run the code directly. 

Without DDP :
~~~
python inference.py
~~~

Use DDP:
~~~
CUDA_VISIBLE_DEVICES=5,7 python -m torch.distributed.launch --nproc_per_node=2 --master_port 29501 inference_ddp.py --n_gpus 2
~~~