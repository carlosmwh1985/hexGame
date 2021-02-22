//============================================================================
// Name        : player.cpp
// Author      : Carlos Granados
// Version     : 1.0
// Date        : 11.02.2021
// Copyright   : GNU
// Description : Implementation of class Player
//============================================================================

#include <iostream>

#include "hexGraph.h"
#include "player.h"



//------------------------------------------------------------------------------
// Implementation of class Player
//------------------------------------------------------------------------------


Player::Player() {
	self_id = 0;
}

Player::Player(int i) {
	self_id = i;
}

// Methods

// Setters and getters

// Function to set a played position
void Player::set_pos(coordBoard const move, hexGraph g) {
	pos_marks.insert(move);
	last_move = move;
	chk_border(move, g);
}

// Function to read the next move for player. If not valid, ask again for the
// Coordinates
bool Player::set_coords(hexGraph g, Player other_player) {
	int i, j;
	// Get Coords
	cout << "Player " << self_id << " move (-1, -1 to exit):" << endl;
	cin >> i >> j;

	// Exit program
	if (i == -1 && j == -1)
		return false;

	coordBoard move = g.check_coords(i, j);

	bool valid = valid_move(move, other_player);

	// If not a valid move, call again
	if (valid) {
		set_pos(move, g);
	}
	else {
		cout << "Not a valid move. Try again!" << endl;
		set_coords(g, other_player);
	}

	return true;
}

// Other methods

// Check if the new move is valid (not played befor for any player)
bool Player::valid_move(coordBoard const move, Player other_player) {

	// Check if the other player has play it already
	bool check_other = other_player.played(move);
	bool check_self = played(move);

	if (check_other || check_self) {	// Played before...
		cout << "Move already played!" << endl;
		return false;
	}
	else {			 					// Not played before
		return true;
	}

	return false;
}

// Check if the player already played the selected move (coord)
bool Player::played(coordBoard const move) {
	return elem_in_set(move, pos_marks);		// Check if move is in the list of the visited positions
}

// Function to determine if a move is in the border (to get a starting or ending point)
// NOTE: I have to write separate cases, get<> needs constant values...
void Player::chk_border(coordBoard const move, hexGraph g) {
	int size = g.get_size();
	int pos = -1;

	// Get 1st or 2nd coordinate for a given move, depending on player ID
	if (self_id == 1 ) {              // First player. Moves N-S (rows)
		pos = get<0>(move);
	}
	else if (self_id == 2) {          // Second player. Moves W-E (cols)
		pos = get<1>(move);
	}

	// Check if such coordinate correspond to a border. If it is, assign move
	// to the corresponding variable (only 1st time)
	if (pos == 0 && get<0>(start_path) == -1) {           // Starting point
		start_path = move;
	}
	else if (pos == size-1 && get<0>(end_path) == -1) {  // Ending point
		end_path = move;
	}
}

// Function to determine if player had complete the game (won): N-S or W-E
bool Player::player_won(hexGraph g) {

	// Path does not have yet any extreme points (N+S or W+E)
	if (!elem_in_set(start_path, pos_marks) || !elem_in_set(end_path, pos_marks))
		return false;

	// Not enough points to make a full path...
	if (pos_marks.size() < g.get_size())
		return false;

	return chk_player_path(g);
}

// Function to determine if a path is complete (N-S or W-E)
bool Player::chk_player_path(hexGraph g) {

	// Check if the visited queue is empty
	while (!visited.empty())
		visited.pop();

	// Starting from N or W, verify if the path is complete (walkable
	// from start to end), If it is, the path is complete
	return is_walkable(g);

}

// Function to count the number of visited neighbors
int Player::count_neighbors(set<coordBoard> neighbors) {

	int count = 0;

	for (auto n : neighbors) {
		// If the given neighbor n is in the marked positions, add it to the queue
		count = 0;
		if (elem_in_set(n, pos_marks)) {
			visited.push(n);
			count++;
		}
	}

	return count;
}

// Function to check if the path is walkable from the start to
// the end points (complete)
bool Player::is_walkable(hexGraph g) {

	coordBoard pos = start_path;
	visited.push(pos);

	while (!visited.empty()) {
		// Get and delete from the queue the first position
		pos = visited.top();
		visited.pop();

		// Get all neighbors for the position in the queue
		set<coordBoard> neighbors = g.get_neighbors(pos);

		// If end_point is in the list of neighbors, the search is ended,
		// because end_path must be already in the played positions!
		if (elem_in_set(end_path, neighbors))
			break;

		int count = count_neighbors(neighbors);

		// If no neighbors were added, the path is not complete
		if (count == 0 && pos != end_path)
			return false;
	}

	// Start and ending positions are in the path, and all points are connected.
	// I assume then that the path is complete and Player won the match!
	return true;
}

// Function to verify if elem is in set s
bool Player::elem_in_set(const coordBoard c, set<coordBoard> s) {
	if (s.find(c) == s.end())
		return false;
	return true;
}
