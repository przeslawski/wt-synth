/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class SynthAudioProcessorEditor  : public AudioProcessorEditor, 
	private SliderListener
{
public:
    SynthAudioProcessorEditor (SynthAudioProcessor&);
    ~SynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

	void sliderValueChanged(Slider* slider) override;
	void updateAngleDelta();

	//void comboBoxChanged(ComboBox* box) override;
	/*void setMidiInput(int index);
	void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message) override;
	void handleNoteOn(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;
	void handleNoteOff(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;
	void postMessageToList(const MidiMessage& message, const String& source);
	void addMessageToList(const MidiMessage& message, const String& source);
	static String getMidiMessageDescription(const MidiMessage& m);
	void logMessage(const String&);*/


private:
	class ParameterSlider;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SynthAudioProcessor& processor;

	/* OSCILATOR CONTROLS */
	ScopedPointer<ParameterSlider> rk_OscWtPos, rk_OscLvl;

	/* FILTER CONTROLS */
	ScopedPointer<ParameterSlider> rk_FilterCutoff, rk_FilterReso, rk_FilterDryWet;

	/* ADSR CONTROLS */
	ScopedPointer<ParameterSlider> rk_Attack, rk_Decay, rk_Sustain, rk_Release;

	/* LFO1 CONTROLS */
	ScopedPointer<ParameterSlider> rk_Lfo1Rate, rk_Lfo1Amp;

	/* LFO2 CONTROLS */
	ScopedPointer<ParameterSlider> rk_Lfo2Rate, rk_Lfo2Amp;

	/* MIDI CONTROLS */
	AudioDeviceManager deviceManager;
	ComboBox midiInputList;
	Label midiInputListLabel;
	int lastInputIndex;
	bool isAddingFromMidiInput;
	MidiKeyboardState keyboardState;
	MidiKeyboardComponent keyboardComponent;
	TextEditor midiMessageBox;
	double startTime;

	bool componentsInitialized = false;
	Label timecodeDisplayLabel, gainLabel, delayLabel;
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthAudioProcessorEditor)
};


// This is used to dispach an incoming message to the message thread
//class IncomingMessageCallback : public CallbackMessage {
//public:
//	IncomingMessageCallback(SynthAudioProcessorEditor* o, const MidiMessage& m, const String& s)
//		: owner(o), message(m), source(s) {}
//
//	void messageCallback() override {
//		if (owner != nullptr)
//			owner->addMessageToList(message, source);
//	}
//
//	Component::SafePointer<SynthAudioProcessorEditor> owner;
//	MidiMessage message;
//	String source;
//};