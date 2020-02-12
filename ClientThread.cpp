#include "ClientThread.h"
#include "ChattingClient.h"
#include "Message.h"

#include <QThread>
#include <QString>
#include <QTcpSocket>
#include <QObject>
#include <QDebug>

ClientThread::ClientThread(QString name, QString ip, QObject* parent) {
	this->parent = parent;
	this->name = name;
	this->ip = ip;
}

void ClientThread::run() {
	QByteArray response;
	QByteArray name = this->name.toUtf8();

	qDebug() << "Starting client thread";

	socket = new QTcpSocket(this);

	socket->connectToHost(this->ip, 1234);

	if (socket->waitForConnected(3000)) {
		qDebug() << "Connected";
	}
	else {
		qDebug() << "something went wrong";
		exit();
	}

	this->socketDescriptor = socket->socketDescriptor();

	qDebug() << "Waiting for server init";
	socket->waitForReadyRead(3000);

	qDebug() << "Reading: " << socket->bytesAvailable();
	response = socket->readAll();

	qDebug() << "Server init response: " << response;

	if (response != "200;Server connection establisehd") {
		qDebug() << "Something was wrong with the servers response";
	}	
	
	qDebug() << "Sending name: " << name;
	socket->write(name);

	response = socket->readAll();

	qDebug() << "Thread officially created";

	connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
	connect(socket, SIGNAL(readyRead()), this, SLOT(onNewData()));

	exec();
}

void ClientThread::onNewData() {
	qDebug() << "Casting client";
	ChattingClient* pChatClient = dynamic_cast<ChattingClient*>(parent);
	qDebug() << "Recieving server data";

	QByteArray data = socket->readAll();
	qDebug() << "Server sent" << data;

	Message* message = new Message();

	qDebug() << "Parsing data";
	
	message->parse(data);

	qDebug() << "Adding message";
	pChatClient->addMessage(message);
}

void ClientThread::disconnected() {
	qDebug() << "Server disconnected";
	socket->deleteLater();

	exit();
}

void ClientThread::sendMessage(QByteArray content) {
	ChattingClient* pChatClient = dynamic_cast<ChattingClient*>(parent);
	Message* message = new Message(content, "Me");

	qDebug() << "Sending: " << content;

	pChatClient->addMessage(message);
	this->socket->write(content);
	this->socket->waitForBytesWritten();
}