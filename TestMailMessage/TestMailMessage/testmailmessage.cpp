#include "mailmessage.h"

#include <QtTest/QTest>
#include <QDebug>
#include <QFile>
#include <iostream>

class TestMailMessage:public QObject
{
    Q_OBJECT

private slots:
    void testGetMailId_data();
    void testGetMailId();

    void testGetSubject_data();
    void testGetSubject();

    void testGetFromUser_data();
    void testGetFromUser();

    void testGetToUser_data();
    void testGetToUser();

    void testGetMailMessage_data();
    void testGetMailMessage();

    void testGetMailRead_data();
    void testGetMailRead();

    void testMailRead_data();
    void testMailRead();
};

void TestMailMessage::testGetMailId_data()
{
    QTest::addColumn<int>("ID");
    QTest::addColumn<int>("IDOutput");

    // Reads in the csv
    QFile testFile("testdata.csv");
    if(testFile.open(QIODevice::ReadOnly)){
        QString fileData = testFile.readAll();
        fileData = fileData.replace(QRegExp("\n"), ",");
        QStringList data = fileData.split(",");
        data.replaceInStrings("\"", "");
        testFile.close();
        QString testName, description, parameter1, output;
        int id, idOutput;

        while (data.size() != 0 && data[0] != ""){
            testName = data[0];
            data.removeFirst();
            if ( testName == "testGetMailId" ){
                description = data[0];
                data.removeFirst();
                parameter1 = data[0];
                data.removeFirst();
                output = data[0];
                data.removeFirst();

                id = parameter1.toInt();
                MailMessage *message = new MailMessage(id, "", "", "", "", false);
                idOutput = message->getMailId();

                QTest::newRow(description.toStdString().c_str()) << idOutput << output.toInt();
            }else{
                for (int i = 0; i < 3; i++)
                    data.removeFirst();
            }
        }
    }

}

void TestMailMessage::testGetMailId()
{
    QFETCH(int, ID);
    QFETCH(int, IDOutput);

    QVERIFY(ID == IDOutput);
}

void TestMailMessage::testGetSubject_data()
{
    QTest::addColumn<QString>("subject");
    QTest::addColumn<QString>("mailSubject");

    // Reads in the csv
    QFile testFile("testdata.csv");
    if(testFile.open(QIODevice::ReadOnly)){
        QString fileData = testFile.readAll();
        fileData = fileData.replace(QRegExp("\n"), ",");
        QStringList data = fileData.split(",");
        data.replaceInStrings("\"", "");
        testFile.close();
        QString testName, description, parameter1, subject, output;

        while (data.size() != 0 && data[0] != ""){
            testName = data[0];
            data.removeFirst();
            if ( testName == "testGetSubject" ){
                description = data[0];
                data.removeFirst();
                parameter1 = data[0];
                data.removeFirst();
                output = data[0];
                data.removeFirst();

                MailMessage *message = new MailMessage(0, "", "", parameter1, "", false);
                subject = message->getEmailSubject();

                QTest::newRow(description.toStdString().c_str()) << subject << output;
            }else{
                for (int i = 0; i < 3; i++)
                    data.removeFirst();
            }
        }
    }

}

void TestMailMessage::testGetSubject()
{
    QFETCH(QString, subject);
    QFETCH(QString, mailSubject);

    QVERIFY(mailSubject == subject);
}

void TestMailMessage::testGetFromUser_data()
{
    QTest::addColumn<QString>("fromUser");
    QTest::addColumn<QString>("fromUserOutput");

    // Reads in the csv
    QFile testFile("testdata.csv");
    if(testFile.open(QIODevice::ReadOnly)){
        QString fileData = testFile.readAll();
        fileData = fileData.replace(QRegExp("\n"), ",");
        QStringList data = fileData.split(",");
        data.replaceInStrings("\"", "");
        testFile.close();
        QString testName, description, parameter1, fromUser, output;

        while (data.size() != 0 && data[0] != ""){
            testName = data[0];
            data.removeFirst();
            if ( testName == "testGetFromUser" ){
                description = data[0];
                data.removeFirst();
                parameter1 = data[0];
                data.removeFirst();
                output = data[0];
                data.removeFirst();

                MailMessage *message = new MailMessage(0, parameter1, "", "", "", false);
                fromUser = message->getFromUser();

                QTest::newRow(description.toStdString().c_str()) << fromUser << output;
            }else{
                for (int i = 0; i < 3; i++)
                    data.removeFirst();
            }
        }
    }

}

void TestMailMessage::testGetFromUser()
{
    QFETCH(QString, fromUser);
    QFETCH(QString, fromUserOutput);

    QVERIFY(fromUser == fromUserOutput);
}

void TestMailMessage::testGetToUser_data()
{
    QTest::addColumn<QString>("toUser");
    QTest::addColumn<QString>("toUserOutput");

    // Reads in the csv
    QFile testFile("testdata.csv");
    if(testFile.open(QIODevice::ReadOnly)){
        QString fileData = testFile.readAll();
        fileData = fileData.replace(QRegExp("\n"), ",");
        QStringList data = fileData.split(",");
        data.replaceInStrings("\"", "");
        testFile.close();
        QString testName, description, parameter1, fromUser, output;

        while (data.size() != 0 && data[0] != ""){
            testName = data[0];
            data.removeFirst();
            if ( testName == "testGetToUser" ){
                description = data[0];
                data.removeFirst();
                parameter1 = data[0];
                data.removeFirst();
                output = data[0];
                data.removeFirst();

                MailMessage *message = new MailMessage(0, "", parameter1, "", "", false);
                fromUser = message->getToUser();

                QTest::newRow(description.toStdString().c_str()) << fromUser << output;
            }else{
                for (int i = 0; i < 3; i++)
                    data.removeFirst();
            }
        }
    }

}

void TestMailMessage::testGetToUser()
{
    QFETCH(QString, toUser);
    QFETCH(QString, toUserOutput);

    QVERIFY(toUser == toUserOutput);
}

void TestMailMessage::testGetMailMessage_data()
{
    QTest::addColumn<QString>("message");
    QTest::addColumn<QString>("messageOutput");

    // Reads in the csv
    QFile testFile("testdata.csv");
    if(testFile.open(QIODevice::ReadOnly)){
        QString fileData = testFile.readAll();
        fileData = fileData.replace(QRegExp("\n"), ",");
        QStringList data = fileData.split(",");
        data.replaceInStrings("\"", "");
        testFile.close();
        QString testName, description, parameter1, fromUser, output;

        while (data.size() != 0 && data[0] != ""){
            testName = data[0];
            data.removeFirst();
            if ( testName == "testGetMailMessage" ){
                description = data[0];
                data.removeFirst();
                parameter1 = data[0];
                data.removeFirst();
                output = data[0];
                data.removeFirst();

                MailMessage *message = new MailMessage(0, "", "", "", parameter1, false);
                fromUser = message->getMailMessage();

                QTest::newRow(description.toStdString().c_str()) << fromUser << output;
            }else{
                for (int i = 0; i < 3; i++)
                    data.removeFirst();
            }
        }
    }

}

void TestMailMessage::testGetMailMessage()
{
    QFETCH(QString, message);
    QFETCH(QString, messageOutput);

    QVERIFY(message == messageOutput);
}

void TestMailMessage::testGetMailRead_data()
{
    QTest::addColumn<bool>("read");
    QTest::addColumn<bool>("readOutput");

    // Reads in the csv
    QFile testFile("testdata.csv");
    if(testFile.open(QIODevice::ReadOnly)){
        QString fileData = testFile.readAll();
        fileData = fileData.replace(QRegExp("\n"), ",");
        QStringList data = fileData.split(",");
        data.replaceInStrings("\"", "");
        testFile.close();
        QString testName, description, parameter1, output;
        bool read, readOutput;

        while (data.size() != 0 && data[0] != ""){
            testName = data[0];
            data.removeFirst();
            if ( testName == "testGetMailRead" ){
                description = data[0];
                data.removeFirst();
                parameter1 = data[0];
                data.removeFirst();
                output = data[0];
                data.removeFirst();

                if (parameter1 == "TRUE")
                    read = true;
                else
                    read = false;

                if (output == "TRUE")
                    read = true;
                else
                    read = false;

                MailMessage *message = new MailMessage(0, "", "", "", "", read);
                readOutput = message->getMailRead();

                QTest::newRow(description.toStdString().c_str()) << read << readOutput;
            }else{
                for (int i = 0; i < 3; i++)
                    data.removeFirst();
            }
        }
    }

}

void TestMailMessage::testGetMailRead()
{
    QFETCH(bool, read);
    QFETCH(bool, readOutput);

    QVERIFY(read == readOutput);
}

void TestMailMessage::testMailRead_data()
{
    QTest::addColumn<bool>("read");
    QTest::addColumn<bool>("readOutput");

    // Reads in the csv
    QFile testFile("testdata.csv");
    if(testFile.open(QIODevice::ReadOnly)){
        QString fileData = testFile.readAll();
        fileData = fileData.replace(QRegExp("\n"), ",");
        QStringList data = fileData.split(",");
        data.replaceInStrings("\"", "");
        testFile.close();
        QString testName, description, parameter1, output;
        bool read, readOutput;

        while (data.size() != 0 && data[0] != ""){
            testName = data[0];
            data.removeFirst();
            if ( testName == "testMailRead" ){
                description = data[0];
                data.removeFirst();
                parameter1 = data[0];
                data.removeFirst();
                output = data[0];
                data.removeFirst();

                if (parameter1 == "TRUE")
                    read = true;

                if (output == "TRUE")
                    read = true;

                MailMessage *message = new MailMessage(0, "", "", "", "", read);
                message->mailRead();
                readOutput = message->getMailRead();

                QTest::newRow(description.toStdString().c_str()) << read << readOutput;
            }else{
                for (int i = 0; i < 3; i++)
                    data.removeFirst();
            }
        }
    }

}

void TestMailMessage::testMailRead()
{
    QFETCH(bool, read);
    QFETCH(bool, readOutput);

    QVERIFY(read == readOutput);
}


QTEST_MAIN (TestMailMessage)
#include "testmailmessage.moc"
