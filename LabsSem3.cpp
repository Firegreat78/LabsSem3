#include <iostream>
#include <vector>
#include "LongNumber.h"
#include "MyString.h"

using std::string;
using std::cout;
using std::cin;
using std::vector;
using std::swap;
using std::exception;

LongNumber arr[4];
LongNumber arr2d[5][5]; // массивы в куче

int main()
{
	LongNumber st_arr[2];
	LongNumber st_arr2d[2][2]; // массивы в стеке рядом с блоком try
	exception a;
	try
	{
		st_arr[0] = 54347537472;
		st_arr[1] = -5434753232327472;
		st_arr2d[1][0] = 694;
		st_arr2d[0][0] = -44123631;
		arr2d[1][2] = 123; // значение сохраняется
		arr2d[0][1] = 14344523; // значение сохраняется
		arr[0] = LongNumber(LongNumber::max_abs, 1); // выполнится, т. к. исключение будет вызвано после присваивания
		arr[3] = LongNumber(LongNumber::max_abs, 1); // выполнится, т. к. исключение будет вызвано после присваивания
		arr[1] = arr[0] + 434; // arr[1] будет в том состоянии, в каком он был до блока try, выражение (arr[0] + 434) не будет "вычислено"
		arr[2] = 434; // не выполнится, т. к. исключение было вызвано до присваивания
	}
	catch (const exception e)
	{

	}

	try
	{
		string numeric;
		cout << "Enter a numeric string: ";
		cin >> numeric; cout << '\n';
		LongNumber num(numeric, -1); // знак отрицательный
		cout << "Number: " << num.ToString() << '\n';
	}

	catch (const std::invalid_argument e) // можно отлавливать разные типы исключений
	{
		cout << "Exception description: ";
		cout << e.what();
	}

	catch (const std::logic_error e)
	{
		cout << "Exception description: ";
		cout << e.what();
	}


	MyString non_printable = "12345";
	try
	{
		non_printable += 6; // управляющий символ
	}

	catch (std::exception e)
	{

	}

	try
	{
		non_printable[0] = 4; // управляющий символ (не отловлен)
	}

	catch (std::exception e)
	{

	}
}
