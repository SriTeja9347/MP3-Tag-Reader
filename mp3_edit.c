/*NAME: A.Sriteja
 * DATE :28/10/2025
 * DESCRIPTION: *This project is to view or edit the mp3 file
                *Edit the tag and store in temporary file and finally change the name as orginal file name.*/


#include "mp3_header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Convert Little Endian ↔ Big Endian (32-bit)
static int convert(int num)
{
    unsigned char byte1 = (num & 0x000000FF);
    unsigned char byte2 = (num & 0x0000FF00) >> 8;
    unsigned char byte3 = (num & 0x00FF0000) >> 16;
    unsigned char byte4 = (num & 0xFF000000) >> 24;

    return ((int)byte1 << 24) | ((int)byte2 << 16) | ((int)byte3 << 8) | ((int)byte4);
}

// Map short flags (-t, -a, etc.) to actual ID3 tag frame IDs
const char *map_flag_to_tag(const char *flag)
{
    if (strcmp(flag, "-t") == 0) return "TIT2";  // Title
    if (strcmp(flag, "-a") == 0) return "TPE1";  // Artist
    if (strcmp(flag, "-A") == 0) return "TALB";  // Album
    if (strcmp(flag, "-y") == 0) return "TYER";  // Year
    if (strcmp(flag, "-C") == 0) return "TCON";  // Content type
    if (strcmp(flag, "-c") == 0) return "COMM";  // Comment
    return NULL;  // Invalid flag
}

void edit_mp3_tag(const char *field_or_flag, const char *new_value, const char *filename)
{
    // Support both full tags (like "TIT2") and short flags (like "-t")
    const char *field = field_or_flag;
    const char *mapped = map_flag_to_tag(field_or_flag);
    if (mapped)
        field = mapped;

    FILE *src = fopen(filename, "rb");
    FILE *tmp = fopen("temp.mp3", "wb");
    if (!src || !tmp)
    {
        perror("File open error");
        return;
    }

    // Copy 10-byte ID3 header
    char header[10];
    fread(header, 1, 10, src);   // <-- fixed 2 to 1
    fwrite(header, 1, 10, tmp);

    int edited = 0;

    while (1)
    {
        char tag[5];
        if (fread(tag, 1, 4, src) != 4)
            break;
        tag[4] = '\0';

        int size_raw;
        if (fread(&size_raw, 4, 1, src) != 1)
            break;
        int frame_size = convert(size_raw);

        unsigned char flags[2];
        fread(flags, 1, 2, src);

        if (frame_size == 0)
            break;

        if (strcmp(tag, field) == 0 && !edited)
        {
            // Write new frame header
            fwrite(tag, 1, 4, tmp);

            int new_frame_size = strlen(new_value) + 1;
            int new_size_byte = convert(new_frame_size);
            fwrite(&new_size_byte, 4, 1, tmp);

            unsigned char new_flags[2] = {0, 0};
            fwrite(new_flags, 1, 2, tmp);

            // Write encoding + new value
            unsigned char encoding = 0;
            fwrite(&encoding, 1, 1, tmp);
            fwrite(new_value, strlen(new_value), 1, tmp);

            // Skip old frame data from src
            fseek(src, frame_size, SEEK_CUR);

            edited = 1;
        }
        else
        {
            // Copy original frame unchanged
            fwrite(tag, 1, 4, tmp);
            fwrite(&size_raw, 4, 1, tmp);
            fwrite(flags, 1, 2, tmp);

            char *content = malloc(frame_size);
            if (!content)
            {
                perror("malloc");
                fclose(src);
                fclose(tmp);
                return;
            }
            fread(content, 1, frame_size, src);
            fwrite(content, 1, frame_size, tmp);
            free(content);
        }
    }

    // Copy the rest of the MP3 (audio data)
    int ch;
    while ((ch = fgetc(src)) != EOF)
        fputc(ch, tmp);

    fclose(src);
    fclose(tmp);

    remove(filename);
    rename("temp.mp3", filename);

    printf("Tag edited successfully!\n");
}



