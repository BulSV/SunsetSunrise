#include "functions.h"
#include <iostream>

namespace functions
{
int fromCharToInt(char  value)
{
    if(value < 0) {
        return (value + 0x100);
    }

    return value;
}

char fromIntToChar(int value)
{
    if(value > 0xFF) {
        std::cerr << "Error at fromIntToChar: value is grater then 255\n";

        return static_cast<char>(value & 0xFF);
    }

    if(value > 0x7F) {
        return static_cast<char>(value - 0x100);
    }

    return static_cast<char>(value);
}

float power(float num, int deg)
{
    float tempNum = 1.0f;
    for(int i = 0; i < deg; i++) {
        tempNum *= num;
    }

    if(deg < 0) {
        return 1.0f / tempNum;
    }

    return tempNum;
}

double power(double num, int deg)
{
    double tempNum = 1.0;
    for(int i = 0; i < deg; i++) {
        tempNum *= num;
    }

    if(deg < 0) {
        return 1.0 / tempNum;
    }

    return tempNum;
}

void swapBytes(QByteArray &ba)
{
    if(ba.size() != 2) {
        std::cerr << "Error at swapBytes: ba size not equal of 2\n";

        return;
    }

    char temp;
    temp = ba[0];
    ba[0] = ba[1];
    ba[1] = temp;
}

QByteArray byteToWord(int value)
{
    if(value > 0xFFFF) {
        std::cerr << "Warning at byteToWord: value greater then size of word type,"
                     " overflow will cut\n";
    }
    QByteArray ba;
    ba.resize(2);
    ba[0] = static_cast<char>(value / 256); // high byte
    ba[1] = static_cast<char>(value % 256); // low byte

    return ba;
}

int bin_dexTodex(int bin_dex)
{
    return (((bin_dex & 0xF0) >> 4) * 10 + (bin_dex & 0x0F));
}

// Convert word to byte
int wordToInt(QByteArray ba)
{
    if(ba.size() != 2) {
        std::cerr << "Error at wordToInt: ba size not equal of 2\n";

        return -1;
    }

    return (fromCharToInt(ba[0]) << 8) + fromCharToInt(ba[1]);
}

int round(float value)
{
    if(value > 0) {
        return (static_cast<int>(value + 0.5f));
    }

    return (static_cast<int>(value - 0.5f));
}


int round(double value)
{
    if(value > 0) {
        return (static_cast<int>(value + 0.5));
    }

    return (static_cast<int>(value - 0.5));
}

float round(float value, int precision)
{
    if(precision <= 0) {
        std::cerr << "Error at round: precision less or equal to zero\n";

        return value;
    }

    precision = static_cast<int>(power(10.0f, precision));
    value *= precision;
    value = round(value);

    return value /= precision;
}

double round(double value, int precision)
{
    if(precision <= 0) {
        std::cerr << "Error at round: precision less or equal to zero\n";

        return value;
    }

    precision = static_cast<int>(power(10.0, precision));
    value *= precision;
    value = round(value);

    return value /= precision;
}

float round(float value, float epsilon)
{
    if(fuzzyIsNull(epsilon)) {
        std::cerr << "Error at round: precision less or equal to zero\n";

        return value;
    }

    if(value < 0) {
        return static_cast<float>(static_cast<int>(value / epsilon - 0.5f) * epsilon);
    }

    return static_cast<float>(static_cast<int>(value / epsilon + 0.5f) * epsilon);
}

double round(double value, double epsilon)
{
    if(fuzzyIsNull(epsilon)) {
        std::cerr << "Error at round: precision less or equal to zero\n";

        return value;
    }

    if(value < 0) {
        return static_cast<double>(static_cast<int>(value / epsilon - 0.5) * epsilon);
    }

    return static_cast<double>(static_cast<int>(value / epsilon + 0.5) * epsilon);
}

// Convert hex representation 000000 to 00 00 00
QString toHumanHex(QByteArray ba)
{
    QString str;
    QByteArray baHex;
    baHex = ba.toHex().toUpper();
    for(int i = 0; i < baHex.size(); i++) {
        if(i % 2) {
            str = str + QString(baHex.at(i)) + ' ';
        } else {
            str = str + QString(baHex.at(i));
        }
    }

    return str;
}

// Convert milliseconds to seconds
QString msToSec(int time)
{
    int timeSec = time / 1000;
    int timeMSec = time % 1000;

    return (QString::number(timeSec) +
            QString::fromUtf8(".") +
            QString::number(timeMSec));
}

// Convert hours representation from 15,90 to 15,54
float decaToSexta(float time)
{
    float hours = static_cast<int>(time);
    float minuts = (time - static_cast<int>(time)) * 0.6f;
    time = hours + minuts;

    return time;
}

double decaToSexta(double time)
{
    double hours = static_cast<int>(time);
    double minuts = (time - static_cast<int>(time)) * 0.6;
    time = hours + minuts;

    return time;
}

// Convert hours representation from 15,54 to 15,90
float sextaToDeca(float time)
{
    float hours = static_cast<int>(time);
    float minuts = (time - static_cast<int>(time)) / 0.6f;
    time = hours + minuts;

    return time;
}

double sextaToDeca(double time)
{
    double hours = static_cast<int>(time);
    double minuts = (time - static_cast<int>(time)) / 0.6;
    time = hours + minuts;

    return time;
}

bool fuzzyIsNull(float value)
{
    return abs(value) <= 0.00001f;
}

bool fuzzyIsNull(double value)
{
    return abs(value) <= 0.000000000001;
}

} // namespace functions
