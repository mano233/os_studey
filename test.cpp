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
    QGuiApplication app(argc, argv);
    QQuickWindow::setSceneGraphBackend(QSGRendererInterface::MetalRhi);
    QQmlApplicationEngine engine;
    qmlRegisterType<ProdConsService2>("com.mano.ProdConsService2", 1, 0, "ProdConsService2");
    ProdConsService2 p2;
    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("file:/Users/mano233/Documents/c_projects/untitled3/ProdConsService2.qml"));
    view.show();
    // QQmlComponent component(&engine,QUrl("file:/Users/mano233/Documents/c_projects/untitled3/ProdConsService2.qml"));
    // QObject *object = component.create();
    QObject::connect(view.engine(), SIGNAL(quit()), &app, SLOT(quit()));
    //QObject::connect(object,SIGNAL(qmlSignal()),&p2,SLOT(qmlSlot()));
    return QGuiApplication::exec();
}