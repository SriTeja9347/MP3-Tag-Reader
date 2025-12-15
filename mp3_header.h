#ifndef MP3_HEADER_H
#define MP3_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void view_mp3_tag(const char *filename);
//void edit_mp3_tag(const char *filename, const char *field, const char *new_value);
void edit_mp3_tag(const char *field, const char *new_value, const char *filename);

#endif


