#include "get_image.h"


int kinect_init()
{
	cv::Mat image;
	//���������ûҶ�ͼ������������ݣ�ԽԶ������Խ����
	image.create(240, 320, CV_8UC1);

	//1����ʼ��NUI��ע�⣺���ﴫ��Ĳ����Ͳ�һ���ˣ���DEPTH
	HRESULT hr = NuiInitialize(NUI_INITIALIZE_FLAG_USES_DEPTH);
	if (FAILED(hr))
	{
		cout << "NuiInitialize failed" << endl;
		return hr;
	}

	//2�������¼���� 
	//������ȡ��һ֡���ź��¼����������KINECT�Ƿ���Կ�ʼ��ȡ��һ֡����
	HANDLE nextColorFrameEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	HANDLE depthStreamHandle = NULL; //����ͼ���������ľ����������ȡ���� 

	//3����KINECT�豸�����ͼ��Ϣͨ��������depthStreamHandle��������ľ�����Ա����Ժ��ȡ
	hr = NuiImageStreamOpen(NUI_IMAGE_TYPE_DEPTH, NUI_IMAGE_RESOLUTION_320x240,
		0, 2, nextColorFrameEvent, &depthStreamHandle);
	if (FAILED(hr))//�ж��Ƿ���ȡ��ȷ 
	{
		cout << "Could not open color image stream video" << endl;
		NuiShutdown();
		return hr;
	}
	namedWindow("depthImage", CV_WINDOW_AUTOSIZE);

	//4����ʼ��ȡ������� 
	while (1)
	{
		const NUI_IMAGE_FRAME * pImageFrame = NULL;

		//4.1�����޵ȴ��µ����ݣ��ȵ��󷵻�
		if (WaitForSingleObject(nextColorFrameEvent, INFINITE) == 0)
		{
			//4.2���ӸղŴ���������������еõ���֡���ݣ���ȡ�������ݵ�ַ����pImageFrame
			hr = NuiImageStreamGetNextFrame(depthStreamHandle, 0, &pImageFrame);
			if (FAILED(hr))
			{
				cout << "Could not get depth image" << endl;
				NuiShutdown();
				return -1;
			}

			INuiFrameTexture * pTexture = pImageFrame->pFrameTexture;
			NUI_LOCKED_RECT LockedRect;

			//4.3����ȡ����֡��LockedRect���������������ݶ���pitchÿ���ֽ�����pBits��һ���ֽڵ�ַ
			//���������ݣ����������Ƕ����ݵ�ʱ��kinect�Ͳ���ȥ�޸���
			pTexture->LockRect(0, &LockedRect, NULL, 0);
			//4.4��ȷ�ϻ�õ������Ƿ���Ч

			if (LockedRect.Pitch != 0)
			{
				//4.5��������ת��ΪOpenCV��Mat��ʽ
				for (int i = 0; i<image.rows; i++)
				{
					uchar *ptr = image.ptr<uchar>(i);  //��i�е�ָ��

					//���ͼ�����ݺ������ָ�ʽ���������صĵ�12λ��ʾһ�����ֵ����4λδʹ�ã�
					//ע��������Ҫת������Ϊÿ��������2���ֽڣ��洢��ͬ�������ɫ��Ϣ��һ����
					uchar *pBufferRun = (uchar*)(LockedRect.pBits) + i * LockedRect.Pitch;
					USHORT * pBuffer = (USHORT*)pBufferRun;

					for (int j = 0; j<image.cols; j++)
					{

						ptr[j] = 255 - (uchar)(256 * pBuffer[j] / 0x0fff);  //ֱ�ӽ����ݹ�һ������
					}
				}
				//cout << "��ֵ�� " << (sum/a++) << endl;
				imshow("depthImage", image); //��ʾͼ�� 

			}
			else
			{
				cout << "Buffer length of received texture is bogus\r\n" << endl;
			}

			//5����֡�Ѿ��������ˣ����Խ������
			pTexture->UnlockRect(0);

			//6���ͷű�֡���ݣ�׼��ӭ����һ֡ 

			NuiImageStreamReleaseFrame(depthStreamHandle, pImageFrame);
		}
		if (cvWaitKey(20) == 'q')
		{
			imwrite("2.jpg", image);
			//imshow("��ȡ�����ͼ", image);
			//imwrite("1.jpg", colorImage);
			//imshow("��ȡ�Ĳ�ɫͼ", colorImage);

			//Sleep(10000);
			break;
		}
			
	}
	//7���ر�NUI���� 
	NuiShutdown();
	return 0;
}
