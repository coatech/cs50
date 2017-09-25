/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
	typedef uint8_t  BYTE;

    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }
	
    // remember filenames
    char *infile = argv[1];
	//declaration of variable
	char jpeg[8];
	bool jpeg_header = false;
	int k = 0;
    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open file\n");
        return 2;
    }

    // output file
    FILE *outptr;
	BYTE image[512];

    // iterate over infile's while not EOF
	while(fread(image, 1, 512, inptr) != 0x00)
    {
        if (image[0] == 0xff && image[1] == 0xd8 &&  image[2] == 0xff &&  (image[3] & 0xf0) == 0xe0){
			// when first jpeg_header has not been found
			if (!jpeg_header){
				// change jpeg_header to true
				jpeg_header = true;
				// read RGB triple from infile
				sprintf(jpeg, "%03i.jpg", k++);

				// write RGB triple to outfile
				outptr = fopen(jpeg, "w");
				if(outptr == NULL)
					return 3;
				fwrite(image, 1, 512, outptr);
			}
			else{
				fclose(outptr);
				sprintf(jpeg, "%03i.jpg", k++);

				// write RGB triple to outfile
				outptr = fopen(jpeg, "w");
				if(outptr == NULL)
					return 3;
				fwrite(image, 1, 512, outptr);
			}
		}
		else{
			fwrite(image, 1, 512, outptr);
		}
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}