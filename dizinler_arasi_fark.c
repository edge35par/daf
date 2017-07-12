//dizin_bir'deki satırlar dizin_iki'de var mı?
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
	printf("Programın çalışma mantığı, sırayla sizden iki dizinin konumlarını girmenizi isteyecektir. Ardından ilk dizinde ve alt klasörlerinde olan dosyaları tek tek ikinci dizinde aratacak, ikinci dizinde olmayan dosyaları ekrana ve \"dizin_fark\" dosyasina yazacaktir. \n\nBu işlemleri yaparken oluşan \"dizin_bir\" ilk dizindeki dosyalar, \"dizin_iki\" ikinci dizindeki dosyalardır.\n\nNOT: İşlem yapılacak dizin adreslerini yazarken kök dosyasından itibaren yazınız. Örn: \"~\" yerine \"/home/kullanici_adi\"\n\n\n\t\tDİZİNLER ARASI FARK\n\n");
	
	char str_dizin_bir[1000], str_dizin_iki[1000], find_bir_acik[1100] ,find_iki_acik[1050] /*,find_bir_gizli[1100] ,find_iki_gizli[1050]*/;
	printf("İlk dizinin konumunu giriniz: "); 	scanf("%s",str_dizin_bir);
	printf("İkinci dizinin konumunu giriniz: "); scanf("%s",str_dizin_iki);
	int say_bir = 2, say_iki = 2;
	for (int i = 0; str_dizin_bir[i] != '\0' || str_dizin_iki[i] != '\0' ; ++i)
	{
		if (str_dizin_bir[i] == '/')	say_bir++;
		if (str_dizin_iki[i] == '/')	say_iki++;
		printf("%d-%d\n", say_bir ,say_iki);
	}
	sprintf(find_bir_acik, "find %s/*|cut -d/ -f%d- > dizin_bir", str_dizin_bir ,say_bir);
//	sprintf(find_bir_gizli, "find %s/.*|cut -d/ -f%d- >> dizin_bir", str_dizin_bir ,say_bir);
	sprintf(find_iki_acik, "find %s/*|cut -d/ -f%d- > dizin_iki" ,str_dizin_iki) ,say_iki;
//	sprintf(find_iki_gizli, "find %s/.*|cut -d/ -f%d- >> dizin_iki" ,str_dizin_iki) ,say_iki;

	system(find_bir_acik);
//	system(find_bir_gizli);
	system(find_iki_acik);
//	system(find_iki_gizli);

	FILE *dg_dizin_bir, *dg_dizin_iki, *dg_dizin_fark;
	dg_dizin_bir = fopen("dizin_bir","r");
	dg_dizin_iki = fopen("dizin_iki","r");
	dg_dizin_fark = fopen("dizin_fark","w");

	int bir_son, iki_son;
	char array_dizin_bir[10000][50], array_dizin_iki[10000][50];
	for (int i = 0; !feof(dg_dizin_bir); ++i)
	{
		fscanf(dg_dizin_bir, "%s",array_dizin_bir[i]);
		bir_son = i;
	}
	for (int i = 0; !feof(dg_dizin_iki); ++i)
	{
		fscanf(dg_dizin_iki, "%s",array_dizin_iki[i]);
		iki_son = i;
	}

	fclose(dg_dizin_bir);
	fclose(dg_dizin_iki);

	printf("\n------------------------------------------\n\n");
	int kontrol;
	for (int i = 0; i < bir_son+1; ++i)
	{
		kontrol = 0;
		for (int j = 0; j < iki_son+1; ++j)
		{
			if(strcmp(array_dizin_bir[i] ,array_dizin_iki[j]) == 0)	
			{
				kontrol = 1;
				break;
			}
		}
		if (kontrol == 1){}
		else 
		{
			fprintf(stdout, "%s\n",array_dizin_bir[i] );
			fprintf(dg_dizin_fark, "%s\n",array_dizin_bir[i] );
		}
	}
	fclose(dg_dizin_fark);
	return 0;
}
