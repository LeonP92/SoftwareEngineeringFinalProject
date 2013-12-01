#include "server.h"
#include <QtGui>
#include <QtNetwork>

///
/// \brief Server::Server
/// \param parent
///
/// The constructor for the server class will set up its widgets, buttons, and labels.
/// It will also make the initial connections for buttons and labels, as well as set up
/// network settings and configurations.
Server::Server(QWidget *parent) : QDialog(parent), m_tcpServer(0), m_networkSession(0),
    m_nextClientNumber(0)
{
    // Create a database
    m_databaseHelper = new DatabaseHelper;
    m_databaseHelper->init();

    // Load the QMaps from the database
    m_mapOfUsers = m_databaseHelper->serverStartUpUserLoad();
    m_mapOfMailMessages = m_databaseHelper->serverStartUpMailLoad();

    // Sets up GUI
    m_serverStatusLabel = new QLabel;
    m_quitButton = new QPushButton(tr("Quit"));
    m_quitButton->setDefault(false);

    // Sets up network settings
    QNetworkConfigurationManager networkManager;
    if ( networkManager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired ){
        // Get saved network configurations
        QSettings networkSettings(QSettings::UserScope, QLatin1String("Trolltech"));
        networkSettings.beginGroup(QLatin1String("QtNetwork"));
        const QString id =
                networkSettings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        networkSettings.endGroup();

        // If saved network configuration is not currently discovered use for the system default
        QNetworkConfiguration networkConfiguration =
                networkManager.configurationFromIdentifier(id);
        if ((networkConfiguration.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered)
            networkConfiguration = networkManager.defaultConfiguration();

        m_networkSession = new QNetworkSession(networkConfiguration, this);
        connect(m_networkSession, SIGNAL(opened()), this, SLOT(sessionOpen()));

        m_serverStatusLabel->setText(tr("Open Network Session"));
        m_networkSession->open();
    }else
        sessionOpened();

    connect(m_quitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(handleClientRequest()));

    // Create main layouts
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(m_quitButton);
    buttonLayout->addStretch(1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_serverStatusLabel);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Mail Server"));

}

///
/// \brief Server::sessionOpened
///
/// This function will open up the session for the server and set up network
/// settings and configuration.
void Server::sessionOpened()
{
    if (m_networkSession) {
        QNetworkConfiguration networkConfiguration = m_networkSession->configuration();
        QString id;

        if(networkConfiguration.type() == QNetworkConfiguration::UserChoice)
            id = m_networkSession->sessionProperty(
                        QLatin1String("UserChoiceConfiguration")).toString();
        else
            id = networkConfiguration.identifier();

        QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
        settings.endGroup();
    }

    m_tcpServer = new QTcpServer(this);
    if(!m_tcpServer->listen()){
        QMessageBox::critical(this, tr("Mail Server"),
                              tr("Unable to start the server: %1.")
                              .arg(m_tcpServer->errorString()));
        close();
        return;
    }

    // Find out which IP address to connect to
    QString ipAddress;
    QList<QHostAddress> listOfIPAddress = QNetworkInterface::allAddresses();
    // Use first non-localhost IP Address
    for (int i = 0; i <listOfIPAddress.size(); ++i){
        if(listOfIPAddress.at(i) != QHostAddress::LocalHost &&
                listOfIPAddress.at(i).toIPv4Address()){
            ipAddress = listOfIPAddress.at(i).toString();
            break;
        }
    }

    // If none were found use the localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    m_serverStatusLabel->setText(tr("The server is running on \n\nIP: %1\nport: %2\n\n"
                                    "Run the Mail Client now.")
            .arg(ipAddress).arg(m_tcpServer->serverPort()));

}

///
/// \brief Server::handleClientRequest
///
/// Creates new connection from client request and connects the socket to necessary
/// slots as well as creating a new thread.
void Server::handleClientRequest()
{
    // Create a new client handler to move it to new thread
    clientHandlerPointer newClientHandler = new ClientHandler(m_tcpServer, m_nextClientNumber);

    // Moving to a new thread
    QThread *newThread = new QThread;
    newClientHandler->moveToThread(newThread);
    QObject::connect(newClientHandler, SIGNAL(destroyed()), newThread, SLOT(quit()));
    QObject::connect(newClientHandler, SIGNAL(endClientConnection(int)), this, SLOT(cleanUp(int)));

    // Set up connection between server and client handler
    QObject::connect(newClientHandler, SIGNAL(newUserCreated(int, QString, QString)),
                     this, SLOT(newUserRegistration(int, QString, QString)));
    QObject::connect(newClientHandler, SIGNAL(userLoginAttempt(int, QString, QString)),
                     this, SLOT(validateUserAccount(int, QString, QString)));
    QObject::connect(newClientHandler, SIGNAL(mailSentCommand(int, QString, QString, QString, QString)),
                     this, SLOT(sendEmail(int, QString, QString, QString, QString)));
    QObject::connect(newClientHandler, SIGNAL(deleteEmailCommand(int, int)),
                     this, SLOT(deleteEmail(int, int)));
    QObject::connect(newClientHandler, SIGNAL(userInboxRequest(int, QString)),
                     this, SLOT(getUserInbox(int, QString)));
    QObject::connect(newClientHandler, SIGNAL(userSentMailRequest(int, QString)),
                     this, SLOT(getUserSentMail(int, QString)));
    QObject::connect(this, SIGNAL(serverResponse(int, QString)),
                     newClientHandler, SLOT(sendDataToClient(int, QString)));

    newThread->start();

    // Adds to maps and increment client number (the client number is used for clean up)
    m_mapOfClientConnections.insert(m_nextClientNumber, newClientHandler);
    m_mapOfThreads.insert(m_nextClientNumber, newThread);
    m_nextClientNumber += 1;
}

///
/// \brief Server::cleanUp
/// \param clientNumber
///
/// When a client is disconnected this slot will be called upon to clean up
/// resources used by the client.
void Server::cleanUp(int clientNumber)
{
    qDebug() << "A connection and thread with the client number, " +
                QString("%1").arg(clientNumber) + ", has been deleted.";

    m_mapOfClientConnections.take(clientNumber);
    m_mapOfThreads.take(clientNumber);

}

///
/// \brief Server::newUserRegistration
/// \param userName
/// \param password
///
/// Will create a new user and send the necessary commands to the data base
/// in order to add the user to the table.
void Server::newUserRegistration(int clientNumber, QString userName, QString password)
{
    QString serverReply;

    if (!m_mapOfUsers.contains(userName.toUpper())){
        QString information = userName + " {:} " + password;
        if (m_databaseHelper->insertIntoTable("user", information)){
            qDebug() << "Inserting new user was a success!";

            m_mapOfUsers.insert(userName.toUpper(), password);
            serverReply = QString::number(clientNumber) +
                    " {:} SUCCESS {:} New user, " + userName + ", was created sucessfully!";
        }else{
            qDebug() << "Error inserting the new user!";

            serverReply = QString::number(clientNumber) +
                    " {:} ERROR {:} New user, " + userName + ", was failed to be created!";
        }
    }else{
        serverReply = QString::number(clientNumber) +
                " {:} ERROR {:} The username " + userName + " already exists.";
    }

    emit serverResponse(serverReply);
}

///
/// \brief Server::validateUserAccount
/// \param userName
/// \param password
///
/// Validates user credentials and sends a success or failure message to
/// the client handler.
void Server::validateUserAccount(int clientNumber, QString userName, QString password)
{
    QString serverReply;
    if ( m_mapOfUsers.contains(userName.toUpper()) ){
        if (m_mapOfUsers[userName.toUpper()] == password){
            qDebug() << "User authentication is successful!";
            serverReply = QString::number(clientNumber) +
                    " {:} SUCCESS {:} Success! Welcome back " + userName + "!";
        }else{
            qDebug() << QString::number(clientNumber) +
                        " {:} ERROR {:} The username and password combination was incorrect!";
        }
    }else{
        serverReply = QString::number(clientNumber) + " {:} ERROR {:} Invalid username.";
    }

    emit serverResponse(serverReply);
}

///
/// \brief Server::sendEmail
/// \param fromUser
/// \param toUser
/// \param subject
/// \param message
///
/// Will create a new mail message object to be added to the user
/// as well as getting the database to insert the new email.
void Server::sendEmail(int clientNumber, QString fromUser, QString toUser,
                       QString subject, QString message)
{
    QString serverReply;
    QString insertInformation = fromUser + " {:} " + toUser + " {:} " +
                                subject + " {:} " + message;
    if (m_databaseHelper->insertIntoTable("mail", insertInformation)){
        serverReply = QString::number(clientNumber) + " {:} SUCCESS {:} The mail sent to "
                + toUser + " was successfully sent!";
        qDebug() << "Success: Inserting mail into the database was successful! ";

        // Need to get the new mail's id and add it to the map of mail
        int newMailId = m_databaseHelper->getMailId(fromUser, toUser, subject, message);
        MailMessage *newMailMessage = new MailMessage(newMailId, fromUser, toUser, subject,
                                                      message, false);
        m_mapOfMailMessages.insert(newMailId, newMailMessage);

    }else{
        serverReply = QString::number(clientNumber) + " {:} ERROR {:} The mail sent to "
                + toUser + " could not be sent due to an error!";
        qDebug() << "ERROR: Inserting the mail into the database was unsuccessful.";
    }

    emit serverResponse(serverReply);
}

///
/// \brief Server::deleteEmail
/// \param id
///
/// Deletes email from the local collection as well as the handle database
/// updates.
void Server::deleteEmail(int clientNumber, int id)
{
    QString serverReply;

    if (m_databaseHelper->deleteFromTable(id)){
        MailMessage *emailToDelete = m_mapOfMailMessages.take(id);
        qDebug() << "Email with the subject: " + emailToDelete->getEmailSubject();

        serverReply = QString::number(clientNumber) +
                " {:} SUCCESS {:} Email Successfully deleted!";
    }else{
        qDebug() << "Unexpected Error: Email couldn't be deleted.";

        serverReply = QString::number(clientNumber) +
                " {:} ERROR {:} Email could not be deleted!";
    }

    emit serverResponse(serverReply);
}

///
/// \brief Server::getUserInbox
/// \param userName
///
/// Upon client request the server will send the collection of user
/// inbox email. Should only be called once per user.
void Server::getUserInbox(int clientNumber, QString userName)
{
    // Don't need to send to user it should be whoever is requesting it
    foreach (MailMessage* mail, m_mapOfMailMessages){
        if (mail->getToUser().toUpper() == userName.toUpper()){
            QString serverReply = QString::number(clientNumber) + "{:} INBOX {:} " +
                    QString::number(mail->getMailId()) +
                    " {:} " + mail->getEmailSubject() + " {:} " + mail->getFromUser() +
                    " {:} " + mail->getMailMessage();
            emit serverResponse(serverReply);
        }
    }
}

///
/// \brief Server::getUserSentMail
/// \param userName
///
/// Upon request the user, the server will send the user's sent emails.
/// Should only need to be sent once per client.
void Server::getUserSentMail(int clientNumber, QString userName)
{
    // Don't need to send from user, it'll be whoever is requesting it
    foreach (MailMessage* mail, m_mapOfMailMessages){
        if (mail->getFromUser().toUpper() == userName.toUpper()){
            QString serverReply = QString::number(clientNumber) + "{:} SENT {:} " +
                    QString::number(mail->getMailId()) +
                    " {:} " + mail->getEmailSubject() + " {:} " + mail->getToUser() +
                    " {:} " + mail->getMailMessage();
            emit serverResponse(serverReply);
        }
    }
}

///
/// \brief Server::~Server
///
/// The destructor for the server. Will clean up any lose connections and clean up pointers.
Server::~Server()
{

}
