#include "clienthandler.h"

///
/// \brief ClientHandler::ClientHandler
/// \param server
/// \param clientNumber
///
/// This constructor will set up the client connection and set up appropriate
/// connections that allows data to be received and sent.
ClientHandler::ClientHandler(QTcpServer *server, int clientNumber)
{
    m_clientNumber = clientNumber;

    m_clientConnection = server->nextPendingConnection();

    // Sets up necessary connections
    QObject::connect(m_clientConnection, SIGNAL(disconnected()), m_clientConnection, SLOT(deleteLater()));
    QObject::connect(m_clientConnection, SIGNAL(disconnected()), this, SLOT(deleteLater()));
    QObject::connect(m_clientConnection, SIGNAL(readyRead()), this, SLOT(readClientData()));

    // Sends welcome message to clients
    QString welcome = "Connection to the mail server is successful!";
    m_blockSize = 0;

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << welcome;
    out.device()->seek(0);
    out << (quint16)(block.size()-sizeof(quint16));
    m_clientConnection->write(block);
}

///
/// \brief ClientHandler::readClientData
///
/// Reads data from the client and call on analyze command to take care
/// of the rest.
void ClientHandler::readClientData()
{
    // Reads data sent from the client
    bool isSending = false;

    QDataStream inData(m_clientConnection);
    inData.setVersion(QDataStream::Qt_4_0);

    if (m_blockSize == 0 ){
        // If there is no data, don't do do anything
        if ( m_clientConnection->bytesAvailable() < (int)sizeof(quint16))
            isSending = false;
        else
            isSending = true;
        inData >> m_blockSize;

    }

    // Once again if there are no data, don't do anything
    if (m_clientConnection->bytesAvailable() < m_blockSize)
        isSending = false;
    else
        isSending = true;

    // It will only get to this part if the socket has data to be read
    if ( isSending == true){
        QString clientCommand;
        inData >> clientCommand;
        // Analyze Command will decipher what the command wants the server to do
        analyzeCommand(clientCommand);
    }
}

///
/// \brief ClientHandler::sendDataToClient
/// \param response
///
/// Once the server finishes compiling its response the client handler will
/// respond to its client.
void ClientHandler::sendDataToClient(QString response)
{
    QStringList responseList = response.split(" {:} ");

    // Will only send data if it is the handler that's trying to respond to its client
    if (responseList[0].toInt() == m_clientNumber){
        // Writes the server response so the client can retrieve it
        QByteArray dataBlock;
        QDataStream outputStream(&dataBlock, QIODevice::WriteOnly);
        outputStream.setVersion(QDataStream::Qt_4_0);
        outputStream << (quint16)0;
        outputStream << response;
        outputStream.device()->seek(0);
        outputStream << (quint16)(dataBlock.size() - sizeof(quint16));
        m_clientConnection->write(dataBlock);
	m_blockSize = 0;
    }
}

///
/// \brief ClientHandler::analyzeCommand
/// \param command
///
/// This will be used to analyze the data the client sent
/// and will then emit the proper signal to
/// get the server to perform the correct operations.
void ClientHandler::analyzeCommand(QString command)
{
    QStringList commandList = command.split(" {:} ");

    // Command {:} NewUserId {:} UserEncryptedPassword
    if ( commandList[0].toUpper() == "NEWUSER"){
        QString newUser = commandList[1];
        QString encryptedPassword = commandList[2];

        emit newUserCreated(m_clientNumber, newUser, encryptedPassword);

    // Command {:} UserId {:} UserEncryptedPassword
    }else if (commandList[0].toUpper() == "USERLOGIN"){
        QString userId = commandList[1];
        QString encryptedPassword = commandList[2];

        emit userLoginAttempt(m_clientNumber, userId, encryptedPassword);

    // Command {:} UserId
    }else if (commandList[0].toUpper() == "GETINBOX"){
        QString userId = commandList[1];

        emit userInboxRequest(m_clientNumber, userId);

    // Command {:} UserId
    }else if (commandList[0].toUpper() == "GETSENT"){
        QString userId = commandList[1];

        emit userSentMailRequest(m_clientNumber, userId);

    // Command {:} MailId
    }else if (commandList[0].toUpper() == "DELETEMAIL"){
        int mailId = commandList[1].toInt();

        emit deleteEmailCommand(m_clientNumber, mailId);

    // Command {:} FromUser {:} ToUser {:} Subject {:} Message
    }else if (commandList[0].toUpper() == "SENDMAIL"){
        QString fromUser = commandList[1];
        QString toUser = commandList[2];
        QString subject = commandList[3];
        QString message = commandList[4];

        emit mailSentCommand(m_clientNumber, fromUser, toUser, subject, message);

    // Should never hit this statement.
    }else {
        qDebug() << "ERROR: Unexpected error invalid command: " + commandList[0];
    }
}

///
/// \brief ClientHandler::~ClientHandler
///
/// This class' destructor will make sure the connection is closed
/// and clean up any pointer member variables.
ClientHandler::~ClientHandler()
{
    m_clientConnection->close();
    delete m_clientConnection;
    m_clientConnection = NULL;

    emit endClientConnection(m_clientNumber);
}
