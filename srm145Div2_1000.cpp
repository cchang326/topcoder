#include <vector>
#include <string>
using namespace std;

class VendingMachine {
public:
	int motorUse(vector <string> prices, vector <string> purchases)
	{
		// init.
		columnExp = 0;
		motorRun = 0; //inited
		currColumn = 0; //inited
		numColumns = 0; //inited
		if (prices.size() == 0)
			return 0;
		machine.resize(prices.size());
		for (int shelf = 0; shelf < prices.size(); shelf++) {
			vector <string> tokens = split(prices[shelf], ' ');
			machine[shelf].resize(tokens.size());
			columns.resize(tokens.size());
			for (int col = 0; col < tokens.size(); col++) {
				machine[shelf][col] = atoi(tokens[col].c_str());
				columns[col] += machine[shelf][col];
			}
		}
		numColumns = machine[0].size();
		findMostExpColumn();
						
		rotate(columnExp);
		
		// for each purchase, call purchase().
		int prevTime = 0;
		for (int i = 0; i < purchases.size(); i++) {
			size_t found = purchases[i].find(',');
			int shelf =atoi(purchases[i].substr(0, found).c_str());
			size_t found2 = purchases[i].find(':');
			int column = atoi(purchases[i].substr(found + 1, found2 - found - 1).c_str());
			int time = atoi(purchases[i].substr(found2 + 1).c_str());
			if (time - prevTime >= 5)
				rotate(columnExp);
			if (!purchase(shelf, column))
				return -1;
			prevTime = time;
		}
		
		rotate(columnExp);
		
		return motorRun;
	}
	
private:
	bool purchase(int shelf, int column)
	{
		if (machine[shelf][column] == 0)
			return false;

		rotate(column);
		
		columns[column] -= machine[shelf][column];
		if (column == columnExp)
			findMostExpColumn();
		
		machine[shelf][column] = 0;
		return true; 
	}
	
	void rotate(int finish)
	{
		int d = finish - currColumn;
		if (d < 0)
			d += numColumns;
		if (d > numColumns - d)
			d = numColumns - d;
		motorRun += d;
		currColumn = finish;
	}
	void findMostExpColumn()
	{
	     // scan through columns and set columnExp.
	     for (int col = numColumns - 1; col >= 0; col--) {
	     	if (columns[col] >= columns[columnExp])
	     		columnExp = col;
	     }
	}
	vector<string> split(string str, char c)
	{
		vector<string> tokens;
		size_t start = 0;
		while (start < str.length()) {
			size_t end = str.find(c,start);
			if (end == string::npos)
				break;
			tokens.push_back(str.substr(start,end - start));
			start = end + 1;
		}
		if (start < str.length())
			tokens.push_back(str.substr(start));
		return tokens;
	}
			
private:
	vector <vector<int>> machine;
	vector <int> columns;
	int numColumns;
	int currColumn;
	int columnExp; // most expensive column
	int motorRun;
};

//void main()
//{
//	static const char *prices_str[] = {"100 100 100"};
//	static const char *purchases_str[] = {"0,0:0", "0,2:5", "0,1:10"};
//	vector<string> prices, purchases;
//	for (int i = 0; i < _countof(prices_str); i++) {
//		prices.push_back(prices_str[i]);
//	}
//	for (int i = 0; i < _countof(purchases_str); i++) {
//		purchases.push_back(purchases_str[i]);
//	}
//
//	VendingMachine vm;
//	vm.motorUse(prices, purchases);
//}