//Jonathan S. Chandranathan
//Old code I wrote to play around with graphs.  Calculates the shortest path around DisneyLand using Prim's algorithm.

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <stack>
#include <deque>
#include <algorithm>
#include <queue>
#include <math.h>
#include "timer.h"

//Update filepath accordingly:
std::string const FILENAME = "C:\\Dropbox\\Dropbox\\data.txt";

class Edge{
private:
	float _weight;
	int _from, _to;
	bool _seen;
public:
	Edge(float const weight, int const from, int const to) {
		_weight = weight;
		_from = from;
		_to = to;
		_seen = false;
	}

	bool operator< (const Edge& e ){
		return _weight > e._weight;
	}

	void set_weight(float weight) {_weight = weight;}
	void set_seen () {_seen = true;}
	int get_from() {return _from;}
	int get_to() {return _to;}
	float get_weight() {return _weight;}
	bool get_seen() {return _seen;}
};

class Node{
private:
	std::string _name;
	int _id, _x_cord, _y_cord;
	bool _seen;

public:
	Node(std::string const name, int const id, int const x_cord, int const y_cord) {
		_name = name;
		_id = id;
		_x_cord = x_cord;
		_y_cord = y_cord;
		_seen  = false;
	}

	void set_seen() {_seen = true;}
	bool get_seen() {return _seen;}
	std::string get_name() {return _name;}
	int get_id() {return _id;}
	int get_x_cord() {return _x_cord;}
	int get_y_cord() {return _y_cord;}
};

class comparator{
public:
	bool operator()( Edge* lhs, Edge* rhs) {
		return lhs->get_weight() > rhs->get_weight();
	}
};

int main() {
	//Step 0: Initialize everything
	std::string name;
	int num_of_points, id, x_cord, y_cord, counter = 1, i, z, d;
	float weight = 0;
	std::priority_queue<Edge*,std::vector<Edge*>, comparator> pq;
	float num_to_sqrt;
	Timer clock;
	
	std::ifstream f(FILENAME.c_str());

	if (!f) {
		std::cout << "ERROR: cannot open " << FILENAME << std::endl;
		system("pause");
		return 1;
	}

	f >> num_of_points;
	num_of_points += 1;
	std::vector<Node*> nodes(num_of_points);
	std::vector<std::vector<Edge*>> edges(num_of_points, std::vector<Edge*> (num_of_points));
	std::vector<Edge*> MSTe(0);
	std::vector<Node*> MSTv(0);

	while (f) {
		f >> id;
		f >> x_cord;
		f >> y_cord;
		f >> name;
		Node* ptr = new Node(name, id, x_cord, y_cord);
		if (counter < 85) nodes[counter] = ptr;
		counter++;
	}
	
	f.close();
	clock.reset();
	
	//Step 1:  Propogate adjacency matrix with weighted edges
	for (i = 1; i < num_of_points; i ++){
		for (z = 1; z < num_of_points; z++){
			//Euclidean distance equation = sqrt [ (x2 - x1)^2 + (y2 - y1)^2 ]
			num_to_sqrt = ( ((nodes[i]->get_x_cord()-nodes[z]->get_x_cord()) * (nodes[i]->get_x_cord()-nodes[z]->get_x_cord()))
						+   ((nodes[i]->get_y_cord()-nodes[z]->get_y_cord()) * (nodes[i]->get_y_cord()-nodes[z]->get_y_cord())) );
			if (num_to_sqrt == 0)
				num_to_sqrt = 99999999999999;
			Edge* ptr = new Edge (sqrt(num_to_sqrt), i, z);
			edges[i][z] = ptr;
		}
	}

	//Step 2:  Use Prim's algorithm to create minimmum spanning tree
	Node* seen = nodes[1];
	MSTv.push_back(seen);
	for (i= 1; i < num_of_points; i++){
			pq.push(edges[1][i]);
	}

	Edge* e_ptr = pq.top();
	seen = nodes[e_ptr->get_from()];
	Node* unseen = nodes[e_ptr->get_to()];
	seen->set_seen();

	while (MSTe.size() < num_of_points-2){
		do{
			e_ptr = pq.top();
			pq.pop();

			if ( nodes[e_ptr->get_from()]->get_seen()  ){
				seen = nodes[e_ptr->get_from()];
				unseen = nodes[e_ptr->get_to()];
			}
			else {
				seen = nodes[e_ptr->get_to()];
				unseen = nodes[e_ptr->get_from()];
			}
		} while (binary_search( MSTv.begin(), MSTv.end(), unseen));
		
		if (nodes[e_ptr->get_from()]->get_seen() ^ nodes[e_ptr->get_to()]->get_seen()){
			MSTe.push_back(e_ptr);
			unseen->set_seen();
			MSTv.push_back(unseen);
			for (d = 1; d < num_of_points; d++){								
				Edge* f_ptr = edges[ unseen->get_id() ][d];							
				if (e_ptr != f_ptr)
					pq.push(f_ptr);
			}
		}
	}

	//Step 3:  Display information
	std::ofstream outputFile ("C:\\Dropbox\\Dropbox\\output.txt");
	outputFile<<"Prim's algoirthm took "<< clock.elapsed() <<" seconds"<<std::endl;	

	do{
	weight += MSTe.back()->get_weight();
	outputFile<<"From "<<MSTe.back()->get_from() <<" [ "<< nodes[MSTe.back()->get_from()]->get_name() <<" ] to "<<MSTe.back()->get_to()<< " [ "<< nodes[MSTe.back()->get_to()]->get_name() <<" ] | Weight "<<MSTe.back()->get_weight()<<std::endl;
	MSTe.pop_back();
	} while (!MSTe.empty());

	outputFile<<"Loaded "<<num_of_points-1<<" sites."<<std::endl;
	outputFile<<"Total weight: "<<weight<<std::endl;
	outputFile.close();
	return 0;
}