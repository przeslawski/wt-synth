#include "Wavetables.h"
#include "../JuceLibraryCode/JuceHeader.h"

void Wavetables::normalize(float* wt) {
	double max = 0.0;					
	for (int i = 0; i < WAVETABLE_SIZE; i++)
		if (abs(wt[i]) > max)			
			max = abs(wt[i]);			
	for (int i = 0; i < WAVETABLE_SIZE; i++)
		wt[i] /= max;				
}

float Wavetables::SincM(double M, double x) {
	if (abs(x) < 0.000000001) return 1.0;
	return (float)(std::sin(double_Pi * x) / (M * std::sin(double_Pi * x / M)));
}

void Wavetables::generateBlit() {
	generate();
}

float Wavetables::linearInterpolation(float* wt, double sample) {

	float x1 = floor(sample);
	float x2 = ceil(sample);
	float y1 = wt[(int)x1];
	float y2 = wt[(int)x2];

	if (x1 == x2) return y1;

	return (y1 * (x2 - (float)sample) + y2 * ((float)sample - x1)) / (x2 - x1);

}

void Wavetables::generate() {

	// geenrate sine waveform 
	for (int i = 0; i < WAVETABLE_SIZE; ++i) {
		sine[i] = std::sin(2 * double_Pi * i / WAVETABLE_SIZE);
	}


	/**
	  * generate shitton of sawtooth waveforms from blits with up to MAX_HARMONICS_COUNT partial frequencies
	  *
	  * TO DO: find out why with even number of partials signal is AWFUL
	  * for now generating only odd number of partials
	  *
	  */
	for (int m = 1; m < MAX_HARMONIC_COUNT + 1; m++) {

		double M = (double)2 * m - 1;

		for (int i = 0; i < WAVETABLE_SIZE; ++i) {

			saw[m-1][i] = (M/WAVETABLE_SIZE) * SincM(M, M*i / WAVETABLE_SIZE);

		}
		normalize(saw[m - 1]);
		float a = 1.0f / WAVETABLE_SIZE;
		for (int i = 1; i < WAVETABLE_SIZE; ++i) {
			saw[m - 1][i] = saw[m - 1][i - 1] * (1.0f - a) + a * saw[m-1][i];
		}

	}

}