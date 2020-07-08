#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <sstream>

#pragma warning(disable : 4996)

CRITICAL_SECTION cs;

DWORD WINAPI writer(void* lpPar)
{
	TCHAR* b = new TCHAR();
	b = (TCHAR*)lpPar;

	HANDLE hOut;
	DWORD dwBytes;
	FILE* fp;

	TCHAR stdPath[30] = TEXT("test.txt");

	EnterCriticalSection(&cs);

	hOut = CreateFile(stdPath, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hOut == INVALID_HANDLE_VALUE)
	{
		std::cout << "ERROR WRITING FILE";
		return 1;
	}
	else
	{
		WriteFile(hOut, b, 10, &dwBytes, NULL);
		std::cout << "Writer work\n";
		CloseHandle(hOut);
	}

	LeaveCriticalSection(&cs);
	return 0;
}


DWORD WINAPI reader(void* lpPar)
{
	TCHAR* b = new TCHAR();
	b = (TCHAR*)lpPar;

	HANDLE hOut;
	FILE* fp;
	DWORD dwTemp;
	char dwArr[10];

	TCHAR stdPath[30] = TEXT("test.txt");

	EnterCriticalSection(&cs);

	hOut = CreateFile(stdPath, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hOut == INVALID_HANDLE_VALUE)
	{
		std::cout << "ERROR READING FILE";
		return 1;
	}
	else
	{
		ReadFile(hOut, &dwArr, sizeof(dwArr), &dwTemp, NULL);
		std::cout << "Reader work: " << dwArr << std::endl;
		CloseHandle(hOut);
	}
	LeaveCriticalSection(&cs);
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int z = 0;
	DWORD writerID;
	DWORD readerID;

	char* u = new char();
	_itoa(123456789, u, 10);

	InitializeCriticalSection(&cs);

	HANDLE writer_handle = CreateThread(0, 0, writer, (void*)u, CREATE_SUSPENDED, &writerID);
	BOOL b = SetThreadPriorityBoost(writer_handle, false);

	if (b)
	{
		SetThreadPriority(writer_handle, THREAD_PRIORITY_HIGHEST);
	}

	HANDLE reader_handle = CreateThread(0, 0, reader, &z, CREATE_SUSPENDED, &readerID);

	ResumeThread(writer_handle);
	ResumeThread(reader_handle);
	WaitForSingleObject(writer_handle, 10000);
	WaitForSingleObject(reader_handle, 10000);

	TerminateThread(writer_handle, 0);
	TerminateThread(reader_handle, 0);

	getchar();

	return 0;
}