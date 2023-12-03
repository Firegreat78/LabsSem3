#include <iostream>
#include <vector>
#include "LongNumber2.h"
#include "LongNumber.h"
#include "MyString.h"

using std::string;
using std::cout;
using std::vector;

int main()
{
	// Передача возвращаемого значения по ссылке:
	// и через указатель:
	MyString mystr = "12345"; // "12345"
	cout << mystr.AsCharArray() << '\n'; // вернули указатель на начало области памяти
	mystr[0] = '6'; // "62345" - изменили символ на нулевой позиции
	cout << mystr.AsCharArray() << '\n'; // "62345"

	// Дружественная функция: (используется для инкремента и декремента)
	LongNumber2 num2_2 = -100;
	num2_2++; // -99
	num2_2--; // -100


	// this:
	cout << "\nOperator this and vector:\n";
	vector<LongNumber*> vec;
	LongNumber value_to_add = 54353422;
	LongNumber value_to_add2 = LongNumber(INT64_MAX) + 4323;
	value_to_add.AddToVector(vec); // элемент добавлен в коллекцию
	value_to_add2.AddToVector(vec); // элемент 2 добавлен в коллекцию
	for (auto num : vec) num->Print();

	

	// Оператор +
	cout << "\nOperator '+' test\n";
	LongNumber num = LongNumber(INT64_MIN) * 12; // -110680464442257309696
	LongNumber num2 = +num; // -110680464442257309696 (то же значение)
	cout << "num = " << num.ToString() << '\n';
	cout << "num2 = " << num2.ToString() << '\n';


	// Инкремент
	cout << "\nIncrement test:\n";
	LongNumber a = 123;
	cout << "Before increment: a = " << a.ToString() << '\n';
	auto b = a++; // b = 123, a = 124
	cout << "b = a++, a = " << a.ToString() << ", b = " << b.ToString() << '\n';
	auto c = ++a; // c = 125, a = 125
	cout << "c = ++a, a = " << a.ToString() << ", c = " << c.ToString() << '\n';

	for (LongNumber i = -10; i <= 10; ++i) i.Print();


	// std::string
	cout << "\nstd::string test\n";
	string str = "12345"; cout << str << '\n'; // "12345"
	str[str.length() - 1]++; // возвращает символ по ссылке
	cout << str << '\n'; // "12346"
	cout << str.substr(2) << '\n'; // "346"
	str.push_back('9'); // добавить символ в конец строки
	cout << str << '\n'; // "123469"

}
