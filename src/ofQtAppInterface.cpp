#include <ui_QtEmbedApp.h> 

#include "ofQtAppInterface.h"
#include "QtOpenGLEmbedWindow.h"
#include "ofqtGlWidget.h"

#include "ofGLRenderer.h"
#include <QtGui/QVBoxLayout>
#include <QtGui/QSizePolicy>
#include <QtCore/QString>
#include <QtOpenGL/QGLFormat>
#include <GL/glxext.h>
#include <GL/glx.h>
#include <iostream>

ofQtAppInterface::ofQtAppInterface(int argc, char *argv[]) :
                                  app(new QApplication(argc, argv)),
                                  mainWindow(new QMainWindow),
                                  ui(new Ui::MainWindow) {
}

void ofQtAppInterface::setupUi() {
    mainWindow->setObjectName(QString::fromUtf8("openframeworks"));
    ui->setupUi(mainWindow);
    mainWindow->setWindowTitle(QApplication::translate(
        "openframeworks", "openframeworks", 0,
        QApplication::UnicodeUTF8
    ));
    embedWindow->setParent(ui->ofWindow);
}

void ofQtAppInterface::show(){
    embedWindow->show();
    mainWindow->show();
}

ofQtAppInterface::~ofQtAppInterface(){
    delete ui;
    delete mainWindow;
    //std::cout << "delete embedWindow" << std::endl;
    //delete embedWindow;
    //std::cout << "done" << std::endl;
    delete app;
}

int ofQtAppInterface::exec(){
    setupUi();
    show();
    return app->exec();
}

ofqt::ofqtGlWidget *ofQtAppInterface::createEmbedWindow(const ofGLWindowSettings *settings){
    windowSettings = settings;
    QGLFormat format;
    format.setVersion(3, 0);
    format.setRgba(true);
    format.setDoubleBuffer(true);
    format.setDepth(true);
    embedWindow = new ofqt::ofqtGlWidget(format);
    embedWindow->makeCurrent();
    return embedWindow; 
}
