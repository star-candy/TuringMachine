#include "TuringMachine.h"

using namespace Turing;

Transition::Transition(const std::string& curr_s, char read_s, char write_s, Move m, const std::string& next_s)
	: curr_state{ curr_s }, read_symbol{ read_s }, write_symbol{ write_s }, move{ m }, next_state{ next_s }
{
}

void Transition::print(std::ostream& os) const
{
	os << curr_state << " ";
	os << read_symbol << " ";
	os << write_symbol << " ";
	os << (move == Move::LEFT ? 'l' : (move == Move::RIGHT ? 'r' : '*')) << " ";
	os << next_state;
}

void Table::addTransition(const std::string& curr_s, char read_s, char write_s, Move m, const std::string& next_s) {
	Transition transition(curr_s, read_s, write_s, m, next_s);
	transitionTable.push_back(transition);
}

void Table::print(std::ostream& os) const {
	for (int i = 0; i < transitionTable.size(); i++) {
		char moveState = '0';//error ป๓ลย
		if (transitionTable[i].getMove() == Move::NONE) moveState = '*';
		if (transitionTable[i].getMove() == Move::LEFT) moveState = '1';
		if (transitionTable[i].getMove() == Move::RIGHT) moveState = 'r';

		os << "(" << transitionTable[i].getCurrState() << ", ";
		os << transitionTable[i].getReadSymbol() << ", ";
		os << transitionTable[i].getWriteSymbol() << ", ";
		os << moveState << ", ";
		os << transitionTable[i].getNextState() << ")\n";
	}
}