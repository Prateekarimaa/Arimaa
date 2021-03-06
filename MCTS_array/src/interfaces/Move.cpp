#include "Move.h"


using std::string;
using std::ostream;
using std::istream;

Move::Move()
{
	_data = 0;
}

Move::Move(string move) : _data(strtol(move.c_str(), nullptr, 10))
{
}

Move::Move(int move) : _data(move)
{
}

Move::Move(u_long move) : _data(move)
{
}

Move::~Move()
{
}


ostream& operator<<(ostream& stream, Move& move)
{
	stream << move.get();
	return stream;
}

istream& operator>>(istream& stream, Move& move)
{
	u_long data;
	stream >> data;
	move.set(data);
	return stream;
}