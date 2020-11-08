#include "ProdConsService2.h"
#include <Qtqml>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlComponent>
#include <QtQuick/QQuickWindow>
#include <QtCore/QUrl>
#include <QDebug>

int main(int argc, char* argv[]){
    QQuickWindow::setGraphicsApi(QSGRendererInterface::MetalRhi);
    // QQuickWindow::setSceneGraphBackend(QSGRendererInterface::MetalRhi);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qmlRegisterType<ProdConsService2>("com.mano.ProdConsService2", 1, 0, "ProdConsService2");
    const QUrl url("qrc:/qml/ProdconsService.qml");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            }, Qt::QueuedConnection);
    engine.load(url);
    return QGuiApplication::exec();
}
