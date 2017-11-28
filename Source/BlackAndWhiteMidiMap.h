/*
  ==============================================================================

    BlackAndWhiteMidiMap.h
    Created: 20 Feb 2017 12:09:47pm
    Author:  blist

  ==============================================================================
*/

#ifndef BLACKANDWHITEMIDIMAP_H_INCLUDED
#define BLACKANDWHITEMIDIMAP_H_INCLUDED
#include <math.h>
#include <map>
#include <stdexcept>
#include "../JuceLibraryCode/JuceHeader.h"
#include "MidiMap.h"
#include "MidiFunctions.h"
using namespace std;
class BlackAndWhiteMidiMap : public MidiMap {
public:
	BlackAndWhiteMidiMap(MidiMap* black, MidiMap* white);
    ~BlackAndWhiteMidiMap();
    void setBlackMidiMap(MidiMap* m);
	MidiMap* getBlackMidiMap();
    void setWhiteMidiMap(MidiMap* m);
	MidiMap* getWhiteMidiMap();
    Array<int> map(int note);

private:
    MidiMap* blackMidiMap;
    MidiMap* whiteMidiMap;
};



#endif  // BLACKANDWHITEMIDIMAP_H_INCLUDED
