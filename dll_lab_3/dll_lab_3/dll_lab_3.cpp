#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <time.h>

using namespace std;

extern "C++" __declspec(dllexport) void LetterList()
{
	std::cout << "This function was called from LetterList() " << std::endl;
}

extern "C++" __declspec(dllexport) int PutInt(int param)
{
	return param;
}

extern "C++" __declspec(dllexport) void WriteLine(char* fileName, char* str)
{
	FILE* file = fopen(fileName, "w");
	if (file)
	{
		bool result = fputs(str, file);
		if (!result)
			cout << "Writting is successed" << endl;
		fclose(file);
	}
	else
		cout << "File is not available" << endl;
}

extern "C++" __declspec(dllexport) bool RunProcess(wchar_t* process)
{
	STARTUPINFO cif;
	ZeroMemory(&cif, sizeof(STARTUPINFO));
	PROCESS_INFORMATION pi;
	if (!(CreateProcess(NULL, process, NULL, NULL, FALSE, 0, NULL, NULL, &cif, &pi)))
	{
		cout << "Error" << endl;
		return false;
	}
	else
	{
		cout << "Process is started" << endl;
		return true;
	}
}

extern "C++" __declspec(dllexport) bool CheckFile(char* fileName)
{
	FILE* file = fopen(fileName, "r");
	if (file) 
	{
		fclose(file);
		cout << "File exists" << endl;
		return true;
	}
	else
	{
		cout << "File not found" << endl;
		return false;
	}
}

extern "C++" __declspec(dllexport) BOOL EdrCenterText(HDC hdc, PRECT prc, LPCWSTR pStr)
{
	int iLength;
	SIZE size;
	iLength = wcslen(pStr);
	GetTextExtentPoint32(hdc, pStr, iLength, &size);
	return TextOut(hdc, (prc->right - prc->left - size.cx) / 2, (prc->bottom - prc->top - size.cy) / 2, pStr, iLength);
}

extern "C" __declspec(dllexport) int __stdcall AddNumbers(int x, int y)
{
	return x + y;
}

extern "C" __declspec(dllexport) char* __stdcall GetTime()
{
	time_t my_time = time(NULL);
	return  ctime(&my_time);
}

