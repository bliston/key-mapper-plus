/*
  ==============================================================================

    MidiUtils.h
    Created: 20 Feb 2017 3:28:45pm
    Author:  blist

  ==============================================================================
*/

#ifndef MIDIFUNCTIONS_H_INCLUDED
#define MIDIFUNCTIONS_H_INCLUDED
#include "../JuceLibraryCode/JuceHeader.h"
using namespace std;
struct piano_key_info {
	bool isBlack;
	int index;
};

class MidiFunctions {
public:
	static const Array<int>  WHITE_INDICES;
	static const Array<int>  BLACK_INDICES;
	static piano_key_info pianoKeyInfo(int val);
	static int posMod(int m, int n);
	static bool isBlack(int val);
	static int scaleIndexOfNoteValue(Array<int> scale, int val);
	static int scaleNoteValueAtIndex(Array<int>  scale, int index);
	static int indexOf(Array<int> vec, int val);
};



#endif  // MIDIFUNCTIONS_H_INCLUDED
