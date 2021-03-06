#include "Move.h"

Move::Move(Square position, Square destination, int cost) : m_position(position), m_destination(destination), m_cost(cost)
{
}

Move::~Move(void)
{
}

bool Move::isPossible(const Board& b, Color player, int movesLeft) const
{
	if(!isValid())
		return false;
	if(movesLeft < m_cost) //not enough moves left
		return false;
	if(b.isFrozen(m_position) || b.getPiece(m_position)->getColor() != player) //there is no piece to move (or it is frozen) or it is the wrong color
		return false;
	if(b.getPiece(m_position)->getType() == RABBIT) //if the piece is a rabbit, forbids it to go backwards
	{
		//figuring out where backwards is
		Square backwards(0,0);
		if(player == GOLD)
			backwards.y -= 1;
		else //SILVER
			backwards.y += 1;
		if(m_destination == m_position + backwards) //going backwards
			return false;
	}
	return b.isFree(m_destination); //rturns true if the destination is free
}

bool Move::execute(Board& b, Color player, int& movesLeft) const
{
	if(!isPossible(b, player, movesLeft))
		return false;

	b.movePiece(m_position, m_destination);
	movesLeft -= m_cost;

	return true;
}

bool Move::isValid() const
{
	return Board::isValid(m_position) && Board::isValid(m_destination) && Board::areAdjacent(m_position, m_destination);
}