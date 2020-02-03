### caffe
学习了这边微博下的内容   [链接](https://blog.csdn.net/jiongnima/article/details/70197866)

caffe在编译过程中 需要去掉`Makefile.config`的 `CPU_ONLY`的注释

利用`make -j`编译时,机器会卡死 

编译完成后

运行时,只有cpu的话,会出现的 cublas_v2.h 无法找到的问题,解决方法如下:

1. BLAS库是用来计算矩阵和向量的,caffe中可以调用的有三种:MKL/ATLAS/OpenBLAS
在cpu端的数值计算由对应的cuBLAS来完成.

编译时利用 `BLAS :=open`来编译

2. 在调用`caffe.h`之前,#define CPU_ONLY 来避免进入GPU计算的相关内容

glog中 CHECK_EQ用来比较


### caffe应用
利用训练完毕的模型进行分类时需要以下文件:

Classifier::Classifier(const string& model_file,  
                       const string& trained_file,  
                       const string& mean_file,  
                       const string& label_file) {};

.prototxt 
.caffemodel
.binaryproto
.txt




CMakeLists.txt中的内容只需要体现:
1. project
2. add_executable
3. include_directories
4. target_link_libraries

其中包含caffe的libcaffe.so是编译生成的
opencv的库在 /usr/lib/x86_64-linux-gnu


***
### main函数中的处理:
```
#include "classification.hpp"  
#include <vector>  
using namespace std;  
  
int main(int argc, char** argv) {  
  clock_t start_time1,end_time1,start_time2,end_time2;  
  ::google::InitGoogleLogging(argv[0]);  
  start_time1 = clock();  
  Classifier classifier;//进行类对象初始化  
  end_time1 = clock();  
  double seconds1 = (double)(end_time1-start_time1)/CLOCKS_PER_SEC;  
  cout<<"init time="<<seconds1<<"s"<<endl;  
  string file = "/home/ubuntu/classification_modified/test_images/dCut2.jpg";  
  Mat img = imread(file, -1);//读入待判别的图片  
  start_time2 = clock();  
  vector<float> result = classifier.Classify(img);//进行网络前传  
  end_time2 = clock();  
  double seconds2 = (double)(end_time2-start_time2)/CLOCKS_PER_SEC;  
  cout<<"classify time="<<seconds2<<"s"<<endl;  
  for(size_t i=0;i<result.size();++i)//输出输入图片属于各个类的概率  
    cout<<result[i]<<endl;  
  return 0;  
}  
```


### classification中的处理
```
include "caffe/caffe.hpp"  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include <algorithm>  
#include <iosfwd>  
#include <memory>  
#include <string>  
#include <utility>  
#include <vector>  
#include <sstream>  
#include "classification.hpp"  
  
using namespace caffe;  
using namespace std;  
using namespace cv;  
  
class Classifier;  
Classifier::Classifier() {  
  Caffe::set_mode(Caffe::GPU);//设置caffe工作模式为GPU  
  string model_file   = "/home/ubuntu/classification_modified/lib/fork_net.prototxt";//网络定义文件  
  string trained_file = "/home/ubuntu/classification_modified/lib/fork.caffemodel";//训练得到的网络参数参数文件  
  net_.reset(new Net<float>(model_file, TEST));//设置网络为训练模式，只进行前向传播  
  net_->CopyTrainedLayersFrom(trained_file);//导入网络参数  
  Blob<float>* input_layer = net_->input_blobs()[0];  
  input_geometry_ = Size(input_layer->width(), input_layer->height());//获取网络规定的输入图像尺寸(宽与高)  
  Blob<float>* output_layer = net_->output_blobs()[0];  
}  
  
vector<float> Classifier::Classify(const Mat& img) {  
  num_channels_ = 3;//在这里网络接受三通道的图片  
  Blob<float>* input_layer = net_->input_blobs()[0];  
  input_layer->Reshape(1, num_channels_,  
                       input_geometry_.height, input_geometry_.width);//网络输入blob(1,3,height,width)  
  net_->Reshape();//初始化网络各层  
  std::vector<Mat> input_channels;  
  Init_Img(img, &input_channels);//将输入图片放入网络的输入blob  
  net_->Forward();//网络前向传播  
  Blob<float>* output_layer = net_->output_blobs()[0];  
  const float* begin = output_layer->cpu_data();  
  const float* end = begin + output_layer->channels();  
  return vector<float>(begin, end);//获取输入图片属于各个类的概率  
}  
  
void Classifier::Init_Img(const Mat& img, std::vector<Mat>* input_channels) {  
  Blob<float>* input_layer = net_->input_blobs()[0];  
  int width = input_layer->width();//网络规定的输入图像的宽  
  int height = input_layer->height();//网络规定的输入图像的高  
  float* input_data = input_layer->mutable_cpu_data();  
  for (int i = 0; i < input_layer->channels(); ++i) {  
    Mat channel(height, width, CV_32FC1, input_data);  
    input_channels->push_back(channel);  
    input_data += width * height;  
  }//这个for循环将网络的输入blob同input_channels关联起来  
  Mat sample_float;  
  img.convertTo(sample_float, CV_32FC3);  
  Mat sample_normalized;  
  subtract(sample_float, Scalar(129.52675, 128.78506, 116.44242), sample_normalized);//减去均值，均值可以自己求，也可以通过.binaryproto均值文件求出  
  split(sample_normalized, *input_channels);//将输入图片放入input_channels，即放入了网络的输入blob  
}  

```
##### 网络初始化的工作:
* 设置工作模式 CPU/GPU
* 引入网络定义
* 引入参数文件
* 设置网络为训练模式,只进行前向传播
* 导入网络参数
* 利用`Blob<float>* input_layer`接收网络input_blobs
* 获取网络的输入图像尺寸 weight and height
* 利用`Blob<float>* output_layer`接受网络的output_blobs

 利用Classifier classifier;//进行类对象初始化 
##### 网络使用
vector<float> result = classifier.Classify(img);//进行网络前传  利用vector中的resul接收结果
调用classifier的Classify方法

vector<float> Classifier::Classify(const Mat& img) { };
接收Mat& img作为参数

* 设定图片通道数
* 将网络中的net_->input_layer传递给`Blob<float>* input_layer`
* 网络输入blob(1,3,height,width)
* 初始化网络 `net_->Reshape();`
* 设置input_channels 病将图片初始化
* 设置网络前向传播
* 利用output_layer接收net_->output_blobs()[0]
* 获得相关识别概率


其中初始化图片由`void Classifier::Init_Img(const Mat& img, std::vector<Mat>* input_channels) { };`完成

接收Mat& img和input_channels

*  利用`Blob<float>* input_layer`接收网络input_blobs()[0]
*  获取网络的图像宽高
*  将输入blob同input_channels关联


>convertTO函数是将一种类型的矩阵转换为另一种类型
```
Mat image_8U = Mat(6,6,CV_8UC3);//声明一个6*6大小的类型为CV_8UC3的图像  
Mat image_32F;//目标图像  
image_8U.convertTo(image_32F,CV_32FC3);//把CV_8UC3类型的图像转换成CV_32FC3类型
```
>subtract

```
C++: void subtract(InputArray src1, InputArray src2, OutputArray dst, InputArray mask=noArray(), int dtype=-1)
```
