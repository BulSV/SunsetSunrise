#include "bulsv_lib.h"
#include <iostream>
int BulSV_Lib::fromCharToInt(char  c)
{
	if(c < 0)
    {
        return (c + 0x100);
    }
    else
    {
        return c;
    }
}

char BulSV_Lib::fromIntToChar(int v)
{
	if(v > 255)
	{
		std::cerr << "Error: value > 255\n";
		return 0;
	}
	if(v > 127)
	{
		return (v - 256);
	}
	else
	{
		return v;
	}
}

float BulSV_Lib::power(float num, int deg)
{
    if(!deg) return 1.0;
    if(deg > 0)
    {
        for(int i = 1; i < deg; ++i)
        {
            num *= num;
        }
        return num;
    }
    else
    {
        for(int i = 0; i > deg; --i)
        {
            if(i)
            {
                num /= num;
            }
            else
            {
                num = 1/num;
            }
        }
        return num;
    }
}

void BulSV_Lib::swapBytes(QByteArray &ba)
{
    QByteArray temp;
    temp.resize(1); // можно не писать!
    temp[0]=ba[0];
    ba[0]=ba[1];
    ba[1]=temp[0];
}

QByteArray BulSV_Lib::byteToWord(int nInt)
{
    QByteArray ba;
    ba.resize(2);   //можно не писать!
    ba[0]=nInt%256; // младший байт
    ba[1]=nInt/256; // старший байт
    swapBytes(ba);  // если необходимо! Или можно поменять местами
    // индексы в двух верхних строчках
    return ba;
}

float BulSV_Lib::roundFloat(float f, float e)
{
    if(f >= 0)
        return (float)((int)(f/e + 0.5)*e);
    else
        return (float)((int)(f/e - 0.5)*e);
}

int BulSV_Lib::bin_dexTodex(int bin_dex)
{
    return (((bin_dex & /*0xF0*/0b11110000)>>4)*10 + (bin_dex & 0x0F));
}

// преобразует word в byte
int BulSV_Lib::wordToInt(QByteArray ba)
{
    if(ba.size() != 2)
        return -1;

    int temp = ba[0];
    if(temp < 0)
    {
        temp += 0x100; // 256;
        temp *= 0x100;
    }
    else
        temp = ba[0]*0x100; // старший байт

    int i = ba[1];
    if(i < 0)
    {
        i += 0x100; // 256;        
        temp += i;
    }
    else
        temp += ba[1]; // младший байт

    return temp;
}

int BulSV_Lib::round(double d)
{
    if(d > 0)
        return ((int)(d + 0.5));
    else
        return ((int)(d - 0.5));
}

float BulSV_Lib::round(float f, int prec)
{
    prec = power(10, prec);
    f *= prec;
    f = (float)round(f);

    return f /= prec;
}

int BulSV_Lib::power(int num, int deg)
{
    int tempNum = 1;

    for(int i = 0; i < deg; ++i)
        tempNum *= num;
    return tempNum;
}

// Преобразует hex вида 000000aa в 00 00 00 AA
QString BulSV_Lib::toHumanHex(QByteArray ba)
{
    QString str(' ');
    QByteArray baHex;
    baHex = ba.toHex().toUpper();
    for(int i = 0; i < baHex.size(); ++i)
    {
        if(i % 2)
            str = str + QString(baHex.at(i)) + ' ';
        else
            str = str + QString(baHex.at(i));
    }
    str.remove(0, 1);
    return str;
}

// Преобразует милисекунды в секунды
QString BulSV_Lib::mSecToSec(int time)
{
    int timeSec = time / 1000;
    int timeMSec = time % 1000;
    return (QString::number(timeSec) +
            QString::fromUtf8(".") +
            QString::number(timeMSec));
}

// 15,90 часов к виду 15,54 часов
//float BulSV_Lib::decaToSexta(float &time)
//{
//    float hours = (int)time;
//    float minuts = (time - (int)time)*0.6;
//    time = hours + minuts;
//    return time;
//}

float BulSV_Lib::decaToSexta(float time)
{
    float hours = (int)time;
    float minuts = (time - (int)time)*0.6;
    time = hours + minuts;
    return time;
}

// 15,54 часов к виду 15,90 часов
//float BulSV_Lib::sextaToDeca(float &time)
//{
//    float hours = (int)time;
//    float minuts = (time - (int)time)/0.6;
//    time = hours + minuts;
//    return time;
//}

float BulSV_Lib::sextaToDeca(float time)
{
    float hours = (int)time;
    float minuts = (time - (int)time)/0.6;
    time = hours + minuts;
    return time;
}
