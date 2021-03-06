#include "Game.h"
#include "Ai.h"

using namespace api;
using namespace std;

inline void test_api()
{
	Game* game = new Game();
	Ai* ai = new Ai(2);
	TheGame* g = game->getGame();
	
	ai->init(game);

	g->diplayBoard(game->getBitboard());

	game->makeMove(4);

	g->diplayBoard(game->getBitboard());

	cout << game->makeMove(ai->makeMove(true)) << endl;
	g->diplayBoard(game->getBitboard());

	game->makeMove(4);
	cout << game->makeMove(ai->makeMove(true)) << endl;
	g->diplayBoard(game->getBitboard());

	game->makeMove(4);
	cout << game->makeMove(ai->makeMove(true)) << endl;
	g->diplayBoard(game->getBitboard());

	game->makeMove(4);
	g->diplayBoard(game->getBitboard());

	cout << game->canMakeMove(4) << endl;
	cout << game->colHeight(4) << endl;

	delete game;
	delete ai;
	
	cout << "test 1 passed" << endl;
	game = new Game();
	ai = new Ai(2);
	g = game->getGame();

	ai->init(game);
	g->diplayBoard(game->getBitboard());

	game->makeMove(4);
	game->makeMove(3);

	game->makeMove(3);
	game->makeMove(3);

	game->makeMove(1);
	game->makeMove(2);

	game->makeMove(1);
	game->makeMove(2);

	game->makeMove(1);
	game->makeMove(4);

	game->makeMove(2);
	game->makeMove(4);

	game->makeMove(4);
	game->makeMove(4);

	game->makeMove(3);
	game->makeMove(3);

	game->makeMove(2);
	game->makeMove(2);

	game->makeMove(1);

	g->diplayBoard(game->getBitboard());
	cout << game->getWinner() << endl;
	cout << "test 2 passed" << endl;
	auto wl = game->getWinningLine();
	for (auto it = wl.begin(); it != wl.end(); ++it)
	{	
		cout << (*it).first << ";" << (*it).second << endl;
	}
}