#include <QGuiApplication>
#include <QStandardPaths>
#include <QtQml>
#include <QQmlApplicationEngine>
#include <QQuickStyle>


// Models
#include "ChattingClient.h"
#include "Message.h"

int main(int argc, char *argv[])
{
	QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;


	ChattingClient w;

	// Register types
	qmlRegisterType<Message>("com.mycompany.messaging", 1, 0, "Message");
	qmlRegisterType<Message>("com.mycompany.messaging", 1, 0, "Client");

	QQuickStyle::setStyle("Material");

	// Register variables
	engine.rootContext()->setContextProperty("client", &w);

	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;
	return app.exec();
}
