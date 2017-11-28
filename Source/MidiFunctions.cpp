/*
  ==============================================================================

    PianoKeyInfo.cpp
    Created: 20 Feb 2017 3:28:45pm
    Author:  blist

  ==============================================================================
*/

#include "MidiFunctions.h"
const Array<int> MidiFunctions::WHITE_INDICES = { 0, 2, 4, 5, 7, 9, 11 };
const Array<int> MidiFunctions::BLACK_INDICES = { 1, 3, 6, 8, 10 };
piano_key_info MidiFunctions::pianoKeyInfo(int val)
{
	bool black = MidiFunctions::isBlack(val);
	Array<int> scale;
	scale = black ? MidiFunctions::BLACK_INDICES : MidiFunctions::WHITE_INDICES;
	int index = MidiFunctions::scaleIndexOfNoteValue(scale, val);
	piano_key_info result;
	result.isBlack = black;
	result.index = index;
	return result;
}
int MidiFunctions::posMod(int m, int n)
{
	return (m % n + n) % n;
}
bool MidiFunctions::isBlack(int val)
{
	bool result;
	switch (val % 12) {
	case 1:
	case 3:
	case 6:
	case 8:
	case 10: {
		result = true;
	}
			 break;
	default: {
		result = false;
	}
	}
	return result;
}
int MidiFunctions::scaleNoteValueAtIndex(Array<int> scale, int index)
{
	int n = scale.size();
	int i = index;
	int posResult = 12 * floor(i / n) + scale[i % n];
	int negResult = 12 * ceil((i + 1) / n - 1) + scale[posMod(i, n)];
	int result = i >= 0 ? posResult : negResult;
	return result;
}
int MidiFunctions::scaleIndexOfNoteValue(Array<int> scale, int val)
{
	int modIndex = indexOf(scale, val % 12);
	int numLoops = floor(val / 12);
	int result = numLoops * scale.size() + modIndex;
	return result;
}

int MidiFunctions::indexOf(Array<int> vec, int val)
{
	auto it = find(vec.begin(), vec.end(), val);
	if (it == vec.end()) return -1;
	return distance(vec.begin(), it);

}