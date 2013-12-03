

#include <QtNetwork>

#include "client.h"


///
/// \brief Client::Client
/// \param parent
/// constructor for the Client class
Client::Client(QWidget *parent)
:   QDialog(parent), networkSession(0)
{
    // Setting up widgets for the login window
    // set labels
    m_userLabel = new QLabel(tr("Email: "));
    m_passwordLabel = new QLabel(tr("Password: "));
    m_hostLabel = new QLabel(tr("IP: "));
    m_portLabel = new QLabel(tr("Port: "));
    m_loginStatusLabel = new QLabel(tr("Please fill in IP and port and press Connect."));

    // setup edits
    m_hostEdit = new QLineEdit;
    m_portEdit = new QLineEdit;
    m_portEdit->setValidator(new QIntValidator(1, 65535, this));
    m_userEdit = new QLineEdit;
    m_passwordEdit = new QLineEdit;

    // connect labels to edits
    m_userLabel->setBuddy(m_userEdit);
    m_passwordLabel->setBuddy(m_passwordEdit);
    m_hostLabel->setBuddy(m_hostEdit);
    m_portLabel->setBuddy(m_portEdit);

    // setup buttons
    m_registerBtn = new QPushButton(tr("Register"));
    m_loginBtn = new QPushButton(tr("Log in"));
    m_connectBtn = new QPushButton(tr("Connect"));

    // initial button settings
    m_connectBtn->setDefault(true);
    //m_loginBtn->setEnabled(false);
    m_registerBtn->setEnabled(false);

    // button box
    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(m_connectBtn, QDialogButtonBox::ActionRole);
    buttonBox->addButton(m_registerBtn, QDialogButtonBox::ActionRole);
    buttonBox->addButton(m_loginBtn, QDialogButtonBox::ActionRole);

    // connect button press signals to slots
    connect(m_connectBtn, SIGNAL(clicked()), this, SLOT(startConnection()));
    connect(m_registerBtn, SIGNAL(clicked()), this, SLOT(registerUser()));
    connect(m_loginBtn, SIGNAL(clicked()), this, SLOT(login()));

    // read from server when server sends data
    m_tcpSocket = new QTcpSocket(this);
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(readServerResponse()));
    connect(m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
                this, SLOT(displayError(QAbstractSocket::SocketError)));

    // put widgets on a window
    //QGridLayout *loginLayout = new QGridLayout;

    loginLayout.addWidget(m_hostLabel, 0, 0);
    loginLayout.addWidget(m_hostEdit, 0, 1);
    loginLayout.addWidget(m_portLabel, 1, 0);
    loginLayout.addWidget(m_portEdit, 1, 1);
    loginLayout.addWidget(m_userLabel, 2, 0);
    loginLayout.addWidget(m_userEdit, 2, 1);
    loginLayout.addWidget(m_passwordLabel, 3, 0);
    loginLayout.addWidget(m_passwordEdit, 3, 1);
    loginLayout.addWidget(m_loginStatusLabel, 4, 0, 1, 2);
    loginLayout.addWidget(buttonBox, 5, 0, 1, 2);
    setLayout(&loginLayout);

    // set up the inbox
    m_inbox = new QListWidget();
    QObject::connect(m_inbox, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(viewMessage(QListWidgetItem*)));
    m_inbox->setStyleSheet("QListWidget::item{border-bottom:1px solid black;}");

    m_viewingSent = 0;

    // test code for setting up emails
    Email* e1 = new Email();
    e1->setFrom("John");
    e1->setSubject("money");
    e1->setMessage("Yo nigga, you betta give me my money!");
    e1->setRead(false);
    e1->setText(e1->getFrom() + " | " + e1->getSubject());
    e1->setData(12, 1);
    e1->setID(1);
    Email* e2 = new Email();
    e2->setFrom("Simon");
    e2->setSubject("hangout");
    e2->setMessage("Hey man, do you want to hangout?");
    e2->setRead(false);
    e2->setText(e2->getFrom() + " | " + e2->getSubject());
    m_emails.append(e1);
    m_emails.append(e2);
    e2->setData(12, 2);
    e2->setID(2);

}

///
/// \brief Client::enableStartConnectionButton
/// enables the connect button to be pressed
void Client::enableStartConnectionButton()
{
}

///
/// \brief Client::startConnection
/// attempts to start a connection betweenthe client
/// and the server through a tcpsocket object.
void Client::startConnection()
{
    m_tcpSocket->connectToHost(m_hostEdit->text(),
                                 m_portEdit->text().toInt());
}

///
/// \brief Client::sessionOpened
/// handles an open networking session
void Client::sessionOpened()
{

}

///
/// \brief Client::registerUser
/// sends the server the new user information
void Client::registerUser()
{

}

///
/// \brief Client::login
/// sends the server the login information.
void Client::login()
{
    m_user = m_userEdit->text();
    m_password = m_passwordEdit->text();

    // send data to server for login
    loadMainUI();
}

///
/// \brief Client::loadMainUI
/// loads the main UI that displayes the inbox and message fields
void Client::loadMainUI()
{
    m_toFromLabel = new QLabel(tr("To:"));
    m_subjectLabel = new QLabel(tr("Subject:"));
    m_statusLabel = new QLabel(tr("Viewing current inbox."));

    for (int i=0; i<m_emails.length(); i++) {
        m_emails[i]->setSizeHint(QSize(50, 40));
        m_inbox->addItem(m_emails[i]);
    }

    //remove all the old widgets
    m_hostLabel->setVisible(false);
    m_hostEdit->setEnabled(false);
    m_hostEdit->setVisible(false);
    m_portLabel->setVisible(false);
    m_portEdit->setEnabled(false);
    m_portEdit->setVisible(false);
    m_userLabel->setVisible(false);
    m_userEdit->setEnabled(false);
    m_userEdit->setVisible(false);
    m_passwordLabel->setVisible(false);
    m_passwordEdit->setVisible(false);
    m_passwordEdit->setEnabled(false);
    m_loginStatusLabel->setVisible(false);
    buttonBox->setVisible(false);
    m_registerBtn->setEnabled(false);
    m_registerBtn->setVisible(false);
    m_loginBtn->setEnabled(false);
    m_loginBtn->setVisible(false);
    m_connectBtn->setEnabled(false);
    m_connectBtn->setVisible(false);
    loginLayout.removeWidget(m_hostLabel);
    loginLayout.removeWidget(m_hostEdit);
    loginLayout.removeWidget(m_portLabel);
    loginLayout.removeWidget(m_portEdit);
    loginLayout.removeWidget(m_userLabel);
    loginLayout.removeWidget(m_userEdit);
    loginLayout.removeWidget(m_passwordLabel);
    loginLayout.removeWidget(m_passwordEdit);
    loginLayout.removeWidget(m_loginStatusLabel);
    loginLayout.removeWidget(buttonBox);

    //create and add the new stuff
    m_toFromLabel = new QLabel(tr("To:"));
    m_subjectLabel = new QLabel(tr("Subject:"));
    m_bodyLabel = new QLabel(tr("Body:"));
    m_toFromEdit = new QLineEdit();
    m_subjectEdit = new QLineEdit();
    m_bodyEdit = new QTextEdit();

    m_new = new QPushButton(tr("New"));
    m_delete = new QPushButton(tr("Delete"));
    m_viewSent = new QPushButton(tr("Sent"));
    m_send = new QPushButton(tr("Send"));
    m_reply = new QPushButton(tr("reply"));

    belowButtonBox = new QDialogButtonBox;
    belowButtonBox->addButton(m_reply, QDialogButtonBox::ActionRole);
    belowButtonBox->addButton(m_send, QDialogButtonBox::ActionRole);

    aboveButtonBox = new QDialogButtonBox;
    aboveButtonBox->addButton(m_new, QDialogButtonBox::ActionRole);
    aboveButtonBox->addButton(m_delete, QDialogButtonBox::ActionRole);
    aboveButtonBox->addButton(m_viewSent, QDialogButtonBox::ActionRole);

    connect(m_new, SIGNAL(clicked()), this, SLOT(newMessage()));
    connect(m_delete, SIGNAL(clicked()), this, SLOT(deleteMessage()));
    connect(m_viewSent, SIGNAL(clicked()), this, SLOT(viewSentMessages()));
    connect(m_reply, SIGNAL(clicked()), this, SLOT(reply()));

    loginLayout.addWidget(m_inbox, 0, 0, 8, 1);
    loginLayout.addWidget(aboveButtonBox, 0, 1, 1, 4);
    loginLayout.addWidget(m_toFromLabel, 1, 1);
    loginLayout.addWidget(m_toFromEdit, 2, 1);
    loginLayout.addWidget(m_subjectLabel, 3, 1);
    loginLayout.addWidget(m_subjectEdit, 4, 1);
    loginLayout.addWidget(m_bodyLabel, 5, 1);
    loginLayout.addWidget(m_bodyEdit, 6, 1);
    loginLayout.addWidget(belowButtonBox, 7, 1, 1, 2);


    setLayout(&loginLayout);

}

///
/// \brief Client::viewMessage
/// loads message data into the message viewing objects
void Client::viewMessage(QListWidgetItem* item)
{
    m_toFromLabel->setText("From:");
    m_delete->setEnabled(true);
    m_selectedEmailID = item->data(12).toInt();
    for (int i=0; i<m_emails.length(); i++) {
        if (m_emails[i]->getID() == m_selectedEmailID) {
            m_toFromEdit->setText(m_emails[i]->getFrom());
            m_subjectEdit->setText(m_emails[i]->getSubject());
            m_bodyEdit->setText(m_emails[i]->getMessage());
        }
    }
    m_toFromEdit->setReadOnly(true);
    m_subjectEdit->setReadOnly(true);
    m_bodyEdit->setReadOnly(true);
    m_send->setEnabled(false);
    m_reply->setEnabled(true);
}

///
/// \brief Client::newMessage
/// clears all message viewing objects and allows the
/// user to fill in all the fields and enables send button
void Client::newMessage()
{
    m_toFromLabel->setText("To:");
    m_delete->setEnabled(false);
    m_toFromEdit->setText("");
    m_toFromEdit->setReadOnly(false);
    m_subjectEdit->setText("");
    m_subjectEdit->setReadOnly(false);
    m_bodyEdit->setText("");
    m_bodyEdit->setReadOnly(false);
    m_reply->setEnabled(false);
    m_send->setEnabled(true);
}

///
/// \brief Client::deleteMessage
/// removes the message from the inbox and
/// tells the server to remove from database
void Client::deleteMessage()
{
    int removeIndex;
    for (int i=0; i<m_emails.length(); i++) {
        if (m_emails[i]->getID() == m_selectedEmailID) {
            m_inbox->removeItemWidget(m_emails[i]);
            delete m_emails[i];
            removeIndex = i;
        }
    }
    m_emails.removeAt(removeIndex);

    refreshInbox("inbox");

    //send to server to delete email by id
}

///
/// \brief Client::viewSentMessages
/// changes the inbox to show sent messages
void Client::viewSentMessages()
{

}

///
/// \brief Client::sendMessage
/// sends the message to the server to be stored
void Client::sendMessage()
{
    refreshInbox("inbox");
    // push message to socket
}

///
/// \brief Client::reply
/// clear all message viewing fields, allowing the
/// user to edit and send a new message
void Client::reply()
{
    m_toFromLabel->setText("To:");
    m_delete->setEnabled(false);
    m_toFromEdit->setReadOnly(false);
    m_subjectEdit->setText("");
    m_subjectEdit->setReadOnly(false);
    m_bodyEdit->setText("");
    m_bodyEdit->setReadOnly(false);
    m_reply->setEnabled(false);
    m_send->setEnabled(true);

}

///
/// \brief Client::refreshInbox
/// refreshes the inbox
void Client::refreshInbox(QString wanted)
{
    for (int i=0; i<m_emails.length(); i++) {
        m_inbox->removeItemWidget(m_emails[i]);
    }
    for (int i=0; i<m_sentMail.length(); i++) {
        m_inbox->removeItemWidget(m_sentMail[i]);
    }
    if (wanted == "sent") {
        for (int j=0; j<m_sentMail.length(); j++) {
            m_sentMail[j]->setSizeHint(QSize(50, 40));
            m_inbox->addItem(m_sentMail[j]);
        }
    }
    else {
        for (int j=0; j<m_emails.length(); j++) {
            m_emails[j]->setSizeHint(QSize(50, 40));
            m_inbox->addItem(m_emails[j]);
        }
    }
}

///
/// \brief Client::displayError
/// \param socketError
/// displays any error given by the tcpsocket
void Client::displayError(QAbstractSocket::SocketError socketError)
{

}

///
/// \brief Client::readServerResponse
/// reads the data the server has pushed to hte tcpsocket
void Client::readServerResponse()
{
    // if server says login successfull, load new UI
    QDataStream in(m_tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);
    if (m_blockSize == 0) {
        if (m_tcpSocket->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> m_blockSize;
    }
    if (m_tcpSocket->bytesAvailable() < m_blockSize)
        return;
    QString servResponse;
    in >> servResponse;
    qDebug() << "server says: " + servResponse;

}

///
/// \brief Client::handleServerResponse
/// \param servResponse
/// performs action based on servResponse
void Client::handleServerResponse(QString servResponse)
{

}

///
/// \brief Client::sendToServer
/// \param command
/// sends 'command' to the server
void Client::sendToServer(QString command)
{

}

