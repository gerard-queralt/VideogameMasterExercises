#include <iostream>

#include "String.h"

int main()
{
    String s("aaa");
    String s1(String("bbb"));
    String s2(std::move(s));
}