#pragma once

#include "ui_ChattingClient.h"
#include "Message.h"
#include "ClientThread.h"

#include <QTcpSocket>
#include <QVector>
#include <QList>
#include <QQmlListProperty>

class ChattingClient : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QQmlListProperty<Message> messages READ messages NOTIFY messagesChanged)
public:
	ChattingClient(QWidget* parent = Q_NULLPTR);
	Q_INVOKABLE void connectToServer(const QString &name, const QString& ip);

	QQmlListProperty<Message> messages();
	void addMessage(Message* msg);
	Q_INVOKABLE void sendMessage(const QString &message);

signals:
	void messagesChanged();

private:
	static void append_message(QQmlListProperty<Message>* list, Message* msg);

	Ui::ChattingClientClass ui;

	ClientThread* thread;

	//QTcpSocket* socket;

	QList<Message *> m_messages;
};