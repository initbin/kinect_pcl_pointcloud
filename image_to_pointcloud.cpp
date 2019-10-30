#include "image_to_pointcloud.h"

int pcl_init()
{
	//cv::Mat color = cv::imread("1.jpg");
	cv::Mat depth = cv::imread("2.jpg");
 
	int rowNumber = depth.rows;
	int colNumber = depth.cols;
 
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ> cloud_a;
	cloud_a.height = rowNumber;
	cloud_a.width = colNumber;
	cloud_a.points.resize(cloud_a.width * cloud_a.height);
 
	for (unsigned int u = 0; u < rowNumber; ++u)
	{
		for (unsigned int v = 0; v < colNumber; ++v)
		{
			unsigned int num = u*colNumber + v;
			double Xw = 0, Yw = 0, Zw = 0;
 
			//Zw = ((double)depth.at<uchar>(u, v)) / 255.0 * 10001.0;
			Zw = ((double)depth.at<uchar>(u, v)) / factor;
			Xw = (u - cx) * Zw / fx;
			Yw = (v - cy) * Zw / fy;
 
			//cloud_a.points[num].b = color.at<cv::Vec3b>(u, v)[0];
			//cloud_a.points[num].g = color.at<cv::Vec3b>(u, v)[1];
			//cloud_a.points[num].r = color.at<cv::Vec3b>(u, v)[2];
 
			cloud_a.points[num].x = Xw;
			cloud_a.points[num].y = Yw;
			cloud_a.points[num].z = Zw;
		}
	}
 
	*cloud = cloud_a;
	pcl::io::savePCDFile("colorImage.pcd", *cloud);
	/*pcl::visualization::CloudViewer viewer("Cloud Viewer");
 
	viewer.showCloud(cloud);
 
	viewer.runOnVisualizationThreadOnce(viewerOneOff);
 
	while (!viewer.wasStopped())
	{
		user_data = 9;
	}*/
	printf("点云生成完毕\n");
	return 0;
}
