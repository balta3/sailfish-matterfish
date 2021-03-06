# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-matterfish

CONFIG += sailfishapp
CONFIG += c++11

QMAKE_CXXFLAGS_DEBUG -= -O1
QMAKE_CXXFLAGS_DEBUG -= -O2
QMAKE_CXXFLAGS_DEBUG -= -O3
QMAKE_CXXFLAGS_DEBUG *= -O0

SOURCES += src/harbour-matterfish.cpp \
    src/mattermostclient.cpp \
    src/mattermostteam.cpp \
    src/mattermostchannel.cpp \
    src/mattermostteammember.cpp \
    src/mattermostuser.cpp \
    src/mattermostpost.cpp \
    src/mattermostavatarimageprovider.cpp \
    src/qmlsettingswrapper.cpp \
    src/matterfishsettings.cpp \
    src/mattermostfile.cpp

DISTFILES += qml/harbour-matterfish.qml \
    qml/cover/CoverPage.qml \
    qml/pages/SecondPage.qml \
    rpm/harbour-matterfish.changes.in \
    rpm/harbour-matterfish.changes.run.in \
    rpm/harbour-matterfish.spec \
    rpm/harbour-matterfish.yaml \
    translations/*.ts \
    harbour-matterfish.desktop \
    qml/pages/LoginPage.qml \
    qml/pages/TeamsPage.qml \
    qml/pages/ChannelsPage.qml \
    qml/pages/PostsPage.qml \
    qml/pages/ImagePage.qml \
    qml/pages/SettingsPage.qml

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/harbour-matterfish-de.ts

HEADERS += \
    src/mattermostclient.h \
    src/mattermostteam.h \
    src/mattermostchannel.h \
    src/mattermostteammember.h \
    src/mattermostuser.h \
    src/mattermostpost.h \
    src/mattermostavatarimageprovider.h \
    src/qmlsettingswrapper.h \
    src/matterfishsettings.h \
    src/mattermostfile.h

PKGCONFIG += Qt5WebSockets

# QT += websockets
