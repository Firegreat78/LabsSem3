#pragma once
#include "MyString.h"

// ƒлинное число (MyString)
class LongNumber2
{
	int sign;
	MyString str;

	// ѕреобразовать модуль числа в его строковое представление
	static const MyString NumToStr(long long);

	// ќтсечь незначащие нули у строки (последний нуль не отсекаетс€)
	// "(0...0)0" -> "0"
	static const MyString StripLeadingZeros(const MyString&);

	// —равнение модулей двух чисел
	// ¬озврат:
	// 1, если |a| > |b|;
	// 0, если |a| == |b|;
	// -1, если |a| < |b|.
	const int CompareAbs(const LongNumber2&) const;

	// —равнение двух чисел
	// ¬озврат:
	// 1 if a > b;
	// 0 if a == b;
	// -1 if a < b.
	const int Compare(const LongNumber2&) const;

	static const MyString UnsignedAdd(const MyString&, const MyString&);
	static const MyString UnsignedSubtract(const MyString&, const MyString&);
	static const MyString UnsignedMultiply(const MyString&, const MyString&);

public:
	static const MyString max_abs; // максимально возможный модуль числа
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

