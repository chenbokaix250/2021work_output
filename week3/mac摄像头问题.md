### 问题描述



想在mac上用Python试下人脸识别的功能，在用OpenCV库，也就是cv2时，当我使用`cv2.imshow()`，程序会出现如下报错

![img](https://img-blog.csdnimg.cn/20200217142630323.jpg)

当时遇到这个错误我有点懵，因为我明明已经安装了Qt，于是开始把红字Error复制到浏览器搜索来，google一下，然后查到了点开很多链接，相关性比较高的是，如下结果

[Qt could not find the platform plugin cocoa](https://stackoverflow.com/questions/54297627/qt-could-not-find-the-platform-plugin-cocoa)

![img](https://img-blog.csdnimg.cn/20200217141806542.png)



![img](https://img-blog.csdnimg.cn/20200217160221982.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzODI3NTk1,size_16,color_FFFFFF,t_70)





后来我看来其他博客怀疑是我的Qt版本的问题，于是又把Qt卸载后重装，说实话这个过程挺费时间，然后满怀期待的以为运行后不会再报错了，结果还是出现了上面的红字Error，当时心态真的有点崩，我折腾了一下午居然还没有成功

没办法，**暂时解决不了这问题，先放一放吧**



于是又开始折腾上次没有解决的问题，还是搜索Qt Could not find the Qt platform plugin "cocoa" in ""，这次看了更多的博客，不管是Stack Overflow上，还是Qt论坛上的，在CSDN上找，都没有找到解决方法，我甚至去问了一些大佬，可是他们也并没有回复我，这让我心里有点失落😞，我慢慢发现自己越搜索越急躁，越没有办法耐心看别人上面写的是什么


![img](https://img-blog.csdnimg.cn/20200217142704778.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzODI3NTk1,size_16,color_FFFFFF,t_70)

## 最终问题解决的办法

后来我觉得这样的心态是解决不了问题的，于是我尝试静下心来好好想想出了什么问题，有那么一瞬间，我问自己为什么不搜索一下cv2，可能是cv2的问题呢，也许搜cv2可以搜到答案呢

于是我Google了一下，令人惊喜的是，真的有对应的解决方法

参考答案：OpenCV cv2.imshow is not working because of the qt



![img](https://img-blog.csdnimg.cn/20200217141953921.png)

上面说是opencv-python版本的问题，安装旧版本的opencv-python就能解决这个问题



![img](https://img-blog.csdnimg.cn/20200217161619396.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzODI3NTk1,size_16,color_FFFFFF,t_70)

可仔细回顾这个过程，我真的学到了很多：

办法永远比问题多：计算机是人类创造出来的，你用计算机时出现bug一定是能解决的，只要好好利用搜索引擎，Google、Stackoverflow，一定能找到解决方法的。况且你遇到的问题一定有人遇到过，你要记住你不是第一个遇到这个问题的人，所以怎么办，搜啊，肯定能找到Solution，如果想了很久还是没有找到解决方法，你也可以到Stackoverflow上提出问题，会有大牛来帮你解决的

* 遇到Bug不必慌张：人总是对未知充满恐惧，你也许会当心出现的错误你没有学过，以前没经历过，然后搜索的解决方法全英文，你又很难理解，然后心里就始终无法冷静下来好好思考。这其实是解决Bug最大的阻力，很多时候你总是瞎搜，看到一个解决方法，就草草扫了几眼，很多关键点没注意就会出错。其实只要静下心里好好分析下出现Error的可能原因，把重心定位到搜索这几个可能原因上，就能很高效的解决问题。不然真的只是在那瞎折腾，还什么都没学到。
* 要学会变通：不能一直只在一个角度思考问题，就像我一开始只搜索Qt could not find the platform plugin cocoa，得到的是各式各样的答案，现在想想确实是啊，很多情况都会出现这个报错，谁知道你搜的是哪种情况呢。稍微变通一下，转变一下角度，搜索opencv的问题，你也许会突然柳暗花明。这是不由得想起大学一个老师跟我说过的一句话：尝试了10次还没成功，说明原来的方法是不行的，要先静下来，好好想一想，你再瞎试也没有用的
* 解决Bug的过程在心态上应该是一种享受，而不是慌张焦虑（现在这个社会充斥着太多的焦虑，这样不好），因为以后工作中大部分时间都要和Debug打交道，现在遇到Bug，能够让自己静下心来去思考如何解决问题才是关键的，而不是你碰巧运气好解决了一个问题。慢慢锻炼自己解决Bug的思维方式，这才是你真正要关注的地方，才是最实打实的能力，其他都是虚的
* 我想以后我再遇到任何Bug，不管过程有多艰难，至少在心态上我要跳转过来，不能慌张，要尝试着锻炼自己解决问题的思维方式。错误不可怕，出现什么问题，你一点点排除所有可能性，一定能高效地解决问题的！

![截屏2020-03-03上午10.54.08](/Users/bokaichen/Desktop/截屏2020-03-03上午10.54.08.png)

