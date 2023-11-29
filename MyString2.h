#pragma once
#include <string.h>
#include <stdlib.h>

struct MyString2
{
	char* symbols = NULL;
	int capacity; // ������� ������ (���-�� ��������, �� ������ '\0', ������� ����� ��������� ������ ��� ��������� ���. ������)
	int length; // ����� ������ 
};

// ���������� ������, ���������� �������
void FreeStr(MyString2* str)
{
	free(str->symbols);
	free(str);
}

// ������������� ������ ������
void StrInit(MyString2* str)
{
	str->symbols = (char*)malloc(1);
	str->capacity = str->length = str->symbols[0] = 0;
}

// ������������� ������ ������ � ��������� ��������� ��������
void StrInit(MyString2* str, const int capacity)
{
	str->capacity = capacity;
	str->symbols = (char*)malloc(capacity + 1);
	str->symbols[0] = str->length = 0;
}

// ������������� ������ ���������� n ������������� ��������
void StrInit(MyString2* str, const char ch, const int val)
{
	str->capacity = str->length = val;
	str->symbols = (char*)malloc(val + 1);
	for (int i = 0; i < val; ++i) str->symbols[i] = ch;
	str->symbols[val] = 0;
}

// ������������� ������ �� ����������� ������ ����� C
void StrInit(MyString2* str, const char* arr)
{
	str->capacity = str->length = strlen(arr);
	str->symbols = (char*)malloc(str->capacity + 1);
	for (int i = 0; i < str->capacity; ++i) str->symbols[i] = arr[i];
	str->symbols[str->capacity] = 0;
}

// ������������� ������ �� ����������� ������ ����� C, ������� ����� �������� ��������� �������
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

// ������������� ������ �� ������ ������, ������� ����� �������� ��������� �������.
void StrInit(MyString2* str, const MyString2* from, const int capacity)
{
	str->capacity = capacity;
	str->symbols = (char*)malloc(capacity + 1);
	str->length = from->length;
	const int len = from->length < capacity ? from->length : capacity;
	for (int i = 0; i < len; ++i) str->symbols[i] = from->symbols[i];
	str->symbols[len] = 0;
}

// ������������� ������ �� ������ ������.
void StrInit(MyString2* str, const MyString2* from)
{
	str->capacity = str->length = from->length;
	str->symbols = (char*)malloc(from->length + 1);
	for (int i = 0; i < from->length; ++i) str->symbols[i] = from->symbols[i];
	str->symbols[str->capacity] = 0;
}

// ���������� ������� ������.
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

// ����������� ������� �� ����������� ������ ����� � � ������ ������.
MyString2* Assign(MyString2* lhs, const char* rhs)
{
	const int len = strlen(rhs);
	lhs->length = len;
	SetCapacity(lhs, len);
	for (int i = 0; i <= len; ++i) lhs->symbols[i] = rhs[i];
	return lhs;
}

// ����������� ������� �� ����� ������ � ������.
MyString2* Assign(MyString2* lhs, const MyString2* rhs)
{
	if (lhs == rhs) return lhs;
	return Assign(lhs, rhs->symbols);
}

// ���������� ������� ������, ������ � �����.
void ShrinkToFit(MyString2* str)
{
	SetCapacity(str, str->length);
}

// ������� ������, ������� ������� �������� � �������� �������.
MyString2* Reversed(const MyString2* str)
{
	MyString2* result = (MyString2*)malloc(sizeof(MyString2));
	StrInit(result, str->length);
	for (int i = 0; i < str->length; ++i) result->symbols[i] = str->symbols[str->length - i - 1];
	result->symbols[str->length] = 0;
	return result;
}

// �������� ������� �������� � ������� ������, �� �������� �����.
void Reverse(MyString2* str)
{
	char* temp = (char*)malloc(str->capacity + 1);
	for (int i = 0; i < str->length; ++i) temp[i] = str->symbols[str->length - i - 1];
	temp[str->length] = 0;
	free(str->symbols);
	str->symbols = temp;
}

// �������� ��������� �� ������.
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

// ��������� ��������� ���� �����
int Equals(const MyString2* str, const char* rhs)
{
	if (str->length != strlen(rhs)) return 0;
	return strcmp(str->symbols, rhs) == 0;
}

// ��������� ��������� ���� �����
int Equals(const MyString2* str, const MyString2* rhs)
{
	if (str->length != rhs->length) return 0;
	return strcmp(str->symbols, rhs->symbols);
}

// �������� ������, ����������� �� ����������� �������
char Index(const MyString2* str, const int index)
{
	if (index >= str->length) return NULL;
	return str->symbols[index];
}

// ������������ ���� �����
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

// ������������ ���� �����
MyString2* Add(const MyString2* str, const MyString2* rhs)
{
	return Add(str, rhs->symbols);
}
// �������� ������ � ����� ������
MyString2* Add(const MyString2* str, const char ch)
{
	MyString2* result = (MyString2*)malloc(sizeof(MyString2));
	StrInit(result, str, str->length + 1);
	result->symbols[str->length] = ch;
	result->symbols[str->length + 1] = 0;
	result->length = str->length + 1;
	return result;
}

// ������������ ���� ����� ��� �������� �����
MyString2* AddAssign(MyString2* str, const char* rhs)
{
	const int len = strlen(rhs);
	if (str->capacity < str->length + len) SetCapacity(str, str->length + len);
	for (int i = 0; i < len; ++i) str->symbols[str->length + i] = rhs[i];
	str->symbols[str->length + len] = 0;
	str->length += len;
	return str;
}

// ������������ ���� ����� ��� �������� �����
MyString2* AddAssign(MyString2* str, const MyString2* rhs)
{
	return AddAssign(str, rhs->symbols);
}

// �������� ������ � ����� ������.
MyString2* AddAssign(MyString2* str, const char ch)
{
	if (str->capacity == str->length) SetCapacity(str, str->capacity + 1);
	str->symbols[str->length] = ch;
	str->symbols[str->length + 1] = 0;
	++str->length;
	return str;
}

// ������� ����� ������ ���� ������� n ���������� �����.
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

// ��������� ������
MyString2* MultiplyAssign(MyString2* str, const int val)
{
	if (val < 0) return NULL;
	const int cnt = str->length * val;
	if (str->capacity < cnt) SetCapacity(str, cnt);
	for (int i = str->length; i < cnt; ++i) str->symbols[i] = str->symbols[i % str->length];
	str->symbols[cnt] = 0;
	str->length *= val;
}

// ���������, �������� �� ������ ��������.
int IsNumeric(const MyString2* str)
{
	for (int i = 0; i < str->length; ++i) { if (str->symbols[i] < '0' || str->symbols[i] > '9') return 0; }
	return 1;
}