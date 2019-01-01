# Data Structures & Algorithms C++
contains assignments as a part of an academic course

1. Matrix Multiplication: program that multiplies two integer matrices given in two files whose names will be passed via command line arguments, program must print out the output matrix to STDOUT in the same format as the matrices in files.

2. Random Number Bucket: The class RandomNumberBucket object must be initialized with a bucket containing numbers from 1 to 39 if the default constructor is called. Non default constructor takes an integer N as argument and that means that the bucket will contain then numbers 1-N. The class must implement a pop() method that will return a number chosen at random from the bucket. Once the number is returned in pop it must be extracted from the bucket. Once the bucket is drained of all numbers pop should return -1. The class must support the class method refill that will replenish the numbers from 1-N when called. You class must never reach a state where a number is replicated in the bucket. Also implement method popWithRefill() which will check if the bucket is empty and refill before returning (i.e. a pop method that never fails). Also implement the empty() method that returns true if the bucket is empty and needs to be refilled. All the numbers in the bucket should have equal probability of being returned.

3. Bitset in C++: Implement a RandomNumberSet class that will store 5 numbers in the range of 1 to N and number N may be passed at construction time. If default constructor is used N = 39. The class must store using a bitset or multiple bitsets for efficient implementation of some of the required methods. The class must support the following methods:
 -Default Constructor and constructor with range argument.
 -void reset(); // clears all the numbers stored
 -bool set(int i); // If number i is not in the set, store it by setting the corresponding bit and return true, else return false
 -int size(); // returns numbers of numbers stored. 
 -Overload operator << so that the numbers can be printed out aligned to the right and in 3 spaces. Overload operator - so the difference between two bitsets can be determined in O(1)

4. Orthogonal Numbers: Using the classes defined in earlier projects create a new class called OrthogonalNumbers which has the following public methods:
 -Constructor that takes as argument the range or random numbers (1-N), the number of numbers to set in each RandomNumberSet generated, and the minimum distance between any two numbers to be generated.
 -OrthogonalNumbers(int n, int c, int d) { your contructing code; }
 -Default constructor must have 39 (n), 5 (c), 4 (d) as arguments.
 -bool generate(int numbersOfRandomNumberSetsToGenerate);
 -This function will generate numbersOfRandomNumberSetsToGenerate sets of random number such that all numbers generated are at a distance of d.
 -bool reset(); //clears all random numbers generated if any
 -Must implement the << output that will print all the numbers one set per line.
