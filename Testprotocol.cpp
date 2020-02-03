#include "Testprotocol.h"

TestProtocol::TestProtocol()
{

}

void TestProtocol::TestEncode()
{
    QString str = "Hello";
    QVERIFY(str.toUpper() == "HELLO");
}
