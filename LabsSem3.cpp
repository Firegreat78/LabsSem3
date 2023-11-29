#include <iostream>
// C++
#include "MyString.h"
#include "LongNumber.h"
// C
#include "MyString2.h"
#include "LongNumber2.h"

int main()
{
    // C++
    LongNumber a1 = INT32_MAX;
    LongNumber b1 = INT32_MIN;
    a1 += 44;
    b1 -= 1214;
    a1 *= 4;
    b1 *= 5;
    auto sum1 = a1 + b1;
    auto difference1 = a1 - b1;
    auto product1 = a1 * b1;

    // C
    LongNumber2 a2, b2, sum2, difference2, product2;
    LongNumberInit(&a2, INT32_MAX);
    LongNumberInit(&b2, INT32_MIN);
    sum2 = *Add(&a2, &b2);
    difference2 = *Difference(&a2, &b2);
    product2 = *Product(&a2, &b2);
}
