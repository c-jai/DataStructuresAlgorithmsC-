#include<vector>

class RandomNumberBucket{
private:
	const int DEFAULT_RANGE = 39;

	std::vector<int> bucket; 
	int bucketRange;
	std::vector<int> poppedBucket;

	void initialize();
public:
	RandomNumberBucket();

	RandomNumberBucket(int range);

	int pop();

	void refill();
	
	int size();
	
	bool empty();
	
	int popWithRefill();
};