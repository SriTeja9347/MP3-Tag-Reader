/*NAME: A.Sriteja
 * DATE :28/10/2025
 * DESCRIPTION: *This project is to view or edit the mp3 file
                *Edit the tag and store in temporary file and finally change the name as orginal file name.
*/
#include "mp3_header.h"



void print_usage(void)
{
	printf("------------------------------------------------------------\n");
	printf("MP3 TAG READER - Usage Guide\n");
	printf("------------------------------------------------------------\n");

	printf("  ./a.out -v  file_name.mp3                : View MP3 Tag Information\n");
	printf("  ./a.out -e  file_name.mp3                : To edit MP3 Tag Information\n");
	printf("  ./a.out -h  file_name.mp3                : Display Help Message\n");
	printf("------------------------------------------------------------\n");
}

int main(int argc, char *argv[])
{

	if (argc < 2)
	{
		print_usage();
		return 0;
	}
	if (strcmp(argv[1], "-h") == 0)
	{
		print_usage();
	}
	else if (strcmp(argv[1], "-v") == 0)
	{
		view_mp3_tag(argv[2]);   
	}
	else if (strcmp(argv[1], "-e") == 0)
	{
		if(argc==5)
		{
		edit_mp3_tag(argv[2],argv[3],argv[4]);   
		}
		else
		print_usage();

	}

	else
	{
		printf("Error: Invalid option '%s'\n", argv[1]);
		print_usage();
	}

	return 0;
}

