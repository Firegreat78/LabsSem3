#pragma once
#include <cstdlib>

class MyString
{
	char* symbols;
	int capacity; // ёмкость строки (кол-во символов, не считая '\0', которое может содержать строка без выделения доп. памяти)
	int length;
	
	friend void Increment(MyString&);

	static const bool IsPrint(const char* str);
public:
	// Пустая строка
	const MyString();

	// Пустая строка с указанной начальной ёмкостью
	const explicit MyString(const int capacity);

	// Строка, полученная из n повторяющихся символов
	const MyString(const char ch, const int val);

	// Строка из стандартной строки языка С
	const MyString(const char* str);

	// Строка из стандартной строки языка С, имеющая заданную начальную ёмкость
	const MyString(const char* str, const int capacity);

	// Строка из другой строки, имеющая заданную начальную ёмкость
	const MyString(const MyString& str, const int capacity);

	// Конструктор копирования
	const MyString(const MyString& str);

	// Оператор присваивания
	const MyString& operator=(const char* str);
	const MyString& operator=(const MyString& str);

	~MyString();

	const int GetLength() const;

	const int GetCapacity() const;

	// Определяет, является ли строка числовой.
	const bool IsNumeric() const;

	// Установить ёмкость строки
	void SetCapacity(const int capacity);

	// Установить ёмкость строки, равную её длине
	void ShrinkToFit();

	const char* AsCharArray() const;

	const MyString Reversed() const;
	void Reverse();

	const MyString Slice(const int startInclusive, const int endExclusive) const;

	const bool operator==(const char* str) const;
	const bool operator==(const MyString& str) const;

	const char operator[](const int index) const;

	const MyString operator+(const char* str) const;
	const MyString operator+(MyString& str) const;
	const MyString operator+(MyString&& str) const;
	const MyString operator+(const char ch) const;

	const MyString& operator+=(const char* str);
	const MyString& operator+=(const MyString& str);
	const MyString& operator+=(const MyString&& str);
	const MyString& operator+=(const char ch);

	const MyString operator*(const int val) const;

	const MyString& operator*=(const int val);
};
