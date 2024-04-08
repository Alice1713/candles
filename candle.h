#ifndef CANDLE_H_INCLUDED
#define CANDLE_H_INCLUDED
#include <vector>
#include <list>

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
        virtual void TrimWick()=0;// подрезка фитиля
        static Candle *Create(CandleType type);
};

typedef Candle * CandlePtr;

class Wax : public Candle
{
public:
    Wax(): Candle() {Color = ColorEnum::White; }//цвет по умолчанию белый
    Wax(ColorEnum color) : Candle() {Color = color; }
    Wax(SmellEnum smell) : Candle() {Smell = smell; }
    int BurningTime = 100;
    CandleType GetType() const {return CandleType::Wax; }
    int Burn(int time) {
        int TimeLeft = BurningTime - time;
        if (TimeLeft>=0)
        {
           cout << "Wax candle is burning " << time << " min"<< endl;
        };

        if ((BurningTime>0)&&(TimeLeft<0))
        {
            cout << "Wax candle is burning " << BurningTime << " min" << endl;
            cout << "The candle can no longer burn"<< endl;
        };
        BurningTime = TimeLeft;
        return TimeLeft;}
    void TrimWick() {cout << "Wick trimmed by 1 mm"; }

};

class Paraffin : public Candle
{
public:
    Paraffin(): Candle() {Color = ColorEnum::White; }
    Paraffin(ColorEnum color) : Candle() {Color = color; }
    Paraffin(SmellEnum smell) : Candle() {Smell = smell; }
    int BurningTime = 60;
    CandleType GetType() const {return CandleType::Paraffin; }
        int Burn(int time) {
        int TimeLeft = BurningTime - time;
        if (TimeLeft>=0)
        {
           cout << "Paraffin candle is burning " << time << " min"<< endl;
        };

        if ((BurningTime>0)&&(TimeLeft<0))
        {
            cout << "Paraffin candle is burning " << BurningTime << " min" << endl;
            cout << "The paraffin candle can no longer burn"<< endl;
        };
        BurningTime = TimeLeft;

        return TimeLeft;}
    void TrimWick() {cout << "Wick trimmed by 3 mm"; }

};

class Gel : public Candle
{
public:
    Gel(SmellEnum smell) : Candle() {Smell = smell; }
    Gel(): Candle() {Color = ColorEnum::White; }
    Gel(ColorEnum color) : Candle() {Color = color; }
    int BurningTime = 30;
    CandleType GetType() const {return CandleType::Gel; }
    int Burn(int time) {
        int TimeLeft = BurningTime - time;
        if (TimeLeft>=0)
        {
           cout << "Gel candle is burning " << time << " min"<< endl;
        }
        else

        if ((BurningTime>0)&&(TimeLeft<0))
        {
            cout << "Gel candle is burning " << BurningTime << " min" << endl;
            cout << "The gel candle can no longer burn"<< endl;
        };
        BurningTime = TimeLeft;

        return TimeLeft;}
};


#endif // CANDLE_H_INCLUDED
