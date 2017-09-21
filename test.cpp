
#include <opencv2/opencv.hpp>  
#include <cstdio>  
#include <cstdlib>  
#include <Windows.h>  
using namespace std;  
int main()  
{  

	// 加载Haar特征检测分类器  
	// haarcascade_frontalface_alt.xml系OpenCV自带的分类器 下面是我机器上的文件路径  
	//const char *pstrCascadeFileName = "E:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml";  
	////const char *pstrCascadeFileName ="C:\\Users\\Administrator\\Desktop\\人群新算法\\testface1226\\cascades.xml"; 
	const char *pstrCascadeFileName ="E:\\opencv标定\\testface\\cascades.xml";
	//const char *pstrCascadeFileName = "C:\\Users\\Administrator\\Desktop\\人群新算法\\readvideo_camshiftkalman1108\\readvideo_camshiftkalman927（加去阴影）\\train_head\\cascade.xml"; 
	CvHaarClassifierCascade *pHaarCascade = NULL;  
	pHaarCascade = (CvHaarClassifierCascade*)cvLoad(pstrCascadeFileName);  


	////char *video="C:\\Users\\Administrator\\Desktop\\人群新算法\\testface1226\\2.avi";//视频文件，名字可以修改
	char *video="E:\\opencv标定\\testface\\1.avi";
	CvCapture *cap=cvCaptureFromAVI(video);//从视频文件中读取
	/*CvCapture *cap=cvCaptureFromCAM(0);*///从摄像头捕捉
	IplImage *pSrcImage=cvQueryFrame(cap);//读取一帧
	//获取视频文件的参数
	int frameHeight  =(int) cvGetCaptureProperty(cap,CV_CAP_PROP_FRAME_HEIGHT);//帧高度
	int frameWidth   =(int) cvGetCaptureProperty(cap,CV_CAP_PROP_FRAME_WIDTH);//帧宽度
	int fps          =(int) cvGetCaptureProperty(cap,CV_CAP_PROP_FPS);//帧率
	int numFrames    =(int) cvGetCaptureProperty(cap,CV_CAP_PROP_FRAME_COUNT);//帧数
	CvVideoWriter *writer=cvCreateVideoWriter("out1.avi",CV_FOURCC('x','v','i','d'),fps,cvSize(frameWidth,frameHeight));//对于彩色视频文件
	//// 载入图像  
	//const char *pstrImageName = "C:\\Users\\Administrator\\Desktop\\人群新算法\\testface\\1.jpg";  
	//IplImage *pSrcImage = cvLoadImage(pstrImageName, CV_LOAD_IMAGE_UNCHANGED);  

	IplImage *pGrayImage = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);  


	// 人脸识别与标记  
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
			// 识别  
			DWORD dwTimeBegin, dwTimeEnd;  
			dwTimeBegin = GetTickCount(); 
			//cvShowImage("pGrayImage",pGrayImage);
			CvSeq *pcvSeqFaces = cvHaarDetectObjects(pGrayImage, pHaarCascade, pcvMStorage);  
			dwTimeEnd = GetTickCount();  

			printf("人脸个数: %d   识别用时: %d ms\n", pcvSeqFaces->total, dwTimeEnd - dwTimeBegin);  

			// 标记  
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
	

	/*const char *pstrWindowsTitle = "人脸识别 ";  
	cvNamedWindow(pstrWindowsTitle, CV_WINDOW_AUTOSIZE);  
	cvShowImage(pstrWindowsTitle, pSrcImage);  

	cvWaitKey(0);  

	cvDestroyWindow(pstrWindowsTitle);  */
	cvReleaseImage(&pSrcImage);   
	cvReleaseImage(&pGrayImage);  
	return 0;  
}  