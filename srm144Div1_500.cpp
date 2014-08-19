// 500 point
// sorted   unique    answer
//  F		F         C^B								<=== permutation with repetition
//  F		T         C!/(C-B)!							<=== permutation without repetition
//  T		F		  Combinations(C+B-1, B)			<=== combination with repetition (hardest)
//  T		T		  Combinations(C,B) = C!/(C-B)!/B!  <=== combination without repetition

#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;

typedef struct {
	string name;
	int choices;
	int blanks;
	bool sorted;
	bool unique;
	unsigned long long possibilities;
} Rule;

bool compareRule(Rule a, Rule b)
{
	if (a.possibilities != b.possibilities) {
		return a.possibilities < b.possibilities;
	}
	else {
		return a.name.compare(b.name) < 0;
	}
}

class Lottery
{
public:
	vector <string> sortByOdds(vector <string> rules)
	{
		vector <Rule> rs = parseTicket(rules);
		for (int i = 0; i < rs.size(); i++) {
			calcPossibilities(rs[i]);
		}
		sort(rs.begin(), rs.begin()+rs.size(), compareRule);
		vector <string> names;
		for (int i = 0; i < rs.size(); i++) {
			names.push_back(rs[i].name);
		}
		return names;
	}
	
	vector <Rule> parseTicket(vector<string> rules)
	{
		vector <Rule> rs;
		for (int i = 0; i < rules.size(); i++) {
			char s, u;
			Rule r;
			size_t found = rules[i].find(':');
			r.name = rules[i].substr(0, found);
			sscanf (rules[i].substr(found+1).c_str(), "%d %d %c %c", &r.choices, &r.blanks, &s, &u);
			r.sorted = s == 'T';
			r.unique = u == 'T';
			rs.push_back(r);
		}
		return rs;
	}
	
	void calcPossibilities(Rule &rule)
	{
		unsigned long long p = 0;
		if (rule.unique == false) {
			if (rule.sorted == false) {
			    p = rule.choices;
			    for (int i = 1; i < rule.blanks; i++) {
			    	p *= rule.choices;
			    }
			}
			else {
				p = getPoss(rule.choices, rule.blanks);
			}
		}		
		else {
			p = 1;
			for (int i = 0; i < rule.blanks; i++) {
				p *= (rule.choices - i);
			}
			
		    if (rule.sorted) {
				p /= getFactorial(rule.blanks);
			}
		}
		rule.possibilities = p;
	}
	
	unsigned long long getPoss(int c, int b)
	{
		if (c == 1)
			return 1;
		if (b == 1)
			return c;
			
		unsigned long long p = 0;
		vector<unsigned long long> table;
		table.resize(c);
		for (int i = 0; i < c; i++)
			table[i] = i + 1;
		for (int i = 2; i < b; i++) {
			for (int j = 1; j < c; j++) {
				table[j] = table[j - 1] + table[j];
			}
		}
		for (int j = 0; j < c; j++)
			p += table[j];
			
		return p;
	}
	
	unsigned long long getFactorial(int b)
	{
		unsigned long long p = b;
		for (int i = 2; i < b; i++) {
			p *= i;
		}
		return p;
	}
};



//void main()
//{
//	static const char *arr[] = {"INDIGO: 93 8 T F",
//		"ORANGE: 29 8 F T",
//		"VIOLET: 76 6 F F",
//		"BLUE: 100 8 T T",
//		"RED: 99 8 T T",
//		"GREEN: 78 6 F T",
//		"YELLOW: 75 6 F F"};
//	vector<string> rules;
//	for (int i = 0; i < _countof(arr); i++) {
//		rules.push_back(arr[i]);
//	}
//
//	Lottery l;
//	l.sortByOdds(rules);
//}