/*
  ==============================================================================

    ScaleMidiMap.cpp
    Created: 20 Feb 2017 12:10:10pm
    Author:  blist

  ==============================================================================
*/

#include "ScaleMidiMap.h"

ScaleMidiMap::ScaleMidiMap()
{
	scaleSizeDegreeOffsetMap[5] = -12;
	scaleSizeDegreeOffsetMap[6] = -6;
	scaleSizeDegreeOffsetMap[7] = 0;
	setShouldNormalizeTheOutput(false);
}
ScaleMidiMap::ScaleMidiMap(Array<int> s, int key, bool normalizeTheOutput)
{
	ScaleMidiMap();
	setScale(s);
	setKey(key);
	setShouldNormalizeTheOutput(normalizeTheOutput);
}
ScaleMidiMap::~ScaleMidiMap()
{

}
void ScaleMidiMap::setScale(Array<int> s)
{
	scale = s;
}
Array<int> ScaleMidiMap::getScale()
{
	return scale;
}
void ScaleMidiMap::setKey(int k)
{
	key = k;
}
int ScaleMidiMap::getKey()
{
	return key;
}
Array<int> ScaleMidiMap::map(int note)
{
	piano_key_info keyInfo = MidiFunctions::pianoKeyInfo(note);
	int index = shouldNormalizeTheOutput ? keyInfo.index + scaleSizeDegreeOffsetMap[scale.size()] : keyInfo.index;
	return { scaleValueAtIndex(index) };
}

int ScaleMidiMap::scaleValueAtIndex(int index)
{
	return { key + MidiFunctions::scaleNoteValueAtIndex(scale, index) };
}

void ScaleMidiMap::setShouldNormalizeTheOutput(bool shouldNormalize)
{
	shouldNormalizeTheOutput = shouldNormalize;
}