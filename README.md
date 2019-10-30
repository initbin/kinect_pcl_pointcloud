# kinect_pcl_pointcloud
kinectv1+vs2010+pcl1.6.0完成深度图的采集和点云转换。
## 环境 
kinectv1  
vs2010  
opencv2.4.13  
pcl1.6.0
## 功能 
捕获kinect的某一帧深度图进行保存。（按q即可完成保存）
将保存的深度图转换成点云。

## 问题 
保存的深度图和转换后的点云效果对不上，可能的原因是相机内参的设置不对，或者是深度图到点云转换公式有误。

## 参考链接
此是对这个博客的复现。
https://blog.csdn.net/qq_39823565/article/details/78022695
