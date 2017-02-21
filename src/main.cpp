#include <iostream>
#include <opencv2/opencv.hpp>
#include <SceneRenderManager.h>
#include <ctime>
#include <io.h>
#include <windows.h>
#include "WinTopFaceSDK.h"
#include <gl/glew.h>
#include "gl/freeglut.h"

using namespace std;
using namespace cv;

sceneRenderer::SceneRenderManager* renderManager;
voomeSDK::WinTopFaceSDK faceSDK;
cv::VideoCapture inputVideo(0);
cv::Mat processImg;
int videoWidth = 800;
int videoHight = 600;

void InitRenderer()
{
	renderManager = new sceneRenderer::SceneRenderManager;
	renderManager->InitWithAutoEnv(0,0,videoWidth, videoHight,"");
	glutSwapBuffers();
	glutPostRedisplay();
}

void Draw()
{
	inputVideo >> processImg;
	if (processImg.empty())
	{
		std::cout << "Not input image.\n";
		return;
	}

	//get gray image
	cv::flip(processImg,processImg,1);
	cv::Mat grayImg;
	if (processImg.channels() == 3)
	{
		cv::cvtColor(processImg, grayImg, CV_BGR2GRAY);
	}
	else if(processImg.channels() == 4)
	{
		cv::cvtColor(processImg, grayImg, CV_BGRA2GRAY);
	}
	else
	{
		grayImg = processImg.clone();
	}

	//detect
	vector<float> face_result;
	float confidence = faceSDK.dynamicDetect(grayImg.data,grayImg.cols,grayImg.rows, face_result);

	//draw points and axes
	for(int i = 0; i < 136; i+=2)
	{
		cv::Point2d p(face_result[i],face_result[i+1]);
		cv::circle(processImg,p, 3, cv::Scalar(0, 255, 0),-1);
	}
	line(processImg,cv::Point2d(face_result[142],face_result[143]),cv::Point2d(face_result[144],face_result[145]),Scalar(0,255,0),2);// x
	line(processImg,cv::Point2d(face_result[142],face_result[143]),cv::Point2d(face_result[146],face_result[147]),Scalar(255,0,0),2);// y
	line(processImg,cv::Point2d(face_result[142],face_result[143]),cv::Point2d(face_result[148],face_result[149]),Scalar(0,0,255),2);// z

	//draw by opengl
	cv::cvtColor(processImg, processImg, CV_BGR2RGB);
	renderManager->SetViewPort(0,0,processImg.cols, processImg.rows);
	renderManager->SetBackGroundData(processImg.data,1,processImg.cols, processImg.rows,0, 0);

	renderManager->UpdateAutoEnv();
	glutSwapBuffers();
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	//请输入正确的clientID和clientSecret
	faceSDK.setLicense("id","secret");

	//初始化
	faceSDK.initWithFocus("sms",31.0);
	if (!inputVideo.isOpened())
	{
		cout<<"can't open camera";
		return -2;
	}
	inputVideo.set(CV_CAP_PROP_FRAME_WIDTH,videoWidth);  
	inputVideo.set(CV_CAP_PROP_FRAME_HEIGHT,videoHight);  

	glutInit(&argc, argv);
	glutInitWindowSize(videoWidth,videoHight);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH|GLUT_DOUBLE|GLUT_MULTISAMPLE);
	glutInitContextVersion(2,1);
	glutCreateWindow("demo");
	if (glewInit()) {
		cerr << "Unable to initialize GLEW ... exiting" << endl;
		exit(EXIT_FAILURE);
	}
	InitRenderer();
	glutDisplayFunc(Draw);
	glutMainLoop();

	return 0;
}