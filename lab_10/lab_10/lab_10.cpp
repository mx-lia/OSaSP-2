#define _CRT_SECURE_NO_WARNINGS

#include <windows.h> 
#include <iostream> 
#include <ctime>

using namespace std;

VOID CALLBACK completion_routine1(
	DWORD dwErrorCode, // код возврата 
	DWORD dwNumberOfBytesTransferred, // количество переданных байтов 
	LPOVERLAPPED lpOverlapped // асинхронная передача данных 
)
{
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	cout << "Процедура 1 завершена с параметрами: " << endl << "Код ошибки: " << dwErrorCode << endl << "\tВремя завершения записи в файл: " << asctime(timeinfo) 
		<< "\tЧисло  записанных байтов: " << dwNumberOfBytesTransferred << endl << "\tOffsets: " << (*lpOverlapped).OffsetHigh << ' ' << (*lpOverlapped).Offset << endl;
}

VOID CALLBACK competition_routine2(
	DWORD dwErrorCode, // код возврата 
	DWORD dwNumberOfBytesTransferred, // количество переданных байтов 
	LPOVERLAPPED lpOverlapped // асинхронная передача данных 
)
{
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	cout << "Процедура 2 завершена с параметрами: " << endl << "Код ошибки: " << dwErrorCode << endl << "\tВремя завершения записи в файл: " << asctime(timeinfo)
		<< "\tЧисло  записанных байтов: " << dwNumberOfBytesTransferred << endl << "\tOffsets: " << (*lpOverlapped).OffsetHigh << ' ' << (*lpOverlapped).Offset << endl;
}

int main()
{
	setlocale(LC_ALL, "ru");
	VOID(__stdcall * competition_procedure)(DWORD, DWORD, LPOVERLAPPED) = &completion_routine1;
	HANDLE hFile; // дескриптор файла 
	OVERLAPPED ovl; // структура управления асинхронным доступом к файлу 
	// инициализируем структуру OVERLAPPED 
	ovl.Offset = 0; // младшая часть смещения равна 0 
	ovl.OffsetHigh = 0; // старшая часть смещения равна 0 
	// создаем или открываем файл для записи данных 
	hFile = CreateFile(L"demo_file.txt", // имя файла 
		GENERIC_WRITE, // запись в файл 
		FILE_SHARE_WRITE, // совместный доступ к файлу 
		NULL, // защиты нет 
		OPEN_ALWAYS, // открываем или создаем новый файл 
		FILE_FLAG_OVERLAPPED, // асинхронный доступ к файлу 
		NULL // шаблона нет 
	);
	// проверяем на успешное создание 
	if (hFile == INVALID_HANDLE_VALUE)
	{
		cerr << "Файл не создан" << endl << "Ошибка: " << GetLastError() << endl;
		cout << "Нажмите любую клавишу";
		cin.get();
		return 0;
	}

	// пишем данные в файл 
	for (int i = 0; i < 2; ++i)
	{
		if (i == 1)
		{
			competition_procedure = &competition_routine2;
		}
		else
		{
			competition_procedure = &completion_routine1;
		}
		DWORD dwRet;
		char temp[64];
		_itoa(i, temp, 10);
		if (!WriteFileEx(
			hFile, // дескриптор файла 
			&temp, // адрес буфера, откуда идет запись 
			2, // количество записываемых байтов 
			&ovl, // запись асинхронная 
			competition_procedure // процедура завершения 
		))
		{
			dwRet = GetLastError();
			if (dwRet == ERROR_IO_PENDING)
				cout << "Write file pending." << endl;
			else
			{
				cout << "Запись закончилась ошибкой" << endl << "Код ошибки: " << dwRet << endl;
				return 0;
			}
		}
		// ждем, пока сработает асинхронная процедура 
		// завершения операции вывода 
		SleepEx(INFINITE, TRUE);
		// увеличивает смещение в файле 
		ovl.Offset += 2;
	}
	CloseHandle(hFile);
	cout << "Запись завершена" << endl;
	return 0;
}
