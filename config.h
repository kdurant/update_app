#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

#define BYTES_PER_WRITE 16

typedef struct _Update
{
    bool    hasWriteData;
    bool    hasReadData;
    QByteArray WriteData;  //
    QByteArray ReadData;
} Update;

#endif // CONFIG_H
