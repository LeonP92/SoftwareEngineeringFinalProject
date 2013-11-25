
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

