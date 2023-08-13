#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngineQuick>
#include <QSqlDatabase>
#include <QFile>
#include "settingsmanager.h"
#include "usersitemmodel.h"

bool isFirstRun()
{
    return !QFile::exists("./app.db");
}

void createDatabase()
{
    qDebug() << "Copying database file from resources to App's directory";
    QFile file(":/app.db");

    if (file.copy("./app.db")) {
        qDebug() << "Database file copied successfully";

        qDebug() << "About to change permissions on database file";
        bool success = QFile::setPermissions("app.db", QFile::ReadOwner| QFile::WriteOwner | QFile::ReadUser | QFile::WriteUser | QFile::ReadGroup | QFile::WriteGroup | QFile::ReadOther | QFile::WriteOther);

        if (success) {
            qDebug() << "Permissions set successfully!";
        } else {
            qCritical() << "Could not set permissions on database file.";
        }
    } else {
        qCritical() << "Database file could not be copied!";
    }
}

void loadSettings(QString* cnpj, QString* userName, QString* ssn, QString* password)
{
    qDebug() << "About to loading App Settings";
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
    if (isFirstRun()) {
        qDebug() << "First Run Detected!";
        createDatabase();
    }

    const QUrl url(u"qrc:/qt/qml/AutoNota/Views/Main.qml"_qs);

    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QtWebEngineQuick::initialize();
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;    
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString cnpj, user, ssn, password;
    db.setDatabaseName("./app.db");

    loadSettings(&cnpj, &user, &ssn, &password);

    app.setWindowIcon(QIcon(":/Icons/app.svg"));
    app.setOrganizationName("Erick Ruh Cardozo");
    app.setOrganizationDomain("github.com/erickruhcardozo");
    app.setApplicationName("AutoNota");

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
