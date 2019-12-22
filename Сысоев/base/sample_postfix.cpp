#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
	string str;
	double res;

	setlocale(LC_ALL, "Russian");
	cout << "Введите арифметическое выражение: ";
	cin >> str;
	TPostfix expression(str);
	cout << "Арифметическое выражение: " << expression.GetInfix() << endl;
	expression.ToPostfix();
	cout << "Постфиксная форма: " << expression.GetPostfix() << endl << endl;
	res = expression.Calculate();
	cout << "Результат: " << res << endl;

	return 0;
}