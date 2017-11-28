/*
  ==============================================================================

    DiatonicChordProgressionMidiMap.cpp
    Created: 19 Feb 2017 2:28:41pm
    Author:  blist

  ==============================================================================
*/

#include "DiatonicChordProgressionMidiMap.h"

DiatonicChordProgressionMidiMap::DiatonicChordProgressionMidiMap()
{
	key = 4;
	chordOctave = 4;
	chordSize = 4;
	setChordAnchorIndex(25);
	scaleMidiMap.setScale(MidiFunctions::WHITE_INDICES);
}

DiatonicChordProgressionMidiMap::~DiatonicChordProgressionMidiMap()
{
}

void DiatonicChordProgressionMidiMap::setProgression(Array<int> _progression)
{
	progression = _progression;
}

Array<int> DiatonicChordProgressionMidiMap::getProgression()
{
	return progression;
}

void DiatonicChordProgressionMidiMap::setScale(Array<int> s)
{
	scaleMidiMap.setScale(s);
}

Array<int> DiatonicChordProgressionMidiMap::map(int note)
{
	Array<int> _progression = getProgression();
	piano_key_info keyInfo = MidiFunctions::pianoKeyInfo(note);
	int blackKeyIndexPosMod = MidiFunctions::posMod(keyInfo.index, _progression.size());
	int blackAnchorIndexPosMod = MidiFunctions::posMod(chordAnchorIndex, _progression.size());
	int modChordIndex = MidiFunctions::posMod(blackKeyIndexPosMod - blackAnchorIndexPosMod, _progression.size());
	Array<int> chord = getChord(_progression[modChordIndex]);
	return chord;
}

Array<int> DiatonicChordProgressionMidiMap::getChord(int degree)
{
	int index = degree - 1;
	int one = scaleMidiMap.scaleValueAtIndex(index);
	index += 2;
	int three = scaleMidiMap.scaleValueAtIndex(index);
	index += 2;
	int five = scaleMidiMap.scaleValueAtIndex(index);
	index += 2;
	int seven = scaleMidiMap.scaleValueAtIndex(index);
	Array<int> triad = { one, three, five };
	Array<int> seventh = { one, three, five, seven };

	return chordSize == 3 ? triad : seventh;
}

void DiatonicChordProgressionMidiMap::setKey(int k)
{
	key = k;
	scaleMidiMap.setKey(getChordReferenceNoteValue());
}

void DiatonicChordProgressionMidiMap::setChordOctave(int oct)
{
	chordOctave = oct;
}

void DiatonicChordProgressionMidiMap::setChordSize(int size)
{
	chordSize = size;
}

void DiatonicChordProgressionMidiMap::setChordAnchorIndex(int blackNoteValue)
{
	piano_key_info pianoKey = MidiFunctions::pianoKeyInfo(blackNoteValue);
	chordAnchorIndex = pianoKey.index - 1;

}

int DiatonicChordProgressionMidiMap::getChordReferenceNoteValue()
{
	return key + 12 * (chordOctave + 1);
}