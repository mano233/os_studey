#include "ProdConsService2.h"
#include <Qtqml>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlComponent>
#include <QtQuick/QQuickWindow>
#include <QtCore/QUrl>
#include <QDebug>
#include <QLoggingCategory>
#include <QProcess>
int main(int argc, char* argv[]){
    QQuickWindow::setGraphicsApi(QSGRendererInterface::Metal);
    // QQuickWindow::setSceneGraphBackend(QSGRendererInterface::MetalRhi);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    // QProcess *process =  new QProcess(&app);
    // process->start("/Users/mano233/Documents/qt_projects/build-qt5_exam-Desktop_Qt_5_15_1_clang_64bit-Debug/qt5_exam");
    // QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    // format.setSwapInterval(0.1);
    // QSurfaceFormat::setDefaultFormat(format);
    qmlRegisterType<ProdConsService2>("com.mano.ProdConsService2", 1, 0, "ProdConsService2");
    // const QUrl url("qrc:/qml/mainwindow.qml");
    const QUrl url("qrc:/qml/qml03.qml");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            }, Qt::QueuedConnection);
    engine.load(url);
    //QLoggingCategory::setFilterRules("qt.scenegraph.*=true");
    return QGuiApplication::exec();
}
