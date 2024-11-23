#include <gtk/gtk.h>
#include "header.h"

static void main_window (GtkWidget* widget, gpointer data) {
	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *stack;
	GtkWidget *stackSidebar;

	window = gtk_application_window_new(GTK_APPLICATION (data));
	gtk_window_set_title (GTK_WINDOW (window), "main");
	gtk_window_set_default_size (GTK_WINDOW (window), 1600, 900);
	gtk_window_set_resizable(GTK_WINDOW (window), TRUE);
	gtk_widget_show(window);

	grid = gtk_grid_new();
	gtk_grid_set_row_homogeneous (GTK_GRID(grid), TRUE);
	gtk_grid_set_column_homogeneous (GTK_GRID(grid), TRUE);

	stack = gtk_stack_new();
	fill_stack(GTK_STACK(stack));

	stackSidebar = gtk_stack_sidebar_new();
	gtk_stack_sidebar_set_stack(GTK_STACK_SIDEBAR (stackSidebar), GTK_STACK(stack));

	gtk_grid_attach(GTK_GRID(grid), stackSidebar, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), stack, 1, 0, 3, 1);

	gtk_window_set_child (GTK_WINDOW (window), grid);
}

static void start_window (GApplication *app, gpointer *user_data) {
	GtkWidget *window;
	GtkWidget* box;
	GtkWidget *pic;
	GdkPixbuf *pixbuf;

	window = gtk_application_window_new(GTK_APPLICATION (app));
	gtk_window_set_title (GTK_WINDOW (window), "start");
	gtk_window_set_default_size (GTK_WINDOW (window), 1000, 800);
	gtk_window_set_resizable(GTK_WINDOW (window), FALSE);

	box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 50);
  	gtk_widget_set_halign (box, GTK_ALIGN_CENTER);
  	gtk_widget_set_valign (box, GTK_ALIGN_START);
  	gtk_widget_set_margin_top(box, 50);

  	pixbuf = gdk_pixbuf_new_from_file_at_size("../Data/0/picture-1.jpg", 640, 360, NULL);

	pic = gtk_picture_new_for_pixbuf(pixbuf);

	GtkWidget *bttn;
	bttn = gtk_button_new();
	gtk_button_set_child(GTK_BUTTON (bttn), pic);

	g_signal_connect (bttn, "clicked", G_CALLBACK (main_window), app);
	g_signal_connect_swapped (bttn, "clicked", G_CALLBACK (gtk_window_destroy), window);

	gtk_box_append(GTK_BOX(box), bttn);

	gtk_window_set_child (GTK_WINDOW (window), box);

	gtk_widget_show(window);
}

int main (int argc, char * argv[]) {
	GtkApplication *app;
	int status;

	app = gtk_application_new ("Dima-s.application", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (start_window), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);
	
	return status;
}

