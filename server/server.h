#ifndef SERVER_H
#define SERVER_H

#include <QMap>
#include <QDialog>
#include <QLabel>
#include <QNetworkSession>
#include <QTcpServer>
#include <QThread>
#include "clienthandler.h"
#include "databasehelper.h"
#include "mailmessage.h"

class Server : public QDialog
{
    Q_OBJECT
public:
    Server(QWidget *parent = 0);
    ~Server();

signals:
    void serverResponse(QString response);

protected slots:
    void sessionOpened();
    void handleClientRequest();
    void cleanUp(int clientNumber);

    void newUserRegistration(int clientNumber, QString userName, QString password);
    void validateUserAccount(int clientNumber, QString userName, QString password);
    void sendEmail(int clientNumber, QString fromUser, QString toUser, QString subject,
                   QString message);
    void deleteEmail(int clientNumber, int id);
    void getUserInbox(int clientNumber, QString userName);
    void getUserSentMail(int clientNumber, QString userName);

private:
    QLabel *m_serverStatusLabel;
    QPushButton *m_quitButton;
    QTcpServer *m_tcpServer;
    QNetworkSession *m_networkSession;

    // Each map to keep track of needed information. Maps will be updated on
    // deletion and such.
    QMap<int, QThread *> m_mapOfThreads;
    QMap<int, clientHandlerPointer> m_mapOfClientConnections;
    QMap<int, MailMessage *> m_mapOfMailMessages;
    QMap<QString, QString> m_listOfUsers;

    DatabaseHelper *m_databaseHelper;

    int m_nextClientNumber;
};

#endif // SERVER_H

