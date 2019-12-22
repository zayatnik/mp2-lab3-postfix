#include "postfix.h"
#include <string>

using namespace std;

bool TPostfix::IsOperator(char op) {
	if (op == '+' || op == '-' || op == '*' || op == '/')
		return true;
	else
		return false;
}

int TPostfix::Priority(char a, char b) {
	if ((a == '*' || a == '/') && (b == '*' || b == '/'))
		return 0;
	if ((a == '*' || a == '/') && (b == '+' || b == '-'))
		return 1;
	if ((a == '+' || a == '-') && (b == '*' || b == '/'))
		return -1;
	if ((a == '+' || a == '-') && (b == '+' || b == '-'))
		return 0;
	throw "not operation";
}

double TPostfix::Operation(double left, double right, char c) {
	switch (c) {
	case '+': {
		return left + right;
	}
	case '-': {
		return left - right;
	}
	case '*': {
		return left * right;
	}
	case '/': {
		if (right == 0)
			throw 0;
		return left / right;
	}
	default:
		throw "invalid operation";
	}
}

bool TPostfix::CheckInfix() {
	int i = 0, k = 0;
	int condition = 0;

	while (condition != 3 && condition != 4) {
		switch (condition) {
		case 0:
			if (infix[i] == '\0')
				condition = 2;
			else if (infix[i] == '(')
				k++;
			else if ((infix[i] >= '0') && (infix[i] <= '9')) {
				int point = 0;
				while ((infix[i] >= '0') && (infix[i] <= '9') || (infix[i] == ',') || (infix[i] == '.')) {
					if ((infix[i] == ',') || (infix[i] == '.'))
						point++;
					i++;
				}
				if (point < 2)
					condition = 1;
				else
					condition = 3;
				i--;
			}
			else
				condition = 3;
			break;
		case 1:
			if (infix[i] == '\0')
				condition = 2;
			else if (infix[i] == ')') {
				k--;
				if (k < 0)
					condition = 3;
			}
			else if ((infix[i] == '+') || (infix[i] == '-') || (infix[i] == '*') || (infix[i] == '/'))
				condition = 0;
			else
				condition = 3;
			break;
		case 2:
			if (k == 0)
				condition = 4;
			else
				condition = 3;
			break;

		default:
			break;
		}
		i++;
	}

	if (condition == 4)
		return true;
	else return false;
}

string TPostfix::ToPostfix() {
	stack<char> opers(infix.size());
	for (int i = 0; i < infix.size(); i++) {
		if (!IsOperator(infix[i]) && infix[i] != '(' && infix[i] != ')') {
			int j = i;
			while (!IsOperator(infix[j]) && j != infix.size() && infix[j] != ')') {
				if (infix[j] == '.')
					infix[j] = ',';
				postfix += infix[j];
				j++;
			}
			i = j - 1;
			postfix += ';';
		}
		else {
			if (opers.empty())
				opers.push(infix[i]);
			else {
				if (opers.onthetop() == '(')
					opers.push(infix[i]);
				else {
					if (infix[i] == '(')
						opers.push(infix[i]);
					else {
						if (infix[i] == ')') {
							while (opers.onthetop() != '(') {
								postfix += opers.pop();
								postfix += ';';
							}
							opers.pop();
						}
						else {
							if (Priority(infix[i], opers.onthetop()) == 1)
								opers.push(infix[i]);
							else {
								while ((opers.onthetop() != '(')) {
									if (Priority(infix[i], opers.onthetop()) == 1)
										break;
									postfix += opers.pop();
									postfix += ';';
									if (opers.empty())
										break;
								}
								opers.push(infix[i]);
							}
						}

					}

				}

			}

		}
	}
	while (!opers.empty()) {
		postfix += opers.pop();
		postfix += ';';
	}
	return postfix;
}

double TPostfix::Calculate() {
	stack<double> nums(infix.size());
	for (int i = 0; i < postfix.size(); i++) {
		if (!IsOperator(postfix[i])) {
			string doub;
			doub += postfix[i];
			int j = i + 1;
			while (postfix[j] != ';') {
				doub += postfix[j];
				j++;
			}
			double tmp = stod(doub);
			nums.push(tmp);
			i = j;
		}
		else {
			nums.push(Operation(nums.pop(), nums.pop(), postfix[i]));
			i++;
		}
	}
	return nums.onthetop();
}