#include "production.h"
#include <algorithm>
Production::Production()
{
	right.clear();
}

Production::~Production()
{

}

void Production::printProdLine() const
{
	cout << left.data << " -> ";
	for_each(right.begin(), right.end(), [](const Token& t) {cout << t.data << " "; });
	cout << endl;
}

string Production::getProd() const
{
	string s;
	s += left.data + " -> ";
	for_each(right.begin(), right.end(), [&s](const Token& t) { s += t.data + " "; });
	return s;
}