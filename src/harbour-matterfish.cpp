#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>

#include "matterfishsettings.h"
#include "mattermostclient.h"
#include "mattermostavatarimageprovider.h"

static QObject* clientGen(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    MattermostClient* client = new MattermostClient();

    engine->addImageProvider("avatar", new MattermostAvatarImageProvider(client));
    engine->addImageProvider("team", new MattermostTeamIconImageProvider(client));
    return client;
}

static QObject* settingsGen(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    MatterfishSettings* settings = new MatterfishSettings();
    return settings;
}

int main(int argc, char *argv[])
{
    // SailfishApp::main() will display "qml/Matterfish.qml", if you need more
    // control over initialization, you can use:
    //
    //   - SailfishApp::application(int, char *[]) to get the QGuiApplication *
    //   - SailfishApp::createView() to get a new QQuickView * instance
    //   - SailfishApp::pathTo(QString) to get a QUrl to a resource file
    //   - SailfishApp::pathToMainQml() to get a QUrl to the main QML file
    //
    // To display the view, call "show()" (will show fullscreen on device).
    qmlRegisterSingletonType<MattermostClient>("harbour.matterfish", 1, 0, "MattermostClient", clientGen);
    qmlRegisterSingletonType<MatterfishSettings>("harbour.matterfish", 1, 0, "MatterfishSettings", settingsGen);
    qmlRegisterUncreatableType<MattermostTeam>("harbour.matterfish", 1, 0, "MattermostTeam", "");
    qmlRegisterUncreatableType<MattermostChannel>("harbour.matterfish", 1, 0, "MattermostChannel", "");
    qmlRegisterUncreatableType<MattermostTeamMember>("harbour.matterfish", 1, 0, "MattermostTeamMember", "");
    qmlRegisterUncreatableType<MattermostPost>("harbour.matterfish", 1, 0, "MattermostPost", "");
    qmlRegisterUncreatableType<MattermostUser>("harbour.matterfish", 1, 0, "MattermostUser", "");
    return SailfishApp::main(argc, argv);
}
