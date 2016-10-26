#include "BmpLibrary.h"

/*
Reads the bitmap file and populates the bitmapData structure.
Allocates memory for each member in the structure.
*/
void LoadBitmapFile(char *filename, BITMAPDATA *bitmapData)
{
   // file pointer
   FILE *filePtr;
   size_t fr = 0;

   // open filename in read binary mode
   filePtr = fopen(filename, "rb");
   if (filePtr == NULL) {
      perror("Could not open file to read");
      exit(-1);
   }

   // allocate memory for bimap header
   bitmapData->bitmapFileHeader = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));
   if (!bitmapData->bitmapFileHeader)
   {
      free(bitmapData->bitmapFileHeader);
      fclose(filePtr);
      perror("Error allocating memory");
      exit(-1);
   }

   // read the bitmap file header
   fr = fread(bitmapData->bitmapFileHeader, 1, sizeof(BITMAPFILEHEADER), filePtr);
   if (fr != sizeof(BITMAPFILEHEADER)) {
      free(bitmapData->bitmapFileHeader);
      fclose(filePtr);
      perror("Error reading file");
      exit(-1);
   }

   // verify that this is a bmp file by check bitmap id
   if (bitmapData->bitmapFileHeader->bfType != 0x4D42) {
      free(bitmapData->bitmapFileHeader);
      fclose(filePtr);
      perror("File is not a bitmap version that I can read");
      exit(-1);
   }

   // allocate memory for bimap header
   bitmapData->bitmapInfoHeader = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));
   if (!bitmapData->bitmapInfoHeader)
   {
      free(bitmapData->bitmapFileHeader);
      free(bitmapData->bitmapInfoHeader);
      fclose(filePtr);
      perror("Error allocating memory");
      exit(-1);
   }

   // read the bitmap info header
   fr = fread(bitmapData->bitmapInfoHeader, 1, sizeof(BITMAPINFOHEADER), filePtr);
   if (fr != sizeof(BITMAPINFOHEADER)) {
      free(bitmapData->bitmapFileHeader);
      free(bitmapData->bitmapInfoHeader);
      fclose(filePtr);
      perror("Error reading file");
      exit(-1);
   }

   // allocate memory for the bitmap palette
   int paletteSize = bitmapData->bitmapFileHeader->bfOffBits - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER);
   bitmapData->bitmapPalette = (BITMAPPALETTE *)malloc(paletteSize);
   if (!bitmapData->bitmapPalette)
   {
      free(bitmapData->bitmapFileHeader);
      free(bitmapData->bitmapInfoHeader);
      free(bitmapData->bitmapPalette);
      fclose(filePtr);
      perror("Error allocating memory");
      exit(-1);
   }

   // read the bitmap palette info
   fr = fread(bitmapData->bitmapPalette, 1, paletteSize, filePtr);
   if (fr != paletteSize) {
      free(bitmapData->bitmapFileHeader);
      free(bitmapData->bitmapInfoHeader);
      free(bitmapData->bitmapPalette);
      fclose(filePtr);
      perror("Error reading file");
      exit(-1);
   }

   // allocate enough memory for the bitmap image data
   bitmapData->bitmapImage = (BYTE *)malloc(bitmapData->bitmapInfoHeader->biSizeImage);
   if (!bitmapData->bitmapImage)
   {
      free(bitmapData->bitmapFileHeader);
      free(bitmapData->bitmapInfoHeader);
      free(bitmapData->bitmapPalette);
      free(bitmapData->bitmapImage);
      fclose(filePtr);
      perror("Error allocating memory");
      exit(-1);
   }

   // read in the bitmap image data
   fr = fread(bitmapData->bitmapImage, 1, bitmapData->bitmapInfoHeader->biSizeImage, filePtr);
   if (fr != bitmapData->bitmapInfoHeader->biSizeImage)
   {
      free(bitmapData->bitmapFileHeader);
      free(bitmapData->bitmapInfoHeader);
      free(bitmapData->bitmapPalette);
      free(bitmapData->bitmapImage);
      fclose(filePtr);
      perror("Error reading image data");
      exit(-1);
   }

   // close file
   fclose(filePtr);
}

/*
Write the bitmap data to a file.
*/
void WriteBitmapFile(char *filename, BITMAPDATA *bitmapData)
{
   // file pointer
   FILE *filePtr;

   // file size
   int fs = bitmapData->bitmapFileHeader->bfSize;
   int fr = 0;
   int paletteSize = (bitmapData->bitmapFileHeader->bfOffBits - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER)) / 4;

   // open filename in write binary mode
   filePtr = fopen(filename, "wb");
   if (filePtr == NULL) {
      perror("Could not open file to write");
      exit(-1);
   }

   // write the bitmap data to the file
   fr = fwrite(bitmapData->bitmapFileHeader, 1, sizeof(BITMAPFILEHEADER), filePtr);
   fr += fwrite(bitmapData->bitmapInfoHeader, 1, sizeof(BITMAPINFOHEADER), filePtr);
   fr += 4 * fwrite(bitmapData->bitmapPalette, sizeof(BITMAPPALETTE), paletteSize, filePtr);
   fr += fwrite(bitmapData->bitmapImage, 1, bitmapData->bitmapInfoHeader->biSizeImage, filePtr);

   // close file 
   fclose(filePtr);
}