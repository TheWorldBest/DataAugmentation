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
	//定义一个特别小的值  
	const double epsilon = numeric_limits<double>::min();//返回目标数据类型能表示的最逼近1的正数和1的差的绝对值  
	static double z0, z1;
	static bool flag = false;
	flag = !flag;
	//flag为假，构造高斯随机变量  
	if (!flag)
		return z1*sigma + mu;
	double u1, u2;
	//构造随机变量  

	do
	{
		u1 = rand()*(1.0 / RAND_MAX);
		u2 = rand()*(1.0 / RAND_MAX);
	} while (u1 <= epsilon);
	//flag为真构造高斯随机变量X  
	z0 = sqrt(-2.0*log(u1))*cos(2 * CV_PI * u2);
	z1 = sqrt(-2.0*log(u1))*sin(2 * CV_PI * u2);
	return z1*sigma + mu;
}


Mat DataAugmentation::mirrorImg()
{
	Mat resultImage;
	flip(img, resultImage, 1);  //水平翻转
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
	Mat resultImage = img.clone();    //深拷贝,克隆  
	int channels = resultImage.channels();    //获取图像的通道  
	int nRows = resultImage.rows;    //图像的行数  

	int nCols = resultImage.cols*channels;   //图像的总列数  
	//判断图像的连续性  
	if (resultImage.isContinuous())    //判断矩阵是否连续，若连续，我们相当于只需要遍历一个一维数组   
	{
		nCols *= nRows;
		nRows = 1;
	}
	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{   //添加高斯噪声  
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

