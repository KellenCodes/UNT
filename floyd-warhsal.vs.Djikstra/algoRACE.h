#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
#include <utility>
#include <fstream>
#include <unistd.h>
#define MAXGRAPHS 30
#define GRAPH_SIZE_VARIANCE 1750
#define GRAPH_SIZE_MIN 50
using namespace std;
typedef pair<int, int> intPair;


class graph;

class djikstra{
	const graph *base;
	int size;
	graph *paths;
	
	public:
	void printG(ofstream& fs);
	int minDistance(int dist[], bool sptSet[]);
	void run();
	void single(int source);
	djikstra(const graph *process, int s);
	~djikstra();
};
class floydWarshall{
	const graph *base;
	int size;
	graph *paths;
	
	public:
	void printG(ofstream& fs);
	void run();
	floydWarshall(const graph *process, int s);
	~floydWarshall();
};

class graph{
	friend class djikstra;
	friend class floydWarshall;
	int size;
	int **subject;
	
	public:
	void scanG(ifstream& fs);
	void printG(ofstream& fs);
	int getSize(){return size;};
	graph(int costs = 0);
	~graph();

};

class resolve{
//will keep record of an individual test case
	double djikst;
	double flowar;
	int size;
	int type;
	
	public:
	void setDjikst(clock_t start, clock_t stop){
		djikst = (double) (stop - start) / CLOCKS_PER_SEC;
	}
	void setFlowar(clock_t start, clock_t stop){
		flowar = (double) (stop - start) / CLOCKS_PER_SEC;
	}
	void setSize(int s){size = s;};
	double getDjikst(){ return djikst;};
	double getFlowar(){ return flowar;};
	int getSize() {return size;};
	string getType() {
		if(type == 0) {return "random";}
		else if (type == 1) {return "uniform";} 
		else if (type == 2) {return "distance";}
	};
	
};

void printTopMenu();
void printGraphMenu();
void printResultsMenu();
void testGraph(resolve *results, int graphsHad);
void seeResults(resolve *results, int graphsHad);
