#include "util.h"

std::vector<std::string> Util::split(const std::string& s, char c)
{
	const char* str = s.c_str();
	std::vector<std::string> result;

	do
	{
		const char* begin = str;

		while (*str != c && *str)
			str++;

		result.push_back(std::string(begin, str));
	} while (0 != *str++);

	return result;
}

bool Util::isWhiteLine(const std::string& s)
{
	for (int i = 0; i < s.length(); i++)
	{
		char c = s[i];
		if (!(c == ' ' || c == '\t' || c == '\n'))
		{
			return false;
		}
	}
	return true;
}

std::string Util::stripComment(const std::string& s)
{
	int i = 0;
	for (; i < s.length(); i++)
	{
		if (s[i] == ';')
			break;
	}
	return s.substr(0, i);
}

const std::string Util::binary_palindrome_code =
"; This example program checks if the input string is a binary palindrome.\n"
"; Input: a string of 0's and 1's, eg '1001001'\n"
"\n"
"; Machine starts in state 0.\n"
"\n"
"; State 0: read the leftmost symbol\n"
"0 0 _ r 1o\n"
"0 1 _ r 1i\n"
"0 _ _ * accept\n"
"\n"
"; State 1o, 1i: find the rightmost symbol\n"
"1o _ _ l 2o\n"
"1o * * r 1o\n"
"\n"
"1i _ _ l 2i\n"
"1i * * r 1i\n"
"\n"
"; State 2o, 2i: check if the rightmost symbol matches the most recently read left - hand symbol\n"
"2o 0 _ l 3\n"
"2o _ _ * accept\n"
"2o * * * reject\n"
"\n"
"2i 1 _ l 3\n"
"2i _ _ * accept\n"
"2i * * * reject\n"
"\n"
"; State 3, 4: return to left end of remaining input\n"
"3 _ _ * accept\n"
"3 * * l 4\n"
"4 * * l 4\n"
"4 _ _ r 0\n"
"\n"
"accept * : r accept2\n"
"accept2 * ) * halt-accept\n"
"\n"
"reject _ : r reject2\n"
"reject * _ l reject\n"
"reject2 * ( * halt-reject";

const std::string Util::binary_addition_code =
"; Binary addition - adds two binary numbers\n"
"; Input: two binary numbers, separated by a single space, eg '100 1110'\n"
"\n"
"0 _ _ r 1\n"
"0 * * r 0\n"
"1 _ _ l 2\n"
"1 * * r 1\n"
"2 0 _ l 3x\n"
"2 1 _ l 3y\n"
"2 _ _ l 7\n"
"3x _ _ l 4x\n"
"3x * * l 3x\n"
"3y _ _ l 4y\n"
"3y * * l 3y\n"
"4x 0 x r 0\n"
"4x 1 y r 0\n"
"4x _ x r 0\n"
"4x * * l 4x ; skip the x / y's\n"
"4y 0 1 * 5\n"
"4y 1 0 l 4y\n"
"4y _ 1 * 5\n"
"4y * * l 4y ; skip the x / y's\n"
"5 x x l 6\n"
"5 y y l 6\n"
"5 _ _ l 6\n"
"5 * * r 5\n"
"6 0 x r 0\n"
"6 1 y r 0\n"
"7 x 0 l 7\n"
"7 y 1 l 7\n"
"7 _ _ r halt\n"
"7 * * l 7\n";

const std::string Util::parenthesis_check_code =
"0 * * l 1\n"
"1 _ ! r 51\n"
"5 _ _ r 5\n"
"5 * * * 10\n"
"10 ( ! l 20\n"
"10 ) ! l 30\n"
"10 _ _ l 40\n"
"10 * ! r 10\n"
"20 ! ! l 20\n"
"20 * * * 21\n"
"21 _ ( r 50\n"
"21 * * l 21\n"
"30 ! ! l 30\n"
"30 * * * 31\n"
"31 _ _ r 32\n"
"31 * * l 31\n"
"32 ( _ r 50\n"
"32 ! ! * 80; Trying to decrement below 0, unbalanced parentheses, missing(\n"
"40 ! ! l 40\n"
"40 _ _ r 60; Stack is empty, parentheses are balanced\n"
"40 * * l 70; Stack is not empty, unbalanced parentheses, missing)\n"
"50 ! ! r 51\n"
"50 _ _ l 40; Reached end - of - input\n"
"50 * * r 50\n"
"51 ! ! r 51\n"
"51 * * * 10\n"
"60 ! _ r 60\n"
"60 * * * accept\n"
"70 _ _ r 71\n"
"70 * * l 70\n"
"71 _ * * reject\n"
"71 * _ r 71\n"
"80 _ * * reject\n"
"80 * _ r 80\n"
"accept * : r accept2\n"
"accept2 * ) * halt-accept\n"
"reject * : r reject2\n"
"reject2 * ( * halt-reject\n";

