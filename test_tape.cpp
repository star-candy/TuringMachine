#include "TuringMachine.h"
#include "util.h"

#include <iostream>
using namespace std;

static void printTape(const Turing::Tape& t)
{
	t.print(cout);
	cout << endl;
}

static void printCommands()
{
	cout << "(*) List of commands" << endl;
	cout << "- construct" << endl;
	cout << "- destroy" << endl;
	cout << "- randomize" << endl;
	cout << "- initialize [s]" << endl;
	cout << "- read [i]" << endl;
	cout << "- write [i] [c]" << endl;
	cout << "- push_back [c]" << endl;
	cout << "- push_front [c]" << endl;
	cout << "- extend_right [n]" << endl;
	cout << "- exted_left [n]" << endl;
	cout << "- print" << endl;
	cout << "- quit" << endl;
	cout << "- help" << endl;
}

static Turing::Tape extendRight(Turing::Tape tape)
{
	tape.push_back('_');
	return tape;
}

static Turing::Tape extendLeft(Turing::Tape tape)
{
	tape.push_front('_');
	return tape;
}

void testTape()
{
	Turing::Tape* tape = nullptr;

	cout << "<<< Turing::Tape Test Program >>>" << endl << endl;

	printCommands();
	cout << endl;

	while (true)
	{
		cout << "> ";

		string input;
		std::getline(cin, input);

		vector<string> tokens = Util::split(input);
		if (tokens.size() > 0)
		{
			string command = tokens[0];

			if (command == "construct")
			{
				if (!tape)
				{
					tape = new Turing::Tape;
					printTape(*tape);
				}
				else
				{
					cout << "Error: tape has been already constructed" << endl;
				}
			}
			else if (command == "destroy")
			{
				if (tape)
				{
					delete tape;
					tape = nullptr;
				}
				else
				{
					cout << "Error: tape has not yet been constructed" << endl;
				}
			}
			else if (command == "randomize")
			{
				if (tape)
				{
					for (int i = 0; i < tape->size(); i++)
					{
						char c = rand() % ('z' - 'A' + 1) + 'A';
						tape->write(i, c);
					}
					printTape(*tape);
				}
				else
				{
					cout << "Error: tape has not yet been constructed" << endl;
				}
			}
			else if (command == "initialize")
			{
				if (tape)
				{
					if (tokens.size() > 1)
					{
						string arg1 = tokens[1];

						tape->initialize(arg1);
						printTape(*tape);
					}
					else
					{
						cout << "Error: read requires [i] argument" << endl;
					}

					/*
					for (int i = 0; i < tape->size(); i++)
					{
						char c = rand() % ('z' - 'A' + 1) + 'A';
						tape->write(i, c);
					}
					printTape(*tape);
					*/
				}
				else
				{
					cout << "Error: tape has not yet been constructed" << endl;
				}
			}
			else if (command == "read")
			{
				if (tape)
				{
					if (tokens.size() > 1)
					{
						string arg1 = tokens[1];
						int i = std::stoi(arg1);
						if (i >= 0 && i < tape->size())
						{
							char c = ' ';
							tape->read(i, c);
							cout << c << endl;
						}
						else
						{
							cout << "Error: [i] is out of range" << endl;
						}
					}
					else
					{
						cout << "Error: read requires [i] argument" << endl;
					}
				}
				else
				{
					cout << "Error: tape has not yet been constructed" << endl;
				}
			}
			else if (command == "write")
			{
				if (tape)
				{
					if (tokens.size() > 2)
					{
						string arg1 = tokens[1];
						string arg2 = tokens[2];

						int i = std::stoi(arg1);
						if (i >= 0 && i < tape->size())
						{
							if (arg2.length() == 1)
							{
								char c = arg2.at(0);
								tape->write(i, c);
								printTape(*tape);
							}
							else
							{
								cout << "Error: [c] should be a string of a single character" << endl;
							}
						}
						else
						{
							cout << "Error: [i] is out of range" << endl;
						}
					}
					else
					{
						cout << "Error: write requires [i] [c] arguments" << endl;
					}
				}
				else
				{
					cout << "Error: tape has not yet been constructed" << endl;
				}
			}
			else if (command == "push_back")
			{
				if (tape)
				{
					if (tokens.size() > 1)
					{
						string arg1 = tokens[1];

						if (arg1.length() == 1)
						{
							char c = arg1.at(0);
							tape->push_back(c);
							printTape(*tape);
						}
						else
						{
							cout << "Error: [c] should be a string of a single character" << endl;
						}
					}
					else
					{
						cout << "Error: push_back requires [c] argument" << endl;
					}
				}
				else
				{
					cout << "Error: tape has not yet been constructed" << endl;
				}
			}
			else if (command == "push_front")
			{
				if (tape)
				{
					if (tokens.size() > 1)
					{
						string arg1 = tokens[1];

						if (arg1.length() == 1)
						{
							char c = arg1.at(0);
							tape->push_front(c);
							printTape(*tape);
						}
						else
						{
							cout << "Error: [c] should be a string of a single character" << endl;
						}
					}
					else
					{
						cout << "Error: push_front requires [c] argument" << endl;
					}
				}
				else
				{
					cout << "Error: tape has not yet been constructed" << endl;
				}
			}
			else if (command == "extend_right")
			{
				if (tape)
				{
					if (tokens.size() > 1)
					{
						string arg1 = tokens[1];
						int n = stoi(arg1);

						if (n > 0)
						{
							for (int i = 0; i < n; i++)
							{
								*tape = extendRight(*tape);
								printTape(*tape);
							}
						}
						else
						{
							cout << "Error: [n] should be an integer greater than 0" << endl;
						}
					}
					else
					{
						cout << "Error: extend_right requires [n] argument" << endl;
					}
				}
				else
				{
					cout << "Error: tape has not yet been constructed" << endl;
				}
			}
			else if (command == "extend_left")
			{
				if (tape)
				{
					if (tokens.size() > 1)
					{
						string arg1 = tokens[1];
						int n = stoi(arg1);

						if (n > 0)
						{
							for (int i = 0; i < n; i++)
							{
								*tape = extendLeft(*tape);
								printTape(*tape);
							}
						}
						else
						{
							cout << "Error: [n] should be an integer greater than 0" << endl;
						}
					}
					else
					{
						cout << "Error: extend_left requires [n] argument" << endl;
					}
				}
				else
				{
					cout << "Error: tape has not yet been constructed" << endl;
				}
			}
			else if (command == "print")
			{
				if (tape)
				{
					printTape(*tape);
				}
				else
				{
					cout << "Error: tape has not yet been constructed" << endl;
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
