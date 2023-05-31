#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngineQuick>
#include <QSqlDatabase>
#include "settingsmanager.h"
#include "usersitemmodel.h"

int main(int argc, char *argv[])
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    const QUrl url(u"qrc:/qt/qml/AutoNota/Views/Main.qml"_qs);
    QString cnpj, ssn, password;
    int defaultUserId = -1;

    db.setDatabaseName("app.db");

    {
        SettingsManager settings;
        cnpj = settings.cnpj();
        defaultUserId = settings.defaultUser();
    }

    if (defaultUserId > 0) {
        UsersItemModel model;
        const User* user = model.getUser(defaultUserId);

        if (user != nullptr) {
            ssn = user->ssn();
            password = user->password();
        }
    }

    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QtWebEngineQuick::initialize();
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("entityCnpj", cnpj);
    engine.rootContext()->setContextProperty("defaultSsn", ssn);
    engine.rootContext()->setContextProperty("defaultPassword", password);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
