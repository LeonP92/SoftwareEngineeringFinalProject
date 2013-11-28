 #ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMap>
#include <QTableView>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include "mailmessage.h"

class DatabaseHelper : public QObject
{
    Q_OBJECT
public:
    DatabaseHelper();
    void init();
    ~DatabaseHelper();

public:
    void serverStartupLoad(QMap<int, QString> userMap,
                           QMap<int, MailMessage *> mailMap);
    bool deleteFromTable(int messageID);
    bool insertIntoTable(QString tableName, QString insertInfo);

protected:
    bool getInitialized();

private:
    QSqlDatabase m_database;
    bool m_isInitialized;
};


#endif // DATABASEHELPER_H
