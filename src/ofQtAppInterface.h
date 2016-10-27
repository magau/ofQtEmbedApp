#pragma once

class ofGLWindowSettings;
class ofAppQGLEmbedWindow;
class QApplication;
class QMainWindow;
namespace Ui {
    class mainWindow;
}
class ofAppQGLEmbedWindow;
namespace ofQt {
    class ofQtGlWidget;
}

class ofQtAppInterface{
    private:
    QApplication *app; //Qt app 
    QMainWindow *mainWindow;
    Ui::mainWindow *ui;
    ofAppQGLEmbedWindow *ofWindow;
    public:
    ofQt::ofQtGlWidget *embedWindow;
    ofQtAppInterface(int argc, char *argv[]);
    ~ofQtAppInterface();
    void setupUi();
    ofQt::ofQtGlWidget *createEmbedWindow(ofAppQGLEmbedWindow *ofWindow_ptr);
    void show();
    int exec();
    void resize_cb_interface(int w, int h);
};
