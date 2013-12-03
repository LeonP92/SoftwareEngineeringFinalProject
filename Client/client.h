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
#include <QtGui>
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
    void loadMainUI();
    void refreshInbox(QString wanted);
    void sendToServer(QString command);
    void handleServerResponse(QString servResponse);

protected slots:
public Q_SLOTS:
    //Login window
    void enableStartConnectionButton();
    void startConnection();
    void sessionOpened();
    void registerUser();
    void login();

    //Main client view
    void viewMessage(QListWidgetItem* item);
    void newMessage();
    void deleteMessage();
    void viewSentMessages();
    void sendMessage();
    void reply();
    void displayError(QAbstractSocket::SocketError socketError);

    void readServerResponse();


private:
    //Login window variables
    QGridLayout loginLayout;
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
    QLabel *m_bodyLabel;
    QLabel *m_statusLabel;
    QListWidget *m_inbox;
    QLineEdit *m_toFromEdit;
    QLineEdit *m_subjectEdit;
    QTextEdit *m_bodyEdit;
    QPushButton *m_view;
    QPushButton *m_new;
    QPushButton *m_delete;
    QPushButton *m_viewSent;
    QPushButton *m_send;
    QPushButton *m_reply;
    QDialogButtonBox *buttonBox;
    QDialogButtonBox *belowButtonBox;
    QDialogButtonBox *aboveButtonBox;

    QList <Email*> m_emails;
    QList <Email*> m_sentMail;
    int m_selectedEmailID;
    bool m_viewingSent;

    QString m_user;
    QString m_password;
    QTcpSocket *m_tcpSocket;
    quint16 m_blockSize;

    QNetworkSession *networkSession;
};


#endif
