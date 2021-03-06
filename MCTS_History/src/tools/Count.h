/**
 * \file Count.h
 * \brief Define singleton Count
 * \author Benoit Viguier
 * \version 1.0
 * \date November 2nd 2014
 *
 */
#pragma once
#include <iostream>

/**
 * \brief Count class : SINGLETON
 * \details 
	static unsigned int _seed : seed used to initialize the srand(), by default time(null);
	static Count* UniqueInstance : instance of the following class;
 */
class Count
{
	int _nodes;
	int _bitboads;
	int _bitboadsC4;
	int _nbleaves;

	int _nodes_saved;
	int _bitboads_saved;
	int _bitboadsC4_saved;
	int _nbleaves_saved;
	static Count* UniqueInstance;
	
	Count();
	~Count();

	inline int ratio(int& a, int& b)
	{
		return (b != 0) ? (a * 100 / b) - 100 : 0;
	}
public:
	
	/**
	 * \fn I
	 * \brief get the instance of the singleton.
	 * \param  seed optionnal, allow us to set the seed in case singleton hasn't been initialized
	 * \return      the object.
	 */
	static Count* I();
	
	inline void addNode() { _nodes++; }
	inline void rmNode() { _nodes--; }

	inline void addBitBoards() { _bitboads++; }
	inline void rmBitBoards() { _bitboads--; }

	inline void addBitBoardsC4() { _bitboadsC4++; }
	inline void rmBitBoardsC4() { _bitboadsC4--; }
	
	inline void saveNbLeaves(int n) { _nbleaves = n; }

	friend std::ostream& operator<< (std::ostream& stream, Count* count) {
		stream << "nb leavs : " << count->_nbleaves << " (" << (count->_nbleaves - count->_nbleaves_saved) << " " << count->ratio(count->_nbleaves, count->_nbleaves_saved) << "%)" << std::endl;
		stream << "nb nodes : " << count->_nodes << " (" << (count->_nodes - count->_nodes_saved) << " " << count->ratio(count->_nodes, count->_nodes_saved) << "%)" << std::endl;
//		stream << "nb Bb : " << count->_bitboads << " (" << (count->_bitboads - count->_bitboads_saved) << " " << count->ratio(count->_bitboads, count->_bitboads_saved) << "%)" << std::endl;
		stream << "nb BbC4  : " << count->_bitboadsC4 << " (" << (count->_bitboadsC4 - count->_bitboadsC4_saved) << " " << count->ratio(count->_bitboadsC4, count->_bitboadsC4_saved) << "%)" << std::endl;
		count->_nodes_saved = count->_nodes;
		count->_bitboads_saved = count->_bitboads;
		count->_bitboadsC4_saved = count->_bitboadsC4;
		count->_nbleaves_saved = count->_nbleaves;
		return stream;
	};
};
