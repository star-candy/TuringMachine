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

void Table::print(std::ostream& os) const {//���° ������� ǥ���ϱ� ���� �ܼ� for�� ���
	for (int i = 0; i < transitionTable.size(); i++) { //const �Լ����� �����ÿ��� const �±� �ʿ��� ��
		const Transition& transition = transitionTable[i];

		char moveState = '0';//0��½� ������ ������
		if (transition.getMove() == Move::NONE) moveState = '*';
		if (transition.getMove() == Move::LEFT) moveState = 'l';
		if (transition.getMove() == Move::RIGHT) moveState = 'r';
		
		os << "[" << i << "]"<< ": "; // �߰� ���� ����
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
	//table�� �䱸���� ��Ȯ �߽߰� ��ȯ
	//���ϵ� ī�� ���ÿ��� ���� ��ġ�ϴ� �κ� ��� ���� (1, 2 �䱸���� ����)
	for (Transition& transition : transitionTable) {
		if (transition.getCurrState() == curr_s && transition.getReadSymbol() == read_s) {
			//transition.print(std::cout);
			return &transition;
		}
	}
	//��Ȯ�� �䱸������ ���ٸ� Tape symbol ���� ���ϵ�ī��� �ν� �ؾ���
	//���ϵ� ī�� ��� �� ��Ȯ�� �䱸���� �̹߰� ��
	if (read_s == '*') {
		for (Transition& transition : transitionTable) {
			if (transition.getCurrState() == curr_s) {
				//transition.print(std::cout);
				return &transition;
			}
		}
	}
	//���ϵ�ī�� �̻�� �Է¿� ���� table�� ��Ȯ�� �䱸���� �߰� x �� tape symbol�� ���ϵ� ī��� �ν��ϰ� �˻�
	if (read_s != '*') {
		for (Transition& transition : transitionTable) {
			if (transition.getCurrState() == curr_s && transition.getReadSymbol() == '*') {
				//transition.print(std::cout);
				return &transition;
			}
		}
	}

	Transition* errorValue = nullptr;
	return errorValue; //�� ã���� ���� ��ȯ
}

void Table::stringToTable(const std::string& rule_script) {
	std::vector<std::string>rules = Util::split(rule_script, '\n'); //n ������ ����
	std::string curr_s, next_s;
	char read_s, write_s, moveChar;

	for (std::string& rule : rules) {
		rule = Util::stripComment(rule); //; ���� ���� ����
		if (Util::isWhiteLine(rule)) continue; //���� ó��

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
	//transitionTable �ʱ�ȭ, string ���� ��Ģ ������ ���
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
	f.close();//���� ó���� ������ �ݴ´�

	return true;
}

Tape::Tape(const Tape& t) : sz{ t.sz }, space{ sz }, elem{ new char[t.space] } {//cp constructor
	for (int i = 0; i < sz; i++) {
		elem[i] = t.elem[i];
	}
}

Tape::Tape(Tape&& t) : sz{ t.sz }, space{ t.space }, elem{ t.elem } {//mv constuctor
	t.sz = 0;
	t.space = 0;
	t.elem = nullptr;
}

Tape& Tape::operator=(const Tape& t) {//cp assignment
	char* p = new char[t.space];
	for (int i = 0; i < t.sz; i++) {
		p[i] = t.elem[i];
	}
	delete[] elem;
	sz = t.sz;
	space = t.space;
	elem = p;
	return *this;
}

Tape& Tape::operator=(Tape&& t) {//mv assignment
	delete[] elem;
	elem = t.elem;
	sz = t.sz;
	space = t.space;
	t.elem = nullptr;
	t.sz = 0;
	t.space = 0;

	return *this;
}

bool Tape::read(int i, char& c)const {
	if (i >= 0 && i < sz) {
		c = elem[i];
		return true;
	}
	return false;
}

bool Tape::write(int i, char c) {
	if (i >= 0 && i < sz) {
		elem[i] = c;
		return true;
	}
	return false;
}

void Tape::reserve(int newalloc) {
	if (newalloc <= space) return;
	char* p = new char[newalloc];
	for (int i = 0; i < sz; i++) p[i] = elem[i];
	delete[] elem;
	elem = p;
	space = newalloc;
}

void Tape::resize(int newsize) {
	reserve(newsize);
	for (int i = sz; i < newsize; i++) elem[i] = 0;
	sz = newsize;
}

void Tape::push_back(char c) {
	int oldSize = sz;
	if (sz == 0) resize(8);
	else if (sz == space) resize(2 * space);
	sz = oldSize;
	elem[sz] = c;
	++sz;
}

void Tape::push_front(char c) { //elem[0]�� �� �߰� / ������ shift
	int newalloc = space;
	if (sz == 0) newalloc = 8;
	else if (sz == space) newalloc = space * 2;
	char* p = new char[newalloc];
	for (int i = 0; i < sz; i++) p[i + 1] = elem[i];
	for (int i = sz; i < newalloc; i++) p[i] = 0;
	delete[] elem;
	elem = p;
	space = newalloc;
	elem[0] = c;
	++sz;
}

void Tape::initialize(const std::string& s) {
	int newalloc = s.size();
	char* p = new char[newalloc];
	for (int i = 0; i < newalloc; i++) p[i] = s[i];
	delete[] elem;
	elem = p;
	sz = newalloc;
	space = newalloc;
}

void Tape::print(std::ostream& os) const {
	for (int i = 0; i < sz; i++) {
		os << elem[i];
	}
	os << "\n";
}