#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <QString>
#include <QByteArray>
#include <QVector>
#include <QQueue>

#include <QDebug>

// 通信协议参数

#define COMMAND_POS 24
#define COMMAND_LEN 8
#define PCK_NUMER_POS 32
#define PCK_NUMBER_LEN 8
#define VALID_LEN_POS 40
#define VALID_LEN_LEN 8

typedef enum
{
    GET_SYS_VERSION,
//    ERASE_BLOCK_ADDR = 0x8000000C,
    ERASE_BLOCK_RUN = 0x0000000C,
//    READ_BLOCK_ADDR,
    READ_BLOCK_RUN,
    WRITE_BLOCK_ADDR,
    WRITE_BLOCK_DATA,
    WRITE_BLOCK_RUN
}Command;

typedef struct _data
{
    QVector<qint32> data;
} NorFlash_Data;

class Protocol
{
    QString      head;
    qint32       cmd_num;
    qint32       command;
    qint32       pck_num;
    qint32       data_len;
    QVector<int> data;
    qint32       checsum;

    NorFlash_Data norflash_data[4];

public:
    Protocol();
    ~Protocol();

    QByteArray encode(qint32 command, qint32 data_len, qint32 data);
    QByteArray encode(qint32 command, QString &data);
    QString &decode(QQueue<QString> &frame);
};

#endif  // PROTOCOL_H
