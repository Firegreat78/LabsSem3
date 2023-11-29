#pragma once
#include <string.h>
#include <stdlib.h>

struct MyString2
{
	char* symbols = NULL;
	int capacity; // ёмкость строки (кол-во символов, не считая '\0', которое может содержать строка без выделения доп. памяти)
	int length; // длина строки 
};

// Освободить память, занимаемую строкой
void FreeStr(MyString2* str)
{
	free(str->symbols);
	free(str);
}

// Инициализация пустой строки
void StrInit(MyString2* str)
{
	str->symbols = (char*)malloc(1);
	str->capacity = str->length = str->symbols[0] = 0;
}

// Инициализация пустой строки с указанной начальной ёмкостью
void StrInit(MyString2* str, const int capacity)
{
	str->capacity = capacity;
	str->symbols = (char*)malloc(capacity + 1);
	str->symbols[0] = str->length = 0;
}

// Инициализация строки содержащей n повторяющихся символов
void StrInit(MyString2* str, const char ch, const int val)
{
	str->capacity = str->length = val;
	str->symbols = (char*)malloc(val + 1);
	for (int i = 0; i < val; ++i) str->symbols[i] = ch;
	str->symbols[val] = 0;
}

// Инициализация строки из стандартной строки языка C
void StrInit(MyString2* str, const char* arr)
{
	str->capacity = str->length = strlen(arr);
	str->symbols = (char*)malloc(str->capacity + 1);
	for (int i = 0; i < str->capacity; ++i) str->symbols[i] = arr[i];
	str->symbols[str->capacity] = 0;
}

// Инициализация строки из стандартной строки языка C, которая имеет заданную начальную ёмкость
void StrInit(MyString2* str, const char* arr, const int capacity)
{
	str->capacity = capacity;
	str->symbols = (char*)malloc(capacity + 1);
	const int arrlen = strlen(arr);
	str->length = arrlen;
	const int len = arrlen < capacity ? arrlen : capacity;
	for (int i = 0; i < len; ++i) str->symbols[i] = arr[i];
	str->symbols[len] = 0;
}

// Инициализация строки из другой строки, которая имеет заданную начальную ёмкость.
void StrInit(MyString2* str, const MyString2* from, const int capacity)
{
	str->capacity = capacity;
	str->symbols = (char*)malloc(capacity + 1);
	str->length = from->length;
	const int len = from->length < capacity ? from->length : capacity;
	for (int i = 0; i < len; ++i) str->symbols[i] = from->symbols[i];
	str->symbols[len] = 0;
}

// Инициализация строки из другой строки.
void StrInit(MyString2* str, const MyString2* from)
{
	str->capacity = str->length = from->length;
	str->symbols = (char*)malloc(from->length + 1);
	for (int i = 0; i < from->length; ++i) str->symbols[i] = from->symbols[i];
	str->symbols[str->capacity] = 0;
}

// Установить ёмкость строки.
void SetCapacity(MyString2* str, const int capacity)
{
	str->capacity = capacity;
	str->symbols = (char*)realloc(str->symbols, capacity + 1);
	if (capacity < str->length)
	{
		str->symbols[capacity] = 0;
		str->length = capacity;
	}
}

// Скопировать символы из стандартной строки языка С в данную строку.
MyString2* Assign(MyString2* lhs, const char* rhs)
{
	const int len = strlen(rhs);
	lhs->length = len;
	SetCapacity(lhs, len);
	for (int i = 0; i <= len; ++i) lhs->symbols[i] = rhs[i];
	return lhs;
}

// Скопировать символы из одной строки в другую.
MyString2* Assign(MyString2* lhs, const MyString2* rhs)
{
	if (lhs == rhs) return lhs;
	return Assign(lhs, rhs->symbols);
}

// Установить ёмкость строки, равную её длине.
void ShrinkToFit(MyString2* str)
{
	SetCapacity(str, str->length);
}

// Создать строку, символы которой записаны в обратном порядке.
MyString2* Reversed(const MyString2* str)
{
	MyString2* result = (MyString2*)malloc(sizeof(MyString2));
	StrInit(result, str->length);
	for (int i = 0; i < str->length; ++i) result->symbols[i] = str->symbols[str->length - i - 1];
	result->symbols[str->length] = 0;
	return result;
}

// Обратить порядок символов в текущей строке, не создавая новую.
void Reverse(MyString2* str)
{
	char* temp = (char*)malloc(str->capacity + 1);
	for (int i = 0; i < str->length; ++i) temp[i] = str->symbols[str->length - i - 1];
	temp[str->length] = 0;
	free(str->symbols);
	str->symbols = temp;
}

// Получить подстроку из строки.
MyString2* Slice(const MyString2* str, const int startInclusive, const int endExclusive) // fix
{
	if (endExclusive < startInclusive || str->length < endExclusive) return NULL;
	const int size = endExclusive - startInclusive;
	char* buff = (char*)malloc(size + 1);
	for (int i = 0; i < size; ++i) buff[i] = str->symbols[startInclusive + i];
	buff[size] = 0;
	MyString2* subStr = (MyString2*)malloc(sizeof(MyString2));
	StrInit(subStr, buff);
	free(buff);
	return subStr;
}

// Проверить равенство двух строк
int Equals(const MyString2* str, const char* rhs)
{
	if (str->length != strlen(rhs)) return 0;
	return strcmp(str->symbols, rhs) == 0;
}

// Проверить равенство двух строк
int Equals(const MyString2* str, const MyString2* rhs)
{
	if (str->length != rhs->length) return 0;
	return strcmp(str->symbols, rhs->symbols);
}

// Получить символ, находящийся на определённой позиции
char Index(const MyString2* str, const int index)
{
	if (index >= str->length) return NULL;
	return str->symbols[index];
}

// Конкатенация двух строк
MyString2* Add(const MyString2* str, const char* rhs)
{
	const int len2 = strlen(rhs);
	char* arr = (char*)malloc(str->length + len2 + 1);
	for (int i = 0; i < str->length; ++i) arr[i] = str->symbols[i];
	for (int i = 0; i < len2; ++i) arr[str->length + i] = rhs[i];
	arr[str->length + len2] = 0;
	MyString2* result = (MyString2*)malloc(sizeof(MyString2));
	StrInit(result, arr);
	return result;
}

// Конкатенация двух строк
MyString2* Add(const MyString2* str, const MyString2* rhs)
{
	return Add(str, rhs->symbols);
}
// Добавить символ в конец строки
MyString2* Add(const MyString2* str, const char ch)
{
	MyString2* result = (MyString2*)malloc(sizeof(MyString2));
	StrInit(result, str, str->length + 1);
	result->symbols[str->length] = ch;
	result->symbols[str->length + 1] = 0;
	result->length = str->length + 1;
	return result;
}

// Конкатенация двух строк без создания новой
MyString2* AddAssign(MyString2* str, const char* rhs)
{
	const int len = strlen(rhs);
	if (str->capacity < str->length + len) SetCapacity(str, str->length + len);
	for (int i = 0; i < len; ++i) str->symbols[str->length + i] = rhs[i];
	str->symbols[str->length + len] = 0;
	str->length += len;
	return str;
}

// Конкатенация двух строк без создания новой
MyString2* AddAssign(MyString2* str, const MyString2* rhs)
{
	return AddAssign(str, rhs->symbols);
}

// Добавить символ в конец строки.
MyString2* AddAssign(MyString2* str, const char ch)
{
	if (str->capacity == str->length) SetCapacity(str, str->capacity + 1);
	str->symbols[str->length] = ch;
	str->symbols[str->length + 1] = 0;
	++str->length;
	return str;
}

// Создать новую строку путём слияния n одинаковых строк.
MyString2* Multiply(const MyString2* str, const int val) // fix
{
	if (val < 0) return NULL;
	MyString2* result = (MyString2*)malloc(sizeof(MyString2));
	const int cnt = str->length * val;
	StrInit(result, str, cnt);
	for (int i = str->length; i < cnt; ++i) result->symbols[i] = str->symbols[i % str->length];
	result->symbols[cnt] = 0;
	result->length = cnt;
	return result;
}

// Расширить строку
MyString2* MultiplyAssign(MyString2* str, const int val)
{
	if (val < 0) return NULL;
	const int cnt = str->length * val;
	if (str->capacity < cnt) SetCapacity(str, cnt);
	for (int i = str->length; i < cnt; ++i) str->symbols[i] = str->symbols[i % str->length];
	str->symbols[cnt] = 0;
	str->length *= val;
}

// Проверить, является ли строка числовой.
int IsNumeric(const MyString2* str)
{
	for (int i = 0; i < str->length; ++i) { if (str->symbols[i] < '0' || str->symbols[i] > '9') return 0; }
	return 1;
}