#ifndef SIMPLEVOICELEADER_H_INCLUDED
#define SIMPLEVOICELEADER_H_INCLUDED
#include "../JuceLibraryCode/JuceHeader.h"
#include <iostream>
#include <algorithm>
#include <iterator> 
#include <math.h>
#include <map>
#include <stdexcept>
using namespace std;

class SimpleVoiceLeader
{
public:
	SimpleVoiceLeader();
	SimpleVoiceLeader(int chordReferenceNoteValue);
	~SimpleVoiceLeader();
	void setChordReferenceNoteValue(int val);
	int getChordReferenceNoteValue();
	int fitChordTone(int note);
	int fitBass(int note);
	Array<int> lead(Array<int> to);
	pair<Array<int>, Array<int>> leadInto(Array<int> to, bool isNoteOn, bool release);

private:
	int chordReferenceNoteValue;
	int bassOctave = 3;
	pair<Array<int>, Array<int>> last;
};

#endif  // SIMPLEVOICELEADER_H_INCLUDED
