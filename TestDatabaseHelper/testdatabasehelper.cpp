/*
 * Leon Pham
 * December 2, 2013
 * Database Helper Test Class
 *
 */

#include "databasehelper.h"
#include <QtTest/QTest>
#include <QtGui>
#include <QTestEventList>
#include <QDebug>
#include <iostream>

class TestDatabaseHelper:public QObject
{
    Q_OBJECT

private slots:
    void testInit_data();
    void testInit();
    void testInsertUserIntoTable();
    void testInsertMailIntoTable();
    void testDeleteFromTable();
};

///
/// \brief TestDatabaseHelper::testInit_data
///
/// Tests the database init to make sure that it sucessfully opened the database
void TestDatabaseHelper::testInit_data()
{
    QTest::addColumn<bool>("hasDatabase");
    QTest::addColumn<bool>("databaseStatus");

    DatabaseHelper *database = new DatabaseHelper;
    database->init();

    bool canBeOpened = database->getDatabase().isOpen();

    QTest::newRow("initialized database") << canBeOpened << true;

}

void TestDatabaseHelper::testInit()
{
    QFETCH(bool, hasDatabase);
    QFETCH(bool, databaseStatus);

    QVERIFY(hasDatabase == databaseStatus);
}

///
/// \brief TestDatabaseHelper::testInsertUserIntoTable
///
/// Tests to make sure that the database can insert users to the users table
void TestDatabaseHelper::testInsertUserIntoTable()
{
    DatabaseHelper *database = new DatabaseHelper;
    database->init();
    database->serverStartUpUserLoad();

    QString user = "RickRoll";
    QString password = "password";
    QString data = user + " {:} " + password;

    if (!database->getMapOfUserIds().contains(user.toUpper()))
        database->insertIntoTable("user", data);

    int userId = -1;
    userId = database->getUserId(user, "password");
    QVERIFY(userId != -1);

    QString user2 = "PatrickStar";
    QString password2 = "password2";
    QString data2 = user2 + " {:} " + password2;

    if (!database->getMapOfUserIds().contains(user2.toUpper()))
        database->insertIntoTable("user", data2);

    int user2Id = -1;
    user2Id = database->getUserId(user2, password2);
    QVERIFY(user2Id != -1);
}

///
/// \brief TestDatabaseHelper::testInsertMailIntoTable
///
/// Makes sure the database can insert mail into the mail table
void TestDatabaseHelper::testInsertMailIntoTable()
{
    DatabaseHelper *database = new DatabaseHelper;
    database->init();
    database->serverStartUpUserLoad();

    QString fromUser = "RickRoll";
    QString toUser = "PatrickStar";
    QString subject = "How are you?";
    QString message = "Just wanted to check up on you.";

    QString data = fromUser.toUpper() + " {:} " + toUser.toUpper()
            + " {:} " + subject + " {:} " + message;

    database->insertIntoTable("mail", data);

    int mailId = -1;
    mailId = database->getMailId(fromUser, toUser, subject, message);

    QVERIFY(mailId != -1);
}

///
/// \brief TestDatabaseHelper::testDeleteFromTable
///
/// Makes sure the database can delete from the mail table, users table
/// will never be deleted
void TestDatabaseHelper::testDeleteFromTable()
{
    DatabaseHelper *database = new DatabaseHelper;
    database->init();
    database->serverStartUpUserLoad();

    QString fromUser = "RickRoll";
    QString toUser = "PatrickStar";
    QString subject = "Let's hang out on Friday";
    QString message = "Try to come to the park on Friday so we can have fun!";

    QString data = fromUser.toUpper() + " {:} " + toUser.toUpper()
            + " {:} " + subject + " {:} " + message;

    database->insertIntoTable("mail", data);

    int mailId = -1;
    mailId = database->getMailId(fromUser, toUser, subject, message);

    QVERIFY(database->deleteFromTable(mailId) == true);
}

QTEST_MAIN (TestDatabaseHelper)
#include "testdatabasehelper.moc"

