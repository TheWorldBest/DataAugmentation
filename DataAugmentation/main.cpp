#include "subFunction.h"
#include <fstream>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>

// 该类主要用于数据扩充
using namespace std;
using namespace cv;

int main()
{
	string imgPath = "D:\\Database\\Yaw_smoke_phone\\smoke\\train\\pos\\";
	string savePath = "D:\\Database\\Yaw_smoke_phone\\smoke\\train\\posDataAug\\";
	string imgFormat = ".jpg";

	ifstream finData(imgPath + "\\data.txt");
	if (!finData.is_open())
	{
		cout << "fail to open file:" + imgPath + "\\data.txt" << endl;
		system("pause");
		return 0;
	}

	while (!finData.eof())
	{
		string line;
		Mat imgDst;
		getline(finData, line);
		if (line.empty())
		{
			continue;
		}

		string imgPathFull = imgPath + line;  //图像
		string imgSave;

		DataAugmentation tempDA(imgPathFull);
		imgSave = savePath + line;
		imwrite(imgSave, tempDA.img);
		imgSave = savePath + line.substr(0, line.length() - 4) + "m" + imgFormat;
		imwrite(imgSave, tempDA.mirrorImg());
		imgSave = savePath + line.substr(0, line.length() - 4) + "ng" + imgFormat;
		imwrite(imgSave, tempDA.addNoiseGaussianImg(0.2, 0.3, 8));
		imgSave = savePath + line.substr(0, line.length() - 4) + "r10" + imgFormat;
		imwrite(imgSave, tempDA.rotationImg(10));
		imgSave = savePath + line.substr(0, line.length() - 4) + "r20" + imgFormat;
		imwrite(imgSave, tempDA.rotationImg(20));
		imgSave = savePath + line.substr(0, line.length() - 4) + "r350" + imgFormat;
		imwrite(imgSave, tempDA.rotationImg(350));
		imgSave = savePath + line.substr(0, line.length() - 4) + "r340" + imgFormat;
		imwrite(imgSave, tempDA.rotationImg(340));

		Mat img = tempDA.img;
		tempDA.img = tempDA.rotationImg(10);
		imgSave = savePath + line.substr(0, line.length() - 4) + "r10m" + imgFormat;
		imwrite(imgSave, tempDA.mirrorImg());
		imgSave = savePath + line.substr(0, line.length() - 4) + "r10ng" + imgFormat;
		imwrite(imgSave, tempDA.addNoiseGaussianImg(0.2, 0.3, 8));

		tempDA.img = img;
		tempDA.img = tempDA.rotationImg(20);
		imgSave = savePath + line.substr(0, line.length() - 4) + "r20m" + imgFormat;
		imwrite(imgSave, tempDA.mirrorImg());
		imgSave = savePath + line.substr(0, line.length() - 4) + "r20ng" + imgFormat;
		imwrite(imgSave, tempDA.addNoiseGaussianImg(0.2, 0.3, 8));

		tempDA.img = img;
		tempDA.img = tempDA.rotationImg(350);
		imgSave = savePath + line.substr(0, line.length() - 4) + "r350m" + imgFormat;
		imwrite(imgSave, tempDA.mirrorImg());
		imgSave = savePath + line.substr(0, line.length() - 4) + "r350ng" + imgFormat;
		imwrite(imgSave, tempDA.addNoiseGaussianImg(0.2, 0.3, 8));

		tempDA.img = img;
		tempDA.img = tempDA.rotationImg(340);
		imgSave = savePath + line.substr(0, line.length() - 4) + "r340m" + imgFormat;
		imwrite(imgSave, tempDA.mirrorImg());
		imgSave = savePath + line.substr(0, line.length() - 4) + "r340ng" + imgFormat;
		imwrite(imgSave, tempDA.addNoiseGaussianImg(0.2, 0.3, 8));		
	}
	finData.close();
	return 0;
}