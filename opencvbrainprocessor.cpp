#include "opencvbrainprocessor.h"

//using namespace std;

// debug
bool debugFlag = false;

float getBrainProcessed(float eeg[], int channels, int samples, int Fs, float lowCutFq, float hiCutFq, float alphaPeak) {

	// setup
	float alphaBandStart = alphaPeak-1;
	float alphaBandEnd = alphaPeak+1;
	int fftAdjust = 2;

	// create opencv matrix with the eeg float array as input
	cv::Mat data(channels, samples, cv::DataType<float>::type, eeg);

	// NIECETOHAVE: support android LOG
	if(debugFlag) {
		std::cout << "input data:" << std::endl;
		printArray(data);
	}

	// nr of points for our fft output - discard half recall fft out put is symmetric
	int N = floor(data.cols / fftAdjust);

	// lets do DC offset
	cv::Scalar tempMean = cv::mean(data);
	float inputMean = tempMean.val[0];
	data = data - inputMean;

	// NIECETOHAVE: support android LOG
	if(debugFlag) {
		std::cout << "input data - after DC offset removal:" << std::endl;
		printArray(data);
	}

	// initialize matrix to hold our fft output
	cv::Mat fftData = data(cv::Rect(0, 0, N, channels));

	// perform fft
	getFft(data, fftData);

	/*
	 * Below we do a debug print of our fft - same rest as in octave test scripts
	 * NIECETOHAVE: move into a unit test
	 */
	for (int i = 5; i < 225 && debugFlag; i += 10) {
		int startSample = ((fftAdjust * i * samples) / Fs);
		int endSample = ((fftAdjust * (i+10) * samples) / Fs);
		float power = getAreaUnderCurve(fftData, startSample, endSample, Fs);
		std::cout << "fq: " << i << " | " << i+10 << " | power: " << power << std::endl;
	}

	// alpha power start - end
	int alpha_start_sample = (floor(fftAdjust * alphaBandStart * samples) / Fs);
	int alpha_end_sample = (floor(fftAdjust * alphaBandEnd * samples) / Fs);

	// total power start - end
	int total_start_sample = (floor(fftAdjust * lowCutFq * samples) / Fs);
	int total_end_sample = (floor(fftAdjust * hiCutFq * samples) / Fs);

	float alphaPower = getAreaUnderCurve(fftData, alpha_start_sample, alpha_end_sample, Fs);
	float totalPower = getAreaUnderCurve(fftData, total_start_sample, total_end_sample, Fs);

	return alphaPower/totalPower;
}


//NIECETOHAVE: update to handle multi channel / 2d arrays or similar
float getAlphaPeak(float eeg[], int channels, int samples, int Fs) {

	// debug
	bool debugFlag = false;

	// create opencv matrix with the eeg int array as input
	cv::Mat rawData(channels, samples, cv::DataType<float>::type, eeg);

	if(debugFlag) {
		printArray(rawData);
	}

	int alphaStartFq = 7;
	int alphaEndFq = 13;
	int binSize = Fs;

	// NIECETOHAVE: make util function which converts from frequency to sampleNr
	int alphaStartOffset = ((2 * alphaStartFq * binSize) / Fs);
	int alphaEndOffset = ((2 * alphaEndFq * binSize) / Fs);


	// initialize variables used throughout loop
	cv::Mat bin;
	cv::Mat fftData = cv::Mat(1, Fs, cv::DataType<float>::type); // NIECETOHAVE: is FS width 100%  right
	cv::Mat alphaBand = cv::Mat(1, (alphaEndOffset - alphaStartOffset), cv::DataType<float>::type);
	cv::MatIterator_<float> fftDataIterator;


	int loops = 0;
	float peakFqSum = 0.0;

	for (int i = 0; i < samples - binSize; i += binSize, loops++) {

		bin = rawData(cv::Rect(i, 0, binSize, 1)); // x, y, width, height - x, y is relative to top left corner (0,0)
		getFft(bin, fftData);

		if(debugFlag) {
			std::cout << "i: " << i << std::endl;
			printArray(bin);
			printArray(fftData);
		}

		alphaBand = fftData(cv::Rect(alphaStartOffset, 0, (alphaEndOffset - alphaStartOffset), 1)); // x, y, width, height - x, y is relative to top left corner (0,0)

		fftDataIterator = std::max_element(alphaBand.begin<float>(),alphaBand.end<float>());

		// get the value
		float peakValue = *fftDataIterator;
		int peakIndex = fftDataIterator.pos().x + alphaStartOffset;
		float peakFq = peakIndex * Fs / binSize / 2.0;

		if(debugFlag) {
			std::cout << "peakFq: " << peakFq << " - peakValue: "<< peakValue << " - peakIndex: " << peakIndex << std::endl;
		}

		peakFqSum += peakFq;
	}

	if(debugFlag) {
		std::cout << "alpha peak loop finished - fqSum: " << peakFqSum << " - loops: "<< loops << std::endl;
	}

	return peakFqSum / loops;

}



void getMinMax(float alphaLevels[], float* result, int alphaLevelsLength, int factor) {

	// create opencv matrix with the alphaLevels float array as input
	cv::Mat data(1, alphaLevelsLength, cv::DataType<float>::type, alphaLevels);

	if(debugFlag) {
		std::cout << "input data:" << std::endl;
		printArray(data);
	}

	cv::Scalar cvMean;
	cv::Scalar cvStddev;
	cv::meanStdDev(data, cvMean, cvStddev);

	cv::MatIterator_<float> dataIterator = std::min_element(data.begin<float>(), data.end<float>());
	float lowestValue = *dataIterator;

	float minValue = cvMean[0] - factor*cvStddev[0];
	float maxValue = cvMean[0] + factor*cvStddev[0];

	// make sure min value is at least 0
	if (minValue < lowestValue) minValue = lowestValue;

	result[0] = minValue;
	result[1] = maxValue;

}




