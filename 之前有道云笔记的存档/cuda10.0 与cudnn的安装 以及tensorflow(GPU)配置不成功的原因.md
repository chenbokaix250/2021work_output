通过[英伟达官网](https://note.youdao.com/)下载了对应的CUDA10.0和cudnn7.3进行了安装

[CUDA10.0](https://developer.download.nvidia.com/compute/cuda/10.0/secure/Prod/local_installers/cuda-repo-ubuntu1604-10-0-local-10.0.130-410.48_1.0-1_amd64.deb?mSr0k11-LwteWlo6c-OZqsH_VDNL0nuG-Ns2D7-3dJGySnDT-4Dsvvdc7aLZU8Bk8uhomjeidvomB7oGTm3sFWNhNWjyDMczE8Z_2w4LiuFNQpjSDKsIpFCseaCgxtwYPWSTfR8Hpmi8kOhHd3s6i9G7UI5olIdAtRcmHi6DZMr4Du296kmbFHo_QutWldjD0dLc4Sx5wgtyHIOYysEs2N3KfAGCMk9moEU3Bs4)

[cudnn7.3](https://developer.download.nvidia.com/compute/machine-learning/cudnn/secure/v7.3.0/prod/10.0_2018920/Ubuntu16_04-x64/libcudnn7-doc_7.3.0.29-1%2Bcuda10.0_amd64.deb?IEUeuZzg-xwrt--SPv1HLn5LjLLzovl9DbxHPcTXcLtfGh_Wnr4AwRGDZqE3vGr5HiqxwOTh6-l1FLcyMLz3JhE9o5njtZareqsYmWLWK5z0QK-CgMUJTb-CXlcu1d-9yBW5pVPbyoIxnhFh38_jYo-fBVGYUpyI-MxI4bnR_2EK1__kaeonvtppoEdgIW9sn68SaT-zem84lTSg7UvPBpw5n_n5AQI0GaA1TZMPNXvDXdcWLvio0WgyRQ)

## CUDA的安装

具体选择情况是  linux -- x86_64 --  Ubuntu -- 16.04 -- deb(local)

安装命令
```
sudo dpkg -i cuda-repo-ubuntu1604-10-0-local-10.0.130-410.48_1.0-1_amd64.deb`
sudo apt-key add /var/cuda-repo-<version>/7fa2af80.pub`
sudo apt-get update`
sudo apt-get install cuda`
```

sudo gedit /etc/profile

export PATH=/usr/local/cuda-10.0/bin${PATH:+:${PATH}}
export LD_LIBRARY_PATH=/usr/local/cuda-10.0/lib64 ${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}} 

![image](https://ws1.sinaimg.cn/large/6b861d65ly1fvntxrlgavj20pn0j176m.jpg)

添加环境变量完毕后重启

重启后检查环境是否设置成功

cat /proc/driver/nvidia/version

nvcc -V       会输出CUDA的版本信息
![输出](https://ws1.sinaimg.cn/large/6b861d65ly1fvntt7jzsoj21hc0u0k75.jpg)
尝试编译cuda的例子

cd /usr/local/samples make进行编译
整个过程20分钟
进入bin后
cd /usr/local/samples/bin/x86_64/linux/release/bin
执行 ./deviceQuery 
![配置成功](https://ws1.sinaimg.cn/large/6b861d65ly1fvntxip7eej21hc0u0k2l.jpg)
再检查CUDA-Capable device的连接情况
执行 ./bandwidthTest


## CUDNN的安装
```
sudo dpkg -i libcudnnxxxxxx.deb
```
利用上述命令安装

## tensorflow-GPU的安装

先解决pip版本过低不能更新的问题
利用`pip install --upgrade pip`升级pip会出现以下问题
`Not uninstalling pip at /usr/xx/xx/xxx,outside environment /usr`的问题

下载get-pip.py文件,然后执行
`sudo python get-pip.py`
可以升级到最新版本

利用`pip install tensorflow-gpu`安装
出现`canuinstall 'enum34'`的问题 解决方法是
`sudo pip install --ignore-installed enum34`

所以`sudo pip install tensorflow-gpu --ignore-installed enum34`

tensorflow安装完成

import时,出现
`ImportError: libcublas.so.9.0: cannot open shared object file: No such file or directory.`

![对应问题](https://ws1.sinaimg.cn/large/6b861d65ly1fvntye70edj21hc0u0atn.jpg)

而CUDA10生成的文件为libcublas.so.10.0 所以9.0找不到

---

随后 对CUDA-10.0进行了卸载

在命令行中输入:
```
sudo apt-get remove cuda 

sudo apt-get autoclean

sudo apt-get remove cuda*
```
然后在目录切换到/esr/local/下

```
cd /usr/local/

sudo rm -r cuda-9.1
```

#### 搞定啦

---
配置9.0版本的cuda

[cuda-9.0下载地址](https://developer.download.nvidia.com/compute/cuda/9.0/secure/Prod/local_installers/cuda-repo-ubuntu1604-9-0-local_9.0.176-1_amd64.deb?Uut66DtD2A77NIBW5NivXP8QbzcaC6kROV4ib0APF_O5LPfn1wXRjEhLMefKixXjp05Us1lJ_UEOFiy5FKaUU-kv_htnfAARm413EqcbNCIRT4I3JGN_K8KRjG987hRqseJs8aXwDlIM0UXl2YJBO2M4rgLhY4gGM43MQt9ubtjvx01lBbutleDPbGRBjD1J_haaQ1Ms6GdwTrEO3x1M)

[cudnn-7](https://developer.download.nvidia.com/compute/machine-learning/cudnn/secure/v7.3.0/prod/9.0_2018920/Ubuntu16_04-x64/libcudnn7_7.3.0.29-1%2Bcuda9.0_amd64.deb?60z1i56cOd2-mH6bVgWiQZLRq-1ReMYK7WHWFVj_kBbw-1fKnQgx-R3JzxPJrRFUUv4HXNnoV6B1F1nkpMKOlRi4UFtQj75Tq5x60XtM-fLlfWN3p1mdNokeEV0gw5oIaWXWHiv9M6HgxpQng9aJORZ29ChHYFiZNNFeMdY47uCMj8P-BItnGkskUm3n2ZwI0C7I0KXBlVwqkp-QUwz3YZdxJ9IeOKY_AOkAs6DkIfHZRDTYtQ)

![下载选择](https://ws1.sinaimg.cn/large/6b861d65ly1fvnu92g44tj20np0lltbc.jpg)