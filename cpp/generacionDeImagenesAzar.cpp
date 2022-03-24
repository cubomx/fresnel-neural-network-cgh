#include "randomImageGenerator.h" 
#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <Math.h>
#include <random>
using namespace cv;
using namespace std;
int N = 1024, M = 1024, 
RandomImages=50, circleSize = 7, 
imageSize = 625, 
LowerRange = 1024 - imageSize - imageSize / 2, 
UpperRange = -imageSize / 2;

float ImagePercentajeDensity = 0.02;
int mapa[25][25], minimoEnMapa = 0, contador = 0;
random_device rd;
uniform_int_distribution<int> dist(0, 25);


string RandomImage_Name(float percentaje, int number)
{
	char StrPercentaje[5], StrNumber[5];
	char newStr[15];
	itoa(percentaje, StrPercentaje, 10);
	itoa(number, StrNumber, 10);
	strcpy(newStr, StrPercentaje);
	strcat(newStr, " X ");
	strcat(newStr, StrNumber);
	strcat(newStr, ".png");
	return newStr;
}

cv::Mat randomMatrix(int circles)
{
	cv::Mat random = cv::Mat(N, M, CV_8U);
	random.setTo(0);
	for (int i = 0; i < circles; i ++)
	{
		bool pipo = true;
		while (pipo)
		{
			int randomCol = dist(rd);
			int randomRow = dist(rd);
			int X = circleSize + (float)(rand()) / (float)(RAND_MAX / (24 - circleSize)), 
			Y = circleSize + (float)(rand()) / (float)(RAND_MAX / (24 - circleSize));
			mapa[randomRow][randomCol] == minimoEnMapa ? mapa[randomRow][randomCol] += 1, pipo = false, circle(random, Point(200 + randomRow * 25 + X, 200 + randomCol * 25 + Y), circleSize, 255, -1), contador++, printf("%d\n", contador) : pipo = true;
			contador % 625 == 0 ? minimoEnMapa +=1  : minimoEnMapa = minimoEnMapa;
		}
	}
	return random;
}

void generateRandomMatrix(int ImageNumber, float ImagePercentage)
{
	int circles = ceil(imageSize * ImagePercentage);
	printf("Total Image Number = %d\n Image Percentage = %f\n Circles = %d\n", ImageNumber, ImagePercentage, circles);
	cv::Mat suma1024 = cv::Mat(N, M, CV_8U);
	for (int i = 0; i < ImageNumber; i++)
	{
		cv::Mat a = randomMatrix(circles);
		suma1024 += a;
		imwrite(RandomImage_Name(ImagePercentage, i), a);
		printf("Image = %d\n", i);
	}
	for (int j = 0; j < N; j ++)
	{
		for (int i = 0; i < M; i ++)
		{
			suma1024.at<uchar>(j, i) = suma1024.at<uchar>(j, i) == 255 ? suma1024.at<uchar>(j, i) : 0;
		}
	}
	Mat sumaimageSize = Mat(imageSize, imageSize, CV_8U);
	for (int j = 0; j < imageSize; j++)
	{
		for (int i = 0; i < imageSize; i++)
		{
			sumaimageSize.at<uchar>(j, i) = suma1024.at<uchar>(j + 200, i + 200);
		}
	}
	imwrite("ZZSuma1024X1024.png", suma1024);
	imwrite("ZZSumaimageSizeXimageSize.png", sumaimageSize);
	printf("Termine");
	return;
}


void main()
{
	generateRandomMatrix(RandomImages, ImagePercentajeDensity);
}