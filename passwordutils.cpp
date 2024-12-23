#include "passwordutils.h"
#include <QList>
#include <QChar>
#include <QMap>
#include <QVector>

const QMap<int, QVector<QChar>> PasswordUtils::charTypeLists = {
    { LOWER_CASE, QList<QChar>{'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'} },
    { UPPER_CASE, QList<QChar>{'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'} },
    { SYMBOL, QList<QChar>{'!','@','#','$','%','^','&','*','(',')','-','=','_','+','~'} },
    { NUMBER, QList<QChar>{'0','1','2','3','4','5','6','7','8','9'} }
};

