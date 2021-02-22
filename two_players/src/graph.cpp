//============================================================================
// Name        : graph.cpp
// Author      : Carlos Granados
// Version     : 1.0
// Date        : 11.02.2021
// Copyright   : GNU
// Description : Implementation of class Graph
//============================================================================


#include <iostream>
#include <fstream>
#include "graph.h"

//using namespace std;



//------------------------------------------------------------------------------
// Implementation of class Graph
//------------------------------------------------------------------------------


// Constructors

Graph::Graph() { // @suppress("Class members should be properly initialized")
	n_nodes = 0;
}

Graph::Graph(const int n) { // @suppress("Class members should be properly initialized")

	n_nodes = n;

	// Resize the vectors to save nodes and edges
	resize_storage();

	// Initialize the graph to 0
	make_graph();
}

Graph::Graph(string file_name) {
	ifstream inFile;

	// Open File
	inFile.open(file_name);
	// Check that file exists. If not, call system to stop
	if ( !inFile ) {
		cerr << "Unable to locate file";
		exit(1);
	}

	// Read Data file
	// First, read number of nodes
	int n;
	inFile >> n;
	n_nodes = n;
	cout << endl << "New graph: " << endl;
	cout << "Num. of vertices : " << n_nodes << endl;

	resize_storage();

	// Close File
	inFile.close();

	// Initialize graph (set all elements to 0)
	make_graph();
	// Call function to read the graph
	read_graph(file_name);
}

// Getters and setters

// Get vertices
int Graph::get_num_nodes() {
	return n_nodes;
}

// Get edges
int Graph::get_e() {
	for (int i = 0; i < n_nodes; ++i) {
		for (int j = 0; j < n_nodes; ++j) {
			if ( g[i][j] )
				n_edges++;
		}
	}
	return n_edges;
}

// Returns the value associated with the node x
int Graph::get_node_value(const int i, const int j) {
	return val_nodes[i][j];
}

// Get the value associated to the edge (i, j)
double Graph::get_edge_value(const int i, const int j) {
	return val_edges[i][j];
}

// Set the value associated with the node i to a
void Graph::set_node_value(const int i, const int j, const int a) {
	val_nodes[i][j] = a;
}

// Set the value associated to the edge (i, j) to v
void Graph::set_edge_value(const int i, const int j, double v) {
	val_edges[i][j] = v;
}

// Other methods

// Check if the nodes i and j are adjacent (an edge from i to j)
bool Graph::adjacent(const int i, const int j) {
	return g[i][j];
}

// List all nodes that have an edge from/to i
void Graph::get_neighbors(const int i, int & n, int * neighs) {
	// Count the number of neighbors
	n = 0;
	for (int j = 0; j < n_nodes; ++j) {
		if ( g[i][j] )
			n++;
	}

	// If there are neighbors, fill the array neigh with the indeces
	if ( n != 0 ) {
		int indx = 0;
		for (int j = 0; j < n_nodes; ++j) {
			if ( g[i][j] ) {
				neighs[indx] = j;
				indx++;
			}
		}
	}
}

// Add an edge between i and j if it is not there
void Graph::add(const int i, const int j) {
	if ( ! g[i][j] )
		g[i][j] = true;
}

// Delete an edge between i and j if it is there
void Graph::del(const int i, const int j) {
	if ( ! g[i][j] )
		g[i][j] = false;
}

// Function to create the graph and initialize it to 0
void Graph::make_graph() {

	for (int i = 0; i < n_nodes; i++) {
		for (int j = 0; j < n_nodes; j++) {
			val_nodes[i][j] = 0;
		}
	}

}

// Function to print the graph in a matrix form.
// It prints the values associated to each edge
void Graph::print() {
	// Print the edges values in matrix form
	cout << endl;
	for (int i=0; i < n_nodes; ++i) {
		for (int j=0; j < n_nodes; ++j) {
			cout << val_edges[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

// Function to read the graph from a file
void Graph::read_graph(string file_name) {

	// Open the file and read the first line
	ifstream inFile;
	inFile.open(file_name);

	int i, j;
	double Cij;
	inFile >> i;

	// Read file line by line (in principle only the upper diagonal is in file)
	while ( inFile >> i >> j >> Cij ) {
		val_nodes[i][j] = i;
		val_edges[i][j] = val_edges[j][i] = Cij;
	}

	// Close File
	inFile.close();

}

// Resize vectors to save nodes and edges
void Graph::resize_storage() {
	val_nodes.resize(n_nodes, vector<int>(n_nodes));
	val_edges.resize(n_nodes, vector<double>(n_nodes));
	g.resize(n_nodes, vector<bool>(n_nodes));
}
