#include "algoRACE.h"

int main(int argc, char *argv[]){
//first user interface. Directs the user to where they want to go.
	int exit = 1;
	int graphsHad = 0;
	resolve *results = new resolve[MAXGRAPHS];
	clock_t start, stop;
	if(argc > 1){
	if(argv[1][0] == 'n'){
		ofstream fs;
		fs.open(argv[2]);
			for(int i = 0; i < MAXGRAPHS; i++){
				sleep(1);
				graph output(0);
				fs << i << endl;
				output.printG(fs);
			}
		fs.close();
	}
	else if(argv[1][0] == 'f'){
		ifstream fs;
		ofstream rfs;
		if(!(argc > 2)){return 1;}
		fs.open(argv[2]);
		int size, doNotUse;
			for(int i = 0; i < MAXGRAPHS; i++){
				fs >> doNotUse;
				fs >> size;
				graph input(size);
				input.scanG(fs);
				
				results[graphsHad].setSize(input.getSize());
				djikstra dj(&input, input.getSize());
				start = clock();
				dj.run();
				stop = clock();
				results[graphsHad].setDjikst(start, stop);
	
				floydWarshall fw(&input, input.getSize());
				start = clock();
				fw.run();
				stop = clock();
				results[graphsHad].setFlowar(start, stop);
				
				graphsHad++;
				if((argc > 4)){
				if(argv[4][0] == 'g'){
					rfs.open(argv[3], std::ofstream::out | std::ofstream::app);
					dj.printG(rfs);
					fw.printG(rfs);
					rfs.close();
				}}
			}
		fs.close();
				if((argc > 3)){
		rfs.open(argv[3], std::ofstream::out | std::ofstream::app);
		for(int i = 0; i < MAXGRAPHS; i++){
			rfs << "graph was size ";
			rfs << results[i].getSize();
			rfs << "x";
			rfs << results[i].getSize() << endl;
			rfs << "Djikstra solved in: ";
			rfs << results[i].getDjikst() << endl;
			rfs << "Floyd-Warshall solved in: ";
			rfs << results[i].getFlowar() << endl;
			rfs << endl;
		}
		rfs.close();}
		seeResults(results, graphsHad);
	}
	}
	else{//////////////////////////////////////////////////////
	
		string command;
		printTopMenu();
		while(exit)
		{
			printTopMenu();
			cout << "> ";
			cin >> command;
			if(command == "exit" || command == "q" || command == "quit" || command == "3")
			{
				exit = 0;
			}
			else if(command == "test" || command == "1" || command == "t")
			{
				if(graphsHad == MAXGRAPHS){
					cout << "System has processesed the maximum number of allowed graphs, better luck next year!" << endl;
				}
				else
					testGraph(results, graphsHad++);
			}
			else if(command == "results" || command == "2" || command == "r")
			{
				seeResults(results, graphsHad);
			}
			else if(command == "clear")
			{
				printTopMenu();
			}
			else
				cout << "I dont understand that command, type clear to see the menu again..." << endl;
		}
	}/////////////////////////////////////////////////////////
	return 0;
}
/////////////////vvv These functions are for my sanity.vvv////////////////////
void printTopMenu()
{
	cout << "\033[2J\033[1;1H";
	cout << "Command me." << endl;
	cout << "1) test, or t" << endl;
	cout << "2) results, or r" << endl;
	cout << "3) quit, or q " << endl << endl;
	return;
}

void printGraphMenu()
{
	cout << "\033[2J\033[1;1H";
	cout << "Weights:" << endl;
	return;
}
void printResultsMenu()
{
	cout << "\033[2J\033[1;1H";
	cout << "type -1 to exit." << endl;
	cout << "look at results for test number:" << endl;
	return;
}
///////////////////^^^^they're just a bunch of menus^^^^////////////////

void testGraph(resolve *results, int graphsHad){
	clock_t start, stop;
	int weight;
	graph *space;

	printGraphMenu();
	cout << "> ";
	cin >> weight;
//this block is looking for how we are to make the graph
	if (cin.fail() || weight < 0) {
		cout << "positive numbers only, type 0 for random values!" << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		cin.ignore();
		return;
	}
	else if (weight > 0 && weight <= 2) {
		space = new graph(weight);
	}
	else {
		space = new graph;
		
	}
//this block administers the test.
	results[graphsHad].setSize(space->getSize());
	djikstra dj(space, space->getSize());
	start = clock();
	dj.run();
	stop = clock();
	results[graphsHad].setDjikst(start, stop);
	
	floydWarshall fw(space, space->getSize());
	start = clock();
	fw.run();
	stop = clock();
	results[graphsHad].setFlowar(start, stop);

	delete space;
	return;
}

void seeResults(resolve *results, int graphsHad){
//ths function will ask for user input, it expects something 1-based.
	int result;
	graphsHad;
	bool exit = false;
	while(!exit){
	printResultsMenu();
	cout << "> ";
	cin >> result;
	result;
	if(result <= graphsHad && result > 0){
		result--;
		cout << "graph was size ";
		cout << results[result].getSize();
		cout << "x";
		cout << results[result].getSize() << endl;
		cout << "Djikstra solved in: ";
		cout << results[result].getDjikst() << endl;
		cout << "Floyd-Warshall solved in: ";
		cout << results[result].getFlowar() << endl;
	}
	else if(result == -1){
		exit = true;
	}
	else{
		cout << "We don't have results for test number ";
		cout << result;
		cout << " right now we have ";
		cout << graphsHad;
		cout << " result";
		if (graphsHad == 1) { cout << "." << endl;}
		else { cout << "s." << endl;}
		
	}
	cin.ignore(10000, '\n');
	cin.ignore();
	}
	return;
}