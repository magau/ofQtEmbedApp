#ifndef OFQTGLWIDGET_H
#define OFQTGLWIDGET_H 1

#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLFormat>
#include <QtCore/QTimer>
//#include <QGLShaderProgram>
//#include "ofqtCamera.h"


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

    private:
        QTimer _internal_timer;
        //ofqtCamera * _camera;
        //QGLShaderProgram * _program;
};

};

#endif /* OFQTGLWIDGET_H */
