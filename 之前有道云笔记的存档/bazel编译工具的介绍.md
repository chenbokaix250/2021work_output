bazel是google推出的一款工程编译工具
##### bazel的几个概念
* workspace 工作空间 每个工作空间中由一个WORKSPACE文件,来描述工作空间所使用到的信息.
* package 程序包 每个程序包中包含一个BUILD文件,此文件中描述了此工具包的生成构建方式
* target 目标,生成的目标,每个target又可以作为另外一个规则的输入
绝大部分的target属于两种基本类型中的一种,file和rule.另外,还有一种其他的target类型,package group.
![target类型层次结构图](http://www.wanguanglu.com/2016/12/16/bazel-tutorial/target_tree.png)

##### 理解BUILD文件
一个BUILD文件包含了集中不同类型的指令 最重要的是编译指令

BUILD文件中的每一条编译指令被称为一个target,它指向一系列的源文件和依赖

一个成功的build将所有的依赖都显式定义在了BUILD文件中.Bazel使用这些定义来创建项目的依赖图,这能够加速编译的过程

`bazel query --nohost_deps --noimplicit_deps 'deps(//main:hello-world)' --output graph`
这个指令告诉Bazel查找target //main:hello-world的所有依赖项(不包括host和隐式依赖),然后输出图的文字描述.
可以在[GraphViz](http://www.webgraphviz.com/)中查看依赖图.

bazel clean可以用来清楚变异的结果


#### bazel编译带gtest的工程

![工程结构](https://file.tink.im/selif/dmkv7mz8.png)

* 文件WORKSPACE 用来下载 GTEST
```
new_git_repository(
    name = "googletest", 
    build_file = "gmock.BUILD", 
    remote = "https://github.com/google/googletest", 
    tag = "release-1.8.0", 
) 
```
* 定义如下定义的gmock构建文件 gmock.BUILD
* 此构建文件负责编译gtest/gmock:
```
cc_library(
     name = "gtest", 
     srcs = [ 
      "googletest/src/gtest-all.cc", 
      "googlemock/src/gmock-all.cc", 
     ], 
     hdrs = glob([ 
      "**/*.h", 
      "googletest/src/*.cc", 
      "googlemock/src/*.cc", 
     ]), 
     includes = [ 
      "googlemock", 
      "googletest", 
      "googletest/include", 
      "googlemock/include", 
     ], 
     linkopts = ["-pthread"], 
     visibility = ["//visibility:public"], 
) 

    cc_library(
     name = "gtest_main", 
     srcs = ["googlemock/src/gmock_main.cc"], 
     linkopts = ["-pthread"], 
     visibility = ["//visibility:public"], 
     deps = [":gtest"], 
) 
```

* 构建测试文件生成的测试 message_test.cpp
```
#include "gtest/gtest.h" 

#include "MyLib/message.hpp" 

TEST(message_test,content) 
{ 
    EXPECT_EQ(get_message(),"Hello World!"); 
}
```
* 构建测试文件用的 BUILD
```
cc_test(
    name = "MyTest", 
    srcs = glob(["**/*.cpp"]), 
    deps = ["//MyLib:MyLib", 
      "@googletest//:gtest_main"], 
) 
```
* 编译所有的目标：
`bazel build ... `
* 运行
`bazel run bin:hello`
`bazel-bin/bin/hello`
* 运行使用GTEST
`bazel test ... --test_output=errors`

##### filegroup参数
使用这个可以得到一个目标的合集名字，方便在其他rule中引用
例子:
```
filegroup(
    name = "mygroup",
    srcs = [
        "a_file.txt",
        "some/subdirectory/another_file.txt",
    ],
)
```
```
filegroup(
    name = "exported_testdata",
    srcs = glob([
        "testdata/*.dat",
        "testdata/logs/**/*.log",
    ]),
)
```
```
cc_library(
    name = "my_library",
    srcs = ["foo.cc"],
    data = [
        "//my_package:exported_testdata",
        "//my_package:mygroup",
    ],
)
```

