/*
  ==============================================================================

    DiatonicChordProgressionAndScaleMidiMap.cpp
    Created: 20 Feb 2017 12:27:38pm
    Author:  blist

  ==============================================================================
*/

#include "DiatonicChordProgressionAndScaleMidiMap.h"

DiatonicChordProgressionAndScaleMidiMap::DiatonicChordProgressionAndScaleMidiMap()
{
	chordMidiMap = new DiatonicChordProgressionMidiMap();
	scaleMidiMap = new ScaleMidiMap();
	scaleMidiMap->setShouldNormalizeTheOutput(true);
	midiMap = new BlackAndWhiteMidiMap(chordMidiMap, scaleMidiMap);
}
Array<int> DiatonicChordProgressionAndScaleMidiMap::map(int note)
{
	return midiMap->map(note);
}

DiatonicChordProgressionMidiMap* DiatonicChordProgressionAndScaleMidiMap::getChordMidiMap()
{
	return chordMidiMap;
}
ScaleMidiMap* DiatonicChordProgressionAndScaleMidiMap::getScaleMidiMap()
{
	return scaleMidiMap;
}