#include <iostream>
#include "candle.h"
#include <stdio.h>

using namespace std;

string PrintType(const CandleType type)
{
    switch(type)
    {

        case CandleType :: Wax: return "Wax candle";
        case CandleType :: Paraffin: return "Paraffin candle";
        case CandleType :: Gel: return "Gel candle";
        default: return "Unknown candle type";

    }
}

string PrintColor (const ColorEnum color)
{
    switch(color)
    {
        case ColorEnum::Green: return " green ";
        case ColorEnum::White: return " white ";
        case ColorEnum::Yellow: return " yellow ";
        default: return "Unknown";

    }
}

string PrintSmell (const SmellEnum smell)
{
    switch(smell)
    {
        case SmellEnum::Apple: return " Apple ";
        case SmellEnum::Cinnamon: return " Cinnamon ";
        case SmellEnum::Ginger: return " Ginger ";
        case SmellEnum::Jasmine: return " Jasmine ";
        case SmellEnum::WithoutSmell: return " WithoutSmell ";
        default: return "Unknown";


    }
}

int main()
{

    FirstContainer tryit(10);

    for(int i = 0; i<10; i++)
    {
        tryit.AddCandle(new Wax(ColorEnum::White, SmellEnum::Apple));

    }

    Iterator <CandlePtr> *it = tryit.GetIterator();
    for(it->First(); !it->IsDone(); it->Next())
    {
        const CandlePtr current = it->GetCurrent();

        if(current->GetColor()==ColorEnum::White)
        {
        cout <<  " (ok) " << endl;

        }
    }

    SecondContainer tryagain;
    for(int i = 0; i<2; i++)
    {
        tryagain.AddCandle(new Wax(ColorEnum::White, SmellEnum::Apple));

    }

        for(int i = 0; i<1; i++)
    {
        tryagain.AddCandle(new Gel ());

    }

       for(int i = 0; i<10; i++)
    {
        tryagain.AddCandle(new Paraffin(ColorEnum::White, SmellEnum::Cinnamon));

    }

    Iterator <CandlePtr> *it2 = new CandleColorIDecorator(tryagain.GetIterator(), ColorEnum::White); //найти белые свечи
    Iterator <CandlePtr> *it3 = new CandleTypeIDecorator(tryagain.GetIterator(), CandleType::Wax);
    Iterator <CandlePtr> *it4 = new CandleSmellIDecorator(tryagain.GetIterator(), SmellEnum::WithoutSmell);


    for(it2->First(); !it2->IsDone(); it2->Next())
    {
        const CandlePtr current2 = it2->GetCurrent();

        cout << "2" << PrintSmell(current2->GetSmell())<< endl;

    }

    for(it3->First(); !it3->IsDone(); it3->Next())
    {
        const CandlePtr current3 = it3->GetCurrent();

        cout << "3" << PrintSmell(current3->GetSmell()) << endl;

    }

        for(it4->First(); !it4->IsDone(); it4->Next())
    {
        const CandlePtr current4 = it4->GetCurrent();

        cout << "4" <<PrintSmell(current4->GetSmell()) << endl;

    }





    return 0;
}
