#include <stdio.h>
#include <gtk-4.0/gtk/gtk.h>

static void app_activate(GApplication *app, gpointer *user_data) {
    g_print("GtkApplication is activated!");

    GtkWidget *win;
    win = gtk_window_new();
    gtk_window_set_application(GTK_WINDOW(win), GTK_APPLICATION(app));
    gtk_window_present(GTK_WINDOW(win));
}

int main(int argc, char* argv[]) {
    GtkApplication *app;
    int stat;

    app = gtk_application_new("com.github.ToshioCp.pr1", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);
    stat = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return stat;
}
