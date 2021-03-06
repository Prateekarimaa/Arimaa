#include "Connect4.h"

//#define DISPLAY_C4
using std::string;
using std::list;

Connect4::Connect4()
{
}

int Connect4::end(const Bitboard* board)
{
	int res = check_horizontal(board);
	if (res > 0)
	{
		return res;
	}

	res = check_vertical(board);
	if (res > 0)
	{
		return res;
	}

	res = check_fst_diag(board);
	if (res > 0)
	{
		return res;
	}

	res = check_snd_diag(board);
	if (res > 0)
	{
		return res;
	}

	return check_null(board);
}

int Connect4::check_horizontal(const Bitboard* board)
{
	u_long boardused = static_cast<u_long>(15); // 0001111 in binary
	u_long board1 = board->get_board(0);
	u_long board2 = board->get_board(1);
	for (int y = 0; y < SIZEY; y++)
	{
		for (int x = 0; x <= SIZEX - 4; x++)
		{
			if ((boardused & board1) == boardused)
			{
				return 1;
			}
			elseif((boardused & board2) == boardused)
			{
				return 2;
			}
			boardused <<= 1;
		}
		boardused <<= 3;
	}
	return 0;
}

int Connect4::check_vertical(const Bitboard* board)
{
	u_long boardused = static_cast<u_long>(1);
	boardused += (boardused << SIZEX) + (boardused << (SIZEX * 2)) + (boardused << (SIZEX * 3));

	u_long board1 = board->get_board(0);
	u_long board2 = board->get_board(1);
	for (int y = 0; y <= SIZEY - 4; y++)
	{
		for (int x = 0; x < SIZEX; x++)
		{
			if ((boardused & board1) == boardused)
			{
				return 1;
			}
			elseif((boardused & board2) == boardused)
			{
				return 2;
			}
			boardused <<= 1;
		}
	}
	return 0;
}

int Connect4::check_fst_diag(const Bitboard* board)
{
	u_long boardused = static_cast<u_long>(1);
	boardused += (boardused << (SIZEX + 1)) + (boardused << ((SIZEX + 1) * 2)) + (boardused << ((SIZEX + 1) * 3));

	u_long board1 = board->get_board(0);
	u_long board2 = board->get_board(1);
	for (int y = 0; y <= SIZEY - 4; y++)
	{
		for (int x = 0; x <= SIZEX - 4; x++)
		{
			if ((boardused & board1) == boardused)
			{
				return 1;
			}
			elseif((boardused & board2) == boardused)
			{
				return 2;
			}
			boardused <<= 1;
		}
		boardused <<= 3;
	}
	return 0;
}

int Connect4::check_snd_diag(const Bitboard* board)
{
	u_long boardused = static_cast<u_long>(1);
	boardused <<= 3; // 1000
	boardused += (boardused << (SIZEX - 1)) + (boardused << ((SIZEX - 1) * 2)) + (boardused << ((SIZEX - 1) * 3));

	u_long board1 = board->get_board(0);
	u_long board2 = board->get_board(1);
	for (int y = 0; y <= SIZEY - 4; y++)
	{
		for (int x = 0; x <= SIZEX - 4; x++)
		{
			if ((boardused & board1) == boardused)
			{
				return 1;
			}
			elseif((boardused & board2) == boardused)
			{
				return 2;
			}
			boardused <<= 1;
		}
		boardused <<= 3;
	}
	return 0;
}

int Connect4::check_null(const Bitboard* board)
{
	u_long boardused = static_cast<u_long>(0);
	boardused = ~boardused;
	boardused >>= 22; // full board
	if (((board->get_board(0) | board->get_board(1)) & boardused) == boardused)
	{
		return 4;
	}
	return 0;
}

void Connect4::play(Move& position, Bitboard* board)
{
	u_long boardused = board->get_board(0) | board->get_board(1); // get what places are used.
	boardused >>= (SIZEX - position.get_move());
	int i = 0;
	while( (boardused & 1) == 1)
	{
		i++;
		boardused >>= SIZEX;
	}
	
	board->setBit(board->get_player() - 1, SIZEX - static_cast<int>(position.get_move()), i);
	board->play();
}

void Connect4::diplay_board(const Bitboard* board)
{
	u_long board0 = board->get_board(0); // get what places are used.
	u_long board1 = board->get_board(1);
	u_long check = static_cast<u_long>(1);
	check = check << (SIZEX * SIZEY - 1);

	std::stringbuf buffer;
	std::ostream os(&buffer);
	os << std::endl;
	for (int y = (SIZEY - 1); y >= 0; --y)
	{
		for (int k = 0; k < SIZEX; ++k) os << "+---";
		os << "+" << std::endl;
		for (int x = 0; x < SIZEX; ++x)
		{
			os << "| ";
			if ((board0 & check) == check)
			{
				os << "O";
			}
			elseif((board1 & check) == check)
			{
				os << "X";
			}
			else
			{
				os << " ";
			}
			os << " ";
			check >>= 1;
		}
		os << "|" << std::endl;
	}
	for (int k = 0; k < SIZEX; ++k) os << "+---";
	os << "+" << std::endl;
	for (int k = 1; k <= SIZEX; ++k) os << "  " << k << " ";
	os << std::endl;
	std::cout << buffer.str() << std::endl;

}

list<Move> Connect4::list_possible_moves(Bitboard* board)
{
	list<Move> moves;
	list<int> listmoves = board->get_empty(0);
	list<int>::iterator iter;
	for (iter = listmoves.begin(); iter != listmoves.end(); ++iter)
	{
		moves.push_front(Move(*iter));
	}
	listmoves.clear();
	return moves;
}

int Connect4::play_random_moves(Bitboard* board)
{
	list<int> ListOfMoves;
	list<int>::iterator iter;
	int chosen, nodet;

	nodet = end(board);

	while (nodet < 1)
	{
		ListOfMoves = board->get_empty(0);
		chosen = Random::I()->get_min_max(0, static_cast<int>(ListOfMoves.size()) - 1);
		iter = ListOfMoves.begin();
		advance(iter,chosen);
#ifdef DISPLAY_C4
		std::cout << " > " << *iter ;
#endif // DISPLAY_C4
		u_long boardused = board->get_board(0) | board->get_board(1); // get what places are used.
		boardused >>= (SIZEX - *iter);
		int i = 0;
		while ((boardused & 1) == 1)
		{
			i++;
			boardused >>= SIZEX;
		}
		board->setBit(board->get_player() - 1, SIZEX - *iter, i);
		board->play();
		nodet = end(board);
		ListOfMoves.clear();
	}

	return nodet;
}