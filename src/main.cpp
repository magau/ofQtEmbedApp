#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main(int argc, char *argv[]){
        QtOpenGLEmbedWindow ofWindow; // create a window

        ofWindow.qtAppInit(argc, argv);

        // set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
        ofSetupOpenGL(&ofWindow, 1024, 768, OF_WINDOW);                   // <-------- setup the GL context


        //ofQtAppInterface app(argc, argv, &ofWindow); //Qt app 
        ofWindow.qtApp->show();
        
        // this kicks off the running of my app
        // can be OF_WINDOW or OF_FULLSCREEN
        // pass in width and height too:
        ofRunApp( new ofApp());

        return ofWindow.qtApp->exec(); //Qt app 

}
