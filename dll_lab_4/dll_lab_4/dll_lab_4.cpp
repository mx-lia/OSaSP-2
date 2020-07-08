#include "pch.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

__declspec(dllexport) int SquareInt(int param);
__declspec(dllexport) int SendMess();
__declspec(dllexport) int GetSum(int a, int b);
__declspec(dllexport) int GetMul(int a, int b);
__declspec(dllexport) int GetDiv(int a, int b);

int SquareInt(int param)
{
	return param * param;
}

int SendMess()
{
	return 100;
}

int GetSum(int a, int b)
{
	return a + b;
}

int GetMul (int a, int b)
{
	return a * b;
}

int GetDiv (int a, int b)
{
	return a / b;
}