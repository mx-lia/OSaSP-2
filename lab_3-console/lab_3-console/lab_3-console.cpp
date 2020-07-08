#include "dll_lab_3.h"

#include <iostream>
#include <conio.h>
#include <tchar.h>
#include <windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	int x = PutInt(5);
	LetterList();
	std::cout << x << std::endl;
	WriteLine((char*)"D:\\Study\\OSaSP-2\\lab_3-console\\test.txt", (char*)"Hello from lab_3-console");
	RunProcess(_tcsdup(TEXT("C:\\Windows\\Notepad.exe")));
	CheckFile((char*)"D:\\Study\\OSaSP-2\\lab_3-console\\test.txt");
	_getch();
	return 0;
}
