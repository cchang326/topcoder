#include <vector>
#include <string>
using namespace std;

class BinaryCode
{
public:
	vector<string> decode(string message)
	{
		vector <string> ret;
		size_t len = message.size();
		if (len == 0) {
			ret.push_back("NONE");
			ret.push_back("NONE");
		}
		else {
			for (int i = 0; i < 2; i++) {			
				P.resize(len);

				setP(0, i);				
				int p2 = 0;
				int p1 = i;
				for (size_t j = 1; j < len; j++) {
					int p = ctoi(message[j - 1]) - p1 - p2;
					if (p < 0 || p > 1) {
						P = "NONE";
						break;
					}
					setP(j, p);
					p2 = p1;
					p1 = p;					
				}
				if (p1 + p2 != ctoi(message[len - 1])) {
					P = "NONE";
				}
				
				ret.push_back(P);
				P.clear();
			}
		}
		
		return ret;
	}
	
	inline int ctoi(char c)
	{
		return c - '0';
	}
	
	inline void setP(int index, int value)
	{	
		P[index] = value + '0';
	}
	
private:
	string P;
};

void main()
{
	BinaryCode bc;
	vector<string> str = bc.decode("123210122");
}