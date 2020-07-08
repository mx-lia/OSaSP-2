#include <iostream>
#include <windows.h>

typedef int(__stdcall* f_funci)();
typedef int(__cdecl* f_funcsum)(int, int);
typedef int(__cdecl* f_funcmul)(int, int);
typedef int(__cdecl* f_funcdiv)(int, int);

int main()
{
	HINSTANCE hProcID = LoadLibrary(TEXT("D:\\Study\\OSaSP-2\\dll_lab_4\\Debug\\dll_lab_4.dll"));


	if (!hProcID) {
		std::cout << "could not load the dynamic library\n" << GetLastError() << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "Dll found!!!!" << std::endl;

	f_funci funci = (f_funci)GetProcAddress(hProcID, "SendMess");
	if (!funci) {
		std::cout << "could not locate the function\n" << GetLastError() << std::endl;
		getchar();
		FreeLibrary(hProcID);
		return EXIT_FAILURE;
	}

	std::cout << "SendMess found " << std::endl;

	int x = (funci)();
	std::cout << "SendMess returned " << x << std::endl;

	f_funcsum funcsum = (f_funcsum)GetProcAddress(hProcID, "GetSum");
	if (!funcsum) {
		std::cout << "could not locate the function\n" << GetLastError() << std::endl;
		getchar();
		FreeLibrary(hProcID);
		return EXIT_FAILURE;
	}

	std::cout << "GetSum found " << std::endl;

	int sum = (funcsum)(7, 10);
	std::cout << "GetSum returned " << sum << std::endl;

	f_funcmul funcmul = (f_funcmul)GetProcAddress(hProcID, "GetMul");
	if (!funcmul) {
		std::cout << "could not locate the function\n" << GetLastError() << std::endl;
		getchar();
		FreeLibrary(hProcID);
		return EXIT_FAILURE;
	}

	std::cout << "GetMul found " << std::endl;

	int mul = (funcmul)(7, 10);
	std::cout << "GetMul returned " << mul << std::endl;

	f_funcdiv funcdiv = (f_funcdiv)GetProcAddress(hProcID, "GetDiv");
	if (!funcdiv) {
		std::cout << "could not locate the function\n" << GetLastError() << std::endl;
		getchar();
		FreeLibrary(hProcID);
		return EXIT_FAILURE;
	}

	std::cout << "GetDiv found " << std::endl;

	int div = (funcdiv)(70, 10);
	std::cout << "GetDiv returned " << div << std::endl;

	getchar();
	FreeLibrary(hProcID);
	return EXIT_SUCCESS;
}
