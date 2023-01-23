
// Written by: Chris Anglin

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>

// this function replaces the match found in the file with the target word in upper case
void replace(int index, char l[], char *t) {
	
	// temporary pointer to work with in replace()
	char *l2 = l;

	// temporary buffer for the modified line
	char tmp[333] = {0};

	char targettmp[strlen(t) + 1];

	strcpy(targettmp, t);
	strcat(targettmp, "\0");
	
	// create upper case version of the target string
	for (int i = 0; i < strlen(t); i++) {
		targettmp[i] = toupper(targettmp[i]);
	}
	
	// copy over line up to the index where match was found
	strncpy(tmp, l2, index);

	// cat the upper case target word
	strcat(tmp, targettmp);
	
	// move line pointer to point to the spot after the index where match was found + target word length
	l2 = &l2[index + strlen(t)];
	
	// cat the remainder of the line
	strcat(tmp, l2);
	strcat(tmp, "\0");
	
	// copy the modified line back to it's original pointer	
	strcpy(l, tmp);
}

// this function searches a line from the file for the target word
int searchLine(char l[], char *t, FILE *source) {
	
	// buffer for local copy of current line	
	char line[333] = {0};
	strcpy(line, l);

	// variable for string length of the target word
	int targetLen = strlen(t);	

	// variable for letters checked, set to zero
	int check = 0;

	// variable for number of matches found in the line, set to zero
	int matches = 0;

	// check each char in the line..
	for (int i = 0; i < 333; i ++) {			

		// if char is null, end of line, break
		if (line[i] == 0) break;
		
		// if not enough room left in line for target word, break
		if (i + targetLen > 333) break;

		// reset check to zero
		check = 0;
		
		// this loop looks forward from current char, char by char, to see if the target word is there
		while (check < targetLen) {
			
			if (tolower(line[i + check]) != tolower(t[0 + check])) {	
				break;
			}
			check++;
		}
		
		// if for the length of the target word, the chars all match, it is indeed a match
		if (check == targetLen) {
			
			// increase matches by one
			matches++;
			
			// call replace()
			replace(i, line, t);
		}
	}

	// write line to temp.txt file whether or not anything was replaced
	fprintf(source, "%s", line);	
	
	// return number of matches
	return matches;
}

// this function searches a .txt file for the target word 
int searchFile(char *f, char *target) {
	
	// remove "./" from filename, for the fopen function
	char *f2 = &f[2];
	
	// variable for number of modifications to a file, set to zero
	int mods = 0;	
	
	// open the file passed in to the function for reading
	FILE *fp = fopen(f2, "r");
	
	// create file to write in modified version
	FILE *source = fopen("temp.txt", "w");

	char line[333] = {0};
		
	// while there are more lines in the file, call searchLine() on each line
	while (fgets(line, 333, fp)){
		mods += searchLine(line, target, source);
	}
	
	fclose(fp);

	fclose(source);	

	// replace the original .txt file by overwriting it with it's modified version
	rename("temp.txt", f);
	
	// return the number of modifications to the file
	return mods;
}
