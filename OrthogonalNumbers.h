#include<vector>
#include<bitset>

using namespace std;

class RandomNumberSet{

private:
	int range;
	bitset<301> mBitSet;
public:

	RandomNumberSet();

	RandomNumberSet(int userDefinedRange);

	void reset();

	bool set(int i);

	int size();

	int operator-(const RandomNumberSet& rhsBitSet);

	friend ostream& operator<<(ostream& os, const RandomNumberSet& bitSet);

};

class OrthogonalNumbers:public RandomNumberSet{
private:
	int randomNumberRange{0}; //todo: discuss wid someone
	int count{0};
	int distance{0};
	vector<RandomNumberSet> orthogonalSets;
public:
	OrthogonalNumbers();

	OrthogonalNumbers(int n, int c, int d);

	bool generate(int numberOfSets);

	bool reset();

	friend ostream& operator<<(ostream& os, const OrthogonalNumbers& orthogonalNumberObject);

};