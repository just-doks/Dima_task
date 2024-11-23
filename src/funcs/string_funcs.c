#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../header.h"

int length(char* str) {
	char c;
	int i = 0;
	if (str == NULL) return i;
	while (c = *(str + i)) {
		if (c == '\0') break;
		i++;
	}
	return i;
}

int compare_strings(char* str1, char* str2) {
	int i = 0;
	int result = 0;
	int length1 = length(str1);
	int length2 = length(str2);
	int limit = (length1 > length2) ? length2 : length1;
	for (i = 0; i < limit + 1; i++) {
		if (*(str1 + i) == *(str2 + i)) continue;
		
		if (*(str1 + i) == '-' && *(str2 + i) >= '0' 
			&& *(str2 + i) <= '9') {
			result =  2;
			break;
		}
		if (*(str2 + i) == '-' && *(str1 + i) >= '0' 
			&& *(str1 + i) <= '9') {
			result =  1;
			break;
		}

		if (*(str1 + i) > *(str2 + i)) 
		{
			if (*(str2 + i + 1) == '\0'
				|| *(str2 + i + 1) == '-') 
			{
				result = 1;	
				break;
			} else if (*(str1 + i + 1) >= '0'
				&& *(str1 + i + 1) <= '9') 
			{
				result = 1;
				break;
			} else {
				result = 2;
				break;
			}
		} else
		if (*(str1 + i) < *(str2 + i)) 
		{
			if (*(str1 + i + 1) == '\0'
				|| *(str1 + i + 1) == '-') 
			{
				result = 2;	
				break;
			} else if (*(str2 + i + 1) >= '0'
				&& *(str2 + i + 1) <= '9') 
			{
				result = 2;
				break;
			} else {
				result = 1;
				break;
			}
		}
	}
	
	return result;
}

void shake_sort_data(char **str_arr, int size) {
	int i = 0;
	int left = 0;
	int right = size - 1;
	char *buf = calloc(260, sizeof(char));
	while (left <= right) {
		for (i = right; i > left; --i) {
			if (compare_strings(*(str_arr + i - 1), *(str_arr + i)) == 1) {
				
				strcpy(buf, *(str_arr + i - 1));
				strcpy(*(str_arr + i - 1), *(str_arr + i));
				strcpy(*(str_arr + i), buf);
				
			}
		}
		++left;
		for (i = left; i < right; ++i) {
			if (compare_strings(*(str_arr + i), *(str_arr + i + 1)) == 1) {
				
				strcpy(buf, *(str_arr + i));
				strcpy(*(str_arr + i), *(str_arr + i + 1));
				strcpy(*(str_arr + i + 1), buf);
				
			}
		}
		--right;
	}

	free(buf);
}

char* glue_strings(char* str1, char* str2, char* str) {
	int i = 0, j = 0;
	int l1 = length(str1);
	int l2 = length(str2);
	str = (char*) realloc (str, (l1 + l2 + 1) * sizeof(char));
	for (i = 0; i < l1; i++) {
		*(str + i) = *(str1 + i);
	}
	for (i = l1, j = 0; j < l2; i++, j++) {
		*(str + i) = *(str2 + j);
	}
	*(str + l1 + l2) = '\0';
	return str;
}

char* string_append(char* str1, char* str2) {
	int i = 0, j = 0;
	int l1 = length(str1);
	int l2 = length(str2);
	str1 = (char*) realloc (str1, (l1 + l2 + 1) * sizeof(char));
	for (i = l1, j = 0; j < l2; i++, j++) {
		*(str1 + i) = *(str2 + j);
	}
	*(str1 + l1 + l2) = '\0';
	return str1;
}

char* get_string_from_num(int num) {
	int i = 0;
	//if (num != 0) i = 1;
	int n = num;
	while (n != 0) {
		n = n / 10;
		i++;
	}
	printf("i = %d\n", i);
	char* str = (char*) calloc(i + 1, sizeof(char));
	int j = 0;
	for (j = i, i = 0; j > 0; j--, i++) {
		*(str + i) = (num / pow_i(10, j - 1) % 10 + '0');
	}
	*(str + i) = '\0';
	return str;
}

char* add_num_to_string (char* str, int num) {
	int i = 0, j = 0;
	int n = num;
	while (n != 0) {
		n = n / 10;
		i++;
	}
	if (num % 10 == 0) i++;
	str = (char*) realloc(str, (length(str) + i + 1) * sizeof(char) );
	for (j = i, i = length(str); j > 0; j--, i++) {
		*(str + i) = (num / pow_i(10, j - 1) % 10 + '0');
	}
	*(str + i) = '\0';
	return str;
}
char* set_string_from_num(char* str, int num) {
	int i = 0;
	//if (num != 0) i = 1;
	int n = num;
	while (n != 0) {
		n = n / 10;
		i++;
	}
	printf("i = %d\n", i);
	str = (char*) realloc(str, (i + 1) * sizeof(char) );
	//char* str = (char*) calloc(i + 1, sizeof(char));
	int j = 0;
	for (j = i, i = 0; j > 0; j--, i++) {
		*(str + i) = (num / pow_i(10, j - 1) % 10 + '0');
	}
	*(str + i) = '\0';
	return str;
}



char* string_new() {
	char* str = NULL;
	return str;
}

char* get_string_with_text_new (char* str) {
	int i = 0;
	char* string = (char*) calloc (length(str) + 1, sizeof(char));
	for (i = 0; i < length(str); i++) {
		*(string + i) = *(str + i);
	}
	*(string + i) = '\0';
	return string;
}

char *string_from_file_new(char* filename) {
	FILE *file;
	int file_size = 0;
	if (!(file = fopen(filename, "r"))) {
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	file_size = ftell(file);

	char *str = (char*) calloc (file_size, sizeof(char));
	fseek(file, 0, SEEK_SET);
	fread(str, sizeof(char), file_size, file);
	*(str + file_size - 1) = '\0';

	fclose(file);
	return str;
}

char *set_string_from_file(char* filename, char* str) {
	FILE *file;
	int file_size = 0;
	if (!(file = fopen(filename, "r"))) {
		free(str);
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	file_size = ftell(file);

	str = (char*) realloc (str, file_size * sizeof(char));
	fseek(file, 0, SEEK_SET);
	fread(str, sizeof(char), file_size, file);
	*(str + file_size - 1) = '\0';

	fclose(file);
	return str;
}

char* insert_letter_to_string(char* str, int pos, char letter) {
	int i = 0, j = 0;
	if (pos >= length(str)) return str;
	char* res = (char*) calloc(length(str) + 2, sizeof(char));
	for (i = 0; i < length(str); i++) {
		*(res + j++) = *(str + i);
		if (i == pos) *(res + j++) = letter;
	}
	*(res + j) = '\0';
	free(str);
	return res;
}

char* split_long_string_with_interval (char* str, int num) {
	int i = 0, j = 0;
	int limit = 0;
	if (length(str) > num) {
		for (i = num - 1; i > limit; i = i - 2) 
		{
			if (*(str + i) == ' ') 
			{
				*(str + i) = '\n';
				limit = i;
				i = i + 1 + num;
				if (i >= length(str)) break;
			}
			
			if (i == limit + 1)
			{
				str = insert_letter_to_string(str, limit + (num - 1) - 1, '-');
				str = insert_letter_to_string(str, limit + (num - 1), '\n');
				limit = limit + num + 1;
				i = limit + num + 1;
				if (i >= length(str)) break;
			}
			
		} // for
	}
	return str;
}