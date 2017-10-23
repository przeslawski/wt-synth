#include "..\JuceLibraryCode\JuceHeader.h"


class WaveTableSound : public SynthesiserSound {

public:

	WaveTableSound() {}

	bool appliesToNote(int midiNoteNumber) override 
	{
		Logger::outputDebugString(String(midiNoteNumber));
		return true;
	}

	bool appliesToChannel(int midiChannel) override
	{
		Logger::outputDebugString(String(midiChannel));
		return true;
	}

};

class WaveTableVoice : public SynthesiserVoice {

public:
	WaveTableVoice() {}

	bool canPlaySound(SynthesiserSound* sound) override 
	{
		return dynamic_cast<WaveTableSound*>(sound) != nullptr;
	}

	void startNote(int midiNoteNumber, 
		float velocity, 
		SynthesiserSound* sound, 
		int currentPitchWheelPosition) override 
	{

		Logger::outputDebugString(String(midiNoteNumber));
	}

	void stopNote(float velocity, bool allowTailOff) override 
	{
		if (allowTailOff) {

		}
		else {
			clearCurrentNote();

		}
	}

	void pitchWheelMoved(int newValue) override 
	{

	}

	void controllerMoved(int controllerNumber, int newValue) override 
	{

	}

	void renderNextBlock(AudioSampleBuffer& outputBuffer, 
		int startSample, 
		int numSamples) override 
	{

	}

};
