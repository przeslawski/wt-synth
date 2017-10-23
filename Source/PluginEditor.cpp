/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


class SynthAudioProcessorEditor::ParameterSlider : public Slider, private Timer {
public:
	ParameterSlider(AudioProcessorParameter& p) : Slider(p.getName(256)), param(p) {
		setRange(0.0, 1.0, 0.0);
		startTimerHz(30);
		updateSliderPos();
	}

	void valueChanged() override { param.setValueNotifyingHost((float)Slider::getValue()); }
	void timerCallback() override { updateSliderPos(); }
	void startedDragging() override { param.beginChangeGesture(); }
	void stoppedDragging() override { param.endChangeGesture(); }

	double getValueFromText(const String& text) override { return param.getValueForText(text); }
	String getTextFromValue(double value) override { return param.getText((float)value, 1024); }

	void updateSliderPos() {
		const float newValue = param.getValue();
		if (newValue != (float)Slider::getValue() && !isMouseButtonDown()) {
			Slider::setValue(newValue, NotificationType::dontSendNotification);
		}
	}

	AudioProcessorParameter& param;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParameterSlider);
};

//==============================================================================
SynthAudioProcessorEditor::SynthAudioProcessorEditor (SynthAudioProcessor& p)
    : AudioProcessorEditor (&p), 
	  processor (p), 
	  keyboardComponent(p.keyboardState, MidiKeyboardComponent::horizontalKeyboard)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

	// Oscilator controls initialization:
	// level
	addAndMakeVisible(rk_OscLvl = new ParameterSlider(*processor.oscLevelParam));
	rk_OscLvl->setSliderStyle(Slider::RotaryVerticalDrag);
	rk_OscLvl->setRange(0.0, 1.0);
	rk_OscLvl->setTextBoxStyle(Slider::TextBoxAbove, true, 70, 20);
	rk_OscLvl->setTextValueSuffix("Level");
	rk_OscLvl->setValue(0.5);

	// wavetable position 
	addAndMakeVisible(rk_OscWtPos = new ParameterSlider(*processor.oscWtPosParam));
	rk_OscWtPos->setSliderStyle(Slider::RotaryVerticalDrag);
	rk_OscWtPos->setRange(0.0, 1.0);
	rk_OscWtPos->setTextBoxStyle(Slider::TextBoxAbove, true, 70, 20);
	rk_OscWtPos->setTextValueSuffix("WT Pos");
	rk_OscWtPos->setValue(0.5);

	// Filter controls:
	// cutoff frequency 
	rk_FilterCutoff = new ParameterSlider(*processor.filterCutoffParam);
	rk_FilterCutoff->setSliderStyle(Slider::RotaryVerticalDrag);
	rk_FilterCutoff->setRange(0.0, 1.0);
	rk_FilterCutoff->setTextBoxStyle(Slider::TextBoxAbove, true, 70, 20);
	rk_FilterCutoff->setTextValueSuffix("Cutoff");
	rk_FilterCutoff->setValue(0.5);
	
	// resonance 
	rk_FilterReso = new ParameterSlider(*processor.filterResoParam);
	rk_FilterReso->setSliderStyle(Slider::RotaryVerticalDrag);
	rk_FilterReso->setRange(0.0, 1.0);
	rk_FilterReso->setTextBoxStyle(Slider::TextBoxAbove, true, 70, 20);
	rk_FilterReso->setTextValueSuffix("Resonance");
	rk_FilterReso->setValue(0.5);
	
	// dry/wet 
	rk_FilterDryWet = new ParameterSlider(*processor.filterDryWetParam);
	rk_FilterDryWet->setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	rk_FilterDryWet->setRange(0.0, 1.0);
	rk_FilterDryWet->setTextBoxStyle(Slider::TextBoxAbove, true, 70, 20);
	rk_FilterDryWet->setTextValueSuffix("Dry/Wet");
	rk_FilterDryWet->setValue(0.5);

	// LFO 1 controls:
	// rate
	rk_Lfo1Rate = new ParameterSlider(*processor.lfo1RateParam);
	rk_Lfo1Rate->setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	rk_Lfo1Rate->setRange(0.0, 1.0);
	rk_Lfo1Rate->setTextBoxStyle(Slider::TextBoxAbove, true, 70, 20);
	rk_Lfo1Rate->setTextValueSuffix("Rate");
	rk_Lfo1Rate->setValue(0.5);

	// amp 
	rk_Lfo1Amp = new ParameterSlider(*processor.lfo1AmpParam);
	rk_Lfo1Amp->setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	rk_Lfo1Amp->setRange(0.0, 1.0);
	rk_Lfo1Amp->setTextBoxStyle(Slider::TextBoxAbove, true, 70, 20);
	rk_Lfo1Amp->setTextValueSuffix("Amp");
	rk_Lfo1Amp->setValue(0.5);

	// LFO 2 controls
	// rate 
	rk_Lfo2Rate = new ParameterSlider(*processor.lfo2RateParam);
	rk_Lfo2Rate->setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	rk_Lfo2Rate->setRange(0.0, 1.0);
	rk_Lfo2Rate->setTextBoxStyle(Slider::TextBoxAbove, true, 70, 20);
	rk_Lfo2Rate->setTextValueSuffix("Rate");
	rk_Lfo2Rate->setValue(0.5);

	// amp
	rk_Lfo2Amp = new ParameterSlider(*processor.lfo2AmpParam);
	rk_Lfo2Amp->setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	rk_Lfo2Amp->setRange(0.0, 1.0);
	rk_Lfo2Amp->setTextBoxStyle(Slider::TextBoxAbove, true, 70, 20);
	rk_Lfo2Amp->setTextValueSuffix("Amp");
	rk_Lfo2Amp->setValue(0.5);

	// ADSR generator controls:
	// attack
	rk_Attack = new ParameterSlider(*processor.adsrAttackParam);
	rk_Attack->setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	rk_Attack->setRange(0.0, 1.0);
	rk_Attack->setTextBoxStyle(Slider::TextBoxAbove, true, 70, 20);
	rk_Attack->setTextValueSuffix("Attack");
	rk_Attack->setValue(0.5);

	// decay
	rk_Decay = new ParameterSlider(*processor.adsrDecayParam);
	rk_Decay->setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	rk_Decay->setRange(0.0, 1.0);
	rk_Decay->setTextBoxStyle(Slider::TextBoxAbove, true, 70, 20);
	rk_Decay->setTextValueSuffix("Decay");
	rk_Decay->setValue(0.5);

	// sustain
	rk_Sustain = new ParameterSlider(*processor.adsrSustainParam);
	rk_Sustain->setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	rk_Sustain->setRange(0.0, 1.0);
	rk_Sustain->setTextBoxStyle(Slider::TextBoxAbove, true, 70, 20);
	rk_Sustain->setTextValueSuffix("Suustain");
	rk_Sustain->setValue(0.5);

	// release
	rk_Release = new ParameterSlider(*processor.adsrReleaseParam);
	rk_Release->setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	rk_Release->setRange(0.0, 1.0);
	rk_Release->setTextBoxStyle(Slider::TextBoxAbove, true, 70, 20);
	rk_Release->setTextValueSuffix("Release");
	rk_Release->setValue(0.5);
	
	// add controls
	//addAndMakeVisible(rk_OscLvl);
	//addAndMakeVisible(rk_OscWtPos);
	addAndMakeVisible(rk_FilterCutoff);
	addAndMakeVisible(rk_FilterReso);
	addAndMakeVisible(rk_FilterDryWet);
	addAndMakeVisible(rk_Lfo1Rate);
	addAndMakeVisible(rk_Lfo1Amp);
	addAndMakeVisible(rk_Lfo2Rate);
	addAndMakeVisible(rk_Lfo2Amp);
	addAndMakeVisible(rk_Attack);
	addAndMakeVisible(rk_Decay);
	addAndMakeVisible(rk_Sustain);
	addAndMakeVisible(rk_Release);

	//lastInputIndex = 0;
	//isAddingFromMidiInput = false;
	//startTime = Time::getMillisecondCounterHiRes() * 0.001;
	//addAndMakeVisible(midiInputList);
	//midiInputList.setTextWhenNoChoicesAvailable("No MIDI Inputs Enabled");
	//const StringArray midiInputs(MidiInput::getDevices());
	//midiInputList.addItemList(midiInputs, 1);
	//midiInputList.addListener(this);

	//find the first enabled device and use that by default
	//for (int i = 0; i < midiInputs.size(); ++i) {
	//	if (deviceManager.isMidiInputEnabled(midiInputs[i])) {
	//		setMidiInput(i);
	//		break;
	//	}
	//}

	//if (midiInputList.getSelectedId() == 0)
	//	setMidiInput(0);

	addAndMakeVisible(keyboardComponent);
	//keyboardState.addListener(this);

	//addAndMakeVisible(midiMessageBox);
	//midiMessageBox.setMultiLine(true);
	//midiMessageBox.setReturnKeyStartsNewLine(true);
	//midiMessageBox.setReadOnly(true);
	//midiMessageBox.setScrollbarsShown(true);
	//midiMessageBox.setCaretVisible(false);
	//midiMessageBox.setPopupMenuEnabled(true);
	//midiMessageBox.setColour(TextEditor::backgroundColourId, Colour(0x32ffffff));
	//midiMessageBox.setColour(TextEditor::outlineColourId, Colour(0x1c000000));
	//midiMessageBox.setColour(TextEditor::shadowColourId, Colour(0x16000000));


	//componentsInitialized = true;
	setSize(800, 600);

	gainLabel.setText("Level", NotificationType::dontSendNotification);
	gainLabel.attachToComponent(rk_OscLvl, false);
}

SynthAudioProcessorEditor::~SynthAudioProcessorEditor()
{
}

//==============================================================================
void SynthAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

    // g.setColour (Colours::white);
    // g.setFont (15.0f);
    // g.drawFittedText ("Midi Volume", getLocalBounds(), Justification::centred, 1);
}

void SynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	//if (!componentsInitialized) return;

	int h = getHeight();
	int w = getWidth();

	int knobWidth = w / 8;

	rk_OscLvl->setBounds(0, h / 2 - knobWidth, knobWidth, knobWidth);
	rk_OscWtPos->setBounds(knobWidth, h / 2 - knobWidth, knobWidth, knobWidth);

	rk_FilterCutoff->setBounds(w / 2, h / 2 - knobWidth, knobWidth, knobWidth);
	rk_FilterReso->setBounds(w / 2 + knobWidth, h / 2 - knobWidth, knobWidth, knobWidth);
	rk_FilterDryWet->setBounds(w / 2 + 2*knobWidth, h / 2 - knobWidth, knobWidth, knobWidth);

	rk_Lfo1Rate->setBounds(0, 3*h / 4 - knobWidth, knobWidth, knobWidth);
	rk_Lfo1Amp->setBounds(knobWidth, 3*h / 4 - knobWidth, knobWidth, knobWidth);

	rk_Lfo2Rate->setBounds(0, h - knobWidth, knobWidth, knobWidth);
	rk_Lfo2Amp->setBounds(knobWidth, h - knobWidth, knobWidth, knobWidth);
	
	rk_Attack->setBounds(w / 2, h - knobWidth, knobWidth, knobWidth);
	rk_Decay->setBounds(w / 2 + knobWidth, h - knobWidth, knobWidth, knobWidth);
	rk_Sustain->setBounds(w / 2 + 2 * knobWidth, h - knobWidth, knobWidth, knobWidth);
	rk_Release->setBounds(w / 2 + 3 * knobWidth, h - knobWidth, knobWidth, knobWidth);

	Rectangle<int> area(getLocalBounds());
	midiInputList.setBounds(area.removeFromTop(36).removeFromRight(getWidth() - 150).reduced(8));
	keyboardComponent.setBounds(area.removeFromTop(80).reduced(8));
	//midiMessageBox.setBounds(area.reduced(8));

}

void SynthAudioProcessorEditor::sliderValueChanged(Slider* slider) {

	if (slider == rk_OscWtPos) {
		//change wavetable position
	}
	else if (slider == rk_OscLvl) {
		// update oscilator output level
	}	

}

void SynthAudioProcessorEditor::updateAngleDelta() {
	//processor.frequency = frequencySlider.getValue();
}
//
//void SynthAudioProcessorEditor::comboBoxChanged(ComboBox* box) {
//	if (box == &midiInputList) {
//		setMidiInput(midiInputList.getSelectedItemIndex()); 
//	}
//}
//
////void SynthAudioProcessorEditor::setMidiInput(int index) {
//	const StringArray list(MidiInput::getDevices());
//	deviceManager.removeMidiInputCallback(list[lastInputIndex], this);
//	const String newInput(list[index]);
//	if (!deviceManager.isMidiInputEnabled(newInput)) {
//		deviceManager.setMidiInputEnabled(newInput, true);
//	}
//	deviceManager.addMidiInputCallback(newInput, this);
//	midiInputList.setSelectedId(index + 1, dontSendNotification);
//	lastInputIndex = index;
//}

//void SynthAudioProcessorEditor::handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message) {
//	const ScopedValueSetter<bool> scopedInputFlag(isAddingFromMidiInput, true);
//	keyboardState.processNextMidiEvent(message);
//	postMessageToList(message, source->getName());
//}

//void SynthAudioProcessorEditor::handleNoteOn(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) {
//	if (!isAddingFromMidiInput) {
//		MidiMessage m(MidiMessage::noteOn(midiChannel, midiNoteNumber, velocity));
//		m.setTimeStamp(Time::getMillisecondCounterHiRes()*0.001);
//		postMessageToList(m, "On-Screen Keyboard");
//	}
//}
//
//void SynthAudioProcessorEditor::handleNoteOff(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) {
//	if (!isAddingFromMidiInput) {
//		MidiMessage m(MidiMessage::noteOff(midiChannel, midiNoteNumber));
//		m.setTimeStamp(Time::getMillisecondCounterHiRes()*0.001);
//		postMessageToList(m, "On-Screen Keyboard");
//	}
//}

//void SynthAudioProcessorEditor::postMessageToList(const MidiMessage& message, const String& source) {
//	IncomingMessageCallback *incomingMsg = new IncomingMessageCallback(this, message, source);
//	incomingMsg->post();
//}
//
//void SynthAudioProcessorEditor::addMessageToList(const MidiMessage& message, const String& source) {
//	const double time = message.getTimeStamp() - startTime;
//
//	const int hours = ((int)(time / 3600.0)) % 24;
//	const int minutes = ((int)(time / 60.0)) % 60;
//	const int seconds = ((int)time) % 60;
//	const int millis = ((int)(time*1000.0)) % 1000;
//
//	const String timecode(String::formatted("%02d:%02d:%02d.%03d",
//		hours,
//		minutes,
//		seconds,
//		millis));
//
//	const String description(getMidiMessageDescription(message));
//
//	const String midiMessageString(timecode + " - " + description + " (" + source + ") ");
//	logMessage(midiMessageString);
//}
//
//String SynthAudioProcessorEditor::getMidiMessageDescription(const MidiMessage& m) {
//	if (m.isNoteOn())           return "Note on " + MidiMessage::getMidiNoteName(m.getNoteNumber(), true, true, 3);
//	if (m.isNoteOff())          return "Note off " + MidiMessage::getMidiNoteName(m.getNoteNumber(), true, true, 3);
//	if (m.isProgramChange())    return "Program change " + String(m.getProgramChangeNumber());
//	if (m.isPitchWheel())       return "Pitch wheel " + String(m.getPitchWheelValue());
//	if (m.isAftertouch())       return "After touch " + MidiMessage::getMidiNoteName(m.getNoteNumber(), true, true, 3) + ": " + String(m.getAfterTouchValue());
//	if (m.isChannelPressure())  return "Channel pressure " + String(m.getChannelPressureValue());
//	if (m.isAllNotesOff())      return "All notes off";
//	if (m.isAllSoundOff())      return "All sound off";
//	if (m.isMetaEvent())        return "Meta event";
//
//	if (m.isController()) {
//		String name(MidiMessage::getControllerName(m.getControllerNumber()));
//
//		if (name.isEmpty())
//			name = "[" + String(m.getControllerNumber()) + "]";
//
//		return "Controller " + name + ": " + String(m.getControllerValue());
//	}
//
//	return String::toHexString(m.getRawData(), m.getRawDataSize());
//}
//
//void SynthAudioProcessorEditor::logMessage(const String& m) {
//	midiMessageBox.moveCaretToEnd();
//	midiMessageBox.insertTextAtCaret(m + newLine);
//}

//==============================================================================
// quick-and-dirty function to format a timecode string
//static String timeToTimecodeString(double seconds) {
//	const int millisecs = roundToInt(seconds * 1000.0);
//	const int absMillisecs = std::abs(millisecs);
//
//	return String::formatted("%02d:%02d:%02d.%03d",
//		millisecs / 3600000,
//		(absMillisecs / 60000) % 60,
//		(absMillisecs / 1000) % 60,
//		absMillisecs % 1000);
//}
//
//// quick-and-dirty function to format a bars/beats string
//static String quarterNotePositionToBarsBeatsString(double quarterNotes, int numerator, int denominator) {
//	if (numerator == 0 || denominator == 0)
//		return "1|1|000";
//
//	const int quarterNotesPerBar = (numerator * 4 / denominator);
//	const double beats = (fmod(quarterNotes, quarterNotesPerBar) / quarterNotesPerBar) * numerator;
//
//	const int bar = ((int)quarterNotes) / quarterNotesPerBar + 1;
//	const int beat = ((int)beats) + 1;
//	const int ticks = ((int)(fmod(beats, 1.0) * 960.0 + 0.5));
//
//	return String::formatted("%d|%d|%03d", bar, beat, ticks);
//}

//// Updates the text in our position label.
//void SynthAudioProcessorEditor::updateTimecodeDisplay(AudioPlayHead::CurrentPositionInfo pos) {
//	MemoryOutputStream displayText;
//
//	displayText << "[" << SystemStats::getJUCEVersion() << "]   "
//		<< String(pos.bpm, 2) << " bpm, "
//		<< pos.timeSigNumerator << '/' << pos.timeSigDenominator
//		<< "  -  " << timeToTimecodeString(pos.timeInSeconds)
//		<< "  -  " << quarterNotePositionToBarsBeatsString(pos.ppqPosition,
//			pos.timeSigNumerator,
//			pos.timeSigDenominator);
//
//	if (pos.isRecording)
//		displayText << "  (recording)";
//	else if (pos.isPlaying)
//		displayText << "  (playing)";
//
//	timecodeDisplayLabel.setText(displayText.toString(), dontSendNotification);
//}
