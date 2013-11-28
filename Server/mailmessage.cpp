#include "mailmessage.h"

///
/// \brief MailMessage::MailMessage
/// \param id
/// \param fromUser
/// \param toUser
/// \param subject
/// \param message
/// \param hasBeenRead
///
/// Instantiates the message and sets the member variable appropariately.
/// This class will be mainly used in order to create a collection of
/// messages so the database does not need to be accessed everytime a client
/// requests a mail.
MailMessage::MailMessage(int id, QString fromUser,
                         QString toUser, QString subject,
                         QString message, bool hasBeenRead)
{
    m_id = id;
    m_fromUser = fromUser;
    m_toUser = toUser;
    m_subject = subject;
    m_message = message;
    m_hasBeenRead = hasBeenRead;
}

///
/// \brief MailMessage::getFromUser
/// \param userName
///
/// Will check if the parameter passed in matches the from user
QString MailMessage::getFromUser() const
{
   return m_fromUser;
}

///
/// \brief MailMessage::getToUser
/// \param userName
///
/// Will check if the parameter passed in matches the to user
QString MailMessage::getToUser() const
{
    return m_toUser;
}

///
/// \brief MailMessage::getMailMessage
/// \return
///
QString MailMessage::getMailMessage() const
{
    return m_message;
}

///
/// \brief MailMessage::getUserSubject
/// \return
///
QString MailMessage::getEmailSubject() const
{
    return m_subject;
}

///
/// \brief MailMessage::getMailId
/// \return
///
int MailMessage::getMailId() const
{
    return m_id;
}

///
/// \brief MailMessage::getMailRead
/// \return
///
bool MailMessage::getMailRead() const
{
    return m_hasBeenRead;
}

///
/// \brief MailMessage::mailRead
///
/// Sets the has read flag of the mail to true.
void MailMessage::mailRead()
{
    m_hasBeenRead = true;
    emit mailRead(m_id);
}

///
/// \brief MailMessage::~MailMessage
///
/// Destructor for the mail message
MailMessage::~MailMessage()
{

}


