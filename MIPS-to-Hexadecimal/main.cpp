
#include "class.h" // our own .h file

using namespace std;

int main()
{
	line* currentLine;
	currentLine = new line; //declaring a new object of class line
	line *headLine = currentLine; //head of the lines

	symbol* currentLabel;
	currentLabel = new symbol;
	symbol *headLabel = currentLabel; //head of the symbol table "label table" (hey! that rhymes!)

	MIPS_arguments args;
	int linecount;
	linecount=0; // linecount starts at zero, count lines for hex addressing
	ifstream input;
	ofstream output;
	string str;
	
	input.open("mips.asm");
	if(input.fail())
	{
		cout << "Input file does not exist." << endl;
		exit(1);
	}

	while(getline(input, str))
	{
		if(str == "\0")
		{;}
		else
		{
		int spacePos1 = str.find(' '); // find 1st space
		args.arg1 = str.substr(0, spacePos1); // from beginning to 1st space
		string str2 = str.substr(spacePos1 + 1); // from 1st space to the end
		
		int commaPos1 = args.arg1.find(','); // find 1st comma
		args.arg1 = args.arg1.substr(0, commaPos1);
		
		int spacePos2 = str2.find(' '); // find 2nd space
		args.arg2 = str2.substr(0, spacePos2); // from 1st space to the 2nd space
		string str3 = str2.substr(spacePos2 + 1); // from 2nd space to the end
		
		int commaPos2 = args.arg2.find(','); // find 1st comma
		args.arg2 = args.arg2.substr(0, commaPos2);
		
		int spacePos3 = str3.find(' '); // find 3rd space
		args.arg3 = str3.substr(0, spacePos3); // from 2nd space to 3rd space
		string str4 = str3.substr(spacePos3 + 1); //from 3rd space to end
		
		int commaPos3 = args.arg3.find(','); // find 1st comma
		args.arg3 = args.arg3.substr(0, commaPos3);
		
		int spacePos4 = str4.find(' '); // find 4th space
		args.arg4 = str4.substr(0, spacePos4); // from 3rd space to 4th space
		
		int commaPos4 = args.arg4.find(','); // find 1st comma
		args.arg4 = args.arg4.substr(0, commaPos4);
		
		args.arg5 = str4.substr(spacePos4 +1); //from 4th space to end

		/*This block of code finds the parathesis delimitors and extracts the info we need*/
		if(args.arg1 == "sw" || args.arg1 == "lw")
		{
			string str = args.arg3;
			int openParen = str.find('('); //find opening parenthesis
			int closeParen = str.find(')'); //find closing parenthesis

			args.arg3 = str.substr(0, openParen); //arg 3 is the number before the parenthesis
			args.arg4 = str.substr(openParen+1, closeParen-2); //arg 4 is the thing inside the 2 parenthesis
		}

		//print out the arguments below to see what's in them.
		//cout << endl << " arg1: " << args.arg1 << "\targ2: " << args.arg2 << "\targ3: " << args.arg3 << "\targ4: " << args.arg4 << "\targ5: " << args.arg5 << endl << endl;

		//maybe take the arguments and pass them into our functions to determine what to do next with them here
		int val = one(args.arg1); // label or instruction
		if(val==1) //label
		{
		
			string hexAddress;
			stringstream s;
			s.str(" ");
			s << "0x" << hex << setw(8) << setfill('0') << linecount*4;
			hexAddress = s.str();
			
			currentLabel->setLabel(args.arg1, hexAddress, linecount*4);
			currentLabel->setNext(new symbol);
			currentLabel = currentLabel->getNext();
			currentLabel->setNext(NULL);
			//add the label and its address into the symbol table
			if(!(args.arg2.empty()))
			{
				val = one(args.arg2);
			if(!(val)) //label could also have an instruction
			{
					args.arg1 = args.arg2;//this block is here to overwrite and move the label so that we can treat...
					args.arg2 = args.arg3;//...the remainder of the argument structure the same across all funcitons...
					args.arg3 = args.arg4;//...for all instances
					args.arg4 = args.arg5;
					if(args.arg1 == "sw" || args.arg1 == "lw")//what if lw or sw come after a LABEL?
					{
						string str = args.arg3;
						int openParen = str.find('('); //find opening parenthesis
						int closeParen = str.find(')'); //find closing parenthesis

						args.arg3 = str.substr(0, openParen); //arg 3 is the number before the parenthesis
						args.arg4 = str.substr(openParen+1, closeParen-2); //arg 4 is the thing inside the 2 parenthesis
					}
					currentLine->setLine(linecount);
					currentLine->opCode(args.arg1, &args);
			
					currentLine->setNext(new line);//makes a new line in the current line's "next"
			        currentLine = currentLine->getNext();//sets the current equal to the new.
		        	currentLine->setNext(NULL);
				
			}
			}
		}
		else //instruction
		{
			currentLine->setLine(linecount);
			currentLine->opCode(args.arg1, &args);	
			
			currentLine->setNext(new line);//makes a new line in the current line's "next"
	        currentLine = currentLine->getNext();//sets the current equal to the new.
	        currentLine->setNext(NULL);
			
		}

	//	cout << endl << "Linecount: " << linecount << endl; //these 3 lines are to check to make sure we're getting the right linecount
	//	cout << "Hex: 0x" << hex << setw(8) << setfill('0') << linecount  << endl; // we need the hex address to save into a list of some sort
	//	cout << "Hex address: 0x" << hex << setw(8) << setfill('0') << linecount*4 << endl; //use this line if the first word is a label, save somewhere

	
		if(val==0)
			{
				linecount++;
			
			}
		}
	}	
	
	
	
	output.open("hex.txt");
	
	currentLine = headLine;
	while(currentLine != NULL)
	{
		currentLine->convertFinalHex();	
		output << currentLine->getFinal() << endl;
		currentLine = currentLine->getNext();
	}
	
	output << "Label" << "\t\t" << "Address" << endl;
	
	currentLabel = headLabel;
	while(currentLabel != NULL)
	{
		output << currentLabel->getLabel() << endl;
		currentLabel = currentLabel->getNext();
	}

	
	
	output.close();
	input.close();

	return 0;
}
