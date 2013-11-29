#include "databasehelper.h"
#include <QDebug>
#include <QSqlQuery>

///
/// \brief DatabaseHelper::DatabaseHelper
///
/// The constructor for the database helper class. This constructor
/// will simply make sure that the is initialized flag is set to false.
/// This will assure that the init must be called and that the connection
/// to the database must be made before the class is used.
DatabaseHelper::DatabaseHelper() : m_isInitialized(false)
{
    // Does nothing other than setting is initalize to false.
}

///
/// \brief DatabaseHelper::init
///
/// Will set up proper connections to the database and
/// create tables if any are missing. This function must be called
/// before any other functions are able to be used.
void DatabaseHelper::init()
{
    // Sets is initialized for the same
    m_isInitialized = true;

    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName("mailServer.sqlite");
    if ( m_database.open() ){
        qDebug() << "Database has been successfully accessed.";

        QSqlQuery sqlQuery;

        // Creation of tables for the database if it doesn't exists
        // Creates a table for user name and password
        if (m_database.tables().contains(QLatin1String("user")))
            qDebug() << "The user table already exists!";
        else{
            if (sqlQuery.exec("CREATE TABLE IF NOT EXISTS user "
                          "(id integer UNIQUE primary key, "
                          "Username varchar(20),"
                          "Password varchar(100))")){
                qDebug() << "Users table created successfully!";
            }
            else
                qDebug() << sqlQuery.lastError();
        }
        // Creates a mail message table
        // Columns include from, to, title, and message
        if (m_database.tables().contains(QLatin1String("mail")))
            qDebug() << "The mail message table already exists!";
        else{
            if (sqlQuery.exec("CREATE TABLE IF NOT EXISTS mail "
                              "(id integer UNIQUE primary key, "
                              "FromUser integer REFERENCES user(id), "
                              "ToUser integer REFERENCES user(id), "
                              "Subject varchar(20), "
                              "Message varchar, "
                              "BeenRead BOOLEAN DEFAULT 0)"))
                qDebug() << "Mail Message table created successfully!";
            else
                qDebug() << sqlQuery.lastError();

        }
    }else{
        qDebug() << "Error opening the database. Please restart the server.";
    }

}

///
/// \brief DatabaseHelper::serverStartUpUserLoad
/// \return
///
QMap<QString, QString> DatabaseHelper::serverStartUpUserLoad()
{
    Q_ASSERT(getInitialized());

    QMap<QString, QString> mapToReturn;
    return mapToReturn;
}

///
/// \brief DatabaseHelper::serverStartUpMailLoad
/// \return
///
QMap<int, MailMessage *> DatabaseHelper::serverStartUpMailLoad()
{
    Q_ASSERT(getInitialized());

    QMap<int, MailMessage *> mapToReturn;
    return mapToReturn;
}

///
/// \brief DatabaseHelper::deleteFromTable
/// \param messageID
/// \return If the operation was successful or not
///
/// Will delete a message from the database.
bool DatabaseHelper::deleteFromTable(int messageID)
{
    Q_ASSERT(getInitialized());

    QSqlQuery sqlQuery;

    if (sqlQuery.exec(QString("DELETE FROM mail WHERE id = %1").arg(messageID))){
        qDebug() << "Email deleted properly from the database.";
        return true;
    }else{
        qDebug() << sqlQuery.lastError();
        return false;
    }
}

///
/// \brief DatabaseHelper::insertIntoTable
/// \param tableName
/// \param insertInfo
/// \return If the operation was successful or not
///
/// Inserts data into a table. The table can either be the user table
/// or the messages table. Prechecks to make sure duplicates aren ot put in
/// will be done elsewhere.
bool DatabaseHelper::insertIntoTable(QString tableName, QString insertInfo)
{
    Q_ASSERT(getInitialized());

    if (tableName == "user"){

    }else if (tableName == "mail"){

    }else
        qDebug() << "The table name, " + tableName + ", is an invalid table name.";
}

///
/// \brief DatabaseHelper::getMailId
/// \param fromUser
/// \param toUser
/// \param subject
/// \param message
/// \return
///
int DatabaseHelper::getMailId(QString fromUser, QString toUser, QString subject, QString message)
{
}

///
/// \brief DatabaseHelper::getInitialized
/// \return Returns is intialized
///
/// Used to make sure that the database helper has been initialized before use
bool DatabaseHelper::getInitialized()
{
    return m_isInitialized;
}

///
/// \brief DatabaseHelper::~DatabaseHelper
///
/// The destructor will close data base connections but makes sure
/// all processes are completed.
DatabaseHelper::~DatabaseHelper()
{

}
