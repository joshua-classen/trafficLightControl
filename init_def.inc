/*
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License Veriosn 3 as 
published by the Free Software Foundation;
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with
this program; if not, see <http://www.gnu.org/licenses/>. 
Author: Joshua Claßen
*/

#ifndef _INIT_DEF_INC_
#define _INIT_DEF_INC_
#include <m16def.inc>




/*
konstanten für die ampelportansteuerung
*/

/*
Im folgenden alle als Ausgang definierten Ports:
A1:
	Port PA0 mit R_A1_ROT
	Port PA1 mit R_A1_GELB
	Port PA2 mit R_A1_GRUEN
	
	
AG2:
	Port PA3 mit R_AG2_ROT
	Port PA4 mit R_AG2_GELB
	Port PA5 mit R_AG2_GRUEN
	
	
F1:
	Port PA6 mit R_F1_ROT
	Port PA7 mit R_F1_GRUEN
	
	
AR2:
	Port PB0 mit R_AR2_ROT
	Port PB1 mit R_AR2_GELB
	Port PB2 mit R_AR2_GRUEN
	
	
A3:
	Port PB3 mit R_A3_ROT
	Port PB4 mit R_A3_GELB
	Port PB5 mit R_A3_GRUEN
	

	
F2:
	Port PB6 mit R_F2_ROT
	Port PB7 mit R_F2_GRUEN

*/


/*
Nun kommen alle als Eingang definierten Ports:
Bei den Ports werden die Pull up Widerstände softwareseitig aktiviert.
Taster t1:

	TASTER1L und TASTER1R mit PC0
	
TASTER t2:
	
	TASTER2L und TASTER2R mit PC1
	
REED I1:
	Plus Seite des Reed Kontakts mit Port PC2 verbunden
	
REED I2:
	Plus Seite des Reed Kontakts mit Port PC3 verbunden
	
*/


/*
definitionen für einige Register
*/


.def temp = r16 ;temporäres register
.def t1_reg = r17 ;prioritäts register für t1
.def t2_reg = r18 ;prioritäts register für t2
.def i1_reg = r19 ;prioritäts register für i1
.def i2_reg = r20 ;prioritäts register für i2
.def priority_reg = r21 ;prioritäts register
.def dectozero = r22 ; HIER NOCH BESCHREIBUNG
.def war_eben_ein_event = r23 ; HIER NOCH BESCHREIBUNG



/* die Register t1_reg, t2_reg, i1_reg, i2_reg geben später darüber auskunft welches event ausgeführt 
	wird und mit welcher priorität / in welcher reihenfolge.
	
	
	
	BEISPIEL AUFBAU t1_reg:
	
			bit7	bit6	bit5	bit4	bit3	bit2	bit1	bit0
										
			0		0		0		0		0	 	0		0		0
	
	
			Wenn das 0te bit gesetzt ist, dann heißt das, dass das jemand auf den taster t1 gedrückt hat und
			das event für t1 noch nicht gestartet wurde oder gerade läuft. Wenn das event für t1 abgeschlossen ist, dann wird
			das 0te bit gecleart.
			jetzt müsste erst jemand wieder auf den Taster t1 drücken damit es wieder aktiviert wird.
			
			
			
			Wenn beispielsweise nach einem reset des controllers als erstes der taster t1 gedrückt wurde, 
			dann wird das 1te bit in t1_reg gesetzt.
			
			Die bits 1 bis bit 4 geben über die Ausführungsreihenfolge der events auskunft.
			Wenn das erste bit für t1_reg gesetzt ist dann hat das event t1 die höchtse priorität
			
			
			Wenn z.B. jemand nach betätigung des t1 taster den t2 taster drückt, dann
			wird das bit 0 und das 2te bit in t2_reg gesetzt.
			
			
			D.h. das nun erst das t1 event ausgeführt wird weil es die höchtse priorität hat.
			Wenn das t1 event abgeschlossen ist dann wird das bit 2 in t2_reg gecleart und das 1te bit gesetzt
			t1 hat nun die höchste priorität.

 */

 
 
 /*
	Das priority_reg gibt darüber Auskunft
	wie viele events ausgeführt werden. 
	
	wenn alle bits im priority_reg gecleart sind, dann bedeutet dies, dass kein event ausgeführt werden wird.
	Wenn das 0te bit im priority_reg gesetzt ist dann bedeutet dies das 1 event ausgeführt werden wird oder gerade ausgeführt wird.
	beim 1ten bit genauso.
	beim 2ten bit genauso.
	beim 3ten bit genauso.
	Es kann kein höheres bit als das 3te gesetzt werden, weil nur maximal 4 events ausgelöst werden können.
	
	Es werden z.B. alle Taster und alle reed kontakte hintereinander aktiviert.
	Dann ist das 3te bit im priority_reg gesetzt.
	
	Wenn man jetzt z.B. auf t1 drückt, dann bleibt das 3te bit im priority_reg aktiviert, weil das 0te bit im t1_reg 
	aktiviert ist.
 
 
 */


/* dectozero registerpaar */

.def dectozero_low = r28 ; produziert warnung weil r28 schon als yl zugewiesen ist. ist aber egal
.def dectozero_high = r29 ;

;nachfolgendes später löschen 
/* register das dafür benötigt wird um zu überprüfen ob das interruptbit im sreg gecleart werden soll oder nicht
	ist das 0te bit gesetzt dann heißt das, dass das interruptbit gecleart werden soll!
*/

;.def interruptbit_clearen = r30 ;
;hier ende der löschung

/*register das die timer interrupt überläufe zählt */


.def ovf_cnt = r25

/*definition register für zeitschleife */
.def cnt = r24 ;
/* 
in m16def.inc steht
<zitat>
.def	XH	= r27
.def	XL	= r26
</zitat>
diese beiden register werden für die zählschleife benutzt


 */

/*konstanten */

.equ switch = 0 ;
.equ TAKT = 1000000 ; der Standart Takt ist 1 MHZ



/* interruptvektortabelle */

.org 0x0000				; Adresse im 2er schritt ;Die Interruptvektortabelle beginnt bei 0x0000 
rjmp    MIN_INIT		;1 POWER ON RESET 
.org 0x0002
reti					;2 Int0-Interrupt 
.org 0x0004
reti					;3 Int1-Interrupt 	
.org 0x0006
reti					;4 timer2 comp
.org 0x0008
reti					;5 timer2 ovf
.org 0x000a
reti					;6 timer1 capt
.org 0x000c
reti					;7 timer1 compA
.org 0x000e
reti					;8 timer1 compB
.org 0x0010
reti					;9 timer1 ovf
.org 0x0012
rjmp TC0_OVF_HANDLER_10_SEKUNDEN	;10 timer0 ovf
.org 0x0014
reti					;11 spi, stc
.org 0x0016
reti					;12 usart,rxc
.org 0x0018
reti					;13 usart, udre
.org 0x001a
reti					;14 usart,txc
.org 0x001c
reti					;15 adc
.org 0x001e
reti					;16 ee_rdy
.org 0x0020
reti					;17 ana_comp
.org 0x0022
reti					;18 twi
.org 0x0024
reti					;19 int2
.org 0x0026
reti					;20 timer0 comp
.org 0x0028
reti					;21 spm_rdy



MIN_INIT:						;RESET Label 
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	ldi temp, high(RAMEND)	;Initialisierung des Stackpointers 
	out SPH, temp			;erst das High - Byte 
	ldi temp, low(RAMEND) 
	out SPL, temp			;dann das Low - Byte
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; nötig um alle pins an portc zu verwenden

	in temp,MCUCSR				 ; Read MCUCSR
	ori      temp,1 << JTD        ; Set jtag disable flag
	out      MCUCSR, temp         ; Write MCUCSR
	out      MCUCSR, temp        ; and again as per datasheet 
	


	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	call INIT_REGISTERS /* Register initialisierung */
	call INIT_PORTS /* inititalisiert alle ports und initialisiert pull up widestände */
	call INIT_TC0  ; init timer


	call ALLE_AMPELN_ROT /* schalte alle Ampeln auf rot */




	
	jmp MAIN ;springe zum hauptprogramm
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	



/* Register initialisierung */
INIT_REGISTERS: ;unterprog

	ldi temp, 0x00
	ldi t1_reg, 0x00
	ldi t2_reg, 0x00
	ldi i1_reg, 0x00
	ldi i2_reg, 0x00
	ldi priority_reg, 0x00
	ldi dectozero, 0x00 ;;ACHTUNG!!!! WERT MUSS NOCH BESTIMMT WERDEN
	ldi war_eben_ein_event, 0x00
	ldi ovf_cnt, 0x00
	;;; cnt bekommt Wert in unterprogramme.inc zugewiesen

	;ldi interruptbit_clearen, 0x00 ; standartmäßig soll es nicht gecleart werden. gibt warnung




	ret


	
/*Portinitialisierung*/

INIT_PORTS: ;unterprog
	/* Alle als Ausgang definierten Ports */
	
	;pa0 bis pa7 als ausgang
	ori temp, ( 1 << PA0 | 1 << PA1 | 1 << PA2 | 1 << PA3 | 1 << PA4 | 1 << PA5 | 1 << PA6 | 1 << PA7 )
	out DDRA, temp
	;ende init portA

	;pb0 bis pb7 als ausgang
	ori temp, ( 1 << PB0 | 1 << PB1 | 1 << PB2 | 1 << PB3 | 1 << PB4 | 1 << PB5 | 1 << PB6 | 1 << PB7 )
	out DDRB, temp
	;ende init portB







	/* ddrd als ausgang debuging */

	ldi temp, 0xFF
	out DDRD, temp



	/* Alle als Eingang definierten Ports */

	;pc0 bis pc7 als eingang
	ori temp, ( 0 << PC0 | 0 << PC1 | 0 << PC2 | 0 << PC3 |0 << PC4 |0 << PC5 | 0 << PC6 | 0 << PC7  ) 
	/* pc4 bis pc7 werden nicht gebraucht und einfach als eingang definiert */
	out DDRC, temp 
	;ende init portc

	; AKTIVIERUNG VON PULL UP bei PORTC:
	/* pc4 bis pc7 werden nicht gebraucht, trotzdem aktiviere pull up auch für diese */
	ori temp, ( 1 << PC0 | 1 << PC1 | 1 << PC2 | 1 << PC3 | 1 << PC4 | 1 << PC5 | 1 << PC6 | 1 << PC7  ) 
	out PORTC, temp ; aktivierung pull up 


	ret ;go back
	
	
ALLE_AMPELN_ROT: ; unterprog
	/* erst portA */
	ori temp, ( 1 << PA0 | 1 << PA3 | 1 << PA6 ) ; pa0 , pa3, pa6 sind die pins an portA an denen die roten leds angeschlossen sind
	out PORTA, temp ; Alle roten leds an porta anschalten



	/* port B */

	ori temp, ( 1 << PB0 | 1 << PB3 | 1 << PB6 ) ; pb0 , pb3, pb6 sind die pins an portB an denen die roten leds angeschlossen sind
	out PORTB, temp ; Alle roten leds an PortB anschalten

	ret ; go back



INIT_TC0: ;unterprog
	/* 
		Der Timer wird so eingestellt, dass er bei einem Takt von 1 Mhz alle 0,26 sekunden einen overflow hat
		REchnung:

		Wie oft wird das timer zähl register pro sekunde erhörht?
		1MHZ / 1024 =  976 mal in der Sekunde

		Wie lange dauert es bis das 8 bit register überläuft?

		255 / 976 = 0,26 sekunden



		Wenn 10 sekunden gewartet werden soll, dann muss das Register  38 mal überlaufen!


		Rechung:

		10 sekunden / 0,26 sekunden  = 38 mal überlaufen
		
		DIES WIRD ALLES IN TC0_OVF_HANDLER_10_SEKUNDEN IMPLEMENTIERT!!!
	
	 */


	
	ldi  temp, 0b00000101  ;Prescaler auf 1/1024 einstellen 
	out  TCCR0, temp    ;und damit TC0 starten 
	in    temp, TIMSK    ;Timer Interrupt Mask Register in r16 laden 
	ori  temp, 1 << TOIE0  ;TC0 Overflow Interrupt freigeben 
	out  TIMSK, temp    ;alle anderen Bits in TIMSK unverändert


	ret



#endif
