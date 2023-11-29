#pragma once
#include <iostream>
#include <stdlib.h>
#include "MyString2.h"

// Длинное число
struct LongNumber2
{
	int sign;
	MyString2 str;
};

// Освободить память, занимаемую длинным числом
void FreeNum(LongNumber2* num)
{
	FreeStr(&num->str); // exception
	free(num);
}

// Преобразовать модуль числа в его строковое представление
MyString2* Num2Str2(long long num)
{
	MyString2* result = (MyString2*)malloc(sizeof(MyString2));
	char* temp = (char*)malloc(30);
	int index = 0;
	if (num > 0) num = -num;
	while (num < 0)
	{
		temp[index] = '0' - (num % 10);
		++index;
		num /= 10;
	}
	temp[index] = 0;
	StrInit(result, temp);
	free(temp);
	Reverse(result);
	return result;
}

// Отсечь незначащие нули у строки (последний нуль не отсекается)
// "(0...0)0" -> "0"
void StripLeadingZeros(MyString2* str)
{
	if (str->symbols[0] != '0') return;
	int zeros = 0;
	while (str->symbols[zeros] == '0' && zeros < (str->length - 1)) ++zeros;
	str->length -= zeros;
	char* buff = (char*)malloc(str->length + 1);
	for (int i = 0; i < str->length; ++i) buff[i] = str->symbols[i + zeros];
	buff[str->length] = 0;
	free(str->symbols);
	str->symbols = buff;
}

// Инициализация длинного числа - 0
void LongNumberInit(LongNumber2* num)
{
	num->sign = 0;
	StrInit(&num->str);
}

// Инициализация длинного числа с использованием модуля и знака
void LongNumberInit(LongNumber2* num, const char* value, const int sign)
{
	StrInit(&num->str);
	if (sign != 0)
	{
		AddAssign(&num->str, value);
		StripLeadingZeros(&num->str);
	}
	num->sign = Equals(&num->str, "") || Equals(&num->str, "0") ? 0 : sign;
}

// Инициализация длинного числа с использованием модуля и знака
void LongNumberInit(LongNumber2* num, const MyString2* value, const int sign)
{
	LongNumberInit(num, value->symbols, sign);
}

// Инициализация длинного числа с использованием примитивного типа
void LongNumberInit(LongNumber2* num, const long long value)
{
	MyString2* str = Num2Str2(value);
	StrInit(&num->str, str);
	FreeStr(str);
	num->sign = (value > 0 ? 1 : value < 0 ? -1 : 0);
}

// Инициализация длинного числа из другого
void LongNumberInit(LongNumber2* num, const LongNumber2* from)
{
	num->sign = from->sign;
	Assign(&num->str, &from->str);
}

// Строковое представление длинного числа
const MyString2* ToString(const LongNumber2* num)
{
	MyString2* result = (MyString2*)malloc(sizeof(MyString2));
	StrInit(result);
	if (num->sign == 0)
	{
		AddAssign(result, '0');
		return result;
	}
	SetCapacity(result, num->sign == -1 ? num->str.length + 1 : num->str.length);
	if (num->sign == -1) AddAssign(result, '-');
	AddAssign(result, &num->str);
	return result;
}

// Модуль числа
LongNumber2* Abs(const LongNumber2* num)
{
	LongNumber2* result = (LongNumber2*)malloc(sizeof(LongNumber2));
	LongNumberInit(result, &num->str, 1);
	return result;
}

void NumAssign(LongNumber2* num, const LongNumber2* other)
{
	Assign(&num->str, &other->str);
	num->sign = other->sign;
}

// Присвоить значение длинному числу
void NumAssign(LongNumber2* num, const long long val)
{
	num->sign = (val > 0 ? 1 : val < 0 ? -1 : 0);
	MyString2* str = Num2Str2(val);
	Assign(&num->str, str);
	FreeStr(str);
}

// Сравнение модулей двух чисел
// Возврат:
// 1, если |a| > |b|;
// 0, если a == b;
// -1, если |a| < |b|.
int CompareAbs(const LongNumber2* a, const LongNumber2* b)
{
	if (a->str.length > b->str.length) return 1;
	if (a->str.length < b->str.length) return -1;
	const int cmp = strcmp(a->str.symbols, b->str.symbols);
	return cmp > 0 ? 1 : cmp < 0 ? -1 : 0;
}

// Сравнение двух чисел
// Возврат:
// 1 if a > b;
// 0 if a == b;
// -1 if a < b.
int Compare(const LongNumber2* a, const LongNumber2* b)
{
	const int cmp = CompareAbs(a, b);
	if (cmp == 1) return a->sign;
	if (cmp == -1) return b->sign;
	return a->sign == b->sign ? 0 : a->sign;
}

// Беззнаковое сумма двух чисел
MyString2* UnsignedAdd(const MyString2* a, const MyString2* b)
{
	MyString2* result = (MyString2*)malloc(sizeof(MyString2));
	StrInit(result, (a->length > b->length ? a->length : b->length) + 1);
	int indexA = a->length - 1;
	int indexB = b->length - 1;
	int carry = 0;
	while (1)
	{
		const int digit1 = indexA < 0 ? 0 : (a->symbols[indexA] - '0');
		const int digit2 = indexB < 0 ? 0 : (b->symbols[indexB] - '0');
		const int res = digit1 + digit2 + carry;
		if (res == 0 && (indexA > indexB ? indexA : indexB) < 0) break;
		carry = res / 10;
		AddAssign(result, (res % 10) + '0');
		--indexA;
		--indexB;
	}
	Reverse(result);
	ShrinkToFit(result);
	return result;
}

// Беззнаковая разность двух чисел, причём a >= b
MyString2* UnsignedSubtract(const MyString2* a, const MyString2* b)
{
	int indexA = a->length - 1;
	int indexB = b->length - 1;
	int carry = 0;
	int zeros = 0;
	MyString2* result = (MyString2*)malloc(sizeof(MyString2));
	StrInit(result, (a->length > b->length ? a->length : b->length));
	while (1)
	{
		const int digit1 = indexA < 0 ? 0 : (a->symbols[indexA] - '0');
		const int digit2 = indexB < 0 ? 0 : (b->symbols[indexB] - '0');
		const int res = digit1 - digit2 + carry;
		const int toAppend = res < 0 ? res + 10 : res;
		carry = res < 0 ? -1 : 0;
		if (toAppend == 0)
		{
			if ((indexA > indexB ? indexA : indexB) < 0 && res != -10) break;
			++zeros;
		}
		else
		{
			for (int i = 0; i < zeros; ++i) AddAssign(result, '0');
			zeros = 0;
			AddAssign(result, toAppend + '0');
		}
		--indexA;
		--indexB;
	}
	Reverse(result);
	if (result->length == 0) AddAssign(result, '0');
	ShrinkToFit(result);
	return result;
}
// Беззнаковое произведение двух чисел
MyString2* UnsignedMultiply(const MyString2* a, const MyString2* b)
{
	const MyString2* longer = a->length > b->length ? a : b;
	const MyString2* shorter = a->length <= b->length ? a : b;
	MyString2* result = (MyString2*)malloc(sizeof(MyString2));
	if (shorter->length == 0 || Equals(shorter, "0")) StrInit(result, "0");
	else if (Equals(shorter, "1")) StrInit(result, longer);
	else if (shorter->length == 1)
	{
		StrInit(result, longer->length);
		int carry = 0;
		int index = longer->length - 1;
		const int digit = shorter->symbols[0] - '0';
		while (1)
		{
			const int digit2 = index < 0 ? 0 : (longer->symbols[index] - '0');
			const int res = digit * digit2 + carry;
			if (res == 0 && index < 0) break;
			carry = res / 10;
			AddAssign(result, (res % 10) + '0');
			--index;
		}
		Reverse(result);
	}
	else
	{
		const int n = longer->length / 2;
		const int index = (0 > shorter->length - n ? 0 : shorter->length - n);
		MyString2* A = Slice(longer, 0, longer->length - n);
		MyString2* B = Slice(longer, longer->length - n, longer->length);
		StripLeadingZeros(B);
		MyString2* C = Slice(shorter, 0, index);
		MyString2* D = Slice(shorter, index, shorter->length);
		StripLeadingZeros(D);
		MyString2* AC = UnsignedMultiply(A, C);
		MyString2* BD = UnsignedMultiply(B, D);
		MyString2* A_P_B = UnsignedAdd(A, B); // A+B
		FreeStr(A);
		FreeStr(B);
		MyString2* C_P_D = UnsignedAdd(C, D); // C+D
		FreeStr(C);
		FreeStr(D);
		MyString2* A_P_B_TIMES_C_P_D = UnsignedMultiply(A_P_B, C_P_D); // [A+B]*[C+D] | (1)
		FreeStr(A_P_B);
		FreeStr(C_P_D);
		MyString2* ONE_MIN_AC = UnsignedSubtract(A_P_B_TIMES_C_P_D, AC); // [A+B]*[C+D] - AC | (1) - AC
		FreeStr(A_P_B_TIMES_C_P_D);
		MyString2* AD_PLUS_BC = UnsignedSubtract(ONE_MIN_AC, BD); // [A+B]*[C+D] - AC - BD
		MyString2* zeros_2n = (MyString2*)malloc(sizeof(MyString2));
		MyString2* zeros_n = (MyString2*)malloc(sizeof(MyString2));
		StrInit(zeros_2n, '0', n << 1);
		StrInit(zeros_n, '0', n);
		AddAssign(AC, zeros_2n);
		FreeStr(zeros_2n);
		AddAssign(AD_PLUS_BC, zeros_n);
		FreeStr(zeros_n);
		MyString2* value = UnsignedAdd(UnsignedAdd(AC, AD_PLUS_BC), BD);
		StrInit(result, value);
		FreeStr(value);
		FreeStr(AC);
		FreeStr(BD);
		FreeStr(AD_PLUS_BC);
	}
	return result;
}

// Сложение двух чисел
LongNumber2* Add(const LongNumber2* a, const LongNumber2* b)
{
	LongNumber2* result = (LongNumber2*)malloc(sizeof(LongNumber2));
	if (a->sign == 0) LongNumberInit(result, b);
	else if (b->sign == 0) LongNumberInit(result, a);
	else if (a->sign == b->sign)
	{
		MyString2* sum = UnsignedAdd(&a->str, &b->str);
		LongNumberInit(result, sum, a->sign);
		FreeStr(sum);
	}
	else
	{
		const LongNumber2* bigger = CompareAbs(a, b) >= 0 ? a : b;
		const LongNumber2* smaller = bigger == b ? a : b;
		MyString2* diff = UnsignedSubtract(&bigger->str, &smaller->str);
		LongNumberInit(result, diff, bigger->sign);
		FreeStr(diff);
	}
	return result;
}

// Разность двух чисел
LongNumber2* Difference(const LongNumber2* a, const LongNumber2* b)
{
	LongNumber2* result = (LongNumber2*)malloc(sizeof(LongNumber2));
	if (a->sign == 0) LongNumberInit(result, &b->str, -b->sign);
	else if (b->sign == 0) LongNumberInit(result, a);
	else if (a->sign == b->sign)
	{
		const LongNumber2* bigger = CompareAbs(a, b) >= 0 ? a : b;
		const LongNumber2* smaller = bigger == b ? a : b;
		MyString2* diff = UnsignedSubtract(&bigger->str, &smaller->str);
		LongNumberInit(result, diff, bigger == a ? a->sign : -b->sign);
		FreeStr(diff);
	}
	else
	{
		MyString2* sum = UnsignedAdd(&a->str, &b->str);
		LongNumberInit(result, sum, a->sign);
		FreeStr(sum);
	}
	return result;
}

// Произведение двух чисел
LongNumber2* Product(const LongNumber2* a, const LongNumber2* b)
{
	LongNumber2* result = (LongNumber2*)malloc(sizeof(LongNumber2));
	MyString2* str = UnsignedMultiply(&a->str, &b->str);
	LongNumberInit(result, str, a->sign * b->sign);
	FreeStr(str);
	return result;
}