#include "../JuceLibraryCode/JuceHeader.h"
#include <iostream>      // for cout and cin
#include <math.h>
#include "MidiMap.h"
#include "ChordProgressionAndScaleMidiMap.h"
#include "SimpleVoiceLeader.h"
#include <sstream>

using namespace std;

struct scaleItem {
	String name;
	Array<int> pitch_set;
};

struct presetItem {
	int blackId;
	int whiteId;
	int chordSize;
};

class MiddleCore                   // begin declaration of the class
{
public:                  // begin public section
	MiddleCore();     // constructor
	~MiddleCore();                  // destructor
	void initScales();
	void initPresets();
	void setPreset(String name);
	void setProgression(Array<String> p);
	void setKey(int k);
	void setChordOctave(int oct);
	void setChordSize(int size);
	void setChordAnchorIndex(int blackNoteValue);
	bool isBlack(int val);
	pair<Array<int>, Array<int>> get(int val, bool isNoteOn);

private:
	int lastBlackIndex = -1;
	map<int, scaleItem> scales;
	map<String, presetItem> presets;
	ChordProgressionAndScaleMidiMap* midiMap;
	SimpleVoiceLeader* voiceLeader;
};
