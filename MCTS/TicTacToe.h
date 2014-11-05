/**
 * \file TicTacToe.h
 * \brief Define class TicTacToe
 * \author Benoit Viguier
 * \version 1.0
 * \date October 30th 2014
 *
 */
#pragma once
#include <algorithm>
#include "TheGame.h"
#include "Random.h"

using std::string;
using std::list;

class TicTacToe : public TheGame
{

public:
	TicTacToe() {}

	virtual ~TicTacToe() {}

	/**
	 * \fn end
	 * \brief check if the game end
	 * \details returns 1 if player 1 wins
	 * returns 2 if player 2 wins
	 * returns 3 if the game is a tie
	 * returns 0 if the game hasn't ended yet
	 * \return integer corresponding to the state of the Board
	 */
	virtual int end(const Bitboard& board) override;

	/**
	* \fn play
	* \brief simulate the play of the "position" move and returns the bitboard after the move
	*
	* \param position move to be play
	* \param board board to be used to play
	* \return the Bitboard after the play
	*/
	virtual void play(Move& position, Bitboard& board) override;

	/**
	 * \fn diplayBoard
	 * \brief display the board of the given Bitboard
	 * 
	 * \param board Bitboard to be displayed
	 */
	virtual void diplayBoard(const Bitboard& board) override;

	/**
	* \fn listPossibleMoves
	* \brief return a list of all possible moves given a board
	*
	* \param board Bitboard to be looked at
	* \return the list of the possible moves
	*/
	virtual list<Move> listPossibleMoves(const Bitboard& board) override;

	virtual int playRandomMoves(Bitboard& board) override;
};

