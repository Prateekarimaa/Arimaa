#pragma once
#include <iostream>
#include <sstream>
#include "Screen.h"
#include "InputHandler.h"
#include "ResourceManager.h"
#include "ConfigOptions.h"
#include "PieceSprite.h"
#include "../Model/Game.h"
#include "TurnSign.h"
#include "Highlighter.h"
#include "PlacementUI.h"

#define NULL_SQUARE sf::Vector2i(-1,-1)

class GameScreen :
	public Screen
{
public:
	GameScreen(unsigned int myID);
	int update (sf::RenderWindow &app);
	void draw (sf::RenderWindow &app);
	void initialize ();
	void uninitialize ();
	~GameScreen(void);

private:
	InputHandler* m_iHandler;
	sf::Sprite m_background;
	BoardAlignedSprite m_cursor;
	BoardAlignedSprite m_selectionSprite;
	BoardAlignedSprite m_targettingSprite;
	std::map<PiecePtr, PieceSprite> m_pieces;
	std::vector<PiecePtr> m_disappearingPieces; //dead pieces that are still disappearing
	sf::Sprite m_goldTurnIndicator;
	sf::Sprite m_silverTurnIndicator;
	TurnSign m_turnSign;
	sf::Sprite m_nbMovesSprite;
	sf::Sprite m_movesBackgroundSprite;
	Highlighter m_highlighter;
	PlacementUI m_placementUI;
	sf::Sprite m_victorySign;

	PieceType m_selectedType;
	sf::Vector2i m_selectedPiece;
	sf::Vector2i m_selectedTarget;
	Color m_victor;

	Game m_game;

	bool playerHasHand() const;
	inline bool isOver() const { return m_victor != NB_PLAYERS; }

	void clickOn(sf::Vector2i s);
	void place(sf::Vector2i s);
	void remove(sf::Vector2i s);
	bool select(sf::Vector2i s); //returns true if a move is made
	void unselect();

	void selectPiece(sf::Vector2i s); //call only if there is a piece there
	void selectTarget(sf::Vector2i s); //call only if there is a piece there
	inline void selectPieceType(PieceType t) { if(m_placementUI.select(t)) m_selectedType = t; }
	bool tryAndEndTurn(); //works only in placement phase

	void updatePositionsAndDeath();
	void updateNbMoves();
	inline void updatePieceAvailability(PieceType type) { m_selectedType = m_placementUI.setAvailability(type, m_game.getNbRemaining(type) != 0); }
	inline void killPieceSprite(PiecePtr p) { m_disappearingPieces.push_back(p); m_pieces[p].startDisappearing(); }
	void clearAll();
	void refreshAll();
	void setVictor(Color victor);

	static inline sf::Vector2i toVector(const Square& s) { return sf::Vector2i(s.x, s.y); }
	static inline Square toSquare(const sf::Vector2i& v) { return Square(v.x, v.y); }
	static inline bool isValid(sf::Vector2i s) { return (s.x >= 0 && s.y >= 0 && s.x < 8 && s.y < 8); }

	static sf::Vector2i m_cardinals[];
	static bool areAdjacent(sf::Vector2i p1, sf::Vector2i p2);
};
