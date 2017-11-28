/*
  ==============================================================================

    ChordProgression.h
    Created: 19 Feb 2017 2:28:41pm
    Author:  blist

  ==============================================================================
*/

#ifndef CHORDPROGRESSIONMIDIMAP_H_INCLUDED
#define CHORDPROGRESSIONMIDIMAP_H_INCLUDED
#include "../JuceLibraryCode/JuceHeader.h"
#include <iostream>      // for cout and cin
#include <math.h>
#include <Array>
#include <map>
#include <stdexcept>
#include "VoiceLeader.h"
#include "SimpleVoiceLeader.h"
#include <sstream>
#include "MidiMap.h"
#include "ScaleMidiMap.h"
#include "MidiFunctions.h"

class ChordProgressionMidiMap : public MidiMap
{
public:
	ChordProgressionMidiMap();
	~ChordProgressionMidiMap();
	void setScale(Array<int> _chordScale);
	void setProgression(Array<String> _progression);
	Array<String> getProgression();
	Array<int> map(int index);
	Array<int> getChord(int degree);
	void setKey(int k);
	void setChordOctave(int oct);
	void setChordSize(int size);
	void setChordAnchorIndex(int noteValue);
	int getChordReferenceNoteValue();

private:
	ScaleMidiMap scaleMidiMap;
	Array<String> progression;
	int key;
	int chordOctave;
	int chordSize;
	int chordAnchorIndex;
};

#endif  // CHORDPROGRESSIONMIDIMAP_H_INCLUDED
