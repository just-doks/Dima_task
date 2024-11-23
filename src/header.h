#ifndef TEST_HEADER_H
#define TEST_HEADER_H

#include <gtk/gtk.h>

#define PACK(X) ((void*)X)
#define PACK_2D_ARRAY(X) ((void**)X)

typedef struct {
	void *list;
	int size;
} Package;

// pack_funcs.c
	Package* pack_new(void);

	Package* get_pack_with_numbers_new(char* str, char** list, int size);

	void set_pack_with_numbers(Package* pack, char* str, char** list, int size);

	int scan_dir_set_pack(Package* pack, char* path);
//// pack_funcs.c //

// string_funcs.c
	int length(char* str);

	int compare_strings(char* str1, char* str2);

	void shake_sort_data(char **str_arr, int size);

	char* glue_strings(char* str1, char* str2, char* str);

	char* string_append(char* str1, char* str2);

	char* get_string_from_num(int num);

	char* add_num_to_string (char* str, int num);

	char* set_string_from_num(char* str, int num);

	char* string_new();

	char* get_string_with_text_new (char* str);

	char *string_from_file_new(char* filename);

	char *set_string_from_file(char* filename, char* str);

	char* insert_letter_to_string(char* str, int pos, char letter);

	char* split_long_string_with_interval (char* str, int num);
//// string_funcs.c //

// other_funsc.c
	void free_2d_array (void **arr, int size);

	void shake_sort_int (int *arr, int size);

	int pow_i(int a, unsigned int b);
//// other_funcs.c //

// set_page.c
	int set_page (GtkStack* stack, char* dir);
//// set_page.c

// fill_stack.c
	int fill_stack(GtkStack* stack);
//// fill_stack.c

#endif // TEST_HEADER_H
