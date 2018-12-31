#include "OrthogonalNumbers.h"

#include<iostream>
#include<vector>
#include <ctime>
#include <chrono>
#include <thread>
#include<bitset>
#include <iomanip>

using namespace std;

RandomNumberSet::RandomNumberSet(){
	range = 300; // todo: change this value
}

RandomNumberSet::RandomNumberSet(int userDefinedRange){

	if(userDefinedRange > 300){ 
		cerr << "The maximum range you can enter is 300. Please run the program again with correct values" << endl;
		exit(1);
	}
	range = userDefinedRange;
}

void RandomNumberSet::reset(){
	mBitSet.reset();
}

bool RandomNumberSet::set(int i){
	


	/*if((i < 1) || (i > range)){
		cerr << "Number " << i << " cannot be set. You can set numbers only between 1 to " << range << endl; 
		return false; //todo: check if correct
	}*/


	if(mBitSet[i]){
		return false;
	}
	else{
		mBitSet.set(i);
		
		return true;
	}
}

int RandomNumberSet::size(){
	return mBitSet.count();
}

int RandomNumberSet::operator-(const RandomNumberSet& rhsBitSet){

	int difference{0};

	int bitset1_size = (this->mBitSet).count();
	int bitset2_size = (rhsBitSet.mBitSet).count();


	bitset<301> commonNumbers = (this->mBitSet)&(rhsBitSet.mBitSet);

	if(bitset1_size > bitset2_size){
		difference = bitset1_size - commonNumbers.count();
	}

	else if(bitset2_size > bitset1_size){
		difference = bitset2_size - commonNumbers.count();
	}

	else{
		difference = bitset2_size - commonNumbers.count();
	}

	return difference;
}


ostream& operator<<(ostream& os, const RandomNumberSet& bitSet)  
{  
    for(int i = 0; i <= bitSet.range; i++){
		if(bitSet.mBitSet[i]){
			cout << right << setw(3) << i;	
		}
	}
	cout << endl;
    return os;  
} 

//default constructor
OrthogonalNumbers::OrthogonalNumbers(){
	std::srand(std::time(0)); 

	randomNumberRange = 39;
	count = 5;
	distance = 4;
}


OrthogonalNumbers::OrthogonalNumbers(int n, int c, int d){

	if(n < 1 || n >300){
		cerr << "The range for generating random numbers is 1 to 300. Please enter a number between 1 and 300" << endl;
		exit(1);
	}

	if(d > c){
		cerr << "The expected distance cannot be greater than the number of random numbers present in a set. Enter appropriate values" << endl;
		exit(1);
	}
	if(c < 1){
		cerr << "value for number of items in a set should be at least 1" << endl;
		exit(1);
	}

	//n, c > 0
	std::srand(std::time(0)); 
	randomNumberRange = n;
	count = c;
	distance = d;
}

bool OrthogonalNumbers::generate(int numberOfSets){
	if(numberOfSets < 1){
		return false;
	}
	bitset<301> entireRange;
	int iterations{0};
	int setDifference{0};
	int sentinel;
	int startSize = orthogonalSets.size(); // to handle consecutive calls to generate()

	for(int i = startSize; i < (numberOfSets + startSize); i++){
		if(iterations > 1000000){
			cerr << "Desired number of sets cannot be generated in finite time, please try other combinations" << endl;
			return false;
		}
		++iterations;
		//cout << "iterations: " << iterations << endl;
		sentinel = 0;
		RandomNumberSet innerSet;
		// generate and create a set of random numbers 
		for(int j = 0; j < count; j++){
			int random = std::rand();
			int randomNumber = (random % randomNumberRange)+1;
			if(!innerSet.set(randomNumber)){
				//to avoid setting the same number twice
				--j;
			}
		}

		if(i > 0){
			for(int k = 1; k <= i; k++){ // calculate distance of newly generated set from the earlier ones
				setDifference = orthogonalSets[i-k] - innerSet;
				if(setDifference >= distance){
					++sentinel;
				}
			}

			if(sentinel == i){
				orthogonalSets.push_back(innerSet); // push back the set if distance is as expected
			}
			else{
				//if distance is not as expected, then regenerate the set
				--i;
			}
		}
		else if(i == 0){
				//++sentinel;
				orthogonalSets.push_back(innerSet);

		}
		
	}
	return true;
}

ostream& operator<<(ostream& os, const OrthogonalNumbers& orthogonalNumberObject){
		for(int i = 0; i < orthogonalNumberObject.orthogonalSets.size(); i++){
			cout << orthogonalNumberObject.orthogonalSets[i] ;
		}
		return os;
}

bool OrthogonalNumbers::reset(){
	if(orthogonalSets.size() != 0){
		orthogonalSets.clear();
		return true;
	}
	return false;
}
