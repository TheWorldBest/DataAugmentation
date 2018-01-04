#include "subFunction.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

DataAugmentation::DataAugmentation(std::string imgPath)
{
	img = imread(imgPath);

}

double DataAugmentation::generateGaussianNoise(double mu, double sigma)  //mu=0.2  sigma=0.3
{
	//����һ���ر�С��ֵ  
	const double epsilon = numeric_limits<double>::min();//����Ŀ�����������ܱ�ʾ����ƽ�1��������1�Ĳ�ľ���ֵ  
	static double z0, z1;
	static bool flag = false;
	flag = !flag;
	//flagΪ�٣������˹�������  
	if (!flag)
		return z1*sigma + mu;
	double u1, u2;
	//�����������  

	do
	{
		u1 = rand()*(1.0 / RAND_MAX);
		u2 = rand()*(1.0 / RAND_MAX);
	} while (u1 <= epsilon);
	//flagΪ�湹���˹�������X  
	z0 = sqrt(-2.0*log(u1))*cos(2 * CV_PI * u2);
	z1 = sqrt(-2.0*log(u1))*sin(2 * CV_PI * u2);
	return z1*sigma + mu;
}


Mat DataAugmentation::mirrorImg()
{
	Mat resultImage;
	flip(img, resultImage, 1);  //ˮƽ��ת
	return resultImage;
}

Mat DataAugmentation::rotationImg(double degreeR)
{
	Mat resultImage;
	int len = max(img.cols, img.rows);
	Point2f pt(len * 0.5, len * 0.5);
	Mat r = getRotationMatrix2D(pt, degreeR, 1.0);
	warpAffine(img, resultImage, r, Size(len, len), INTER_LINEAR, IPL_BORDER_REPLICATE);
	return resultImage;
}

Mat DataAugmentation::addNoiseGaussianImg(double mu, double sigma, int k)
{
	Mat resultImage = img.clone();    //���,��¡  
	int channels = resultImage.channels();    //��ȡͼ���ͨ��  
	int nRows = resultImage.rows;    //ͼ�������  

	int nCols = resultImage.cols*channels;   //ͼ���������  
	//�ж�ͼ���������  
	if (resultImage.isContinuous())    //�жϾ����Ƿ��������������������൱��ֻ��Ҫ����һ��һά����   
	{
		nCols *= nRows;
		nRows = 1;
	}
	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{   //��Ӹ�˹����  
			int val = resultImage.ptr<uchar>(i)[j] + generateGaussianNoise(mu, sigma) * k;
			if (val < 0)
				val = 0;
			if (val > 255)
				val = 255;
			resultImage.ptr<uchar>(i)[j] = (uchar)val;
		}
	}
	return resultImage;
}

