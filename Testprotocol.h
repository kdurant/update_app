#ifndef TESTPROTOCOL_H
#define TESTPROTOCOL_H

#include <QtTest/QtTest>

class TestProtocol: public QObject
{
    Q_OBJECT
public:
    TestProtocol();
private slots:
    void TestEncode();
};

#endif // TESTPROTOCOL_H
