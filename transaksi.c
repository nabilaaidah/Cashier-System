#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "header.h"

void pilihtransaksi()
{
	int n;
	system("cls");
	while(1){
		printf("Pilih salah satu:\n");
		printf("(1)Beli Produk\n(2)Print Receipt\n(0)Back\n\n");
		scanf("%d", &n);
		printf("\n\n");
		if(n == 1){
			buyproduct();
		}
		else if(n == 2){
			printreceipt();
		}
		else if(n == 0){
			return;
		}
	}
}


void buyproduct()
{
	system("cls");
	struct data master = { 0, "", "", 0};
	struct receipt bill = { 0, "", "", 0};
	FILE *fp;
	if((fp = fopen("mastermenu.dat", "rb+")) == NULL){
		printf("File could not be opened\n");
	}
	
	FILE *pf;
	if((pf = fopen("rc.txt", "wb+")) == NULL){
		printf("File could not be opened\n");
	}
	int total = 0;
	int count;
	
	cetakmenu();
	while(1){
		printf("Masukkan no barang yang akan dibeli:\n");
		printf("(Masukkan -1 jika selesai)\n");
		scanf("%d", &master.no);
		if(master.no == -1){
			break;
		}
		
		fseek( fp, ( master.no - 1 ) * sizeof( struct data ), SEEK_SET );
		fread(&master, sizeof(struct data ), 1, fp);
		
		printf("\n\nInformasi produk:\n");
		printf("%-6s%-6s%-16s%-11s%10s\n","No", "Kode", "Merk", "Harga", "Stok");
		printf( "%-6d%-6s%-16s%-11d%10d\n", master.no, master.kode, master.merk, 
		master.harga, master.stok);
      	printf("\n");
		
		if(master.stok > 0){
			printf("Masukkan jumlah barang yang dibeli\n");
			scanf("%d", &count);
			if(count != 0 && master.stok >= count){
				master.jumlah = count;
				master.stok = master.stok - count;
				total = master.harga * count;
				master.total = total;
				total = 0;
				count = 0;
				fseek( fp, ( master.no - 1 ) * sizeof( struct data ), SEEK_SET ); 
				fwrite(&master, sizeof(struct data ), 1, fp);
				waktu(master);
				bill.no = master.no;
				strcpy(bill.kode,master.kode);
				strcpy(bill.merk,master.merk);
				bill.jumlah = master.jumlah;
				bill.harga = master.harga;
				bill.total = master.total;
				
				fseek( pf, 0 * sizeof( struct receipt ), SEEK_SET );
				fwrite(&bill, sizeof(struct receipt ), 1, pf);
				freopen("rc.txt", "ab+", pf);

			}
		}
	}
	fclose(fp);
	fclose(pf);
}


void printreceipt()
{
	time_t t;
	time(&t);
	system("cls");
	struct receipt bill = { 0, "", "", 0};
	FILE *pf;	
	if((pf = fopen("rc.txt","rb"))== NULL){
		printf("File couldn't be opened\n");
	}
	int total = 0;
	printf("--------------------------BILL----------------------\n\n");
	printf("\t\t%s\n", ctime(&t));
	printf("=====================================================\n");
	printf( "%-6s%-16s%-10s%-11s%10s\n","Kode", "Merk", "Jumlah", "Harga", "Harga Total" );
	while ( !feof( pf ) ) { 
         	if(fread( &bill, sizeof( struct receipt ), 1, pf )){
				 	if(bill.no != -1){
					printf( "%-6s%-16s%-10d%-11d%10d\n", bill.kode, bill.merk , bill.jumlah,
					bill.harga, bill.total);
				}
				total += bill.total;
			 }
      	}
      	printf("TOTAL = %d", total);
      	printf("\n\n");
      fclose (pf);
}
