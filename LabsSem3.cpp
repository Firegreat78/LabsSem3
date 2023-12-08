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
LongNumber arr2d[5][5]; // ������� � ����

int main()
{
	LongNumber st_arr[2];
	LongNumber st_arr2d[2][2]; // ������� � ����� ����� � ������ try
	exception a;
	try
	{
		st_arr[0] = 54347537472;
		st_arr[1] = -5434753232327472;
		st_arr2d[1][0] = 694;
		st_arr2d[0][0] = -44123631;
		arr2d[1][2] = 123; // �������� �����������
		arr2d[0][1] = 14344523; // �������� �����������
		arr[0] = LongNumber(LongNumber::max_abs, 1); // ����������, �. �. ���������� ����� ������� ����� ������������
		arr[3] = LongNumber(LongNumber::max_abs, 1); // ����������, �. �. ���������� ����� ������� ����� ������������
		arr[1] = arr[0] + 434; // arr[1] ����� � ��� ���������, � ����� �� ��� �� ����� try, ��������� (arr[0] + 434) �� ����� "���������"
		arr[2] = 434; // �� ����������, �. �. ���������� ���� ������� �� ������������
	}
	catch (const exception e)
	{

	}

	try
	{
		string numeric;
		cout << "Enter a numeric string: ";
		cin >> numeric; cout << '\n';
		LongNumber num(numeric, -1); // ���� �������������
		cout << "Number: " << num.ToString() << '\n';
	}

	catch (const std::invalid_argument e) // ����� ����������� ������ ���� ����������
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
		non_printable += 6; // ����������� ������
	}

	catch (std::exception e)
	{

	}

	try
	{
		non_printable[0] = 4; // ����������� ������ (�� ��������)
	}

	catch (std::exception e)
	{

	}
}
