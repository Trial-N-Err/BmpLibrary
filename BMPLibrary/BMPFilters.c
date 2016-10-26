#include "BmpLibrary.h"

void AvgFilter(BITMAPDATA *bitmapData) {
   int h, i;
   int offset = 0;
   BYTE maxValue = 255;
   int height = bitmapData->bitmapInfoHeader->biHeight;
   int widthBytes = bitmapData->bitmapInfoHeader->biWidth * bitmapData->bitmapInfoHeader->biBitCount / 8;
   int pad = widthBytes % 4;
   for (h = 0; h < height; h++) {
      for (i = offset; i < offset + widthBytes; i += 3) {
         float grayscale = (bitmapData->bitmapImage[i] + bitmapData->bitmapImage[i + 1] + bitmapData->bitmapImage[i + 2]) / 3;
         bitmapData->bitmapImage[i] = (BYTE)grayscale;
         bitmapData->bitmapImage[i + 1] = (BYTE)grayscale;
         bitmapData->bitmapImage[i + 2] = (BYTE)grayscale;
      }
      offset += widthBytes + pad;
   }
}

void LumaFilter(BITMAPDATA *bitmapData) {
   int h, i;
   int offset = 0;
   BYTE maxValue = 255;
   int height = bitmapData->bitmapInfoHeader->biHeight;
   int widthBytes = bitmapData->bitmapInfoHeader->biWidth * bitmapData->bitmapInfoHeader->biBitCount / 8;
   int pad = widthBytes % 4;
   for (h = 0; h < height; h++) {
      for (i = offset; i < offset + widthBytes; i += 3) {
         float grayscale = .114f*bitmapData->bitmapImage[i] + .587f*bitmapData->bitmapImage[i + 1] + .299f*bitmapData->bitmapImage[i + 2];
         bitmapData->bitmapImage[i] = (grayscale > maxValue ? maxValue : (BYTE)grayscale);
         bitmapData->bitmapImage[i + 1] = (grayscale > maxValue ? maxValue : (BYTE)grayscale);
         bitmapData->bitmapImage[i + 2] = (grayscale > maxValue ? maxValue : (BYTE)grayscale);
      }
      offset += widthBytes + pad;
   }
}


void SepiaFilter(BITMAPDATA *bitmapData) {
   int h, i;
   int offset = 0;
   BYTE maxValue = 255;
   int height = bitmapData->bitmapInfoHeader->biHeight;
   int widthBytes = bitmapData->bitmapInfoHeader->biWidth * bitmapData->bitmapInfoHeader->biBitCount / 8;
   int pad = widthBytes % 4;
   for (h = 0; h < height; h++) {
      for (i = offset; i < offset + widthBytes; i += 3) {
         float r = 0.189f*bitmapData->bitmapImage[i] + 0.769f*bitmapData->bitmapImage[i + 1] + 0.393f*bitmapData->bitmapImage[i + 2];
         float g = 0.168f*bitmapData->bitmapImage[i] + 0.686f*bitmapData->bitmapImage[i + 1] + 0.349f*bitmapData->bitmapImage[i + 2];
         float b = 0.131f*bitmapData->bitmapImage[i] + 0.534f*bitmapData->bitmapImage[i + 1] + 0.272f*bitmapData->bitmapImage[i + 2];

         bitmapData->bitmapImage[i] = (b > maxValue ? maxValue : (BYTE)b);
         bitmapData->bitmapImage[i + 1] = (g > maxValue ? maxValue : (BYTE)g);
         bitmapData->bitmapImage[i + 2] = (r > maxValue ? maxValue : (BYTE)r);
      }
      offset += widthBytes + pad;
   }
}

void Inverted(BITMAPDATA *bitmapData) {
   int h, i;
   int offset = 0;
   BYTE maxValue = 255;
   int height = bitmapData->bitmapInfoHeader->biHeight;
   int widthBytes = bitmapData->bitmapInfoHeader->biWidth * bitmapData->bitmapInfoHeader->biBitCount / 8;
   int pad = widthBytes % 4;
   for (h = 0; h < height; h++) {
      for (i = offset; i < offset + widthBytes; i += 3) {
         bitmapData->bitmapImage[i] = ~bitmapData->bitmapImage[i];
         bitmapData->bitmapImage[i + 1] = ~bitmapData->bitmapImage[i + 1];
         bitmapData->bitmapImage[i + 2] = ~bitmapData->bitmapImage[i + 2];
      }
      offset += widthBytes + pad;
   }
}