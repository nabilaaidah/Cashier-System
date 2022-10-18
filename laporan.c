#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "header.h"

void pilihlaporan(){
	int n;
	system("cls");
	printf("Pilih:\n");
	printf("(1)Laporan\n(2)Riwayat Transaksi\n(0)Kembali\n");
	scanf("%d", &n);
	printf("\n");
	if(n == 1){
		laporan();
	}
	else if(n == 2){
		history();
	}
	else if(n == 0){
		return;
	}
	printf("\n\n");
}

void laporan()
{
	struct data master = { 0, "", "", 0};
	system("cls");
	FILE *fp;
	
	if((fp = fopen("mastermenu.dat","rb+"))== NULL){
		printf("File couldn't be opened\n");
	}
	
	unsigned long long modal = 0;
	unsigned long long totalsemua = 0;
	unsigned long long totalterjual = 0;
	unsigned long long laba;
	printf("HASIL LAPORAN:\n");
	printf( "%-6s%-14s%-8s%-11s%-10s%-10s%-10s%\n", "KODE", "MERK" , "JUMLAH", "STOK",
					"MODAL", "HARGA", "TOTAL");
	while ( !feof( fp ) ) { 
         	if(fread( &master, sizeof( struct data ), 1, fp )){
				 if (master.no != -1) {
					printf( "%-6s%-14s%-8d%-11d%-10d%-10d%-10d%\n", master.kode, master.merk , master.jumlah, master.stok,
					master.modal, master.harga, master.total);
					modal += (master.modal*master.paten);
					totalsemua += master.total;
					totalterjual += master.jumlah;
				}
			 }
      	}
      	
    fclose(fp);
    printf("\n\n");
    printf("Modal 				= %llu \n", modal);
    printf("Total barang terjual \t\t= %llu \n", totalterjual);
    printf("Pemasukan 			= %llu \n", totalsemua);
    laba = modal - totalsemua;
    if(laba < 0){
    	printf("Keterangan 			= Untung sejumlah %llu \n", laba*-1);
	}
	else{
		printf("Keterangan 			= Rugi sejumlah %llu \n", laba);
	}	
	
}

void waktu(struct data master)
{
	int d,m,y;
	time_t t;
	time(&t);
	
	struct tm *time = localtime(&t);
	d = time->tm_mday;
	m = time->tm_mon + 1;
	y = time->tm_year + 1900;
	
	struct data bill = { 0, "", "", 0};
	
	FILE *fp;
	
	if((fp = fopen("riwayat.dat","ab+"))== NULL){
		printf("File couldn't be opened\n");
	}
	
	bill.no = master.no;
	strcpy(bill.kode,master.kode);
	strcpy(bill.merk,master.merk);
	bill.harga = master.harga;
	bill.jumlah = master.jumlah;
	bill.total = master.total;
	strcpy(bill.time,ctime(&t));
	bill.day = d;
	bill.month = m;
	bill.year = y;
	
	fseek( fp, ( bill.no - 1 ) * sizeof( struct data ), SEEK_SET ); 
	fwrite(&bill, sizeof(struct data ), 1, fp);
	
	fclose(fp);
}

void history()
{
	struct data bill = { 0, "", "", 0};
	system("cls");
	FILE *fp;
	
	if((fp = fopen("riwayat.dat","rb+"))== NULL){
		printf("File couldn't be opened\n");
	}
	
	int mintgl, maxtgl, minbln, maxbln, minthn, maxthn;
	
	while(1){
		printf("Masukkan -1 jika selesai\n");
		printf("Tanggal awal:\n");
		scanf("%d %d %d", &mintgl, &minbln, &minthn);
		if(mintgl == -1 || maxtgl == -1 || minbln == -1|| maxbln == -1 || minthn == -1||maxthn == -1){
			break;
		}
		printf("\nTanggal akhir:\n");
		scanf("%d %d %d", &maxtgl, &maxbln, &maxthn);
		printf( "\n%-6s%-16s%-10s%-11s%-10s%-10s%\n","Kode", "Merk", "Jumlah", "Harga", "Total", "Waktu" );
		while ( !feof( fp ) ) { 
         	if(fread( &bill, sizeof( struct data ), 1, fp )){
				 if ( bill.no != -1 ) {
				 	if(bill.day >= mintgl && bill.day <= maxtgl && bill.month >= minbln && bill.month <= maxbln && bill.year >= minthn && bill.year <= maxthn)
				 	{
					printf( "%-6s%-16s%-10d%-11d%-10d%-10s%\n", bill.kode, bill.merk, bill.jumlah, 
					bill.harga, bill.total, bill.time);
				}
				}
			 }
      	}
      	printf("\n\n");
	}
	fclose (fp);
}
