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

void ofQtAppInterface::show(){
    ui->setupUi(mainWindow, (QWidget *) embedWindow);
    //ui->setupUi(mainWindow);
    //resetQtUi();
    embedWindow->show();
    mainWindow->show();
}

void ofQtAppInterface::resetQtUiEmbedWindow() {
    delete ui->ofWindow;
    ui->ofWindow = (QWidget *) embedWindow;
    embedWindow->setObjectName(QString::fromUtf8("ofWindow"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(embedWindow->sizePolicy().hasHeightForWidth());
    embedWindow->setSizePolicy(sizePolicy);
    delete ui->ofVerticalLayout;
    ui->ofVerticalLayout = new QVBoxLayout(embedWindow);
    ui->horizontalLayout->addWidget(embedWindow);
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
    show();
    return app->exec();
}

ofqt::ofqtGlWidget *ofQtAppInterface::createEmbedWindow(const ofGLWindowSettings & settings){
   QGLFormat format;
   format.setVersion(3, 0);
   format.setRgba(true);
   format.setDoubleBuffer(true);
   format.setDepth(true);
   embedWindow = new ofqt::ofqtGlWidget(format);
   embedWindow->makeCurrent();
   return embedWindow; 
}
