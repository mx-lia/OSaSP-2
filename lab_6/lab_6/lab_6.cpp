// lab_6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "windows.h"
#include <ole2.h>
#include <oaidl.h>
#include<string>
#include<string.h>
#include <tchar.h>                 
#include <cstdio>  
#include <conio.h>
#include "dll.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "RUS");
	//OpenWord();
	WIN32_FIND_DATA FindFileData;
	//HANDLE hFind;
	TCHAR files[MAX_PATH];
	cout << "Введите путь файла: ";
	wcin >> files;
	HANDLE handle = FindFirstFile(files, &FindFileData);

	if (INVALID_HANDLE_VALUE != handle)
	{
		cout << "Файл найден:";
		std::wcout << FindFileData.cFileName << endl;
		CallWord(files);
	}
	else
	{
		cout << "Файл не найден";
	}

	getchar();
}
