
#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;
int ComAmpPhase(Mat re, Mat phi, Mat datCom[2])
{
	int rows = re.rows;
	int cols = re.cols;
	for (int j = 0; j < rows; j++)
	{
		for (int i = 0; i < cols; i++)
		{
			double phix = cos(phi.at<double>(j, i));
			double phiy = sin(phi.at<double>(j, i));
			datCom[0].at<double>(j, i) = re.at<double>(j, i) * phix;  // A*cos(M_PI*phaseR);
			datCom[1].at<double>(j, i) = re.at<double>(j, i) * phiy;  // A*sin(M_PI*phaseR);
		}
	}
	return 1;
}