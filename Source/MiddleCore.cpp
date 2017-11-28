/*
  ==============================================================================

    MiddleCore.cpp
    Created: 19 Oct 2016 1:07:03am
    Author:  blist

  ==============================================================================
*/

#include "MiddleCore.h"
// constructor of MiddleCore,
MiddleCore::MiddleCore()
{
	midiMap = new ChordProgressionAndScaleMidiMap();
	initScales();
	initPresets();
	setPreset("Major");
	voiceLeader = new SimpleVoiceLeader(midiMap->getChordMidiMap()->getChordReferenceNoteValue());
}

MiddleCore::~MiddleCore()                 // destructor, just an example
{

}

// definition of methods

void MiddleCore::initScales()
{
	scales[321] = { "Iwato Japan",{ 0, 1, 5, 6, 10 } };
	scales[323] = { "Japanese",{ 0, 1, 5, 7, 8 } };
	scales[371] = { "Hirajoshi Japan",{ 0, 2, 3, 7, 8 } };
	scales[393] = { "Major Pentatonic",{ 0, 2, 4, 7, 9 } };
	scales[400] = { "Unknown",{ 0, 2, 4, 9, 11 } };
	scales[408] = { "Ritusen Japan",{ 0, 2, 5, 7, 9 } };
	scales[465] = { "Minor Blues Pentatonic",{ 0, 3, 5, 7, 10 } };
	scales[673] = { "Raga Simantini",{ 0, 1, 3, 5, 7, 8 } };
	scales[785] = { "Major Blues",{ 0, 2, 3, 4, 7, 9 } };
	scales[823] = { "Hawaiian",{ 0, 2, 3, 7, 9, 11 } };
	scales[936] = { "Minor Blues",{ 0, 3, 5, 6, 7, 10 } };
	scales[1191] = { "Locrian",{ 0, 1, 3, 5, 6, 8, 10 } };
	scales[1193] = { "Locrian Natural Maj 6",{ 0, 1, 3, 5, 6, 9, 10 } };
	scales[1197] = { "Phryigian",{ 0, 1, 3, 5, 7, 8, 10 } };
	scales[1232] = { "Phrygian Dominant",{ 0, 1, 4, 5, 7, 8, 10 } };
	scales[1323] = { "Minor",{ 0, 2, 3, 5, 7, 8, 10 } };
	scales[1324] = { "Harmonic Minor",{ 0, 2, 3, 5, 7, 8, 11 } };
	scales[1326] = { "Melodic Minor",{ 0, 2, 3, 5, 7, 9, 11 } };
	scales[1361] = { "Major",{ 0, 2, 4, 5, 7, 9, 11 } };
	scales[1364] = { "Harmonic Major",{ 0, 2, 4, 5, 8, 9, 11 } };
}

void MiddleCore::initPresets()
{

	presets["Major 1"] = { 1361, 1361, 3 };
	presets["Major Solo 1"] = { 1361, 393, 3 };
	presets["Minor 1"] = { 1323, 1323, 3 };
	presets["Minor Solo 1"] = { 1323, 465, 3 };
	presets["Harmonic Minor 1"] = { 1324, 1324, 3 };
	presets["Harmonic Minor Solo 1"] = { 1324, 371, 3 };
	presets["Major Blues Solo 1"] = { 1361, 785, 3 };
	presets["Minor Blues Solo 1"] = { 1323, 936, 3 };
}

void MiddleCore::setPreset(String name)
{
	presetItem selPreset = presets[name];
	midiMap->getChordMidiMap()->setScale(scales[selPreset.blackId].pitch_set);
	midiMap->getScaleMidiMap()->setScale(scales[selPreset.whiteId].pitch_set);
	setChordSize(selPreset.chordSize);
}

void MiddleCore::setProgression(Array<String> p)
{
	midiMap->getChordMidiMap()->setProgression(p);
}

void MiddleCore::setKey(int k)
{
	midiMap->getChordMidiMap()->setKey(k);
	midiMap->getScaleMidiMap()->setKey(k);
}

void MiddleCore::setChordOctave(int oct)
{
	midiMap->getChordMidiMap()->setChordOctave(oct);
}

void MiddleCore::setChordSize(int size)
{
	midiMap->getChordMidiMap()->setChordSize(size);
}

void MiddleCore::setChordAnchorIndex(int blackNoteValue)
{
	midiMap->getChordMidiMap()->setChordAnchorIndex(blackNoteValue);
}

bool MiddleCore::isBlack(int val)
{
	return MidiFunctions::isBlack(val);
}

pair<Array<int>, Array<int>> MiddleCore::get(int val, bool isNoteOn)
{
	voiceLeader->setChordReferenceNoteValue(midiMap->getChordMidiMap()->getChordReferenceNoteValue());
	pair<Array<int>, Array<int>> result;
	piano_key_info keyInfo = MidiFunctions::pianoKeyInfo(val);
	Array<int> notes = midiMap->map(val);
	if (keyInfo.isBlack) {
		result = voiceLeader->leadInto(notes, isNoteOn, keyInfo.index == lastBlackIndex);
		lastBlackIndex = isNoteOn ? keyInfo.index : lastBlackIndex;
	}
	else {
		if (isNoteOn) {
			result.first = {};
			result.second = notes;
		}
		else {
			result.first = notes;
			result.second = {};
		}
		
	}
	return result;
}