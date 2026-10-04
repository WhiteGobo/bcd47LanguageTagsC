#include "bcd47LanguageTagsC.h"

#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

const char* lang = NULL;
const char* range = NULL;
bool inverse = false;
bool only_extended = true;

static int parse_args(int argc, char *argv[]);

int main(int argc, char *argv[]){
	int ret = EXIT_SUCCESS;
	int err;
	bool success;
	err = parse_args(argc, argv);
	if (err != 0){
		exit(EXIT_FAILURE);
	}
	if (!only_extended){
		success = basic_match_language_tag(range, lang);
		if(success == inverse){
			fprintf(stderr, "basic_match_language_tag failed to "
					"match lanugage '%s' to range '%s'\n",
					lang, range);
			ret = EXIT_FAILURE;
		}
	}
	success = extended_match_language_tag(range, lang);
	if(success == inverse){
		fprintf(stderr, "extended_match_language_tag failed to match "
				"lanugage '%s' to range '%s'\n", lang, range);
		ret = EXIT_FAILURE;
	}
	exit(ret);
}

static struct option parse_options[] = {
	{"lang", required_argument, NULL, 'l'},
	{"range", required_argument, NULL, 'r'},
	{"inverse", no_argument, NULL, 'i'},
	{"extended", no_argument, NULL, 'e'},
        {NULL, 0, NULL, 0}
};

static int parse_args(int argc, char *argv[]){
	int err = 0;
	int c = 0;
	int option_index;
	while(c != -1){
		c = getopt_long(argc, argv, "ie",
				parse_options, &option_index);
		switch(c){
			case -1: //end of arguments
				break;
			case 'l':
				lang = optarg;
				break;
			case 'r':
				range = optarg;
				break;
			case 'i':
				inverse = true;
				break;
			case 'e':
				only_extended = true;
				break;
			default:
				fprintf(stderr, "unrecognized argument\n");
				err = 1;
				break;
		}
	}
	if (lang == NULL){
		fprintf(stderr, "no lang given\n");
		err = 1;
	}
	if (range == NULL){
		fprintf(stderr, "no range given\n");
		err = 1;
	}
	return err;
}
