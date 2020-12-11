#include <QDebug>
#include <QLoggingCategory>
#include <QProcess>
#include <QtCore/QUrl>
#include <QtGui/QGuiApplication>
#include <QtNetwork>
#include <QtQml/QQmlComponent>
#include <QtQuick/QQuickWindow>
#include <Qtqml>
#include "ProdConsService2.h"
#include "option.h"
#include "DynamicAlloc.h"

int main(int argc, char* argv[]) {
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
    qmlRegisterType<ProdConsService2>("com.mano.ProdConsService2", 1, 0,
                                      "ProdConsService2");
    qmlRegisterType<DynamicAlloc>("com.mano233.DynamicAlloc",1,0,"DynamicAlloc");
    const QUrl url("qrc:/qml/DynamicAlloc.qml");
    // const QUrl url("qrc:/qml/ProdconsService.qml");
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject* obj, const QUrl& objUrl) {
            if ((obj == nullptr) && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    mm_init();
    mem_malloc(4);
    engine.load(url);
    // QLoggingCategory::setFilterRules("qt.scenegraph.time.renderloop=true");
    return QGuiApplication::exec();
}
