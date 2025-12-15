/*NAME:A.Sriteja
 * DATE :28/10/2025
 * DESCRIPTION: *This project is to view or edit the mp3 file
                *Edit the tag and store in temporary file and finally change the name as orginal file name.
*/


#include "mp3_header.h"



void view_mp3_tag(const char *filename)
{
    FILE *fp;
    char header[10];
    char frame_id[5];
    unsigned int frame_size;
    unsigned char size_bytes[4];
//    atexit(fun);
    fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        printf("Error: Cannot open file %s\n", filename);
        return;
    }

    /* Read first 10 bytes (ID3v2 header) */
    fread(header, 1, 10, fp);

    /* Check if file starts with "ID3" */
    if (header[0] != 'I' || header[1] != 'D' || header[2] != '3')
    {
	    printf("No ID3 tag found in %s\n", filename);
	    fclose(fp);
	    return;
    }

    printf("\n----------------------------------------\n");
    printf("     MP3 TAG INFORMATION (ID3v2.3)\n");
    printf("----------------------------------------\n");

    unsigned int tag_size =
	    ((header[6] & 0x7F) << 21) |
	    ((header[7] & 0x7F) << 14) |
	    ((header[8] & 0x7F) << 7)  |
	    (header[9] & 0x7F);

    unsigned int tag_end = tag_size + 10;
    while (ftell(fp) < tag_end && fread(frame_id, 1, 4, fp) == 4)
	    // while (fread(frame_id, 1, 4, fp) == 4)
    {
	    frame_id[4] = '\0';

	    if(strcmp(frame_id,"TIT2")==0)
	    {

		    fread(size_bytes, 1, 4, fp);
		    frame_size = (size_bytes[0] << 24) |
			    (size_bytes[1] << 16) |
			    (size_bytes[2] << 8)  |
			    size_bytes[3];

		    fseek(fp, 2, SEEK_CUR);  // Skip 2 flag bytes

		    if (frame_size == 0)
			    break;

		    char* frame_data = (char *)malloc(frame_size +1 );
		    fread(frame_data, 1, frame_size, fp);
		    frame_data[frame_size] = '\0';

		    char *text = frame_data+1  ;
		    printf("Title   : %s\n", text);
		    free(frame_data);
	    }

	    else if(strcmp(frame_id,"TPE1")==0)
	    {

		    fread(size_bytes, 1, 4, fp);
		    frame_size = (size_bytes[0] << 24) |
			    (size_bytes[1] << 16) |
			    (size_bytes[2] << 8)  |
			    size_bytes[3];

		    fseek(fp, 2, SEEK_CUR);  // Skip 2 flag bytes

		    if (frame_size == 0)
			    break;

		    char* frame_data1 = (char *)malloc(frame_size +1 );
		    fread(frame_data1, 1, frame_size, fp);
		    frame_data1[frame_size] = '\0';

		    char *text = frame_data1+1  ;

		    printf("Artist  : %s\n", text);
		    free(frame_data1);
	    }

	    else if (strcmp(frame_id, "TALB") == 0)
	    {

		    fread(size_bytes, 1, 4, fp);
		    frame_size = (size_bytes[0] << 24) |
			    (size_bytes[1] << 16) |
			    (size_bytes[2] << 8)  |
			    size_bytes[3];

		    fseek(fp, 2, SEEK_CUR);  // Skip 2 flag bytes

		    if (frame_size == 0)
			    break;

		    char* frame_data2 = (char *)malloc(frame_size +1 );
		    fread(frame_data2, 1, frame_size, fp);
		    frame_data2[frame_size] = '\0';

		    char *text = frame_data2+1  ;


		    printf("Album   : %s\n", text);
		    free(frame_data2);
	    }

	    else if (strcmp(frame_id, "TYER") == 0)
	    {

		    fread(size_bytes, 1, 4, fp);
		    frame_size = (size_bytes[0] << 24) |
			    (size_bytes[1] << 16) |
			    (size_bytes[2] << 8)  |
			    size_bytes[3];

		    fseek(fp, 2, SEEK_CUR);  // Skip 2 flag bytes

		    if (frame_size == 0)
			    break;

		    char* frame_data3 = (char *)malloc(frame_size +1 );
		    fread(frame_data3, 1, frame_size, fp);
		    frame_data3[frame_size] = '\0';

		    char *text = frame_data3+1  ;

		    printf("Year    : %s\n", text);
	    }

	    else if (strcmp(frame_id, "TCON") == 0)
	    {

		    fread(size_bytes, 1, 4, fp);
		    frame_size = (size_bytes[0] << 24) |
			    (size_bytes[1] << 16) |
			    (size_bytes[2] << 8)  |
			    size_bytes[3];

		    fseek(fp, 2, SEEK_CUR);  // Skip 2 flag bytes

		    if (frame_size == 0)
			    break;

		    char* frame_data4 = (char *)malloc(frame_size +1 );
		    fread(frame_data4, 1, frame_size, fp);
		    frame_data4[frame_size] = '\0';

		    char *text = frame_data4+1  ;

		    printf("Content : %s\n", text);
	    }
	    else if (strcmp(frame_id, "COMM") == 0)
	    {

		    fread(size_bytes, 1, 4, fp);
		    frame_size = (size_bytes[0] << 24) |
			    (size_bytes[1] << 16) |
			    (size_bytes[2] << 8)  |
			    size_bytes[3];

		    fseek(fp, 2, SEEK_CUR);  // Skip 2 flag bytes

		    if (frame_size == 0)
			    break;

		    char* frame_data5 = (char *)malloc(frame_size +1 );
		    fread(frame_data5, 1, frame_size, fp);
		    frame_data5[frame_size] = '\0';

		    char *text = frame_data5+1  ;


		    printf("Comments: %s\n", text);


	   }



    }

	    printf("extra: %s\n","@@@@@@");
    fclose(fp);
}


