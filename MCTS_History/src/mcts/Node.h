/**
 * \file Node.h
 * \brief Define class Node
 * \author Benoit Viguier
 * \version 1.0
 * \date November 2nd 2014
 *
 */
#pragma once
#include <iostream>
#include <list>
#include <algorithm>
#include "Bitboard.h"
#include "Move.h"

namespace mcts
{

	/**
	 * \brief Node class
	 * \details 
		int _visits = number of visits on the node
		int _wins = number of wins on that node
		double _uct = value of uct on the node
		Bitboard _state = current state of the board
		string _move = last move been played
		list<Node*> _children = list of all possible Bitboards after that node;
		list<Node*> _parents = list of all parents, right now there is only 1 parent per node, but in order to improve the algorithm we need to factorise the number of nodes;
	 */
	class Node
	{
		int _visits;
		double _wins;
		int _terminal;
		double _uct;
		Bitboard* _state;
		Move _move;
		std::list<Node*> _children;
		std::list<Node*> _parents;

		/**
		 * \fn UCT
		 * \brief calculate the UCT value of a node and record it.
		 * \details winrate + sqrt(2)*log(total of visit / visits)
		 * if uct is set to 10 => we don't update the value : move that has to be played (win)
		 * if uct is set to -1 => we don't change the value either : move that should not be played (loss)
		 * 
		 * \param visits number of visits on the parent node.
		 */
		inline void UCT(int visits) {
			if (_uct != -1 && _uct != 10)
			{
				_uct = _wins / static_cast<double>(std::max(_visits, 1)) + sqrt(2.0 * log(static_cast<double>(visits + 1)) / std::max(_visits, 1));
			}
#ifdef DEBUG_NODE
			cout << "_uct " << " = " << static_cast<double>(_wins) << " / " << static_cast<double>(max(_visits, 1)) << " + sqrt(2.0 * log( " << static_cast<double>(visits + 1) << " / " << max(_visits, 1) << ")" << endl;
			cout << "_uct = " << _uct << endl;
#endif //DEBUG_NODE

		};

	public :
		/**
		 * \fn Node
		 * \brief Constructor by default.
		 */
//		Node();

		/**
		* \fn Node(Node *parent)
		* \brief i don't know why i created that function...
		*
		* \param state Board to create the node with
		*/
		explicit Node(Bitboard* state);

		/**
		 * \fn Node(Node* p_parent, Bitboard state, string move);
		 * \brief create a Node with parent as parent and move + Bitboard after the move played
		 * 
		 * \param parent parent of the node
		 * \param state Bitboard after the move
		 * \param move move played
		 */
		Node(Node* parent, Bitboard* state, Move& move);

		/**
		 * \fn ~Node
		 * \brief Destructor of the Node
		 * \details call Delete on all the childrens of the node.
		 */
		virtual ~Node();

		/**
		 * \fn killChildrens
		 * \brief kill all the children of a node but the one with the exception adress
		 * 
		 * \param exception Node that we MUST NOT KILL
		 */
		void killChildrens(Node* exception);

		/**
		* \fn setTerminal
		* \brief setter for _terminal
		*
		* \param value of the terminal
		*/
		inline void setTerminal(int terminal) { _terminal = terminal; };

		/**
		* \fn forceSetUCT
		* \brief setter for _uct
		* \details it allows us to force a value to uct : 10 or -1 in order to make sure that some moves must or mustn't be played
		*
		* \param value of the uct
		*/
		inline void forceSetUCT(int uct) { if (_uct == -1) return; _uct = uct; };

		/**
		* \fn getUCT
		* \brief setter for _uct
		* \details it allows us to force a value to uct : 10 or -1 in order to make sure that some moves must or mustn't be played
		*
		* \param value of the uct
		*/
		inline double getUCT() { return _uct; };

		/**
		* \fn getTerminal
		* \brief getter for the childs
		*
		* \return 0 if not, 1 if player 1 wins, 2 if player 2 wins
		*/
		inline int getTerminal() { return _terminal; };

		/**
		* \fn getState
		* \brief getter for the childs
		*
		* \return the state of the current node
		*/
		Bitboard* getState() { return _state; };

		/**
		* \fn getMove
		* \brief getter for the move
		*
		* \return the last move played to access the current node
		*/
		Move getMove() { return _move; };

		/**
		 * \fn getChildren
		 * \brief getter for the children
		 *
		 * \return return the list of the childrens
		 */
		inline std::list<Node*> getChildren() { return _children; };

		/**
		* \fn clearParents
		* \brief clear the parents' list
		*/
		inline void clearParents() { _parents.clear(); };

		/**
		 * \fn getParents
		 * \brief getter for the parents
		 *
		 * \return return the list of the parents
		 */
		inline std::list<Node*> getParents() { return _parents; };

		/**
		 * \fn getProba
		 * \brief getter for the winrate
		 *
		 * \return return the winrate of a node
		 */
		inline double getProba() { return (_uct != -1) ? static_cast<double>(_wins) / static_cast<double>(std::max(1,_visits)) : 0; };

		/**
		 * \fn getVisits
		 * \brief getter for the number of visits
		 *
		 * \return return the number of visits
		 */
		inline int getVisits() { return _visits; };

		/**
		 * \fn compare
		 * \brief compare Node* a and Node *b,
		 *
		 * \param Node a
		 * \param Node b
		 * \return true if a's uct is greater than b's uct value.
		 */
		static bool compareUCT(Node* a, Node* b);

		/**
		* \fn compareWR
		* \brief compare Node* a and Node *b,
		*
		* \param Node a
		* \param Node b
		* \return true if a's WR is greater than b's WR value.
		*/
		static bool compareWR(Node* a, Node* b);

		/**
		 * \fn select_child_UCT
		 * \brief fecth the childrens and select the one with the highest UCT
		 * 
		 * \return Return the Node with the best UCT
		 */
		Node* select_child_UCT();
		
		/**
		* \fn select_child_WR
		* \brief fecth the childrens and select the one with the highest WR
		*
		* \return Return the Node with the best UCT
		*/
		Node* select_child_WR();

		/**
		 * \fn addChild
		 * \brief add a Child to a node, given his Bitboard and move played
		 * 
		 * \param state Bitboard after the nove
		 * \param move move played
		 */
		void addChild(Bitboard* state, Move& move, int terminal = -1);

		/**
		 * \fn update
		 * \brief back propate the results of the last simulation to the parents of the node, update _visits & _wins
		 * 
		 * \param win int representing the last winner : 1 2 or 3
		 */
		void update(int win);

		/**
		 * \fn print_tree
		 * \brief print the sub-tree starting with the current node as a root
		 * 
		 * \param numtab the depth we are in the tree in order to insert \t in front of the display
		 * \param depth How deep we want to dive in the tree
		 */
		void print_tree(int numtab, int depth);

		int count();
	};
};