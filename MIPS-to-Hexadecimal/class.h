//this is our personal .h file
//here we should define the classes
//put only function prototype here... save the function body for the function file

#include <iostream>
#include <string>
#include <fstream>
#include <sstream> //stringstream
#include <cstdlib> //need this to use exit(1)
#include <string> // need this to access string library
#include <iomanip> // need this to use setw and setfill
using namespace std;

int one(string first);//return 1 or 0. 1=label, 0=instruction
string convertBinary(string decimal, int bits);
string convertBinaryDec(int decimal, int bits);
char hexify(string word);


/*Symbol class is instantiated for each label the program encounters*/
class symbol{
	
	private:
	symbol *next;
	string labelName;//ie "LOOP"
	///string labelAdress;//ie "0x00000004"
	int _count;
	
	public:
	void setLabel(string makeMeLabel, string hexLine, int linecount);
	void setNext(symbol* set){next = set;return;}
	string getLabel(){return labelName;}
	symbol* getNext(){return next;}

};


/*These are the arguments read in on the current line from our file.*/
struct MIPS_arguments{
	string arg1;
	string arg2;
	string arg3;
	string arg4;
	string arg5;
};
class line{
	private:
	line* next;
	int myLine;
	string given; //given is the original string that was passed to this class's primary function add()
	string opcode;
	string rd;
	string rt;
	string rs;
	string shamt;
	string funct;
	string immediate;
	string address;
	string label;
	string final;


	public:
//	void operator=(string cmd);
	int memoryAddress(string arg);
	void setNext(line* set){next = set; return;}; //call it with line.setNext(new line);  then line = line->getNext();
	void setLine(int i){myLine = i; return;};

	/*
	Here i've placed extra tab's to make the functions look "nested" to help the design of function calls.
	registers() should be called when needed and have its return value set equal to a member of the object's rd, rs or rt strings
	*/

	 //takes in the address of the new string of assembly and expects a finished line class address.
	line* add(string* line);
	void opCode(string arg, MIPS_arguments* args);
	void typeR(string line, MIPS_arguments* args); //takes in the original line and a substr with the assembly function
	void addressBasicR(MIPS_arguments* args); //understands that it should be looking for rs, rt, rd
	/* removed asterisk below because it didn't match what was in functions.cpp */			
	string registers(string reg); //this function is here to take in a tiny string and spit out the corresponding string. that way the calling environment can decide where to put it.
	
	/*adding function to tell binary value of funct, only to be called in R-Type*/
	string functions(string funct);

	void branch(MIPS_arguments* args); //for beq and bne
	void addressJR(MIPS_arguments* args); // because JR ONLY needs the RS
	void addressShift(MIPS_arguments* args); // for sll srl
	
	void typeI(string line, MIPS_arguments* args); //takes in the original line and a substr with the assembly function
	void addressBasicI(MIPS_arguments* args); // knows to look for rt, rs and the rest is a constant
	void addressJI(MIPS_arguments* args); //knows to look for a label(address) and rs, rt.
	void addressStore(MIPS_arguments* args); //the function for sw.
	
	void typeJ(string line, MIPS_arguments* args); //tpyeJ should just be the two simple J and JAL

	void hexLine();
	string* print();
	line* getNext(){return next;}
	string getFinal(){return final;}
	void convertFinalHex(); //if you call this function, it will convert final to hex.
};
