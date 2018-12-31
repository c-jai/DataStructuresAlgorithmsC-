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