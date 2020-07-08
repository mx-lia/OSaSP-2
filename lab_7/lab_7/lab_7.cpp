// lab_7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

using namespace std;

short get_nod2(short a, short b)
{
	_asm
	{
		mov ax, a
		mov bx, b
		L:	cmp ax, bx
			je End
			jl IfLess
			sub ax, bx
			jmp L
			IfLess:
				sub bx, ax
				jmp L
			End: mov a, ax
	}
	return a;
}

short get_nod3(short a, short b, short c)
{
	return get_nod2(get_nod2(a, b), c);
}

void check_bin(short a)
{
	_asm
	{
		mov ax, a
		test ax, 00000100B
		jnz One
		jz Null
		One: 
			mov ax, 1
			jmp End
		Null: 
			mov ax, 0
			jmp End
		End:
			mov a, ax
	}
	if (a == 1)
		cout << "true" << endl;
	else
		cout << "false" << endl;
}

char* my_strcpy(char* my_str)
{
	char* new_str = new char[255];
	__asm
	{
		mov esi, my_str
		mov ecx, 0ffffffffh
		checkloop:
			lodsb
			cmp al, 0
			jz replace
			loop checkloop
			replace:
				mov al, '$'
				mov [esi - 2], al
				jmp quit
			quit:
				mov eax, my_str
				mov new_str, eax
	}
	return new_str;
}

short calculate(int a, int b)
{
	_asm
	{
		mov eax, a
		mov ebx, b
		cmp eax, ebx
		jg IfMore
		FINIT
		FILD b
		FILD b
		FMUL
		FIST a
		FWAIT
		jmp End
		IfMore:
		FINIT
			FILD a
			FILD a
			FMUL
			FIST a
			FWAIT
		End : ;
	}
	return a;
}


int main()
{
	short a, b, c;
	char* my_str = new char[255];
	cout << "a -> ";
	cin >> a;
	cout << "b -> ";
	cin >> b;
	cout << "c -> ";
	cin >> c;
	cout << "nod of a and b = " << get_nod2(a, b) << endl;
	cout << "nod of a, b and c = " << get_nod3(a, b, c) << endl;
	cout << "a -> ";
	cin >> a;
	cout << "is 1 in third position of a: ";
	check_bin(a);
	cout << "Enter some string -> ";
	cin >> my_str;
	cout << "Modified string -> " << my_strcpy(my_str) << endl;
	int ia, ib;
	cout << "a -> ";
	cin >> ia;
	cout << "b -> ";
	cin >> ib;
	cout << "Resut -> " << calculate(ia, ib) << endl;
}
