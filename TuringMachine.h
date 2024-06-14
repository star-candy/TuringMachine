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
	const char EMPTY_SYMBOL = '_'; //�������
	const char WILDCARD_SYMBOL = '*'; //���ϵ�ī��

	enum class Move
	{
		NONE = 0, LEFT, RIGHT // �̵� ���� ����
	};

	struct Transition
	{
	public:
		Transition(const std::string& curr_s, char read_s, char write_s, Move m, const std::string& next_s);
		//���� ����, ���ٿ��� ���� ��, �ۼ��� ��, �̵��� ����, ���� ���� : 5������ ���� ���̺� ����
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
		std::vector<Transition> transitionTable; //transition ��ü�� vector ���ڷ� �޴´�
	};

	class Tape
	{
		//���� �Լ� ���Ǵ� ���� pdf�� ���õ�, ���� class ���� �� ������ ��
	};

	class Machine
	{
		//���� �Լ� ���Ǵ� ���� pdf�� ���õ� ���� class ���� �� ������ ��
	};
};
