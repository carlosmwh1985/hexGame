//============================================================================
// Name        : hexGraph.h
// Author      : Carlos Granados
// Version     : 1.0
// Date        : 11.02.2021
// Copyright   : GNU
// Description : Class to create a hex-graph object. Based on the graph class
//============================================================================

#ifndef HEXGRAPH_H
#define HEXGRAPH_H

#include <set>
#include <utility>

#include "graph.h"

//using namespace std;



//------------------------------------------------------------------------------
//  SOME NEEDED DATA TYPES
//------------------------------------------------------------------------------

typedef pair <int, int> coordBoard;



//------------------------------------------------------------------------------
// class hexGraph
//------------------------------------------------------------------------------

class hexGraph : public Graph
{
	public:

	// Constructors
	hexGraph();
	hexGraph(const int n);

	// Destructor
	~hexGraph() {}

	// Methods

	// setters and getters

	// Returns the number of neighbors for a given position
	int get_num_neighbors(coordBoard const coord);

	// Function to get the number of nodes (one side. Total = n*n)
	int get_size();

	// For a given coordinate, it returns a vector with all its neighbors
	set<coordBoard> get_neighbors(coordBoard const coord);

	// For a given player and its new move in coord, add the corresponding mark
	// to the graph
	void set_move(int const player_id, coordBoard const coords);

	// Other methods

	// Check if the value i is inside the board
	bool valid(const int i);

	// Check if the points i and j make a valid coordinate. If true, returns
	// the new coordinate
	coordBoard check_coords(const int i, const int j);

	// Print the hex graph. It clears the screen first
	void print();

	protected:

	char white_space = ' ';
//	string white_space = "   ";
	int num_hex;
	int val_none = 46;				// Print '.'
	int hor_line = 45;              // Print horizontal line, '-'
	int diags [2] = {47, 92};       // Print '\' and '/'

	// Additional methods

	// It adds a coordinate to a set
	void add_pair(set<coordBoard> & all_coords, coordBoard coord);

	// Auxiliary function to print the hex graph. It prints the corresponding
	// mark assigned to each player.
	void print_player(const int i, const int j);

	// Auxiliary function to print white spaces, to make look the graph more like
	// the traditional hexx board. It prints white spaces as the number of the row
	// that precedes it
	void print_white_space(const int i);

	// Auxiliary function to print the diagonal lines for the hex graph after
	// each row...
	void print_lines(const int i);

};

#endif
