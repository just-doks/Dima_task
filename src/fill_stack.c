#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "header.h"

int fill_stack(GtkStack* stack) {
	int i = 0;
	char *data_path = "../Data/";
	Package* pack = pack_new();
	scan_dir_set_pack(pack, data_path);
	if (pack == NULL) 
	{
		perror("Package failed\n");
		return -1;
	}
	char** dir_list = (char**) pack->list;
	int list_size = pack->size;
	char* new_path = string_new();
	for (i = 0; i < list_size; i++) 
	{
		new_path = glue_strings(data_path, dir_list[i], new_path);
		set_page(stack, new_path);
	}
	free_2d_array(PACK_2D_ARRAY (dir_list), list_size);
	free(new_path);
	free(pack);
	return 0;
}