#include <iostream>
#include <windows.h>

int main()
{
   FILE *f24;
   FILE *fr8;
   FILE *fg8;
   FILE *fb8;
   BITMAPFILEHEADER bf;
   BITMAPINFOHEADER bi;
   f24 = fopen("21.bmp", "rb");
   fr8 = fopen("12r.bmp", "wb");
   fg8 = fopen("12g.bmp", "wb");
   fb8 = fopen("12b.bmp", "wb");
   
   fread(&bf, sizeof(BITMAPFILEHEADER),1, f24);
   fread(&bi, sizeof(BITMAPINFOHEADER),1, f24);
   
   int height = bi.biHeight;
   int width = bi.biWidth;
   
   int src_wb = ((bi.biWidth * 24 + 31) / 32) * 4;
   int dst_wb = ((bi.biWidth * 8 + 31) / 32) * 4;
   
   int src_size = src_wb * height;
   int dst_size = dst_wb * height;
   
   unsigned char *src;
   unsigned char *dst;
   unsigned char clr[1024];
   src = new unsigned char[src_size];
   dst = new unsigned char[dst_size];
   fread(src, 1, src_size, f24);
   
   bi.biBitCount = 8;
   for(int i = 0; i < 256; i++)
   clr[i * 4 + 0] = clr[i * 4 + 1] = clr[i * 4 + 2] 
= (unsigned char)i;
   
   for(int i = height - 1; i >= 0; i--)
   {
      for(int j = 0; j < width;j++)
      {
         unsigned char blue =   src[i*src_wb + j *3 +0];
         unsigned char green =  src[i*src_wb + j *3 +1];
         unsigned char red =  src[i*src_wb + j *3 +2];
         unsigned char gry = (1 * red + 0* green + 0 * blue);
         dst [i*dst_wb + j] = gry;
      }
   }
 
   fwrite(&bf, sizeof(bf), 1, fr8);
   fwrite(&bi, sizeof(bi), 1, fr8);
   fwrite(clr, 1, 1024, fr8);
   fwrite(dst, 1, dst_size, fr8);
   
    for(int i = height - 1; i >= 0; i--)
   {
      for(int j = 0; j < width;j++)
      {
         unsigned char blue =   src[i*src_wb + j *3 +0];
         unsigned char green =  src[i*src_wb + j *3 +1];
         unsigned char red =  src[i*src_wb + j *3 +2];
         unsigned char gry = (0 * red + 1* green + 0 * blue);
         dst [i*dst_wb + j] = gry;
      }
   }
   
   fwrite(&bf, sizeof(bf), 1, fg8);
   fwrite(&bi, sizeof(bi), 1, fg8);
   fwrite(clr, 1, 1024, fg8);
   fwrite(dst, 1, dst_size, fg8);
   
   for(int i = height - 1; i >= 0; i--)
   {
      for(int j = 0; j < width;j++)
      {
         unsigned char blue =   src[i*src_wb + j *3 +0];
         unsigned char green =  src[i*src_wb + j *3 +1];
         unsigned char red =  src[i*src_wb + j *3 +2];
         unsigned char gry = (0 * red + 0* green + 1 * blue);
         dst [i*dst_wb + j] = gry;
      }
   }
   
   fwrite(&bf, sizeof(bf), 1, fb8);
   fwrite(&bi, sizeof(bi), 1, fb8);
   fwrite(clr, 1, 1024, fb8);
   fwrite(dst, 1, dst_size, fb8);
   
   delete [] src;
   delete [] dst;
   
   fclose(f24);
   fclose(fr8);
   fclose(fg8);
   fclose(fb8);
   return 0;
}
