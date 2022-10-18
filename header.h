#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

struct receipt{
	int no;
	char kode[5];
	char merk[1000];
	int harga;
	int jumlah;
	unsigned long long total;
};

struct data{
	int no;
	char kode[5];
	char merk[1000];
	int harga;
	int jumlah;
	int stok;
	int modal;
	unsigned long long total;
	int day;
	int month;
	int year;
	char time[50];
	int paten;
};


void pilihmenutransaksi();
void pilihtransaksi();
void pilihmenu();
void inputmenu();
void cetakmenu();
void editmenu();
void waktu(struct data master);
void buyproduct();
void printreceipt();
void pilihlaporan();
void laporan();
void history();
