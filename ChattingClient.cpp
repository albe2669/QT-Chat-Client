#include "ChattingClient.h"
#include "ClientThread.h"

#include <QTcpSocket>
#include <QDateTime>
#include <QString>
#include <QQmlListProperty>

// Widgets
#include <QInputDialog>
#include <QLineEdit>

ChattingClient::ChattingClient(QWidget *parent)
{

}

void ChattingClient::connectToServer(const QString &name, const QString& ip) {

	ClientThread* thread = new ClientThread(name, ip, this);
		
	this->thread = thread;
		
	thread->start();

}

QQmlListProperty<Message> ChattingClient::messages() {
	//return QQmlListProperty<Message>(this, 0, &ChattingClient::append_message);
	return QQmlListProperty<Message>(this, m_messages);
}

void ChattingClient::append_message(QQmlListProperty<Message>* list, Message* msg) {
	ChattingClient* client = qobject_cast<ChattingClient*>(list->object);
	if (msg) {
		client->m_messages.prepend(msg);	
	}
}

void ChattingClient::addMessage(Message* msg) {
	this->m_messages.prepend(msg);

	emit messagesChanged();
}

void ChattingClient::sendMessage(const QString &message) {
	QByteArray arr = message.toUtf8();
	Message* myMessage = new Message(arr, "Me");

	this->thread->sendMessage(arr);

	emit messagesChanged();
}
