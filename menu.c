#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "header.h"

void pilihmenu()
{
	int n;
	while(1){
		system("cls");
		printf("Pilih salah satu:\n");
		printf("(1)Input Barang\n(2)Print Daftar Barang\n(3)Edit Daftar Barang\n(0)Kembali\n\n");
		scanf("%d", &n);
		printf("\n\n");
		if(n == 1){
			inputmenu();
		}
		else if(n == 2){
			cetakmenu();
		}
		else if(n == 3){
			editmenu();
		}
		else if(n == 0){
			return;
		}
	}
}

void inputmenu()
{
	system("cls");
	int no;
	struct data master = { 0, "", "", 0};
	FILE *fp;
	if((fp = fopen("mastermenu.dat", "rb+"))==NULL){
		printf("File could not be opened\n");
	}
	
	while(1){
		printf("\tMasukkan Data Menu:\t\n\n");
		printf("Masukkan nomor:\n");
		printf("(Masukkan -1 jika selesai)\n");
		scanf("%d", &master.no);
		if(master.no == -1){
			break;
		}
		printf("Masukkan kode barang:\n");
		scanf("%s", master.kode);
		printf("Masukkan merk barang:\n");
		scanf(" %[^\n]", master.merk);
		printf("Masukkan harga barang:\n");
		scanf("%d", &master.harga);
		printf("Masukkan harga modal:\n");
		scanf("%llu", &master.modal);
		printf("Masukkan stok barang:\n");
		scanf("%d", &master.stok);
		printf("\n\n");
	master.paten = master.stok;
	master.day = 0;
	master.month = 0;
	master.year = 0;
	fseek( fp, ( master.no - 1 ) * sizeof( struct data ), SEEK_SET ); 
	fwrite(&master, sizeof(struct data ), 1, fp);
	}
	
	
	fclose(fp);
}

void cetakmenu()
{
	system("cls");
	struct data master = { 0, "", "", 0};
	FILE *fp;
	if((fp = fopen("mastermenu.dat","rb"))== NULL){
		printf("File couldn't be opened\n");
	}
	else{
		printf("--------------------------------------------------\n");
		printf("-                   DAFTAR BARANG                -\n");
		printf("--------------------------------------------------\n");
		printf( "%-6s%-6s%-16s%-11s%10s\n","No", "Kode", "Merk", "Harga", "Stok" );
		while ( !feof( fp ) ) { 
         	if(fread( &master, sizeof( struct data ), 1, fp )){
				 if ( master.no != -1 ) {
					printf( "%-6d%-6s%-16s%-11d%10d\n", master.no, master.kode, master.merk, 
					master.harga, master.stok);
				}
			 }
      	}
      	printf("\n\n");
      fclose (fp);
	}
}

void editmenu()
{
	system("cls");
	struct data master = { 0, "", "", 0};
	
	FILE *fp;
	
	if((fp = fopen("mastermenu.dat","rb+"))== NULL){
		printf("File couldn't be opened\n");
	}
	
	cetakmenu();
	while(1){
	printf("Masukkan no urutan barang yang ingin diedit:\n");
	printf("(Masukkan -1 jika selesai)\n");
	scanf("%d", &master.no);
	if(master.no == -1){
		break;
	}
	printf("Masukkan id yang ingin diedit:\n");
	scanf("%s", master.kode);
	printf("Masukkan merk barang:\n");
	scanf(" %[^\n]", master.merk);
	printf("Maasukkan harga barang:\n");
	scanf("%d", &master.harga);
	printf("Masukkan harga modal:\n");
	scanf("%llu", &master.modal);
	printf("Masukkan stok barang:\n");
	scanf("%d", &master.stok);
	
	fseek( fp, ( master.no - 1 ) * sizeof( struct data ), SEEK_SET ); 
	fwrite(&master, sizeof(struct data ), 1, fp);
	
	}
	printf("\n\n");
	fclose(fp);	
}
