#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow window;
    QWidget *centralWidget = new QWidget();
    window.setCentralWidget(centralWidget);
    window.setWindowTitle("Order Manager");
    window.resize(800, 600);
    window.show();

    return app.exec();
}