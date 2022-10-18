#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "header.h"

int main (){
	int n;
	system("cls");
	printf("--------------------------------------------------\n");
	printf("-                 SELAMAT DATANG               	 -\n");
	printf("-                        DI                      -\n");
	printf("-                    TOKO BUKU                   -\n");
	printf("--------------------------------------------------\n");

	while(1){
	printf("Pilih:\n");
	printf("(1)Daftar Barang\n(2)Transaksi\n(3)Laporan\n(4)Edit Menu\n(0)Selesai\n");
	printf("\n");
	scanf("%d", &n);
	printf("\n\n");
	if(n == 1){
		cetakmenu();
	}
	else if(n == 2){
		pilihtransaksi();
	}
	else if(n == 3){
		pilihlaporan();
	}
	else if(n == 4){
		pilihmenu();
	}
	else if(n == 0){
		break;
	}
}
}
