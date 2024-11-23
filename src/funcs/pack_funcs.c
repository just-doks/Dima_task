#include <stdio.h>
#include <dirent.h> // DIR*, struct dirent*, opendir, rewinddir, readdirr, closedir
#include <stdlib.h> // calloc, free
#include <string.h> // strcmp, strcpy

#include "../header.h" // Package

Package* pack_new() {
	Package* pack = (Package*) calloc(1, sizeof(Package));
	//pack->list = NULL;
	//pack->size = 0;
	return pack;
}

Package* get_pack_with_numbers_new(char* str, char** list, int size) {
	int i = 0;
	int amount = 0;
	int* numSet = (int*) calloc(0, sizeof(int));
	for (i = 0; i < size; i++) {
		if (length(list[i]) < length(str)) continue;
		if (strncmp(str, list[i], length(str)) == 0) {
			amount ++;
			numSet = (int*) realloc(numSet, amount * sizeof(int));
			*(numSet + amount - 1) = list[i][length(str)] - '0'; 
		}
	}
	Package* pack = (Package*) calloc(1, sizeof(Package));
	pack->list = PACK(numSet);
	pack->size = amount;
	return pack;
}

void set_pack_with_numbers(Package* pack, char* str, char** list, int size) {
	int i = 0;
	int amount = 0;
	int* numSet = (int*) calloc(0, sizeof(int));
	for (i = 0; i < size; i++) {
		if (length(list[i]) < length(str)) continue;
		if (strncmp(str, list[i], length(str)) == 0) {
			amount ++;
			numSet = (int*) realloc(numSet, amount * sizeof(int));
			*(numSet + amount - 1) = list[i][length(str)] - '0'; 
		}
	}
	pack->list = PACK(numSet);
	pack->size = amount;
}

int scan_dir_set_pack(Package* pack, char* path) {
	struct dirent *entry;
	DIR *dir;
	long int files_amount = 0;
	char **dir_files;
	int i = 0;

	// открываем директорию Data с данными для страниц
	dir = opendir(path);
	// если не открылась, программа завершится с ошибкой
	if (dir == NULL) {
		perror("Opendir\n");
		return -1;
	}
	// считаем количество файлов внутри директории, пропуская специальные файлы
	// точка означает текущий каталог, две - предыдущий
	// используются для навигации и запуска исполняемых файлов в каталоге через терминал
	while (entry = readdir(dir)) {
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
		files_amount++;
	}

	// выделяем память под имена найденных файлов (каталогов)
	dir_files = (char**) calloc (files_amount, sizeof(char*));
	for (i = 0; i < files_amount; i++) {
		dir_files[i] = (char*) calloc (260, sizeof(char));
	}
	files_amount = 0;
	// перемещаем указатель в потоке на начало
	rewinddir(dir);

	// заполняем строковый массив данными из потока
	while (entry = readdir(dir)) {
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
		strcpy(dir_files[files_amount], entry->d_name);
		files_amount++;
	}

	// сортируем каталоги по реализованному методу
	shake_sort_data(dir_files, files_amount);
	
	closedir(dir);

	pack->list = PACK(dir_files);
	pack->size = files_amount;

	return 0;
}