#include<iostream>
#include<regex>
using namespace std;

class Regular {
public:
	regex preSp();
	regex postSp();
	regex header();
	regex namingConversion();
	regex mainFunc();
	regex fullCodereg();
	regex keyword();
	regex identifier();
	regex operators();
	regex sChar();
	regex constant();
	regex string();
};