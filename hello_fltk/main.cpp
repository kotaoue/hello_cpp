#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

int main(int argc, char *argv[])
{
    Fl_Window *window = new Fl_Window(640, 480, "Hello World");
    Fl_Box *box = new Fl_Box(0, 0, 640, 480, "Hello, World!");
    box->labelsize(36);
    window->end();
    window->show(argc, argv);
    return Fl::run();
}
