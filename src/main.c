/**
* @file			: main.c
* @description	: 
* @course		: 2-B
* @assignment	: 1. Proje / Tasarim
* @date			: 08.05.2021
* @author		: Sinan KAMILCELEBI, sinan.kamilcelebi@ogr.sakarya.edu.tr
*/
#ifdef _WIN32 //Windows'da da calistirma icin tanimlandi.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jrb.h"
#include "fields.h"
#include "dllist.h"
#include "jval.h"
#else
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jrb.h"
#include "fields.h"
#include "dllist.h"
#include "jval.h"
#endif

void decripted(IS is, JRB m_jrb);
void encripted(IS is, JRB m_jrb);
void RChar(char * s, char c);
void error(void);

void error(void){
    printf("\nHatali giris\n");
	printf("\nKullanım: kripto -d | -e giriş_metin cikis_metin\n");
	printf("\nProgram sonlandirildi.\n");
	exit(1);
}

void RChar(char * s, char c) {
    int j, n = strlen(s);
    for (int i = j = 0; i < n; i++)
        if (s[i] != c)
            s[j++] = s[i];
    s[j] = '\0';
}

int main(int argc, char **argv)
{
  if (argc != 4) { 
  	fprintf(stderr, "kripto -d giriş_metin cikis_metin\n    kripto -e giriş_metin cikis_metin\n"); 
  	exit(1); 
  }
  IS is = new_inputstruct(".kilit");
  
  if (is == NULL) {
    perror("\nKilit dosyasi bulunamadi.");
	printf("\nProgram sonlandirildi.\n");
    exit(1);
  }

  JRB m_jrb = make_jrb();
  
  if(argv[1][1] == 'd')
  	decripted(is, m_jrb);
  else if(argv[1][1] == 'e')
  	encripted(is, m_jrb);
  else{
  	fprintf(stderr, "-d : decripted\n    -e : encripted\n");
	error();	
  }
  
  IS is_input = new_inputstruct(argv[2]);
    
  if (is_input == NULL) {
    perror("\nGiris dosyasi bulunamadi.");
	printf("\nProgram sonlandirildi.\n");
    exit(1);
  }
   
    FILE *ofile = fopen(argv[3], "w");
    if(ofile == NULL){
        perror("\nCikti dosyasi olusturulamadi.\n");
		printf("\nProgram sonlandirildi.\n");
        exit(-1);
    }
    
	while (get_line(is_input) >= 0) { 
              int i;
              for (i = 0; i < is_input->NF; i++) 
                {                
                            JRB bul = jrb_find_str(m_jrb,is_input->fields[i] ); 
                            if (bul == NULL)
                                {
                                    fputs(is_input->fields[i], ofile);
                                    fputc(' ', ofile);
                                }
                            else
                                { 
                                    fputs(bul->val.s, ofile);
                                    fputc(' ', ofile);
                                }
                }
  }

  fclose(ofile);    
  jettison_inputstruct(is);
  return 0;
}

//decripted mode.
void decripted(IS is, JRB b){
    char *cd, *wrld;
	while (get_line(is) >= 0) { 
           if (is->NF == 2)
           { 
              cd = strtok(is->fields[1], "\"");
              wrld = strtok(is->fields[0], "\"");
              (void) jrb_insert_str(b, strdup(cd), new_jval_s(strdup(wrld)));
           }       
  }
  printf("\ndencrypt islemi basariyla tamamlandi.\n");
}

//encripted mode.
void encripted(IS is, JRB b){
	char *cd, *wrld;
	while (get_line(is) >= 0) { 
           if (is->NF == 2)
           { 
              cd = strtok (is->fields[1], "\"");
              wrld = strtok (is->fields[0], "\"");
              (void) jrb_insert_str(b, strdup(wrld), new_jval_s(strdup(cd)));
           }       
  }
  printf("\nencrypt islemi basariyla tamamlandi.\n");
}
