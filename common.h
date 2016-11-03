#ifndef COMMON_H
#define COMMON_H

#include <QString>

struct BookBase
{
    enum index
    {
        book=0,
        writer,
        ISBN,
        info,
        indexNum
    };

    QString infos[4];
};

#endif // COMMON_H
