#include "TuringMachine.h"
#include "util.h"

#include <iostream>
using namespace std;

static void printTransition(const Turing::Transition& t)
{
	t.print(cout);
	cout << endl;
}

static void printTable(const Turing::Table &t)
{
	t.print(cout);
}

static void printCommands()
{
	cout << "(*) List of commands" << endl;
	cout << "- add [curr_s] [read_s] [write_s] [move] [next_s]" << endl;
	cout << "- find [curr_s] [read_s]" << endl;
	cout << "- initialize [name] (name = palindrome, addition, parenthesis)" << endl;
	cout << "- load [path]" << endl;
	cout << "- clear" << endl;
	cout << "- print" << endl;
	cout << "- quit" << endl;
	cout << "- help" << endl;
}

void testTable()
{
	Turing::Table table;

	cout << "<<< Turing::Table Test Program >>>" << endl << endl;

	printCommands();

	while (true)
	{
		cout << "> ";

		string input;
		std::getline(cin, input);

		vector<string> tokens = Util::split(input);
		if (tokens.size() > 0)
		{
			string command = tokens[0];

			if (command == "add")
			{
				if (tokens.size() > 5)
				{
					string curr_s = tokens[1];
					char read_s = tokens[2].at(0);
					char write_s = tokens[3].at(0);
					char move_c = tokens[4].at(0);
					string next_s = tokens[5];

					Turing::Move move = Turing::Move::NONE;
					switch (move_c) {
					case 'l':	move = Turing::Move::LEFT;	break;
					case 'r':	move = Turing::Move::RIGHT;	break;
					}

					table.addTransition(curr_s, read_s, write_s, move, next_s);
					printTable(table);
				}
				else
				{
					cout << "Error: add requires [curr_s] [read_s] [write_s] [move] [next_s] arguments" << endl;
				}
			}
			else if (command == "find")
			{
				if (tokens.size() > 2)
				{
					string curr_s = tokens[1];
					char read_s = tokens[2].at(0);

					Turing::Transition* trans = table.findTransition(curr_s, read_s);
					if (trans)
					{
						printTransition(*trans);
					}
					else
					{
						cout << "Error: no transition is matched" << endl;
					}
				}
				else
				{
					cout << "Error: find requires [curr_s] [read_s] arguments" << endl;
				}
			}
			else if (command == "initialize")
			{
				if (tokens.size() > 1)
				{
					string name = tokens[1];
					bool is_initialized = false;

					if (name == "palindrome")
					{
						table.initialize(Util::binary_palindrome_code);
						is_initialized = true;
					}
					else if (name == "addition")
					{
						table.initialize(Util::binary_addition_code);
						is_initialized = true;
					}
					else if (name == "parenthesis")
					{
						table.initialize(Util::parenthesis_check_code);
						is_initialized = true;
					}

					if (is_initialized)
					{
						printTable(table);
					}
					else
					{
						cout << "Error: \'" << name << "\' is not a valid name" << endl;
					}
				}
				else
				{
					cout << "Error: initialize requires [name] argument" << endl;
				}
			}
			else if (command == "load")
			{
				if (tokens.size() > 1)
				{
					string path = tokens[1];

					bool is_loaded = table.load(path);
					if (!is_loaded)
					{
						cout << "Error: \'" << path << "\' does not exist" << endl;
					}
					else
					{
						printTable(table);
					}
				}
				else
				{					
					cout << "Error: load requires [path] argument" << endl;
				}

			}
			else if (command == "clear")
			{
				table.clear();
				printTable(table);
			}
			else if (command == "print")
			{
				printTable(table);
			}
			else if (command == "help")
			{
				printCommands();
			}
			else if (command == "quit")
			{
				break;
			}
			else
			{
				cout << "Error: \'" << command << "\' is not a valid command" << endl;
			}
		}
		cout << endl;
	}
}