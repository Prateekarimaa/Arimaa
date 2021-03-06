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
#include <omp.h>
#include "../interfaces/Bitboard.h"
#include "../interfaces/Move.h"
#include "../tools/FastLog.h"
#define FASTLOG
#define MAXI std::max

using std::max;

namespace mcts
{

	/**
	 * \brief Node class
	 * \details 
		int _visits = number of visits on the node
		int _wins = number of wins on that node
		int _terminal = determine if the node has be visited or is a terminal :
		-1 : not visited
		0 : non terminal
		1/2 : player 1/2 wins
		3 : tie
		double _uct = value of uct on the node
		Bitboard* _state = current state of the board
		Move _move = last move been played
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
#ifdef FASTLOG
				_uct = _wins / static_cast<double>(max(_visits, 1)) + sqrt(2.0 * FastLog::fast_log(visits + 1) / max(_visits, 1));
#else
				_uct = _wins / static_cast<double>(max(_visits, 1)) + sqrt(2.0 * log(static_cast<double>(visits + 1)) / max(_visits, 1));
#endif
			}
#ifdef DEBUG_NODE
			cout << "_uct " << " = " << static_cast<double>(_wins) << " / " << static_cast<double>(max(_visits, 1)) << " + sqrt(2.0 * log( " << static_cast<double>(visits + 1) << " / " << max(_visits, 1) << ")" << endl;
			cout << "_uct = " << _uct << endl;
#endif //DEBUG_NODE
		};

	public :

		Node();
		/**
		* \fn Node(Bitboard* state)
		* \brief create a node given a Bitboard
		*
		* \param state : Board to create the node with
		*/
		explicit Node(Bitboard* state);

		/**
		 * \fn Node(Node* p_parent, Bitboard state, Move& move);
		 * \brief create a Node with parent as parent and move + Bitboard after the move played
		 * 
		 * \param parent : parent of the node
		 * \param state : Bitboard after the move
		 * \param move : move played
		 */
		Node(Node* parent, Bitboard* state, Move& move);

		/**
		 * \fn ~Node()
		 * \brief Destructor of the Node
		 * \details call Delete on the bitboard.
		 */
		virtual ~Node();

		/**
		 * \fn killChildrens(Node* exception)
		 * \brief kill all the children of a node but the one with the exception adress
		 * 
		 * \param exception Node that we MUST NOT KILL
		 */
		void killChildrens(Node* exception);

		/**
		* \fn setTerminal(int terminal)
		* \brief setter for _terminal
		*
		* \param value of the terminal
		*/
		inline void setTerminal(int terminal) { _terminal = terminal; };

		/**
		* \fn forceSetUCT
		* \brief setter for _uct(int uct)
		* \details it allows us to force a value to uct : 10 or -1 in order to make sure that some moves must or mustn't be played
		*
		* \param value of the uct
		*/
		inline void forceSetUCT(int uct) { if (_uct == -1) return; _uct = uct; };

		/**
		* \fn getUCT()
		* \brief getter for _uct
		*
		* \return value of the uct
		*/
		inline double getUCT() { return _uct; };

		/**
		* \fn getTerminal()
		* \brief getter for the _termianl
		*
		* \return 0 if not, 1 if player 1 wins, 2 if player 2 wins, 3 if tie
		*/
		inline int getTerminal() { return _terminal; };

		/**
		* \fn getState()
		* \brief getter for the Board
		*
		* \return the Board of the current node
		*/
		Bitboard* getState() { return _state; };

		/**
		* \fn getMove()
		* \brief getter for the move
		*
		* \return the last move played to access the current node
		*/
		Move getMove() { return _move; };

		/**
		 * \fn getChildren()
		 * \brief getter for the children
		 *
		 * \return return the list of the childrens
		 */
		inline std::list<Node*> getChildren() { return _children; };

		/**
		* \fn clearParents()
		* \brief clear the parents' list
		*/
		inline void clearParents() { _parents.clear(); };

		/**
		 * \fn getParents()
		 * \brief getter for the parents
		 *
		 * \return return the list of the parents
		 */
		inline std::list<Node*> getParents() { return _parents; };

		/**
		 * \fn getProba()
		 * \brief getter for the winrate
		 *
		 * \return return the winrate of a node
		 */
		inline double getProba() { return (_uct != -1) ? ((_uct != 10) ? static_cast<double>(_wins) / static_cast<double>(max(1, _visits)) : 2) : 0; };

		/**
		 * \fn getVisits()
		 * \brief getter for the number of visits
		 *
		 * \return return the number of visits
		 */
		inline int getVisits() { return _visits; };

		/**
		 * \fn compare()
		 * \brief compare Node* a and Node *b,
		 *
		 * \param Node a
		 * \param Node b
		 * \return true if a's uct is greater than b's uct value.
		 */
		static bool compareUCT(Node* a, Node* b);

		/**
		* \fn compareWR()
		* \brief compare Node* a and Node *b,
		*
		* \param Node a
		* \param Node b
		* \return true if a's WR is greater than b's WR value.
		*/
		static bool compareWR(Node* a, Node* b);

		/**
		 * \fn select_child_UCT()
		 * \brief fecth the childrens and select the one with the highest UCT
		 * 
		 * \return Return the Node with the best UCT
		 */
		Node* select_child_UCT();
		
		/**
		* \fn select_child_WR()
		* \brief fecth the childrens and select the one with the highest WR
		*
		* \return Return the Node with the best UCT
		*/
		Node* select_child_WR();

		/**
		 * \fn addChild(Bitboard* state, Move& move, int terminal = -1)
		 * \brief add a Child to a node, given his Bitboard and move played
		 * 
		 * \param state : Bitboard after the nove
		 * \param move : move played
		 * \param terminal : set if node is terminal or not. By default, not explored. 
		 */
		void addChild(Bitboard* state, Move& move, int terminal = -1);

		/**
		* \fn set(Bitboard* state, Move& move, Node* parent)
		* \brief add a Child to a node, given his Bitboard and move played and reset its parameters
		*
		* \param state : Bitboard after the nove
		* \param move : move played
		* \param terminal : set if node is terminal or not. By default, not explored.
		*/
		void set(Bitboard* state, Move& move, Node* parent);

		/**
		* \fn unset()
		* \brief clear data of a node (it will be added to the aviable list later).
		*/
		void unset();

		/**
		 * \fn update(int win)
		 * \brief back propate the results of the last simulation to the parents of the node, update _visits & _wins
		 * 
		 * \param win int representing the last winner : 1 2 or 3
		 */
		void update(int win);

		/**
		 * \fn print_tree(int numtab, int depth)
		 * \brief print the sub-tree starting with the current node as a root
		 * 
		 * \param numtab the depth we are in the tree in order to insert \t in front of the display
		 * \param depth How deep we want to dive in the tree
		 */
		void print_tree(int numtab, int depth);

		/**
		 * \fn count()
		 * \brief recursive function that count the number of leaves of the subtree.
		 * \return number of leaves of the sub tree.
		 */
		int count();

		int max_depth();
	};
};