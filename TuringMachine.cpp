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
	for (const Transition& transition : transitionTable) { //const 함수에서 참조시에는 const 태그 필요한 듯
		char moveState = '0';//0출력시 비정상 상태임
		if (transition.getMove() == Move::NONE) moveState = '*';
		if (transition.getMove() == Move::LEFT) moveState = 'l';
		if (transition.getMove() == Move::RIGHT) moveState = 'r';

		os << transition.getCurrState() << ", ";
		os << transition.getReadSymbol() << ", ";
		os << transition.getWriteSymbol() << ", ";
		os << moveState << ", ";
		os << transition.getNextState() << "\n";
	}
}

void Table::clear() {
	transitionTable.clear(); 
}

Transition* Table::findTransition(const std::string& curr_s, char read_s) {
	//table에 요구사항 정확 발견시 반환
	//와일드 카드 사용시에도 완전 일치하는 부분 출력 가능 (1, 2 요구사항 만족)
	for (Transition& transition : transitionTable) {
		if (transition.getCurrState() == curr_s && transition.getReadSymbol() == read_s) {
			//transition.print(std::cout);
			return &transition;
		}
	}
	//정확한 요구사항이 없다면 Tape symbol 값을 와일드카드로 인식 해야함
	//와일드 카드 사용 및 정확한 요구사항 미발견 시
	if (read_s == '*') {
		for (Transition& transition : transitionTable) {
			if (transition.getCurrState() == curr_s) {
				//transition.print(std::cout);
				return &transition;
			}
		}
	}
	//와일드카드 미사용 입력에 대해 table에 정확한 요구사항 발견 x 시 tape symbol을 와일드 카드로 인식하고 검색
	if (read_s != '*') {
		for (Transition& transition : transitionTable) {
			if (transition.getCurrState() == curr_s && transition.getReadSymbol() == '*') {
				//transition.print(std::cout);
				return &transition;
			}
		}
	}

	Transition* errorValue = nullptr;
	return errorValue; //못 찾으면 공백 반환
}


void Table::stringToTable(const std::string& rule_script) {
	std::vector<std::string>rules = Util::split(rule_script, '\n'); //n 단위로 분할
	std::string curr_s, next_s;
	char read_s, write_s, moveChar;

	for (std::string& rule : rules) {
		rule = Util::stripComment(rule); //; 이후 문장 제거
		if (Util::isWhiteLine(rule)) continue; //공백 처리

		std::istringstream ss(rule);
		ss >> curr_s >> read_s >> write_s >> moveChar >> next_s;

		Move move = Move::NONE;
		if (moveChar == '*') move = Move::NONE;
		if (moveChar == 'l') move = Move::LEFT;
		if (moveChar == 'r') move = Move::RIGHT;

		addTransition(curr_s, read_s, write_s, move, next_s);
	}
}

void Table::initialize(const std::string& rule_script) {
	//transitionTable 초기화, string 통해 규칙 재정의 기능
	clear();
	stringToTable(rule_script);
}

bool Table::load(const std::string& path) {
	std::ifstream f;
	f.open(path);
	if (!f.is_open()) return false;

	std::string lineValue;
	while (std::getline(f, lineValue)) {
		stringToTable(lineValue);
	}
	f.close();//파일 처리가 끝나면 닫는다

	return true;
}
