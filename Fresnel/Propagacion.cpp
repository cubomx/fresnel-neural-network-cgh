#include "propagacion.h" 
//#include "FocusTool.hpp" 
#define _USE_MATH_DEFINES

using namespace cv;
using namespace std;

//*********************************************************************************************************
//*********************************************************************************************************
//*********************************************************************************************************
int fourierMethod(Mat mat[], int op) {
	Mat complexMat(mat[0].rows, mat[0].cols, CV_64F);
	cv::merge(mat, 2, complexMat);
	shiftFT(complexMat);

	if (op==1)
		cv::dft(complexMat, complexMat);
	else 
		cv::dft(complexMat, complexMat, DFT_INVERSE);
    
	shiftFT(complexMat);
	cv::split(complexMat, mat);
	return(1);
}
//****************************************************************************
int multiplyI(Mat mat1[], Mat mat2[], Mat E[]) {
	double a, b, c, d;
	for (int j = 0; j < mat1[0].rows; j++)
		for (int i = 0; i < mat1[1].cols; i++)
		{
			a = mat1[0].at<double>(j, i);
			b = mat1[1].at<double>(j, i);
			c = mat2[0].at<double>(j, i);
			d = mat2[1].at<double>(j, i);
			E[0].at<double>(j, i) = (a * c - b * d);
			E[1].at<double>(j, i) = (a * d + b * c);
		}
	return(1);
}

int mT_Fresnel_freq_RI(int N, int M, double dxp, double dyp, double z, double lamb, Mat Trans[2])
{
	Mat planes[] = {
		Mat_<double>(N, M, CV_64F),
		Mat_<double>(N, M, CV_64F)
	};

	int centroX, centroY;
	centroX = M / 2;
	centroY = N / 2;

	/*TERMINO CUADRATICO e^(i*sqrt(lambda^2-(x^2+y^2))
	*/

	double du = 1.0 / (M * dxp);
	double dv = 1.0 / (N * dyp);

	double dfx = du * lamb / z;  //revisar
	double dfy = dv * lamb / z;


	for (int j = 0; j < N; j++)
		for (int i = 0; i < M; i++)
		{
			double fx = (double)(i - centroX) * du;
			double fy = (double)(centroY - j) * dv;
			//double p1 = M_PI * 2 * z / lambda;

			double phasephi =  ((fx * fx) + (fy * fy));
			phasephi =  -1.0*M_PI *lamb * z * phasephi;
			//Trans.at<double>(j, i) = phasephi;
			Trans[0].at<double>(j, i) = 1.0 * cos(phasephi);
			Trans[1].at<double>(j, i) = 1.0 * sin(phasephi);
		}
	mostrarMagPha(Trans[0], Trans[1]);
	return(1);
}
//*******************************************************************************

int propagationFresnelNew(Mat img, Mat imaginariaNP, double tconst, Mat transfe[], Mat E[])
{//PARA 1 PROPAGACION
	int N = img.rows;
	int M = img.cols;

	Mat planes[] = {
		Mat_<double>(N, M, CV_64F),
		Mat_<double>(N, M, CV_64F)
	};
	img.copyTo(planes[0]);
	imaginariaNP.copyTo(planes[1]);

	fourierMethod(planes, 1);
	//mostrarMagPha(planes[0], planes[1]);

	Mat Fh[] = { Mat(N, M, CV_64F), Mat(N, M, CV_64F) };
	Mat Uprop[] = { Mat(N, M, CV_64F), Mat(N, M, CV_64F) };

	multiplyI(planes, transfe, Fh);
	// mostrarMagPha(Fh[0], Fh[1]);
	fourierMethod(Fh, -1);
	// pendiente agregar termino constante
	// 
	// mostrarMagPha(Fh[0], Fh[1]);
	Fh[0].copyTo(E[0]);
	Fh[1].copyTo(E[1]);

	//GetMagPha(Fh[0], Fh[1], Uprop[0], Uprop[1]);
	return(1);
}


//*********************************************************************************************************
//*********************************************************************************************************
//*********************************************************************************************************

void mostrarMagPha(Mat& real, Mat& imag)
{
	Mat mag = real.clone();
	Mat phasmat = real.clone();

	mag.setTo(0);
	phasmat.setTo(0);

	magnitude(real, imag, mag);

	phase(real, imag, phasmat, false);

	//phasmat = phasmat - M_PI;
	phasmat = (phasmat / (2 * M_PI)) * 255.0;
	Mat phaseview = phasmat.clone();
	phasmat.convertTo(phaseview, CV_8U);
	namedWindow("phase imag", WINDOW_NORMAL);
	resizeWindow("phase imag", 500, 500);
	imshow("phase imag", phaseview);

	waitKey(10);

	double mmin, mmax;
	cv::minMaxLoc(mag, &mmin, &mmax);
	//mmax = sqrt(mmax);
	mag = (mag / mmax) * 255.0;
	Mat magview = mag.clone();
	mag.convertTo(magview, CV_8U);
	namedWindow("magnitude", WINDOW_NORMAL);
	imshow("magnitude", magview);
	resizeWindow("magnitude", 500, 500);
	waitKey(10);
	/*magview.setTo(0.0);
	imshow("magnitude", magview);
	resizeWindow("magnitude", 500, 500);
	waitKey(10);*/

}
//*********************************************************************************
//normaliza una matriz a 255 y convierte a UC
void normaliza255(Mat& ori, Mat& dest)
{
	Mat tmp = ori.clone();
	
	double mmin, mmax;
	cv::minMaxLoc(ori, &mmin, &mmax);
	//mmax = sqrt(mmax);
	double range = mmax - mmin;
	tmp = (tmp -mmin)/ range * 255.0;

	tmp.convertTo(dest, CV_8U);
	namedWindow("normalizada", WINDOW_NORMAL);
	imshow("normalizada", dest);
	resizeWindow("normalizada", 500, 500);
	waitKey(10);
	return;
}


void GetMagPha(Mat& real, Mat& imag, Mat& magmat, Mat& phasmat)
{
	magmat.setTo(0);
	phasmat.setTo(0);

	magnitude(real, imag, magmat);
	double mmin, mmax;
	cv::minMaxLoc(magmat, &mmin, &mmax);
	//mmax = sqrt(mmax);
	magmat = (magmat / mmax) * 255.0;
	Mat magview = magmat.clone();
	magview.convertTo(magmat, CV_8U);

	phase(real, imag, phasmat, false);
	phasmat = (phasmat / (2 * M_PI)) * 255.0;
	Mat phaseview = phasmat.clone();
	phaseview.convertTo(phasmat, CV_8U);

	waitKey(10);

}
//*****************************************************************************

int shiftFT(Mat& magI)
{
	Mat result(magI.rows, magI.cols, CV_64FC2);

	//vector<Mat> complexComp(2);

	Mat complexComp[] = { Mat(magI.rows, magI.cols, CV_64F), Mat(magI.rows, magI.cols, CV_64F) };
	split(magI, complexComp);
	// rearrange the quadrants of Fourier image  so that the origin is at the image center
	int cx = complexComp[0].cols / 2;
	int cy = complexComp[0].rows / 2;

	Mat q0(complexComp[0], Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
	Mat q1(complexComp[0], Rect(cx, 0, cx, cy));  // Top-Right
	Mat q2(complexComp[0], Rect(0, cy, cx, cy));  // Bottom-Left
	Mat q3(complexComp[0], Rect(cx, cy, cx, cy)); // Bottom-Right

	Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
	q2.copyTo(q1);
	tmp.copyTo(q2);

	Mat q01(complexComp[1], Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
	Mat q11(complexComp[1], Rect(cx, 0, cx, cy));  // Top-Right
	Mat q21(complexComp[1], Rect(0, cy, cx, cy));  // Bottom-Left
	Mat q31(complexComp[1], Rect(cx, cy, cx, cy)); // Bottom-Right

	Mat tmp1;                           // swap quadrants (Top-Left with Bottom-Right)
	q01.copyTo(tmp1);
	q31.copyTo(q01);
	tmp1.copyTo(q31);

	q11.copyTo(tmp1);                    // swap quadrant (Top-Right with Bottom-Left)
	q21.copyTo(q11);
	tmp1.copyTo(q21);

	//merge(complexComp, result);
	merge(complexComp, 2, result);
	result.copyTo(magI);
	return 1;
}

