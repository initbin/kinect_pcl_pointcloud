#include "image_to_pointcloud.h"
#include "get_image.h"

//调整背景颜色
void viewerOneOff (pcl::visualization::PCLVisualizer& viewer)
{
    viewer.setBackgroundColor (0.5, 0.5, 1.0);
}


int main()
{
	//kinect_init();//摄像
	pcl_init();//点云提取
 
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::io::loadPCDFile("colorImage.pcd", *cloud);//加载点云文件
 
	pcl::visualization::CloudViewer viewer("Cloude Viewer");//创建viewer对象
 
	viewer.showCloud(cloud);
 
	//运行一次这个函数
	viewer.runOnVisualizationThreadOnce(viewerOneOff);
 
	//每次可视化迭代都要调用一下
	//viewer.runOnVisualizationThread(viewerPsycho);
	while (!viewer.wasStopped())  //窗口保持
	{
	}
	return 0;

}