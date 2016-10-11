#include <ui_QtEmbedApp.h> 
#include "ofQtAppInterface.h"
#include "QtOpenGLEmbedWindow.h"
#include "ofqtGlWidget.h"
//#define GLX_GLXEXT_PROTOTYPES 
#include <GL/glxext.h>
#include <GL/glx.h>
#include <GL/freeglut.h>
//#include <QtOpenGL/QGLWidget>

ofQtAppInterface::ofQtAppInterface(int argc, char *argv[], QtOpenGLEmbedWindow* ofWindow) :
                                  app(new QApplication(argc, argv)),
                                  mainWindow(new QMainWindow),							
                                  ui(new Ui::MainWindow) {

    if (ofWindow != NULL){
        embedWidget = ofWindow;
        ui->setupUi(mainWindow, (QWidget *) embedWidget->qgl_window);
        embedWidget->qgl_window->show();
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
