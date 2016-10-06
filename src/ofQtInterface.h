class QApplication;
class QMainWindow;
class QX11EmbedContainer;
namespace Ui {
    class MainWindow;
}
class QtEmbedGlutWindow;

class ofQtAppInterface{
    private:
    QApplication *app; //Qt app 
    QMainWindow *mainWindow;
    QX11EmbedContainer *embedWidget;
    Ui::MainWindow *ui;
    public:
    ofQtAppInterface(int argc, char *argv[], QtEmbedGlutWindow* ofWindow=NULL);
    ~ofQtAppInterface();
    int exec();
};
