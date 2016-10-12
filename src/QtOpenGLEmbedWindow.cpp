#include "QtOpenGLEmbedWindow.h"
#include "ofBaseApp.h"
#include "ofConstants.h"
#include "ofPixels.h"
#include "ofGLRenderer.h"

#include "ofIcon.h"
#include "ofImage.h"
#include <X11/Xatom.h>

#include "ofQtAppInterface.h"

// glut works with static callbacks UGH, so we need static variables here:

static ofWindowMode windowMode;
static bool			bNewScreenMode;
static int			buttonInUse;
static bool			bEnableSetupScreen;
static bool			bDoubleBuffered; 

static int			requestedWidth;
static int			requestedHeight;
static int 			nonFullScreenX;
static int 			nonFullScreenY;
static int			windowW;
static int			windowH;
static int          nFramesSinceWindowResized;
static ofOrientation	orientation;
static QtOpenGLEmbedWindow * instance;


//----------------------------------------------------------
QtOpenGLEmbedWindow::QtOpenGLEmbedWindow(){
	windowMode			= OF_WINDOW;
	bNewScreenMode		= true;
	nFramesSinceWindowResized = 0;
	buttonInUse			= 0;
	bEnableSetupScreen	= true;
	requestedWidth		= 0;
	requestedHeight		= 0;
	nonFullScreenX		= -1;
	nonFullScreenY		= -1;
	displayString		= "";
	orientation			= OF_ORIENTATION_DEFAULT;
	bDoubleBuffered = true; // LIA
	iconSet = false;
	instance = this;
	windowId = 0;
}

void QtOpenGLEmbedWindow::qtAppInit(int argc, char *argv[]) {
    qtApp = new ofQtAppInterface(argc, argv);
}

ofqt::ofqtGlWidget *QtOpenGLEmbedWindow::createEmbedWindow() {
    return qtApp->createEmbedWindow();
}

//lets you enable alpha blending using a display string like:
// "rgba double samples>=4 depth" ( mac )
// "rgb double depth alpha samples>=4" ( some pcs )
//------------------------------------------------------------
 void QtOpenGLEmbedWindow::setGlutDisplayString(string displayStr){
	displayString = displayStr;
 }

 //------------------------------------------------------------
void QtOpenGLEmbedWindow::setDoubleBuffering(bool _bDoubleBuffered){ 
	bDoubleBuffered = _bDoubleBuffered;
}

//------------------------------------------------------------
void QtOpenGLEmbedWindow::setup(const ofGLWindowSettings & settings){

	int argc = 1;
	char *argv = (char*)"openframeworks";
	char **vptr = &argv;
//	glutInit(&argc, vptr);

//	if( displayString != ""){
//		glutInitDisplayString( displayString.c_str() );
//	}else{
//		if(bDoubleBuffered){  
//			glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA );
//		}else{
//			glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH | GLUT_ALPHA );
//		}
//	}

//        QGLFormat format = ofqt::ofqtGlWidget::createOpenGLContextFormat();
        //format.setVersion(3, 0);
        windowId = createEmbedWindow();

	windowMode = settings.windowMode;
	bNewScreenMode = true;

	if (windowMode == OF_FULLSCREEN){
//		glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
//		windowId = glutCreateWindow("");
		
		requestedWidth  = settings.width;
		requestedHeight = settings.height;
//	} else if (windowMode != OF_GAME_MODE){
//		glutInitWindowSize(settings.width, settings.height);
//		windowId = glutCreateWindow("");

		/*
		ofBackground(200,200,200);		// default bg color
		ofSetColor(0xFFFFFF); 			// default draw color
		// used to be black, but
		// black + texture = black
		// so maybe grey bg
		// and "white" fg color
		// as default works the best...
		*/

//		requestedWidth  = glutGet(GLUT_WINDOW_WIDTH);
//		requestedHeight = glutGet(GLUT_WINDOW_HEIGHT);
	} else {
//		if( displayString != ""){
//			glutInitDisplayString( displayString.c_str() );
//		}else{
//			glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA );
//		}

    	// w x h, 32bit pixel depth, 60Hz refresh rate
		char gameStr[64];
		sprintf( gameStr, "%dx%d:%d@%d", settings.width, settings.height, 32, 60 );

//    	glutGameModeString(gameStr);

//    	if (!glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)){
//    		ofLogError("QtOpenGLEmbedWindow") << "setupOpenGL(): selected game mode format " << gameStr << " not available";
//    	}
    	// start fullscreen game mode
//    	windowId = glutEnterGameMode();
	}
//	windowW = glutGet(GLUT_WINDOW_WIDTH);
//	windowH = glutGet(GLUT_WINDOW_HEIGHT);

	currentRenderer = shared_ptr<ofBaseRenderer>(new ofGLRenderer(this));


#ifndef TARGET_OPENGLES
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		ofLogError("ofAppRunner") << "couldn't init GLEW: " << glewGetErrorString(err);
		return;
	}
#endif
	static_cast<ofGLRenderer*>(currentRenderer.get())->setup();
	setVerticalSync(true);


    //----------------------
    // setup the callbacks

//    glutMouseFunc(mouse_cb);
//    glutMotionFunc(motion_cb);
//    glutPassiveMotionFunc(passive_motion_cb);
//    glutIdleFunc(idle_cb);
//    glutDisplayFunc(display);
//
//    glutKeyboardFunc(keyboard_cb);
//    glutKeyboardUpFunc(keyboard_up_cb);
//    glutSpecialFunc(special_key_cb);
//    glutSpecialUpFunc(special_key_up_cb);
//
//    glutReshapeFunc(resize_cb);
//	glutEntryFunc(entry_cb);
//#ifdef TARGET_LINUX
//	glutCloseFunc(exit_cb);
//#endif
//
//#ifdef TARGET_OSX
//	glutDragEventFunc(dragEvent);
//#endif

    nFramesSinceWindowResized = 0;

#ifdef TARGET_LINUX
    if(!iconSet){
		ofPixels iconPixels;
		#ifdef DEBUG
			iconPixels.allocate(ofIconDebug.width,ofIconDebug.height,ofIconDebug.bytes_per_pixel);
			GIMP_IMAGE_RUN_LENGTH_DECODE(iconPixels.getData(),ofIconDebug.rle_pixel_data,iconPixels.getWidth()*iconPixels.getHeight(),ofIconDebug.bytes_per_pixel);
		#else
			iconPixels.allocate(ofIcon.width,ofIcon.height,ofIcon.bytes_per_pixel);
			GIMP_IMAGE_RUN_LENGTH_DECODE(iconPixels.getData(),ofIcon.rle_pixel_data,iconPixels.getWidth()*iconPixels.getHeight(),ofIcon.bytes_per_pixel);
		#endif
		setWindowIcon(iconPixels);
    }
#endif
	if (settings.isPositionSet()) {
		setWindowPosition(settings.getPosition().x,settings.getPosition().y);
	}

#ifdef TARGET_OSX
	// The osx implementation of glut changes the cwd, this restores it
	// to wherever it was when the app was started
	ofRestoreWorkingDirectoryToDefault();
#endif
}

#ifdef TARGET_LINUX
//------------------------------------------------------------
void QtOpenGLEmbedWindow::setWindowIcon(const string & path){
    ofPixels iconPixels;
	ofLoadImage(iconPixels,path);
	setWindowIcon(iconPixels);
}

//------------------------------------------------------------
void QtOpenGLEmbedWindow::setWindowIcon(const ofPixels & iconPixels){
	iconSet = true;
	Display *m_display = glXGetCurrentDisplay();
	GLXDrawable m_window = glXGetCurrentDrawable();
	iconSet = true;
	int length = 2+iconPixels.getWidth()*iconPixels.getHeight();
	unsigned long * buffer = new unsigned long[length];
	buffer[0]=iconPixels.getWidth();
	buffer[1]=iconPixels.getHeight();
	for(int i=0;i<iconPixels.getWidth()*iconPixels.getHeight();i++){
		buffer[i+2] = iconPixels[i*4+3]<<24;
		buffer[i+2] += iconPixels[i*4]<<16;
		buffer[i+2] += iconPixels[i*4+1]<<8;
		buffer[i+2] += iconPixels[i*4];
	}

	XChangeProperty(m_display, m_window, XInternAtom(m_display, "_NET_WM_ICON", False), XA_CARDINAL, 32,
						 PropModeReplace,  (const unsigned char*)buffer,  length);
	delete[] buffer;
	XFlush(m_display);
}
#endif

//------------------------------------------------------------
void QtOpenGLEmbedWindow::update(){
	idle_cb();
}

//------------------------------------------------------------
void QtOpenGLEmbedWindow::draw(){
	display();
}

//------------------------------------------------------------
void QtOpenGLEmbedWindow::close(){
	events().notifyExit();
	events().disable();
//#ifdef TARGET_LINUX
//	glutLeaveMainLoop();
//#else
//	std::exit(0);
//#endif
}

//------------------------------------------------------------
void QtOpenGLEmbedWindow::loop(){
	instance->events().notifySetup();
	instance->events().notifyUpdate();
//	glutMainLoop();
}

//------------------------------------------------------------
void QtOpenGLEmbedWindow::setWindowTitle(string title){
//	glutSetWindowTitle(title.c_str());
}

//------------------------------------------------------------
ofPoint QtOpenGLEmbedWindow::getWindowSize(){
	return ofPoint(windowW, windowH,0);
}

//------------------------------------------------------------
ofPoint QtOpenGLEmbedWindow::getWindowPosition(){
	int x = 0;//glutGet(GLUT_WINDOW_X);
	int y = 0;//glutGet(GLUT_WINDOW_Y);
	if( orientation == OF_ORIENTATION_DEFAULT || orientation == OF_ORIENTATION_180 ){
		return ofPoint(x,y,0);
	}else{
		return ofPoint(y,x,0);
	}
}

//------------------------------------------------------------
ofPoint QtOpenGLEmbedWindow::getScreenSize(){
	int width = 500;//glutGet(GLUT_SCREEN_WIDTH);
	int height = 500;//glutGet(GLUT_SCREEN_HEIGHT);
	if( orientation == OF_ORIENTATION_DEFAULT || orientation == OF_ORIENTATION_180 ){
		return ofPoint(width, height,0);
	}else{
		return ofPoint(height, width,0);
	}
}

//------------------------------------------------------------
int QtOpenGLEmbedWindow::getWidth(){
	if( orientation == OF_ORIENTATION_DEFAULT || orientation == OF_ORIENTATION_180 ){
		return windowW;
	}
	return windowH;
}

//------------------------------------------------------------
int QtOpenGLEmbedWindow::getHeight(){
	if( orientation == OF_ORIENTATION_DEFAULT || orientation == OF_ORIENTATION_180 ){
		return windowH;
	}
	return windowW;
}

//------------------------------------------------------------
void QtOpenGLEmbedWindow::setOrientation(ofOrientation orientationIn){
	orientation = orientationIn;
}

//------------------------------------------------------------
ofOrientation QtOpenGLEmbedWindow::getOrientation(){
	return orientation;
}

//------------------------------------------------------------
void QtOpenGLEmbedWindow::setWindowPosition(int x, int y){
	//glutPositionWindow(x,y);
}

//------------------------------------------------------------
void QtOpenGLEmbedWindow::setWindowShape(int w, int h){
//	glutReshapeWindow(w, h);
	// this is useful, esp if we are in the first frame (setup):
	requestedWidth  = w;
	requestedHeight = h;
}

//------------------------------------------------------------
void QtOpenGLEmbedWindow::hideCursor(){
	#if defined(TARGET_OSX) && defined(MAC_OS_X_VERSION_10_7)
		 CGDisplayHideCursor(0);
	#else
//		glutSetCursor(GLUT_CURSOR_NONE);
	#endif
}

//------------------------------------------------------------
void QtOpenGLEmbedWindow::showCursor(){
	#if defined(TARGET_OSX) && defined(MAC_OS_X_VERSION_10_7)
		 CGDisplayShowCursor(0);
	#else
//		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	#endif
}

//------------------------------------------------------------
ofWindowMode QtOpenGLEmbedWindow::getWindowMode(){
	return windowMode;
}

//------------------------------------------------------------
void QtOpenGLEmbedWindow::toggleFullscreen(){
	if( windowMode == OF_GAME_MODE)return;

	if( windowMode == OF_WINDOW ){
		windowMode = OF_FULLSCREEN;
	}else{
		windowMode = OF_WINDOW;
	}

	bNewScreenMode = true;
}

//------------------------------------------------------------
void QtOpenGLEmbedWindow::setFullscreen(bool fullscreen){
    if( windowMode == OF_GAME_MODE)return;

    if(fullscreen && windowMode != OF_FULLSCREEN){
        bNewScreenMode  = true;
        windowMode      = OF_FULLSCREEN;
    }else if(!fullscreen && windowMode != OF_WINDOW) {
        bNewScreenMode  = true;
        windowMode      = OF_WINDOW;
    }
}

//------------------------------------------------------------
void QtOpenGLEmbedWindow::enableSetupScreen(){
	bEnableSetupScreen = true;
}

//------------------------------------------------------------
void QtOpenGLEmbedWindow::disableSetupScreen(){
	bEnableSetupScreen = false;
}

//------------------------------------------------------------
void QtOpenGLEmbedWindow::setVerticalSync(bool bSync){
	//----------------------------
	//--------------------------------------
	#ifdef TARGET_OSX
	//--------------------------------------
		GLint sync = bSync == true ? 1 : 0;
		CGLSetParameter (CGLGetCurrentContext(), kCGLCPSwapInterval, &sync);
	//--------------------------------------
	#endif
	//--------------------------------------

	//--------------------------------------
	#ifdef TARGET_LINUX
	//--------------------------------------
		void (*swapIntervalExt)(Display *,GLXDrawable, int)	 = (void (*)(Display *,GLXDrawable, int)) glXGetProcAddress((const GLubyte*) "glXSwapIntervalEXT");
		if(swapIntervalExt){
			Display *dpy = glXGetCurrentDisplay();
			GLXDrawable drawable = glXGetCurrentDrawable();
			if (drawable) {
				swapIntervalExt(dpy, drawable, bSync ? 1 : 0);
				return;
			}
		}
		void (*swapInterval)(int) = (void (*)(int)) glXGetProcAddress((const GLubyte*) "glXSwapIntervalSGI");
		if(!swapInterval) {
			swapInterval = (void (*)(int)) glXGetProcAddress((const GLubyte*) "glXSwapIntervalMESA");
		}
		if(swapInterval) {
			swapInterval(bSync ? 1 : 0);
		}
	//--------------------------------------
	#endif
	//--------------------------------------
}

//------------------------------------------------------------
ofCoreEvents & QtOpenGLEmbedWindow::events(){
	return coreEvents;
}

//------------------------------------------------------------
shared_ptr<ofBaseRenderer> & QtOpenGLEmbedWindow::renderer(){
	return currentRenderer;
}

//------------------------------------------------------------
void QtOpenGLEmbedWindow::display(void){

	//--------------------------------
	// when I had "glutFullScreen()"
	// in the initOpenGl, I was gettings a "heap" allocation error
	// when debugging via visual studio.  putting it here, changes that.
	// maybe it's voodoo, or I am getting rid of the problem
	// by removing something unrelated, but everything seems
	// to work if I put fullscreen on the first frame of display.

	if (windowMode != OF_GAME_MODE){
		if ( bNewScreenMode ){
			if( windowMode == OF_FULLSCREEN){

				//----------------------------------------------------
				// before we go fullscreen, take a snapshot of where we are:
				nonFullScreenX = 0;//glutGet(GLUT_WINDOW_X);
				nonFullScreenY = 0;//glutGet(GLUT_WINDOW_Y);
				//----------------------------------------------------

				//glutFullScreen();

				#ifdef TARGET_OSX
					[NSApp setPresentationOptions:NSApplicationPresentationHideMenuBar | NSApplicationPresentationHideDock];
					#ifdef MAC_OS_X_VERSION_10_7 //needed for Lion as when the machine reboots the app is not at front level
						if( instance->events().getFrameNum() <= 10 ){  //is this long enough? too long?
							[[NSApplication sharedApplication] activateIgnoringOtherApps:YES];
						}
					#endif
				#endif

			}else if( windowMode == OF_WINDOW ){

				//glutReshapeWindow(requestedWidth, requestedHeight);

				//----------------------------------------------------
				// if we have recorded the screen posion, put it there
				// if not, better to let the system do it (and put it where it wants)
				//if (instance->events().getFrameNum() > 0){
				//	glutPositionWindow(nonFullScreenX,nonFullScreenY);
				//}
				//----------------------------------------------------

				#ifdef TARGET_OSX
					[NSApp setPresentationOptions:NSApplicationPresentationDefault];
				#endif
			}
			bNewScreenMode = false;
		}
	}

	instance->currentRenderer->startRender();

	if( bEnableSetupScreen ) instance->currentRenderer->setupScreen();

	instance->events().notifyDraw();

    #ifdef TARGET_WIN32
    if (instance->currentRenderer->getBackgroundAuto() == false){
        // on a PC resizing a window with this method of accumulation (essentially single buffering)
        // is BAD, so we clear on resize events.
        if (nFramesSinceWindowResized < 3){
            instance->currentRenderer->clear();
        } else {
 //           if ( (instance->events().getFrameNum() < 3 || nFramesSinceWindowResized < 3) && bDoubleBuffered)    glutSwapBuffers();
 //           else  glFlush();
              glFlush();
        }
    } else {
        //if(bDoubleBuffered){
	//		glutSwapBuffers();
	//	} else{
	//		glFlush();
	//	}
              glFlush();
    }
    #else
		if (instance->currentRenderer->getBackgroundAuto() == false){
			// in accum mode resizing a window is BAD, so we clear on resize events.
			if (nFramesSinceWindowResized < 3){
				instance->currentRenderer->clear();
			}
		}
	//	if(bDoubleBuffered){
	//		glutSwapBuffers();
	//	} else{
	//		glFlush();
	//	}
              glFlush();
    #endif

	instance->currentRenderer->finishRender();

    nFramesSinceWindowResized++;

}

//------------------------------------------------------------
static void rotateMouseXY(ofOrientation orientation, int w, int h, int &x, int &y) {
	int savedY;
	switch(orientation) {
		case OF_ORIENTATION_180:
			x = w - x;
			y = h - y;
			break;

		case OF_ORIENTATION_90_RIGHT:
			savedY = y;
			y = x;
			x = w-savedY;
			break;

		case OF_ORIENTATION_90_LEFT:
			savedY = y;
			y = h - x;
			x = savedY;
			break;

		case OF_ORIENTATION_DEFAULT:
		default:
			break;
	}
}

//------------------------------------------------------------
void QtOpenGLEmbedWindow::mouse_cb(int button, int state, int x, int y) {
	rotateMouseXY(orientation, instance->getWidth(), instance->getHeight(), x, y);
    

//	switch(button){
//	case GLUT_LEFT_BUTTON:
//		button = OF_MOUSE_BUTTON_LEFT;
//		break;
//	case GLUT_RIGHT_BUTTON:
//		button = OF_MOUSE_BUTTON_RIGHT;
//		break;
//	case GLUT_MIDDLE_BUTTON:
//		button = OF_MOUSE_BUTTON_MIDDLE;
//		break;
//	}
    
	if (instance->events().getFrameNum() > 0){
//		if (state == GLUT_DOWN) {
//			instance->events().notifyMousePressed(x, y, button);
//		} else if (state == GLUT_UP) {
//			instance->events().notifyMouseReleased(x, y, button);
//		}
//
		buttonInUse = button;
	}
}

//------------------------------------------------------------
void QtOpenGLEmbedWindow::motion_cb(int x, int y) {
	rotateMouseXY(orientation, instance->getWidth(), instance->getHeight(), x, y);

	if (instance->events().getFrameNum() > 0){
		instance->events().notifyMouseDragged(x, y, buttonInUse);
	}

}

//------------------------------------------------------------
void QtOpenGLEmbedWindow::passive_motion_cb(int x, int y) {
	rotateMouseXY(orientation, instance->getWidth(), instance->getHeight(), x, y);

	if (instance->events().getFrameNum() > 0){
		instance->events().notifyMouseMoved(x, y);
	}
}

//------------------------------------------------------------
void QtOpenGLEmbedWindow::dragEvent(char ** names, int howManyFiles, int dragX, int dragY){

	// TODO: we need position info on mac passed through
	ofDragInfo info;
	info.position.x = dragX;
	info.position.y = instance->getHeight()-dragY;

	for (int i = 0; i < howManyFiles; i++){
		string temp = string(names[i]);
		info.files.push_back(temp);
	}

	instance->events().notifyDragEvent(info);
}


//------------------------------------------------------------
void QtOpenGLEmbedWindow::idle_cb(void) {
	instance->events().notifyUpdate();

//	glutPostRedisplay();
}


//------------------------------------------------------------
void QtOpenGLEmbedWindow::keyboard_cb(unsigned char key, int x, int y) {
	instance->events().notifyKeyPressed(key);
}

//------------------------------------------------------------
void QtOpenGLEmbedWindow::keyboard_up_cb(unsigned char key, int x, int y){
	instance->events().notifyKeyReleased(key);
}

//------------------------------------------------------
void QtOpenGLEmbedWindow::special_key_cb(int key, int x, int y) {
	instance->events().notifyKeyPressed(key | OF_KEY_MODIFIER);
}

//------------------------------------------------------------
void QtOpenGLEmbedWindow::special_key_up_cb(int key, int x, int y) {
	instance->events().notifyKeyReleased(key | OF_KEY_MODIFIER);
}

//------------------------------------------------------------
void QtOpenGLEmbedWindow::resize_cb(int w, int h) {
	windowW = w;
	windowH = h;

	instance->events().notifyWindowResized(w, h);

	nFramesSinceWindowResized = 0;
}

//------------------------------------------------------------
void QtOpenGLEmbedWindow::entry_cb(int state) {
//	if (state == GLUT_ENTERED){
//		instance->events().notifyMouseEntered(instance->events().getMouseX(), instance->events().getMouseY());
//	}else if (state == GLUT_LEFT){
//		instance->events().notifyMouseExited(instance->events().getMouseX(), instance->events().getMouseY());
//	}
}

//------------------------------------------------------------
void QtOpenGLEmbedWindow::exit_cb() {
	instance->events().notifyExit();
	instance->events().disable();
}

