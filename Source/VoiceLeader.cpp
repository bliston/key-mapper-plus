/*
  ==============================================================================

    VoiceLeader.cpp
    Created: 19 Oct 2016 1:07:21am
    Author:  blist

  ==============================================================================
*/

#include "VoiceLeader.h"
VoiceLeader::VoiceLeader()
{
	from = {};
}

VoiceLeader::~VoiceLeader()
{

}

// definition of methods

int VoiceLeader::modDiff(int from, int to)
{
	int modFrom = from % 12; //2
	int modTo = to % 12; //8

	int forward = 0;
	int modForward = modFrom; //2
	while (modForward != modTo) {
		modForward = (modForward + 1) % 12;
		forward++;
	}

	int backward = 0;
	int modBackward = modFrom; //2
	while (modBackward != modTo) {
		modBackward = (12 + (modBackward - 1) % 12) % 12;
		backward--;
	}

	return (forward <= -1 * backward) ? forward : backward;

}

pair<map<int, vector<MatchItem>>, map<int, vector<MatchItem>>> VoiceLeader::scoreMatches(vector<int> from, vector<int> to)
{
	pair<map<int, vector<MatchItem>>, map<int, vector<MatchItem>>> matches;
	//vector<vector<int> > test{ { 0, 1, 2 }, { 0, 1, 2 } };
	//vector<vector<int> > res = cart_product(test);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			MatchItem mi;
			mi.i = i;
			mi.j = j;
			mi.diff = modDiff(from[i], to[j]);
			MatchItem mj;
			mj.i = j;
			mj.j = i;
			mj.diff = modDiff(to[j], from[i]);
			matches.first[i].push_back(mi);
			matches.second[j].push_back(mj);
		}
	}
	for (int i = 0; i < N; i++) {
		sortMatches(matches.first[i]);
		sortMatches(matches.second[i]);
	}
	printf("%s", "end of cartesian matches");
	return matches;
}

void VoiceLeader::sortMatches(vector<MatchItem>& matches)
{
	sort(matches.begin(), matches.end(), [](MatchItem a, MatchItem b) {
		return abs(a.diff) < abs(b.diff);
	});
}

vector<int> VoiceLeader::leadResult(vector<int> from, vector<int> to, vector<int> assignments)
{
	vector<int> result;
	for (int i = 0; i < N; i++) {
		int diff = modDiff(from[i], to[assignments[i]]);
		int r = from[i] + diff;
		result.push_back(r);
	}
	return result;
}

vector<int> VoiceLeader::lead(vector<int> from, vector<int> to)
{
	printf("%s", "beginning of lead");
	pair<map<int, vector<MatchItem>>, map<int, vector<MatchItem>>> matches = scoreMatches(from, to);
	vector<int> preferences;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int suitor = matches.second[i][j].j;
			preferences.push_back(suitor);
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int suitor = matches.first[i][j].j;
			preferences.push_back(suitor);
		}
	}

	printf("%s", "after for loops of lead");
	for (auto a : preferences) {
		printf("%d", a);
	}
	vector<int> assignments = stable_marriage(preferences, N);

	vector<int> result = leadResult(from, to, assignments);

	for (auto a : result) {
		printf("%d", a);
	}
	return result;
}

pair<vector<int>, vector<int>> VoiceLeader::leadInto(vector<int> to, bool isNoteOn)
{
	pair<vector<int>, vector<int>> result;
	if (isNoteOn) {
		if (!from.empty()) {
			result.first = from;
			vector<int> lead_result = lead(from, to);
			result.second = lead_result;
			from = lead_result;
		}
		else {
			result.first = {};
			result.second = to;
			from = to;
		}
	}
	else {
		result.first = from;
		result.second = {};
	}

	return result;
}

//***************************************************************************//
// The main event! This contains the implementation of how to compute a stable
// marriage. It also contains the definition of a few helper functions, and
// an alternative implementation that is in some ways "simpler".
// The implementation is based off of Kleinberg and Tardos, page 42 (section
// 2.3). There is always a balance between a sophisticated implementation,
// and an implementation that can be read by others. I hope this strikes a
// good balance for students. Definitely email me at <mygithubname>@outlook.com
// if you have suggestions or questions.
//***************************************************************************//

// The main algorithm.
vector<int> VoiceLeader::stable_marriage(const vector<int>& preferences, const int n) {
	// We preprocess the preference list so that it's 
	// constant time to determine if a woman prefers one suitor
	// over the other.
	auto woman_preferences = woman_ranking_map(preferences, n);

	// This is the ultimate product, where assignment[w] = m
	// means that woman w is married to suitor m. We use -1 to indicate
	// unattached.
	vector<int> assignment(n, -1);

	// Set up our worklist, of suitors still needing to be married.
	// We use an array so that we only allocate memory once.
	vector<int> worklist(n);
	for (int i = 0; i < n; ++i) { worklist[i] = i; }

	// Set up who's next for each suitor to ask.
	// They each start out wanting to ask their top choice.
	vector<int> men_next(n, 0);

	// While there is an unattached suitor.
	while (worklist.size()) {
		// Get the current suitor
		auto suitor = worklist[worklist.size() - 1];
		worklist.pop_back();

		// Determine the next woman our suitor will ask.
		// This pattern of iterator + n*offset is to emulate our vector
		// being a matrix.
		auto suitor_preferences = begin(preferences) + (n*suitor);
		auto woman = suitor_preferences[men_next[suitor]];
		men_next[suitor]++;

		// if she's unattached, easy.
		if (assignment[woman] == -1) {
			assignment[woman] = suitor;
		}
		else {
			// otherwise, she chooses the man she prefers
			auto woman_pref = begin(woman_preferences) + (n*woman);
			// The woman ranks the suitor sooner (i.e., better) than
			// her current fiance.
			if (woman_pref[assignment[woman]] > woman_pref[suitor]) {
				worklist.push_back(assignment[woman]);
				assignment[woman] = suitor;
			}
			else {
				// this should never allocate memory!
				worklist.push_back(suitor);
			}
		}
	}
	return assignment;
}

// The second half of the preferences matrix is an n x n matrix W
// where W[i,j] is woman i's j-th choice of suitor. So W[i,0] is her
// most preferred suitor, W[i,1] is her next, and so on. This is
// just like the men's preference ranking as well.
//
// This function produces a W[i,m] = j matrix, where given a woman i
// and a suitor m, we get the rank woman i gives suitor m.
// This makes it much easier for a woman to see if she prefers m1 or m2:
// she prefers m1 exactly when W[i,m1] < W[i,m2] (e.g., she may prefer
// m1 as her 2nd choice, so W[i,m1] == 2, and m2 is her 5th, so W[i,m2] == 5.
vector<int> VoiceLeader::woman_ranking_map(const vector<int>& preferences, const int n) {
	vector<int> woman_ranking(n*n, -1);

	auto women_prefs_begin = begin(preferences) + (n*n);
	auto women_ranks_begin = begin(woman_ranking);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			// the j-th most preferred man by woman i:
			women_ranks_begin[women_prefs_begin[j]] = j;
		}
		women_prefs_begin += n;
		women_ranks_begin += n;
	}

	return woman_ranking;
}