#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


typedef unsigned char	BYTE;    // 1 byte
typedef unsigned short	WORD;    // 2 bytes
typedef unsigned long	DWORD;   // 4 bytes

                                 /*
                                 To store general information about the bitmap image file.
                                 should be bytes 0 to 13 in  .bmp file. (14 bytes)
                                 The bftype field checks to see if you are in fact loading
                                 a bmp file.  There are 7 versions.
                                 */
#pragma pack(push, 1)
typedef struct BITMAPFILEHEADER
{
   WORD	bfType;			// specifies the file type
   DWORD	bfSize;			// specifies the size in bytes of the bitmap file
   WORD	bfReserved1;	// reserved; must be 0
   WORD	bfReserved2;	// reserved; must be 0
   DWORD	bfOffBits;		// species the offset in bytes from the bitmapfileheader to the bitmap bits
}BITMAPFILEHEADER;
#pragma pack(pop)


/*
To store detailed information about the bitmap image and define the pixel format.
This is used when bfType is 0x4D42, "BM" version.
should be bytes 14 to 54 in .bmp file. (40 bytes)

*/
#pragma pack(push, 1)
typedef struct BITMAPINFOHEADER
{
   DWORD biSize;           // the size of this header (40 bytes)
   long  biWidth;          // the bitmap width in pixels (signed integer)
   long  biHeight;         // the bitmap height in pixels (signed integer)
   WORD  biPlanes;         // the number of color planes (must be 1)
   WORD  biBitCount;       // the number of bits per pixel, which is the color 
                           // depth of the image. Typical values are 1, 4, 8, 16, 24 and 32.
   DWORD biCompression;    // the compression method being used
   DWORD biSizeImage;      // size of image in bytes
   long  biXPelsPerMeter;  // number of pixels per meter in x axis
   long  biYPelsPerMeter;  // number of pixels per meter in y axis
   DWORD biClrUsed;        // number of colors used by th ebitmap
   DWORD biClrImportant;   // number of colors that are important
}BITMAPINFOHEADER;

#pragma pack(pop)

/*
Holds a color from the bitmap palette
*/

#pragma pack(push, 1)
typedef struct BITMAPPALETTE
{
   BYTE bmpBlue;
   BYTE bmpGreen;
   BYTE bmpRed;
   BYTE bmpAlpha;
}BITMAPPALETTE;
#pragma pack(pop)

/*
Stores pointers to the data for a bitmap file
*/
typedef struct BITMAPDATA
{
   BITMAPFILEHEADER *bitmapFileHeader;    // pointer to the file header structure
   BITMAPINFOHEADER *bitmapInfoHeader;    // pointer to the file info structure
   BITMAPPALETTE *bitmapPalette;          // pointer to the bitmap palette array (size will depend on number of colors)
   BYTE *bitmapImage;                     // pointer to the bitmap image array (size will depend on size of image)
}BITMAPDATA;

// Function definitions
void LoadBitmapFile(char *filename, BITMAPDATA *bitmapData);
void WriteBitmapFile(char *filename, BITMAPDATA *bitmapData);
void AvgFilter(BITMAPDATA *bitmapData);
void LumaFilter(BITMAPDATA *bitmapData);