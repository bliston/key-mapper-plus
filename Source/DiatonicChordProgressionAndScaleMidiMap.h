/*
  ==============================================================================

    DiatonicChordProgressionAndScaleMidiMap.h
    Created: 20 Feb 2017 12:27:38pm
    Author:  blist

  ==============================================================================
*/

#ifndef DIATONICCHORDPROGRESSIONANDSCALEMIDIMAP_H_INCLUDED
#define DIATONICCHORDPROGRESSIONANDSCALEMIDIMAP_H_INCLUDED
#include "../JuceLibraryCode/JuceHeader.h"
#include "MidiMap.h"
#include "BlackAndWhiteMidiMap.h"
#include "DiatonicChordProgressionMidiMap.h"
#include "ScaleMidiMap.h"
class DiatonicChordProgressionAndScaleMidiMap : public MidiMap {
public:
	DiatonicChordProgressionAndScaleMidiMap();
	DiatonicChordProgressionMidiMap* getChordMidiMap();
	ScaleMidiMap* getScaleMidiMap();
	Array<int> map(int note);
	
private:
	BlackAndWhiteMidiMap* midiMap;
	DiatonicChordProgressionMidiMap* chordMidiMap;
	ScaleMidiMap* scaleMidiMap;
};




#endif  // DIATONICCHORDPROGRESSIONANDSCALEMIDIMAP_H_INCLUDED
