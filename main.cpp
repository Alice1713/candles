#include <iostream>
#include "candle.h"
#include <stdio.h>

using namespace std;

int main()
{
    Wax test(ColorEnum::Yellow);
    int t=test.Burn(20);
    test.Burn(100);
    Paraffin test2 (SmellEnum::Apple);
    test2.Burn(40);


    return 0;
}
