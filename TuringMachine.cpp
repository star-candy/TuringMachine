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

void Table::print(std::ostream& os) const {//��ȣ�� ��� �䱸������ �ƴ� �� �ϴ�.
	for (int i = 0; i < transitionTable.size(); i++) {
		char moveState = '0';//0��½� ������ ������
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
	//table�� �䱸���� ��Ȯ �߽߰� ���
	for (Transition& transition : transitionTable) {
		if (transition.getCurrState() == curr_s && transition.getReadSymbol() == read_s) {
			transition.print(std::cout);
			return &transition;
		}
	}
	//��Ȯ�� �䱸������ ���ٸ� ���ϵ�ī��� �ν� �ؾ���
	//���ϵ� ī�� ��� �� ��Ȯ�� �䱸���� �߰� ��
	if (read_s == '*') {
		for (Transition& transition : transitionTable) {
			if (transition.getCurrState() == curr_s && transition.getReadSymbol() == '*') {
				transition.print(std::cout);
				return &transition;
			}
		}
	}
	//���ϵ�ī�� ��� �� ��Ȯ�� �䱸���� �߰� x �� ���� ���ڷ� �ؼ��ϰ� �� �� ù��° ��� ��ȯ
	if (read_s == '*') {
		for (Transition& transition : transitionTable) {
			if (transition.getCurrState() == curr_s) {
				transition.print(std::cout);
				return &transition;
			}
		}
	}

	////���ϵ� ī�� ��� x ��Ȯ�� �䱸���� �߰� ���ϸ� ���ϵ�ī��� �ν�
	// ù��° for�� �̽���� �ڵ����� ���ϵ�ī��� �ν�, ���� ���� �ʿ� ���� ��

	return;
}


