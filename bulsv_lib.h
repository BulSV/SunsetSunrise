#ifndef BULSV_LIB_H
#define BULSV_LIB_H

#include <QByteArray>
#include <QString>

namespace BulSV_Lib
{	
    int fromCharToInt(char  c);
    char fromIntToChar(int v);
	float power(float num, int deg);
	void swapBytes(QByteArray &ba);
	QByteArray byteToWord(int nInt);
	float roundFloat(float f, float e);
	int bin_dexTodex(int bin_dex);
	// преобразует word в byte
	int wordToInt(QByteArray ba);
	int round(double d);
	float round(float f, int prec);
	int power(int num, int deg);
	// Преобразует hex вида 000000 в 00 00 00
    QString toHumanHex(QByteArray ba);
	// Преобразует милисекунды в секунды
    QString mSecToSec(int time);
    // 15,90 часов к виду 15,54 часов
//    float decaToSexta(float &time);
    float decaToSexta(float time);
    // 15,54 часов к виду 15,90 часов
//    float sextaToDeca(float &time);
    float sextaToDeca(float time);
}

namespace BLib = BulSV_Lib;
#endif // BULSV_LIB_H
