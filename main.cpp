#include "ProdConsService2.h"
#include <Qtqml>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlComponent>
#include <QtQuick/QQuickWindow>
#include <QtCore/QUrl>
#include <QDebug>
#include <QLoggingCategory>
#include <QProcess>
#include <QtNetwork>
#include "option.h"

int main(int argc, char* argv[]){

#ifdef QT6
#ifdef WIN32
    QQuickWindow::setGraphicsApi(QSGRendererInterface::Direct3D11);
#endif
    QQuickWindow::setGraphicsApi(QSGRendererInterface::Metal);
#endif
#ifdef QT5
    // QQuickWindow::setSceneGraphBackend(QSGRendererInterface::MetalRhi);
#endif
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // QProcess *process =  new QProcess(&app);
    // process->start("/Users/mano233/Documents/qt_projects/build-qt5_exam-Desktop_Qt_5_15_1_clang_64bit-Debug/qt5_exam");
    qmlRegisterType<ProdConsService2>("com.mano.ProdConsService2", 1, 0, "ProdConsService2");
    const QUrl url("qrc:/qml/qml03.qml");
    // const QUrl url("qrc:/qml/ProdconsService.qml");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            }, Qt::QueuedConnection);
    engine.load(url);
    // QLoggingCategory::setFilterRules("qt.scenegraph.time.renderloop=true");
    return QGuiApplication::exec();
}
