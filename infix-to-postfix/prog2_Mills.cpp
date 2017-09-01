// Michael Kellen Mills
// CSCE3110.program 2
// convert an infix expression to a postfix expression. with error checking
#include <iostream>
#include <stack>
#include <string>

using namespace std;

//This program makes use of recusion, and I needed my counters to say constant across all calls.
typedef struct{
	int i;
	int paren;
	int rate;
	int rand;
	bool opran;
	bool oprat;
	bool openP;
}counter;

//////////////FUNCTIONS//////////////////////////
void inToPostFix();
string statement(string infix, counter *q);
bool higherPrec(char n, char s);
///////////////////////////////////////////////////////////////////////
//MAIN FUNCTION
/////////////////////////////////////////////////////////////////////
int main()
{
	inToPostFix();
	return 0;
}

void inToPostFix()
{
	string infix;
	string postfix;
	cout << "Type an infix expression" << endl << "> ";
	getline(cin, infix);

	//The construction of the counting structure to keep track of my various ints across calls.
	counter quake;
	quake.i = 0;
	quake.rand = 0;
	quake.rate = 0;
	quake.paren = 0;
	quake.opran = false;
	quake.oprat = false;
	quake.openP = false;

	postfix = statement(infix, &quake);//statement will create a postfix expression.

	//error handling of the infix expression, the necessary counter was done in the various calls of the function "statement"
	if(quake.paren != 0)
	{
		cout << "Parenthesis are not balanced!" << endl;
	}
	else if(quake.rand == 0)
	{
		;
	}
	else if(quake.rate >= quake.rand)
	{
		cout << "too many operators!" << endl;
	}
	else if((1+quake.rate) != quake.rand)
	{
		cout << "not enough operators!" << endl;
	}
	else
		cout << postfix << endl;

	return;
}
string statement(string infix, counter *q)
{
	string postfix;
	stack<char> funcs;

	//Check to see if the function encounters a close parenthesis too soon.
	if((infix[q->i] == ')') && (q->paren == 0))
	{
		cout << "cannot close parenthesis without opening first!" << endl;
		q->paren--;
		return postfix;
	}
	//this while statement can build simple postfix expressions
	while((infix[q->i] != '\0') && (infix[q->i] != ')'))
	{
		if((infix[q->i] > 64) && (infix[q->i] < 91))
		{
			infix[q->i] += 32;
		}
		if((infix[q->i] > 96) && (infix[q->i] < 123))
		//lowercase letters
		{
			if(q->opran == true)
			{
				cout << "Two operands in a row! Not a valid infix!" << endl;
				q->rand++;
				q->rand++;
					return postfix;
			}
			q->oprat = false;
			q->openP = false; //flag for if an operand has been seen after a parenthesis
			q->opran = true;
			q->rand++;
			postfix += infix[q->i];
		}
		else if(infix[q->i] == '(')
		{
			q->paren++;
			q->i++;
			//this recursive call is made for each open parenthesis. they are treated like individual expressions
			postfix += statement(infix, q);
		}
		else if((infix[q->i] == '+') ||
			(infix[q->i] == '-') ||
			(infix[q->i] == '*') ||
			(infix[q->i] == '/') ||
			(infix[q->i] == '^'))
			//the five available operators
		{
			if(q->openP == true)
			{
				cout << "Operator seen immediately after an open parnethesis." << endl;
				return postfix;
			}
			if(q->oprat == true)
			{
				cout << "Two Operators in a row! Not a valid infix!" << endl;
				q->rate++;
				q->rate++;
				return postfix;
			}
			if(q->opran == false)
			//if operand is false AND operator is true, then this must be the first term the program has seen.
			{
				cout << "Program must begin with an operand!" << endl;
			}
			q->oprat = true;
			q->opran = false;
			q->rate++;
			if(funcs.empty())
			{
				funcs.push(infix[q->i]);
			}
			else
			{
				while((!funcs.empty()) && (higherPrec(infix[q->i], funcs.top())))
				//the higher precedence function is where all the postfix-logic-magic happens
				{
					postfix += funcs.top();
					funcs.pop();
				}
				funcs.push(infix[q->i]);
			}
		}
		else if(infix[q->i] == ' ')
		//the program recognizes spaces and throws them out
		{;}
		else
		//a character which the program did not recognize
		{
			cout << "Invalid character, what are you doing?" << endl;
		}
		q->i++;
	}
	while(!funcs.empty())
	//this loop prints any remaining operators on the stack.
	{
		postfix += funcs.top();
		funcs.pop();
	}
	if(infix[q->i] == ')')
	{
		q->paren--;
	}
	return postfix;
}
bool higherPrec(char n, char s)
//compares two operators and returns true if the stack is greater than or equal to the new operator
{
	switch(n)
	//the outer switch statement is the current, or New operator
	{
		case '+':
		case '-':
		{
			switch(s)
			//each inner switch statement is the operator on the stack.
			{
				default:
				return true;
			}
			break;
		}
		case '*':
		case '/':
		{
			switch(s)
			{
				case '-':
				case '+':
				return false;
				default:
				return true;
			}
		}
		case '^':
		{
			switch(s)
			{
				case '+':
				case '-':
				case '*':
				case '/':
				case '^':
					return false;
				default:
					return true;
			}
		}
		case '(':
		{
			switch(s)
			{
				case '+':
				case '-':
				case '*':
				case '/':
				case '^':
				case '(':
					return false;
				default:
					return true;
			}
		}
		default:
		//not sure how the function got here, but, if it did it's returning false.
			return false;
	}
}
