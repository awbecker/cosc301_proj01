/*
 *
 * author name, date, and other info here
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "list.h"

void usage(char *program) {
    fprintf(stderr, "usage: %s [<datafile>]\n", program);
    exit(1);
}


int main(int argc, char **argv) {
    FILE *datafile = NULL;

    /* find out how we got invoked and deal with it */
    switch (argc) {
        case 1:
            /* only one program argument (the program name) */ 
            /* just equate stdin with our datafile */
            datafile = stdin;        
            break;

        case 2:
            /* two arguments: program name and input file */
            /* open the file, assign to datafile */
            datafile = fopen(argv[1], "r");
            if (datafile == NULL) {
                printf("Unable to open file %s: %s\n", argv[1], strerror(errno));
                exit(-1);
            }
            break;

        default:
            /* more than two arguments?  throw hands up in resignation */
            usage(argv[0]);
    }

    /* 
     * you should be able to just read from datafile regardless 
     * whether it's stdin or a "real" file.
     */
	char buffer[256];
	struct node *head = NULL;
	while (fgets(buffer, 256, datafile) != NULL) {
		char *token = strtok(buffer, " \t\n");
		while(token){
			int i = 0;
			if(token[i] == '-'){
				i++;
			}
			else if(token[i] == '#'){
				break;
			}
			while(token[i] != '\0'){
				if(! isdigit(token[i])){
					break;
				}
				i++;
			}
			if(token[i] == '\0'){
				int number = atoi(token);
				list_insert(number, &head);
			}
			token = strtok(NULL, " \t\n");
		}
    	}
	printf("%s\n", "*** List Contents Begin ***");
	list_print(head);
	printf("%s\n", "*** List Contents End ***");
	struct rusage ru;
	getrusage(RUSAGE_SELF, &ru);
	double user = ru.ru_utime.tv_sec + ((.000001)*ru.ru_utime.tv_usec);
	double system = ru.ru_stime.tv_sec + ((.000001)*ru.ru_stime.tv_usec);
	printf("%s", "User Time: ");
	printf("%e", user);
	printf("%s\n", " seconds.");
	printf("%s", "System Time: ");
	printf("%e", system);
	printf("%s\n", " seconds.");
    	fclose(datafile);
	list_clear(head);
    	return 0;
}

