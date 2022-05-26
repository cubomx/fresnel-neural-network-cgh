#include "Propagacion.h" 
#include "utils.h" 
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;

using namespace cv;
using namespace std;

void generateHolo(string srcImage, string folder, int numImag) {
	
	string fullPath = folder + to_string(numImag);

	int dx, dy;
	dx = 32;  //microns
	dy = dx;
	double lamb = 0.535;
	double z = (4 * pow(10, 6)); //mts
	RNG rng;
	Mat grayImg;
	Mat paso = imread(srcImage);
	int N = paso.rows;
	int M = paso.cols;

	Mat re(N * 4, M * 4, CV_8U);
	N *= 4;
	M *= 4;
	Mat matTrans[2];

	Mat orgImg;

	orgImg = imread(srcImage);
	cvtColor(orgImg, grayImg, COLOR_RGB2GRAY);

	re.setTo(0);
	grayImg.copyTo(re.rowRange(grayImg.rows * 1.5, grayImg.rows * 2.5).colRange(grayImg.cols * 1.5, grayImg.cols * 2.5));
	grayImg = re;
	grayImg.convertTo(orgImg, CV_64F);

	double zo = 4000000;  //4 metros para separar el orden 1

	matTrans[0].create(N, M, CV_64F);
	matTrans[1].create(N, M, CV_64F);

	//mT_ASM_fourier_RI(N, M, dx, dy, zm, lamb, matTrans[i]);

	mT_Fresnel_freq_RI(N, M, dx, dy, -zo, lamb, matTrans);

	int rows = re.rows;
	int cols = re.cols;
	float nx = cols / 2.0f;
	float ny = rows / 2.0f;
	// phase
	Mat phaseR = Mat(rows, cols, CV_64F);
	randu(phaseR, Scalar(0.), Scalar(1.));

	Mat Fo[] = { Mat(rows, cols, CV_64F), Mat(rows, cols, CV_64F) };
	Mat Fc[] = { Mat(rows, cols, CV_64F), Mat(rows, cols, CV_64F) };
	Mat Ftot[] = { Mat(rows, cols, CV_64F), Mat(rows, cols, CV_64F) };
	Mat Uprop[] = { Mat(rows, cols, CV_64F), Mat(rows, cols, CV_64F) };
	Ftot[0].setTo(0);
	Ftot[1].setTo(0);
	//Mat phi = phaseR * 2 * M_PI;
	Mat phi = { Mat(rows, cols, CV_64F, 0.) };

	ComAmpPhase(orgImg, phi, Fo);

	propagationFresnelNew(Fo[0], Fo[1], z, matTrans, Fc);

	Fc[0].copyTo(Ftot[0]);
	Fc[1].copyTo(Ftot[1]);
	mostrarMagPha(Ftot[0], Ftot[1]);

	GetMagPha(Ftot[0], Ftot[1], Uprop[0], Uprop[1]);
	int sf = 512;
	int difx = M - sf;
	int dify = N - sf;

	imwrite(fullPath + "ampHolo.png", Uprop[0].rowRange(dify / 2, dify / 2 + 512).colRange(dify / 2, dify / 2 + 512));
	imwrite(fullPath + "phaseHolo.png", Uprop[1].rowRange(dify / 2, dify / 2 + 512).colRange(dify / 2, dify / 2 + 512));

	/*normaliza255(Ftot[0], Uprop[0]);
	normaliza255(Ftot[1], Uprop[1]);
	*/


	/*imwrite(fullPath + "realProp.png", Uprop[0].rowRange(dify / 2, dify / 2 + 512).colRange(dify / 2, dify / 2 + 512));
	imwrite(fullPath + "imagProp.png", Uprop[1].rowRange(dify / 2, dify / 2 + 512).colRange(dify / 2, dify / 2 + 512));
	*/
	int a = 1;
}


int main()
{
	int numImag = 1;
	string specificDir = "/cropped3__3/";
	string directory = "../py/images" + specificDir;
	string dstFolder = "holos" + specificDir;
	fs::create_directory(dstFolder);

	for (const auto& entry : fs::directory_iterator(directory)) {
		string imagePath = entry.path().generic_string();
		generateHolo(imagePath, dstFolder, numImag);
		numImag++;
	}

	return 0;
}