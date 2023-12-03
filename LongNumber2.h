#pragma once
#include "MyString.h"

// ������� ����� (MyString)
class LongNumber2
{
	int sign;
	MyString str;

	// ������������� ������ ����� � ��� ��������� �������������
	static const MyString NumToStr(long long);

	// ������ ���������� ���� � ������ (��������� ���� �� ����������)
	// "(0...0)0" -> "0"
	static const MyString StripLeadingZeros(const MyString&);

	// ��������� ������� ���� �����
	// �������:
	// 1, ���� |a| > |b|;
	// 0, ���� |a| == |b|;
	// -1, ���� |a| < |b|.
	const int CompareAbs(const LongNumber2&) const;

	// ��������� ���� �����
	// �������:
	// 1 if a > b;
	// 0 if a == b;
	// -1 if a < b.
	const int Compare(const LongNumber2&) const;

	static const MyString UnsignedAdd(const MyString&, const MyString&);
	static const MyString UnsignedSubtract(const MyString&, const MyString&);
	static const MyString UnsignedMultiply(const MyString&, const MyString&);

public:
	static const MyString max_abs; // ����������� ��������� ������ �����
	const LongNumber2();
	const LongNumber2(const char*, const int);
	const LongNumber2(const MyString&, const int);
	const LongNumber2(const LongNumber2&);
	const LongNumber2(const long long);

	const MyString ToString() const;
	void Print() const;

	const LongNumber2 Abs() const;

	const LongNumber2 Negate() const;

	const LongNumber2& operator=(const long long);
	const LongNumber2& operator=(const LongNumber2&);
	const LongNumber2& operator=(const LongNumber2&&);

	const bool operator==(const LongNumber2&) const;
	const bool operator==(const LongNumber2&&) const;
	const bool operator==(const long long) const;

	const bool operator!=(const LongNumber2&) const;
	const bool operator!=(const LongNumber2&&) const;
	const bool operator!=(const long long) const;

	const bool operator>(const LongNumber2&) const;
	const bool operator>(const LongNumber2&&) const;
	const bool operator>(const long long) const;

	const bool operator>=(const LongNumber2&) const;
	const bool operator>=(const LongNumber2&&) const;
	const bool operator>=(const long long) const;

	const bool operator<(const LongNumber2&) const;
	const bool operator<(const LongNumber2&&) const;
	const bool operator<(const long long) const;

	const bool operator<=(const LongNumber2&) const;
	const bool operator<=(const LongNumber2&&) const;
	const bool operator<=(const long long) const;

	const LongNumber2 operator+() const;
	const LongNumber2 operator-() const;

	const LongNumber2 operator+(const LongNumber2&) const;
	const LongNumber2& operator+=(const LongNumber2&);
	const LongNumber2 operator+(const LongNumber2&&) const;
	const LongNumber2& operator+=(const LongNumber2&&);
	const LongNumber2 operator+(const long long) const;
	const LongNumber2& operator+=(const long long);

	const LongNumber2 operator*(const LongNumber2&) const;
	const LongNumber2& operator*=(const LongNumber2&);
	const LongNumber2 operator*(const LongNumber2&&) const;
	const LongNumber2& operator*=(const LongNumber2&&);
	const LongNumber2 operator*(const long long) const;
	const LongNumber2& operator*=(const long long);

	const LongNumber2 operator-(const LongNumber2&) const;
	const LongNumber2& operator-=(const LongNumber2&);
	const LongNumber2 operator-(const LongNumber2&&) const;
	const LongNumber2& operator-=(const LongNumber2&&);
	const LongNumber2 operator-(const long long) const;
	const LongNumber2& operator-=(const long long);

	const LongNumber2& operator++();
	const LongNumber2& operator--();

	const LongNumber2 operator++(int);
	const LongNumber2 operator--(int);

};

