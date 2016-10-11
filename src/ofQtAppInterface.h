
class QApplication;
class QMainWindow;
namespace Ui {
    class MainWindow;
}
class QtOpenGLEmbedWindow;

class ofQtAppInterface{
    private:
    QApplication *app; //Qt app 
    QMainWindow *mainWindow;
    QtOpenGLEmbedWindow *embedWidget;
    Ui::MainWindow *ui;
    public:
    ofQtAppInterface(int argc, char *argv[], QtOpenGLEmbedWindow* ofWindow=NULL);
    ~ofQtAppInterface();
    int exec();
};
