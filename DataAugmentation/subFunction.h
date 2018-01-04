#ifndef _subFunction_h_
#define _subFunction_h_
#include <opencv2\core\core.hpp>
#include <string>

// 该类主要用于数据扩充
class DataAugmentation
{
private:


public:
	DataAugmentation(std::string imgPath);
	//DataAugmentation(cv::Mat img);
	cv::Mat img;  //待扩增的图像
	std::string savePath;  //保存路径
	std::string imgFormat;  //保存图像格式
	double generateGaussianNoise(double mu, double sigma);  //生成高斯分布随机数序列，方法由Marsaglia和Bray在1964年提出, C++版本如下: mu是均值, sigma是方差, X服从N(0, 1)分布

	cv::Mat mirrorImg();  // 图像水平镜像
	cv::Mat rotationImg(double degreeR);  // 旋转度数，
	cv::Mat addNoiseGaussianImg(double mu, double sigma, int k);  // 添加高斯噪声,mu是均值, sigma是方差
};
#endif