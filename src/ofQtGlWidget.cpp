#include <iostream>
//#include <QGLShader>

#include "ofQtAppInterface.h"
#include "ofQtGlWidget.h"

using namespace ofQt;

ofQtGlWidget::ofQtGlWidget(QGLFormat format) : QGLWidget(format)
{
    std::cout << "aqui 0" << std::endl;
    /* Connect the internal timer to the method that will control the widget
     * redraw call.
     */
    connect(&_internal_timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    std::cout << "aqui 1" << std::endl;

    /* Set the refresh rate of the OpenGL window to be equal to
     * the monitor refresh rate, i.e., VSync.
     */
    if(format.swapInterval() == -1) {
        std::cout << "VSync not available, using an aproximate 60 fps rate." << std::endl;
        /* For now leave the constant 17 as it is aproximatly equal to the number
         * of miliseconds available for a frame when the application is running at
         * 60 fps, but replace it later for a function to be more clear what we are
         * doing here.
         */
        _internal_timer.setInterval(17);
    } else {
        /* Using an interval equal to 0 in the timer we guarantee that the timer will
         * eventually synchronize with the monitor refresh rate.
         */
        _internal_timer.setInterval(0);
    }

    /* Perform other initializations here */

    /* Initialize the camera for the current widget */
    //_camera = new ofQtCamera();
    //_program = new QGLShaderProgram();

    /* end */

    /* Start running the timer. */
    _internal_timer.start();

    setMouseTracking(true);

}


QGLFormat ofQtGlWidget::createOpenGLContextFormat()
{
    QGLFormat format;

    /* We always want a context with version 3.0 to get all the functionalities
     * of OpenGL 3.0+
     */
    format.setVersion(3, 0);

    return format;
}


//ofQtCamera& ofQtGlWidget::getCurrentCamera() const
//{
//    return *_camera;
//}


void ofQtGlWidget::initializeGL()
{
    /* Set the clear color to complete black.
     */
//    glClearColor(0.0, 0.0, 0.0, 0.0);

    /* Enable depth testing, as it is required for the
     * corrent rendering behaviour of the mesh.
     */
    glEnable(GL_DEPTH_TEST);

    /* Compile and link the shader program
     */
    //if(!_program->addShaderFromSourceFile(QGLShader::Vertex, "shaders/basic.vert")) {
    //    std::cout << "Unable to compile Vertex shader." << std::endl;
    //    return;
    //}

    //if(!_program->addShaderFromSourceFile(QGLShader::Fragment, "shaders/basic.frag")) {
    //    std::cout << "Unable to compile Fragment shader." << std::endl;
    //    return;
    //}

    //if(!_program->link()) {
    //    std::cout << "Unable to link shader program." << std::endl;
    //    return;
    //}
}


void ofQtGlWidget::paintGL()
{
    //glClear(GL_COLOR_BUFFER_BIT);
    appInterface->update();
}


void ofQtGlWidget::resizeGL()
{
//    getCurrentCamera().setCameraAspect(width() / height());
}

void ofQtGlWidget::resizeEvent(QResizeEvent * event){
    const QSize& size = event->size();
    appInterface->of_resize(
        size.width(),
        size.height()
    );
}

//void ofQtGlWidget::closeEvent(QCloseEvent *event){
//    appInterface->of_close();
//    std::cout << "ofApp closed." << std::endl;
//    event->accept();
//}

void ofQtGlWidget::mouseMoveEvent(QMouseEvent * event){
    appInterface->of_mouse_move(
        event->x(),
        event->y()
    );
}

void ofQtGlWidget::mousePressEvent(QMouseEvent * event){
    Qt::MouseButton button = event->button();
    appInterface->of_mouse_button(
        button, 1,
        event->x(),
        event->y()
    );
}

void ofQtGlWidget::mouseReleaseEvent(QMouseEvent * event){
    Qt::MouseButton button = event->button();
    appInterface->of_mouse_button(
        button, 2,
        event->x(),
        event->y()
    );
}

void ofQtGlWidget::setAppInterface(ofQtAppInterface* appInterface_ptr){
    appInterface = appInterface_ptr;
};
