#ifndef _subFunction_h_
#define _subFunction_h_
#include <opencv2\core\core.hpp>
#include <string>

// ������Ҫ������������
class DataAugmentation
{
private:


public:
	DataAugmentation(std::string imgPath);
	//DataAugmentation(cv::Mat img);
	cv::Mat img;  //��������ͼ��
	std::string savePath;  //����·��
	std::string imgFormat;  //����ͼ���ʽ
	double generateGaussianNoise(double mu, double sigma);  //���ɸ�˹�ֲ���������У�������Marsaglia��Bray��1964�����, C++�汾����: mu�Ǿ�ֵ, sigma�Ƿ���, X����N(0, 1)�ֲ�

	cv::Mat mirrorImg();  // ͼ��ˮƽ����
	cv::Mat rotationImg(double degreeR);  // ��ת������
	cv::Mat addNoiseGaussianImg(double mu, double sigma, int k);  // ��Ӹ�˹����,mu�Ǿ�ֵ, sigma�Ƿ���
};
#endif