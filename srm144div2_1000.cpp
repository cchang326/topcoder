#include <array>
#include <vector>
using namespace std;

typedef struct _Junction Junction;

struct _Junction {
	int junction;
	int lengthToParent;
	vector <Junction> children;
};

class PowerOutage
{
public:
	int estimateTimeOut(vector<int> fromJunction, vector<int> toJunction, vector<int> ductLength)
	{
		buildTree(fromJunction, toJunction, ductLength);
		
		int backTrackCost = -1, traverseCost = -1;
		estimateRecursive(&m_root, &backTrackCost, &traverseCost);
		return traverseCost;
	}
	
private:
	void estimateRecursive(Junction *pRoot, int *bcost, int *tcost)
	{
		*bcost = 0;
		*tcost = 0;
		int maxBacktrackCost = 0;
		// find the children with most backtrack cost and traverse it.
		for (int i = 0; i < pRoot->children.size(); i++) {
			Junction *pChild = &pRoot->children[i];
			int backCost = 0, traverseCost = 0;
			if (pChild->children.size() > 0) {
				estimateRecursive(pChild, &backCost, &traverseCost);
			}
			backCost += pChild->lengthToParent * 2;
			traverseCost += pChild->lengthToParent;
			if (backCost - traverseCost > maxBacktrackCost) {
				maxBacktrackCost = backCost - traverseCost;				
			}
			*bcost += backCost;
		}
		*tcost = *bcost - maxBacktrackCost;
	}

	void buildTree(vector<int> fromJunction, vector<int> toJunction, vector<int> ductLength)
	{
		m_root.junction = 0;
		m_root.lengthToParent = 0;
		buildTreeRecursive(&m_root, fromJunction, toJunction, ductLength);
	}
	
	void buildTreeRecursive(Junction *pRoot, vector<int> fromJunction, vector<int> toJunction, vector<int> ductLength)
	{
		if (fromJunction.size() == 0)
			return;
		// add children
		vector<int> junctionsProcessed;
		for (int i = 0; i < fromJunction.size(); i++) {
			if (pRoot->junction == fromJunction[i]) {
				Junction child;
				child.junction = toJunction[i];
				child.lengthToParent = ductLength[i];
				pRoot->children.push_back(child);
				junctionsProcessed.push_back(i);
			}
			if (pRoot->junction == toJunction[i]) {
				Junction child;
				child.junction = fromJunction[i];
				child.lengthToParent = ductLength[i];
				pRoot->children.push_back(child);
				junctionsProcessed.push_back(i);
			}			
		}
		// erase processed ducts.
		for (int i = junctionsProcessed.size() - 1; i >= 0 ; i--) {
			fromJunction.erase(fromJunction.begin() + junctionsProcessed[i]);
			toJunction.erase(toJunction.begin() + junctionsProcessed[i]);
			ductLength.erase(ductLength.begin() + junctionsProcessed[i]);
		}
		// build tree for each child.
		for (int i = 0; i < pRoot->children.size(); i++) {
			buildTreeRecursive(&pRoot->children[i], fromJunction, toJunction, ductLength);
		}
	}
	
private:
	Junction m_root;
};

void main()
{
	/*{0,0,0,1,4,4,6,7,7,7,20}
{1,3,4,2,5,6,7,20,9,10,31}
{10,10,100,10,5,1,1,100,1,1,5}*/
	static const int from[] = {0,0,0,1,4,4,6,7,7,7,20};
	static const int to[] = {1,3,4,2,5,6,7,20,9,10,31};
	static const int length[] = {10,10,100,10,5,1,1,100,1,1,5};
	vector<int> fromJunction(from, from + sizeof(from) / sizeof(from[0]) );
	vector<int> toJunction(to, to + sizeof(to) / sizeof(to[0]) );
	vector<int> ductLength(length, length + sizeof(length) / sizeof(length[0]) );

	PowerOutage po;
	int cost = po.estimateTimeOut(fromJunction, toJunction, ductLength);

	printf("%d", cost); // 281
	
}