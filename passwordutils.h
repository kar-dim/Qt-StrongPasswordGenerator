#ifndef PASSWORDUTILS_H
#define PASSWORDUTILS_H

#include <QChar>
#include <QVector>
#include <QMap>

enum CHARACTER_TYPE
{
    LOWER_CASE,
    UPPER_CASE,
    SYMBOL,
    NUMBER
};

class PasswordUtils
{
public:
    PasswordUtils() = delete;
    static const QMap<int, QVector<QChar>> charTypeLists;
};

#endif // PASSWORDUTILS_H
