#include <stdio.h>
#include <syslog.h>
#include <errno.h>
#include <string.h>


int main(int argc, char* argv[]) {

	openlog(NULL, 0, LOG_USER);

	if (argc < 3) {
		// missing arguements
		fprintf(stderr, "Error: expected <filepath> <filecontent>\n");
		syslog(LOG_ERR, "Invalid number of arguments: %d, arguments", argc);
		closelog();
		return 1;
	}

	char* path = argv[1];
	char* textInput = argv[2];


	FILE *file = fopen(path, "w");
	if (file == NULL) {
		fprintf(stderr, "Unable to open file: %s\n", strerror(errno));
		syslog(LOG_ERR, "Unable to open file %s: %s", path, strerror( errno ));
		closelog();
		return 1;
	}

	syslog(LOG_DEBUG, "Writing <%s> to <%s>", textInput, path);

	if ( fprintf(file, "%s", textInput) < 0) {
		fprintf(stderr, "Error writing to file");
		syslog(LOG_ERR, "Error writing to file %s", path);
		fclose(file);
		closelog();
		return 1;
	}
	if (fclose(file) == EOF) {
		syslog(LOG_ERR, "Error closing file %s", path);
		closelog();
		return 1;
	}
	
	closelog();
	return 0;
}
