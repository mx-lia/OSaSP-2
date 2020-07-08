#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <map>
using namespace std;

#define doFST int step = 0;\
bool rc = false;\
Stack<states> stk(1);\
stk.push(initial);\
pair<states, char> curr;\
FST::iterator iter;\
while (!stk.empty())\
{\
	if (step < strlen(word))\
	{\
		curr = { stk.pop(),word[step] };\
		iter = wh.find(curr);\
		if (iter != wh.end())\
		{\
\
			cout << iter->first.first << " : " << iter->first.second << " -> " << iter->second << endl;\
			step++;\
			if (iter->second == fin) rc = true;\
			else\
			{\
				rc = false;\
				stk.push(iter->second);\
			}\
		}\
		else\
		{\
			cout << curr.first << " : " << curr.second << " -> ERROR." << endl;\
			return false;\
		}\
	}\
	else return false;\
}\
if (step < strlen(word))\
{\
	cout << "<empty> : \'" << word[step] << "\' -> ERROR. Stack is empty." << endl;\
	return false;\
}\
else return rc;

template< class T >
class Stack {

private:
	int MAX;
	int top;
	T* items;

public:
	Stack(int size) {
		MAX = size;
		top = -1;
		items = new T[MAX];
	}

	~Stack() { delete[] items; }

	void push(T c) {
		if (full()) {
			cout << "Stack Full!" << endl;
			exit(1);
		}

		items[++top] = c;
	}

	T pop() {
		if (empty()) {
			cout << "Stack Empty!" << endl;
			exit(1);
		}

		return items[top--];
	}
	T at_top()
	{
		return items[top];
	}
	int empty() { return top == -1; }

	int full() { return top + 1 == MAX; }
};

bool fixed_check(char *word)
{
	enum states
	{
		initial = 0,
		intp, //целая честь
		dot,// точка
		fract,//дробная часть
		fin
	};
	typedef std::map<pair<states, char>, states> FST;
	FST wh = {
		{ { initial,'-' },intp },{ { initial,'+' },intp },
		{ { initial,'0' },intp },{ { initial,'1' },intp },{ { initial,'2' },intp },{ { initial,'3' },intp },{ { initial,'4' },intp },
		{ { initial,'5' },intp },	{ { initial,'6' },intp },{ { initial,'7' },intp },{ { initial,'8' },intp },{ { initial,'9' },intp },
		{ { intp,'0' },intp },{ { intp,'1' },intp },{ { intp,'2' },intp },{ { intp,'3' },intp },{ { intp,'4' },intp },
		{ { intp,'5' },intp },{ { intp,'6' },intp },{ { intp,'7' },intp },{ { intp,'8' },intp },{ { intp,'9' },intp },
		{ { intp,'.' },dot },{ { intp,' ' },fin },
		{ { dot,'0' },fract },{ { dot,'1' },fract },{ { dot,'2' },fract },{ { dot,'3' },fract },{ { dot,'4' },fract },
		{ { dot,'5' },fract },{ { dot,'6' },fract },{ { dot,'7' },fract },{ { dot,'8' },fract },{ { dot,'9' },fract },
		{ { fract,' ' },fin },
		{ { fract,'0' },fract },{ { fract,'1' },fract },{ { fract,'2' },fract },{ { fract,'3' },fract },{ { fract,'4' },fract },
		{ { fract,'5' },fract },{ { fract,'6' },fract },{ { fract,'7' },fract },{ { fract,'8' },fract },{ { fract,'9' },fract }
	};
	doFST
}

bool float_check(char * word)
{
	enum states
	{
		initial = 0,
		intp, //целая часть
		dot, // точка
		fract, // дробная часть
		ee, // е
		exp, //степень е
		fin // конец состояния
	};
	typedef std::map<pair<states, char>, states> FST;
	FST wh = {
		{ { initial,'-' },intp },{ { initial,'+' },intp },
		{ { initial,'0' },intp },{ { initial,'1' },intp },{ { initial,'2' },intp },{ { initial,'3' },intp },{ { initial,'4' },intp },
		{ { initial,'5' },intp },{ { initial,'6' },intp },{ { initial,'7' },intp },{ { initial,'8' },intp },{ { initial,'9' },intp },
		{ { intp,'0' },intp },{ { intp,'1' },intp },{ { intp,'2' },intp },{ { intp,'3' },intp },{ { intp,'4' },intp },
		{ { intp,'5' },intp },{ { intp,'6' },intp },{ { intp,'7' },intp },{ { intp,'8' },intp },{ { intp,'9' },intp },
		{ { intp,'.' },dot },
		{ { intp,'e' },ee },
		{ { dot,'0' },fract },{ { dot,'1' },fract },{ { dot,'2' },fract },{ { dot,'3' },fract },{ { dot,'4' },fract },
		{ { dot,'5' },fract },{ { dot,'6' },fract },{ { dot,'7' },fract },{ { dot,'8' },fract },{ { dot,'9' },fract },
		{ { fract,'0' },fract },{ { fract,'1' },fract },{ { fract,'2' },fract },{ { fract,'3' },fract },{ { fract,'4' },fract },
		{ { fract,'5' },fract },{ { fract,'6' },fract },{ { fract,'7' },fract },{ { fract,'8' },fract },{ { fract,'9' },fract },
		{ { fract,'e' },ee },
		{ { ee,'-' },exp },{ { ee,'+' },exp },
		{ { exp,'0' },exp },{ { exp,'1' },exp },{ { exp,'2' },exp },{ { exp,'3' },exp },{ { exp,'4' },exp },
		{ { exp,'5' },exp },{ { exp,'6' },exp },{ { exp,'7' },exp },{ { exp,'8' },exp },{ { exp,'9' },exp },
		{ { exp,' ' },fin }
	};
	doFST
}

bool complex_number_check(char * word)
{
	enum states
	{
		initial = 0,
		sign, //знак
		real, //целая часть
		isign, //знак перед i
		imag, // мнимая часть
		i, //i
		fin
	};
	typedef std::map<pair<states, char>, states> FST;
	FST wh = {
		{ { initial,'0' },real },{ { initial,'1' },real },{ { initial,'2' },real },{ { initial,'3' },real },{ { initial,'4' },real },
		{ { initial,'5' },real },{ { initial,'6' },real },{ { initial,'7' },real },{ { initial,'8' },real },{ { initial,'9' },real },
		{ { initial,'-' },sign },{ { initial,'+' },sign },
		{ { sign,'0' },real },{ { sign,'1' },real },{ { sign,'2' },real },{ { sign,'3' },real },{ { sign,'4' },real },
		{ { sign,'5' },real },{ { sign,'6' },real },{ { sign,'7' },real },{ { sign,'8' },real },{ { sign,'9' },real },
		{ { sign,'i' },i },
		{ { real,'0' },real },{ { real,'1' },real },{ { real,'2' },real },{ { real,'3' },real },{ { real,'4' },real },
		{ { real,'5' },real },{ { real,'6' },real },{ { real,'7' },real },{ { real,'8' },real },{ { real,'9' },real },
		{ { real,'+' },isign },{ { real,'-' },isign },{ { real,' ' },fin },
		{ { isign,'0' },imag },{ { isign,'1' },imag },{ { isign,'2' },imag },{ { isign,'3' },imag },{ { isign,'4' },imag },
		{ { isign,'5' },imag },{ { isign,'6' },imag },{ { isign,'7' },imag },{ { isign,'8' },imag },{ { isign,'9' },imag },
		{ { isign,'i' },i },
		{ { imag,'0' },imag },{ { imag,'1' },imag },{ { imag,'2' },imag },{ { imag,'3' },imag },{ { imag,'4' },imag },
		{ { imag,'5' },imag },{ { imag,'6' },imag },{ { imag,'7' },imag },{ { imag,'8' },imag },{ { imag,'9' },imag },
		{ { imag,'i' },i },
		{ { i,' ' },fin },

	};
	doFST
}

bool simple_exp_check(char * word)
{
	enum states
	{
		initial = 0,
		operation, //операция
		sign,//переменная
		fin
	};
	typedef std::map<pair<states, char>, states> FST;
	FST wh = {
		{ { initial,'a' },operation },{ { initial,'b' },operation },
		{ {operation,'+' },sign },{ { operation,'-' },sign },{ { operation,'*' },sign },{ { operation,'/' },sign },{ { operation,'^' },sign },{ { operation,'%' },sign },
		{ { operation,' ' },fin },
		{ { sign,'a' },operation },{ { sign,'b' },operation }

	};
	doFST
}

bool complex_exp_check(char * word)
{
	enum states
	{
		initial = 0,
		operation, //операция
		sign, //переменная
		obr,
		cbr,
		fin
	};
	typedef std::map<pair<states, char>, states> FST;
	FST wh = {
		{ { initial,'a' },operation },{ { initial,'b' },operation }, { { initial,'c' },operation }, { { initial,'(' },obr },
		{ { obr,'a' },operation },{ { obr,'b' },operation },{ { obr,'c' },operation }, { { obr,'(' },obr },
		{ { operation,'+' },sign },{ { operation,'-' },sign },{ { operation,'*' },sign },{ { operation,'/' },sign },{ { operation,'^' },sign },{ { operation,'%' },sign },
		{ { operation,')' },cbr },{ { operation,' ' },fin },
		{ { sign,'a' },operation },{ { sign,'b' },operation },{ { sign,'d' },operation },{ { sign,'(' },obr },
		{ { cbr,'+' },sign },{ { cbr,'-' },sign },{ { cbr,'*' },sign },{ { cbr,'/' },sign },{ { cbr,'^' },sign },{ { cbr,'%' },sign },
		{ { cbr,')' },cbr },{ { cbr,' ' },fin },
	};
	unsigned int index = 0, left_curr = 0, right_curr = 0;
	for (; index < strlen(word); index++)
	{
		if (word[index] == '(')
			left_curr++;
		if (word[index] == ')')
			right_curr++;
	}
	if (left_curr == right_curr && left_curr != 0 && right_curr != 0)
	{
		doFST
	}
	else return false;
}

int main() {
	while (true) {
		int task;
		cout << "Input number of task (1-5) or 0 for exit: ";
		cin >> task;
		string expression = "";
		if (task == 0)
			break;
		switch (task) {
		case 1: {
			cout << "Input expression for checking: ";
			cin >> expression;
			cout << (fixed_check((char*)expression.append(" ").c_str()) ? "YES" : "NO") << endl;
		} break;
		case 2: {
			cout << "Input expression for checking: ";
			cin >> expression;
			cout << (float_check((char*)expression.append(" ").c_str()) ? "YES" : "NO") << endl;
		} break;
		case 3: {
			cout << "Input expression for checking: ";
			cin >> expression;
			cout << (complex_number_check((char*)expression.append(" ").c_str()) ? "YES" : "NO") << endl;
		} break;
		case 4: {
			cout << "Input expression for checking: ";
			cin >> expression;
			cout << (simple_exp_check((char*)expression.append(" ").c_str()) ? "YES" : "NO") << endl;
		} break;
		case 5: {
			cout << "Input expression for checking: ";
			cin >> expression;
			cout << (complex_exp_check((char*)expression.append(" ").c_str()) ? "YES" : "NO") << endl;
		} break;
		}
	}
}
