/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "..\Builds\VisualStudio2015\WavetableSynthesizer.h"

//==============================================================================
SynthAudioProcessor::SynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	currentSampleRate = 48000.0;
	angleDelta = 0.0;
	currentAngle = 0.0;
	currSample = 0.0;
	frequency = 440.0;
	lfo_idx = 0.0;

	freqLFO = new LFO(0.3, 48000.0, 3.0);

	addParameter(oscLevelParam = new AudioParameterFloat("oscLevel", "Level", 0.0f, 1.0f, 0.9f));
	addParameter(oscWtPosParam = new AudioParameterFloat("oscWtPos", "Wavetable Position", 0.0f, 1.0f, 0.5f));
	addParameter(filterCutoffParam = new AudioParameterFloat("filterCutoff", "Cutoff Frequency", 0.0f, 1.0f, 0.5f));
	addParameter(filterResoParam = new AudioParameterFloat("filterReso", "Filter Resonance", 0.0f, 1.0f, 0.5f));
	addParameter(filterDryWetParam = new AudioParameterFloat("filterDryWet", "Filter Dry/Wet", 0.0f, 1.0f, 0.5f));
	addParameter(adsrAttackParam = new AudioParameterFloat("attack", "Attack", 0.0f, 1.0f, 0.5f));
	addParameter(adsrDecayParam = new AudioParameterFloat("decay", "Decay", 0.0f, 1.0f, 0.5f));
	addParameter(adsrSustainParam = new AudioParameterFloat("sustain", "Sustain", 0.0f, 1.0f, 0.5f));
	addParameter(adsrReleaseParam = new AudioParameterFloat("release", "Release", 0.0f, 1.0f, 0.5f));
	addParameter(lfo1RateParam = new AudioParameterFloat("lfo1Rate", "LFO1 Frequency", 0.0f, 1.0f, 0.5f));
	addParameter(lfo1AmpParam = new AudioParameterFloat("lfo1Amp", "LFO1 Amplitude", 0.0f, 1.0f, 0.5f));
	addParameter(lfo2RateParam = new AudioParameterFloat("lfo2Rate", "LFO2 Frequency", 0.0f, 1.0f, 0.5f));
	addParameter(lfo2AmpParam = new AudioParameterFloat("lfo2Amp", "LFO2 Amplitude", 0.0f, 1.0f, 0.5f));

	initializeSynth();

}

SynthAudioProcessor::~SynthAudioProcessor()
{
}

//==============================================================================
const String SynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthAudioProcessor::setCurrentProgram (int index)
{
}

const String SynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

	//TODO: GENERATE WAVETABLES
	wavetables = new Wavetables();
	wavetables->generateBlit();

	keyboardState.reset();

}

void SynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
	keyboardState.reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SynthAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{

	process(buffer, midiMessages);

 //   ScopedNoDenormals noDenormals;
 //   const int totalNumInputChannels  = getTotalNumInputChannels();
 //   const int totalNumOutputChannels = getTotalNumOutputChannels();

	//
	//MidiBuffer::Iterator iter(midiMessages);
	//MidiMessage message;
	//int sampleNumber;

	//keyboardState.processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);

	//

 //   for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
 //       buffer.clear (i, 0, buffer.getNumSamples());
	//int max_partials;

 //   for (int channel = 0; channel < 1; ++channel)
 //   {
 // //      float* channelData = buffer.getWritePointer (channel);
	//	//float level = 0.0f;
	//	//for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
	//	//	
	//	//	float f = freqLFO->process(frequency);				// modulate frequency with LFO
	//	//	//float f = frequency;
	//	//	max_partials = floor(20000.0 / f);
	//	//	if (max_partials > 2 * MAX_HARMONIC_COUNT) max_partials = 2 * MAX_HARMONIC_COUNT - 1;
	//	//	float* wt = wavetables->saw[max_partials/2];

	//	//	currSample += f * WAVETABLE_SIZE / 48000.0;	    // phase step dependent on frequency
	//	//	if (currSample >= (double)WAVETABLE_SIZE) 
	//	//		currSample = fmodf(currSample, (double)WAVETABLE_SIZE); // wrap phase at end of buffer

	//	//	float currentSample = wavetables->linearInterpolation(wt, currSample); //interpolate value for not integer phase values
	//	//	channelData[sample] = currentSample;
	//	//}
	//		
 //   }
}

//==============================================================================
bool SynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SynthAudioProcessor::createEditor()
{
    return new SynthAudioProcessorEditor (*this);
}

//==============================================================================
void SynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthAudioProcessor();
}

template <typename FloatType>
void SynthAudioProcessor::process(AudioBuffer<FloatType>& buffer,
	MidiBuffer& midiMessages) {

	const int numSamples = buffer.getNumSamples();

	// Now pass any incoming midi messages to our keyboard state object, and let it
    // add messages to the buffer if the user is clicking on the on-screen keys
	keyboardState.processNextMidiBuffer(midiMessages, 0, numSamples, true);

	// get synth to process these midi events and generate output
	synth.renderNextBlock(buffer, midiMessages, 0, numSamples);

	for (int i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
		buffer.clear(i, 0, numSamples);

	//updateCurrentTimeInfoFromHost);

}

void SynthAudioProcessor::initializeSynth() {
	const int numVoices = 8;

	for (int i = numVoices; --i >= 0;)
		synth.addVoice(new WaveTableVoice());
	synth.addSound(new WaveTableSound());
}