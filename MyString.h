#pragma once
#include <cstdlib>

class MyString
{
	char* symbols;
	int capacity; // ������� ������ (���-�� ��������, �� ������ '\0', ������� ����� ��������� ������ ��� ��������� ���. ������)
	int length;
	
	friend void Increment(MyString&);
	friend void Decrement(MyString&);

	static const bool IsPrint(const char* str);
public:
	// ������ ������
	const MyString();

	// ������ ������ � ��������� ��������� ��������
	const explicit MyString(const int capacity);

	// ������, ���������� �� n ������������� ��������
	const MyString(const char ch, const int val);

	// ������ �� ����������� ������ ����� �
	const MyString(const char* str);

	// ������ �� ����������� ������ ����� �, ������� �������� ��������� �������
	const MyString(const char* str, const int capacity);

	// ������ �� ������ ������, ������� �������� ��������� �������
	const MyString(const MyString& str, const int capacity);

	// ����������� �����������
	const MyString(const MyString& str);

	// �������� ������������
	const MyString& operator=(const char* str);
	const MyString& operator=(const MyString& str);

	~MyString();

	const int GetLength() const;

	const int GetCapacity() const;

	// ����������, �������� �� ������ ��������.
	const bool IsNumeric() const;

	// ���������� ������� ������
	void SetCapacity(const int capacity);

	// ���������� ������� ������, ������ � �����
	void ShrinkToFit();

	const char* AsCharArray() const;

	const MyString Reversed() const;
	void Reverse();

	const MyString Slice(const int startInclusive, const int endExclusive) const;

	const bool operator==(const char* str) const;
	const bool operator==(const MyString& str) const;
	const bool operator==(const MyString&& str) const;

	char& operator[](const int index) const;

	const MyString operator+(const char*) const;
	const MyString operator+(const MyString&) const;
	const MyString operator+(const MyString&&) const;
	const MyString operator+(const char) const;

	const MyString& operator+=(const char* str);
	const MyString& operator+=(const MyString& str);
	const MyString& operator+=(const MyString&& str);
	const MyString& operator+=(const char ch);

	const MyString operator*(const int) const;

	const MyString& operator*=(const int);
};
