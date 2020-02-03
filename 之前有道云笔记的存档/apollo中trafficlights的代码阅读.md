## base 

### utils
- ClearBox 清空矩形
- BoxIsValid 确定盒子可用
- refineBox 重新定义盒尺寸
- GetCenter 找到中心 返回Point2f
- Get2dGaussianScore 获取高斯2维值（最小二乘法?）
- Get2dGaussianScore 获取高斯1维值


### light
- Distance2Stopline 车位置到stopline的距离

### pose
- set_pose 车位置设定 bool
- pose 车位置获取 Matrix4d

### tl_shared_data
- kColorStr map string->TLColor

### image
- Image::Init 分为mat和image_data
- Image::ts 获取时间戳timestamp
- Image::camera_id 获取相机camera_id
- Image::camera_id_str
- Image::GenerateMat 将image_data赋值给mat_
- Image::mat 获取mat_
- Image::size 获取mat.size

***

## preprocessor

### tl_preprocessor
- TLPreprocessor::Init 从config中获取parameters
- TLPreprocessor::CacheLightsProjections 缓存灯光的投影 传入carpose signals timestamp
- TLPreprocessor::SyncImage 同步图片
- TLPreprocessor::set_last_pub_camera_id
- TLPreprocessor::last_pub_camera_id
- TLPreprocessor::max_cached_lights_size
- TLPreprocessor::SelectImage
- TLPreprocessor::IsOnBorder 确定ROI的边界


## projection

### projection
- BoundaryProjection::Project 
- BoundaryProjection::ProjectPoint
- 
### multi_camera_projection
-  MultiCamerasProjection::Init
-  MultiCamerasProjection::Project


## recognizer
### classify
> ClassifyBySimple::ClassifyBySimple
- ClassifyBySimple::SetCropBox
- ClassifyBySimple::Init
- ClassifyBySimple::Perform

std::vector<LightPtr> *lights 包括 hdmap signal、LightRegion region、LightStatus status


- ClassifyBySimple::ProbToColor


### unity_recognize
- UnityRecognize::Init
- UnityRecognize::InitModel
- UnityRecognize::RecognizeStatus
- UnityRecognize::name


## rectify
### cropbox
- CropBox::GetCropBox
- CropBox::Init
- CropBoxWholeImage::GetCropBox

### decetion
- Detection::Perform
- Detection::Init
- Detection::Detection
- Detection::SelectOutputBboxes
- Detection::SetCropBox

 
### selected
- GaussianSelect::Select


### unity_rectify
- UnityRectify::Init
- UnityRectify::InitDetection
- UnityRectify::Rectify