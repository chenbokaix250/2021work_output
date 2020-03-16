#!/usr/bin/env python
# coding: utf-8

# In[1]:


import cv2 as cv
from scipy.spatial import distance
import numpy as np
from collections import OrderedDict


# In[2]:


class Tracker:
    def __init__(self, maxLost = 30):           # maxLost: maximum object lost counted when the object is being tracked
        self.nextObjectID = 0                   # ID of next object
        self.objects = OrderedDict()            # stores ID:Locations
        self.lost = OrderedDict()               # stores ID:Lost_count
        
        self.maxLost = maxLost                  # maximum number of frames object was not detected.
        
    def addObject(self, new_object_location):
        self.objects[self.nextObjectID] = new_object_location    # store new object location
        self.lost[self.nextObjectID] = 0                         # initialize frame_counts for when new object is undetected
        
        self.nextObjectID += 1
    
    def removeObject(self, objectID):                          # remove tracker data after object is lost
        del self.objects[objectID]
        del self.lost[objectID]
    
    @staticmethod
    def getLocation(bounding_box):
        xlt, ylt, xrb, yrb = bounding_box
        return (int((xlt + xrb) / 2.0), int((ylt + yrb) / 2.0))
    
    def update(self,  detections):
        
        if len(detections) == 0:   # if no object detected in the frame
            lost_ids = list(self.lost.keys())
            for objectID in lost_ids:
                self.lost[objectID] +=1
                if self.lost[objectID] > self.maxLost: self.removeObject(objectID)
            
            return self.objects
        
        new_object_locations = np.zeros((len(detections), 2), dtype="int")     # current object locations
        
        for (i, detection) in enumerate(detections): new_object_locations[i] = self.getLocation(detection)
            
        if len(self.objects)==0:
            for i in range(0, len(detections)): self.addObject(new_object_locations[i])
        else:
            objectIDs = list(self.objects.keys())
            previous_object_locations = np.array(list(self.objects.values()))
            
            D = distance.cdist(previous_object_locations, new_object_locations) # pairwise distance between previous and current
            
            row_idx = D.min(axis=1).argsort()   # (minimum distance of previous from current).sort_as_per_index
            print(row_idx)
            print(type(row_idx))
            cols_idx = D.argmin(axis=1)[row_idx]   # index of minimum distance of previous from current
            print(cols_idx)
            print(type(cols_idx))
            assignedRows, assignedCols = set(), set()
            
            for (row, col) in zip(row_idx, cols_idx):
                
                if row in assignedRows or col in assignedCols:
                    continue
                
                objectID = objectIDs[row]
                self.objects[objectID] = new_object_locations[col]
                self.lost[objectID] = 0
                
                assignedRows.add(row)
                assignedCols.add(col)
                
            unassignedRows = set(range(0, D.shape[0])).difference(assignedRows)
            unassignedCols = set(range(0, D.shape[1])).difference(assignedCols)
            
            
            if D.shape[0]>=D.shape[1]:
                for row in unassignedRows:
                    objectID = objectIDs[row]
                    self.lost[objectID] += 1
                    
                    if self.lost[objectID] > self.maxLost:
                        self.removeObject(objectID)
                        
            else:
                for col in unassignedCols:
                    self.addObject(new_object_locations[col])
            
        return self.objects


# In[3]:


model_info = {"config_path":"./faster_rcnn_resnet50_coco_2018_01_28/faster_rcnn_resnet50_coco_2018_01_28.pbtxt",
              "model_weights_path":"./faster_rcnn_resnet50_coco_2018_01_28/frozen_inference_graph.pb",
              "object_names": {0: 'background',
                          1: 'person', 2: 'bicycle', 3: 'car', 4: 'motorcycle', 5: 'airplane', 6: 'bus',
                          7: 'train', 8: 'truck', 9: 'boat', 10: 'traffic light', 11: 'fire hydrant',
                          13: 'stop sign', 14: 'parking meter', 15: 'bench', 16: 'bird', 17: 'cat',
                          18: 'dog', 19: 'horse', 20: 'sheep', 21: 'cow', 22: 'elephant', 23: 'bear',
                          24: 'zebra', 25: 'giraffe', 27: 'backpack', 28: 'umbrella', 31: 'handbag',
                          32: 'tie', 33: 'suitcase', 34: 'frisbee', 35: 'skis', 36: 'snowboard',
                          37: 'sports ball', 38: 'kite', 39: 'baseball bat', 40: 'baseball glove',
                          41: 'skateboard', 42: 'surfboard', 43: 'tennis racket', 44: 'bottle',
                          46: 'wine glass', 47: 'cup', 48: 'fork', 49: 'knife', 50: 'spoon',
                          51: 'bowl', 52: 'banana', 53: 'apple', 54: 'sandwich', 55: 'orange',
                          56: 'broccoli', 57: 'carrot', 58: 'hot dog', 59: 'pizza', 60: 'donut',
                          61: 'cake', 62: 'chair', 63: 'couch', 64: 'potted plant', 65: 'bed',
                          67: 'dining table', 70: 'toilet', 72: 'tv', 73: 'laptop', 74: 'mouse',
                          75: 'remote', 76: 'keyboard', 77: 'cell phone', 78: 'microwave', 79: 'oven',
                          80: 'toaster', 81: 'sink', 82: 'refrigerator', 84: 'book', 85: 'clock',
                          86: 'vase', 87: 'scissors', 88: 'teddy bear', 89: 'hair drier', 90: 'toothbrush'},
              "confidence_threshold": 0.5,
              "threshold": 0.4
             }

net = cv.dnn.readNetFromTensorflow(model_info["model_weights_path"], model_info["config_path"])


# In[6]:


get_ipython().system('pwd')


# In[7]:


np.random.seed(12345)

bbox_colors = {key: np.random.randint(0, 255, size=(3,)).tolist() for key in model_info['object_names'].keys()}


# In[8]:


maxLost = 5   # maximum number of object losts counted when the object is being tracked
tracker = Tracker(maxLost = maxLost)


# In[9]:


video_src = "./1080p1.mp4"#0
cap = cv.VideoCapture(video_src)


# In[10]:


(H, W) = (None, None)  # input image height and width for the network
writer = None
while(True):
    
    ok, image = cap.read()
    
    if not ok:
        print("Cannot read the video feed.")
        break
    
    if W is None or H is None: (H, W) = image.shape[:2]
    
    blob = cv.dnn.blobFromImage(image, size=(300, 300), swapRB=True, crop=False)
    net.setInput(blob)
    detections = net.forward()
    
    detections_bbox = []     # bounding box for detections
    
    boxes, confidences, classIDs = [], [], []
    
    for detection in detections[0, 0, :, :]:
        classID = detection[1]
        confidence = detection[2]

        if confidence > model_info['confidence_threshold']:
            box = detection[3:7] * np.array([W, H, W, H])
            
            (left, top, right, bottom) = box.astype("int")
            width = right - left + 1
            height = bottom - top + 1

            boxes.append([int(left), int(top), int(width), int(height)])
            confidences.append(float(confidence))
            classIDs.append(int(classID))
    
    indices = cv.dnn.NMSBoxes(boxes, confidences, model_info["confidence_threshold"], model_info["threshold"])
    
    if len(indices)>0:
        for i in indices.flatten():
            x, y, w, h = boxes[i][0], boxes[i][1], boxes[i][2], boxes[i][3]
            
            detections_bbox.append((x, y, x+w, y+h))
            
            clr = [int(c) for c in bbox_colors[classIDs[i]]]
            cv.rectangle(image, (x, y), (x+w, y+h), clr, 2)
            
            label = "{}:{:.4f}".format(model_info["object_names"][classIDs[i]], confidences[i])
            (label_width, label_height), baseLine = cv.getTextSize(label, cv.FONT_HERSHEY_SIMPLEX, 0.5, 2)
            y_label = max(y, label_height)
            cv.rectangle(image, (x, y_label-label_height),
                                 (x+label_width, y_label+baseLine), (255, 255, 255), cv.FILLED)
            cv.putText(image, label, (x, y_label), cv.FONT_HERSHEY_SIMPLEX, 0.5, clr, 2)
    
    objects = tracker.update(detections_bbox)           # update tracker based on the newly detected objects
    
    for (objectID, centroid) in objects.items():
        text = "ID {}".format(objectID)
        cv.putText(image, text, (centroid[0] - 10, centroid[1] - 10), cv.FONT_HERSHEY_SIMPLEX,
                    0.5, (0, 255, 0), 2)
        cv.circle(image, (centroid[0], centroid[1]), 4, (0, 255, 0), -1)
        
    cv.imshow("image", image)
    
    if cv.waitKey(1) & 0xFF == ord('q'):
        break
        
    if writer is None:
        fourcc = cv.VideoWriter_fourcc(*"MJPG")
        writer = cv.VideoWriter("output.avi", fourcc, 30, (W, H), True)
    writer.write(image)
writer.release()
cap.release()
cv.destroyWindow("image")


# In[ ]:




