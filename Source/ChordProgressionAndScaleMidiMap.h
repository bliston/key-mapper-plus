/*
  ==============================================================================

    ChordProgressionAndScaleMidiMap.h
    Created: 20 Feb 2017 12:27:38pm
    Author:  blist

  ==============================================================================
*/

#ifndef CHORDPROGRESSIONANDSCALEMIDIMAP_H_INCLUDED
#define CHORDPROGRESSIONANDSCALEMIDIMAP_H_INCLUDED
#include "../JuceLibraryCode/JuceHeader.h"
#include "MidiMap.h"
#include "BlackAndWhiteMidiMap.h"
#include "ChordProgressionMidiMap.h"
#include "ScaleMidiMap.h"
class ChordProgressionAndScaleMidiMap : public MidiMap {
public:
	ChordProgressionAndScaleMidiMap();
	ChordProgressionMidiMap* getChordMidiMap();
	ScaleMidiMap* getScaleMidiMap();
	Array<int> map(int note);
	
private:
	BlackAndWhiteMidiMap* midiMap;
	ChordProgressionMidiMap* chordMidiMap;
	ScaleMidiMap* scaleMidiMap;
};




#endif  // CHORDPROGRESSIONANDSCALEMIDIMAP_H_INCLUDED
