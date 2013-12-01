/*
 * opencvbrainprocessor.h
 * 
 * take care don't overlap with brainprocessing.h
 */

// NB! OpenCV 2:
#include "opencv2/core/core.hpp"
#include "printutil.h"
#include "signalprocessingutil.h"

// Note: so fare we explicit name spacing so "using" not:
// using namespace cv;

#ifndef OPENCVBRAINPROCESSOR_H_
#define OPENCVBRAINPROCESSOR_H_

// NIECETOHAVE: change into a float[][] in order to receive multi channel data
float getBrainProcessed(float eeg[], int channels, int samples, int Fs, float lowCutFq, float hiCutFq, float alphaPeak);

float getAlphaPeak(float eeg[], int channels, int samples, int Fs);

void getMinMax(float alphaLevels[], float* result, int alphaLevelsLength, int factor);

#endif /* OPENCVBRAINPROCESSOR_H_ */
