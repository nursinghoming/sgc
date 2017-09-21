
#include <opencv2/opencv.hpp>  
#include <cstdio>  
#include <cstdlib>  
#include <Windows.h>  
using namespace std;  
int main()  
{  

	// ����Haar������������  
	// haarcascade_frontalface_alt.xmlϵOpenCV�Դ��ķ����� �������һ����ϵ��ļ�·��  
	//const char *pstrCascadeFileName = "E:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml";  
	////const char *pstrCascadeFileName ="C:\\Users\\Administrator\\Desktop\\��Ⱥ���㷨\\testface1226\\cascades.xml"; 
	const char *pstrCascadeFileName ="E:\\opencv�궨\\testface\\cascades.xml";
	//const char *pstrCascadeFileName = "C:\\Users\\Administrator\\Desktop\\��Ⱥ���㷨\\readvideo_camshiftkalman1108\\readvideo_camshiftkalman927����ȥ��Ӱ��\\train_head\\cascade.xml"; 
	CvHaarClassifierCascade *pHaarCascade = NULL;  
	pHaarCascade = (CvHaarClassifierCascade*)cvLoad(pstrCascadeFileName);  


	////char *video="C:\\Users\\Administrator\\Desktop\\��Ⱥ���㷨\\testface1226\\2.avi";//��Ƶ�ļ������ֿ����޸�
	char *video="E:\\opencv�궨\\testface\\1.avi";
	CvCapture *cap=cvCaptureFromAVI(video);//����Ƶ�ļ��ж�ȡ
	/*CvCapture *cap=cvCaptureFromCAM(0);*///������ͷ��׽
	IplImage *pSrcImage=cvQueryFrame(cap);//��ȡһ֡
	//��ȡ��Ƶ�ļ��Ĳ���
	int frameHeight  =(int) cvGetCaptureProperty(cap,CV_CAP_PROP_FRAME_HEIGHT);//֡�߶�
	int frameWidth   =(int) cvGetCaptureProperty(cap,CV_CAP_PROP_FRAME_WIDTH);//֡���
	int fps          =(int) cvGetCaptureProperty(cap,CV_CAP_PROP_FPS);//֡��
	int numFrames    =(int) cvGetCaptureProperty(cap,CV_CAP_PROP_FRAME_COUNT);//֡��
	CvVideoWriter *writer=cvCreateVideoWriter("out1.avi",CV_FOURCC('x','v','i','d'),fps,cvSize(frameWidth,frameHeight));//���ڲ�ɫ��Ƶ�ļ�
	//// ����ͼ��  
	//const char *pstrImageName = "C:\\Users\\Administrator\\Desktop\\��Ⱥ���㷨\\testface\\1.jpg";  
	//IplImage *pSrcImage = cvLoadImage(pstrImageName, CV_LOAD_IMAGE_UNCHANGED);  

	IplImage *pGrayImage = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);  


	// ����ʶ������  
	if (pHaarCascade != NULL)  
	{         
		CvScalar FaceCirclecolors[] =   
		{  
			{{0, 0, 255}},  
			{{0, 128, 255}},  
			{{0, 255, 255}},  
			{{0, 255, 0}},  
			{{255, 128, 0}},  
			{{255, 255, 0}},  
			{{255, 0, 0}},  
			{{255, 0, 255}}  
		};  

		CvMemStorage *pcvMStorage = cvCreateMemStorage(0);  
		
	while (pSrcImage)
	{
		    cvClearMemStorage(pcvMStorage);
		  	cvCvtColor(pSrcImage, pGrayImage, CV_BGR2GRAY);  
			// ʶ��  
			DWORD dwTimeBegin, dwTimeEnd;  
			dwTimeBegin = GetTickCount(); 
			//cvShowImage("pGrayImage",pGrayImage);
			CvSeq *pcvSeqFaces = cvHaarDetectObjects(pGrayImage, pHaarCascade, pcvMStorage);  
			dwTimeEnd = GetTickCount();  

			printf("��������: %d   ʶ����ʱ: %d ms\n", pcvSeqFaces->total, dwTimeEnd - dwTimeBegin);  

			// ���  
			for(int i = 0; i <pcvSeqFaces->total; i++)  
			{  
				CvRect* r = (CvRect*)cvGetSeqElem(pcvSeqFaces, i);  
				CvPoint center;  
				int radius;  
				center.x = cvRound((r->x + r->width * 0.5));  
				center.y = cvRound((r->y + r->height * 0.5));  
				radius = cvRound((r->width + r->height) * 0.25);  
				cvCircle(pSrcImage, center, radius, FaceCirclecolors[i % 8], 2);  
			}  
			cvWriteFrame(writer,pSrcImage);
			pSrcImage=cvQueryFrame(cap);
			  
		}  
	cvReleaseMemStorage(&pcvMStorage);
	}
	

	/*const char *pstrWindowsTitle = "����ʶ�� ";  
	cvNamedWindow(pstrWindowsTitle, CV_WINDOW_AUTOSIZE);  
	cvShowImage(pstrWindowsTitle, pSrcImage);  

	cvWaitKey(0);  

	cvDestroyWindow(pstrWindowsTitle);  */
	cvReleaseImage(&pSrcImage);   
	cvReleaseImage(&pGrayImage);  
	return 0;  
}  