#include <vector>
#include <stdlib.h>

using namespace std;

class HillHike {
public:
	long long numPaths(int distance, int maxHeight, vector<int> landmarks)
	{
		// init hist.
		landmarkHist.resize(maxHeight + 1);
		for (auto &l: landmarks) 
			landmarkHist[l]++;
		if (landmarkHist[0] > 2)
			return 0;
		H = maxHeight;
		
		vector<int> currHist(maxHeight + 1, 0);
		
		return calcPaths(distance, 0, 0, currHist, false);		
	}
	
	long long calcPaths(int L, int base, int delta, vector<int> currHist, bool peaked)
	{
		if (!peaked && (2 * H - 2 * base - delta > L))
			return 0;
		if (abs(delta) > L)
			return 0;
			
		if (!peaked && base == H)
			peaked = true;
					
		long long num;
		if (L == 1) {
			num = 1;
			currHist[base]++;
			currHist[base+delta]++;				
			if (!checkHist(currHist, 0))
				num = 0;
		}
		else { // >= 2
			currHist[base]++;
			if (!checkHist(currHist, L - 1))
				num = 0;
				
			num = calcPaths(L-1, base+1, delta-1, currHist, peaked);
			num+= calcPaths(L-1, base, delta, currHist, peaked);
			if (base > 1)
				num += calcPaths(L-1, base-1, delta+1, currHist, peaked);			
		}
		
		return num;
	}
	
	bool checkHist(vector<int> &hist, int remainingL)
	{		
		// if it's not possible to contain all landmarks, return false.
		if (hist[0] > 2)
			return false;
		
		for (int i  = 0; i < H + 1; i++) {
			if (landmarkHist[i] - hist[i] > remainingL)
				return false;
		}
		
		return true;
	}
	
private:
	vector<int> landmarkHist;
	int H;
};

void main()
{
	int lm[] = {2, 2};
	vector<int> landmarks(lm, lm+2);
	HillHike hh;
	long long n = hh.numPaths(5, 2, landmarks);

}