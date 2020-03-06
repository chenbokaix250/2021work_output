# Inception-v3图片分类

Inception-v3是由Google提出，用于实现ImageNet大规模视觉识别任务（ImageNet Large Visual Recognition Challenge）的一种神经网络



![img](https://user-gold-cdn.xitu.io/2018/9/19/165f22c117200016?imageslim)

Inception-v3反复使用了Inception Block，涉及大量的卷积和池化，而ImageNet包括1400多万张图片，类别数超过1000

因此手动在ImageNet上训练Inception-v3，需要耗费大量的资源和时间

这里我们选择加载pre-trained的Inception-v3模型，来完成一些图片分类任务

## 准备

预训练好的模型共包括三个部分

- `classify_image_graph_def.pb`：Inception-v3模型结构和参数
- `imagenet_2012_challenge_label_map_proto.pbtxt`：从类别编号到类别字符串的对应关系
- `imagenet_synset_to_human_label_map.txt`：从类别字符串到类别名的对应关系

例如，`169`对应`n02510455`，对应`giant panda, panda, panda bear, coon bear, Ailuropoda melanoleuca`



## 图片分类

加载库

```python
# -*- coding: utf-8 -*-

import tensorflow as tf
import numpy as np
复制代码
```

整理两个映射文件，得到从类别编号到类别名的对应关系

```python
uid_to_human = {}
for line in tf.gfile.GFile('imagenet_synset_to_human_label_map.txt').readlines():
	items = line.strip().split('\t')
	uid_to_human[items[0]] = items[1]

node_id_to_uid = {}
for line in tf.gfile.GFile('imagenet_2012_challenge_label_map_proto.pbtxt').readlines():
	if line.startswith('  target_class:'):
		target_class = int(line.split(': ')[1])
	if line.startswith('  target_class_string:'):
		target_class_string = line.split(': ')[1].strip('\n').strip('\"')
		node_id_to_uid[target_class] = target_class_string

node_id_to_name = {}
for key, value in node_id_to_uid.items():
	node_id_to_name[key] = uid_to_human[value]
复制代码
```

加载模型

```python
def create_graph():
	with tf.gfile.FastGFile('classify_image_graph_def.pb', 'rb') as f:
		graph_def = tf.GraphDef()
		graph_def.ParseFromString(f.read())
		_ = tf.import_graph_def(graph_def, name='')
复制代码
```

定义一个分类图片的函数

```python
def classify_image(image, top_k=1):
	image_data = tf.gfile.FastGFile(image, 'rb').read()

	create_graph()

	with tf.Session() as sess:
		# 'softmax:0': A tensor containing the normalized prediction across 1000 labels
		# 'pool_3:0': A tensor containing the next-to-last layer containing 2048 float description of the image
		# 'DecodeJpeg/contents:0': A tensor containing a string providing JPEG encoding of the image
		softmax_tensor = sess.graph.get_tensor_by_name('softmax:0')
		predictions = sess.run(softmax_tensor, feed_dict={'DecodeJpeg/contents:0': image_data})
		predictions = np.squeeze(predictions)

		top_k = predictions.argsort()[-top_k:]
		for node_id in top_k:
			human_string = node_id_to_name[node_id]
			score = predictions[node_id]
			print('%s (score = %.5f)' % (human_string, score))
复制代码
```

调用函数进行图片分类，指定参数`top_k`可以返回最可能的多种分类结果

```python
classify_image('test1.png')
复制代码
```

分类结果如下

- `test1`：giant panda, panda, panda bear, coon bear, Ailuropoda melanoleuca (score = 0.89107)
- `test2`：Pekinese, Pekingese, Peke (score = 0.90348)
- `test3`：Samoyed, Samoyede (score = 0.92054)



# 分类任务定制:手部实时检测器

与inception-v3通过迁移学习实现定制的图片分类任务类似

通过添加手部标注数据,使用训练好的模型完成迁移学习

## 数据



手部检测数据来自于

[vision.soic.indiana.edu/projects/eg…](http://vision.soic.indiana.edu/projects/egohands/)

`egohands_dataset_clean.py`依次完成以下几项工作

- 如果当前目录下没有`egohands_data.zip`则下载，即调用`download_egohands_dataset()`
- 否则解压`egohands_data.zip`并得到`egohands`文件夹，并对其中的图片数据执行`rename_files()`
- `rename_files()`会将所有的图片重命名，加上其父文件夹的名称，避免图片名重复，并调用`generate_csv_files()`
- `generate_csv_files()`读取每个场景下的图片，调用`get_bbox_visualize()`，根据标注文件`polygons.mat`绘制手部轮廓和Anchor Box并显示，同时将图片标注转换并存储为csv文件，全部处理完后，再调用`split_data_test_eval_train()`
- `split_data_test_eval_train()`完成训练集和测试集的分割，在`images`文件夹中新建`train`和`test`两个文件夹，分别存放对应的图片和csv标注
- 完成以上工作后，便可以手动删除一开始解压得到的`egohands`文件夹

也就是从`egohands_data.zip`得到`images`文件夹，在我的笔记本上共花费6分钟左右

接下来调用`generate_tfrecord.py`，将训练集和测试集整理成TFRecord文件

由于这里只需要检测手部，因此物体类别只有一种即`hand`，如果需要定制其他物体检测任务，修改以下代码即可

```
def class_text_to_int(row_label):
    if row_label == 'hand':
        return 1
    else:
        None
复制代码
```

运行以下两条命令，生成训练集和测试集对应的TFRecord文件

```
python generate_tfrecord.py --csv_input=images/train/train_labels.csv  --output_path=retrain/train.record
复制代码
python generate_tfrecord.py --csv_input=images/test/test_labels.csv  --output_path=retrain/test.record
```



## 模型

使用的`ssd_mobilenet_v1_coco`，但这里只需要检测手部，所以需要根据定制的标注数据进行迁移学习

`retrain`文件夹中内容如下

- `train.record`和`test.record`：定制物体检测任务的标注数据
- `ssd_mobilenet_v1_coco_11_06_2017`：预训练好的`ssd_mobilenet_v1_coco`模型
- `ssd_mobilenet_v1_coco.config`：使用迁移学习训练模型的配置文件
- `hand_label_map.pbtxt`：指定检测类别的名称和编号映射
- `retrain.py`：迁移学习的训练代码
- `object_detection`：一些辅助文件

配置文件`ssd_mobilenet_v1_coco.config`的模版在这里

[github.com/tensorflow/…](https://github.com/tensorflow/models/blob/master/research/object_detection/samples/configs/ssd_mobilenet_v1_coco.config)

按需修改配置文件，主要是包括`PATH_TO_BE_CONFIGURED`的配置项

- `num_classes`：物体类别的数量，这里为1
- `fine_tune_checkpoint`：预训练好的模型checkpoint文件
- `train_input_reader`：指定训练数据`input_path`和映射文件路径`label_map_path`
- `eval_input_reader`：指定测试数据`input_path`和映射文件路径`label_map_path`

映射文件`hand_label_map.pbtxt`内容如下，只有一个类别

```
item {
    id: 1
    name: 'hand'
}
复制代码
```

使用以下命令开始模型的迁移训练，`train_dir`为模型输出路径，`pipeline_config_path`为配置项路径

```
python retrain.py --logtostderr --train_dir=output/ --pipeline_config_path=ssd_mobilenet_v1_coco.config
复制代码
```

模型迁移训练完毕后，在`output`文件夹中即可看到生成的`.data`、`.index`、`.meta`等模型文件

使用TensorBoard查看模型训练过程，模型总损失如下

```
tensorboard --logdir='output'
```

![img](https://user-gold-cdn.xitu.io/2018/9/20/165f4a5198cc48d4?imageslim)

最后，再使用`export_inference_graph.py`将模型打包成`.pb`文件

- `--pipeline_config_path`：配置文件路径
- `--trained_checkpoint_prefix`：模型checkpoint路径
- `--output_directory`：`.pb`文件输出路径

```
python export_inference_graph.py --input_type image_tensor --pipeline_config_path retrain/ssd_mobilenet_v1_coco.config  --trained_checkpoint_prefix retrain/output/model.ckpt-153192 --output_directory hand_detection_inference_graph
复制代码
```

运行后会生成文件夹`hand_detection_inference_graph`，里面可以找到一个`frozen_inference_graph.pb`文件


## 应用

现在便可以使用训练好的手部检测模型，实现一个手部实时检测器

主要改动以下三行代码即可

```
PATH_TO_CKPT = 'hand_detection_inference_graph/frozen_inference_graph.pb'
PATH_TO_LABELS = 'retrain/hand_label_map.pbtxt'
NUM_CLASSES = 1
复制代码
```

完整代码如下

```
# -*- coding: utf-8 -*-

import numpy as np
import tensorflow as tf

from utils import label_map_util
from utils import visualization_utils as vis_util

import cv2
cap = cv2.VideoCapture(0)

PATH_TO_CKPT = 'hand_detection_inference_graph/frozen_inference_graph.pb'
PATH_TO_LABELS = 'retrain/hand_label_map.pbtxt'
NUM_CLASSES = 1

detection_graph = tf.Graph()
with detection_graph.as_default():
	od_graph_def = tf.GraphDef()
	with tf.gfile.GFile(PATH_TO_CKPT, 'rb') as fid:
		od_graph_def.ParseFromString(fid.read())
		tf.import_graph_def(od_graph_def, name='')

label_map = label_map_util.load_labelmap(PATH_TO_LABELS)
categories = label_map_util.convert_label_map_to_categories(label_map, max_num_classes=NUM_CLASSES, use_display_name=True)
category_index = label_map_util.create_category_index(categories)

with detection_graph.as_default():
	with tf.Session(graph=detection_graph) as sess:
	    image_tensor = detection_graph.get_tensor_by_name('image_tensor:0')
	    detection_boxes = detection_graph.get_tensor_by_name('detection_boxes:0')
	    detection_scores = detection_graph.get_tensor_by_name('detection_scores:0')
	    detection_classes = detection_graph.get_tensor_by_name('detection_classes:0')
	    num_detections = detection_graph.get_tensor_by_name('num_detections:0')
	    while True:
	    	ret, image_np = cap.read()
	    	image_np = cv2.cvtColor(image_np, cv2.COLOR_BGR2RGB)
	    	image_np_expanded = np.expand_dims(image_np, axis=0)
	    	(boxes, scores, classes, num) = sess.run(
	    		[detection_boxes, detection_scores, detection_classes, num_detections], 
	    		feed_dict={image_tensor: image_np_expanded})
	    	
	    	vis_util.visualize_boxes_and_labels_on_image_array(image_np, np.squeeze(boxes), np.squeeze(classes).astype(np.int32), np.squeeze(scores), category_index, use_normalized_coordinates=True, line_thickness=8)
	    	
	    	cv2.imshow('hand detection', cv2.cvtColor(image_np, cv2.COLOR_RGB2BGR))
	    	if cv2.waitKey(25) & 0xFF == ord('q'):
	    		cap.release()
	    		cv2.destroyAllWindows()
	    		break
复制代码
```

运行代码后，即可看到摄像头中手部检测的结果

![img](https://user-gold-cdn.xitu.io/2018/9/20/165f4a5198d88b90?imageslim)

# 定制检测任务

准备一些图片,然后手动标注,有个几百条就差不多了

使用labelImg进行图片标注,安装方法参考以下链接

[github.com/tzutalin/la…](https://github.com/tzutalin/labelImg)

进入`labelImg`文件夹，使用以下命令，两个参数分别表示图片目录和分类文件路径

```
python labelImg.py ../imgs/ ../predefined_classes.txt
复制代码
```

标注界面如下图所示，按`w`开始矩形的绘制，按`Ctrl+S`保存标注至`xml`文件夹

![img](https://user-gold-cdn.xitu.io/2018/9/20/165f4a5198eab08f?imageslim)

之后运行`xml_to_csv.py`即可将`.xml`文件转为`.csv`文件

总之，为了准备TFRecord数据，按照以下步骤操作

- 新建`train`和`test`文件夹并分配图片
- 分别对训练集和测试集图片手工标注
- 将训练集和测试集对应的多个`.xml`转为一个`.csv`
- 根据原始图片和`.csv`生成对应的TFRecord






