#ifndef CANDLE_H_INCLUDED
#define CANDLE_H_INCLUDED
#include <vector>
#include <list>
#include "Patterns.h"

using namespace std;

enum class ColorEnum : int
{
    White = 0,
    Green = 1,
    Yellow = 2,
    Unknown = -1
};

enum class CandleType : int
{
    Wax = 0,
    Paraffin = 1,
    Gel = 2,
    Unknown = -1
};

enum class SmellEnum : int
{
    Apple,
    Cinnamon,
    Ginger,
    Jasmine,
    WithoutSmell,
    Unknown = -1
};


class Candle
{
    protected:
        ColorEnum Color;
        SmellEnum Smell;
        int BurningTime;


    public:
        virtual ~ Candle() {};
        ColorEnum GetColor() const {return Color; }
        SmellEnum GetSmell() const {return Smell; }
        virtual CandleType GetType() const = 0;
        virtual int Burn(int time) = 0;
        virtual void TrimWick() = 0;// подрезка фитиля
        static Candle *Create(CandleType type);
};

typedef Candle *CandlePtr;

class Wax : public Candle
{
public:
    Wax(): Candle() {Color = ColorEnum::White; }//цвет по умолчанию белый
    Wax(ColorEnum color) : Candle() {Color = color; Smell = SmellEnum::WithoutSmell; } //можно задать свечу только с параметром цвет
    Wax(ColorEnum color, SmellEnum smell) : Candle() {Color = color; Smell = smell;  }
    int BurningTime = 100;
    CandleType GetType() const {return CandleType::Wax; }
    int Burn(int time) {
        int TimeLeft = BurningTime - time;
        if (TimeLeft>=0)
        {
           cout << "Wax candle is burning " << time << " min... "<< endl;
        };

        if ((BurningTime>0)&&(TimeLeft<0))
        {
            cout << "Wax candle is burning " << BurningTime << " min... " << endl;
            cout << "The candle can no longer burn! "<< endl;
        };
        BurningTime = TimeLeft;
        return TimeLeft;}
    void TrimWick() {cout << " Wick trimmed by 2 mm"; }

};

class Paraffin : public Candle
{
public:
    Paraffin(): Candle() {Color = ColorEnum::White; }
    Paraffin(ColorEnum color) : Candle() {Color = color; Smell = SmellEnum::WithoutSmell; }
    Paraffin(ColorEnum color, SmellEnum smell) : Candle() {Color = color; Smell = smell; }
    int BurningTime = 60;
    CandleType GetType() const {return CandleType::Paraffin; }
        int Burn(int time) {
        int TimeLeft = BurningTime - time;
        if (TimeLeft>=0)
        {
           cout << "Paraffin candle is burning " << time << " min... "<< endl;
        };

        if ((BurningTime>0)&&(TimeLeft<0))
        {
            cout << "Paraffin candle is burning " << BurningTime << " min... " << endl;
            cout << "The paraffin candle can no longer burn! "<< endl;
        };
        BurningTime = TimeLeft;

        return TimeLeft;}
    void TrimWick() {cout << " Wick trimmed by 3 mm"; }

};

class Gel : public Candle
{
public:
    Gel(): Candle() {Color = ColorEnum::Green; Smell = SmellEnum::WithoutSmell; }
    Gel(ColorEnum color) : Candle() {Color = color; Smell = SmellEnum::WithoutSmell; }
    Gel(ColorEnum color, SmellEnum smell) : Candle() {Color = color; Smell = smell; }
    int BurningTime = 30;
    CandleType GetType() const {return CandleType::Gel; }
    int Burn(int time) {
        int TimeLeft = BurningTime - time;
        if (TimeLeft>=0)
        {
           cout << "Gel candle is burning " << time << " min... "<< endl;
        }
        else

        if ((BurningTime>0)&&(TimeLeft<0))
        {
            cout << "Gel candle is burning " << BurningTime << " min... " << endl;
            cout << "The gel candle can no longer burn! "<< endl;
        };
        BurningTime = TimeLeft;

        return TimeLeft;}
        void TrimWick() {cout << " Wick trimmed by 1 mm"; }
};

class FCIterator : public Iterator<CandlePtr>
{
private:
    const CandlePtr *CandleBox;
    int Position;
    int CandleCount;
public:
    FCIterator(const CandlePtr *candleBox, int candleCount)
    {
        CandleBox = candleBox;
        CandleCount = candleCount;
        Position = 0;
    }

    void First() {Position = 0; }
    void Next() { Position++; }
    bool IsDone() const {return Position >= CandleCount; }
    CandlePtr GetCurrent() const { return CandleBox[Position]; }
};


class Container
{
    protected:
        CandlePtr *CandleBox;
        int Count;
        int MaxSize;
    public:
        virtual void AddCandle (CandlePtr newCandle) = 0;
        virtual int GetCount () const = 0;
        virtual ~Container(){}

};


class FirstContainer : public Container
{
    public:
        FirstContainer(int maxSize)
        {
            CandleBox = new CandlePtr[maxSize];
            for(int i=0; i<maxSize; i++)
            {
                CandleBox[i] = NULL;
                Count = 0;
                MaxSize = maxSize;
            }
        }
        void AddCandle (CandlePtr newCandle)
        {
            CandleBox[Count++] = newCandle;
        }
        ~FirstContainer()
        {
            for(int i=0; i<MaxSize; i++)
        {
                if(CandleBox[i]!= NULL)
                {
                    delete CandleBox[i];
                    CandleBox[i] = NULL;
                }
        }

            delete[] CandleBox;
        }

        int GetCount() const {return Count;}

        CandlePtr GetByIndex(int index) const { return CandleBox[index]; }
        Iterator<CandlePtr> *GetIterator()
        {
            return new FCIterator(CandleBox, Count);
        }
};

class SCIterator : public Iterator<CandlePtr>
{
private:
    const list<CandlePtr> *CandleBox;
    list<CandlePtr>::const_iterator it;

public:
    SCIterator(const list<CandlePtr> *candleBox)
    {
        CandleBox = candleBox;
        it = CandleBox->begin();
    }

    void First() {it = CandleBox->begin();}
    void Next() {it++; }
    bool IsDone() const {return it == CandleBox->end(); }
    CandlePtr GetCurrent() const { return *it; }
};

class SecondContainer
{
private:
    list<CandlePtr> CandleBox;

public:
    void AddCandle(CandlePtr newCandle) {CandleBox.push_back(newCandle);}
    int GetCount() const {return CandleBox.size(); }
     Iterator<CandlePtr> *GetIterator()
    {
        return new SCIterator(&CandleBox);
    }
};

class CandleColorIDecorator : public IteratorDecorator<CandlePtr>
{
private:
    ColorEnum TargetColor;

public:
    CandleColorIDecorator(Iterator<CandlePtr> *it, ColorEnum targetColor)
    : IteratorDecorator(it)
    {
        TargetColor = targetColor;
    }

    void First()
    {
        It->First();
        while(!It->IsDone() && It->GetCurrent()->GetColor() != TargetColor)
        {
            It->Next();
        }

    }

    void Next()
    {
        do
        {
            It->Next();

        } while(!It->IsDone() && It->GetCurrent()->GetColor() != TargetColor);
    }

};


class CandleTypeIDecorator : public IteratorDecorator<CandlePtr>
{
private:
    CandleType TargetType;

public:
    CandleTypeIDecorator(Iterator<CandlePtr> *it, CandleType targetType)
    : IteratorDecorator(it)
    {
        TargetType = targetType;
    }

    void First()
    {
        It->First();
        while(!It->IsDone() && It->GetCurrent()->GetType() != TargetType)
        {
            It->Next();
        }

    }

    void Next()
    {
        do
        {
            It->Next();

        } while(!It->IsDone() && It->GetCurrent()->GetType() != TargetType);
    }

};

class CandleSmellIDecorator : public IteratorDecorator<CandlePtr>
{
private:
    SmellEnum TargetSmell;

public:
    CandleSmellIDecorator(Iterator<CandlePtr> *it, SmellEnum targetSmell)
    : IteratorDecorator(it)
    {
        TargetSmell = targetSmell;
    }

    void First()
    {
        It->First();
        while(!It->IsDone() && It->GetCurrent()->GetSmell() != TargetSmell)
        {
            It->Next();
        }

    }

    void Next()
    {
        do
        {
            It->Next();

        } while(!It->IsDone() && It->GetCurrent()->GetSmell() != TargetSmell);
    }

};







#endif // CANDLE_H_INCLUDED
