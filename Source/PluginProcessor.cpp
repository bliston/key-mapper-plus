/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <string>
#include <limits>
//==============================================================================

MiddlePluginAudioProcessor::MiddlePluginAudioProcessor() 
	: parameters(*this, nullptr)
{
	bassNotesChannel = 1;
	blackNotesChannel = 2;
	whiteNotesChannel = 3;


	parameters.state = ValueTree(Identifier("MiddlePlugin"));
	parameters.state.setProperty("scalesId", "Major 1", nullptr);
	parameters.state.setProperty("key", "C", nullptr);
	parameters.state.setProperty("chordOctave", "3", nullptr);
	parameters.state.setProperty("chordSize", "3", nullptr);
	parameters.state.setProperty("progressionString", "Am F G", nullptr);

	keyMap["C"] = 0;
	keyMap["C#/Db"] = 1;
	keyMap["D"] = 2;
	keyMap["D#/Eb"] = 3;
	keyMap["E"] = 4;
	keyMap["F"] = 5;
	keyMap["F#/Gb"] = 6;
	keyMap["G"] = 7;
	keyMap["G#/Ab"] = 8;
	keyMap["A"] = 9;
	keyMap["A#/Bb"] = 10;
	keyMap["B"] = 11;
}

MiddlePluginAudioProcessor::~MiddlePluginAudioProcessor()
{
}

//==============================================================================

const String MiddlePluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MiddlePluginAudioProcessor::acceptsMidi() const
{
    return true;
}

bool MiddlePluginAudioProcessor::producesMidi() const
{
    return true;
}

bool MiddlePluginAudioProcessor::isMidiEffect() const
{
    return true;
}

double MiddlePluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MiddlePluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MiddlePluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MiddlePluginAudioProcessor::setCurrentProgram (int index)
{
}

const String MiddlePluginAudioProcessor::getProgramName (int index)
{
    return String();
}

void MiddlePluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MiddlePluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

}

void MiddlePluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MiddlePluginAudioProcessor::setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet)
{
    // Reject any bus arrangements that are not compatible with your plugin

    const int numChannels = preferredSet.size();

   #if JucePlugin_IsMidiEffect
    if (numChannels != 0)
        return false;
   #elif JucePlugin_IsSynth
    if (isInput || (numChannels != 1 && numChannels != 2))
        return false;
   #else
    if (numChannels != 1 && numChannels != 2)
        return false;

    if (! setPreferredBusArrangement (! isInput, bus, preferredSet))
        return false;
   #endif

    return setPreferredBusArrangement (isInput, bus, preferredSet);
}
#endif

MidiBuffer MiddlePluginAudioProcessor::allBlackNotesOff(const int time)
{
	MidiBuffer events;
	for (int n = 0; n < 128; n++) {
		MidiMessage mm = MidiMessage::noteOff(blackNotesChannel, n);
		events.addEvent(mm, time);
	}
	return events;
}

MidiBuffer MiddlePluginAudioProcessor::mappedEvents(MidiMessage m, const int time)
{
	MidiBuffer events;
	bool isBlack = mc.isBlack(m.getNoteNumber());
	pair<Array<int>, Array<int>> notes;
	int bass;
	int note;
	MidiMessage mm;
	{// white scale notes
		if (m.isNoteOff()) {
			notes = mc.get(m.getNoteNumber(), false);
			if (isBlack) {
				blackNotesOn.clear();
			}
		}
		else if (m.isNoteOn()) {
			notes = mc.get(m.getNoteNumber(), true);
			if (isBlack) {
				blackNotesOn.add(m.getNoteNumber());
				if (blackNotesOn.size() > 2) {
					int minBlack = *std::min_element(blackNotesOn.begin(), blackNotesOn.end());
					//mc.setChordAnchorIndex(minBlack);
					return allBlackNotesOff(time);
				}
			}
		}
		if (isBlack)
		{
			bass = notes.first[0];
			notes.first.remove(0);
			mm = MidiMessage::noteOff(bassNotesChannel, bass);
			events.addEvent(mm, time);
			for (int n : notes.first) 
			{
				if (isPositiveAndBelow(n, (int)128)) {
					mm = MidiMessage::noteOff(blackNotesChannel, n);
					events.addEvent(mm, time);
				}
			}
		}
		else 
		{
			for (int n : notes.first) 
			{
				if (isPositiveAndBelow(n, (int)128)) {
					mm = MidiMessage::noteOff(whiteNotesChannel, n);
					events.addEvent(mm, time);
				}
			}
		}
		if (isBlack)
		{
			bass = notes.second[0];
			notes.second.remove(0);
			mm = MidiMessage::noteOn(bassNotesChannel, bass, m.getVelocity());
			events.addEvent(mm, time);
			for (int n : notes.second) {
				if (isPositiveAndBelow(n, (int)128)) {
					mm = MidiMessage::noteOn(blackNotesChannel, n, m.getVelocity());
					events.addEvent(mm, time);
				}
			}
		}
		else
		{
			for (int n : notes.second) 
			{
				if (isPositiveAndBelow(n, (int)128)) {
					mm = MidiMessage::noteOn(whiteNotesChannel, n, m.getVelocity());
					events.addEvent(mm, time);
				}
			}
		}

		return events;
	}
}

void MiddlePluginAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	updateMiddleCore();
	buffer.clear();

	MidiBuffer processedMidi;
	int time;
	MidiMessage m;

	for (MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, time);)
	{
		MidiBuffer mEvents = mappedEvents(m, time);
		int mtime;
		MidiMessage mm;
		for (MidiBuffer::Iterator i(mEvents); i.getNextEvent(mm, mtime);)
		{
			processedMidi.addEvent(mm, mtime);
		}
	}

	midiMessages.swapWith(processedMidi);
}

//==============================================================================
bool MiddlePluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MiddlePluginAudioProcessor::createEditor()
{
    return new MiddlePluginAudioProcessorEditor(*this, parameters);
}

//==============================================================================
void MiddlePluginAudioProcessor::getStateInformation(MemoryBlock& destData)
{
	ScopedPointer<XmlElement> xml(parameters.state.createXml());
	copyXmlToBinary(*xml, destData);
}

void MiddlePluginAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState != nullptr)
	{
		if (xmlState->hasTagName(parameters.state.getType()))
		{
			parameters.state = ValueTree::fromXml(*xmlState);
			updateMiddleCore();
		}	
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MiddlePluginAudioProcessor();
}

String MiddlePluginAudioProcessor::decodeScalesProperty(String input)
{
	return input;
}

int MiddlePluginAudioProcessor::decodeKeyProperty(String input)
{
	return keyMap[input];
}

int MiddlePluginAudioProcessor::decodeChordOctaveProperty(String input)
{
	return input.getIntValue();
}

int MiddlePluginAudioProcessor::decodeChordSizeProperty(String input)
{
	return input.getIntValue();
}

Array<String> MiddlePluginAudioProcessor::decodeProgressionProperty(String input)
{
	//StringArray tokens;
	//tokens.addTokens(input, " ", "");
	//return stringToVectorOfDigits(tokens.joinIntoString("").toStdString());

	//::std::string symbolToSplit = input.toStdString();
	//::std::string regexString = "\s+";
	//::std::regex regexDelimiter(regexString);
	//Array<String> chords = Bach::DataUtils::split(symbolToSplit, regexDelimiter);
	Array<String> chordsArray;
	StringArray tokens;
	tokens = StringArray::fromTokens(input, true);
	for (auto c : tokens)
	{
		chordsArray.add(c);
	}
	return chordsArray;
}

Array<int> MiddlePluginAudioProcessor::stringToVectorOfDigits(string id)
{
	Array<int> digits;
	string::iterator it;
	for (it = id.begin(); it != id.end(); it++)
	{
		int d = *it;
		digits.add(d + 1);
	}
	return digits;
}

void MiddlePluginAudioProcessor::updateMiddleCore()
{
	String scalesId = decodeScalesProperty(parameters.state.getProperty("scalesId").toString());
	int key = decodeKeyProperty(parameters.state.getProperty("key").toString());
	int chordOctave = decodeChordOctaveProperty(parameters.state.getProperty("chordOctave").toString());
	int chordSize = decodeChordSizeProperty(parameters.state.getProperty("chordSize").toString());
	Array<String> progression;
	if (parameters.state.hasProperty("progressionString"))
	{
		progression = decodeProgressionProperty(parameters.state.getProperty("progressionString").toString());
	}
	mc.setPreset(scalesId);
	mc.setKey(key);
	mc.setChordOctave(chordOctave);
	mc.setChordSize(chordSize);
	mc.setProgression(progression);
}
