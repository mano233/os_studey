#include <iostream>
#include "ProdConsService2.h"
#include <Qtqml>
#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include <QtQuick/QQuickWindow>
#include <QtCore/QUrl>
#include <QDebug>
#include <QQuickView>
#include <QDir>

int main(int argc, char* argv[]){
    QQuickWindow::setGraphicsApi(QSGRendererInterface::MetalRhi);
    // QQuickWindow::setSceneGraphBackend(QSGRendererInterface::MetalRhi);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<ProdConsService2>("com.mano.ProdConsService2", 1, 0, "ProdConsService2");
    const QUrl url("file:/Users/mano233/Documents/c_projects/untitled3/ProdConsService2.qml");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            }, Qt::QueuedConnection);
    engine.clearComponentCache();
    engine.load(url);
    return app.exec();
}