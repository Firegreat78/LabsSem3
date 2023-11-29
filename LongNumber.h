#pragma once
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "MyString.h"
class LongNumber
{
	int sign; // 1 - positive, -1 - negative, 0 - zero
	MyString str;

	// Преобразовать модуль числа в его строковое представление
	static const MyString Num2Str(long long num)
	{
		if (num == 0) return MyString();
		if (num > 0) num = -num;
		char* temp = (char*)malloc(25);
		int index = 0;
		MyString str;
		while (num < 0)
		{
			temp[index] = ('0' - (num % 10));
			++index;
			num /= 10;
		}
		temp[index] = 0;
		str += temp;
		free(temp);
		return str.Reversed();
	}

	// Отсечь незначащие нули у строки (последний нуль не отсекается)
	// "(0...0)0" -> "0"
	static const MyString StrippedLeadingZeros(const MyString& str)
	{
		if (str == "") return MyString();
		int zeros = 0;
		while (zeros < (str.GetLength() - 1) && str[zeros] == '0') ++zeros;
		return str.Slice(zeros, str.GetLength());
	}

	// Сравнение модулей двух чисел
	// Возврат:
	// 1, если |a| > |b|;
	// 0, если |a| == |b|;
	// -1, если |a| < |b|.
	int CompareAbs(const LongNumber& other) const
	{
		if (this->str.GetLength() > other.str.GetLength()) return 1;
		if (this->str.GetLength() < other.str.GetLength()) return -1;
		const int cmp = strcmp(this->str.ToCharArray(), other.str.ToCharArray());
		return cmp > 0 ? 1 : cmp < 0 ? -1 : 0;
	}

	// Сравнение двух чисел
	// Возврат:
	// 1 if a > b;
	// 0 if a == b;
	// -1 if a < b.
	int Compare(const LongNumber& other) const
	{
		const int cmp = this->CompareAbs(other);
		if (cmp == 1) return this->sign;
		if (cmp == -1) return other.sign;
		return this->sign == other.sign ? 0 : this->sign;
	}

	static MyString UnsignedAdd(const MyString& a, const MyString& b)
	{
		MyString result(std::max(a.GetLength(), b.GetLength()) + 1);
		int indexA = a.GetLength() - 1;
		int indexB = b.GetLength() - 1;
		int carry = 0;
		while (true)
		{
			const int digit1 = indexA < 0 ? 0 : (a[indexA] - '0');
			const int digit2 = indexB < 0 ? 0 : (b[indexB] - '0');
			const int res = digit1 + digit2 + carry;
			if (res == 0 && std::max(indexA, indexB) < 0) break;
			carry = res / 10;
			result += ('0' + res % 10);
			--indexA;
			--indexB;
		}
		result.Reverse();
		result.ShrinkToFit();
		return result;
	}

	static MyString UnsignedSubtract(const MyString& a, const MyString& b)
	{
		MyString result(std::max(a.GetLength(), b.GetLength()));
		int indexA = a.GetLength() - 1;
		int indexB = b.GetLength() - 1;
		int carry = 0;
		int zeros = 0;
		while (true)
		{
			const int digit1 = indexA < 0 ? 0 : (a[indexA] - '0');
			const int digit2 = indexB < 0 ? 0 : (b[indexB] - '0');
			const int res = digit1 - digit2 + carry;
			const int toAppend = res < 0 ? res + 10 : res;
			carry = res < 0 ? -1 : 0;
			if (toAppend == 0)
			{
				if (std::max(indexA, indexB) < 0 && res != -10) break;
				++zeros;
			}
			else
			{
				result += (MyString('0', zeros) + MyString('0' + toAppend, 1));
				zeros = 0;
			}
			--indexA;
			--indexB;
		}
		return result.Reversed();
	}

	static MyString UnsignedMultiply(const MyString& a, const MyString& b)
	{
		const MyString& longer = a.GetLength() > b.GetLength() ? a : b;
		const MyString& shorter = a.GetLength() <= b.GetLength() ? a : b;

		if (shorter.GetLength() == 0 || shorter == "0") return "0";
		else if (shorter == "1") return MyString(longer);
		else if (shorter.GetLength() == 1)
		{
			MyString result(longer.GetLength() + 1);
			int carry = 0;
			int index = longer.GetLength() - 1;
			const int digit = shorter[0] - '0';
			while (true)
			{
				const int digit2 = index < 0 ? 0 : (longer[index] - '0');
				const int res = digit * digit2 + carry;
				if (res == 0 && index < 0) break;
				carry = res / 10;
				result += (res % 10) + '0';
				--index;
			}
			return result.Reversed();
		}
		else
		{
			// karatsuba algorithm (base 10)
			// x = a * 10^n + b
			// y = c * 10^n + d
			// n - non-negative integer
			// xy = ac*10^(2n) + [(a+b)(c+d)-ac-bd]*10^n + bd
			const int n = longer.GetLength() >> 1;
			const int index = std::max(0, shorter.GetLength() - n);
			MyString A = longer.Slice(0, longer.GetLength() - n);
			MyString B = StrippedLeadingZeros(longer.Slice(longer.GetLength() - n, longer.GetLength()));
			MyString C = index == 0 ? "0" : shorter.Slice(0, index);
			MyString D = StrippedLeadingZeros(shorter.Slice(index, shorter.GetLength()));
			MyString AC = UnsignedMultiply(A, C);
			MyString BD = UnsignedMultiply(B, D);
			MyString AD_PLUS_BC = UnsignedSubtract(UnsignedSubtract(UnsignedMultiply(UnsignedAdd(A, B), UnsignedAdd(C, D)), AC), BD);
			return UnsignedAdd(UnsignedAdd(AC + MyString('0', n << 1), AD_PLUS_BC + MyString('0', n)), BD);
		}
	}

	static MyString UnsignedMultiply(const MyString&& a, const MyString&& b)
	{
		return UnsignedMultiply(a, b);
	}

public:

	const LongNumber()
	{
		this->str = "";
		this->sign = 0;
	}

	const LongNumber(const char* value, const int sign)
	{
		MyString str = value;
		if (!str.IsNumeric()) throw std::invalid_argument("String must be a numeric string");
		this->str = sign != 0 ? StrippedLeadingZeros(value) : "";
		this->sign = (str == "" ? 0 : sign);
	}

	const LongNumber(const MyString& value, const int sign)
	{
		if (!value.IsNumeric()) throw std::invalid_argument("String must be a numeric string");
		str = sign != 0 ? StrippedLeadingZeros(value) : "";
		this->sign = (this->str == "" ? 0 : sign);
	}

	const LongNumber(const LongNumber& value)
	{
		this->sign = value.sign;
		this->str = value.str;
	}

	const LongNumber(const long long num)
	{
		this->str = LongNumber::Num2Str(num);
		this->sign = (num > 0 ? 1 : (num < 0 ? -1 : 0));
	}

	const MyString ToString() const
	{
		if (this->sign == 0) return MyString("0");
		MyString result(this->str.GetLength());
		if (this->sign == -1) result += '-';
		result += this->str;
		return result;
	}

	const LongNumber Abs() const
	{
		return LongNumber(this->str, 1);
	}

	const LongNumber& operator=(const long long num)
	{
		this->str = LongNumber::Num2Str(num);
		this->sign = (num > 0 ? 1 : (num < 0 ? -1 : 0));
		return *this;
	}

	const LongNumber& operator=(const LongNumber& num)
	{
		this->str = num.str;
		this->sign = num.sign;
		return *this;
	}

	const bool operator==(const LongNumber& other) const
	{
		return this->sign == other.sign && this->CompareAbs(other) == 0;
	}

	const bool operator==(const long long other) const
	{
		return *this == LongNumber(other);
	}

	const bool operator!=(const LongNumber& other) const
	{
		return this->sign != other.sign || this->CompareAbs(other) != 0;
	}

	const bool operator!=(const long long other) const
	{
		return *this != LongNumber(other);
	}

	const bool operator>(const LongNumber& other) const
	{
		return this->Compare(other) > 0;
	}

	const bool operator>(const long long other) const
	{
		return *this > LongNumber(other);
	}

	const bool operator>=(const LongNumber& other) const
	{
		return this->Compare(other) >= 0;
	}

	const bool operator>=(const long long other) const
	{
		return *this >= LongNumber(other);
	}

	const bool operator<(const LongNumber& other) const
	{
		return this->Compare(other) < 0;
	}

	const bool operator<(const long long other) const
	{
		return *this < LongNumber(other);
	}

	const bool operator<=(const LongNumber& other) const
	{
		return this->Compare(other) <= 0;
	}

	const bool operator<=(const long long other) const
	{
		return *this <= LongNumber(other);
	}

	const LongNumber operator+() const
	{
		return LongNumber(*this);
	}

	const LongNumber operator-() const
	{
		return LongNumber(this->str, -this->sign);
	}

	const LongNumber operator+(const LongNumber& other) const
	{
		if (this->sign == 0) return LongNumber(other);
		if (other.sign == 0) return LongNumber(*this);
		if (other.sign == this->sign) return LongNumber(UnsignedAdd(this->str, other.str), this->sign);
		const LongNumber* bigger = this->CompareAbs(other) >= 0 ? this : &other;
		const LongNumber* smaller = *bigger == other ? this : &other;
		return LongNumber(UnsignedSubtract(bigger->str, smaller->str), bigger->sign);
	}

	const LongNumber operator+(const LongNumber&& other)
	{
		return this->operator+(other);
	}

	const LongNumber operator+(const long long other) const
	{
		return *this + LongNumber(other);
	}

	const LongNumber operator-(const LongNumber& other) const
	{
		if (this->sign == 0) return -other;
		if (other.sign == 0) return LongNumber(*this);
		if (this->sign == other.sign)
		{
			const LongNumber* bigger = this->CompareAbs(other) >= 0 ? this : &other;
			const LongNumber* smaller = *bigger == other ? this : &other;
			return LongNumber(UnsignedSubtract(bigger->str, smaller->str), bigger->sign);
		}
		return LongNumber(UnsignedAdd(this->str, other.str), this->sign);
	}

	const LongNumber operator-(const long long other) const
	{
		return *this - LongNumber(other);
	}

	const LongNumber operator-(const LongNumber&& other)
	{
		return this->operator-(other);
	}

	const LongNumber& operator+=(const LongNumber& other)
	{
		*this = *this + other;
		return *this;
	}

	const LongNumber& operator+=(const LongNumber&& other)
	{
		return this->operator+=(other);
	}

	const LongNumber& operator+=(const long long other)
	{
		return *this += LongNumber(other);
	}

	const LongNumber& operator-=(const LongNumber& other)
	{
		*this = *this - other;
		return *this;
	}

	const LongNumber& operator-=(const LongNumber&& other)
	{
		return this->operator-=(other);
	}

	const LongNumber& operator-=(const long long other)
	{
		return *this -= LongNumber(other);
	}

	const LongNumber operator*(const LongNumber& other) const
	{
		if (this->sign == 0 || other.sign == 0) return 0;
		return LongNumber(UnsignedMultiply(this->str, other.str), this->sign * other.sign);
	}

	const LongNumber& operator*(const LongNumber&& other)
	{
		return this->operator*(other);
	}

	const LongNumber operator*(const long long other) const
	{
		return (*this) * LongNumber(other);
	}

	const LongNumber& operator*=(const LongNumber& other)
	{
		*this = (*this * other);
		return *this;
	}

	const LongNumber& operator*=(const LongNumber&& other)
	{
		return this->operator*=(other);
	}

	const LongNumber& operator*=(const long long other)
	{
		return *this *= LongNumber(other);
	}
};