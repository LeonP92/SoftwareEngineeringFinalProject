#ifndef MAILMESSAGE_H
#define MAILMESSAGE_H
#include <QString>
#include <QObject>

class MailMessage : public QObject
{
    Q_OBJECT
public:
    MailMessage(int id, QString fromUser, QString toUser, QString subject,
                QString message, bool hasBeenRead);
    ~MailMessage();

    QString getEmailSubject() const;
    QString getFromUser() const;
    QString getToUser() const;
    QString getMailMessage() const;
    int getMailId() const;
    bool getMailRead() const;
    void mailRead();

signals:
    void mailRead(int mailID);

private:
    int m_id;
    QString m_fromUser;
    QString m_toUser;
    QString m_subject;
    QString m_message;
    bool m_hasBeenRead;
};


#endif // MAILMESSAGE_H
