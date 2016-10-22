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
                                  ui(new Ui::openframeworks) {

        //cout << "argc: " << argc << endl;
        //vector<std::string> args(argv, argv + argc);
        //for (string& iarg : args){
        //    cout << "argv: " << iarg << endl;
        //}

}

ofQtAppInterface::~ofQtAppInterface(){
    delete ui;
    delete mainWindow;
    //std::cout << "delete embedWindow" << std::endl;
    //delete embedWindow;
    //std::cout << "done" << std::endl;
    delete app;
}


void ofQtAppInterface::setupUi() {
    /*
     * In case you get the folowing error:
     * ofQtEmbedApp: fccache.c:525: FcCacheFini: Assertion `fcCacheChains[i] == ((void *)0)' failed.
     * Aborted (core dumped)
     *
     * edit the file:
     * ../../../../libs/openFrameworks/graphics/ofTrueTypeFont.cpp
     *
     * Comment the line where FcFini() function is called.
     */
    ui->setupUi(mainWindow);
    embedWindow->setParent(ui->ofWindow);
    mainWindow->resize(ofWindow->windowW,
                       ofWindow->windowH);   
    ofWindow->windowW = embedWindow->width();
    ofWindow->windowH = embedWindow->height();
}

ofqt::ofqtGlWidget *ofQtAppInterface::createEmbedWindow(QtOpenGLEmbedWindow *ofWindow_ptr){
    ofWindow = ofWindow_ptr;
    QGLFormat format;
    format.setVersion(3, 0);
    format.setRgba(true);
    format.setDoubleBuffer(true);
    format.setDepth(true);
    embedWindow = new ofqt::ofqtGlWidget(format);
    embedWindow->makeCurrent();
    return embedWindow; 
}
void ofQtAppInterface::show(){
    setupUi();
    embedWindow->show();
    mainWindow->show();
}

int ofQtAppInterface::exec(){
    show();
    return app->exec();
}
