#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableSmoothing();
    ofSetVerticalSync(true);
    ofBackground(0);
    //cout << "ofApp.setup()" << endl;
    //cout << "W: " << ofGetWindowWidth() << "; H: " << ofGetWindowHeight() << endl;
    ploc.x = ofGetWindowWidth()/2;
    ploc.y = ofGetWindowHeight()/2;
}

//--------------------------------------------------------------
void ofApp::update(){
    ploc.x = ofGetWindowWidth()/2;
    ploc.y = ofGetWindowHeight()/2;
    //ploc.x = ofGetMouseX();
    //ploc.y = ofGetMouseY();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(ofColor(255,0,0));
    int rad = 13;
    ofDrawEllipse(ploc.x,ploc.y,rad,rad);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
