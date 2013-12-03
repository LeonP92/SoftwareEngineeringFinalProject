#include "server.h"

#include <QtTest/QTest>
#include <QtGui>
#include <QTestEventList>
#include <QDebug>
#include <iostream>

Q_DECLARE_METATYPE(Server*)

class TestServer:public QObject
{
    Q_OBJECT

public:
    void sendCommand(QString commandString, QTcpSocket* tcpSocket,
                     QByteArray dataBlock);

private slots:
    void testConstructor();

    void testClientMap_data();
    void testClientMap();

    void testClientConnection_data();
    void testClientConnection();

    void testMessageReceived();
};

void TestServer::sendCommand(QString commandString, QTcpSocket* tcpSocket,
                             QByteArray dataBlock)
{
    QDataStream outputData(&dataBlock, QIODevice::WriteOnly);

    outputData.setVersion(QDataStream::Qt_4_0);
    outputData << (quint16)0;
    outputData << commandString;
    outputData.device()->seek(0);
    outputData << (quint16)(dataBlock.size()-sizeof(quint16));
    tcpSocket->write(dataBlock);
    tcpSocket->waitForBytesWritten(3000);
    QTest::qWait(100);
}

void TestServer::testConstructor()
{
    QWidget *parent = new QWidget;
    Server *server = new Server(parent);

    qApp->processEvents();
    bool validDatabase = server->isDatabaseValid();

    delete server;
    server = NULL;

    QVERIFY(validDatabase == true);
}

void TestServer::testClientMap_data()
{
    QTest::addColumn<Server*>("server");
    QTest::addColumn<int>("sizeOfClientMap");

    QWidget *parent = new QWidget;
    Server *server = new Server(parent);
    QString ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    QTest::newRow("test no clients") << server << 0;

    Server *server1 = new Server(parent);
    int serverPort = server1->getServerPort();

    for (int i = 0; i < 5; i++) {
        QTcpSocket *socket = new  QTcpSocket();
        socket->connectToHost(ipAddress, serverPort);
    }

    QTest::newRow("test 5 clients") << server1 << 5;

    Server *server2 = new Server(parent);
    int serverPort2 = server2->getServerPort();

    for (int i = 0; i < 10; i++) {
        QTcpSocket *socket = new QTcpSocket();
        socket->connectToHost(ipAddress, serverPort2);
    }

    QTest::newRow("test 10 clients") << server2 << 10;

    Server *server3 = new Server(parent);
    int serverPort3 = server3->getServerPort();

    for (int i = 0; i < 15; i++) {
        QTcpSocket *socket = new  QTcpSocket();
        socket->connectToHost(ipAddress, serverPort3);
    }

    QTest::newRow("test 15 clients") << server3 << 15;
    qApp->processEvents();
}

void TestServer::testClientMap()
{
    QFETCH(Server*, server);
    QFETCH(int, sizeOfClientMap);

    QVERIFY(server->getClientMap().size() == sizeOfClientMap);
}

void TestServer::testClientConnection_data()
{
    QTest::addColumn<Server*>("testServer");
    QTest::addColumn<int>("numberOfClients");

    QWidget *parent = new QWidget;
    Server *server = new Server(parent);
    QString ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    QTest::newRow("test no clients") << server << 0;

    Server *server1 = new Server(parent);
    int serverPort = server1->getServerPort();

    for (int i = 0; i < 5; i++) {
        QTcpSocket *socket = new  QTcpSocket();
        socket->connectToHost(ipAddress, serverPort);
    }

    QTest::newRow("test 5 clients") << server1 << 5;

    Server *server2 = new Server(parent);
    int serverPort2 = server2->getServerPort();

    for (int i = 0; i < 10; i++) {
        QTcpSocket *socket = new QTcpSocket();
        socket->connectToHost(ipAddress, serverPort2);
    }

    QTest::newRow("test 10 clients") << server2 << 10;

    Server *server3 = new Server(parent);
    int serverPort3 = server3->getServerPort();

    for (int i = 0; i < 15; i++) {
        QTcpSocket *socket = new  QTcpSocket();
        socket->connectToHost(ipAddress, serverPort3);
    }

    QTest::newRow("test 15 clients") << server3 << 15;
    qApp->processEvents();

}

void TestServer::testClientConnection()
{
    QFETCH(Server*, testServer);
    QFETCH(int, numberOfClients);

    QVERIFY(testServer->getNumberOfClients() == numberOfClients);
}

void TestServer::testMessageReceived()
{
    QTest::addColumn<Server*>("server");
    QTest::addColumn<int>("numberOfMessages");

    QWidget *parent = new QWidget;
    QString ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    Server *server = new Server(parent);
    int serverPort = server->getServerPort();

    QTcpSocket *socket = new  QTcpSocket();
    socket->connectToHost(ipAddress, serverPort);
    qApp->processEvents();

    QByteArray dataBlock;
    QString commandString =  "NEWUSER {:} spongebob {:} jellyfishing";
    sendCommand(commandString, socket, dataBlock);

    commandString = "USERLOGIN {:} spongebob {:} jellyfishing";
    sendCommand(commandString, socket, dataBlock);

    commandString = "GETSENT {:} spongebob";
    sendCommand(commandString, socket, dataBlock);

    commandString =  "GETINBOX {:} spongebob";
    sendCommand(commandString, socket, dataBlock);

    commandString =  "DELETEMAIL {:} 0";
    sendCommand(commandString, socket, dataBlock);

    commandString =  "UNKNOWNCOMMAND {:} spongebob {:} jellyfishing";
    sendCommand(commandString, socket, dataBlock);

    commandString =  "SENDMAIL {:} spongebob {:} spongebob {:} Hi {:} HI";
    sendCommand(commandString, socket, dataBlock);

    QVERIFY(server->getNumberOfCommandsReceived() == 6);

}

QTEST_MAIN (TestServer)
#include "testserver.moc"
