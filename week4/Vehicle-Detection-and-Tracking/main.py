#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""@author: kyleguan
"""

import numpy as np
import matplotlib.pyplot as plt
import glob
from moviepy.editor import VideoFileClip
from collections import deque # 双向队列
from sklearn.utils.linear_assignment_ import linear_assignment
import time
import helpers
import detector
import tracker
from tracker import Tracker
from detector import CarDetector
from helpers import box_iou2
# Global variables to be used by funcitons of VideoFileClop
frame_count = 0 # frame counter

max_age = 5  # no.of consecutive unmatched detection before
             # a track is deleted

min_hits = 2 # no. of consecutive matches needed to establish a track
#建立追踪所需要的最小匹配数
tracker_list =[] # list for trackers
# list for track ID
track_id_list= deque(['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'])

debug = True

#建立识别和跟踪的关系 参数:跟踪/识别 iou_thrd表示重叠率(相关性/匹配程度)
def assign_detections_to_trackers(trackers, detections, iou_thrd = 0.3):
    '''
    From current list of trackers and new detections, output matched detections,
    unmatchted trackers, unmatched detections.
    '''    
    
    IOU_mat= np.zeros((len(trackers),len(detections)),dtype=np.float32)
    #建立长宽为跟踪器和识别器的零矩阵
    for t,trk in enumerate(trackers):
        #trk = convert_to_cv2bbox(trk) 
        for d,det in enumerate(detections):
         #   det = convert_to_cv2bbox(det)
            IOU_mat[t,d] = box_iou2(trk,det) 
    #遍历填满 IOU_mat
    # Produces matches       
    # Solve the maximizing the sum of IOU assignment problem using the
    # Hungarian algorithm (also known as Munkres algorithm)
    
    matched_idx = linear_assignment(-IOU_mat)        
    #linear_assignment用于实现匈牙利算法的最大匹配
    unmatched_trackers, unmatched_detections = [], []
    
    for t,trk in enumerate(trackers):
        if(t not in matched_idx[:,0]):
            unmatched_trackers.append(t)

    for d, det in enumerate(detections):
        if(d not in matched_idx[:,1]):
            unmatched_detections.append(d)
    #没有匹配成功的存在unmatched_trackers/unmatched_detections
    matches = []
   
    # For creating trackers we consider any detection with an 
    # overlap less than iou_thrd to signifiy the existence of 
    # an untracked object
    
    for m in matched_idx:
        if(IOU_mat[m[0],m[1]]<iou_thrd):
            unmatched_trackers.append(m[0])
            unmatched_detections.append(m[1])
        else:
            matches.append(m.reshape(1,2))
    #根据匹配率剔除相关性低的目标
    if(len(matches)==0):
        matches = np.empty((0,2),dtype=int)
    else:
        matches = np.concatenate(matches,axis=0)
    #np.concatenate 用于对数组进行拼接
    return matches, np.array(unmatched_detections), np.array(unmatched_trackers)       
    #返回 匹配组 和没有匹配的detection和tracker


def pipeline(img):#图片管道
    '''
    Pipeline function for detection and tracking
    '''
    global frame_count
    global tracker_list
    global max_age
    global min_hits
    global track_id_list
    global debug
    
    frame_count+=1
    
    img_dim = (img.shape[1], img.shape[0])#获取图片尺寸
    z_box = det.get_localization(img) # measurement
    #利用detection得到car_boxes
    if debug:
       print('Frame:', frame_count)
       
    x_box =[]# 清零
    if debug: 
        for i in range(len(z_box)):
           img1= helpers.draw_box_label(img, z_box[i], box_color=(255, 0, 0))
           plt.imshow(img1)
        plt.show()
    #利用helper标注label
    if len(tracker_list) > 0:
        for trk in tracker_list:
            x_box.append(trk.box)
    #遍历tracker_list
    
    matched, unmatched_dets, unmatched_trks \
    = assign_detections_to_trackers(x_box, z_box, iou_thrd = 0.3)
    #接收返回值
    if debug:
         print('Detection: ', z_box)
         print('x_box: ', x_box)
         print('matched:', matched)
         #print('matched type',type(matched))
         #print('matched shape',matched.shape)
         print('unmatched_det:', unmatched_dets)
         print('unmatched_trks:', unmatched_trks)
    
    #eg
    #Frame: 2
    # Detection:  [array([ 410, 1080,  520, 1273]), array([415, 832, 480, 938])]  z_box
    # x_box:  [[417, 822, 494, 952], [404, 1036, 491, 1218]]
    # matched: [[0 1]
    #  [1 0]]      matched 说明z_box和x_box的对应关系
    # unmatched_det: []
    # unmatched_trks: []
    # Ending tracker_list:  2
    # Ending good tracker_list:  0
    # [413 791 475 895] , confidence:  0.8680635 ratio: 0.5960965291798865
    # wrong ratio or wrong size,  [ 426 1185  532 1274] , confidence:  0.33806056 ratio: 1.190877429502303
    # Deal with matched detections     
    if matched.size >0:
        for trk_idx, det_idx in matched:
            z = z_box[det_idx]
            z = np.expand_dims(z, axis=0).T
            tmp_trk= tracker_list[trk_idx] #object Trackers
            tmp_trk.kalman_filter(z) #卡尔曼滤波
            xx = tmp_trk.x_state.T[0].tolist() #得到新的x_state
            xx =[xx[0], xx[2], xx[4], xx[6]]
            x_box[trk_idx] = xx #更新tracker中的box
            tmp_trk.box =xx
            tmp_trk.hits += 1
            tmp_trk.no_losses = 0
    #对于match的目标和跟踪 进行卡尔曼滤波 更新迭代状态 更新hist loss清零
    # Deal with unmatched detections      
    if len(unmatched_dets)>0:
        for idx in unmatched_dets:
            z = z_box[idx]
            z = np.expand_dims(z, axis=0).T #添加维度后 转置
            tmp_trk = Tracker() # Create a new tracker
            x = np.array([[z[0], 0, z[1], 0, z[2], 0, z[3], 0]]).T
            tmp_trk.x_state = x
            tmp_trk.predict_only() #预测得到新的x_state
            xx = tmp_trk.x_state
            xx = xx.T[0].tolist()
            xx =[xx[0], xx[2], xx[4], xx[6]]
            tmp_trk.box = xx
            tmp_trk.id = track_id_list.popleft() # assign an ID for the tracker
            tracker_list.append(tmp_trk)
            x_box.append(xx)
    #对于没有匹配的目标 进行卡尔曼预测  得到的box加入tracker中
    # Deal with unmatched tracks       
    if len(unmatched_trks)>0:
        for trk_idx in unmatched_trks:
            tmp_trk = tracker_list[trk_idx]
            tmp_trk.no_losses += 1
            tmp_trk.predict_only()
            xx = tmp_trk.x_state
            xx = xx.T[0].tolist()
            xx =[xx[0], xx[2], xx[4], xx[6]]
            tmp_trk.box =xx
            x_box[trk_idx] = xx
                   
    # 对丢失的跟踪 更新loss 做卡尔曼预测 得到的box加入x_box z
    # 总结:
    # 三种目标遍历的不同
    # 匹配到的 loss清零 增加更新hist(用于备选)
    # 独立的det 左加入tracker_list(用于为下次选准备ihist)
    # 独立的trk 累加loss
    #
    # The list of tracks to be annotated  
    good_tracker_list =[]
    for trk in tracker_list:
        if ((trk.hits >= min_hits) and (trk.no_losses <=max_age)):
             good_tracker_list.append(trk)
             x_cv2 = trk.box
             if debug:
                 print('updated box: ', x_cv2)
                 print()
             img= helpers.draw_box_label(img, x_cv2) # Draw the bounding boxes on the 
                                             # images
    # 遍历tracker_list 得到符合条件的good_tracker_list
    # Book keeping
    deleted_tracks = filter(lambda x: x.no_losses >max_age, tracker_list)  
    # 得到剔除的tracker
    for trk in deleted_tracks:
            track_id_list.append(trk.id)
    
    tracker_list = [x for x in tracker_list if x.no_losses<=max_age]
     
    if debug:
       print('Ending tracker_list: ',len(tracker_list))
       print('Ending good tracker_list: ',len(good_tracker_list))
    
       
    return img
    
if __name__ == "__main__":    
    
    det = detector.CarDetector()
    
    if debug: # test on a sequence of images
        images = [plt.imread(file) for file in glob.glob('./test_images/*.jpg')]
        
        for i in range(len(images))[0:7]:
             image = images[i]
             image_box = pipeline(image)   
             plt.imshow(image_box)
             plt.show()
           
    else: # test on a video file.
        
        start=time.time()
        output = 'test_v7-1.mp4'
        clip1 = VideoFileClip("project_video.mp4")#.subclip(4,49) # The first 8 seconds doesn't have any cars...
        clip = clip1.fl_image(pipeline)
        clip.write_videofile(output, audio=False)
        end  = time.time()
        
        print(round(end-start, 2), 'Seconds to finish')
