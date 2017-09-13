#pragma once
//#ifndef OFQTGLWIDGET_H
//#define OFQTGLWIDGET_H 1

#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLFormat>
#include <QtCore/QTimer>
#include <QtCore/QSize>
#include <QtCore/QPoint>
#include <QtGui/QResizeEvent>
#include <QtGui/QMouseEvent>
//#include <QGLShaderProgram>
//#include "ofQtCamera.h"

class ofQtAppInterface;

namespace ofQt {

class ofQtGlWidget : public QGLWidget
{
    public:
        ofQtGlWidget(QGLFormat format);
        ~ofQtGlWidget() {}

        /* Static function to create a new instance of the wanted OpenGL
         * context.
         */
        static QGLFormat createOpenGLContextFormat();

        /* Returns a reference to the current camera object that
         * is associated with the class instance.
         */
        //ofQtCamera& getCurrentCamera() const;

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
        void mouseMoveEvent(QMouseEvent * event);

    private:
        QTimer _internal_timer;
        ofQtAppInterface* appInterface;
        //ofQtCamera * _camera;
        //QGLShaderProgram * _program;
};

};

//#endif /* OFQTGLWIDGET_H */
