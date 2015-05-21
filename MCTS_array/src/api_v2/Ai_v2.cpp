#include "Ai.h"

#define CLOCKTOCK 1000

using namespace mcts;

namespace api_v2 {
/*
	mcts::MctsArgs* _param;
	mcts::Mcts* _ai;
	Bitboard* _board;
	TheGame* _game;

*/
	Ai::Ai() : _param(new MctsArgs()), _ai(nullptr), _game(new Connect4()), _board(new BitboardConnect4())
	{
		_ai = new Mcts(_game, _board, _param);	
	}

	Ai::Ai(prog_options& options) : _param(new MctsArgs(options)), _ai(nullptr), _game(new Connect4()), _board(new BitboardConnect4())
	{
		_ai = new Mcts(_game, _board, _param);	
	}

	void Ai::setThinkingTime(int t)
	{
		_param->set_time_limit_simulation_per_root(t * CLOCKTOCK);
	}

	double Ai::getThinkingTime()
	{
		return _param->get_time_limit_simulation_per_root() / CLOCKTOCK;
	}

	void Ai::makeMove(u_long move)
	{
		auto m = Move(move);
		_ai->update_root();
		_ai->move_played(m);
	}

	double Ai::estimateWinChances()
	{
		return _ai->winning_chances();
	}

	v_stat Ai::getMovesStatistics()
	{
		return _ai->get_moves_statistics();
	}

	void Ai::explore(){
		_ai->get_best_move();
	}

	void Ai::exploreSingle()
	{
		_ai->explore();
	}

	void Ai::displayASCII()
	{
		_game->diplay_board(_ai->get_current_bitboard());
	}

	std::vector<u_long> getState()
	{
		return _ai->get_current_bitboard()->serialize();
	}

	void setState(std::vector<u_long> state)
	{
		_ai->kill_tree();
		_ai->get_current_bitboard()->import(state);
	}

}