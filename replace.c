
// COMP348 A1 -- Chris Anglin 40216346

// main() is at the bottom

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "traversal.h"
#include "text.h"
#include "report.h"

// this function counts the number of .txt filepaths from the temporary .md file created in main()
int fileCounter() {
	
	// open txt_files.md to read it
	FILE *fp = fopen("txt_files.md", "r");
	
	// variable for the number of .txt files
	int count = 0;

	// this is a buffer used for each line read
	char line[333];

	// while there are more filepaths, increase count for each one
	while(fgets(line, 333, fp)) {	
		count++;
	}
	
	fclose(fp);
		
	return count;
}

// this function fills the txt struct array with the filepaths from the temporary .md file
void fillArray(struct txt *txt) {

	// open txt_files.md to read it
	FILE *fp = fopen("txt_files.md", "r");

	// for each .txt file, put relevant data into txt struct array
	for (int i = 0; i < fileCounter(); i++) {

		char line[333] = {0};

		fgets(line, 333, fp);
		
		// copy filepath into txt struct array
		strcpy(txt[i].filepath, line);
		
		// add null after ".txt"
		for (int j = 0 ; j < 333; j++) {
			if (txt[i].filepath[j] == '.' && txt[i].filepath[j + 1] == 't') {
				if (txt[i].filepath[j + 2] == 'x' && txt[i].filepath[j + 3] == 't') {
				   	txt[i].filepath[j + 4] = '\0';
				}
			}
		}
		
		// initialize modCount to zero
		txt[i].modCount = 0;
	}
	fclose(fp);
}

int main(int argc, char *argv[]){	
		
	// if user gives zero arguments or more than one, display relevant error message and terminate program
	if (argv[1] == 0) {
		printf("\n -- MUST ENTER A TARGET STRING --\n\n");
		return 1;
	} else if (argc > 2) {
		printf("\n -- PLEASE ENTER A SINGLE TARGET STRING --\n\n");
		return 1;
	}

	// create new .md file to temporarily store filepaths of .txt files found during traversal
	FILE *fp = fopen("txt_files.md", "w");
	
	// call searchDir() on the current directory
	searchDir(".");

	fclose(fp);
	
	// variable to hold the number of .txt files found, set to the return value of fileCounter()
	int txtFilesFound = fileCounter();
	
	// calloc new txt struct array of correct size	
	struct txt *txtFiles = (struct txt *)calloc(txtFilesFound, sizeof(struct txt));

	// call fillArray() to fill the array
	fillArray(txtFiles);

	// delete the temporary .md file, now that the array is holding the data
	remove("txt_files.md");
	
	// call searchFile() on every .txt file found, set modification count upon return
	for (int i = 0; i < txtFilesFound; i++) {
		txtFiles[i].modCount = searchFile(txtFiles[i].filepath, argv[1]);
	}

	// call printReport() to display the report
	printReport(argv[1], txtFiles, txtFilesFound);
	
	free(txtFiles);

	return 0;
}
