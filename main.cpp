#include "image_to_pointcloud.h"
#include "get_image.h"

//����������ɫ
void viewerOneOff (pcl::visualization::PCLVisualizer& viewer)
{
    viewer.setBackgroundColor (0.5, 0.5, 1.0);
}


int main()
{
	//kinect_init();//����
	pcl_init();//������ȡ
 
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::io::loadPCDFile("colorImage.pcd", *cloud);//���ص����ļ�
 
	pcl::visualization::CloudViewer viewer("Cloude Viewer");//����viewer����
 
	viewer.showCloud(cloud);
 
	//����һ���������
	viewer.runOnVisualizationThreadOnce(viewerOneOff);
 
	//ÿ�ο��ӻ�������Ҫ����һ��
	//viewer.runOnVisualizationThread(viewerPsycho);
	while (!viewer.wasStopped())  //���ڱ���
	{
	}
	return 0;

}