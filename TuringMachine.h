#pragma once

#include <iostream>
#include <string>
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
		Table();
		~Table();

		void addTransition(const std::string& curr_s, char read_s, char write_s, Move move, const std::string& next_s);
		Transition* findTransition(const std::string& curr_s, char read_s);
		void clear();
		void print(std::ostream& os) const;
		void initialize(const std::string& rule_script);
		bool load(const std::string& path);

	private:
		std::vector<Transition> transitionTable; //transition 객체를 vector 인자로 받는다
	};

	class Tape
	{
		//기초 함수 정의는 과제 pdf에 제시됨, 선행 class 제작 후 구현할 것
	};

	class Machine
	{
		//기초 함수 정의는 과제 pdf에 제시됨 선행 class 제작 후 구현할 것
	};
};
