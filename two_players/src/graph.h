//============================================================================
// Name        : graph.h
// Author      : Carlos Granados
// Version     : 1.0
// Date        : 11.02.2021
// Copyright   : GNU
// Description : Class to create a graph object.
//============================================================================

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

using namespace std;



//------------------------------------------------------------------------------
// class Graph
//------------------------------------------------------------------------------

class Graph
{
	protected:

	int n_nodes, n_edges=0, id;

	vector<vector<int>> val_nodes;
	vector<vector<double>> val_edges;
	vector<vector<bool>> g;

	// Function to read the graph from a file
	void read_graph(string file_name);

	// Resize vectors to save nodes and edges
	void resize_storage();

	public:
	// Constructors

	Graph();
	Graph(const int n);
	Graph(string file_name);

	// Destructor
	virtual ~Graph() {};

	// getters and setters

	// Get vertices
	int get_num_nodes();

	// Get edges
	int get_e();

	// Returns the value associated with the node x
	int get_node_value(const int i, const int j);

	// Get the value associated to the edge (i, j)
	double get_edge_value(const int i, const int j);

	// Set the value associated with the node i to a
	void set_node_value(const int i, const int j, const int a);

	// Set the value associated to the edge (i, j) to v
	void set_edge_value(const int i, const int j, double v);

	// Other methods

	// Check if the nodes i and j are adjacent (an edge from i to j)
	bool adjacent(const int i, const int j);

	// List all nodes that have an edge from/to i
	virtual void get_neighbors(const int i, int & n, int * neighs);

	// Add an edge between i and j if it is not there
	void add(const int i, const int j);

	// Delete an edge between i and j if it is there
	void del(const int i, const int j);

	// Function to create the graph and initialize it to 0
	void make_graph();

	// Function to print the graph in a matrix form.
	// It prints the values associated to each edge
	virtual void print();

};

#endif
