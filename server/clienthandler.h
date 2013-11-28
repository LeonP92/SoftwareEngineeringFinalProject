#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QtNetwork>
#include <QObject>

// Forward pointer for the class
class ClientHandler;
typedef QPointer<ClientHandler> clientHandlerPointer;

class ClientHandler : public QObject
{
    Q_OBJECT
public:
    ClientHandler(QTcpServer *server, int clientNumber);
    ~ClientHandler();

signals:
    void endClientConnection(int clientNumber);
    void newUserCreated(int clientNumber, QString userName, QString password);
    void userLoginAttempt(int clientNumber, QString userName, QString password);
    void mailSentCommand(int clientNumber, QString fromUser, QString toUser, QString subject,
                         QString message);
    void deleteEmailCommand(int clientNumber, int id);
    void userInboxRequest(int clientNumber, QString userName);
    void userSentMailRequest(int clientNumber, QString userName);

protected slots:
    void readClientData();
    void sendDataToClient(QString response);

protected:
    void analyzeCommand(QString command);

private:
    QTcpSocket *m_clientConnection;
    quint16 m_blockSize;

    int m_clientNumber;
};

#endif // CLIENTHANDLER_H
