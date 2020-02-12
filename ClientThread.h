#pragma once

#include "Message.h"

#include <QThread>
#include <QTcpSocket>
#include <QObject>

class ClientThread : public QThread
{
	Q_OBJECT

public:
	explicit ClientThread(QString, QString, QObject* parent = 0);
	void run();
	void sendMessage(QByteArray);

	~ClientThread() {
		socket->close();
	}

signals:
	void error(QTcpSocket::SocketError socketError);

public slots:
	void onNewData();
	void disconnected();

private:
	void checkResponse(QByteArray);

	QTcpSocket* socket;
	qintptr socketDescriptor;
	QObject* parent;
	QString name;
	QString ip;
};

