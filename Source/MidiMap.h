/*
  ==============================================================================

    MidiMap.h
    Created: 20 Feb 2017 10:57:40am
    Author:  blist

  ==============================================================================
*/

#ifndef MIDIMAP_H_INCLUDED
#define MIDIMAP_H_INCLUDED
#include "../JuceLibraryCode/JuceHeader.h"

class MidiMap {
public:
	virtual Array<int> map(int note) = 0;
};



#endif  // MIDIMAP_H_INCLUDED
