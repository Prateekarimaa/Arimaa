/**
 * \file Node.h
 * \brief Define class Node
 * \author Benoit Viguier
 * \version 1.0
 * \date November 2nd 2014
 *
 */
#pragma once
#include "../tools/typedef.h"
#include <iostream>
#include <algorithm>
#include <omp.h>
#include "../interfaces/Bitboard.h"
#include "../interfaces/Move.h"
#include "../tools/FastLog.h"

using std::max;

namespace mcts
{

	/**
	 * \brief Node class
	 * \details 
		double _uct = value of uct on the node
		u_long _visits = number of visits on the node
		u_long _wins = number of wins on that node

		u_int _nbchildren = number of children
		u_short _toplay = player to play
		char _terminal = determine if the node has be visited or is a terminal :
		10000000 : not visited
		00000000 : non terminal
		00000001 : player 1 wins
		00000010 : player 2 wins
		00000011 : tie
		01000000 : has no parents
		bool _lock : lock for the exploration

		Move _move = last move been played
		Node*	_firstchild = adresse of the first child, null if not explored
	 */
	class Node
	{
		double	_uct;		// 8 bytes
		u_long _visits;		// 8 bytes
		u_long _wins;		// 8 bytes

		u_int _nbchildren;	// 4 bytes
		u_short	_toplay;	// 2 bytes
		char	_terminal;	// 1 byte
		bool	_lock;		// 1 byte

		Move	_move;		// 8 bytes (uint64)
		Node*	_firstchild;// 8 bytes

		/**
		 * \fn UCT
		 * \brief calculate the UCT value of a node and record it.
		 * \details winrate + sqrt(2)*log((total of visit +1)/ visits)
		 * if uct is set to 42 => we don't update the value : move that has to be played (win)
		 * if uct is set to -1 => we don't change the value either : move that should not be played (loss)
		 * 
		 * _visits | 1 makes sure that it has at least 1 in order to not divide by 0
		 * 
		 * \param visits number of visits on the parent node.
		 */
		inline void UCT(u_long visits) {
			if (!(_uct == -1 || _uct == 42))
			{
				_uct = _wins / static_cast<double>(_visits | 1) + sqrt(2.0 * FastLog::fast_log((visits >> 1) + 1) / ((_visits >> 1) | 1));
			}
		};

	public:

		Node();
		/**
		 * \fn Node(u_short player)
		 * \brief create a node given a player
		 *
		 * \param player : player with the move
		 */
		explicit Node(u_short player);

		/**
		 * \fn Node(u_short player, Move& move);
		 * \brief create a Node with a move + player with the move
		 *
		 * \param player : player with the move
		 * \param move : move played
		 */
		Node(u_short player, Move& move);

		/**
		 * \fn ~Node()
		 * \brief Destructor of the Node
		 * \details call Delete on the bitboard.
		 */
		virtual ~Node();

		/**
		 * \fn setTerminal(u_int terminal)
		 * \brief setter for _terminal
		 *
		 * \param value of the terminal
		 */
		inline void setTerminal(u_int terminal) { _terminal = static_cast<char>(terminal & 255); };

		/**
		 * \fn getTerminal()
		 * \brief getter for the _termianl
		 *
		 * \return 0 if no win yest, 1 if player 1 wins, 2 if player 2 wins, 3 if tie, 64 if no parents, 128 if not explored
		 */
		inline u_int getTerminal() { return (_terminal & 255); };

		/**
		* \fn hasParent()
		* \brief quick check if has parents
		*/
		inline bool hasParent() { return _terminal != 64; };

		/**
		* \fn setHasParent()
		* \brief setter for parents => not explored
		*/
		inline void setHasParent() { _terminal = static_cast<char>(128); };

		/**
		* \fn clearParent()
		* \brief setter for no parents
		*/
		inline void clearParent() { _terminal = static_cast<char>(64); };

		/**
		* \fn setChildrens(Node* c, u_int n)
		* \brief setter for the children
		*
		* \param c address of the first child
		* \param n number of children
		*/
		inline void setChildrens(Node* c, u_int n) { _firstchild = c; _nbchildren = n; };

		/**
		* \fn forceSetUCT
		* \brief setter for _uct(int uct)
		* \details it allows us to force a value to uct : 42 or -1 in order to make sure that some moves must or mustn't be played
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
		* \fn getPlayer()
		* \brief getter for the player to move
		*
		* \return the player with the move
		*/
		inline u_short getPlayer() { return _toplay; };

		/**
		* \fn getMove()
		* \brief getter for the move
		*
		* \return the last move played to access the current node
		*/
		inline Move getMove() { return _move; };

		/**
		 * \fn getChildren()
		 * \brief getter for the children
		 *
		 * \return return the first child and number of siblings
		 */
		inline std::pair<Node*, u_int> getChildren() { return std::pair<Node*, u_int>(_firstchild, _nbchildren); };

		/**
		 * \fn getProba()
		 * \brief getter for the winrate
		 * \details using a lookup table remove a branch : gain in term of cycle and prediction during the execution
		 *
		 * \return return the winrate of a node
		 */
		inline double getProba()
		{
			if (!(_uct == -1 || _uct == 42))
			{
				return static_cast<double>(_wins) / static_cast<double>(_visits | 1);
			}
			static const double lookup[2] = { 0, 2 };
			return lookup[(_uct != -1)];
		};

		/**
		 * \fn addVirtualLoss(int i)
		 * \brief add virtual losses
		 */
		inline void addVirtualLoss(u_int i) { _visits += (i << 1); };

		/**
		 * \fn getVisits()
		 * \brief getter for the number of visits
		 *
		 * \return return the number of visits
		 */
		inline u_long getVisits() { return _visits; };

		/**
		 * \fn compare()
		 * \brief compare Node* a and Node *b,
		 *
		 * \param Node a
		 * \param Node b
		 * \return true if a's uct is greater than b's uct value.
		 */
		inline static bool compareUCT(Node* a, Node* b) { return a->_uct < b->_uct; };

		/**
		* \fn compareWR()
		* \brief compare Node* a and Node *b,
		*
		* \param Node a
		* \param Node b
		* \return true if a's WR is greater than b's WR value.
		*/
		inline static bool compareWR(Node* a, Node* b) { return a->getProba() < b->getProba(); };

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
		* \fn set(Move& move)
		* \brief reset its parameters and set the move played
		*
		* \param move : move played
		*/
		void set(Move& move);

		/**
		* \fn unset()
		* \brief clear data of a node
		*/
		void unset();

		/**
		 * \fn update(int win)
		 * \brief back propate the results of the last simulation to the parents of the node, update _visits & _wins
		 * \details using a lookup table remove a branch : gain in term of cycle and prediction during the execution
		 * 	lookup[8] = {0, 0, 2, 1, 0, 2, 0, 1}
		 * 	index 0 and 4 are never used
		 *	win = 1, _toplay = 1 => 0 (index 1)
		 *	win = 2, _toplay = 1 => 2 (index 2)
		 *	win = 3, _toplay = 1 => 1 (index 3)
		 *	win = 1, _toplay = 2 => 2 (index 5)
		 *	win = 2, _toplay = 2 => 0 (index 6)
		 *	win = 3, _toplay = 2 => 1 (index 7)
 		 *
		 * \param win int representing the last winner : 1 2 or 3
		 */
		inline void update(u_int win) {
			static const u_int lookup[8] = {0, 0, 2, 1, 0, 2, 0, 1}; // lookup table removes branches
			_wins += lookup[win+((_toplay & 2)<<1)];
		};

		/**
		 * \fn print_tree(int numtab, int depth)
		 * \brief print the sub-tree starting with the current node as a root
		 * 
		 * \param numtab the depth we are in the tree in order to insert \t in front of the display
		 * \param depth How deep we want to dive in the tree
		 */
		void print_tree(u_int numtab, u_int depth);

		/**
		 * \fn play(int i = 0)
		 * \brief change the value of the player
		 * \details using a lookup table remove a branch : gain in term of cycle and prediction during the execution
		 * 	i = 0, _toplay = 1 => 2 (index 0)
		 *	i = 1, _toplay = 1 => 2 (index 1)
		 *	i = 2, _toplay = 1 => 1 (index 2)
		 *	i = 0, _toplay = 2 => 1 (index 2)
		 *	i = 1, _toplay = 2 => 2 (index 3)
		 *	i = 2, _toplay = 2 => 1 (index 4)
		 * 
		 * \param i last player 
		 */
		inline void play(int i = 0)
		{
			static const u_short lookup[5] = { 2, 2, 1, 2, 1 };
			_toplay = lookup[((_toplay & 2)<<1) + i];
		};


		/**
		* \fn getLock()
		* \brief try to capture the lock
		* \details function intended to be used in a critical section.
		* if the lock is set (returns true), it means that a thread is already working on the node
		* if the lock is not set (returns false but set the lock to true) no one is working on the node
		* 
		* \return the previous value of the lock 
		*/
		inline bool getLock()
		{
			// printf("%p locked.\n",(void*)this); // trop lent !!!!
			bool t = _lock;
			_lock = true;
			return t;
		}

		/**
		* \fn releaseLock()
		* \brief release the lock
		*/
		inline void releaseLock()
		{
			// printf("%p unlocked.\n",(void*)this); // trop lent !!!!
			_lock = false;
		}
	};
};