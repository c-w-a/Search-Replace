
// COMP348 A1 -- Chris Anglin 40216346

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>

// this function cats file name onto directory path to create filepath
char* pathName(char *dir, char *ent) {

	// calloc for char array 
	char *path = (char *) calloc(strlen(dir) + strlen(ent) + 2, sizeof(char));
	
	// initialize char array values to null
	for (int i = 0; i < strlen(path); i++){
		path[i] = '\0';
	}

	// copy directory path, then cat "/", then cat filename
	strcpy(path,dir);
	strcat(path, "/");
	strcat(path, ent);
	strcat(path, "\0");

	return path;
}

// this function checks if a given file is a .txt file
bool isTxt(char *fn) {
	
	// variable to hold length of filename
	int length = strlen(fn);
	
	// if length is 4 or less, can't be .txt (because ".txt" is of length 4 itself), 
	if (length < 5) return false;
	
	// create char array which contains last 4 chars of filename
	char check[5];
	check[0] = fn[length - 4];
	check[1] = fn[length - 3];
	check[2] = fn[length - 2];
	check[3] = fn[length - 1];
	check[4] = 0;
	
	// if last 4 chars of filename are ".txt" return true, else false
	if (strcasecmp(check, ".txt") == 0) return true;
	else return false;
}

// this function traverses the current directory in search of .txt files & is called recursively to check subdirectories
void searchDir(char *d){	

	// open directory d and assign to DIR pointer directory
	DIR *directory = opendir(d);

	// entry points to current directory entry
	struct dirent *entry;
	
	// open file txt_files.md to append it
	FILE *fp = fopen("txt_files.md", "a");

	// while there are more entries in the directory..
	while ((entry = readdir(directory)) != NULL) {
		
		// if entry is a .txt file, call pathName() to get it's filepath, then add the filepath to temporary .md file
		if (entry->d_type == DT_REG && isTxt(entry->d_name) == 1){
			
			char *filepath = pathName(d, entry->d_name);	
			
			fprintf(fp, "%s\n", filepath);

			free(filepath);
		
		// if entry is a directory, get it's path, and call searchDir() recursively on that path
		} else if (entry->d_type == DT_DIR) {
			
			// if the directory is the current one ('.') or parent ('..') do NOT call searchDir() recursively
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
				continue;
			}
			
			char *path = pathName(d, entry->d_name);

			searchDir(path);
	
			free(path);
		}
	}
	closedir(directory);
	fclose(fp);
}
