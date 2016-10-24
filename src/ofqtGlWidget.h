#ifndef OFQTGLWIDGET_H
#define OFQTGLWIDGET_H 1

#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLFormat>
#include <QtCore/QTimer>
#include <QtCore/QSize>
#include <QtGui/QResizeEvent>
//#include <QGLShaderProgram>
//#include "ofqtCamera.h"

class ofQtAppInterface;

namespace ofqt {

class ofqtGlWidget : public QGLWidget
{
    public:
        ofqtGlWidget(QGLFormat format);
        ~ofqtGlWidget() {}

        /* Static function to create a new instance of the wanted OpenGL
         * context.
         */
        static QGLFormat createOpenGLContextFormat();

        /* Returns a reference to the current camera object that
         * is associated with the class instance.
         */
        //ofqtCamera& getCurrentCamera() const;

        void setAppInterface(ofQtAppInterface* appInterface_ptr);

    protected:
        /* Initializes the OpenGL rendering context for the current widget
         * instance.
         */
        void initializeGL();

        /* Renders the OpenGL scene for the current widget instance.
         */
        void paintGL();

        /* Resets the OpenGL rendering context for widget instance when it
         * get resized. Note that the function is also called when the
         * widget is first displayed, as it gets a resize event automatically.
         */
        void resizeGL();
        void resizeEvent(QResizeEvent * event);

    private:
        QTimer _internal_timer;
        ofQtAppInterface* appInterface;
        //ofqtCamera * _camera;
        //QGLShaderProgram * _program;
};

};

#endif /* OFQTGLWIDGET_H */
