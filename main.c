#include <stdio.h>
#include <gtk-4.0/gtk/gtk.h>

static void click_cb(GtkButton *btn, GtkWindow *win) {
    gtk_window_destroy(win);
}

static void click1_cb(GtkButton *btn) {
    const char *s;

    s = gtk_button_get_label(btn);
    if (g_strcmp0(s, "Hello.") == 0) {
        gtk_button_set_label(btn, "Good-bye.");
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

static void app_activate2(GApplication *app) {
    GtkWidget *win;
    GtkWidget *tv;
    GtkWidget *scr;
    GtkTextBuffer *tb;
    gchar *text;

    text = "Once upon a time, there was an old man who was called Taketori-no-Okina. "
           "It is a japanese word that means a man whose work is making bamboo baskets.\n"
           "One day, he went into a hill and found a shining bamboo. "
           "\"What a mysterious bamboo it is!,\" he said. "
           "He cut it, then there was a small cute baby girl in it. "
           "The girl was shining faintly. "
           "He thought this baby girl is a gift from Heaven and took her home.\n"
           "His wife was surprised at his story. "
           "They were very happy because they had no children. ";

    win = gtk_application_window_new((GTK_APPLICATION(app)));
    gtk_window_set_title(GTK_WINDOW(win), "Taketori");
    gtk_window_set_default_size(GTK_WINDOW(win), 400, 300);

    scr = gtk_scrolled_window_new();
    gtk_window_set_child(GTK_WINDOW(win), scr);

    tv = gtk_text_view_new();
    tb = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv));
    gtk_text_buffer_set_text(tb, text, -1);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(tv), GTK_WRAP_WORD_CHAR);

    //gtk_window_set_child(GTK_WINDOW(win), tv);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scr), tv);

    gtk_window_present(GTK_WINDOW(win));
}

static void app_activate3(GApplication *app) {
    g_printerr("You need a filename argument.\n");
}

static void app_open(GApplication *app, GFile ** files, int n_files, char *hint) {
    GtkWidget *win;
    GtkWidget *scr;
    GtkWidget *tv;
    GtkTextBuffer *tb;
    char *contents;
    gsize length;
    char *filename;
    GError *err = NULL;

    win = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_default_size(GTK_WINDOW(win), 400, 300);

    scr = gtk_scrolled_window_new();
    gtk_window_set_child(GTK_WINDOW(win), scr);

    tv = gtk_text_view_new();
    tb = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv));
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(tv), GTK_WRAP_CHAR);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(tv), FALSE);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scr), tv);

    if (g_file_load_contents(files[0], NULL, &contents, &length, NULL, &err)) {
        gtk_text_buffer_set_text(tb, contents, length);
        g_free(contents);
        if ((filename = g_file_get_basename(files[0])) != NULL) {
            gtk_window_set_title(GTK_WINDOW(win), filename);
            g_free(filename);
        }
        gtk_window_present(GTK_WINDOW(win));
    } else {
        g_printerr("%s.\n", err->message);
        g_error_free(err);
        gtk_window_destroy(GTK_WINDOW(win));
    }
}

static void app_open2(GApplication *app, GFile ** files, gint n_files, gchar *hint) {
    GtkWidget *win;
    GtkWidget *nb;
    GtkWidget *lab;
    GtkNotebookPage *nbp;
    GtkWidget  *scr;
    GtkWidget  *tv;
    GtkTextBuffer *tb;
    char *contents;
    gsize length;
    char *filename;
    int i;
    GError  *err = NULL;

    win = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(win), "File viewer");
    gtk_window_set_default_size(GTK_WINDOW(win), 600, 400);
    nb = gtk_notebook_new();
    gtk_window_set_child(GTK_WINDOW(win), nb);

    for (i = 0; i < n_files; i++) {
        if (g_file_load_contents(files[i], NULL, &contents, &length, NULL, &err)) {
            scr = gtk_scrolled_window_new();
            tv = gtk_text_view_new();
            tb = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv));
            gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(tv), GTK_WRAP_WORD_CHAR);
            gtk_text_view_set_editable(GTK_TEXT_VIEW(tv), FALSE);
            gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scr), tv);

            gtk_text_buffer_set_text(tb, contents, length);
            g_free(contents);
            if ((filename = g_file_get_basename(files[i])) != NULL) {
                lab = gtk_label_new(filename);
                g_free(filename);
            } else {
                lab = gtk_label_new("");
            }
            gtk_notebook_append_page(GTK_NOTEBOOK(nb), scr, lab);
            nbp = gtk_notebook_get_page(GTK_NOTEBOOK(nb), scr);
            g_object_set(nbp, "tab-expand", TRUE, NULL);
        } else  {
            g_printerr("%s\n.", err->message);
            g_clear_error(&err);
        }
    }
    if (gtk_notebook_get_n_pages(GTK_NOTEBOOK(nb)) > 0) {
        gtk_window_present(GTK_WINDOW(win));
    } else {
        gtk_window_destroy(GTK_WINDOW(win));
    }
}

int main(int argc, char* argv[]) {
    GtkApplication *app;
    int stat;

    app = gtk_application_new("com.github.ToshioCp.tfv3", G_APPLICATION_HANDLES_OPEN);
    g_signal_connect(app, "activate", G_CALLBACK(app_activate3), NULL);
    g_signal_connect(app, "open", G_CALLBACK(app_open2), NULL);
    stat = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return stat;
}
