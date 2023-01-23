
// COMP348 A1 -- Chris Anglin 40216346

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "report.h" // because it holds the definition of txt struct

// this function prints the report of the programs results
void printReport(char *target, struct txt *p, int size) {
	
	// this code block sorts the txt struct array by modCount from highest to lowest
	for (int j = 0; j < size; j++) {
		for (int i = 0; i < size; i++){
			if (i + 1 == size) break;
			if (p[i].modCount < p[i + 1].modCount){
				struct txt tmp;
				tmp = p[i];
		    	p[i] = p[i + 1];
	  			p[i + 1] = tmp;
		 	}		
		}
	}

	printf("\n\nTarget string: %s\n\n", target);
	
	// buffer to hold the returned result of the getcwd() function
	char line[333] = {0};

	printf("Search begins in current folder: %s\n\n\n", getcwd(line, 333));

	printf("** Search Report **\n\n");
	
	printf("Updates          File Name\n");

	for (int i = 0; i < size; i ++){
		char *tmp = &p[i].filepath[2];
		printf("%d                %s\n", p[i].modCount, tmp);
	}	
	printf("\n\n");
}
