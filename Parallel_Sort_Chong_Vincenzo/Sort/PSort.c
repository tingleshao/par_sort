#include <compiler_defs.h> 
#include <C8051F020_defs.h>
#include <TS_vInterface.h>
#include <bubble.h>
#include <merge.h>


SBIT (flow, SFR_P3, 7);
SBIT (MSet, SFR_P0, 5);
SBIT (SEn, SFR_P0, 6);
SBIT (RX, SFR_P1, 0);
SBIT (TX, SFR_P1, 1);

//--Settings---------------------------------------------------------------------------------------------------------


void init_Device(void) {


			WDTCN = 0xDE;
			WDTCN = 0xAD;

			SilabsInit020 ();
			
   			SPI0CN    = 0x03;
    		SPI0CKR   = 0x22;

    		P0MDOUT   = 0x54;
    		P1MDOUT   = 0x02;

    		XBR0      = 0x06;
    		XBR2      = 0x40;
			
			MSet = 1;
			SEn = 1;
}



//--TXRX_for_Master--------------------------------------------------------------------------------------------------



void Send_Data_Master(int va){
	int i;
	SEn = 1;
	TX = 1;
	while (RX == 0);
	SEn = 0;
	for (i = 0; i< 10; i++);
	SPI0DAT = va;
	for (i = 0; i< 10; i++);
	while (TXBSY == 1);
	SEn = 1;
	for (i = 0; i< 10; i++);
	while(RX == 1);
	TX = 0;

}



int Recieve_Data_Master(void){
	int i;
	int va;
	int UDat;

	SEn = 1;
	UDat = 0x00;
	while (RX == 0);
	TX = 1;
	SEn = 0;
	for (i = 0; i< 10; i++);
	SPI0DAT = UDat;
	for (i = 0; i< 10; i++);
	while (TXBSY == 1);
	SEn = 1;
	for (i = 0; i< 10; i++);
	while(RX == 1);
	TX = 0;
	va = SPI0DAT;

return(va);
}





//--Main_Program----------------------------------------------------------------------------------------------------





void main(void) {
	int xdata Dat1[500];
	int xdata Dat2[400];
	int xdata Dat3[500];
	int xdata Dat4[100];
	int tempdata;
	int i;
	int count;
	int *pa;
	int *pc;
	int *d2;
	int *d4;
	int *d3;

	init_Device();



	//Recieve Initial Data Set
	pa = Dat1;
	count = 0;
	d2 = Dat2;
	while(count <= 499) {
		flow = 0;
		*pa = TerminalRead();
		for (i = 0; i< 10; i++);
		if (count < 400){
			*d2 = *pa;
			for (i = 0; i< 10; i++);
			*d2++;
		}
		count++;
		*pa++;
		for (i = 0; i< 10; i++);
	}


	//Store My Data and Send Slave Data to Slave
	count = 0;
	pc = Dat1;
	for ( i = 0; i < 400 ; i++){
		*pc++ ;
	}
	while(count <= 99) {
		Send_Data_Master(*pc);
		for (i = 0; i< 10; i++);
		*pc++;
		count++;
	}

	//Bubble Sort My Data
	for (i = 0; i< 100; i++);
	bubble_sort(Dat2,400);
	for (i = 0; i< 100; i++);


	//Recieve and Store Slave Data
	count = 0;
	d4 = Dat4;
	while(count <= 99) {
		tempdata = Recieve_Data_Master();
		for (i = 0; i< 10; i++);
		*d4 = tempdata;
		for (i = 0; i< 10; i++);
		count++;
		*d4++;
	}


	//Merge Sort Both Data Sets
	for (i = 0; i< 100; i++);
	merge(Dat2, Dat4, Dat3,400,100,500);
	for (i = 0; i< 100; i++);


	//Send Sorted Data Set
	d3 = Dat3;
	for (i = 0; i< 10; i++);
	count = 0;
	while(count <= 499) {
		tempdata = *d3;
		for (i = 0; i< 10; i++);
		TerminalWrite(tempdata);
		for (i = 0; i< 10; i++);
		count++;
		*d3++;
	}



}