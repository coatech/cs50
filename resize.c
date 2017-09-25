/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }
	//remember resize number
	int n = atoi(argv[1]);
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];
	
    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // modifing the outfile's BITMAPFILEHEADER and outfile's BITMAPINFOHEADER
	BITMAPFILEHEADER bf2 = bf;
	BITMAPINFOHEADER bi2 = bi;
	bi2.biWidth 		 = bi2.biWidth * n;
	bi2.biHeight 		 = bi2.biHeight * n;
	int padding2 		 = (4 - (bi2.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
	bi2.biSizeImage  	 = abs(bi2.biHeight) * (sizeof(RGBTRIPLE) * bi2.biWidth + padding2);
	bf2.bfSize			 = bi2.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf2, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi2, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int l = 0; l < n; l++){
			// iterate over pixels in scanline
			for (int j = 0; j < bi.biWidth; j++)
			{
				// temporary storage
				RGBTRIPLE triple;

				// read RGB triple from infile
				fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

				// write RGB triple to outfile
				for(int m = 0; m < n; m++){
					fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
				}
			}

			// skip over padding, if any
			fseek(inptr, padding, SEEK_CUR);

			// then add it back (to demonstrate how)
			for (int k = 0; k < padding2; k++)
			{
				fputc(0x00, outptr);
			}
			
			if(l < n-1){
				// return to current scanline
				fseek(inptr, -(3* bi.biWidth + padding), SEEK_CUR);
			}
		}
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}