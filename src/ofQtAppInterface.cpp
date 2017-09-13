#include <ofAppQtUi.h> 
/* The "ofAppQtUi.h" header file is
 * automatically generated; do not edit
 * 
 * uic src/ofAppQt.ui > src/ofAppQtUi.h
 */
#include "ofApp.h"
#include "ofQtAppInterface.h"
#include "ofAppQGLEmbedWindow.h"
#include "ofQtGlWidget.h"

#include "ofGLRenderer.h"
//#include <QtGui/QVBoxLayout>
//#include <QtGui/QHBoxLayout>
//#include <QtGui/QSizePolicy>
//#include <QtCore/QString>
#include <QtOpenGL/QGLFormat>
#include <GL/glxext.h>
#include <GL/glx.h>
#include <iostream>

ofQtAppInterface::ofQtAppInterface(int argc, char *argv[]) :
                                  qt_app(new QApplication(argc, argv)),
                                  of_app( new ofApp()),
                                  mainWindow(new QMainWindow),
                                  ui(new Ui::mainWindow) {

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
    delete of_app;
    delete qt_app;
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

    /* Remove the ui->ofWindow QWidget, which was created
       by the ui->setupUi method. Replace it by the 
       'embedWindow' our QGLWidget derived class.
     */
    embedWindow->setSizePolicy(ui->ofWindow->sizePolicy());
    //ui->horizontalLayout->removeWidget(ui->ofWindow);
    delete ui->ofWindow;
    ui->ofWindow = embedWindow;
    ui->horizontalLayout->addWidget(embedWindow);

    mainWindow->resize(ofWindow->windowW,
                       ofWindow->windowH);   
}

void ofQtAppInterface::of_resize(int w, int h){
    ofWindow->resize_cb(w, h);
}


void ofQtAppInterface::of_mouse_move(int x, int y){
    //y -= ofWindow->windowH; 
    ofWindow->motion_cb(x, y);
}

ofQtGlWidget *ofQtAppInterface::createEmbedWindow(ofAppQGLEmbedWindow *ofWindow_ptr){
    ofWindow = ofWindow_ptr;
    QGLFormat format;
    format.setVersion(3, 0);
    format.setRgba(true);
    format.setDoubleBuffer(true);
    format.setDepth(true);
    embedWindow = new ofQtGlWidget(format);
    embedWindow->setAppInterface(this);
    embedWindow->makeCurrent();
    return embedWindow; 
}
void ofQtAppInterface::setup(){
    //cout << "qtUi.setup()" << endl;
    //cout << "W: " << (ofWindow->windowW) << "; H: " << (ofWindow->windowH) << endl;
    setupUi();
    //cout << "embedWindow" << endl;
    //cout << "W: " << (embedWindow->width()) << "; H: " << (embedWindow->height()) << endl;
    of_app->setup();
    embedWindow->show();
    mainWindow->show();
}

int ofQtAppInterface::get_width(){
    return embedWindow->width();
}

int ofQtAppInterface::get_height(){
    return embedWindow->height();
}


void ofQtAppInterface::update(){
    of_app->update();
    of_app->draw();
}

int ofQtAppInterface::exec(){
    return qt_app->exec();
}
