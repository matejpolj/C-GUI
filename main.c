#include <stdio.h>
#include <gtk-4.0/gtk/gtk.h>

static void click_cb(GtkButton *btn, GtkWindow *win) {
    gtk_window_destroy(win);
}

static void click1_cb(GtkButton *btn) {
    const char *s;

    s = gtk_button_get_label(btn);
    if (g_strcmp0(s, "Hello.") == 0) {
        gtk_button_set_label(btn, "Goob-bye.");
    } else {
        gtk_button_set_label(btn, "Hello.");
    }
}

static void click2_cb(GtkButton *btn, GtkWindow *win) {
    gtk_window_destroy(win);
}

static void app_activate(GApplication *app, gpointer *user_data) {
    g_print("GtkApplication is activated!");

    GtkWidget *win;
    GtkWidget *lab;
    GtkWidget *btn;

    win = gtk_window_new();
    gtk_window_set_application(GTK_WINDOW(win), GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(win), "pr4");
    gtk_window_set_default_size(GTK_WINDOW(win), 400, 300);

//    lab = gtk_label_new("Hello.");
//    gtk_window_set_child(GTK_WINDOW(win), lab);

    btn = gtk_button_new_with_label("Click me!");
    gtk_window_set_child(GTK_WINDOW(win), btn);
    g_signal_connect(btn, "clicked", G_CALLBACK(click_cb), win);

    gtk_window_present(GTK_WINDOW(win));
}

static void app_activate1(GApplication *app) {
    GtkWidget *win;
    GtkWidget *box;
    GtkWidget *btn1;
    GtkWidget *btn2;

    win = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(win), "lb4");
    gtk_window_set_default_size(GTK_WINDOW(win), 400, 300);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_set_homogeneous(GTK_BOX(box), TRUE);
    gtk_window_set_child(GTK_WINDOW(win), box);

    btn1 = gtk_button_new_with_label("Hello.");
    g_signal_connect(btn1, "clicked", G_CALLBACK(click1_cb), NULL);

    btn2 = gtk_button_new_with_label("Close.");
    g_signal_connect(btn2, "clicked", G_CALLBACK(click2_cb), win);

    gtk_box_append(GTK_BOX(box), btn1);
    gtk_box_append(GTK_BOX(box), btn2);

    gtk_window_present(GTK_WINDOW(win));


}

int main(int argc, char* argv[]) {
    GtkApplication *app;
    int stat;

    app = gtk_application_new("com.github.ToshioCp.pr1", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(app_activate1), NULL);
    stat = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return stat;
}
