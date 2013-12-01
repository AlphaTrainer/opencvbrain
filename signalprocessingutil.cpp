/*
 * signalprocessingutil.cpp
 */

#include "signalprocessingutil.h"

/*
 * This method simulates trapez function in octave - output is the area of interest under a curve represented as input matrix a
 */

float getAreaUnderCurve(cv::Mat a, int startSample, int endSample, int Fs) {

	int N = endSample - startSample; // number of data points in area of interest
	int nrOfRectangles = N; // here we can trade performance for accuracy by looking at fewer rectangles
	int stepSize =  N / nrOfRectangles; // number of data points for each rectangle
	int channels = a.rows;
	float area = 0.0;
	// NIECETOHAVE: can this be optimized with linear algebra = no forloop stuff
	for (int i = startSample; i < endSample; i+= stepSize) {
		for (int j = 0; j < channels; j += stepSize) {
			// area += pow((a.at<float>(j, i) * stepSize), 2.0);
			area += a.at<float>(j, i) * stepSize / Fs;
		}
	}
	return area;
}


void getFft(cv::Mat input, cv::Mat& dest) {

	// lets do fast fourier transform
	// dft - fft is the default
	// DFT_ROWS performs a forward or inverse transform of every individual row of the input matrix; this flag enables
	// you to transform multiple vectors simultaneously and can be used to decrease the overhead (which is sometimes several
	// times larger than the processing itself) to perform 3D and higher-dimensional transformations and so forth.
	cv::dft(input, input, cv::DFT_ROWS, 0);

	// some values are now negative, we could just look at the positive values - according to:
	// http://www.mathworks.com/matlabcentral/answers/41177
	// - we do the same thing in octave script "get_fft.m"
	input = cv::abs(input);

	// initialization of matrix holding our fft output - easy to read but
	// NIECETOHAVE: it would probably be more effective to keep using first half of data matrix
	// since fft is symmetrical, we throw away second half and double first half of our values
	dest = input(cv::Rect(0, 0, dest.cols, dest.rows)); // x, y, width, height - x, y is relative to top left corner (0,0)

	// retaining magnitude by doubling first half of our values
	dest = dest.mul(2.0);

	// to go form magnitude to power we square all fft output values
	cv::pow(dest, 2.0, dest);

}
