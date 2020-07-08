#include <iostream>
#include <Windows.h>

HANDLE hThread;
DWORD IDThread;
DWORD dwRet;

void CALLBACK a_proc(DWORD p)
{
	DWORD* ptr = (DWORD*)p;
	std::cout << "The async a_proc is called!" << std::endl;
	*ptr += 10;
	std::cout << "The async a_proc returned!!" << std::endl;
}

void CALLBACK b_proc(DWORD p)
{
	DWORD* ptr = (DWORD*)p;
	std::cout << "The async b_proc is called!" << std::endl;
	*ptr += 100;
	std::cout << "The async b_proc returned!!" << std::endl;
}


DWORD WINAPI add(LPVOID ptr)
{
	DWORD* zz = (DWORD*)ptr;
	std::cout << "Thread says: initial count is " << *zz << std::endl;
	SleepEx(INFINITE, TRUE);
	std::cout << "Thread says: Final count from async proc is " << *zz << std::endl;
	return 0;

}

int main()
{
	DWORD count = 10;

	hThread = CreateThread(NULL, 0, add, &count, 0, &IDThread);
	Sleep(100);
	dwRet = QueueUserAPC(a_proc, hThread, (DWORD)&count);
	QueueUserAPC(b_proc, hThread, (DWORD)&count);
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	getchar();
}