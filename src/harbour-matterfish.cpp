#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>

#include "mattermostclient.h"

static QObject* clientGen(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    MattermostClient* client = new MattermostClient();
    return client;
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
    qmlRegisterUncreatableType<MattermostTeam>("harbour.matterfish", 1, 0, "MattermostTeam", "");
    qmlRegisterUncreatableType<MattermostChannel>("harbour.matterfish", 1, 0, "MattermostChannel", "");
    return SailfishApp::main(argc, argv);
}
