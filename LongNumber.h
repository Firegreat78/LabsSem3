#pragma once
#include "MyString.h"

void Increment(MyString&);

class LongNumber
{
	int sign;
	MyString str;

	// Преобразовать модуль числа в его строковое представление
	static const MyString Num2Str(long long);

	// Отсечь незначащие нули у строки (последний нуль не отсекается)
	// "(0...0)0" -> "0"
	static const MyString StrippedLeadingZeros(const MyString&);

	// Сравнение модулей двух чисел
	// Возврат:
	// 1, если |a| > |b|;
	// 0, если |a| == |b|;
	// -1, если |a| < |b|.
	const int CompareAbs(const LongNumber&) const;

	// Сравнение двух чисел
	// Возврат:
	// 1 if a > b;
	// 0 if a == b;
	// -1 if a < b.
	const int Compare(const LongNumber&) const;

	static const MyString UnsignedAdd(const MyString&, const MyString&);
	static const MyString UnsignedSubtract(const MyString&, const MyString&);
	static const MyString UnsignedMultiply(const MyString&, const MyString&);

public:
	const LongNumber();
	const LongNumber(const char*, const int);
	const LongNumber(const MyString&, const int);
	const LongNumber(const LongNumber&);
	const LongNumber(const long long);

	const MyString ToString() const;

	const LongNumber Abs() const;

	const LongNumber Negate() const;

	const LongNumber& operator=(const long long);
	const LongNumber& operator=(const LongNumber&);

	const bool operator==(const LongNumber&) const;
	const bool operator==(const long long) const;

	const bool operator!=(const LongNumber&) const;
	const bool operator!=(const long long) const;

	const bool operator>(const LongNumber&) const;
	const bool operator>(const long long) const;

	const bool operator>=(const LongNumber&) const;
	const bool operator>=(const long long) const;

	const bool operator<(const LongNumber&) const;
	const bool operator<(const long long) const;

	const bool operator<=(const LongNumber&) const;
	const bool operator<=(const long long) const;

	const LongNumber operator+() const;
	const LongNumber operator-() const;

	const LongNumber operator+(const LongNumber&) const;
	const LongNumber& operator+=(const LongNumber&) const;
	const LongNumber operator+(const long long) const;
	const LongNumber& operator+=(const long long) const;

	const LongNumber operator*(const LongNumber&) const;
	const LongNumber& operator*=(const LongNumber&) const;
	const LongNumber operator*(const long long) const;
	const LongNumber& operator*=(const long long) const;

	const LongNumber operator-(const LongNumber&) const;
	const LongNumber& operator-=(const LongNumber&) const;
	const LongNumber operator-(const long long) const;
	const LongNumber& operator-=(const long long) const;

	const LongNumber& operator++() const;
	const LongNumber& operator--() const;

	const LongNumber& operator++(int) const;
	const LongNumber& operator--(int) const;
};

