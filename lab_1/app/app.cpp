#include <iostream>
#include <objbase.h>

interface IX :IUnknown
{
	virtual void __stdcall Fx() = 0;
	virtual void __stdcall GetSquare(int number) = 0;
};

interface IY :IUnknown
{
	virtual void __stdcall Fy() = 0;
};