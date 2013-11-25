#ifndef EMAIL_H
#define EMAIL_H

#include <QAbstractButton>

class Email : public QAbstractButton
{
    Q_OBJECT

public:
    Email(QWidget *parent = 0);
    ~Email();
    void setTo(QStirng to);
    void setFrom(QString from);
    void setSubject(QString subject);
    void setMessage(QString message);
    void setRead(bool read);
    void setID(int id);
    QString getSubject();
    QString getTo();
    QString getFrom();
    QString getMessage();


private:
    bool m_read;
    QString m_subject;
    QString m_to;
    QString m_from;
    QString m_message;
    int m_id;


};

#endif // EMAIL_H
