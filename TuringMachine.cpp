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

		char moveState = '0';//0��½� ������ ����
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

void Tape::resize(int newsize) {//����ִ� ���´� 0�� �ƴ϶� empty_symbol�� ó���ؾ� ��
	reserve(newsize);
	for (int i = sz; i < newsize; i++) elem[i] = EMPTY_SYMBOL;
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
	for (int i = sz; i < newalloc - 1; i++) p[i + 1] = EMPTY_SYMBOL;
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
}

void Machine::initTape(const std::string& initial_symbols) {
	tape.initialize(initial_symbols);
}

void Machine::initTable(const std::string& rule_script) {
	table.initialize(rule_script);
}

bool Machine::loadTable(const std::string& path) {
	bool validate = table.load(path);
	return validate;
}

void Machine::start(const std::string& start_state, const std::string& accept_state,
	const std::string& reject_state) {
	this->current_state = start_state;
	this->accept_state = accept_state;
	this->reject_state = reject_state;
}

bool Machine::step() {
	current_mode = Mode::NORMAL; //�������� ���� �߻��� error�� ������ return �� ��
	char current_tape_symbol = ' ';

	if (!tape.read(current_pos, current_tape_symbol)) {//tape�� ��������� _���� ��µǾ�� �ϴµ�
		current_tape_symbol = EMPTY_SYMBOL;
	}

	Transition* transition = table.findTransition(current_state, current_tape_symbol); //��ġ�� �ش�Ǵ� ��Ģ ã�´�
	if (transition == nullptr) {//findTransition �����ϸ� nullptr ��ȯ��
		current_mode = Mode::ERROR;
		return false;
	}

	//��Ģ ã���� write symbol�� �ش��ϴ� ���� �ۼ��Ѵ�.
	if (transition->getWriteSymbol() == WILDCARD_SYMBOL) {} //���ϵ� ī�� ���¶�� ���� �ʴ´�.
	else if (transition->getWriteSymbol() != WILDCARD_SYMBOL) {//���ϵ� ī�� �ƴϸ� �ش� �� ����.
		tape.write(current_pos, transition->getWriteSymbol());
	}

	//moveDir ��� ��ġ �ٲٱ�
	if (transition->getMove() == Move::NONE) {} 
	else if (transition->getMove() == Move::LEFT) {
		if (current_pos == 0) {
			tape.push_front(EMPTY_SYMBOL); //pos 0 ���� ���� �̵��� emptysymbol�� �߰��Ǿ�� ��
		}
		else {
			current_pos--;
		}
	}
	else if (transition->getMove() == Move::RIGHT) {//���� �̵��� pos�� sz ������ ������ emptysymbol �߰� �ʿ���
		if (current_pos == tape.size() - 1) {
			tape.push_back(EMPTY_SYMBOL);
			current_pos++;
		}
		else {
			current_pos++;
		}
	}
	//��� ���¸� ���� �� ���� ���� Ȯ��
	current_state = transition->getNextState();

	if (current_state == accept_state) {
		current_mode = Mode::ACCEPT;
		return false;
	}
	else if (current_state == reject_state) {
		current_mode = Mode::REJECT;
		return false;
	}
	return true;
}