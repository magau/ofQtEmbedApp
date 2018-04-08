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
//#include <GL/glxext.h>
#include <GL/glx.h>
#include <iostream>

#include <signal.h>
#include <unistd.h>

ofQtAppInterface::ofQtAppInterface(int argc, char *argv[]) :
                                  of_app( new ofApp()){//,
                                  //qt_app(new QApplication(argc, argv)),
                                  //mainWindow(new QMainWindow),
                                  //ui(new Ui::mainWindow) {

        
        appInterfaceArgc = argc;
        for (int i = 0; i < argc; i++){
            appInterfaceArgv[i] = argv[i];
        }
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
//    std::cout << "call setupUi..." << std::endl;
//    ui->setupUi(mainWindow);
//    std::cout << "setupUi done." << std::endl;

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
    ofWindow->motion_cb(x, ofWindow->windowH - y);
}

void ofQtAppInterface::of_mouse_button(int button, int state, int x, int y){

    switch(button){
    case Qt::LeftButton:
        ofWindow->mouse_cb(OF_MOUSE_BUTTON_LEFT, state, x, ofWindow->windowH - y);
        break;
    case Qt::RightButton:
        ofWindow->mouse_cb(OF_MOUSE_BUTTON_RIGHT, state, x, ofWindow->windowH - y);
        break;
    case Qt::MiddleButton:
        ofWindow->mouse_cb(OF_MOUSE_BUTTON_MIDDLE, state, x, ofWindow->windowH - y);
        break;
    }
}

void ofQtAppInterface::of_close(){
    //std::cout << "closing ofApp..." << std::endl;
    ofWindow->close();
}

std::pair<int, int> ofQtAppInterface::get_window_pos(){
    return std::pair<int, int>(embedWindow->pos().x(),
                               embedWindow->pos().y());
}

ofQtGlWidget *ofQtAppInterface::createEmbedWindow(){
    //cout << "argc: " << appInterfaceArgc << endl;
    //vector<std::string> args(appInterfaceArgv, appInterfaceArgv + appInterfaceArgc);
    //for (string& iarg : args){
    //    cout << "argv: " << iarg << endl;
    //}

    qt_app = new QApplication(appInterfaceArgc, appInterfaceArgv);
    mainWindow = new QMainWindow;
    ui = new Ui::mainWindow;
    ui->setupUi(mainWindow);
    embedWindow = new ofQtGlWidget();
    embedWindow->setAppInterface(this);
    embedWindow->makeCurrent();
    return embedWindow; 
}

void ofQtAppInterface::setOfWindow(ofAppQGLEmbedWindow *ofWindow_ptr){
    ofWindow = ofWindow_ptr;
}

void ofQtAppInterface::setup(){
    setupUi();
    embedWindow->show();
    mainWindow->show();
    of_app->setup();
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
