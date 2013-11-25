/***********************************************
 * Start connection in constructor.
 *
 *
 *
 *
 *
 ************************************************/
#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QTcpSocket>
#include "email.h"

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTextEdit;
class QListView;
class QTcpSocket;
class QNetworkSession;
QT_END_NAMESPACE


class Client : public QDialog
{
    Q_OBJECT

public:
    Client(QWidget *parent = 0);

protected slots:
    //Login window
    void enableStartConnectionButton();
    void startConnection();
    void sessionOpened();
    void registerUser();
    void login();

    //Main client view
    void viewMessage();
    void newMessage();
    void deleteMessage();
    void viewSentMessages();
    void sendMessage();
    void reply();
    void displayError(QAbstractSocket::SocketError socketError);

    void readServerResponse();


private:
    //Login window variables
    QLabel *m_userLabel;
    QLabel *m_passwordLabel;
    QLabel *m_hostLabel;
    QLabel *m_portLabel;
    QLabel *m_loginStatusLabel;
    QLineEdit *m_hostEdit;
    QLineEdit *m_portEdit;
    QLineEdit *m_userEdit;
    QLineEdit *m_passwordEdit;
    QPushButton *m_registerBtn;
    QPushButton *m_loginBtn;
    QPushButton *m_connectBtn;

    //Main client view varibales
    QLabel *m_currentUser;
    QLabel *m_toFromLabel;
    QLabel *m_subjectLabel;
    QLabel *m_statusLabel;
    QListView *m_inbox;
    QPushButton *m_view;
    QPushButton *m_new;
    QPushButton *m_delete;
    QPushButton *m_viewSent;
    QPushButton *m_send;
    QPushButton *m_reply;
    QDialogButtonBox *buttonBox;

    QList <Email*> m_emails;
    QList <Email*> m_sentMail;

    QTcpSocket *m_tcpSocket;
    quint16 m_blockSize;

    QNetworkSession *networkSession;
};


#endif
