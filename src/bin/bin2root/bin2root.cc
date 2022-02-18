////////////////////////////////////////////////////////////
// ./bin2root rootspe.root (J.M. Allmond - ORNL - 3/2018) //
//                                                        //
// Creates a *.root file from all *.mat, *.spn, and *.sec //
// files in current directory                             //
////////////////////////////////////////////////////////////

#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "TCutG.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TObject.h"
#include "TROOT.h"

using namespace std;

TH1S *mat1d;
TH2S *mat2d;
TH1I *spn1d, *sec1d;
TH2I *spn2d, *sec2d;

int main(int argc, char **argv)
{

   char str1[127], str2[127], *stra, *strb;

   FILE *fp;
   short mat[4096] = {0};
   int spn[4096] = {0};
   int sec[8192] = {0};
   int ydim;

   if (argc < 2) {
      std::cout << "No input file specified" << std::endl;
      return -1;
   }

   // create root file
   TString RootName;
   if (argc > 2) {
      RootName = argv[2];
      printf("writing to %s\n", argv[2]);
   } else {
      RootName = "bin2root.root";
      printf("writing to bin2root.root\n");
   }
   TFile *fRoot = new TFile(RootName, "RECREATE");

   ////////////////////////////////////////////
   // get binary spectra and put into root file
   ////////////////////////////////////////////

   // read in files from current directory
   DIR *current_dir;
   struct dirent *dir;
   current_dir = opendir(".");

   if (current_dir) {
      while ((dir = readdir(current_dir)) != NULL) {

         // get name and extension
         strcpy(str1, dir->d_name);
         stra = strtok(str1, ".");
         strb = strtok(NULL, ".");

         // replace special characters in name with '_'
         for (int i = 0; i < (int)strlen(str1); i++) {
            if (str1[i] == '-' || str1[i] == ' ') {
               str2[i] = '_';
            } else {
               str2[i] = str1[i];
            }
         }
         str2[(int)strlen(str1)] = '\0';

         // read binary files if name and ext is good, create root spe, and fill 1
         // at a time (slow but needed for right weight)
         if (stra != NULL && strb != NULL) {

            //////////////////////
            // read in *.mat files
            if (strcmp(strb, "mat") == 0) {
               if ((fp = fopen(dir->d_name, "r")) == NULL) {
                  fprintf(stderr, "Error, cannot open input file %s\n", dir->d_name);
                  return 1;
               }

               // get file size --> ydim
               fseek(fp, 0L, SEEK_END);
               ydim = (ftell(fp) / sizeof(short int)) / 4096; // still need to check if it's an integer (should be)
               rewind(fp);

               // make root spe
               if (ydim == 1) {
                  mat1d = new TH1S(str2, str2, 4096, 0, 4096);
               } else if (ydim > 1) {
                  mat2d = new TH2S(str2, str2, 4096, 0, 4096, ydim, 0, ydim);
               } else {
                  printf("no data in %s\n", dir->d_name);
                  continue;
               }

               // read file and fill root spe
               for (int i = 0; i < ydim; i++) {
                  if (fread(mat, 4096 * sizeof(short int), 1, fp) == 1) {
                     for (int j = 0; j < 4096; j++) {
                       if (mat[j] > 0 ) {
                         std::cout << "filling " << j << "   " << i << "   " << mat[j] << std::endl;
                       }
                        for (int k = 0; k < mat[j]; k++) { // must do one fill at a time
                                                           // or it will change "weight"
                           if (ydim == 1)
                              mat1d->Fill(j+0.5);
                           if (ydim > 1)
                              mat2d->Fill(j+0.5, i+0.5);
                        }
                     }
                  } else {
                     printf("Error in reading file\n");
                     exit(0);
                  }
               }
               if (ydim == 1)
                  mat1d->Write();
               if (ydim > 1)
                  mat2d->Write();
               fclose(fp);
               printf("read in %s, 4096 row width, short int : y = %d rows\n", dir->d_name, ydim);
            }

            //////////////////////
            // read in *.spn files
            if (strcmp(strb, "spn") == 0) {
               if ((fp = fopen(dir->d_name, "r")) == NULL) {
                  fprintf(stderr, "Error, cannot open input file %s\n", dir->d_name);
                  return 1;
               }

               // get file size --> ydim
               fseek(fp, 0L, SEEK_END);
               ydim = (ftell(fp) / sizeof(int)) / 4096; // still need to check if it's an integer (should be)
               rewind(fp);

               // make root spe
               if (ydim == 1) {
                  spn1d = new TH1I(str2, str2, 4096, 0, 4096);
               } else if (ydim > 1) {
                  spn2d = new TH2I(str2, str2, 4096, 0, 4096, ydim, 0, ydim);
               } else {
                  printf("no data in %s\n", dir->d_name);
                  continue;
               }

               // read file and fill root spe
               for (int i = 0; i < ydim; i++) {
                  if (fread(spn, 4096 * sizeof(int), 1, fp) == 1) {
                     for (int j = 0; j < 4096; j++) {
                        for (int k = 0; k < spn[j]; k++) { // must do one fill at a time
                                                           // or it will change "weight"
                           if (ydim == 1)
                              spn1d->Fill(j);
                           if (ydim > 1)
                              spn2d->Fill(j, i);
                        }
                     }
                  } else {
                     printf("Error in reading file\n");
                     exit(0);
                  }
               }
               if (ydim == 1)
                  spn1d->Write();
               if (ydim > 1)
                  spn2d->Write();
               fclose(fp);
               printf("read in %s, 4096 row width, int : y = %d rows\n", dir->d_name, ydim);
            }

            //////////////////////
            // read in *.sec files
            if (strcmp(strb, "sec") == 0) {
               if ((fp = fopen(dir->d_name, "r")) == NULL) {
                  fprintf(stderr, "Error, cannot open input file %s\n", dir->d_name);
                  return 1;
               }

               // get file size --> ydim
               fseek(fp, 0L, SEEK_END);
               ydim = (ftell(fp) / sizeof(int)) / 8192; // still need to check if it's an integer (should be)
               rewind(fp);

               // make root spe
               if (ydim == 1) {
                  sec1d = new TH1I(str2, str2, 8192, 0, 8192);
               } else if (ydim > 1) {
                  sec2d = new TH2I(str2, str2, 8192, 0, 8192, ydim, 0, ydim);
               } else {
                  printf("no data in %s\n", dir->d_name);
                  continue;
               }

               // read file and fill root spe
               for (int i = 0; i < ydim; i++) {
                  if (fread(sec, 8192 * sizeof(int), 1, fp) == 1) {
                     for (int j = 0; j < 8192; j++) {
                        for (int k = 0; k < sec[j]; k++) { // must do one fill at a time
                                                           // or it will change "weight"
                           if (ydim == 1)
                              sec1d->Fill(j);
                           if (ydim > 1)
                              sec2d->Fill(j, i);
                        }
                     }
                  } else {
                     printf("Error in reading file\n");
                     exit(0);
                  }
               }
               if (ydim == 1)
                  sec1d->Write();
               if (ydim > 1)
                  sec2d->Write();
               fclose(fp);
               printf("read in %s, 8192 row width, int : y = %d rows\n", dir->d_name, ydim);
            }
         }
      }
      closedir(current_dir);
   }

   fRoot->Close();
   return 0;
}
