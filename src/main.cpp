#include "ofMain.h"
#include "ofApp.h"
#include "ofAppQGLEmbedWindow.h"

//========================================================================
int main(int argc, char *argv[]){
        ofAppQGLEmbedWindow ofQtWindow; // create a window

        ofQtWindow.qtAppInit(argc, argv);
        
        // set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
        ofSetupOpenGL(&ofQtWindow, 1024, 768, OF_WINDOW);                   // <-------- setup the GL context
        
        // this kicks off the running of my app
        // can be OF_WINDOW or OF_FULLSCREEN
        // pass in width and height too:
        ofRunApp( new ofApp());

        return ofQtWindow.qtAppExec(); //Qt app 
}
