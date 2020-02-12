#pragma once
#include <QDateTime>
#include <QObject>

class Message : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString content READ getContent NOTIFY contentChanged)
	Q_PROPERTY(QString sender READ getSender NOTIFY senderChanged)
	Q_PROPERTY(QDateTime date READ getDate NOTIFY dateChanged)
public:
	Message();
	Message(QByteArray, QString);
	Message(QByteArray, QString, QDateTime);

	void parse(QByteArray);

	QString getSender();
	QString getContent();
	QDateTime getDate();

signals:
	void senderChanged();
	void contentChanged();
	void dateChanged();

private:
	QByteArray content;
	QDateTime date = QDateTime::currentDateTime();
	QString sender;

	bool logged = false;
};

