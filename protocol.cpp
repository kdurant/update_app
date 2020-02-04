#include "protocol.h"

Protocol::Protocol()
{
    cmd_num = 1;
}

Protocol::~Protocol()
{
}

QByteArray Protocol::encode(qint32 command, qint32 data_len, qint32 data)
{
    QByteArray frame;
    QByteArray origin;
    qint32     checksum = 0xeeeeffff;
    origin.append("AA555AA5AA555AA5");
    origin.append(QByteArray::number(cmd_num++, 16).rightJustified(8, '0'));
    origin.append(QByteArray::number(command, 16).rightJustified(8, '0'));
    origin.append(QByteArray::number(pck_num, 16).rightJustified(8, '0'));
    origin.append(QByteArray::number(data_len, 16).rightJustified(8, '0'));
    origin.append(QByteArray::number(data, 16).rightJustified(8, '0').append(504, '0'));
    origin.append(QByteArray::number(checksum, 16).rightJustified(8, '0'));
    frame = QByteArray::fromHex(origin);
#ifdef PRINT_DEBUG_INFO
    qDebug() << frame.toHex();
#endif
    return frame;
}

QString &Protocol::decode(QQueue<QString> &frame)
{
//    return ;
}
