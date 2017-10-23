#include "ofMain.h"
#include "ofApp.h"
#include "ofAppQGLEmbedWindow.h"

//========================================================================
int main(int argc, char *argv[]){
        ofAppQGLEmbedWindow ofQtWindow; // create a window

        ofInit();
        ofGetMainLoop()->addWindow(shared_ptr<ofAppQGLEmbedWindow> (&ofQtWindow));
        auto settings = ofQtWindow.getSettings();
        settings.windowMode = OF_WINDOW;
        settings.width = 1024;
        settings.height = 768;
        ofQtWindow.setup(settings);

        ofQtWindow.qtAppInit(argc, argv);
        

        // set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
        //ofSetupOpenGL(&ofQtWindow, 1024, 768, OF_WINDOW);                   // <-------- setup the GL context

        // this kicks off the running of my app
        // can be OF_WINDOW or OF_FULLSCREEN
        // pass in width and height too:
        //ofRunApp( new ofApp());

        auto exec_return = ofQtWindow.qtApp->exec();
        return exec_return;
        //return ofQtWindow.qtAppExec(argc, argv); //Qt app 
}
