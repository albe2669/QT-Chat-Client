#include "Message.h"

#include <QDebug>

Message::Message() {
	this->content = "";
	this->sender = "";
}

Message::Message(QByteArray content, QString sender) {
	this->content = content;
	this->sender = sender;
	
	emit senderChanged();
	emit contentChanged();
}

Message::Message(QByteArray content, QString sender, QDateTime date) {
	this->content = content;
	this->sender = sender;
	this->date = date;

	emit senderChanged();
	emit contentChanged();
	emit dateChanged();
}

void Message::parse(QByteArray data) {
	QByteArrayList split = data.split(';');

	qDebug() << "Sender: " << split[0];
	this->sender = split[0];
	split.pop_front();

	qDebug() << "Content: " << split[0];
	this->content = split.join("");

	emit senderChanged();
	emit contentChanged();
	emit dateChanged();
}

QString Message::getSender() {
	return this->sender;
}

QString Message::getContent() {
	return this->content;
}

QDateTime Message::getDate() {
	return this->date;
}