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
// Convert word to byte
int wordToInt(QByteArray ba);
bool fuzzyIsNull(float value);
bool fuzzyIsNull(double value);
int round(float value);
int round(double value);
float round(float value, int precision);
double round(double value, int precision);
float round(float value, float epsilon);
double round(double value, float epsilon);
// Convert hex representation 000000 to 00 00 00
QString toHumanHex(QByteArray ba);
// Convert milliseconds to seconds
QString msToSec(int time);
// Convert hours representation from 15,90 to 15,54
float decaToSexta(float time);
double decaToSexta(double time);
// Convert hours representation from 15,54 to 15,90
float sextaToDeca(float time);
double sextaToDeca(double time);
}

#endif // FUNCTIONS_H
