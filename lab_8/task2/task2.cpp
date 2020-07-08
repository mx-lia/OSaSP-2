#include <iostream>
#include <Windows.h>

HANDLE hThread1;
DWORD IDThread1;
HANDLE hThread2;
DWORD IDThread2;
DWORD dwRet;

void CALLBACK a_proc(DWORD p)
{
	std::cout << "a_proc()" << std::endl;
}

void CALLBACK b_proc(DWORD p)
{
	std::cout << "b_proc()" << std::endl;
}


DWORD WINAPI call(LPVOID IDThread)
{
	DWORD* zz = (DWORD*)IDThread;
	std::cout << "ThreadID = " << *zz << std::endl;
	SleepEx(INFINITE, TRUE);
	return 0;

}

int main()
{
	hThread1 = CreateThread(NULL, 0, call, &IDThread1, 0, &IDThread1);
	Sleep(100);
	hThread2 = CreateThread(NULL, 0, call, &IDThread2, 0, &IDThread2);
	Sleep(100);
	dwRet = QueueUserAPC(a_proc, hThread1, 0);
	QueueUserAPC(b_proc, hThread2, 0);
	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE);
	CloseHandle(hThread1);
	CloseHandle(hThread2);
	getchar();
}