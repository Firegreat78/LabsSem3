#include "MyString.h"
#include <cstdlib>
#include <cstring>
#include <locale>

const bool MyString::IsPrint(const char* str)
{
	for (int i = 0; str[i] != 0; ++i) { if (!isprint(str[i])) return false; }
	return true;
}

// Пустая строка
MyString::MyString()
{
	this->symbols = (char*)malloc(1);
	this->capacity = this->length = this->symbols[0] = 0;
}

// Пустая строка с указанной начальной ёмкостью
MyString::MyString(const int capacity)
{
	this->capacity = capacity; 
	this->symbols = (char*)malloc(capacity + 1);
	this->symbols[0] = this->length = 0;
}

// Строка, полученная из n повторяющихся символов
MyString::MyString(const char ch, const int val)
{
	if (!isprint(ch)) throw std::invalid_argument("A string can't contain non-printable characters");
	this->capacity = this->length = val;
	this->symbols = (char*)malloc(val + 1);
	for (int i = 0; i < val; ++i) this->symbols[i] = ch;
	this->symbols[val] = 0;
}

// Строка из стандартной строки языка С
MyString::MyString(const char* arr)
{
	this->capacity = this->length = strlen(arr);
	this->symbols = (char*)malloc(this->capacity + 1);
	for (int i = 0; i < capacity; ++i) this->symbols[i] = arr[i];
	this->symbols[capacity] = 0;
}

// Строка из стандартной строки языка С, имеющая заданную начальную ёмкость
MyString::MyString(const char* arr, const int capacity)
{
	this->capacity = capacity;
	symbols = (char*)malloc(capacity + 1);
	const int arrlen = strlen(arr);
	length = arrlen;
	const int len = arrlen < capacity ? arrlen : capacity;
	for (int i = 0; i < len; ++i) symbols[i] = arr[i];
	symbols[len] = 0;
}

// Конструктор копирования
MyString::MyString(const MyString& str)
{
	const int len = str.length;
	this->capacity = this->length = str.length;
	this->symbols = (char*)malloc(capacity + 1);
	for (int i = 0; i < len; ++i) this->symbols[i] = str.symbols[i];
	this->symbols[this->capacity] = 0;
}

// Оператор присваивания
const MyString& MyString::operator=(const char* str)
{
	const int len = strlen(str);
	length = len;
	this->SetCapacity(len);
	for (int i = 0; i < len; ++i) this->symbols[i] = str[i];
	this->symbols[len] = 0;
	return *this;
}

const MyString& MyString::operator=(const MyString& str)
{
	return *this = str.symbols;
}

MyString::~MyString()
{
	free(this->symbols);
}

const int MyString::GetLength() const
{
	return this->length;
}

const int MyString::GetCapacity() const
{
	return this->capacity;
}

const bool MyString::IsNumeric() const
{
	if (this->length == 0) return false;
	for (int i = 0, len = this->GetLength(); i < len; ++i)
	{
		if (!isdigit(this->symbols[i])) return false;
	}
	return true;
}

// Установить ёмкость строки
void MyString::SetCapacity(const int capacity)
{
	if (capacity < 0) throw std::invalid_argument("A string's capacity cannot be a negative number");
	this->capacity = capacity;
	this->symbols = (char*)realloc(this->symbols, capacity + 1);
	if (capacity < this->length)
	{
		this->symbols[capacity] = 0;
		this->length = capacity;
	}
}

// Установить ёмкость строки, равную её длине
void MyString::ShrinkToFit()
{
	this->SetCapacity(this->length);
}

const char* MyString::AsCharArray() const
{
	return this->symbols;
}

const MyString MyString::Reversed() const
{
	char* temp = (char*)malloc(this->length + 1);
	for (int i = 0; i < this->length; ++i) temp[i] = this->symbols[this->length - i - 1];
	temp[this->length] = 0;
	return temp;
}

void MyString::Reverse()
{
	char* temp = (char*)malloc(capacity + 1);
	for (int i = 0; i < this->length; ++i) temp[i] = this->symbols[this->length - i - 1];
	temp[this->length] = 0;
	free(this->symbols);
	this->symbols = temp;
}

const MyString MyString::Slice(const int startInclusive, const int endExclusive) const
{
	if (startInclusive < 0 || endExclusive > this->length || endExclusive < startInclusive) throw std::invalid_argument("");
	const int len = endExclusive - startInclusive;
	MyString str(len);
	for (int i = 0; i < len; ++i) str.symbols[i] = this->symbols[i + startInclusive];
	str.symbols[len] = 0;
	return str;
}

const bool MyString::operator==(const char* str) const
{
	for (int i = 0; i <= this->length; ++i) { if (this->symbols[i] != str[i]) return false; }
	return true;
}

const bool MyString::operator==(const MyString& str) const
{
	if (this->length != str.length) return false;
	return strcmp(this->symbols, str.symbols) == 0;
}

const char MyString::operator[](const int index) const
{
	if (index >= this->length) throw std::invalid_argument("String index out of bounds");
	return this->symbols[index];
}

const MyString MyString::operator+(const char* str) const
{
	if (!IsPrint(str)) throw std::invalid_argument("A string can't contain non-printable characters");
	const int len2 = strlen(str);
	MyString sum(this->length + len2);
	for (int i = 0; i < this->length; i++) sum.symbols[i] = this->symbols[i];
	for (int i = 0; i < len2; i++) sum.symbols[this->length + i] = str[i];
	sum.symbols[this->length + len2] = 0;
	return sum;
}

const MyString MyString::operator+(MyString& str) const
{
	MyString sum(this->length + str.length);
	for (int i = 0; i < this->length; i++) sum.symbols[i] = this->symbols[i];
	for (int i = 0; i < str.length; i++) sum.symbols[this->length + i] = str.symbols[i];
	sum.symbols[this->length + str.length] = 0;
	return sum;
}

const MyString MyString::operator+(MyString&& str) const
{
	return *this + str;
}

const MyString MyString::operator+(const char ch) const
{
	if (!isprint(ch)) throw std::invalid_argument("A string can't contain non-printable characters");
	MyString result(*this, this->length + 1);
	result.symbols[this->length] = ch;
	result.symbols[this->length + 1] = 0;
	return result;
}

const MyString& MyString::operator+=(const char* str)
{
	const int len = strlen(str);
	if (this->length + len > this->capacity) this->SetCapacity(this->length + len);
	for (int i = 0; i < len; ++i) this->symbols[this->length + i] = str[i];
	this->symbols[this->length + len] = 0;
	this->length += len;
	return *this;
}

const MyString& MyString::operator+=(const MyString& str)
{
	if (this->length + str.length > this->capacity) this->SetCapacity(this->length + str.length);
	for (int i = 0; i < str.length; ++i) this->symbols[this->length + i] = str.symbols[i];
	this->symbols[this->length + str.length] = 0;
	this->length += str.length;
	return *this;
}

const MyString& MyString::operator+=(const MyString&& str)
{
	return *this += str;
}

const MyString& MyString::operator+=(const char ch)
{
	if (!isprint(ch)) throw std::invalid_argument("A string can't contain non-printable characters");
	if (this->capacity == this->length) SetCapacity(this->length + 1);
	symbols[this->length] = ch;
	symbols[this->length + 1] = 0;
	this->length++;
	return *this;
}

const MyString MyString::operator*(const int val) const
{
	if (val < 0) throw std::invalid_argument("Cannot multiply a string by a negative integer");
	MyString result(*this, this->length * val);
	for (int i = 1; i < val; ++i) result += this->symbols;
	return result;
}

const MyString& MyString::operator*=(const int val)
{
	if (val < 0) throw std::invalid_argument("Cannot multiply a string by a negative integer");
	if (this->capacity < (this->length * val)) this->SetCapacity(this->length * val);
	MyString temp(*this);
	for (int i = 1; i < val; i++) *this += temp;
	return *this;
}