#include "TuringMachine.h"
#include "util.h"

#include <iostream>
using namespace std;


static void printTape(const Turing::Tape& t)
{
	t.print(cout);
	cout << endl;
}

static void printTable(const Turing::Table& t)
{
	t.print(cout);
	cout << endl;
}

static void printMachine(const Turing::Machine& m)
{
	m.getTape().print(cout);
	
	std::string state = m.getCurrentState();
	state += '/';

	Turing::Machine::Mode mode = m.getCurrentMode();
	switch (mode) {
	case Turing::Machine::Mode::NORMAL:	state += "NORMAL";	break;
	case Turing::Machine::Mode::ACCEPT:	state += "ACCEPT";	break;
	case Turing::Machine::Mode::REJECT:	state += "REJECT";	break;
	case Turing::Machine::Mode::ERROR:	state += "ERROR";	break;
	}

	std::cout << " [" << state << "]" << std::endl;

	int curr_p = m.getCurrentPos();
	for (int i = 0; i < curr_p; i++)	std::cout << " ";
	std::cout << "^" << std::endl;
}

static void printCommands()
{
	cout << "(*) List of commands" << endl;
	cout << "- load_table [path]" << endl;
	cout << "- init_table [name] (name=palindrome, addition, parenthesis)" << endl;
	cout << "- init_tape [data]" << endl;
	cout << "- start [initial state] [accept state] [reject state]" << endl;
	cout << "- run" << endl;
	cout << "- step" << endl;
	cout << "- quit" << endl;
	cout << "- help" << endl;
	cout << endl;
}

void testMachine()
{
	Turing::Machine machine;

	cout << "<<< Turing::Machine Test Program >>>" << endl << endl;

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

			if (command == "load_table")
			{
				if (tokens.size() > 1)
				{
					string path = tokens[1];

					bool is_loaded = machine.loadTable(path);
					if (!is_loaded)
					{
						cout << "Error: \'" << path << "\' does not exist" << endl;
					}
					else
					{
						printTable(machine.getTable());
					}
				}
				else
				{
					cout << "Error: load_table requires [path] argument" << endl;
				}
			}
			else if (command == "init_table")
			{
				if (tokens.size() > 1)
				{
					string name = tokens[1];
					bool is_initialized = false;

					if (name == "palindrome")
					{
						machine.initTable(Util::binary_palindrome_code);
						is_initialized = true;
					}
					else if (name == "addition")
					{
						machine.initTable(Util::binary_addition_code);
						is_initialized = true;
					}
					else if (name == "parenthesis")
					{
						machine.initTable(Util::parenthesis_check_code);
						is_initialized = true;
					}

					if (is_initialized)
					{
						printTable(machine.getTable());
					}
					else
					{
						cout << "Error: \'" << name << "\' is not a valid name" << endl;
					}
				}
				else
				{
					cout << "Error: init_table requires [name] argument" << endl;
				}
			}
			else if (command == "init_tape")
			{
				if (tokens.size() > 1)
				{
					string data = tokens[1];
					machine.initTape(data);

					printTape(machine.getTape());
				}
				else
				{
					cout << "Error: init_tape requires [data] argument" << endl;
				}
			}
			else if (command == "start")
			{
				if (tokens.size() > 3)
				{
					string init_state = tokens[1];
					string accept_state = tokens[2];
					string reject_state = tokens[3];

					machine.start(init_state, accept_state, reject_state);

					printMachine(machine);
				}
				else
				{
					cout << "Error: start requires [initial state] [accept state] [reject state] arguments" << endl;
				}
			}
			else if (command == "step")
			{
				bool is_stepped = machine.step();

				printMachine(machine);
				
				if (!is_stepped)
				{
					cout << "Error: machine has not been updated properly" << endl;
				}
			}
			else if (command == "run")
			{
				bool is_good = true;
				while (is_good)
				{
					is_good = machine.step();
					printMachine(machine);
				}
			}
			else if (command == "quit")
			{
				break;
			}
			else if (command == "help")
			{
				printCommands();
			}
			else
			{
				cout << "Error: \'" << command << "\' is not a valid command" << endl;
			}
		}
		cout << endl;
	}
}
