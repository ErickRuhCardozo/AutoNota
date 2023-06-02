#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngineQuick>
#include <QSqlDatabase>
#include <QFile>
#include "settingsmanager.h"
#include "usersitemmodel.h"

bool isFirstRun()
{
    return !QFile::exists("app.db");
}

void createDatabase()
{
    QFile file(":/app.db");
    file.copy("app.db");
    QFile::setPermissions("app.db", QFile::ReadOwner | QFile::WriteOwner | QFile::ReadUser | QFile::WriteUser);
}

void loadSettings(QString* cnpj, QString* userName, QString* ssn, QString* password)
{
    SettingsManager settings;
    *cnpj = settings.cnpj();
    int defaultUserId = settings.defaultUser();

    if (defaultUserId > 0) {
        UsersItemModel model;
        const User* user = model.getUser(defaultUserId);

        if (user != nullptr) {
            *userName = user->fullName();
            *ssn = user->ssn();
            *password = user->password();
        }
    }
}

int main(int argc, char *argv[])
{
    bool firstRun = isFirstRun();

    if (firstRun)
        createDatabase();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("app.db");
    const QUrl url(u"qrc:/qt/qml/AutoNota/Views/Main.qml"_qs);

    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QtWebEngineQuick::initialize();
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    QString cnpj, user, ssn, password;
    loadSettings(&cnpj, &user, &ssn, &password);
    app.setWindowIcon(QIcon(":/Icons/app.svg"));
    engine.rootContext()->setContextProperty("isFirstRun", firstRun);
    engine.rootContext()->setContextProperty("entityCnpj", cnpj);
    engine.rootContext()->setContextProperty("defaultUser", user);
    engine.rootContext()->setContextProperty("defaultSsn", ssn);
    engine.rootContext()->setContextProperty("defaultPassword", password);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
