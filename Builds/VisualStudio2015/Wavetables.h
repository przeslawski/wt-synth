#pragma once

#define WAVETABLE_SIZE 4096
#define MAX_HARMONIC_COUNT 400

class Wavetables {
public:
	float sine[WAVETABLE_SIZE];
	float saw[MAX_HARMONIC_COUNT][WAVETABLE_SIZE];
	float blit[WAVETABLE_SIZE];

	void generateBlit();
	float SincM(double M, double x);
	float linearInterpolation(float* wt, double sample);
	void generate();
	void normalize(float* wt);
};