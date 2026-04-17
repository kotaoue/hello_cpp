#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QLabel label("Hello, World!");
    label.setWindowTitle("Hello World");
    label.resize(640, 480);
    label.setAlignment(Qt::AlignRight | Qt::AlignBottom);
    label.show();

    return app.exec();
}
