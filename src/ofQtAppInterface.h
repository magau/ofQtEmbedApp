#pragma once

class ofApp;
class ofGLWindowSettings;
class QApplication;
class QMainWindow;

class ofAppQGLEmbedWindow;
namespace Ui {
    class mainWindow;
}
namespace ofQt {
    class ofQtGlWidget;
}
using namespace ofQt;

class ofQtAppInterface{
    private:
    QApplication *qt_app; //Qt app 
    ofApp *of_app; //openframeworks app 
    QMainWindow *mainWindow;
    Ui::mainWindow *ui;
    ofAppQGLEmbedWindow *ofWindow;
    public:
    ofQtGlWidget *embedWindow;
    ofQtAppInterface(int argc, char *argv[]);
    ~ofQtAppInterface();
    void setupUi();
    ofQtGlWidget *createEmbedWindow(ofAppQGLEmbedWindow *ofWindow_ptr);
    void setup();
    void update();
    int exec();
    void of_resize(int w, int h);
    void of_mouse_move(int x, int y);
    void of_mouse_button(int button, int state, int x, int y);
    std::pair<int,int> get_window_pos();
    int get_width();
    int get_height();
};
