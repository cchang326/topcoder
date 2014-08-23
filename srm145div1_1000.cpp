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
		D = distance;
		
		vector<int> currHist(maxHeight + 1, 0);
		vector<int> route(D+1, 0);
		
		return calcPaths(distance, 0, 0, currHist, false, route);		
	}
	
	long long calcPaths(int L, int base, int delta, vector<int> currHist, bool peaked, vector<int> route)
	{
		if (!peaked && (2 * H - 2 * base - delta > L))
			return 0;
		if (abs(delta) > L)
			return 0;
			
		if (!peaked && base == H)
			peaked = true;
					
		long long num;
		if (L == 1) {
			if (delta != -1 && base != 1)
				num = 0; // shouldn't happen!
			else
				num = 1;
			currHist[base]++;
			currHist[base+delta]++;
			if (!checkHist(currHist, 0))
				num = 0;
			if (num>0) {
				route[D - 1] = base;
				route[D] = base+delta;
				for (auto &r: route)
					printf("%d ", r);
				printf("        Hist: ");
				for (auto &h: currHist)
					printf("%d ", h);
				printf("\n");
			}
		}
		else { // >= 2
			num = 0;
			currHist[base]++;
			route[D-L] = base;
			if (checkHist(currHist, L - 1)) {
				if (base < H)
					num = calcPaths(L-1, base+1, delta-1, currHist, peaked, route);
				if (base > 0)
					num+= calcPaths(L-1, base, delta, currHist, peaked, route);
				if (base > 1)
					num += calcPaths(L-1, base-1, delta+1, currHist, peaked, route);	
			}	
		}
		
		return num;
	}
	
	bool checkHist(vector<int> &hist, int remainingL)
	{	
		// todo: landmarks need to appear in order!
		for (int i  = 0; i < H + 1; i++) {
			if (landmarkHist[i] - hist[i] > remainingL)
				return false;
		}
		
		if (remainingL == 0 && hist[H] == 0)
			return false;
		
		return true;
	}
	
private:
	vector<int> landmarkHist;
	int H;
	int D;
};

void main()
{
	int lm[] = {2, 2, 3, 1};
	vector<int> landmarks(lm, lm+2);
	HillHike hh;
	long long n = hh.numPaths(8, 3, landmarks);

}