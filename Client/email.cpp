
#include "email.h"

///
/// \brief Email::Email
/// \param parent
/// constuctor for email object
Email::Email(QWidget *parent)
{

}

///
/// \brief Email::~Email
/// destructor for email object
Email::~Email()
{

}

///
/// \brief Email::setTo
/// \param to
/// sets the m_to member variable
void Email::setTo(QString to)
{
    m_to = to;
}

///
/// \brief Email::setFrom
/// \param from
/// set m_from
void Email::setFrom(QString from)
{
    m_from = from;
}

///
/// \brief Email::setSubject
/// \param subject
/// set m_subject
void Email::setSubject(QString subject)
{
    m_subject = subject;
}

///
/// \brief Email::setMessage
/// \param message
/// set m_subject
void Email::setMessage(QString message)
{
    m_message = message;
}

///
/// \brief Email::setRead
/// \param read
/// set m_read
void Email::setRead(bool read)
{
    m_read = read;
}

///
/// \brief Email::setID
/// \param id
/// set m_id
void Email::setID(int id)
{
    m_id = id;
}

///
/// \brief Email::getSubject
/// \return
/// returns m_subject
QString Email::getSubject()
{
    return m_subject;
}

///
/// \brief Email::getTo
/// \return
/// return m_to
QString Email::getTo()
{
    return m_to;
}

///
/// \brief Email::getFrom
/// \return
/// return m_from
QString Email::getFrom()
{
    return m_from;
}

///
/// \brief Email::getMessage
/// \return
/// return m_message
QString Email::getMessage()
{
    return m_message;
}
