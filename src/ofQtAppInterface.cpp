#include <ui_QtEmbedApp.h> 
#include "ofQtAppInterface.h"
#include "QtOpenGLEmbedWindow.h"
#include "ofqtGlWidget.h"
//#define GLX_GLXEXT_PROTOTYPES 
#include <QtOpenGL/QGLFormat>
#include <GL/glxext.h>
#include <GL/glx.h>

ofQtAppInterface::ofQtAppInterface(int argc, char *argv[]) :
                                  app(new QApplication(argc, argv)),
                                  mainWindow(new QMainWindow),
                                  ui(new Ui::MainWindow) {
}

void ofQtAppInterface::show(QtOpenGLEmbedWindow* ofWindow){

    if (ofWindow != NULL){
        //GLXContext glXGetCurrentContext();
        //Display* currentDisplay = glXGetCurrentDisplay();
        ui->setupUi(mainWindow, (QWidget *) ofWindow->get_windowId());
        ofWindow->get_windowId()->show();
    }else{ 
        ui->setupUi(mainWindow);
    }
    mainWindow->show();
}

ofQtAppInterface::~ofQtAppInterface(){
    delete app;
    delete mainWindow;
    delete ui;
}

int ofQtAppInterface::exec(){
    return app->exec();
}

ofqt::ofqtGlWidget *ofQtAppInterface::createEmbedWindow(){
   QGLFormat format;
   format.setVersion(3, 0);
   return new ofqt::ofqtGlWidget(format); 
}
