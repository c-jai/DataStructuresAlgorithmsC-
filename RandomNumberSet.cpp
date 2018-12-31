#include "RandomNumberSet.h"

#include<iostream>
#include<bitset>
#include <iomanip>

using namespace std;


RandomNumberSet::RandomNumberSet(){
	range = 39; // todo: change this value
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
	if(size() == 5){
		cerr << "You can set maximum 5 numbers only; so this number cannot be set" << endl;
		return false;//todo: check if correct
	}
	
	if((i < 1) || (i > range)){
		cerr << "Number " << i << " cannot be set. You can set numbers only between 1 to " << range << endl; 
		return false; //todo: check if correct
	}

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