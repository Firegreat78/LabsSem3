#include "LongNumber.h"
#include <stdexcept>
#include <utility>
#include <iostream>

using std::string;
using std::vector;
using std::length_error;
using std::logic_error;
using std::max;
using std::min;
using std::swap;

// примечание: строка max_abs может содержать только девятки
// иначе алгоритм не будет правильно работать
const string LongNumber::max_abs = string(50, '9'); // 10^50 - 1

inline void reverse(char* str, const int len)
{
	const auto half = len >> 1;
	for (int i = 0; i < half; ++i) swap(str[i], str[len - i - 1]);
}

inline void reverse(string& str)
{
	const auto half = str.length() >> 1;
	for (int i = 0; i < half; ++i) swap(str[i], str[str.length() - i - 1]);
}

inline const bool is_numeric(const char* str)
{
	for (int i = 0; str[i] != 0; ++i)
	{
		//if ((unsigned char)str[i] + 198ui8 < 246ui8) return false;
		if (str[i] < '0' || str[i] > '9') return false;
	}
	return true;
}

inline const bool is_numeric(const string& str)
{
	for (char symbol : str) 
	{
		//if ((unsigned char)symbol + 198ui8 < 246ui8) return false;
		if (symbol < '0' || symbol > '9') return false;
	}
	return true;
}

inline const string reversed(const string& str)
{
	string result;
	result.reserve(str.length());
	for (int i = str.length() - 1; i >= 0; i--) result.push_back(str[i]);
	return result;
}

const string LongNumber::NumToStr(long long value)
{
	if (value == 0) return "";
	if (value > 0) value = -value;
	string str;
	while (value < 0)
	{
		str.push_back('0' - (value % 10));
		value /= 10;
	}
	reverse(str);
	return str;
}

const string LongNumber::StripLeadingZeros(const string& str)
{
	if (str.empty() || str[0] != '0') return str;
	int zeros = 0;
	while (zeros < str.length() - 1 && str[zeros] == '0') zeros++;
	return str.substr(zeros);
}

const int LongNumber::CompareAbs(const LongNumber& other) const
{
	if (this->str.length() > other.str.length()) return 1;
	if (this->str.length() < other.str.length()) return -1;
	const int cmp = this->str.compare(other.str);
	return cmp > 0 ? 1 : cmp < 0 ? -1 : 0;
}

const int LongNumber::Compare(const LongNumber& other) const
{
	return this->sign == other.sign ? (this->CompareAbs(other) * this->sign) : (this->sign > other.sign ? 1 : -1);
}

const string LongNumber::UnsignedAdd(const string& a, const string& b)
{
	string result;
	result.reserve(max(a.length(), b.length() + 1));
	int indexA = a.length() - 1;
	int indexB = b.length() - 1;
	int carry = 0;
	while (true)
	{
		const int digit1 = indexA < 0 ? 0 : (a[indexA] - '0');
		const int digit2 = indexB < 0 ? 0 : (b[indexB] - '0');
		const int res = digit1 + digit2 + carry;
		if (res == 0 && max(indexA, indexB) < 0) break;
		carry = res / 10;
		result.push_back('0' + (res % 10));
		--indexA;
		--indexB;
	}
	if (result.length() > max_abs.length()) throw length_error("Result number is too big");
	return reversed(result);
}

const string LongNumber::UnsignedSubtract(const string& a, const string& b)
{
	string result;
	result.reserve(max(a.length(), b.length()));
	int indexA = a.length() - 1;
	int indexB = b.length() - 1;
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
			if (max(indexA, indexB) < 0 && res != -10) break;
			++zeros;
		}
		else
		{
			result += (string(zeros, '0') + (char)(toAppend + '0'));
			zeros = 0;
		}
		--indexA;
		--indexB;
	}
	return reversed(result);
}

const string LongNumber::UnsignedMultiply(const string& a, const string& b)
{
	const string& longer = a.length() > b.length() ? a : b;
	const string& shorter = a.length() <= b.length() ? a : b;
	string res;
	if (shorter.empty() || shorter[0] == '0') return "0";
	else if (shorter == "1") return longer;
	else if (shorter.length() == 1)
	{
		char* buff = (char*)malloc(longer.length() + 2);
		int carry = 0;
		int index = longer.length() - 1;
		const int digit = shorter[0] - '0';
		while (true)
		{
			const int digit2 = index < 0 ? 0 : (longer[index] - '0');
			const int res = digit * digit2 + carry;
			if (res == 0 && index < 0) break;
			carry = res / 10;
			buff[longer.length() - index - 1] = ((res % 10) + '0');
			--index;
		}
		buff[longer.length() - index - 1] = 0;
		reverse(buff, longer.length() - index - 1);
		res = buff;
		free(buff);
	}
	else
	{
		// karatsuba algorithm (base 10)
		// x = a * 10^n + b
		// y = c * 10^n + d
		// n - non-negative integer
		// xy = ac*10^(2n) + [(a+b)(c+d)-ac-bd]*10^n + bd
		const auto n = longer.length() >> 1;
		const auto index = max(0ll, ((long long)shorter.length() - (long long)n));
		const string A = longer.substr(0, longer.length() - n);
		const string B = StripLeadingZeros(longer.substr(longer.length() - n));
		const string C = index == 0 ? "0" : shorter.substr(0, index);
		const string D = StripLeadingZeros(shorter.substr(index));
		const string AC = UnsignedMultiply(A, C);
		const string BD = UnsignedMultiply(B, D);
		const string AD_PLUS_BC = UnsignedSubtract(UnsignedSubtract(UnsignedMultiply(UnsignedAdd(A, B), UnsignedAdd(C, D)), AC), BD);
		res = UnsignedAdd(UnsignedAdd(AC + string(n << 1, '0'), AD_PLUS_BC + string(n, '0')), BD);
	}
	if (res.length() > max_abs.length()) throw length_error("Result number is too big");
	return res;
}

void LongNumber::AddToVector(vector<LongNumber*>& vec)
{
	vec.push_back(this);
}

LongNumber::LongNumber()
{
	this->str = "";
	this->sign = 0;
}

LongNumber::LongNumber(const char* value, const int sign)
{
	string str = value;
	if (!is_numeric(str)) throw std::invalid_argument("String must be a numeric string");
	string stripped = StripLeadingZeros(str);
	if (stripped.length() > max_abs.length()) throw length_error("Result number is too big");
	this->str = stripped == "0" ? "" : stripped;
	this->sign = this->str.empty() ? 0 : sign > 0 ? 1 : -1;
}

LongNumber::LongNumber(const string& str, const int sign)
{
	if (!is_numeric(str)) throw std::invalid_argument("String must be a numeric string");
	string stripped = StripLeadingZeros(str);
	if (stripped.length() > max_abs.length()) throw length_error("Result number is too big");
	this->str = stripped == "0" ? "" : stripped;
	this->sign = this->str.empty() ? 0 : sign > 0 ? 1 : -1;
}

LongNumber::LongNumber(const LongNumber& value)
{
	this->sign = value.sign;
	this->str = value.str;
}

LongNumber::LongNumber(const long long num)
{
	this->str = NumToStr(num);
	this->sign = num > 0 ? 1 : num < 0 ? -1 : 0;
}

const string LongNumber::ToString() const
{
	return this->sign == 0 ? "0" : this->sign == 1 ? this->str : string(1, '-') + this->str;
}

void LongNumber::Print() const
{
	std::cout << this->ToString() << '\n';
}

const LongNumber LongNumber::Abs() const
{
	return LongNumber(this->str, 1);
}

const LongNumber& LongNumber::operator=(const long long num)
{
	this->str = LongNumber::NumToStr(num);
	this->sign = num > 0 ? 1 : num < 0 ? -1 : 0;
	return *this;
}

const LongNumber& LongNumber::operator=(const LongNumber& num)
{
	this->str = num.str;
	this->sign = num.sign;
	return *this;
}
const LongNumber& LongNumber::operator=(const LongNumber&& num)
{
	return this->operator=(num);
}

const bool LongNumber::operator==(const LongNumber& other) const
{
	return this->sign == other.sign && this->CompareAbs(other) == 0;
}

const bool LongNumber::operator==(const LongNumber&& other) const
{
	return this->operator==(other);
}

const bool LongNumber::operator==(const long long other) const
{
	return this->operator==(LongNumber(other));
}

const bool LongNumber::operator!=(const LongNumber& other) const
{
	return this->sign != other.sign || this->CompareAbs(other) == 0;
}

const bool LongNumber::operator!=(const LongNumber&& other) const
{
	return this->operator!=(other);
}

const bool LongNumber::operator!=(const long long other) const
{
	return this->operator!=(LongNumber(other));
}

const bool LongNumber::operator>(const LongNumber& other) const
{
	return this->Compare(other) > 0;
}

const bool LongNumber::operator>(const LongNumber&& other) const
{
	return this->operator>(other);
}

const bool LongNumber::operator>(const long long other) const
{
	return this->Compare(LongNumber(other)) > 0;
}

const bool LongNumber::operator>=(const LongNumber& other) const
{
	return this->Compare(other) >= 0;
}

const bool LongNumber::operator>=(const LongNumber&& other) const
{
	return this->operator>=(other);
}

const bool LongNumber::operator>=(const long long other) const
{
	return this->Compare(LongNumber(other)) >= 0;
}

const bool LongNumber::operator<(const LongNumber& other) const
{
	return this->Compare(other) < 0;
}

const bool LongNumber::operator<(const LongNumber&& other) const
{
	return this->operator<(other);
}

const bool LongNumber::operator<(const long long other) const
{
	return this->Compare(LongNumber(other)) < 0;
}

const bool LongNumber::operator<=(const LongNumber& other) const
{
	return this->Compare(other) <= 0;
}

const bool LongNumber::operator<=(const LongNumber&& other) const
{
	return this->operator<=(other);
}

const bool LongNumber::operator<=(const long long other) const
{
	return this->Compare(LongNumber(other)) <= 0;
}

const LongNumber LongNumber::operator+() const
{
	return *this;
}

const LongNumber LongNumber::operator-() const
{
	return LongNumber(this->str, -this->sign);
}

const LongNumber LongNumber::operator+(const LongNumber& other) const
{
	if (this->sign == 0) return other;
	if (other.sign == 0) return *this;
	if (other.sign == this->sign) return LongNumber(UnsignedAdd(this->str, other.str), this->sign);
	const auto cmp = this->CompareAbs(other);
	const auto bigger = cmp >= 0 ? this : &other;
	const auto smaller = cmp < 0 ? this : &other;
	return LongNumber(UnsignedSubtract(bigger->str, smaller->str), bigger->sign);
}

const LongNumber LongNumber::operator+(const LongNumber&& other) const
{
	return this->operator+(other);
}

const LongNumber LongNumber::operator+(const long long other) const
{
	return this->operator+(LongNumber(other));
}

const LongNumber& LongNumber::operator+=(const LongNumber& other)
{
	*this = this->operator+(other);
	return *this;
}

const LongNumber& LongNumber::operator+=(const LongNumber&& other)
{
	return this->operator+=(other);
}

const LongNumber& LongNumber::operator+=(const long long other)
{
	return this->operator+=(LongNumber(other));
}

const LongNumber LongNumber::operator-(const LongNumber& other) const
{
	if (this->sign == 0) return -other;
	if (other.sign == 0) return *this;
	if (this->sign == other.sign)
	{
		const LongNumber* bigger = this->CompareAbs(other) >= 0 ? this : &other;
		const LongNumber* smaller = *bigger == other ? this : &other;
		return LongNumber(UnsignedSubtract(bigger->str, smaller->str), bigger->sign);
	}
	return LongNumber(UnsignedAdd(this->str, other.str), this->sign);
}

const LongNumber LongNumber::operator-(const LongNumber&& other) const
{
	return this->operator-(other);
}

const LongNumber LongNumber::operator-(const long long other) const
{
	return this->operator-(LongNumber(other));
}

const LongNumber& LongNumber::operator-=(const LongNumber& other)
{
	*this = this->operator-(other);
	return *this;
}

const LongNumber& LongNumber::operator-=(const LongNumber&& other)
{
	return this->operator-=(other);
}

const LongNumber& LongNumber::operator-=(const long long other)
{
	return this->operator-=(LongNumber(other));
}

const LongNumber LongNumber::operator*(const LongNumber& other) const
{
	if (this->sign == 0 || other.sign == 0) return 0;
	if (this->str.length() + other.str.length() - 1 > max_abs.length()) throw length_error("Result number is too big");
	return LongNumber(UnsignedMultiply(this->str, other.str), this->sign * other.sign);
}

const LongNumber LongNumber::operator*(const LongNumber&& other) const
{
	return this->operator*(other);
}

const LongNumber LongNumber::operator*(const long long other) const
{
	return this->operator*(LongNumber(other));
}

const LongNumber& LongNumber::operator*=(const LongNumber& other)
{
	*this = this->operator*(other);
	return *this;
}

const LongNumber& LongNumber::operator*=(const LongNumber&& other)
{
	return this->operator*=(other);
}

const LongNumber& LongNumber::operator*=(const long long other)
{
	return this->operator*=(LongNumber(other));
}

const LongNumber& LongNumber::operator++()
{
	if (sign == 0) 
	{ 
		sign++;
		str = "1";
	}

	else if (sign == 1)
	{
		int nines = 0;
		while (nines < str.length() && str[str.length() - 1 - nines] == '9') nines++;

		if (nines == str.length() && str.length() < max_abs.length()) throw length_error("Result number is too big");
		else if (nines < str.length())
		{
			for (int i = 0; i < nines; i++) str[str.length() - 1 - i] = '0';
			str[str.length() - nines - 1]++;
		}
	}

	else if (sign == -1)
	{
		if (str.length() == 1 && str[0] == '1')
		{
			sign++;
			str = "";
			return *this;
		}

		int zeros = 0;
		while (str[str.length() - 1 - zeros] == '0') zeros++;
		if (zeros == str.length() - 1 && str[0] == '1') str = string(str.length() - 1, '9');
		else
		{
			for (int i = 0; i < zeros; i++) str[str.length() - 1 - i] = '9';
			str[str.length() - 1 - zeros]--;
		}
	}
	return *this;
}

const LongNumber LongNumber::operator++(int a)
{
	LongNumber ret(*this);
	this->operator++();
	return ret;
}

const LongNumber& LongNumber::operator--()
{
	if (sign == 0)
	{
		sign--;
		str = "1";
	}

	else if (sign == -1)
	{
		int nines = 0;
		while (nines < str.length() && str[str.length() - 1 - nines] == '9') nines++;
		if (nines == str.length() && str.length() < max_abs.length()) throw length_error("Result number is too big");
		else if (nines < str.length())
		{
			for (int i = 0; i < nines; i++) str[str.length() - 1 - i] = '0';
			str[str.length() - nines - 1]++;
		}
	}

	else if (sign == 1)
	{
		if (str.length() == 1 && str[0] == '1')
		{
			sign--;
			str = "";
		}

		else
		{
			int zeros = 0;
			while (str[str.length() - 1 - zeros] == '0') zeros++;
			if (zeros == str.length() - 1 && str[0] == '1') str = string(str.length() - 1, '9');
			else
			{
				for (int i = 0; i < zeros; i++) str[str.length() - 1 - i] = '9';
				str[str.length() - 1 - zeros]--;
			}
		}
	}
	return *this;
}

const LongNumber LongNumber::operator--(int a)
{
	LongNumber ret(*this);
	this->operator--();
	return ret;
}
