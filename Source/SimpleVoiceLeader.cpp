/*
==============================================================================

VoiceLeader.cpp
Created: 19 Oct 2016 1:07:21am
Author:  blist

==============================================================================
*/

#include "SimpleVoiceLeader.h"
SimpleVoiceLeader::SimpleVoiceLeader()
{
	SimpleVoiceLeader(36);
}

SimpleVoiceLeader::SimpleVoiceLeader(int chordReferenceNoteVal)
{
	setChordReferenceNoteValue(chordReferenceNoteVal);
	last.first = {};
	last.second = { 36, 38, 40 }; //dummy init
}

SimpleVoiceLeader::~SimpleVoiceLeader()
{

}

void SimpleVoiceLeader::setChordReferenceNoteValue(int val)
{
	chordReferenceNoteValue = val;
}

int SimpleVoiceLeader::getChordReferenceNoteValue()
{
	return chordReferenceNoteValue;
}

int SimpleVoiceLeader::fitChordTone(int note)
{
	return chordReferenceNoteValue + note % 12 - chordReferenceNoteValue % 12;
}

int SimpleVoiceLeader::fitBass(int note)
{
	return note % 12 + bassOctave * 12;
}

Array<int> SimpleVoiceLeader::lead(Array<int> to)
{
	int bass = to[0];
	to.remove(0);
	Array<int> result;
	result.add(fitBass(bass));
	for (int n : to) {
		result.add(fitChordTone(n));
	}
	return result;
}

pair<Array<int>, Array<int>> SimpleVoiceLeader::leadInto(Array<int> to, bool isNoteOn, bool release)
{
	pair<Array<int>, Array<int>> result;
	Array<int> lead_result = lead(to);
	if (isNoteOn) {
		if (!last.second.isEmpty()) {//noteOn last noteOns not empty
			result.first = last.second;//turn off last noteOns
			result.second = lead_result;
		}
		else {//1. noteOn last noteOns is empty case
			result.first = {};//offs
			result.second = to;//ons
		}
		last = result;
	}
	else {//noteOff
		result.first = {};
		if (release) {
			result.first = last.second;
			result.second = {};
		}
		else {
			result.first = {};
			result.second = {};
		}
	}
	return result;
}
