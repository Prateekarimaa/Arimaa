#include "Ai.h"
#include "../tools/Count.h"

using namespace mcts;

namespace api {
	Ai::Ai(int t) :_param(new MctsArgs(40, t*CLOCK)), _ai(nullptr), _game(nullptr)
	{
	}

	void Ai::setThinkingTime(int t)
	{
		_param->setTimeLimitSimulationPerRoot(t * CLOCK);
	}

	int Ai::getThinkingTime()
	{
		return _param->getTimeLimitSimulationPerRoot() / CLOCK;
	}

	void Ai::init(Game* g)
	{
		if (_ai != nullptr)
		{
			_ai->kill_tree();
			delete _ai;
		}
		_game = g;
		_ai = new Mcts(_game->getGame(), _game->getBitboard()->clone(), _param);
		// clone of the BitBoard because it will be deleted once the root is destroyed
	}

	int Ai::makeMove(bool player)
	{
		if(player){
			auto m = Move(_game->getLastMove());
			_ai->UpdateRoot();
			_ai->movePlayed(m);
			//	_ai->get_Number_Leaves();
		}
		auto m = _ai->GetBestMove();
//		_ai->get_Number_Leaves();
		_ai->print_tree(2);
		_ai->movePlayed(m);
//		_ai->get_Number_Leaves();
		Count::I()->clear();
		return m.getInt();
	}

	double Ai::estimateWinChances()
	{
		return _ai->winning_Strategy();
	}
}


