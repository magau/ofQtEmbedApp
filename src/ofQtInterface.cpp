#include <ui_QtEmbedApp.h> 
#include <Qt/qx11embed_x11.h>
#include "ofQtInterface.h"
#include "QtEmbedGlutWindow.h"
//#define GLX_GLXEXT_PROTOTYPES 
#include <GL/glxext.h>
#include <GL/glx.h>
#include <GL/freeglut.h>

ofQtAppInterface::ofQtAppInterface(int argc, char *argv[], QtEmbedGlutWindow* ofWindow) :
                                  app(new QApplication(argc, argv)),
                                  mainWindow(new QMainWindow),							
                                  embedWidget (new QX11EmbedContainer),
                                  ui(new Ui::MainWindow) {

    cout << "aqui" << endl;
    if (ofWindow != NULL){
        FGAPI int *glutWin = ofWindow->get_windowId();
        //cout << "x11Win Id: " << glutWin << endl;
        //GLXContext winContext = ofWindow->getGLXContext();
        //Display* currentDisplay = glXGetCurrentDisplay();
        cout << "Display: " << currentDisplay << endl;
        //embedWidget->embedClient(glutWin->ID);
        ui->setupUi(mainWindow, (QWidget *) embedWidget);
    }else{ 
        ui->setupUi(mainWindow);
    }
    mainWindow->show();
    embedWidget->show();
}

ofQtAppInterface::~ofQtAppInterface(){
    delete app;
    delete embedWidget;
    delete ui;
}

int ofQtAppInterface::exec(){
    return app->exec();
}
