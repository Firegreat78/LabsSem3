#include "MyString.h"
#include "LongNumber2.h"
#include <stdexcept>
#include <iostream>
const MyString LongNumber2::max_abs = MyString('9', 50); // 10^50 - 1

void Increment(MyString& str) // если строка immutable, следует реализовать дружественную функцию
{
	// строка не пуста
	int nines = 0;
	while (nines < str.length && str[str.length - 1 - nines] == '9') nines++;
	if (nines == str.length && str.length < LongNumber2::max_abs.length)
	{
		str = MyString("1") + MyString('0', str.length);
	}

	else if (nines < str.length)
	{
		for (int i = 0; i < nines; i++) str.symbols[str.length - 1 - i] = '0';
		str.symbols[str.length - nines - 1]++;
	}
}

void Decrement(MyString& str)
{
	// строка не пуста
	if (str.length == 1 && str.symbols[0] == '1')
	{
		str = "";
		return;
	}

	int zeros = 0;
	while (str.symbols[str.length - 1 - zeros] == '0') zeros++;
	if (zeros == str.length - 1 && str.symbols[0] == '1') str = MyString('9', str.length - 1);
	else
	{
		for (int i = 0; i < zeros; i++) str.symbols[str.length - 1 - i] = '9';
		str.symbols[str.length - 1 - zeros]--;
	}
}


const MyString LongNumber2::NumToStr(long long value)
{
	if (value == 0) return "";
	if (value > 0) value = -value;
	char* temp = (char*)malloc(25);
	int index = 0;
	MyString str;
	while (value < 0)
	{
		temp[index] = ('0' - (value % 10));
		++index;
		value /= 10;
	}
	temp[index] = 0;
	str += temp;
	free(temp);
	return str.Reversed();
}

const MyString LongNumber2::StripLeadingZeros(const MyString& str)
{
	if (str.GetLength() == 0 || str[0] != '0') return str;
	int zeros = 0;
	while (zeros < str.GetLength() - 1 && str[zeros] == 0) zeros++;
	return str.Slice(zeros, str.GetLength());
}

const int LongNumber2::CompareAbs(const LongNumber2& other) const
{
	if (this->str.GetLength() > other.str.GetLength()) return 1;
	if (this->str.GetLength() < other.str.GetLength()) return -1;
	const int cmp = strcmp(this->str.AsCharArray(), other.str.AsCharArray());
	return cmp > 0 ? 1 : cmp < 0 ? -1 : 0;
}

const int LongNumber2::Compare(const LongNumber2& other) const
{
	const int cmp = this->CompareAbs(other);
	if (cmp == 1) return this->sign;
	if (cmp == -1) return other.sign;
	return this->sign == other.sign ? 0 : this->sign;
}

const MyString LongNumber2::UnsignedAdd(const MyString& a, const MyString& b)
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

const MyString LongNumber2::UnsignedSubtract(const MyString& a, const MyString& b)
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
	result.ShrinkToFit();
	return result.Reversed();
}

const MyString LongNumber2::UnsignedMultiply(const MyString& a, const MyString& b)
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
		MyString B = StripLeadingZeros(longer.Slice(longer.GetLength() - n, longer.GetLength()));
		MyString C = index == 0 ? "0" : shorter.Slice(0, index);
		MyString D = StripLeadingZeros(shorter.Slice(index, shorter.GetLength()));
		MyString AC = UnsignedMultiply(A, C);
		MyString BD = UnsignedMultiply(B, D);
		MyString AD_PLUS_BC = UnsignedSubtract(UnsignedSubtract(UnsignedMultiply(UnsignedAdd(A, B), UnsignedAdd(C, D)), AC), BD);
		return UnsignedAdd(UnsignedAdd(AC + MyString('0', n << 1), AD_PLUS_BC + MyString('0', n)), BD);
	}
}

LongNumber2::LongNumber2()
{
	this->str = "";
	this->sign = 0;
}

LongNumber2::LongNumber2(const char* value, const int sign)
{
	MyString str = value;
	if (!str.IsNumeric()) throw std::invalid_argument("String must be a numeric string");
	MyString stripped = StripLeadingZeros(str);
	this->str = sign != 0 ? (stripped.GetLength() > max_abs.GetLength() ? max_abs : stripped) : "";
	this->sign = this->str.GetLength() == 0 ? 0 : sign > 0 ? 1 : -1;
}

LongNumber2::LongNumber2(const MyString& str, const int sign)
{
	if (!str.IsNumeric()) throw std::invalid_argument("String must be a numeric string");
	MyString stripped = StripLeadingZeros(str);
	this->str = sign != 0 ? (stripped.GetLength() > max_abs.GetLength() ? max_abs : stripped) : "";
	this->sign = this->str.GetLength() == 0 ? 0 : sign > 0 ? 1 : -1;
}

LongNumber2::LongNumber2(const LongNumber2& value)
{
	this->sign = value.sign;
	this->str = value.str;
}

LongNumber2::LongNumber2(const long long num)
{
	this->str = NumToStr(num);
	this->sign = (num > 0 ? 1 : (num < 0 ? -1 : 0));
}

const MyString LongNumber2::ToString() const
{
	if (this->sign == 0) return "0";
	return this->sign == 1 ? this->str : MyString('-', 1) + this->str;
}

void LongNumber2::Print() const
{
	std::cout << this->ToString().AsCharArray() << '\n';
}

const LongNumber2 LongNumber2::Abs() const
{
	return LongNumber2(this->str, 1);
}

const LongNumber2& LongNumber2::operator=(const long long num)
{
	this->str = LongNumber2::NumToStr(num);
	this->sign = (num > 0 ? 1 : (num < 0 ? -1 : 0));
	return *this;
}

const LongNumber2& LongNumber2::operator=(const LongNumber2& num)
{
	this->str = num.str;
	this->sign = num.sign;
	return *this;
}
const LongNumber2& LongNumber2::operator=(const LongNumber2&& num)
{
	return this->operator=(num);
}

const bool LongNumber2::operator==(const LongNumber2& other) const
{
	return this->sign == other.sign && this->CompareAbs(other) == 0;
}

const bool LongNumber2::operator==(const LongNumber2&& other) const
{
	return this->operator==(other);
}

const bool LongNumber2::operator==(const long long other) const
{
	return this->operator==(LongNumber2(other));
}

const bool LongNumber2::operator!=(const LongNumber2& other) const
{
	return this->sign != other.sign || this->CompareAbs(other) == 0;
}

const bool LongNumber2::operator!=(const LongNumber2&& other) const
{
	return this->operator!=(other);
}

const bool LongNumber2::operator!=(const long long other) const
{
	return this->operator!=(LongNumber2(other));
}

const bool LongNumber2::operator>(const LongNumber2& other) const
{
	return this->Compare(other) > 0;
}

const bool LongNumber2::operator>(const LongNumber2&& other) const
{
	return this->operator>(other);
}

const bool LongNumber2::operator>(const long long other) const
{
	return this->Compare(LongNumber2(other)) > 0;
}

const bool LongNumber2::operator>=(const LongNumber2& other) const
{
	return this->Compare(other) >= 0;
}

const bool LongNumber2::operator>=(const LongNumber2&& other) const
{
	return this->operator>=(other);
}

const bool LongNumber2::operator>=(const long long other) const
{
	return this->Compare(LongNumber2(other)) >= 0;
}

const bool LongNumber2::operator<(const LongNumber2& other) const
{
	return this->Compare(other) < 0;
}

const bool LongNumber2::operator<(const LongNumber2&& other) const
{
	return this->operator<(other);
}

const bool LongNumber2::operator<(const long long other) const
{
	return this->Compare(LongNumber2(other)) < 0;
}

const bool LongNumber2::operator<=(const LongNumber2& other) const
{
	return this->Compare(other) <= 0;
}

const bool LongNumber2::operator<=(const LongNumber2&& other) const
{
	return this->operator<=(other);
}

const bool LongNumber2::operator<=(const long long other) const
{
	return this->Compare(LongNumber2(other)) <= 0;
}

const LongNumber2 LongNumber2::operator+() const
{
	return *this;
}

const LongNumber2 LongNumber2::operator-() const
{
	return LongNumber2(this->str, -this->sign);
}

const LongNumber2 LongNumber2::operator+(const LongNumber2& other) const
{
	if (this->sign == 0) return other;
	if (other.sign == 0) return *this;
	if (other.sign == this->sign) return LongNumber2(UnsignedAdd(this->str, other.str), this->sign);
	const LongNumber2* bigger = this->CompareAbs(other) >= 0 ? this : &other;
	const LongNumber2* smaller = *bigger == other ? this : &other;
	return LongNumber2(UnsignedSubtract(bigger->str, smaller->str), bigger->sign);
}

const LongNumber2 LongNumber2::operator+(const LongNumber2&& other) const
{
	return this->operator+(other);
}

const LongNumber2 LongNumber2::operator+(const long long other) const
{
	return this->operator+(LongNumber2(other));
}

const LongNumber2& LongNumber2::operator+=(const LongNumber2& other)
{
	*this = this->operator+(other);
	return *this;
}

const LongNumber2& LongNumber2::operator+=(const LongNumber2&& other)
{
	return this->operator+=(other);
}

const LongNumber2& LongNumber2::operator+=(const long long other)
{
	return this->operator+=(LongNumber2(other));
}

const LongNumber2 LongNumber2::operator-(const LongNumber2& other) const
{
	if (this->sign == 0) return -other;
	if (other.sign == 0) return *this;
	if (this->sign == other.sign)
	{
		const LongNumber2* bigger = this->CompareAbs(other) >= 0 ? this : &other;
		const LongNumber2* smaller = *bigger == other ? this : &other;
		return LongNumber2(UnsignedSubtract(bigger->str, smaller->str), bigger->sign);
	}
	return LongNumber2(UnsignedAdd(this->str, other.str), this->sign);
}

const LongNumber2 LongNumber2::operator-(const LongNumber2&& other) const
{
	return this->operator-(other);
}

const LongNumber2 LongNumber2::operator-(const long long other) const
{
	return this->operator-(LongNumber2(other));
}

const LongNumber2& LongNumber2::operator-=(const LongNumber2& other)
{
	*this = this->operator-(other);
	return *this;
}

const LongNumber2& LongNumber2::operator-=(const LongNumber2&& other)
{
	return this->operator-=(other);
}

const LongNumber2& LongNumber2::operator-=(const long long other)
{
	return this->operator-=(LongNumber2(other));
}

const LongNumber2 LongNumber2::operator*(const LongNumber2& other) const
{
	if (this->sign == 0 || other.sign == 0) return 0;
	return LongNumber2(UnsignedMultiply(this->str, other.str), this->sign * other.sign);
}

const LongNumber2 LongNumber2::operator*(const LongNumber2&& other) const
{
	return this->operator*(other);
}

const LongNumber2 LongNumber2::operator*(const long long other) const
{
	return this->operator*(LongNumber2(other));
}

const LongNumber2& LongNumber2::operator*=(const LongNumber2& other)
{
	*this = this->operator*(other);
	return *this;
}

const LongNumber2& LongNumber2::operator*=(const LongNumber2&& other)
{
	return this->operator*=(other);
}

const LongNumber2& LongNumber2::operator*=(const long long other)
{
	return this->operator*=(LongNumber2(other));
}

const LongNumber2& LongNumber2::operator++()
{
	if (this->sign == 0) *this = 1;
	else if (this->sign == 1) Increment(this->str);
	else
	{
		Decrement(this->str);
		if (this->str.GetLength() == 0) this->sign = 0;
	}
	return *this;
}

const LongNumber2 LongNumber2::operator++(int a)
{
	LongNumber2 ret(*this);
	this->operator++();
	return ret;
}

const LongNumber2& LongNumber2::operator--()
{
	if (this->sign == 0) *this = -1;
	else if (this->sign == -1) Increment(this->str);
	else
	{
		Decrement(this->str);
		if (this->str.GetLength() == 0) this->sign = 0;
	}
	return *this;
}

const LongNumber2 LongNumber2::operator--(int a)
{
	LongNumber2 ret(*this);
	this->operator--();
	return ret;
}
