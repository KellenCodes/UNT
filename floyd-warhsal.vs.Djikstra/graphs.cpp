#include "algoRACE.h"

graph::graph(int costs){
//this constructore will build a cost matrix based on use input.
	srand(time(NULL));
	if(costs > 3){
		size = costs;
	}
	else{
		size = ((rand() % GRAPH_SIZE_VARIANCE) + GRAPH_SIZE_MIN);
	}
	subject = new int*[size];
	for(int i = 0; i < size; i++){
		subject[i] = new int[size];
	}
	
	if ( costs == 0){
		for (int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				subject[i][j] = ((rand() % 200) + 1);
				if(i==j){subject[i][j] = 0;};
				}
		}
	}
	else if (costs == 1){
		;//i am explicitly doing nothing.
	}
/*	else if (costs == 2){
		for (int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				if(i<j) {subject[i][j] = (j-i);}
				else if(i>j) {subject[i][j] = (i-j);}
				else if(i==j){subject[i][j] = 0;}
				else {cout << "the system has a virus!" << endl;};
			}
		}
	}
*/	else if (costs > 3){
	
		for (int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				subject[i][j] = costs;
				if(i==j){subject[i][j] = 1000000;};
				if(i==j){subject[i][j] = 0;};
			}
		}
	}	
	else{
		cout << "I dont have functionality for ";
		cout << costs;
		cout <<", try 0 for random." << endl;
		cin.ignore(10000, '\n');
		cin.ignore();
	}		
}
void graph::scanG(ifstream& fs){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			fs >> subject[i][j];
		}
	}
}

void graph::printG(ofstream& fs){
	fs << size << endl;
	for(int j = 0; j < size; j++){
		for(int k = 0; k < size; k++){
			fs << subject[j][k] << " ";
		}
		fs << endl;
	}
}
void djikstra::printG(ofstream& fs){
	paths->printG(fs);
}
void floydWarshall::printG(ofstream& fs){
	paths->printG(fs);
}

graph::~graph(){
	for(int i = 0; i < size; i++){
		delete subject[i];
	}
	delete subject;
}

djikstra::djikstra(const graph *process, int s){
	base = process;
	size = s;
	paths = new graph(size);
}

djikstra::~djikstra(){
}

floydWarshall::floydWarshall(const graph *process, int s){
	base = process;
	size = s;
	paths = new graph(size);
}

floydWarshall::~floydWarshall(){
}
///referenced http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/
void djikstra::run(){	
	for(int i =  0; i < size; i++){
		single(i);
	}
/*	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			cout << paths->subject[i][j] << " ";
		}
		cout << endl;
	}
*/
}

void djikstra::single(int source){
	
	int distance[size]; 
	bool visited[size]; //the set of all visited nodes
	
	for(int i = 0; i < size; i++){
		paths->subject[source][i] = INT_MAX; 
		visited[i] = false;
	}
	
	paths->subject[source][source] = 0;
	
	for(int i = 0; i < size-1; i++){
		int u = minDistance(paths->subject[source], visited);
		visited[u] = true;
		for(int v=0; v < size; v++){
			if(paths->subject[source][u] != INT_MAX && paths->subject[source][u]+base->subject[u][v] < paths->subject[source][v] && !visited[v] && base->subject[u][v] )
				paths->subject[source][v] = paths->subject[source][u] + base->subject[u][v];
		}
	}
/*//	bool visited[size];
	set<int> Q;
	set<int>::iterator it;
	

	
	for(int i = 0; i < size; i++){
		Q.insert(i);
	//		visited[i] = false;
	}
	Q.erase(source);
	int active = source;
	//cout << source << " ";
	while(!Q.empty()){
		int smallest = INT_MAX;
		int indexSmallest = INT_MAX;
		paths->subject[active][active] = 0;
		for(int i = 0; i < size; i++){
			//u := ExtractCheapest(Q);; u is indexSmallest and its weight is smallest
			if(base->subject[active][i] < smallest && Q.find(i) != Q.end()){
				smallest = base->subject[active][i];
				indexSmallest = i;
				//cout << smallest << "," << indexSmallest << " ";
				//cout << active << endl;
			}		
		}
		//AddNode(S, u); S == Q - visited
		Q.erase(indexSmallest);
		//for each vertex v in Adjacent(u)
		for( int i = 0; i < size; i++)
		{
			int v = i;
			//weight from u to v.
			int weight = base->subject[indexSmallest][v];
			//cout << weight << " ";
			if(base->subject[active][v] > base->subject[active][indexSmallest] + weight){
				paths->subject[active][v] = paths->subject[active][indexSmallest] + weight;
				//cout << paths->subject[active][v] << " ";
			}
		}
			//relax(u,v,w)
			//relax( Node u, Node v, double w[][] )
				//if d[v] > d[u] + w[u,v] then
					//d[v] := d[u] + w[u,v]
					//pi[v] := u
		active = indexSmallest;
		//cout << active << " ";
	}
	//cout << endl;*/
}
int djikstra::minDistance(int distance[], bool visited[])
{
   // Initialize min value
   int min = INT_MAX, min_index;
  
   for (int v = 0; v < size; v++)
     if (visited[v] == false && distance[v] <= min)
         min = distance[v], min_index = v;
  
   return min_index;
}

void floydWarshall::run(){

	int distance[size][size],from,to,inbetween;
	for (from=0; from < size; from++){
		for(to=0;to < size; to++){
			paths->subject[from][to] = base->subject[from][to];
		}
	}
	for (inbetween = 0;inbetween < size; inbetween++){
		for(from = 0; from < size; from++){
			for(to = 0; to < size; to++){
				if(paths->subject[from][inbetween] + paths->subject[inbetween][to] < paths->subject[from][to]){
					paths->subject[from][to] = paths->subject[from][inbetween] + paths->subject[inbetween][to];
				}
			}
		}
	}
	
}