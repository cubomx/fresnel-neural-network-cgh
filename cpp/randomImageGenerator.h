#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <Math.h>
#include <random>
std::string RandomImage_Name(float percentaje, int number);
cv::Mat randomMatrix(int circles);
void generateRandomMatrix(int ImageNumber, float ImagePercentage);