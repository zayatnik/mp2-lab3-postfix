#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"

using namespace std;

class TPostfix {
	string infix;
	string postfix;
	bool IsOperator(char op);
	int Priority(char a, char b);
	double Operation(double right, double left, char c);
public:
	TPostfix() {}
	TPostfix(string str) {
		infix = str;
		if (!CheckInfix())
			throw "Incorrect infix";
	}
	TPostfix(TPostfix &p) {
		infix = p.infix;
		postfix = p.postfix;
	}
	string GetInfix() {
		return infix;
	}
	string GetPostfix() {
		return postfix;
	}
	bool CheckInfix();
	string ToPostfix();
	double Calculate();
};

#endif