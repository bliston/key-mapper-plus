/*
  ==============================================================================

    ChordProgressionAndScaleMidiMap.cpp
    Created: 20 Feb 2017 12:27:38pm
    Author:  blist

  ==============================================================================
*/

#include "ChordProgressionAndScaleMidiMap.h"

ChordProgressionAndScaleMidiMap::ChordProgressionAndScaleMidiMap()
{
	chordMidiMap = new ChordProgressionMidiMap();
	scaleMidiMap = new ScaleMidiMap();
	scaleMidiMap->setShouldNormalizeTheOutput(true);
	midiMap = new BlackAndWhiteMidiMap(chordMidiMap, scaleMidiMap);
}
Array<int> ChordProgressionAndScaleMidiMap::map(int note)
{
	return midiMap->map(note);
}

ChordProgressionMidiMap* ChordProgressionAndScaleMidiMap::getChordMidiMap()
{
	return chordMidiMap;
}
ScaleMidiMap* ChordProgressionAndScaleMidiMap::getScaleMidiMap()
{
	return scaleMidiMap;
}