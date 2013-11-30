

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
    m_inbox = new QListView;


    QListWidget * listWidget = new QListWidget();
    listWidget->setStyleSheet("QListWidget::item{border-bottom:1px solid black;}");
    for (int i=0; i<10; i++) {
        Email * item = new Email();
        item->setText("Test email "+QString::number(i));
        item->setSizeHint(QSize(50, 40));
        listWidget->addItem(item);

    }
    qDebug() << "yo im heere";
    //remove all the old widgets
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

    m_view = new QPushButton(tr("View"));
    m_new = new QPushButton(tr("New"));
    m_delete = new QPushButton(tr("Delete"));
    m_viewSent = new QPushButton(tr("Sent"));
    m_send = new QPushButton(tr("Send"));
    m_reply = new QPushButton(tr("reply"));

    belowButtonBox = new QDialogButtonBox;
    belowButtonBox->addButton(m_reply, QDialogButtonBox::ActionRole);
    belowButtonBox->addButton(m_send, QDialogButtonBox::ActionRole);

    aboveButtonBox = new QDialogButtonBox;
    aboveButtonBox->addButton(m_view, QDialogButtonBox::ActionRole);
    aboveButtonBox->addButton(m_new, QDialogButtonBox::ActionRole);
    aboveButtonBox->addButton(m_delete, QDialogButtonBox::ActionRole);
    aboveButtonBox->addButton(m_viewSent, QDialogButtonBox::ActionRole);

    loginLayout.addWidget(listWidget, 0, 0, 7, 1);
    loginLayout.addWidget(aboveButtonBox, 0, 1, 1, 4);
    loginLayout.addWidget(m_toFromLabel, 1, 1);
    loginLayout.addWidget(m_toFromEdit, 2, 1);
    loginLayout.addWidget(m_subjectLabel, 3, 1);
    loginLayout.addWidget(m_subjectEdit, 4, 1);
    loginLayout.addWidget(m_bodyLabel, 5, 1);
    loginLayout.addWidget(m_bodyEdit, 6, 1);


    setLayout(&loginLayout);

}

///
/// \brief Client::viewMessage
/// loads message data into the message viewing objects
void Client::viewMessage()
{

}

///
/// \brief Client::newMessage
/// clears all message viewing objects and allows the
/// user to fill in all the fields and enables send button
void Client::newMessage()
{

}

///
/// \brief Client::deleteMessage
/// removes the message from the inbox and
/// tells the server to remove from database
void Client::deleteMessage()
{

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

}

///
/// \brief Client::reply
/// clear all message viewing fields, allowing the
/// user to edit and send a new message
void Client::reply()
{

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

}

