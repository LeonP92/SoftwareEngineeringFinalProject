
#include <QtGui>
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
    m_loginBtn->setEnabled(false);
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
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(m_hostLabel, 0, 0);
    mainLayout->addWidget(m_hostEdit, 0, 1);
    mainLayout->addWidget(m_portLabel, 1, 0);
    mainLayout->addWidget(m_portEdit, 1, 1);
    mainLayout->addWidget(m_userLabel, 2, 0);
    mainLayout->addWidget(m_userEdit, 2, 1);
    mainLayout->addWidget(m_passwordLabel, 3, 0);
    mainLayout->addWidget(m_passwordEdit, 3, 1);
    mainLayout->addWidget(m_loginStatusLabel, 4, 0, 1, 2);
    mainLayout->addWidget(buttonBox, 5, 0, 1, 2);
    setLayout(mainLayout);
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
/// If valid, loads the inbox screen.
void Client::login()
{

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

}

