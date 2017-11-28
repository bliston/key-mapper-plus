/*
  ==============================================================================

    DiatonicChordProgression.h
    Created: 19 Feb 2017 2:28:41pm
    Author:  blist

  ==============================================================================
*/

#ifndef DIATONICCHORDPROGRESSIONMIDIMAP_H_INCLUDED
#define DIATONICCHORDPROGRESSIONMIDIMAP_H_INCLUDED
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

class DiatonicChordProgressionMidiMap : public MidiMap
{
public:
	DiatonicChordProgressionMidiMap();
	~DiatonicChordProgressionMidiMap();
	void setScale(Array<int> _chordScale);
	void setProgression(Array<int> _progression);
	Array<int> getProgression();
	Array<int> map(int index);
	Array<int> getChord(int degree);
	void setKey(int k);
	void setChordOctave(int oct);
	void setChordSize(int size);
	void setChordAnchorIndex(int noteValue);
	int getChordReferenceNoteValue();

private:
	ScaleMidiMap scaleMidiMap;
	Array<int> progression;
	int key;
	int chordOctave;
	int chordSize;
	int chordAnchorIndex;
};

#endif  // DIATONICCHORDPROGRESSIONMIDIMAP_H_INCLUDED
