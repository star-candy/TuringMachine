#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <cassert>
#include <iterator>
#include <fstream>
#include "util.h"

namespace Turing
{
	const char EMPTY_SYMBOL = '_'; //비어있음
	const char WILDCARD_SYMBOL = '*'; //와일드카드

	enum class Move
	{
		NONE = 0, LEFT, RIGHT // 이동 상태 정의
	};

	struct Transition
	{
	public:
		Transition(const std::string& curr_s, char read_s, char write_s, Move m, const std::string& next_s);
		//현재 상태, 테잎에서 읽을 값, 작성할 값, 이동할 방향, 다음 상태 : 5가지에 대한 테이블 상태
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
	public:
		Table() {};
		~Table() {};

		void addTransition(const std::string& curr_s, char read_s, char write_s, Move move, const std::string& next_s);
		Transition* findTransition(const std::string& curr_s, char read_s);
		void clear();
		void print(std::ostream& os) const;
		void initialize(const std::string& rule_script); //clear후 stringToTable 호출
		bool load(const std::string& path); //파일 열고 한줄씩 stringToTable 호출

	private:
		std::vector<Transition> transitionTable; //transition 객체를 vector 인자로 받는다
		void stringToTable(const std::string& rule_script);//initialize는 기존 규칙을 초기화 하며 시작
		//파일에서 반복적으로 규칙을 입력받기 위해 clear 사용하지 않는 initialize 필요
	};

	class Tape
	{
	public:
		Tape() : sz{ 0 }, space{ 0 }, elem{0} {}
		Tape(const Tape& t);
		Tape(Tape&& t);
		~Tape() { delete[] elem; };

		Tape& operator=(const Tape& t);
		Tape& operator=(Tape&& t);

		bool read(int i, char& c) const;
		bool write(int i, char c);
		
		void push_back(char c);
		void push_front(char c);
		
		void reserve(int newalloc);
		void resize(int newsize);

		int size() const {return sz;}
		int capacity() const { return space; }

		void initialize(const std::string& s);
		void clear() { sz = 0; }
		void print(std::ostream& os) const;

	private:
		int sz;
		int space;
		char* elem;
	};

	class Machine
	{
	public:
		enum class Mode {NONE, NORMAL, ACCEPT, REJECT, ERROR};

		void initTape(const std::string& initial_symbols);
		void initTable(const std::string& rule_script);
		bool loadTable(const std::string& path);

		void start(const std::string& start_state, const std::string& accept_state, 
			const std::string& reject_state);
		bool step();

		const Table& getTable() const { return table; }
		const Tape& getTape() const { return tape; }
		const std::string& getCurrentState() const { return current_state; }
		int getCurrentPos() const { return current_pos; }
		Mode getCurrentMode() const { return current_mode; }

	private:
		Table table;
		Tape tape;

		Mode current_mode = Mode::NONE; //정상 종료 에러대한 상태인듯
		std::string current_state = ""; //table의 상태 의미?
		int current_pos = 0; //?

		std::string accept_state = ""; //정상(긍정) 종료 조건
		std::string reject_state = ""; //이상(부정) 종료 조건
	};
};
