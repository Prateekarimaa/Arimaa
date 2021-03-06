#define OPENMP

#include "Mcts.h"
#define elseif else if
#define OPTIMIZED_MCTS
#include <time.h>

//#define DEBUG_MCTS
//#define DISPLAY_MCTS

using std::list;
using std::cout;
using std::endl;

namespace mcts{

	Mcts::Mcts()
	{
	}

	Mcts::Mcts(	TheGame* game,
				Bitboard* Bb,
				MctsArgs* args)
				:_game(game), _root(new Node(Bb)), _param(args), _maxdepthreached(false)
	{
		FreeObjects<Node>::I()->set(2000000);
	}

	Bitboard* Mcts::movePlayed(Move& move)
	{
		UpdateNode(_root);
		list<Node*> ListOfNodes = _root->getChildren();
		list<Node*>::iterator iterN;
		for (iterN = ListOfNodes.begin(); iterN != ListOfNodes.end(); ++iterN)
		{
			if ((*iterN)->getMove() == move) // we got the move played !
			{
				break;
			}
		}
		// TO CHECK AND IMPROVE
		_root->killChildrens(*iterN);
		_root->unset();
		FreeObjects<Node>::I()->storeNode(_root);
		_root = *iterN;
		ListOfNodes.clear();
		_root->clearParents();

		return _root->getState();
	}

	int Mcts::UpdateNode(Node* node)
	{
		Bitboard* Bb = node->getState();
		int nodet = node->getTerminal();

		if (nodet == -1) { // first time we are here, check if terminate
			nodet = _game->end(Bb);
			node->setTerminal(nodet);
		}

		if (nodet == 0 && !node->getChildren().empty())
		{
			return nodet;
		}

		#pragma omp critical
		if (node->getChildren().empty()) // not explored yet => explore
		{
			list<Move> ListOfMoves;
			list<Move>::iterator iter;

			Bitboard* Bb2;

			ListOfMoves = _game->listPossibleMoves(Bb);
			for (iter = ListOfMoves.begin(); iter != ListOfMoves.end(); ++iter)
			{
				Bb2 = Bb->clone();
				_game->play(*iter, Bb2);
				node->addChild(Bb2, *iter);
			}
		}

		return nodet;
	}

	void Mcts::playRandom(Node* node)
	{
		int nodet;
		for (int i = 0; i < _param->getSimulationPerLeaves(); ++i)
		{
#ifdef DEBUG_MCTS
			cout << endl << "round n " << (i + 1) << endl;
#endif // DEBUG_MCTS
			Bitboard* Bb = node->getState()->clone();
			nodet = _game->playRandomMoves(Bb);
			delete Bb;
			node->update(nodet);
		}
	}


	void Mcts::explore()
	{
		Node* node = _root;
		int depth = 0;
		int nodet;
//		#pragma omp critical
		nodet = UpdateNode(node); // update and exploration
		while (depth < _param->getDepth() && nodet <= 0 && node->getVisits() > _param->getNumberOfVisitBeforeExploration())
		{
			node = node->select_child_UCT();
//			#pragma omp critical
			nodet = UpdateNode(node);
#ifdef DISPLAY_MCTS
			if (depth == 0)
			{
				cout << endl << "Node to explore : " << endl;

			}
			cout << node->getMove() << " > ";
#endif // DISPLAY_MCTS
			++depth;
			if (depth == _param->getDepth() && !_maxdepthreached)
			{
				_maxdepthreached = true;
				cout << endl << "max depth reached : " << _param->getDepth() << "moves ahead.";
			}
		}

		if (nodet <= 0) // no victory found yet
		{
#ifdef DISPLAY_MCTS
			cout << endl << "depth reached : start random";
#endif // DISPLAY_MCTS
			playRandom(node);
		}
#ifdef OPTIMIZED_MCTS
		elseif(nodet < 3 && nodet > 0 && nodet != node->getState()->getPlayer()) // losing move !
		{
			node->forceSetUCT(10);
			feedbackWinningMove(node);
			node->update(nodet);
		}
#endif //OPTIMIZED_MCTS
		else
		{
			node->update(nodet);
		}
	}

	void Mcts::updateLosingParent(Node* node) // for each parent check if uct = -1 => if yes it's a winning move for the opponent, he has to play here : uct = 10
	{
		list<Node*> ListParents;
		list<Node*> ListChilds;
		list<Node*>::iterator iter;
		list<Node*>::iterator iter2;
		bool loser;
		ListParents = node->getParents();
		for (iter = ListParents.begin(); iter != ListParents.end(); ++iter)
		{
			loser = true;
			ListChilds = (*iter)->getChildren();
			for (iter2 = ListChilds.begin(); (iter2 != ListChilds.end() && loser); ++iter2)
			{
				if ((*iter2)->getUCT() != -1) { loser = false; }
			}
			if (loser)
			{
				(*iter)->forceSetUCT(10);
				feedbackWinningMove(*iter);
			}
		}
	}

	void Mcts::feedbackWinningMove(Node* node) // if someone has a winning move given a position, we must not go to that position.
	{
		if (node->getUCT() != 10) return;
		list<Node*> ListParents;
		list<Node*>::iterator iter;
		ListParents = node->getParents();
		for (iter = ListParents.begin(); iter != ListParents.end(); ++iter)
		{
			(*iter)->forceSetUCT(-1);
			updateLosingParent(*iter);
		}
	}

	Move Mcts::GetBestMove()
	{
#ifdef DISPLAY_MCTS
		cout << endl << "turn : " << _root->getState()->getPlayer();
#endif // DISPLAY_MCTS
		_maxdepthreached = false;
		int i = 0;
		int start = clock();
		int timeend = start + (static_cast<double>(_param->getTimeLimitSimulationPerRoot()) / 1000 * CLOCKS_PER_SEC);
#ifdef OPENMP
#pragma omp parallel shared(i,timeend)
#endif
		while (clock() < timeend && i < _param->getSimulationPerRoot())
		{
			i++;
#ifdef DISPLAY_MCTS
			cout << endl << "simulation n : " << i;
#endif // DISPLAY_MCTS
			explore();
		}
		cout << endl << "start search : " << static_cast<double>(start) / CLOCKS_PER_SEC << "s.";
		cout << endl << "end search : " << static_cast<double>(clock()) / CLOCKS_PER_SEC << "s in " << static_cast<double>(clock() - start) * 1000 / CLOCKS_PER_SEC << "ms and " << i << " simulations." << endl;
		return _root->select_child_WR()->getMove();
	}

	void Mcts::print_tree(int depth)
	{
		auto d = (depth == 0) ? _param->getDepth() : depth;
		_root->print_tree(0, d);
	}

	void Mcts::kill_tree()
	{
		_root->killChildrens(nullptr);
	}

	void Mcts::get_Number_Leaves()
	{
		Count::I()->saveNbLeaves(_root->count());
		Count::I()->saveMaxDepth(_root->max_depth());
	}

	double Mcts::winning_Strategy()
	{
		return (_root->getUCT() != 10 && _root->getUCT() != -1) ? _root->getProba() : _root->getUCT();
	}
}