#include "RandomNumberBucket.h"

#include<iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;

void RandomNumberBucket::initialize(){
	for(int i = 0; i < bucketRange; i++){
		bucket.push_back(i+1);
	}
}

RandomNumberBucket::RandomNumberBucket(){
	std::srand(std::time(0)); 
	bucketRange = DEFAULT_RANGE;
	initialize();
}

RandomNumberBucket::RandomNumberBucket(int range){
	std::srand(std::time(0)); 
	bucketRange = range;
	initialize();
}


int RandomNumberBucket::pop(){
	if(bucket.size() == 0){ //if bucket is empty
		return (-1);
	}
	int random = std::rand();
	int randomIndex = random % bucket.size();

	int poppedValue = bucket[randomIndex];
	bucket.erase(bucket.begin() + randomIndex);
	poppedBucket.push_back(poppedValue);
	return poppedValue;
}

int RandomNumberBucket::popWithRefill(){
	
	if(bucket.size() == 0){ //if bucket is empty
		RandomNumberBucket::refill();
	}

	return RandomNumberBucket::pop();
}

void RandomNumberBucket::refill(){

	bucket.insert(end(bucket), begin(poppedBucket), end(poppedBucket));//insert from poppedBucket

	int poppedBucketSize = poppedBucket.size();//flush poppedBucket
		for(int i=0; i < poppedBucketSize; i++){
			poppedBucket.erase(poppedBucket.begin());
		}
}

int RandomNumberBucket::size(){
	return bucket.size();
}

bool RandomNumberBucket::empty(){
	return (bucket.size() == 0);
}

