#include "databasehelper.h"
#include <QDebug>
#include <QSqlQuery>
#include <QMutex>

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
                              "Subject varchar(50), "
                              "Message varchar, "
                              "BeenRead BOOLEAN DEFAULT 0)"))
                qDebug() << "Mail Message table created successfully!";
            else
                qDebug() << sqlQuery.lastError();

        }
    }else{
        qDebug() << "Error opening the database. Please restart the server.";
    }

    // For safety practices.
    serverStartUpUserLoad();
}

///
/// \brief DatabaseHelper::serverStartUpUserLoad
/// \return
///
/// Loads all users. Should be used before anything
QMap<QString, QString> DatabaseHelper::serverStartUpUserLoad()
{
    Q_ASSERT(getInitialized());

    QMap<QString, QString> mapToReturn;

    QSqlQuery sqlQuery;
    QString query = "SELECT id, Username, Password FROM user";
    bool isQuerySuccess = sqlQuery.exec(query);

    while (isQuerySuccess && sqlQuery.next()){
        int userId = sqlQuery.value(0).toInt();
        QString userName = sqlQuery.value(1).toString();
        QString userPassword = sqlQuery.value(2).toString();

        m_mapOfUsers.insert(userId, userName.toUpper());
        m_mapOfUserIds.insert(userName.toUpper(), userId);
        mapToReturn.insert(userName.toUpper(), userPassword);
    }

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

    QSqlQuery sqlQuery;
    QString query = "SELECT id, FromUser, ToUser, Subject, Message, BeenRead FROM user";
    bool isQuerySuccessful = sqlQuery.exec(query) ;

    while (isQuerySuccessful && sqlQuery.next()){
        int mailId = sqlQuery.value(0).toInt();
        QString fromUser = m_mapOfUsers[sqlQuery.value(1).toInt()];
        QString toUser = m_mapOfUsers[sqlQuery.value(2).toInt()];
        QString Subject = sqlQuery.value(3).toString();
        QString Message = sqlQuery.value(4).toString();
        bool hasBeenRead = sqlQuery.value(5).toInt() == 1;

        MailMessage *loadedMail = new MailMessage(mailId, fromUser, toUser,
                                                 Subject, Message, hasBeenRead);

        mapToReturn.insert(mailId, loadedMail);
    }

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

    QMutex mutex;
    QSqlQuery sqlQuery;

    mutex.lock();
    if (sqlQuery.exec(QString("DELETE FROM mail WHERE id = %1").arg(messageID))){
        mutex.unlock();
        qDebug() << "Email deleted properly from the database.";
        return true;
    }else{
        mutex.unlock();
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

    QMutex mutex;
    QSqlQuery sqlQuery;

    if (tableName == "user"){
        QStringList information = insertInfo.split(" {:} ");
        QString userName = sqlQuery.value(0).toString();

        if (!m_mapOfUserIds.contains(userName.toUpper())){
            mutex.lock();
            if (sqlQuery.exec(QString("INSERT INTO user values(NULL, '%1', '%2')").
                              arg(information[0].toUpper()).arg(information[1]))){
                mutex.unlock();
                qDebug() << "DATABASE: Inserting user information successful.";

                // Add inserting user run query to find user's int and then put it into the map
                QSqlQuery sqlQuery;
                QString query = "SELECT id FROM user WHERE Username = '"
                        + userName.toUpper() + "'";

                if (sqlQuery.exec(query)){
                    int userId = sqlQuery.value(0).toInt();

                    m_mapOfUsers.insert(userId, userName.toUpper());
                    m_mapOfUserIds.insert(userName.toUpper(), userId);
                }

                return true;
             }else{
                mutex.unlock();
                qDebug() << "DATABASE: Failure to insert user.";
                return false;
            }
        }else{
            qDebug() << "DATABASE: User already exists";
            return false;
        }
    }else if (tableName == "mail"){
        QStringList information = insertInfo.split(" {:} ");
        int fromUserId = m_mapOfUserIds[information[0].toUpper()];
        int toUserId = m_mapOfUserIds[information[1].toUpper()];

        mutex.lock();
        if (sqlQuery.exec(QString("INSERT INTO mail values(NULL, %1, %2, "
                                  "%3, %4, 0)").arg(fromUserId).arg(toUserId).
                          arg(information[2]).arg(information[3]))){
            mutex.unlock();
            return true;
        }
        else{
            mutex.unlock();
            qDebug() << "DATABASE: Failure while inserting new mail.";
            return false;
        }
    }else
        qDebug() << "The table name, " + tableName + ", is an invalid table name.";
    return false;
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
    Q_ASSERT(getInitialized());

    QSqlQuery sqlQuery;
    int mailId = 0;

    if (sqlQuery.exec(QString("SELECT id FROM mail WHERE FromUser = '%1' AND ToUser = '%2' "
                              "AND Subject = '%3' AND Message = '%3'").arg(fromUser).
                      arg(toUser).arg(subject).arg(message))){
        sqlQuery.next();
        mailId = sqlQuery.value(0).toInt();
    }else
        qDebug() << "ERROR: Could not load mail ID. Return value is meaningless.";

    return mailId;
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
/// \brief DatabaseHelper::getDatabase
/// \return QSqlDatabase
///
/// Used in testing to make sure database is created
QSqlDatabase DatabaseHelper::getDatabase()
{
    return m_database;
}

///
/// \brief DatabaseHelper::getDatabase
/// \return QSqlDatabase
///
/// Used in testing to make sure database is created
QMap<QString, int> DatabaseHelper::getMapOfUserIds()
{
    return m_mapOfUserIds;
}

///
/// \brief DatabaseHelper::~DatabaseHelper
///
/// The destructor will close data base connections but makes sure
/// all processes are completed.
DatabaseHelper::~DatabaseHelper()
{
    m_database.close();
    m_mapOfUserIds.clear();
    m_mapOfUsers.clear();
}
