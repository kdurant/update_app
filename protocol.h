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
    ERASE_BLOCK_RUN = 0x00100000,
    //    READ_BLOCK_ADDR,
    READ_BLOCK_RUN   = 0x00100001,
    WRITE_BLOCK_ADDR = 0x00100002,
    WRITE_BLOCK_DATA = 0x00100003,
    WRITE_BLOCK_RUN  = 0x00100004,
    RES_FLASH_DATA   = 0x80100002

} Command;

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

    /**
     * @brief 从返回的数据中得到nor flash的响应数据
     * @param frame
     * @return 
     */
    QString &decode(QByteArray &frame);
};

#endif  // PROTOCOL_H
