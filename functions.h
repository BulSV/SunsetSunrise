#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QByteArray>
#include <QString>

namespace functions
{
template<typename T>
T abs(T value)
{
    if(value < 0) {
        return -value;
    }

    return value;
}
int fromCharToInt(char  value);
char fromIntToChar(int value);
float power(float num, int deg);
double power(double num, int deg);
void swapBytes(QByteArray &ba);
QByteArray byteToWord(int value);
int bin_dexTodex(int bin_dex);
// преобразует word в byte
int wordToInt(QByteArray ba);
bool fuzzyIsNull(float value);
bool fuzzyIsNull(double value);
int round(float value);
int round(double value);
float round(float value, int precision);
double round(double value, int precision);
float round(float value, float epsilon);
double round(double value, float epsilon);
// Преобразует hex вида 000000 в 00 00 00
QString toHumanHex(QByteArray ba);
// Преобразует милисекунды в секунды
QString msToSec(int time);
// 15,90 часов к виду 15,54 часов
float decaToSexta(float time);
double decaToSexta(double time);
// 15,54 часов к виду 15,90 часов
float sextaToDeca(float time);
double sextaToDeca(double time);
}

#endif // FUNCTIONS_H
