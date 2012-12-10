#include <compiler_defs.h>
#include <C8051F020_defs.h>
#include <TS_vInterface.h>
#include <bubble.h>


SBIT (RX, SFR_P1, 0);
SBIT (TX, SFR_P1, 1);

//--Settings------------------------------------------------------------------------

void init_Device(void) {

		WDTCN = 0xDE ; 
		WDTCN = 0xAD ;

		SilabsInit020 () ;

		SPI0CN    = 0x01; 
	
    	P0MDOUT   = 0x08;
    	P1MDOUT   = 0x02;

    	XBR0      = 0x06;
    	XBR2      = 0x40;
		

}


//--TXRX_for_slave---------------------------------------------------------------------


int Recieve_Data_Slave(void){
	int i;
	int GG;

	while (RX == 0) ;
	TX = 1;
	while (SLVSEL == 0);
	while(SLVSEL == 1);
	for (i = 0; i < 10; i++);
	GG = SPI0DAT;

	RXOVRN = 0;
	SPIF = 0;
	WCOL = 0;
	TX = 0;

return(GG);


}

void Send_Data_Slave(int GG){
	int i;
	for (i = 0; i < 10; i++);
	SPI0DAT = GG;
	for (i = 0; i < 10; i++);
	TX = 1;
	while (RX == 0) ;
	while (SLVSEL == 0);
	while(SLVSEL == 1);

	RXOVRN = 0;
	SPIF = 0;
	WCOL = 0;
	TX = 0;

}


//--Main_Program-----------------------------------------------------------------------

void main(void) {
	int pdata Dat1[100];
	int *pa;
	int *pb;
	int count;
	int FE;
	int i;

	init_Device();
	
	//Recieve Data
	pa = Dat1;
	count = 0;
	while (count <= 99){
		for (i = 0; i < 10; i++);
		*pa = Recieve_Data_Slave();
		for (i = 0; i < 10; i++);
		TerminalWrite(*pa);
		count++;
		*pa++;
	}

	//Bubble Sort
	for (i = 0; i < 100; i++);
	bubble_sort(Dat1,100);
	for (i = 0; i < 100; i++);

	//Send Data
	pb = Dat1;
	count = 0;
	while (count <= 99) {
		for (i = 0; i < 10; i++);
		FE = *pb;
		for (i = 0; i < 10; i++);
		TerminalWrite(FE);
		for (i = 0; i < 10; i++);
		Send_Data_Slave(FE);
		for (i = 0; i < 10; i++);
		count++;
		*pb++;
	}
	
}