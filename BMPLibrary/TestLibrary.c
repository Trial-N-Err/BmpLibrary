#include "BmpLibrary.h"

int main() {
   BITMAPDATA bitmapData;
   char inFileName[256] = "C:\\tiger.bmp";
   char outFileName[256];

   LoadBitmapFile(inFileName, &bitmapData);
   AvgFilter(&bitmapData);
   strcpy(outFileName, inFileName);
   strcat(outFileName, "-avg.bmp");
   WriteBitmapFile(outFileName, &bitmapData);


   LoadBitmapFile(inFileName, &bitmapData);
   LumaFilter(&bitmapData);
   strcpy(outFileName, inFileName);
   strcat(outFileName, "-luma.bmp");
   WriteBitmapFile(outFileName, &bitmapData);

   LoadBitmapFile(inFileName, &bitmapData);
   SepiaFilter(&bitmapData);
   strcpy(outFileName, inFileName);
   strcat(outFileName, "-sepia.bmp");
   WriteBitmapFile(outFileName, &bitmapData);

   LoadBitmapFile(inFileName, &bitmapData);
   Inverted(&bitmapData);
   strcpy(outFileName, inFileName);
   strcat(outFileName, "-inverted.bmp");
   WriteBitmapFile(outFileName, &bitmapData);

   free(bitmapData.bitmapFileHeader);
   free(bitmapData.bitmapInfoHeader);
   free(bitmapData.bitmapPalette);
   free(bitmapData.bitmapImage);

}
