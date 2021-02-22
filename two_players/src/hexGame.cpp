//============================================================================
// Name        : hexGame.cpp
// Author      : Carlos Granados
// Version     : 1.0
// Date        : 11.02.2021
// Copyright   : GNU
// Description : First implementation of a game of Hex, using graphs.
//				 For 2 players. The program can draw the board using ASCII
//				 symbols for a given size; determine if a move is legal and
//				 determine who won.
//============================================================================

#include <iostream>

#include "hexGraph.h"
#include "player.h"

using namespace std; // @suppress("Symbol is not resolved")



// Functions to test the code

// Function to simulate one player.
// Used to verify the winning conditions
void verify_one(const int graph_size) {

	hexGraph hg0(graph_size);
	hg0.print();

	Player player_one(1);

	// Small code to test the conditions to win...
	for (int i = 0; i < graph_size; i++) {
		cout << "i = " << i << endl;
//	    if (i == 3)
//	    	continue;
	    coordBoard p = make_pair(i, 0);
	    player_one.set_pos(p, hg0);
	    hg0.set_move(player_one.get_player(), player_one.get_pos());
	}
	hg0.print();
	cout << "Verifying who won" << endl;
	if (player_one.player_won(hg0))
		cout << "Player One Won!" << endl;

}

// Function to run the code for two players
void two_players(const int graph_size) {

	int i = 0, j = 0;

	Player players [2] = {Player(1), Player(2)};
	hexGraph hg0(graph_size);

	// Initialize graph and print empty board
	hg0.make_graph();
	hg0.print();

	// Start playing
	int count = 0;
	bool setted;
	while (i != -1 && j != -1) {
		int id_current = count % 2;
	    int id_other = (count + 1) % 2;
	    // Set the coordinated for a new move. If not, exit loop
	    setted = (players[id_current]).set_coords(hg0, players[id_other]);
	    if (! setted)
	      break;
	    // If it is a valid move, then add to the graph and show it
	    hg0.set_move(players[id_current].get_player(), players[id_current].get_pos());
	    hg0.print();
	    if (players[id_current].player_won(hg0)) {
	      cout << "Player " << id_current + 1 << " won!" << endl;
	      break;
	    }
	    count++;
	  }
}


// MAIN function

void main() {

	int i = 0, j = 0, b_size;

	Player players [2] = {Player(1), Player(2)};

	cout << "Easy implementation of Hex game" << endl;;
	cout << "Enter board size:" << endl;
	cin >> b_size;
	cout << endl;

	/*
	// To test verification of whom won the match. 1 player
	verify_one(b_size);
	*/

	// For 2 players. Each step the code is verifying if a given player win or not
	two_players(b_size);

	cout << "Have a nice day!" << endl;

}
