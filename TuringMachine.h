#pragma once

#include <string>
#include <vector>
#include <set>
#include <cassert>
#include <iterator>
#include <fstream>

#include "util.h"

namespace Turing
{
	const char EMPTY_SYMBOL = '_';
	const char WILDCARD_SYMBOL = '*';

	enum class Move
	{
		NONE = 0, LEFT, RIGHT
	};

	struct Transition
	{
	public:
		Transition(const std::string& curr_s, char read_s, char write_s, Move m, const std::string& next_s);

		void print(std::ostream& os) const;

		inline const std::string& getCurrState() const { return curr_state; }
		inline const std::string& getNextState() const { return next_state; }

		inline char getReadSymbol() const { return read_symbol; }
		inline char getWriteSymbol() const { return write_symbol; }
		
		inline Move getMove() const { return move; }

	private:
		std::string curr_state, next_state;
		char read_symbol, write_symbol;
		Move move;
	};

	class Table
	{
	};

	class Tape
	{
	};

	class Machine
	{
	};
};
