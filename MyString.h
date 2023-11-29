#pragma once
#include <cstdlib>

class MyString
{
	char* symbols = nullptr;
	int capacity; // ёмкость строки (кол-во символов, не считая '\0', которое может содержать строка без выделения доп. памяти)
	int length;

	static const bool IsPrint(const char* str)
	{
		for (int i = 0; str[i] != 0; ++i) { if (!isprint(str[i])) return false; }
		return true;
	}
public:
	// Пустая строка
	const MyString()
	{
		this->symbols = (char*)malloc(1);
		this->capacity = this->length = this->symbols[0] = 0;
	}

	// Пустая строка с указанной начальной ёмкостью
	const explicit MyString(const int capacity)
	{
		this->capacity = capacity;
		this->symbols = (char*)malloc(capacity + 1);
		this->symbols[0] = this->length = 0;
	}

	// Строка, полученная из n повторяющихся символов
	const MyString(const char ch, const int val)
	{
		if (!isprint(ch)) throw std::invalid_argument("A string can't contain non-printable characters");
		this->capacity = this->length = val;
		this->symbols = (char*)malloc(val + 1);
		for (int i = 0; i < val; ++i) this->symbols[i] = ch;
		this->symbols[val] = 0;
	}

	// Строка из стандартной строки языка С
	const MyString(const char* arr)
	{
		this->capacity = this->length = strlen(arr);
		this->symbols = (char*)malloc(this->capacity + 1);
		for (int i = 0; i < capacity; ++i) this->symbols[i] = arr[i];
		this->symbols[capacity] = 0;
	}

	// Строка из стандартной строки языка С, имеющая заданную начальную ёмкость
	const MyString(const char* arr, const int capacity)
	{
		this->capacity = capacity;
		symbols = (char*)malloc(capacity + 1);
		const int arrlen = strlen(arr);
		length = arrlen;
		const int len = arrlen < capacity ? arrlen : capacity;
		for (int i = 0; i < len; ++i) symbols[i] = arr[i];
		symbols[len] = 0;
	}

	// Строка из другой строки, имеющая заданную начальную ёмкость
	const MyString(const MyString& str, const int capacity)
	{
		this->capacity = capacity;
		symbols = (char*)malloc(capacity + 1);
		this->length = str.length;
		const int len = str.length < capacity ? str.length : capacity;
		for (int i = 0; i < len; ++i) symbols[i] = str.symbols[i];
		symbols[len] = 0;
	}

	// Конструктор копирования
	const MyString(const MyString& str)
	{
		const int len = str.length;
		this->capacity = this->length = str.length;
		this->symbols = (char*)malloc(capacity + 1);
		for (int i = 0; i < len; ++i) this->symbols[i] = str.symbols[i];
		this->symbols[this->capacity] = 0;
	}

	// Оператор присваивания
	const MyString& operator=(const char* rhs)
	{
		const int len = strlen(rhs);
		length = len;
		this->SetCapacity(len);
		for (int i = 0; i < len; ++i) this->symbols[i] = rhs[i];
		this->symbols[len] = 0;
		return *this;
	}

	const MyString& operator=(const MyString& rhs)
	{
		return *this = rhs.symbols;
	}

	~MyString()
	{
		free(symbols);
	}

	const int GetLength() const
	{
		return length;
	}

	const int GetCapacity() const
	{
		return capacity;
	}

	// Определяет, является ли строка числовой.
	const bool IsNumeric() const
	{
		if (this->length == 0) return false;
		for (int i = 0, len = this->GetLength(); i < len; ++i)
		{
			if (!isdigit(this->symbols[i])) return false;
		}
		return true;
	}

	// Установить ёмкость строки
	void SetCapacity(const int capacity)
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
	void ShrinkToFit()
	{
		SetCapacity(GetLength());
	}

	const char* ToCharArray() const
	{
		return this->symbols;
	}

	const MyString Reversed() const
	{
		char* temp = (char*)malloc(this->length + 1);
		for (int i = 0; i < this->length; ++i) temp[i] = this->symbols[this->length - i - 1];
		temp[this->length] = 0;
		return MyString(temp);
	}

	void Reverse()
	{
		char* temp = (char*)malloc(capacity + 1);
		for (int i = 0; i < this->length; ++i) temp[i] = this->symbols[this->length - i - 1];
		temp[this->length] = 0;
		free(this->symbols);
		this->symbols = temp;
	}


	const MyString Slice(const int startInclusive, const int endExclusive) const
	{
		if (startInclusive < 0 || endExclusive > this->length || endExclusive < startInclusive) throw std::invalid_argument("");
		const int len = endExclusive - startInclusive;
		char* buff = (char*)malloc(len + 1);
		for (int i = 0; i < len; ++i) buff[i] = this->symbols[i + startInclusive];
		buff[len] = 0;
		return MyString(buff);
	}

	const bool operator==(const char* rhs) const
	{
		for (int i = 0; i <= this->length; ++i) { if (this->symbols[i] != rhs[i]) return false; }
		return true;
	}

	const bool operator==(const MyString& rhs) const
	{
		if (this->length != rhs.length) return false;
		return strcmp(this->symbols, rhs.symbols);
	}

	const char operator[](const int index) const
	{
		if (index >= this->length) throw std::invalid_argument("String index out of bounds");
		return this->symbols[index];
	}

	const MyString operator+(const char* rhs) const
	{
		if (!IsPrint(rhs)) throw std::invalid_argument("A string can't contain non-printable characters");
		const int len2 = strlen(rhs);
		char* arr = (char*)malloc(this->length + len2 + 1);
		for (int i = 0; i < this->length; ++i) arr[i] = this->symbols[i];
		for (int i = 0; i < len2; ++i) arr[this->length + i] = rhs[i];
		arr[this->length + len2] = 0;
		return MyString(arr);
	}

	const MyString operator+(MyString& rhs) const
	{
		return *this + rhs.symbols;
	}

	const MyString operator+(MyString&& rhs) const
	{
		return *this + rhs.symbols;
	}

	const MyString operator+(const char ch) const
	{
		if (!isprint(ch)) throw std::invalid_argument("A string can't contain non-printable characters");
		MyString result(*this, this->length + 1);
		result.symbols[this->length] = ch;
		result.symbols[this->length + 1] = 0;
		return result;
	}

	const MyString& operator+=(const char* rhs)
	{
		const int len = strlen(rhs);
		if (this->length + len > this->capacity) this->SetCapacity(this->length + len);
		for (int i = 0; i < len; ++i) this->symbols[this->length + i] = rhs[i];
		this->symbols[this->length + len] = 0;
		this->length += len;
		return *this;
	}

	const MyString& operator+=(const MyString& rhs)
	{
		*this += rhs.symbols;
		return *this;
	}

	const MyString& operator+=(const char ch)
	{
		if (!isprint(ch)) throw std::invalid_argument("A string can't contain non-printable characters");
		if (this->capacity == this->length) SetCapacity(this->length + 1);
		symbols[this->length] = ch;
		symbols[this->length + 1] = 0;
		++this->length;
		return *this;
	}

	const MyString operator*(const int val) const
	{
		if (val < 0) throw std::invalid_argument("Cannot multiply a string by a negative integer");
		MyString result(*this, this->length * val);
		for (int i = 1; i < val; ++i) result += this->symbols;
		return result;
	}

	const MyString& operator*=(const int val)
	{
		if (val < 0) throw std::invalid_argument("Cannot multiply a string by a negative integer");
		if (this->capacity < (this->length * val)) this->SetCapacity(this->length * val);
		MyString temp(*this); temp += temp;
		for (int i = 1; i < val; ++i) *this += temp;
	}
};