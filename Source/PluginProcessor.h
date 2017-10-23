/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "../Builds/VisualStudio2015/Wavetables.h"
#include "../Builds/VisualStudio2015/LFO.h"

//==============================================================================
/**
*/
class SynthAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    SynthAudioProcessor();
    ~SynthAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect () const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;


	float noteOnVel;
	float frequency;
	float phase;

	double currentAngle, angleDelta, currentSampleRate;
	double currSample, lfo_idx;

	Wavetables* wavetables;
	LFO* freqLFO;

	MidiKeyboardState keyboardState;

	Synthesiser synth;

	/* PARAMETERS */
	AudioParameterFloat* oscLevelParam = nullptr;
	AudioParameterFloat* oscWtPosParam = nullptr;
	AudioParameterFloat* filterCutoffParam = nullptr;
	AudioParameterFloat* filterResoParam = nullptr;
	AudioParameterFloat* filterDryWetParam = nullptr;
	AudioParameterFloat* adsrAttackParam = nullptr;
	AudioParameterFloat* adsrDecayParam = nullptr;
	AudioParameterFloat* adsrSustainParam = nullptr;
	AudioParameterFloat* adsrReleaseParam = nullptr;
	AudioParameterFloat* lfo1RateParam = nullptr;
	AudioParameterFloat* lfo1AmpParam = nullptr;
	AudioParameterFloat* lfo2RateParam = nullptr;
	AudioParameterFloat* lfo2AmpParam = nullptr;


private:

	AudioParameterFloat *gain_param, *frequency_param;

	template <typename FloatType>
	void process(AudioBuffer<FloatType>& buffer, MidiBuffer& midiMEssages);

	void initializeSynth();
	void updateCurrentTimeInfoFromHost();
	static BusesProperties getBusesProperties();


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthAudioProcessor)
};
