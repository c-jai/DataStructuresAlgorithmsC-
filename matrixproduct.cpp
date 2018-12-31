// Name: Jai Vilas Chhatre
// Date of submission: 9/27/2018
// SJSU ID: 013752193


#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>

using namespace std;

int readMatrixFromFile(vector<vector<int>>& matrixVector, const string& fileName);
//Precondition: 2 dimensional empty vector to store matrix, name of the file to be read from
//Postcondition: 2 dimensional matrix populated in the vector 

void multiplyMatrices(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2, vector<vector<int>>& resultMatrix, const int rows_matrix1, const int columns_matrix2, const int columns_matrix1);
//Precondition: 2 matrices to be multiplied, empty result matrix for storing the result, number of rows and columns of matrix 1, number of columns of matrix 2 
//Postcondition: result of matrix product stored in result vector

void printResult(vector<vector<int>>& resultMatrix, const int rows_matrix1, const int columns_matrix2);
//Precondition: result matrix, number of rows of matrix 1, number of columns of matrix 2
//Postcondition: printed result (matrix multiplication)

int main(int argc, char** argv){

	vector<vector<int>> matrix1, matrix2;
	string filename1, filename2, argument;

	for(int i = 0; i < argc; i++){
		argument = argv[i];
		if(argument == "-m"){
			filename1 = argv[i+1];
		}

		if(argument == "-M"){
			filename2 = argv[i+1];
		}
	}
	
	int flagForFile1 = readMatrixFromFile(matrix1, filename1);
	int flagForFile2 = readMatrixFromFile(matrix2, filename2);

	if((flagForFile1 == 3) || (flagForFile2 == 3)){
		cerr << "Either or both the text files are empty, matrix multiplication cannot be performed" << endl;
		return -1;	
	}
	else if(flagForFile1 == 2 || flagForFile2 == 2){
		cerr << "Please ensure that file name(s) are correct" << endl;
		return -1;
	}
	else{
		int r1=0, c1=0, r2=0, c2=0; // number of rows and columns for matrix-1 and matrix-2	
		r1 = matrix1.size();
		c1 = matrix1[0].size(); //number of columns = size of inner vector(matrix)
		r2 = matrix2.size();
		c2 = matrix2[0].size();
		
		if (c1 != r2) {
			cerr << "Matrix multiplication cannot be performed, as the number of columns in matrix-1 are not equal to number of rows in matrix-2" << endl; 
			return -1;
		}

		vector<vector<int>> resultMatrix(r1,  std::vector<int>(c2)); //initialize result matrix with size=row1*column2
		multiplyMatrices(matrix1, matrix2, resultMatrix, r1, c2, c1);
		printResult(resultMatrix, r1, c2);			
	}
}

int readMatrixFromFile(vector<vector<int>>& matrixVector,const string& fileName){
		ifstream inStream;
		string elementStr, row;
		int flag;

		// handle error if file cannot be opened
		inStream.open(fileName); 
		if(inStream.fail()){
			cerr << "Cannot open file " << fileName << endl;
			flag = 2;
			return flag;
		}
	
		// check if opened file is empty
		if ( inStream.peek() == ifstream::traits_type::eof() )
		{
			cout << "Empty file encountered: " << fileName << endl;
			flag = 3;
			inStream.close();
			return flag; 
		}

		while(getline(inStream, row)) {
			vector<int> innerVector;// each entry in this vector is a row

			int element;
			stringstream rowStrStream(row);
			for(element = 0; rowStrStream >> element;){ // get every column for the row
				innerVector.push_back(element);
			}

		    // to skip blank lines
			if(!(innerVector.size() == 0)){
				matrixVector.push_back(innerVector);// this might be pushed for extra lines
			}	
		}

		inStream.close();
		flag = 4;
		return flag; // indicate that values have been read	
}

void multiplyMatrices(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2, vector<vector<int>>& resultMatrix, const int r1, const int c2, const int c1)
{
	for(int i = 0; i < r1; i++){	// select a row of matrix1
		for(int j = 0; j < c1; j++){	// select an element of that row
			for(int k = 0; k < c2; k++){	// select an element of matrix2 column-wise
				resultMatrix[i][k] = resultMatrix[i][k] + (matrix1[i][j]*matrix2[j][k]);
			}
		
		}
	}
}

void printResult(vector<vector<int>>& resultMatrix, const int r1, const int c2){
	for(int i = 0; i < r1; i++){
		for(int j =0; j < c2; j++){
			cout << resultMatrix[i][j] << "\t" ;
		}
		cout << "\n";
	}
}

