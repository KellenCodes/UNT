//functions file
//define functions in this file


//string library
#include "class.h" //our own .h file

//using namespace std;

/*
Function: one
parameters: a string that is the first word in the current getline
returns: 1 for label, 0 for instruction
decription: checks to see if there is a colon next to the word. if there is, it's a label, otherwise it's an instruction
	should also save the label in the symbol table, somehow
*/
int one(string first)
{
	int length;
	length=first.size();

	if(first.at(length-1) == ':')
	{
		return 1; //label
	}
	else
	{
		return 0; //instruction
	}
}

/*
Function: symbol::setLabel
Parameters: string: label's name, string: Hex address of the label, int: the decimal line count
desciption: This function builds one line of the symbol table
*/
void symbol::setLabel(string makeMeLabel, string hexLine, int linecount)
{
	labelName = makeMeLabel + "\t\t" + hexLine;
	_count = linecount; //this will remember.
	return;
}

/*function: line::opCode
Parameters: MIPS argument struct and the first mips argument.
// opCode is a function inthe class line, it identifies the first 5 bits of binary for the current line of assembly
// opCode expects the MIPS function and sets the opcode equal accordingly.
*/
void line::opCode(string arg, MIPS_arguments* args)
{
	if(arg == "add" || arg == "addu" || arg == "and" || arg == "jr" || arg == "nor" || arg == "or" || arg == "slt" || arg == "sltu" || arg == "sll" || arg == "srl" || arg == "sub" || arg == "subu")
	{
		typeR(arg,args);
	}
	else if(arg == "addi" || arg == "addiu" || arg == "andi" || arg == "beq" || arg == "bne" || arg == "lw" || arg =="ori" || arg == "slti" || arg == "sltiu" || arg == "sw")
		typeI(arg,args);
	else if(arg == "j" || arg == "jal")
		typeJ(arg,args);
	else
		cout << "error, do not recognize command" + arg << endl;
	
	return;
}


/*
funciton: line::typeR
parameters: Mips primary argument, MIPS argument struct
Description: The function will check the main argument and either immediately set some registers, or it will pass
control to a different function.
*/
void line::typeR(string arg, MIPS_arguments* args)
{
	opcode = "000000"; // the opcode for every rType is six zeroes.
	
	if(args->arg1 == "jr")
	{
		rs = registers(args->arg2);
		rt = "00000";
		rd = "00000";
		shamt = "00000";
		funct = functions(args->arg1);
		
		
	}
	else if(args->arg1 == "sll" || args->arg1 == "srl")
	{
		rd = registers(args->arg2);
		rs = "00000";
		rt = registers(args->arg3);
		shamt = convertBinary(args->arg4, 5); //CONVERT INTO 5 BIT BINARY
		funct = functions(args->arg1);
		
	}
	else
	{
		addressBasicR(args); //this will parse out some registers and set the result of register() = to the right reg
	
		
	}
	final = opcode + rs + rt + rd + shamt + funct;
	return;
}

/*
function: typeI
parameters
description: Function will pass control to a more spceific function, or call
immediate and register functions within its own if/else statemnt
*/
void line::typeI(string arg, MIPS_arguments* args)
{
	if     (arg == "addi" )	
	{
		opcode="001000";
		addressBasicI(args); //this function should go get all the registers
		
	}//08 = 0000 1000 doing everything in line easier to read
	else if(arg == "addiu")	
	{
		opcode="001001";
		//cout << opcode <<endl;//this was for debugging
		addressBasicI(args); //this function should go get all the registers
		
	}//09 = 0000 1001
	else if(arg == "andi" )	
	{
		opcode="001100";
		addressBasicI(args); //this function should go get all the registers
		
	}//0c = 0000 1100
	else if(arg == "beq"  )	
	{
		opcode="000100";
		branch(args);
	}//04 = 0000 0100
	else if(arg == "bne"  )	
	{
		opcode="000101";
		branch(args);
		
	}//05 = 0000 0101
	else if(arg == "lw"   )	
	{
		opcode="100011";
		rs = registers(args->arg4);
		rt = registers(args->arg2);
		immediate = convertBinary(args->arg3, 16); // NEEDS TO BE CONVERTED INTO 16 BIT BINARY FIRST
		
	}//23 = 0010 0011
	else if(arg == "ori"  )	
	{
		opcode="001101";
		addressBasicI(args); //this function should go get all the registers
		
	}//0d = 0000 1101
	else if(arg == "slti" )	
	{
		opcode="001010";
		addressBasicI(args); //this function should go get all the registers
		
	}//0a = 0000 1010
	else if(arg == "sltiu")	
	{
		opcode="001011";
		addressBasicI(args); //this function should go get all the registers
		
	}//0b = 0000 1011
	else if(arg == "sw"   )	
	{
		opcode="101011";
		rs = registers(args->arg4);
		rt = registers(args->arg2);
		immediate = convertBinary(args->arg3, 16); // NEEDS TO BE CONVERTED INTO 16 BIT BINARY FIRST
		
	}//2b = 0010 1011
	else
		cout << "error function not supported" + arg << endl;
	
	final = opcode + rs + rt + immediate;
	return;
}

/*
function: typeJ
paramenters: primary arg and the MIPS arg struct
description: Will set opcodes for jump-type functions.
will call memoryAddress for their proper jumps.

*/
void line::typeJ(string arg, MIPS_arguments* args)
{
	int i;
	if     (arg == "j")	
	{
		opcode="000010";
		
	}//02 = 0000 0010
	else if(arg == "jal")	
	{
		opcode="000011";
		
	}//03 = 0000 0011
	i = memoryAddress(args->arg2);
	address = convertBinaryDec(i, 26);
	final = opcode + address;
	//cout << final << endl;
	return;
}
/*
Name: addressBasicR
parameters: mips argument struct.
returns: nothing
description: parses through line to call registers function to set registers to binary values
*/
void line::addressBasicR(MIPS_arguments* args)
{
	rd = registers(args->arg2);
	rs = registers(args->arg3);
	rt = registers(args->arg4);
	shamt = "00000";
	funct = functions(args->arg1);
	final = opcode + rs + rt + rd + shamt + funct;
	return;
}
/*
Name: addressBasicI
parameters: mips argument struct.
returns: nothing
description: parses through line to call registers function to set registers to binary values
*/
void line::addressBasicI(MIPS_arguments* args)
{
	rt = registers(args->arg2);
	//cout << rt <<endl;
	rs = registers(args->arg3);
	//cout << rs <<endl;
	immediate = convertBinary(args->arg4, 16); //NEED TO CONVERT THIS INTO 16 BIT BINARY FIRST

	return;
}

/*
function: line::registers
parameters: a single string representing the register as it appears in MIPS

Will take in the MIPS register and return a binary string value equal to the register's basic value.
*/
string line::registers(string reg)
{
	if		(reg == "$zero"){reg="00000";}//00 = 0000 0000
	else if	(reg == "$at")	{reg="00001";}//01 = 0000 0001
	else if (reg == "$v0")	{reg="00010";}//02 = 0000 0010
	else if (reg == "$v1")	{reg="00011";}//03 = 0000 0011
	else if	(reg == "$a0")	{reg="00100";}//04 = 0000 0100
	else if (reg == "$a1")	{reg="00101";}//05 = 0000 0101
	else if (reg == "$a2")	{reg="00110";}//06 = 0000 0110
	else if (reg == "$a3")	{reg="00111";}//07 = 0000 0111
	else if (reg == "$t0")  {reg="01000";}//08 = 0000 1000
	else if (reg == "$t1")  {reg="01001";}//09 = 0000 1001
	else if (reg == "$t2")	{reg="01010";}//0a = 0000 1010
	else if (reg == "$t3")  {reg="01011";}//0b = 0000 1011
	else if (reg == "$t4")  {reg="01100";}//0c = 0000 1100
	else if (reg == "$t5")  {reg="01101";}//0d = 0000 1101
	else if (reg == "$t6")  {reg="01110";}//0e = 0000 1110
	else if (reg == "$t7")  {reg="01111";}//0f = 0000 1111
	else if (reg == "$s0")  {reg="10000";}//10 = 0001 0000
	else if (reg == "$s1")  {reg="10001";}//11 = 0001 0001
	else if (reg == "$s2")  {reg="10010";}//12 = 0001 0010
	else if (reg == "$s3")  {reg="10011";}//13 = 0001 0011
	else if (reg == "$s4")  {reg="10100";}//14 = 0001 0100
	else if (reg == "$s5")  {reg="10101";}//15 = 0001 0101
	else if (reg == "$s6")  {reg="10110";}//16 = 0001 0110
	else if (reg == "$s7")  {reg="10111";}//17 = 0001 0111
	else if (reg == "$t8")  {reg="11000";}//18 = 0001 1000
	else if (reg == "$t9")  {reg="11001";}//19 = 0001 1001
	else if (reg == "$k0")  {reg="11010";}//1a = 0001 1010
	else if (reg == "$k1")  {reg="11011";}//1b = 0001 1011
	else if (reg == "$gp")  {reg="11100";}//1c = 0001 1100
	else if (reg == "$sp")  {reg="11101";}//1d = 0001 1101
	else if (reg == "$fp")  {reg="11110";}//1e = 0001 1110
	else if (reg == "$ra")  {reg="11111";}//1f = 0001 1111
	else
		cout << "register does not exist " << reg << endl;
	return reg;
}

/*
name: functions
parameters: the name of the function being used
returns: a string that is the binary value for that function
description: sets the funct value for R type
*/
string line::functions(string funct)
{
	if		(funct == "add")  {funct="100000";}
	else if (funct == "addu") {funct="100001";}
	else if (funct == "and")  {funct="100100";}
	else if (funct == "jr")   {funct="001000";}
	else if (funct == "nor")  {funct="100111";}
	else if (funct == "or")   {funct="100101";}
	else if (funct == "slt")  {funct="101010";}
	else if (funct == "sltu") {funct="101011";}
	else if (funct == "sll")  {funct="000000";}
	else if (funct == "srl")  {funct="000010";}
	else if (funct == "sub")  {funct="100010";}
	else if (funct == "subu") {funct="100011";}
	else
		cout << "not r-type, doesn't have a funct value " << funct << endl;

	return funct;
}

/*
name: branch
parameters: one getline that has all the arguments for that line
returns: nothing
description: performs the branch operations by finding the correct immediate value, which is based on the offset
*/
void line::branch(MIPS_arguments* args)
{
	int i = 0;
	int offset;
	
	i = memoryAddress(args->arg4);
	rs = registers(args->arg2);
	rt = registers(args->arg3);
	
	offset = myLine + 1;
	i = i - offset;
	
	immediate = convertBinaryDec(i,16);

	return;
}

/*
name: memoryAddress
parameters: a string that represents the argument that is a label name
returns: an integer representing the program counter
description: finds where a certain label was made, and tells you the program count there
*/
int line::memoryAddress(string arg)
{
	ifstream fp2("mips.asm");
	string str;
	
	int i = 0;
	int offset;
	int val1;
	int val2;
	
	arg = arg + ":";
	while(getline(fp2, str))
	{
		int spacePos1 = str.find(' '); // find 1st space
		string arg1 = str.substr(0, spacePos1); // from beginning to 1st space
		string str2 = str.substr(spacePos1 + 1); // from 1st space to the end
		
		int spacePos2 = str2.find(' ');
		string arg2 = str.substr(0, spacePos2);
		string str3 = str.substr(spacePos2 + 1);
		int commaPos1 = arg2.find(','); // find 1st comma
		arg2 = arg2.substr(0, commaPos1);
		
		if (arg1 == arg)
		{
		//	cout << "label: " << arg << "found at: " << i << endl;
			return i;
		}
		else
		{
			
			val1 = one(arg1);
			val2 = one(arg2);
			if(!(val1) || !(val2))
			{
				i++;
			}
		}
		
	}
	cout << "label not found: " << arg << endl;
	return 0;
}

/*
name: convertFinalHex
parameters: none
returns: nothing
description: this function takes the final binary number and converts 4 bits at a time into hex by calling the hexify function and 
then adding the hex together and setting final equal to the hex
*/
void line::convertFinalHex()
{
	string word;
	string hex;
	int i, start, cap;
	
	start = 0;
	cap = 4;
	i =0;
	if(final.length() == 32)
	{
		while(i <= 7)
		{
		
			word = final.substr(0, 4);
			hex = hex + hexify(word);
			//start+=4;
			//cap+=4;
			final = final.substr(4, (final.length())+1);
			i++;
		}
		final = "0x" + hex;
	}
	return;
}

/*
name: hexify
parameters: a string of numbers that represents a 4 bit binary number
returns: a character that represents the binary being converted into hex
description: converts 4 bit binary into a hex digit
*/
char hexify(string word)
{
	//cout << word << endl;
	char digit;
	if		(word == "0000"){digit = '0';}
	else if	(word == "0001"){digit = '1';}
	else if	(word == "0010"){digit = '2';}
	else if	(word == "0011"){digit = '3';}
	else if	(word == "0100"){digit = '4';}
	else if	(word == "0101"){digit = '5';}
	else if	(word == "0110"){digit = '6';}
	else if	(word == "0111"){digit = '7';}
	else if	(word == "1000"){digit = '8';}
	else if	(word == "1001"){digit = '9';}
	else if	(word == "1010"){digit = 'a';}
	else if	(word == "1011"){digit = 'b';}
	else if	(word == "1100"){digit = 'c';}
	else if	(word == "1101"){digit = 'd';}
	else if	(word == "1110"){digit = 'e';}
	else if	(word == "1111"){digit = 'f';}
	else					{digit = 'x';}
	return digit;
}

/*
Name: convertBinary
parameters: a string decimal number and the number of bits to have for the binary conversion
returns: a string of the binary conversion
description: takes in a string of a decimal number and converts it to the right length of binary bits wanted
*/
string convertBinary(string decimal, int bits)
{
	int quotient, dividend, divisor, remainder, i;
	int bi[bits]; // = {0};
	string final;
	stringstream s;
	s.str(" ");
	bool flip=false;
	quotient = 1;
	dividend = atoi(decimal.c_str());
	divisor = 2;
	remainder = 0;
	
	if(dividend<0)
	{
		flip=true;
		dividend*=-1;
		
	}
	
	//initialize bi[bits] to all zeros
	for(i=0; i < bits; i++)
	{
		bi[i] = 0;
	}
	
	i=(bits - 1);
	//i=15;
	while(quotient != 0)
	{
		quotient = dividend/divisor;
		remainder = dividend - (quotient*divisor);
		dividend = quotient;
		
		bi[i] = remainder;
		
	//	cout << "bi[i]: " << bi[i] << endl;
		
		i--;
	}
	
	if(flip)
	{
		for(i=bits; i > 0; i--)//change all binary values to the opposite
		{
			if(bi[i]==1)
			{
				i--;
				while( i >= 0 )
				{
					if(bi[i]==1)
						bi[i]=0;
					else
						bi[i]=1;
					i--;
				}
			}
			else
			{
				;	
			}
		}
	}
		
	for(i = 0; i < bits; i++)
	{
		s << bi[i];
	}
	
	final = s.str();
//	cout << "final: " << final << endl;
	

	return final;
	
}

/*
Name: convertBinaryDec
parameters: the decimal number given, the number of bits it needs to be converted into
returns: the binary string
description: this function converts a decimal number into a certain length binary number
*/
string convertBinaryDec(int decimal, int bits)
{
	int quotient, dividend, divisor, remainder, i;
	int bi[bits]; // = {0};
	string final;
	stringstream s;
	
	s.str(" ");
	quotient = 1;
	dividend = decimal;
	divisor = 2;
	remainder = 0;
	
	//initialize bi[bits] to all zeros
	for(i=0; i < bits; i++)
	{
		bi[i] = 0;
	}
	
	i=(bits - 1);
	//i=15;
	while(quotient != 0)
	{
		quotient = dividend/divisor;
		remainder = dividend - (quotient*divisor);
		dividend = quotient;
		
		bi[i] = remainder;
		
	//	cout << "bi[i]: " << bi[i] << endl;
		
		i--;
	}
	
	for(i = 0; i < bits; i++)
	{
		s << bi[i];
	}
	
	final = s.str();
	//cout << "final: " << final << endl;
	
	return final;
}