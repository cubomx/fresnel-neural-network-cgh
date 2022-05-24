#pragma once
//#pragma once
#ifndef __PROPAGATION_H_INCLUDED__
#define __PROPAGATION_H_INCLUDED__  

#include "opencv2/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
//#include <complex.h>
#include <stdio.h>


#define lambda2 0.6328
#define _USE_MATH_DEFINES
#include <math.h>

using namespace cv;
using namespace std;

//void mostrarMatriz(string title, Mat& planes);
//void mostrarResultado(string title, Mat* planes);
//void mostrarShift(string title, Mat* planes);
////int propagationFres(Mat img, Mat imaginariaNP, int padvalue, double z, double dxp, double dyp, Mat E[]);
//void mostrarResultado(string title, Mat* planes);
//
//void createRef(double inten, double uo, double vo, double dxp, double dyp, Mat MatRef[]);
//

void mostrarMagPha(Mat& real, Mat& imag);
//void copyInttoComplex(Mat& inten, Mat& complexR, Mat& complexI);
//
////void writeMagPha(string name,Mat &real, Mat &imag, int op);
//
//int matrizTransfe(int N, int M, double dxp, double dyp, Mat& Trans);
//int propagationSpec(Mat img, Mat imaginariaNP, double z, double dxp, double dyp, Mat E[]);
//int propagationSpec(Mat img, Mat imaginariaNP, double z, Mat transfe, Mat E[]);
////int fresnelProp(int dx, int dy, double z, Mat mat[]);
int fourierMethod(Mat mat[], int op);
int multiplyI(Mat mat1[], Mat mat2[], Mat E[]);
//int propagationFres(Mat img, Mat imaginariaNP, double z, double dxp, double dyp, Mat E[]);
//
//int mT_ASM_fourier_RI(int N, int M, double dxp, double dyp, double z, double lamb, Mat Trans[2]);
int mT_Fresnel_freq_RI(int N, int M, double dxp, double dyp, double z, double lamb, Mat Trans[2]);
//int matrizTransfeRI(int N, int M, double dxp, double dyp, Mat Trans[2]);
//int propagationSpecNew(Mat img, Mat imaginariaNP, double z, Mat transfe[], Mat E[]);
int propagationFresnelNew(Mat img, Mat imaginariaNP, double z, Mat transfe[], Mat E[]);
//
////int propagationSpecPC(Mat img, Mat imaginariaNP, double z, Mat transfe, Mat E[], Mat PCF);
//
void GetMagPha(Mat& real, Mat& imag, Mat& magmat, Mat& phasmat);
void normaliza255(Mat& ori, Mat& dest);
//
//
//int shiftFTS(Mat& magI);
int shiftFT(Mat& magI);
//void multiplyWave(Mat wave1[], Mat wave2[], Mat res[]);
//void spatialFilter(Mat wave[], int x0, int x1, int y0, int y1, Mat res[]);
//void ajustSizeFT(Mat& real, Mat& imag, int padvalue);
////void savedata(Mat var1, Mat var2);
//
//void compensate(Mat input[]);
//void compensate(Mat& input);
//
//void createRef2(double inten, double z, double dxp, double dyp, Mat MatRef[]);

static void help()
{
	printf("\nEste programa calculará la propagación de una campo con información inicial representada como archivo de imagen en blanco y negro \n"
		"The dft of an image is taken and it's power spectrum is displayed.\n"
		"Usage:\n"
		"./dft [image_name -- default ../data/lena.jpg]\n");
}

//const char* keys =
//{
//    "{help h||}{@image|../data/square2000.png|input image file}"
//};
//***************************************************************************************************************************

#endif
