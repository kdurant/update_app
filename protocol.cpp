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

QByteArray Protocol::encode(qint32 command, QString &data)
{
    QByteArray frame;
    QByteArray origin;
    qint32     checksum = 0xeeeeffff;
    origin.append("AA555AA5AA555AA5");
    origin.append(QByteArray::number(cmd_num++, 16).rightJustified(8, '0'));
    origin.append(QByteArray::number(command, 16).rightJustified(8, '0'));
    origin.append(QByteArray::number(pck_num, 16).rightJustified(8, '0'));
    origin.append(QByteArray::number(256, 16).rightJustified(8, '0'));
    //    origin.append(QByteArray::number(data, 16).rightJustified(8, '0').append(504, '0'));

    for(int i = 0; i < data.size(); i += 2)
    {
        origin.append(QByteArray::number(data.mid(i, 2).toInt(nullptr, 16), 16));
    }
    origin.append(QByteArray::number(checksum, 16).rightJustified(8, '0'));
    frame = QByteArray::fromHex(origin);
#ifdef PRINT_DEBUG_INFO
    qDebug() << frame.toHex();
#endif
    return frame;
}

QString &Protocol::decode(QByteArray &frame)
{
}
