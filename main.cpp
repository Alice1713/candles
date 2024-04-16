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
        case ColorEnum::Green: return " Green ";
        case ColorEnum::White: return " White ";
        case ColorEnum::Yellow: return " Yellow ";
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

Candle *CreateCandle()
{

    int randType = rand()%3+1;
    int randColor = rand()%3+1;
    ColorEnum color;
    int randSmell = rand()%5+1;
    SmellEnum smell;
    switch (randSmell)
    {
        case 1: smell=SmellEnum::Cinnamon; break;
        case 2: smell=SmellEnum::Ginger; break;
        case 3: smell=SmellEnum::Jasmine; break;
        case 4: smell=SmellEnum::WithoutSmell; break;
        case 5: smell=SmellEnum::Apple; break;
        default: smell=SmellEnum::Unknown;
    }
    switch (randColor)
    {
        case 1: color=ColorEnum::Green; break;
        case 2: color=ColorEnum::White; break;
        case 3: color=ColorEnum::Yellow; break;
        default: color=ColorEnum::Unknown;

    }
    switch(randType)
    {
        case 1: return new Wax(color, smell);
        case 2: return new Paraffin(color, smell);
        case 3: return new Gel(color, smell);
        default: return NULL;
    }
}

void FirstContainersIter (Iterator<CandlePtr> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        const CandlePtr current = it->GetCurrent();
        int timeToBurn = rand()%80;
        current->Burn(timeToBurn);
        current->TrimWick();
        cout << "  " << endl;

    }

}

void WhiteColor (Iterator<CandlePtr> *it2)
{
    for(it2->First(); !it2->IsDone(); it2->Next())
    {
        const CandlePtr current2 = it2->GetCurrent();

        cout << "2" << PrintSmell(current2->GetSmell())<< endl;

    }

}

void WaxType (Iterator<CandlePtr> *it3)
{
        for(it3->First(); !it3->IsDone(); it3->Next())
    {
        const CandlePtr current3 = it3->GetCurrent();

        cout << "3" << PrintSmell(current3->GetSmell()) << endl;

    }

}

void WithoutSmellSmell (Iterator<CandlePtr> *it4)
{
        for(it4->First(); !it4->IsDone(); it4->Next())
    {
        const CandlePtr current4 = it4->GetCurrent();

        cout << "4" <<PrintSmell(current4->GetSmell()) << endl;

    }

}

void WhiteWithoutWax (Iterator<CandlePtr> *it5)
{
    for(it5->First(); !it5->IsDone(); it5->Next())
    {
        const CandlePtr current5 = it5->GetCurrent();
        cout << "5 " <<PrintColor(current5->GetColor()) <<  PrintSmell(current5->GetSmell()) <<  PrintType(current5->GetType())<< endl;

    }
}


int main()
{

// Первый тип контейнера
    int randFNumber = rand()%30;
    FirstContainer tryit(randFNumber);
    for(int i = 0; i<randFNumber; i++)
    {
        tryit.AddCandle(CreateCandle());

    }
    Iterator <CandlePtr> *it = tryit.GetIterator();
    FirstContainersIter (it);
    delete it;

// Второй тип контейнера list

    SecondContainer tryagain;
    int randNumber = rand()%90;
    for(int i = 0; i<randNumber; i++)
    {
        tryagain.AddCandle(CreateCandle());

    }

    Iterator <CandlePtr> *it2 = new CandleColorIDecorator(tryagain.GetIterator(), ColorEnum::White); //найти белые свечи
    WhiteColor (it2);
    delete it2;
    Iterator <CandlePtr> *it3 = new CandleTypeIDecorator(tryagain.GetIterator(), CandleType::Wax);
    WaxType (it3);
    delete it3;
    Iterator <CandlePtr> *it4 = new CandleSmellIDecorator(tryagain.GetIterator(), SmellEnum::WithoutSmell);
    WithoutSmellSmell (it4);
    delete it4;
    Iterator <CandlePtr> *it5 = new CandleSmellIDecorator(new CandleTypeIDecorator
                                                         (new CandleColorIDecorator(tryagain.GetIterator(),
                                                          ColorEnum::White), CandleType::Wax), SmellEnum::WithoutSmell);

    WhiteWithoutWax (it5);
    delete it5;

    return 0;
}
