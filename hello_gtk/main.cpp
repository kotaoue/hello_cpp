#include <gtk/gtk.h>

static void activate(GtkApplication *app, gpointer /*user_data*/)
{
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Hello World");
    gtk_window_set_default_size(GTK_WINDOW(window), 320, 240);

    GtkWidget *label = gtk_label_new("Hello, World!");

#if GTK_MAJOR_VERSION >= 4
    gtk_window_set_child(GTK_WINDOW(window), label);
    gtk_window_present(GTK_WINDOW(window));
#else
    gtk_container_add(GTK_CONTAINER(window), label);
    gtk_widget_show_all(window);
#endif
}

int main(int argc, char **argv)
{
#if GTK_MAJOR_VERSION >= 4
    GtkApplication *app = gtk_application_new("org.example.helloworld",
                                              G_APPLICATION_DEFAULT_FLAGS);
#else
    GtkApplication *app = gtk_application_new("org.example.helloworld",
                                              G_APPLICATION_FLAGS_NONE);
#endif

    g_signal_connect(app, "activate", G_CALLBACK(activate), nullptr);

    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
