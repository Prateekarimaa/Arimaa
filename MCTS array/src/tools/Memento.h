#pragma once
#include "typedef.h"
#include <vector>

template <class N> class Memento
{
	std::vector<N> _states;
	short _readNext;
	short _writeNext;

public:
	explicit Memento(short n) : _states(std::vector<N>(n)), _readNext(0), _writeNext(0) {};
	~Memento()
	{
		for (auto itr = _states.begin(); itr != _states.end(); ++itr)
		{
			delete &(*itr);
		}
	};

	void rewind()
	{
		_readNext = _writeNext - 1;
	};

	void reset()
	{
		_writeNext = 0;
	};

	void push(const N& state)
	{
		_states[_writeNext] = state;
		_writeNext++;
	}

	N* get()
	{
		if (_readNext == -1) return nullptr;
		auto data = &_states[_readNext];
		_readNext--;
		return data;
	}


	/* test stuff , probably not working, but you never know... */
	void applyFunIncr(void* fun, void* arg)
	{
		for (_readNext = 0; _readNext < _writeNext; ++_readNext)
		{
			_states[_readNext]->*fun(*arg);
		}
	}

	void applyFunDecr(void* fun, void* arg)
	{
		for (_readNext = (_writeNext - 1); _readNext >= 0; --_readNext)
		{
			_states[_readNext]->*fun(*arg);
		}
	}
};
