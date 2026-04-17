#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

int main(int argc, char *argv[])
{
    Fl_Window *window = new Fl_Window(640, 480, "Hello World");
    int box_width = 240;
    int box_height = 120;
    Fl_Box *box = new Fl_Box(window->w() / 2 - box_width / 2, window->h() / 2 - box_height / 2, box_width, box_height, "Hello, FLTK!");
    box->labelsize(36);
    box->box(FL_FLAT_BOX);
    box->color(FL_BLACK);
    box->labelcolor(FL_WHITE);
    window->end();
    window->show(argc, argv);
    int ret = Fl::run();
    delete window;
    return ret;
}
