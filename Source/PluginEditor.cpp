/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

MiddlePluginAudioProcessorEditor::MiddlePluginAudioProcessorEditor(AudioProcessor& parent, AudioProcessorValueTreeState& vts)
	: AudioProcessorEditor(parent),
	valueTreeState(vts)
{
    LookAndFeel::setDefaultLookAndFeel(&lookAndFeel);
	scalesLabel.setText("Scales:", dontSendNotification);
	addAndMakeVisible(scalesLabel);

	scalesComboBox.addItem("Major 1", 1);
	scalesComboBox.addItem("Major Solo 1", 2);
	scalesComboBox.addItem("Minor 1", 3);
	scalesComboBox.addItem("Minor Solo 1", 4);
	scalesComboBox.addItem("Harmonic Minor 1", 5);
	scalesComboBox.addItem("Harmonic Minor Solo 1", 6);
	scalesComboBox.addItem("Major Blues Solo 1", 7);
	scalesComboBox.addItem("Minor Blues Solo 1", 8);

	addAndMakeVisible(scalesComboBox);
	scalesAttachment = new ValueTreeComboBoxAttachment(valueTreeState.state, &scalesComboBox, "scalesId");

	keyLabel.setText("Key:", dontSendNotification);
	addAndMakeVisible(keyLabel);

	keyComboBox.addItem("C", 1);
	keyComboBox.addItem("C#/Db", 2);
	keyComboBox.addItem("D", 3);
	keyComboBox.addItem("D#/Eb", 4);
	keyComboBox.addItem("E", 5);
	keyComboBox.addItem("F", 6);
	keyComboBox.addItem("F#/Gb", 7);
	keyComboBox.addItem("G", 8);
	keyComboBox.addItem("G#/Ab", 9);
	keyComboBox.addItem("A", 10);
	keyComboBox.addItem("A#/Bb", 11);
	keyComboBox.addItem("B", 12);

	addAndMakeVisible(keyComboBox);
	keyAttachment = new ValueTreeComboBoxAttachment(valueTreeState.state, &keyComboBox, "key");



	chordOctaveLabel.setText("Chord Octave:", dontSendNotification);
	addAndMakeVisible(chordOctaveLabel);
	chordOctaveComboBox.addItem("1", 1);
	chordOctaveComboBox.addItem("2", 2);
	chordOctaveComboBox.addItem("3", 3);
	chordOctaveComboBox.addItem("4", 4);
	chordOctaveComboBox.addItem("5", 5);
	chordOctaveComboBox.addItem("6", 6);

	addAndMakeVisible(chordOctaveComboBox);
	chordOctaveAttachment = new ValueTreeComboBoxAttachment(valueTreeState.state, &chordOctaveComboBox, "chordOctave");


	chordSizeLabel.setText("Chord Size:", dontSendNotification);
	addAndMakeVisible(chordSizeLabel);

	chordSizeComboBox.addItem("3", 1);
	chordSizeComboBox.addItem("4", 2);

	addAndMakeVisible(chordSizeComboBox);
	chordSizeAttachment = new ValueTreeComboBoxAttachment(valueTreeState.state, &chordSizeComboBox, "chordSize");



	progressionLabel.setText("Progression (ex: C Am F G):", dontSendNotification);
	addAndMakeVisible(progressionLabel);

	progressionInputLabel.setEditable(true);
	progressionInputLabel.setText("C Am F G", dontSendNotification);
	addAndMakeVisible(progressionInputLabel);
	progressionAttachment = new ChordNameProgressionValueTreeLabelAttachment(valueTreeState.state, &progressionInputLabel, "progressionString");
	setSize(paramComponentWidth + paramLabelWidth + 50, paramControlHeight * 5 + 50);
}

MiddlePluginAudioProcessorEditor::~MiddlePluginAudioProcessorEditor()
{
}

//==============================================================================
void MiddlePluginAudioProcessorEditor::resized()
{
    const int padding = 10;
	juce::Rectangle<int> r = getLocalBounds().reduced(padding);
	
	juce::Rectangle<int> scalesRect = r.removeFromTop(paramControlHeight);
	scalesLabel.setBounds(scalesRect.removeFromLeft(paramLabelWidth));
	scalesComboBox.setBounds(scalesRect.reduced(padding));

	juce::Rectangle<int> keyRect = r.removeFromTop(paramControlHeight);
	keyLabel.setBounds(keyRect.removeFromLeft(paramLabelWidth));
	keyComboBox.setBounds(keyRect.reduced(padding));

	juce::Rectangle<int> chordOctaveRect = r.removeFromTop(paramControlHeight);
	chordOctaveLabel.setBounds(chordOctaveRect.removeFromLeft(paramLabelWidth));
	chordOctaveComboBox.setBounds(chordOctaveRect.reduced(padding));

	juce::Rectangle<int> chordSizeRect = r.removeFromTop(paramControlHeight);
	chordSizeLabel.setBounds(chordSizeRect.removeFromLeft(paramLabelWidth));
	chordSizeComboBox.setBounds(chordSizeRect.reduced(padding));

	juce::Rectangle<int> progressionRect = r.removeFromTop(paramControlHeight);
	progressionLabel.setBounds(progressionRect.removeFromLeft(paramLabelWidth));
	progressionInputLabel.setBounds(progressionRect.reduced(padding));

}

void MiddlePluginAudioProcessorEditor::paint(Graphics& g)
{
	g.setColour(Colours::white);
	g.fillRect(getLocalBounds());
}
