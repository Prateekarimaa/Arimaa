/**
 * \file Bitboard.h
 * \brief Define class Bitboard
 * \author Benoit Viguier
 * \version 1.0
 * \date October 30th 2014
 *
 */
#pragma once
#include <stdint.h>
#include <vector>
#include <list>
#include "../tools/Count.h"

/**
 * \brief Bitboard class
 * \details vector<unsigned long> _boards : bitboards of the game;
 *	short _toplay : player to play (1 or 2);
 *	short _number : number of bitboards;
 *	short _sizeX  : number of rows of the bitboards;
 *	short _sizeY  : number of lines of the bitboards;
 */
typedef uint64_t numtyp;

class Bitboard
{

protected:
	std::vector<numtyp> _boards;
	short _toplay;
	short _number;
	short _sizeX;
	short _sizeY;

public:
	/**
	 * \fn Bitboard
	 * \brief Default constructor
	 */
	Bitboard();

	/**
	 * \fn Bitboard
	 * \brief Constructor of the Bitboard given the sizes and number of bitboards to store.
	 * 
	 * \param sizeX	 : number of rows
	 * \param sizeY	 : number of lines
	 * \param n		 : number of boards to be created
	 * \param toplay : player to play
	 */
	Bitboard(int sizeX, int sizeY, int n, int toplay);

	/**
	 * \fn ~Bitboard
	 * \brief Destructor of the class
	 */
	virtual ~Bitboard();

	/**
	* \fn clone
	* \brief clone a Bitboard
	*/
	virtual inline Bitboard* clone() const
	{
		Count::I()->addBitBoards();
		return new Bitboard(*this);
	}

	/**
	* \fn getSizeX
	* \brief blabla
	*/
	virtual int getSizeX() const
	{
		return _sizeX;
	}

	/**
	* \fn getSizeY
	* \brief blabla
	*/
	virtual int getSizeY() const
	{
		return _sizeY;
	}

	/**
	 * \fn getBit
	 * \brief return the value of the bit on a given board and position
	 * 
	 * \param n bitboard to search
	 * \param x position x
	 * \param y position y
	 * \return the value of the bit (0 or 1)
	 */
	virtual int getBit(int n, int x, int y) const;

	/**
	* \fn getBit
	* \brief return the value of the bit on a given board and position
	*
	* \param n bitboard to search
	* \param pos position of the bit
	* \return the value of the bit (0 or 1)
	*/
	virtual int getBit(int n, int pos) const;

	/**
	 * \fn setBit
	 * \brief set to 1 the bit on a given board and position
	 * 
	 * \param n bitboard to search
	 * \param x position x
	 * \param y position y
	 */
	virtual void setBit(int n, int x, int y);

	/**
	* \fn setBit
	* \brief set to 1 the bit on a given board and position
	*
	* \param n bitboard to search
	* \param pos position of the bit
	*/
	virtual void setBit(int n, int pos);

	/**
	 * \fn clearBit
	 * \brief set to 0 the bit on a given board and position
	 * 
	 * \param n bitboard to search
	 * \param x position x
	 * \param y position y
	 */
	virtual void clearBit(int n, int x, int y);

	/**
	* \fn clearBit
	* \brief set to 0 the bit on a given board and position
	*
	* \param n bitboard to search
	* \param pos position of the bit
	*/
	virtual void clearBit(int n, int pos);

	/**
	* \fn getBoard
	* \brief return the given board
	*
	* \param n board to look for
	* \return board number n
	*/
	virtual inline numtyp getBoard(int n) const { return _boards[n]; };

	/**
	 * \fn getEmpty
	 * \brief list 0 bits of a given board
	 * 
	 * \param n board to look at
	 * \return list of the empty positions (0 to size² -1)
	 */
	virtual std::list<int> getEmpty(int n) const;

	/**
	 * \fn getOccupied
	 * \brief list 1 bits of a given board
	 * 
	 * \param n board to look at
	 * \return list of the set positions (0 to size² -1)
	 */
	virtual std::list<int> getOccupied(int n);

	/**
	* \fn getPlayer
	* \brief return the player to play
	*
	* \return player to play (1 or 2)
	*/
	virtual inline int getPlayer() const { return _toplay; };

	/**
	* \fn play
	* \brief swap players
	*/
	virtual inline void play() { _toplay = (_toplay == 1) ? 2 : 1; };
};

