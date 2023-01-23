
// COMP348 A1 -- Chris Anglin 40216346

#ifndef report_H
#define report_H

struct txt {
	char filepath[333];
	int modCount;
};

void printReport(char *target, struct txt *p, int size);

#endif
