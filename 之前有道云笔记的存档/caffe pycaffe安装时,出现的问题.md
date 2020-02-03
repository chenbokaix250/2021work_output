make pycaffe出现了这样的问题:
```
CXX/LD -o python/caffe/_caffe.so python/caffe/_caffe.cpp
/usr/bin/ld: /usr/local/lib/libgflags.a(gflags.cc.o): relocation R_X86_64_32 against `.rodata.str1.1' can not be used when making a shared object; recompile with -fPIC
/usr/local/lib/libgflags.a: 无法添加符号: 错误的值
collect2: error: ld returned 1 exit status

```

重新编译gflags
```
 cd build/
 
 cmake .. -DBUILD_SHARED_LIBS=ON
-- Configuring done
-- Generating done
-- Build files have been written to: /home/cold/gflags/build

make -j2
Scanning dependencies of target gflags_shared
Scanning dependencies of target gflags_nothreads_shared
[ 12%] Building CXX object CMakeFiles/gflags_shared.dir/src/gflags.cc.o
[ 25%] Building CXX object CMakeFiles/gflags_nothreads_shared.dir/src/gflags.cc.o
[ 37%] Building CXX object CMakeFiles/gflags_shared.dir/src/gflags_reporting.cc.o
[ 50%] Building CXX object CMakeFiles/gflags_nothreads_shared.dir/src/gflags_reporting.cc.o
[ 62%] Building CXX object CMakeFiles/gflags_shared.dir/src/gflags_completions.cc.o
[ 75%] Building CXX object CMakeFiles/gflags_nothreads_shared.dir/src/gflags_completions.cc.o
[ 87%] Linking CXX shared library lib/libgflags.so
[100%] Linking CXX shared library lib/libgflags_nothreads.so
[100%] Built target gflags_shared
[100%] Built target gflags_nothreads_shared

```


添加~/caffe/python到$PYTHONPATH：

$ sudo gedit /etc/profile

# 添加： export PYTHONPATH=/path/to/caffe/python:$PYTHONPATH

$ source /etc/profile # 使之生效


import caffe后出现如下问题:
```
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
  File "/home/cold/Downloads/caffe-master/python/caffe/__init__.py", line 1, in <module>
    from .pycaffe import Net, SGDSolver, NesterovSolver, AdaGradSolver, RMSPropSolver, AdaDeltaSolver, AdamSolver, NCCL, Timer
  File "/home/cold/Downloads/caffe-master/python/caffe/pycaffe.py", line 13, in <module>
    from ._caffe import Net, SGDSolver, NesterovSolver, AdaGradSolver, \
ImportError: libgflags.so.2.2: cannot open shared object file: No such file or directory

```
使用以下:
`sudo ln -s /usr/loca/lib/libgflags.so.2 /usr/lib/libgflags.so.2`

完成