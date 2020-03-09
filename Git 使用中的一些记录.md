# Git 使用中的一些记录

今年需要输出一下相关的内容 准备用github托管一下 

所以准备在git上记录相关内容

简要的Git入门一下

1. 先要生成ssh key
2. 在github上配置ssh key
3. `$ ssh -T git@github.com`来验证是否成功

---

要将本地仓库传到github上去,需要设置username和email

```shell
$ git config --global user.name "your name"
$ git config --global user.email "your_email@youremail.com"
```

提交/上传

* 在本地仓库里添加一些文件,比如README

```shell
$ git add README
$ git commit -m "first commit"
```

* 上传到github

```shell
git push
```

* 如果需要强行上传本地文件

```shell
git push -f
```

