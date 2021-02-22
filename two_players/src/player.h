//============================================================================
// Name        : player.h
// Author      : Carlos Granados
// Version     : 1.0
// Date        : 11.02.2021
// Copyright   : GNU
// Description : Class to create a player object. Get and set the moves,
//				 and check if a given player won
//============================================================================

#include <queue>

#include "hexGraph.h"



//------------------------------------------------------------------------------
// class Player
//------------------------------------------------------------------------------

// This class save the information related to each player, particularly the
// last played position and saves all played positions as well

class Player {

	public:

	Player();
	Player(int i);

//	~Player();

	// Methods

	// Setters and getters

	// Returns the last played position
	coordBoard get_pos() {
		return last_move;
	}

	// Returns the player ID
	int get_player() {
		return self_id;
	}

	// Function to set a played position
	void set_pos(coordBoard const move, hexGraph g);

	// Function to read the next move for player. If not valid, ask again for the
	// Coordinates
	bool set_coords(hexGraph g, Player other_player);

	// Other methods

	// Check if the new move is valid (not played befor for any player)
	bool valid_move(coordBoard const move, Player other_player);

	// Check if the player already played the selected move (coord)
	bool played(coordBoard const move);

	// Function to determine if a move is in the border (to get a starting or ending point)
	// NOTE: I have to write separate cases, get<> needs constant values...
	void chk_border(coordBoard const move, hexGraph g);

	// Function to determine if player had complete the game (won): N-S or W-E
	bool player_won(hexGraph g);

	// Function to determine if a path is complete (N-S or W-E)
	bool chk_player_path(hexGraph g);

	protected:

	int self_id;
	set<coordBoard> pos_marks;
	coordBoard last_move;

	private:

	// Used to define the start and ending points of the full path: N-S or W-E
	coordBoard start_path = make_pair(-1, -1);
	coordBoard end_path = make_pair(-1, -1);

	// Used to verify the visited nodes
	priority_queue<coordBoard> visited;

	// Function to verify if elem is in set s
	bool elem_in_set(const coordBoard c, set<coordBoard> s);

	// Function to count the number of visited neighbors
	int count_neighbors(set<coordBoard> neighbors);

	// Function to check if the path is walkable from the start to
	// the end points (complete)
	bool is_walkable(hexGraph g);

};
