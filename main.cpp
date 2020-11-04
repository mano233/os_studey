#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include <QtQuick/QQuickWindow>
#include <QtCore/QUrl>
#include <QDebug>
#include <QQuickView>
#include <QDir>
#include "TaskManager.h"
#include <iostream>
#include <thread>
#include "Filewatcher.h"

int main(int argc, char* argv[])
{
    QQuickWindow::setSceneGraphBackend(QSGRendererInterface::Direct3D11Rhi);
    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    QGuiApplication app(argc, argv);

    QQuickView view;

    const QDir DIRECTORY("F:\\clion_projects\\untitled3"); //你的qml文件所在的目录
    const QUrl SOURCE_URL = QUrl::fromLocalFile(DIRECTORY.filePath("mybox.qml"));

    view.setSource(SOURCE_URL);
    view.setWidth(600);
    view.setHeight(400);
    view.show();

    FileWatcher watcher([&view, SOURCE_URL](){
        view.engine()->clearComponentCache();
        view.setSource(SOURCE_URL);
    });

    watcher.setDirectory(DIRECTORY.absolutePath());
    // TaskManager ts(1);
    // ts.create("",1,3);
    return app.exec();
}