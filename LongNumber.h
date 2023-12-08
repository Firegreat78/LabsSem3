#pragma once
#include <string>
#include <vector>
#include <xstring>

// ������� ����� (std::string)
class LongNumber
{
	int sign;
	std::string str;
	
	// ������������� ������ ����� � ��� ��������� �������������
	static const std::string NumToStr(long long);

	// ������ ���������� ���� � ������ (��������� ���� �� ����������)
	// "(0...0)0" -> "0"
	static const std::string StripLeadingZeros(const std::string&);

	// ��������� ������� ���� �����
	// �������:
	// 1, ���� |a| > |b|;
	// 0, ���� |a| == |b|;
	// -1, ���� |a| < |b|.
	const int CompareAbs(const LongNumber&) const;

	// ��������� ���� �����
	// �������:
	// 1 if a > b;
	// 0 if a == b;
	// -1 if a < b.
	const int Compare(const LongNumber&) const;

	static const std::string UnsignedAdd(const std::string&, const std::string&);
	static const std::string UnsignedSubtract(const std::string&, const std::string&);
	static const std::string UnsignedMultiply(const std::string&, const std::string&);

public:
	static const std::string max_abs; // ����������� ��������� ������ �����
	const LongNumber();
	const LongNumber(const char*, const int);
	const LongNumber(const std::string&, const int);
	const LongNumber(const LongNumber&);
	const LongNumber(const long long);

	const std::string ToString() const;
	void Print() const;
	void AddToVector(std::vector<LongNumber*>&);

	const LongNumber Abs() const;

	const LongNumber Negate() const;

	const LongNumber& operator=(const long long);
	const LongNumber& operator=(const LongNumber&);
	const LongNumber& operator=(const LongNumber&&);

	const bool operator==(const LongNumber&) const;
	const bool operator==(const LongNumber&&) const;
	const bool operator==(const long long) const;

	const bool operator!=(const LongNumber&) const;
	const bool operator!=(const LongNumber&&) const;
	const bool operator!=(const long long) const;

	const bool operator>(const LongNumber&) const;
	const bool operator>(const LongNumber&&) const;
	const bool operator>(const long long) const;

	const bool operator>=(const LongNumber&) const;
	const bool operator>=(const LongNumber&&) const;
	const bool operator>=(const long long) const;

	const bool operator<(const LongNumber&) const;
	const bool operator<(const LongNumber&&) const;
	const bool operator<(const long long) const;

	const bool operator<=(const LongNumber&) const;
	const bool operator<=(const LongNumber&&) const;
	const bool operator<=(const long long) const;

	const LongNumber operator+() const;
	const LongNumber operator-() const;

	const LongNumber operator+(const LongNumber&) const;
	const LongNumber& operator+=(const LongNumber&);
	const LongNumber operator+(const LongNumber&&) const;
	const LongNumber& operator+=(const LongNumber&&);
	const LongNumber operator+(const long long) const;
	const LongNumber& operator+=(const long long);

	const LongNumber operator*(const LongNumber&) const;
	const LongNumber& operator*=(const LongNumber&);
	const LongNumber operator*(const LongNumber&&) const;
	const LongNumber& operator*=(const LongNumber&&);
	const LongNumber operator*(const long long) const;
	const LongNumber& operator*=(const long long);

	const LongNumber operator-(const LongNumber&) const;
	const LongNumber& operator-=(const LongNumber&);
	const LongNumber operator-(const LongNumber&&) const;
	const LongNumber& operator-=(const LongNumber&&);
	const LongNumber operator-(const long long) const;
	const LongNumber& operator-=(const long long);

	const LongNumber& operator++();
	const LongNumber& operator--();

	const LongNumber operator++(int);
	const LongNumber operator--(int);
	
};