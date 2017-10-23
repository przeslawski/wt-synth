#include "LFO.h"
#include "../JuceLibraryCode/JuceHeader.h"


double LFO::process(double value) {
	phase += frequency * 2 * double_Pi / sampleRate;
	return value += std::sin(phase) * depth;
}

float LFO::process(float value) {
	phase += frequency * 2 * double_Pi / sampleRate;
	return value += (float)(std::sin(phase) * depth);
}