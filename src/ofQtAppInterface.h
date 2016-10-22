class ofGLWindowSettings;
class QtOpenGLEmbedWindow;
class QApplication;
class QMainWindow;
namespace Ui {
    class openframeworks;
}
class QtOpenGLEmbedWindow;
namespace ofqt {
    class ofqtGlWidget;
}

class ofQtAppInterface{
    private:
    QApplication *app; //Qt app 
    QMainWindow *mainWindow;
    Ui::openframeworks *ui;
    QtOpenGLEmbedWindow *ofWindow;
    public:
    ofqt::ofqtGlWidget *embedWindow;
    ofQtAppInterface(int argc, char *argv[]);
    ~ofQtAppInterface();
    void setupUi();
    ofqt::ofqtGlWidget *createEmbedWindow(QtOpenGLEmbedWindow *ofWindow_ptr);
    void show();
    int exec();
};
