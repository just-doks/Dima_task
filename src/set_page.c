#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "header.h"


int set_page (GtkStack* stack, char* dir) {
// 1 //
	// pack cleared 
	Package* pack = pack_new();

	if (scan_dir_set_pack(pack, dir) == -1) 
	{
		perror("No such directory\n");
		return -2;
	}
	// files cleared 
	char** files = (char**) pack->list;
	int f_size = pack->size;

	set_pack_with_numbers(pack, "picture-", files, f_size);
	// pic_nums cleared 
	int* pic_nums = (int*) pack->list;
	int p_size = pack->size; 
	shake_sort_int(pic_nums, p_size);

	set_pack_with_numbers(pack, "text-", files, f_size);
	// text_nums cleared 
	int* text_nums = (int *) pack->list;
	int t_size = pack->size;
	shake_sort_int(text_nums, t_size);
///// 1

// 2 //
	GtkWidget *scrolledWindow;
	GtkWidget *vBox;
	GtkWidget *label;
	GtkWidget **pictures;
	GtkWidget **frames;
	GtkWidget **textViews;
	GtkTextBuffer *textBuf;
	GdkPixbuf* pixbuf;
	
	vBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 20);
	gtk_box_set_baseline_position (GTK_BOX (vBox), GTK_BASELINE_POSITION_CENTER);;
	gtk_widget_set_margin_top(vBox, 20);

	// path cleared
	char* path = string_new();
//// 2

// 3 //
	int i = 0, p = 0, t = 0;
	int p_max = *(pic_nums + p_size - 1);
	int t_max = *(text_nums + t_size - 1);
	// clear text 6
	char* text = string_new();

	//### label #################################
	path = glue_strings(dir, "/label.txt", path);
	// title cleared
	char* title = string_from_file_new (path);
	if (title == NULL) title = get_string_with_text_new ("-");
	label = gtk_label_new (title);
	char* markup = g_markup_printf_escaped("<b><span font='30px'>%s</span></b>", title);
	gtk_label_set_markup (GTK_LABEL (label), markup);

	gtk_label_set_xalign (GTK_LABEL(label), 0.05);
	gtk_box_append (GTK_BOX (vBox), label);
	g_free(markup);
	//###_____________________________________###
	//###########################################

	pictures = (GtkWidget**) calloc (p_size, sizeof(GtkWidget*));

	textViews = (GtkWidget**) calloc (t_size, sizeof(GtkWidget*));

	frames = (GtkWidget**) calloc (t_size, sizeof(GtkWidget*));


	for (i = 0, p = 0, t = 0; i <= ((p_max > t_max) ? p_max : t_max); i++) {

		if (*(pic_nums + p) == i && p < p_size) {
			//### picture #################################
			path = glue_strings(dir, "/picture-", path);
			path = add_num_to_string(path, *(pic_nums + p));
			path = string_append(path, ".jpg");
			pixbuf = gdk_pixbuf_new_from_file_at_scale(path, 1000, 1000, TRUE, NULL);
			*(pictures + p) = gtk_picture_new_for_pixbuf(pixbuf);
			gtk_picture_set_can_shrink(GTK_PICTURE (*(pictures + p)), FALSE);
			gtk_box_append (GTK_BOX (vBox), *(pictures + p));
			p++;
			//###_____________________________________###
			//###########################################
		}

		if (*(text_nums + t) == i && t < t_size) {
			//### text #################################
			path = glue_strings(dir, "/text-", path);
			path = add_num_to_string(path, *(text_nums + t));
			path = string_append(path, ".txt");
			text = set_string_from_file (path, text);
			if (text == NULL) text = get_string_with_text_new ("\0");

			*(textViews + t) = gtk_text_view_new();
			textBuf = gtk_text_view_get_buffer (GTK_TEXT_VIEW (*(textViews + t)));
			gtk_text_buffer_set_text (textBuf, text, -1);
			
			gtk_text_view_set_left_margin (GTK_TEXT_VIEW(*(textViews + t)), 20);
			gtk_text_view_set_right_margin (GTK_TEXT_VIEW(*(textViews + t)), 20);
			gtk_text_view_set_top_margin (GTK_TEXT_VIEW(*(textViews + t)), 20);
			gtk_text_view_set_bottom_margin (GTK_TEXT_VIEW(*(textViews + t)), 20);
			

			gtk_text_view_set_editable(GTK_TEXT_VIEW (*(textViews + t)), FALSE);
			gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW (*(textViews + t)), FALSE);
			gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (*(textViews + t)), GTK_WRAP_WORD_CHAR);

			gtk_text_view_set_monospace(GTK_TEXT_VIEW (*(textViews + t)), TRUE);

			*(frames + t) = gtk_frame_new (NULL);
			gtk_frame_set_child (GTK_FRAME(*(frames + t)), *(textViews + t));

			gtk_box_append (GTK_BOX (vBox), *(frames + t));
			t++;
			//###_____________________________________###
			//###########################################
		}
	}
//// 3

// 4 //
	scrolledWindow = gtk_scrolled_window_new();
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolledWindow), vBox);

	split_long_string_with_interval(title, 50);
	gtk_stack_add_titled(stack, scrolledWindow, title, title);

	free(pack);
	free_2d_array (PACK_2D_ARRAY (files), f_size);
	free(pic_nums);
	free(text_nums);
	free(path);
	free(text);
	free(title);

	free(pictures);
	free(textViews);
	free(frames);
	return 0;

}