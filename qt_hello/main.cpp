#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QLabel label("Hello, World!");
    label.setWindowTitle("Qt Hello World");
    label.resize(320, 240);
    label.setAlignment(Qt::AlignCenter);
    label.show();

    return app.exec();
}
