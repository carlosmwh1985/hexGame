//============================================================================
// Name        : hexGraph.cpp
// Author      : Carlos Granados
// Version     : 1.0
// Date        : 11.02.2021
// Copyright   : GNU
// Description : Implementation of class hexGraph
//============================================================================

#include <iostream>

#include "graph.h"
#include "hexGraph.h"

//using namespace std;



//------------------------------------------------------------------------------
// class hexGraph
//------------------------------------------------------------------------------

hexGraph::hexGraph() { // @suppress("Class members should be properly initialized")
	n_nodes = 0;
}

hexGraph::hexGraph(const int n) {		   // @suppress("Class members should be properly initialized")
	num_hex = n;
	n_nodes = num_hex;

	// Resize the vectors to save nodes and edges
	resize_storage();

	// Initialize the graph to 0
	make_graph();
}


// Methods

// setters and getters

// Returns the number of neighbors for a given position
int hexGraph::get_num_neighbors(coordBoard const coord) {

	// Extract individual values
	int i = coord.first;
	int j = coord.second;

	// Corners
	if (i == 0 && j == 0) {
		return 2;
	}
	else if (i == n_nodes-1 && j == n_nodes-1) {
		return 2;
	}
	else if (i == 0 && j == n_nodes-1) {
		return 3;
	}
	else if (i == n_nodes-1 && j == 0) {
		return 3;
	}

	// Borders
	if (i == 0 || i == n_nodes-1) {
		return 4;
	}
	if (j == 0 || j == n_nodes-1) {
		return 4;
	}

	// All others
	return 6;
}

// Function to get the number of nodes (one side. Total = n*n)
int hexGraph::get_size() {
	return n_nodes;
}


// For a given coordinate, it returns a vector with all its neighbors
set<coordBoard> hexGraph::get_neighbors(coordBoard const coord) {

	int i = coord.first;
	int j = coord.second;

	set<coordBoard>  neighbors;

	int row = i - 1;                          // Upper row
	if (row >= 0) {
		for (int col=j; col <= j+1; col++) {    // col = j, j+1
			coordBoard neigh = make_pair(row, col);
			if (col >= 0 && col < n_nodes)
				add_pair(neighbors, neigh);
		}
	}

	row++;                                    // Current row
	for (int col=j-1; col <= j+1; col++) {    // col = j-1, j+1
		coordBoard neigh = make_pair(row, col);
		if (col == j)
			continue;
		if (col >= 0 && col < n_nodes) {
			add_pair(neighbors, neigh);
		}
	}

	row++;                                    // Lower row
	if (row < n_nodes){                    	  // col = j-1, j
		for (int col=j-1; col <= j; col++) {
			coordBoard neigh = make_pair(row, col);
			if (col >= 0 && col < n_nodes) {
				add_pair(neighbors, neigh);
			}
		}
	}

	return neighbors;

}

// For a given player and its new move in coord, add the corresponding mark
// to the graph
void hexGraph::set_move(int const player_id, coordBoard const coords) {

	int val_i = coords.first;
	int val_j = coords.second;

	if (player_id == 1 || player_id == 2)
		val_nodes[val_i][val_j] = player_id;

}

// Other methods

// Check if the value i is inside the board
bool hexGraph::valid(const int i) {
	if (i >= 0 && i < n_nodes)
		return true;
	return false;
}

// Check if the points i and j make a valid coordinate. If true, returns
// the new coordinate
coordBoard hexGraph::check_coords(const int i, const int j) {
	bool coord_valid = false;
	int new_i = i, new_j = j;

	coord_valid = valid(i) && valid(j);

	while (! coord_valid) {
		cout << "Not a valid move, Coords. out of range. Try again:" << endl;
		cin >> new_i >> new_j;
		coord_valid = (valid(new_i) && valid(new_j));
	}
	return make_pair(new_i, new_j);
}

// Print the hex graph. It clears the screen first
void hexGraph::print() {

	// Clear the screen
	system("clear");
	cout << endl;

	// Loop rows
	for (int i=0; i < n_nodes; i++) {

		// Print white spaces at the beginning of each new line
		print_white_space(i);

		// Loop columns
		for (int j=0; j < n_nodes; j++){
			print_player(i, j);
		}

		// Print diagonal lines between rows
		if (i < n_nodes-1) {
			print_white_space(i);
			print_lines(i);
		}
	}
}

// It adds a coordinate to a set
void hexGraph::add_pair(set<coordBoard> & all_coords, coordBoard coord) {
	all_coords.insert(coord);
}

// Auxiliary function to print the hex graph. It prints the corresponding
// mark assigned to each player.
void hexGraph::print_player(const int i, const int j) {

	int player_in_node = val_nodes[i][j];

	if (player_in_node == 0)
      cout << char(val_none); //<< '(' << i << ',' << j << ')';
    else if (player_in_node == 1)
      cout << "X";
    else if (player_in_node == 2)
      cout << "O";

    if (j < n_nodes - 1)
      cout << white_space << char(hor_line) << white_space;
    else
      cout << endl;

  }

// Auxiliary function to print white spaces, to make look the graph more like
// the traditional hex board. It prints white spaces as the number of the row
// that precedes it
void hexGraph::print_white_space(const int i) {
    int count = 0;
    while (count <= i) {
      cout << white_space;
      count++;
    }
 }

// Auxiliary function to print the diagonal lines for the hex graph after
// each row...
void hexGraph::print_lines(const int i) {
    // first line;
    cout << char(diags[1]) << white_space;
    for (int count=0; count < n_nodes-1; count++) {
      for (auto val : diags)
        cout << char(val) << white_space;
    }
    cout << endl;
}
