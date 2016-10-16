class ofGLWindowSettings;
class QApplication;
class QMainWindow;
namespace Ui {
    class MainWindow;
}
class QtOpenGLEmbedWindow;
namespace ofqt {
    class ofqtGlWidget;
}

class ofQtAppInterface{
    private:
    QApplication *app; //Qt app 
    QMainWindow *mainWindow;
    ofqt::ofqtGlWidget *embedWindow;
    Ui::MainWindow *ui;
    const ofGLWindowSettings *windowSettings;
    public:
    ofQtAppInterface(int argc, char *argv[]);
    ~ofQtAppInterface();
    int exec();
    void setupUi();
    void show();
    ofqt::ofqtGlWidget *createEmbedWindow(const ofGLWindowSettings *settings);
};
