#pragma once

class LFO {
public:
	LFO(double f, double sr, double d) : frequency(f), depth(d), sampleRate(sr), phase(0.0) {}
	double process(double value);
	float process(float value);

private:
	double sampleRate, phase, frequency, depth;
};

