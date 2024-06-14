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

void Table::print(std::ostream& os) const {//괄호는 출력 요구사항이 아닌 듯 하다.
	for (int i = 0; i < transitionTable.size(); i++) {
		char moveState = '0';//0출력시 비정상 상태임
		if (transitionTable[i].getMove() == Move::NONE) moveState = '*';
		if (transitionTable[i].getMove() == Move::LEFT) moveState = '1';
		if (transitionTable[i].getMove() == Move::RIGHT) moveState = 'r';

		os << transitionTable[i].getCurrState() << ", ";
		os << transitionTable[i].getReadSymbol() << ", ";
		os << transitionTable[i].getWriteSymbol() << ", ";
		os << moveState << ", ";
		os << transitionTable[i].getNextState() << "\n";
	}
}

void Table::clear() {
	transitionTable.clear(); 
}

Transition* Table::findTransition(const std::string& curr_s, char read_s) {
	//table에 요구사항 정확 발견시 출력
	for (Transition& transition : transitionTable) {
		if (transition.getCurrState() == curr_s && transition.getReadSymbol() == read_s) {
			transition.print(std::cout);
			return &transition;
		}
	}
	//정확한 요구사항이 없다면 와일드카드로 인식 해야함
	//와일드 카드 사용 및 정확한 요구사항 발견 시
	if (read_s == '*') {
		for (Transition& transition : transitionTable) {
			if (transition.getCurrState() == curr_s && transition.getReadSymbol() == '*') {
				transition.print(std::cout);
				return &transition;
			}
		}
	}
	//와일드카드 사용 및 정확한 요구사항 발견 x 시 임의 문자로 해석하고 그 중 첫번째 결과 반환
	if (read_s == '*') {
		for (Transition& transition : transitionTable) {
			if (transition.getCurrState() == curr_s) {
				transition.print(std::cout);
				return &transition;
			}
		}
	}

	////와일드 카드 사용 x 정확한 요구사항 발견 못하면 와일드카드로 인식
	// 첫번째 for문 미실행시 자동으로 와일드카드로 인식, 따라서 정의 필요 없을 듯

	return;
}


