#include <iostream>
#include "opencvbrainprocessor.h"
#include "testutil.h"

int main(int argc, char **argv) {
/*
	int samples = 10; //512
	float inputArray[samples];

	// ok manipulate the array
	for (int i = 0; i < samples; i++) {
		inputArray[i] = i;
	}
*/

	int samples = 1200;
	float* inputArray = getTestSignal();
	int Fs = 1000; // test recording samplerate needs to be 1000


	std::cout << "---------------------------------" << std::endl;
	float result = getBrainProcessed(inputArray, 1, samples, Fs, 5.0000076876, 50.000068875858, 9.0000006876);
	std::cout << "getBrainProcessed(...): " << result << std::endl;
	std::cout << "expected: 6.22933e-17" << std::endl;
	std::cout << "---------------------------------" << std::endl;


	float alphaPeak = getAlphaPeak(inputArray, 1, samples, Fs);
	std::cout << "getAlphaPeak(): " << alphaPeak << std::endl;
	std::cout << "expected: 10" << std::endl;
	std::cout << "---------------------------------" << std::endl;


	float minMax[2] = {0.0, 0.0};
	getMinMax(inputArray, minMax, samples, 2);
	std::cout << "getMinMax(): " << minMax[0] << " - " << minMax[1] << std::endl;
	std::cout << "expected: 0 - 1.03917e+13" << std::endl;
	std::cout << "---------------------------------" << std::endl;

	return 0;

}
