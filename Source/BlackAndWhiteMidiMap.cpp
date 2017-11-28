/*
  ==============================================================================

    BlackAndWhiteMidiMap.cpp
    Created: 20 Feb 2017 12:09:47pm
    Author:  blist

  ==============================================================================
*/

#include "BlackAndWhiteMidiMap.h"

BlackAndWhiteMidiMap::BlackAndWhiteMidiMap(MidiMap* black, MidiMap* white)
{
	setBlackMidiMap(black);
	setWhiteMidiMap(white);
}
BlackAndWhiteMidiMap::~BlackAndWhiteMidiMap()
{

}
void BlackAndWhiteMidiMap::setBlackMidiMap(MidiMap* m)
{
	blackMidiMap = m;
}
MidiMap* BlackAndWhiteMidiMap::getBlackMidiMap()
{
	return blackMidiMap;
}
void BlackAndWhiteMidiMap::setWhiteMidiMap(MidiMap* m)
{
	whiteMidiMap = m;
}
MidiMap* BlackAndWhiteMidiMap::getWhiteMidiMap()
{
	return whiteMidiMap;
}
Array<int> BlackAndWhiteMidiMap::map(int note)
{
	bool isBlack = MidiFunctions::isBlack(note);
	return isBlack ? getBlackMidiMap()->map(note) : getWhiteMidiMap()->map(note);
}