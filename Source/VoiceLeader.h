#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
#include <map>
#include <stdexcept>
using namespace std;
#define N  3

struct MatchItem {
	int i;
	int j;
	int diff;
};

class VoiceLeader
{
public:
	VoiceLeader();
	~VoiceLeader();
	int modDiff(int x, int y);
	pair<map<int, vector<MatchItem>>, map<int, vector<MatchItem>>> scoreMatches(vector<int> from, vector<int> to);
	void sortMatches(vector<MatchItem>& matches);
	vector<int> leadResult(vector<int> from, vector<int> to, vector<int> assignments);
	vector<int> lead(vector<int> from, vector<int> to);
	pair<vector<int>, vector<int>> leadInto(vector<int> to, bool isNoteOn);
	vector<int> stable_marriage(const vector<int>& preferences, const int n);
	vector<int> woman_ranking_map(const vector<int>& preferences, const int n);

private:
	vector<int> from; //the chord to lead from
};
