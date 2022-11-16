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

#ifndef _UNTERPROGRAMME_INC_
#define _UNTERPROGRAMME_INC_

#include <m16def.inc>
#include "init_def.inc"

/* In dieser Datei befinden sich die Definintionen für einige Unterprogramme für die Ampelsteuerung  */


	
/* im folgenden alle definintionen die die ampeln grün schalten */	
	

MACHE_A1_GRUEN: ;unterprog

	cbi PORTA, PA0 ;schalte rot aus
	cbi PORTA, PA1 ;schalte gelb aus
	sbi PORTA, PA2 ;schalte gruen ein

	ret



MACHE_AG2_GRUEN:  ;unterprog

	cbi PORTA, PA3 ;schalte rot aus
	cbi PORTA, PA4 ;schalte gelb aus
	sbi PORTA, PA5 ;schalte gruen ein

	ret


MACHE_F1_GRUEN:  ;unterprog
	
	cbi PORTA, PA6 ;schalte rot aus
	sbi PORTA, PA7 ;schalte gruen ein

	ret




MACHE_AR2_GRUEN: ;unterprog

	cbi PORTB, PA0 ;schalte rot aus
	cbi PORTB, PA1 ;schalte gelb aus
	sbi PORTB, PA2 ;schalte gruen ein

	ret


MACHE_A3_GRUEN: ;unterprog

	cbi PORTB, PA3 ;schalte rot aus
	cbi PORTB, PA4 ;schalte gelb aus
	sbi PORTB, PA5 ;schalte gruen ein

	ret

MACHE_F2_GRUEN: ;unterprog

	cbi PORTB, PA6 ;schalte rot aus
	sbi PORTB, PA7 ;schalte gruen ein

	ret

/* im folgenden alle definintionen die die ampeln gelb schalten */	

MACHE_A1_GELB:
	
	cbi PORTA, PA0 ;schalte rot aus
	sbi PORTA, PA1 ;schalte gelb ein
	cbi PORTA, PA2 ;schalte gruen aus

	ret


MACHE_AG2_GELB:

	cbi PORTA, PA3 ;schalte rot aus
	sbi PORTA, PA4 ;schalte gelb ein
	cbi PORTA, PA5 ;schalte gruen aus

	ret

; F1 gelb gibt es nicht weil es eine fußgängerampel ist die kein gelb hat



MACHE_AR2_GELB:

	cbi PORTB, PA0 ;schalte rot aus
	sbi PORTB, PA1 ;schalte gelb ein
	cbi PORTB, PA2 ;schalte gruen aus

	ret


MACHE_A3_GELB:

	cbi PORTB, PA3 ;schalte rot aus
	sbi PORTB, PA4 ;schalte gelb ein
	cbi PORTB, PA5 ;schalte gruen aus

	ret


; F2 gelb gibt es nicht weil es eine fußgängerampel ist die kein gelb hat; F1 gelb gibt es nicht weil es eine fußgängerampel ist die kein gelb hat






/* im folgenden alle definintionen die die ampeln rot schalten */	

MACHE_A1_ROT:
	
	sbi PORTA, PA0 ;schalte rot ein
	cbi PORTA, PA1 ;schalte gelb aus
	cbi PORTA, PA2 ;schalte gruen aus

	ret


MACHE_AG2_ROT:
	sbi PORTA, PA3 ;schalte rot ein
	cbi PORTA, PA4 ;schalte gelb aus
	cbi PORTA, PA5 ;schalte gruen aus

	ret


MACHE_F1_ROT:

	sbi PORTA, PA6 ;schalte rot ein
	cbi PORTA, PA7 ;schalte gruen aus

	ret



MACHE_AR2_ROT:

	sbi PORTB, PA0 ;schalte rot ein
	cbi PORTB, PA1 ;schalte gelb aus
	cbi PORTB, PA2 ;schalte gruen aus

	ret


MACHE_A3_ROT:

	sbi PORTB, PA3 ;schalte rot ein
	cbi PORTB, PA4 ;schalte gelb aus
	cbi PORTB, PA5 ;schalte gruen aus

	ret


MACHE_F2_ROT:

	sbi PORTB, PA6 ;schalte rot ein
	cbi PORTB, PA7 ;schalte gruen aus

	ret





/* im folgenden alle definintionen die die ampeln rot und gelb schalten */	


MACHE_A1_ROT_UND_GELB:
	
	sbi PORTA, PA0 ;schalte rot ein
	sbi PORTA, PA1 ;schalte gelb ein
	cbi PORTA, PA2 ;schalte gruen aus

	ret


MACHE_AG2_ROT_UND_GELB:

	sbi PORTA, PA3 ;schalte rot ein
	sbi PORTA, PA4 ;schalte gelb ein
	cbi PORTA, PA5 ;schalte gruen aus

	ret


; f1 hat kein gelb und kann somit nicht aktiviert werden





MACHE_AR2_ROT_UND_GELB:

	sbi PORTB, PA0 ;schalte rot ein
	sbi PORTB, PA1 ;schalte gelb ein
	cbi PORTB, PA2 ;schalte gruen aus

	ret



MACHE_A3_ROT_UND_GELB:

	sbi PORTB, PA3 ;schalte rot ein
	sbi PORTB, PA4 ;schalte gelb ein
	cbi PORTB, PA5 ;schalte gruen aus

	ret

; f2 hat kein gelb und kann somit nicht aktiviert werden






/* wait Unterprogramme folgen hier */

;warte für 10 sekunden
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
WARTE_FUER_10_SEKUNDEN:
	ldi cnt, 38 ; HIER NOCH ERKLÄRUNG WIE MAN AUF 38 KOMMT!


WARTE_FUER_10_SEKUNDEN_B:
	
	; Ressete die Register XL und XH
	ldi XL, 0xFF		;low wert der in LOOPINNER_WARTE_10_SEKUNDEN dekrementiert wird
	ldi XH, 0xFF		;low wert der in LOOPINNER_WARTE_10_SEKUNDEN dekrementiert wird
	dec cnt				
	brne LOOPINNER_WARTE_10_SEKUNDEN ; wenn cnt == 0 ist, dann wird das hier übersprungen
	
	ldi cnt, 38 ;restore
	;setzte bit0  in "war_eben_ein_event" auf 0 ; wichtig!
	ori war_eben_ein_event, 1 << switch


	ret
	
	
LOOPINNER_WARTE_10_SEKUNDEN:
	sbiw XH:XL, 1 ; sbiw takes 2 clocks
	brne LOOPINNER_WARTE_10_SEKUNDEN ;branch if not equal ; takes 2 clocks if condition is true
	jmp WARTE_FUER_10_SEKUNDEN_B


;ende des unterprogs: warte für 10 sekunden
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; warte für 3 sekunden
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

WARTE_FUER_3_SEKUNDEN: ;unterprog
	;wert der immer dekrementiert wird
	ldi cnt, 11 ; 3sekunden / 0,26 = 11 


WARTE_FUER_3_SEKUNDEN_B:
	
	; Ressete die Register XL und XH
	ldi XL, 0xFF		;low wert der in LOOPINNER_WARTE_10_SEKUNDEN dekrementiert wird
	ldi XH, 0xFF		;low wert der in LOOPINNER_WARTE_10_SEKUNDEN dekrementiert wird
	dec cnt				
	brne LOOPINNER_WARTE_3_SEKUNDEN ; wenn cnt == 0 ist, dann wird das hier übersprungen
	
	ldi cnt, 11 ;restore


	ret
	
	
LOOPINNER_WARTE_3_SEKUNDEN:
	sbiw XH:XL, 1 ; sbiw takes 2 clocks
	brne LOOPINNER_WARTE_3_SEKUNDEN ;branch if not equal ; takes 2 clocks if condition is true
	jmp WARTE_FUER_3_SEKUNDEN_B

; ende der definition für WARTE_FUER_3_SEKUNDEN
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; warte für 1 ms 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
WARTE_FUER_1_MS:
	/*
	(1ms * 1mhz) = 250
	muss 250 mal durchlaufen.
	takt /x = 250  | *x | /250
	takt / 250 = x

	x=  1mhz / 250 = 4000
	*/
	ldi XL, LOW(TAKT/4000)
	ldi XH, HIGH(TAKT/4000)


	WARTE_FUER_1_MS_B:
		sbiw XH:XL, 1
		brne WARTE_FUER_1_MS_B
		ret ;go back


;ende WARTE_FUER_1_MS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



/* hier stehen alle unterprogramme die überprüfen ob ein event von außen ausgelöst wurde. Außerdem verändern die Unterprogramme werte in registern */




CHECK_T1: ; unterprog für taster t1


	in temp, PINC ;lade pin register in temp register
	; wenn nicht gedrückt dann sieht temp so aus : 0b00000001
	

	;achtung pin register war hier falsch !!!!! an anderer stelle z.b. bei check_t2

	;t1 an pc0 angeschlossen


	sbrc temp, PC0;überprüfe ob t1 gerade gedrückt wird ; hier war fehler !!!! wenn gedrückt wird geskippt
		ret

	; hier ist klar das der taster gedrückt wurde

	sbrc t1_reg, 0; jetzt wird geprüft ob das 0te bit in t1_reg gesetzt ist. Wenn es gesetzt ist, dann führe ein return aus.

		;hier noch checken
		ret ;führe return aus, wenn bit 0 in t1_reg gesetzt ist
	



	;hier noch checken



	; an dieser Stelle ist klar das es nicht gesetzt ist


	; überprüfe nun ob das priority_reg == 4 ist. Wenn dies der Fall ist dann führe return aus.
	; Wenn das priority_reg einen Wert besitzt der etweder 3 , 2, 1, oder 0 ist dann überspringe.
	; es wird nun überprüft ob das 3te bit in priority_reg nicht gesetzt ist. Denn dann ist der Wert dieses Registers
	; ganz sicher nicht 4. Die bits 3,4,5,6,7 können nicht gesetzt werden weil es der Programmablauf so vorsieht.
	sbrc priority_reg, 3
		ret ; return


	sbr t1_reg, 1 ; setzte bit 0 in t1_reg ÜBERPRÜFEN !!!!!!!!! ;aktiviere diesen event
	
	/* das prioritäts register ist wie folgt aufgebaut.
	 
	 Es besteht aus 8 bit von denen aber nur die ersten 4 genutzt werden.
	 IN der Tabelle wird der Inhalt mit den entsprechenden Werten dargestellt.


	INHALT = 0 0 0 0 . 0 0 0 0			WERT = 0
	INHALT = 0 0 0 0 . 0 0 0 1			WERT = 1
	INHALT = 0 0 0 0 . 0 0 1 0			WERT = 2
	INHALT = 0 0 0 0 . 0 1 0 0			WERT = 3
	INHALT = 0 0 0 0 . 1 0 0 0			WERT = 4

	Eine Inkrementoperation auf 
	INHALT = 0 0 0 0 . 0 1 0 0			WERT = 3
	sieht wie folgt aus:
	INHALT = 0 0 0 0 . 1 0 0 0			WERT = 4

	*/


	

	; setzte das bit $(priority_reg +1) in t1_reg

	;wenn priority_reg leer ist dann setze das 0te bit also maximal die größe 3 erreicht hat
	;wenn nicht leer ist, dann linksschieben


	sbrc priority_reg, 2 ; Wenn das bit 2 in priority_reg == 0 ist dann wird übersprungen
		jmp IST_NICHT_LEER_CHECK_T1
	sbrc priority_reg, 1 ; Wenn das bit 1 in priority_reg == 0 ist dann wird übersprungen
		jmp IST_NICHT_LEER_CHECK_T1
	sbrc priority_reg, 0 ; Wenn das bit 0 in priority_reg == 0 ist dann wird übersprungen
		jmp IST_NICHT_LEER_CHECK_T1

	jmp IST_LEER_CHECK_T1 ; ok. kein bit in priority_reg ist gesetzt. ; rjmp nur zur übersichts halber

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		IST_LEER_CHECK_T1:
			; wenn es leer ist dann aktiviere das 1te bit in t1_reg
			sbr t1_reg, 2 ; hier wird das 1te bit im Register gesetzt

			
			sbr priority_reg, 1 ;setzte bit 0 in priority_reg


			jmp WEITER_GEHTS_MIT_DER_CHECK_ROUTINE_CHECK_T1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

		IST_NICHT_LEER_CHECK_T1:
			;z.b. t1_reg vorher 0b00000101
			lsl t1_reg ;linksschieben
			; nacher t1_reg 0b00001010
			cbr t1_reg, 2 ;cleare also 1tes bit 
			;nacher t1_reg 0b00001000
			sbr t1_reg, 1 ;und setzte 0tes bit
			;nacher t1_reg 0b00001001

			;jetzt inkrementire priority_reg
			lsl priority_reg ;linkschiebung von priority_reg

			jmp WEITER_GEHTS_MIT_DER_CHECK_ROUTINE_CHECK_T1 ;rjmp nur zur übersicht
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	

	WEITER_GEHTS_MIT_DER_CHECK_ROUTINE_CHECK_T1:



	ret ; go back






CHECK_T2: ; unterprog für taster t2
	
	in temp, PINC ;lade pin register in temp register
	; wenn nicht gedrückt dann sieht temp so aus : 0b00000010 ;bit 1 ist also gesetzt. die anderen bits eventuell auch.
	;ist hier aber nicht von bedeutung


	;t2 an pc1 angeschlossen

	sbrc temp, PC1 ;überprüfe ob t2 gerade gedrückt wird
		ret		; wird ausgeführt wenn bit 1 in pinc gesetzt ist!

	; hier ist klar das der taster gedrückt wurde

	sbrc t2_reg, 0; jetzt wird geprüft ob das 0te bit in t2_reg gesetzt ist. Wenn es gesetzt ist, dann führe ein return aus.
		ret ;führe return aus, wenn bit 0 in t2_reg gesetzt ist

	; an dieser Stelle ist klar das es nicht gesetzt ist


	; überprüfe nun ob das priority_reg == 4 ist. Wenn dies der Fall ist dann führe return aus.
	; Wenn das priority_reg einen Wert besitzt der etweder 3 , 2, 1, oder 0 ist dann überspringe.
	; es wird nun überprüft ob das 3te bit in priority_reg nicht gesetzt ist. Denn dann ist der Wert dieses Registers
	; ganz sicher nicht 4. Die bits 3,4,5,6,7 können nicht gesetzt werden weil es der Programmablauf so vorsieht.
	sbrc priority_reg, 3 
		ret ; return

	
	sbr t2_reg, 1 ; setzte bit 0 in t2_reg	
	
	/* das prioritäts register ist wie folgt aufgebaut.
	 
	 Es besteht aus 8 bit von denen aber nur die ersten 4 genutzt werden.
	 IN der Tabelle wird der Inhalt mit den entsprechenden Werten dargestellt.

	INHALT = 0 0 0 0 . 0 0 0 0			WERT = 0
	INHALT = 0 0 0 0 . 0 0 0 1			WERT = 1
	INHALT = 0 0 0 0 . 0 0 1 0			WERT = 2
	INHALT = 0 0 0 0 . 0 1 0 0			WERT = 3
	INHALT = 0 0 0 0 . 1 0 0 0			WERT = 4

	Eine Inkrementoperation auf 
	INHALT = 0 0 0 0 . 0 1 0 0			WERT = 3
	sieht wie folgt aus:
	INHALT = 0 0 0 0 . 1 0 0 0			WERT = 4

	*/

	; setzte das bit $(priority_reg +1) in t2_reg

	;wenn priority_reg leer ist dann setze das 0te bit also maximal die größe 3 erreicht hat
	;wenn nicht leer ist, dann linksschieben


	sbrc priority_reg, 2 ; Wenn das bit 2 in temp == 0 ist dann wird übersprungen
		jmp IST_NICHT_LEER_CHECK_T2
	sbrc priority_reg, 1 ; Wenn das bit 1 in temp == 0 ist dann wird übersprungen
		jmp IST_NICHT_LEER_CHECK_T2
	sbrc priority_reg, 0 ; Wenn das bit 0 in temp == 0 ist dann wird übersprungen
		jmp IST_NICHT_LEER_CHECK_T2

	jmp IST_LEER_CHECK_T2 ; ok. kein bit in priority_reg ist gesetzt. ; rjmp nur zur übersicht

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		IST_LEER_CHECK_T2:
		; wenn es leer ist dann aktiviere das 1te bit in t2_reg
			sbr t2_reg, 2 ;setzte hier das 1te bit

			sbr priority_reg, 1 ;setzte bit 0 in priority_reg

			jmp WEITER_GEHTS_MIT_DER_ROUTINE_CHECK_T2
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

		IST_NICHT_LEER_CHECK_T2:
			

			;z.b. t2_reg vorher 0b00000101
			lsl t2_reg ;linksschieben
			; nacher t2_reg 0b00001010
			cbr t2_reg, 2 ;cleare also 1tes bit 
			;nacher t2_reg 0b00001000
			sbr t2_reg, 1 ;und setzte 0tes bit
			;nacher t2_reg 0b00001001

			;jetzt inkrementire priority_reg
			lsl priority_reg ;linkschiebung von priority_reg


		
			jmp WEITER_GEHTS_MIT_DER_ROUTINE_CHECK_T2 ;rjmp nur zur übersicht
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


	WEITER_GEHTS_MIT_DER_ROUTINE_CHECK_T2:



	ret ; go back







CHECK_I1: ; unterprog für reed i1
	
	in temp, PINC ;lade pin register in temp register
	; wenn nicht gedrückt dann sieht temp so aus : 0b00000100

	;i1 an pc2 angeschlossen

	sbrc temp, PC2 ;überprüfe ob i1 gerade gedrückt wird
		ret		; wird ausgeführt wenn bit 1 in pinc gesetzt ist!

	; hier ist klar das der taster gedrückt wurde

	sbrc i1_reg, 0; jetzt wird geprüft ob das 0te bit in i1_reg gesetzt ist. Wenn es gesetzt ist, dann führe ein return aus.
		ret ;führe return aus, wenn bit 0 in i1_reg gesetzt ist

	; an dieser Stelle ist klar das es nicht gesetzt ist


	; überprüfe nun ob das priority_reg == 4 ist. Wenn dies der Fall ist dann führe return aus.
	; Wenn das priority_reg einen Wert besitzt der etweder 3 , 2, 1, oder 0 ist dann überspringe.
	; es wird nun überprüft ob das 3te bit in priority_reg nicht gesetzt ist. Denn dann ist der Wert dieses Registers
	; ganz sicher nicht 4. Die bits 3,4,5,6,7 können nicht gesetzt werden weil es der Programmablauf so vorsieht.
	sbrc priority_reg, 3 
		ret ; return

	
	sbr i1_reg, 1 ; setzte bit 0 in i1_reg	
	
	/* das prioritäts register ist wie folgt aufgebaut.
	 
	 Es besteht aus 8 bit von denen aber nur die ersten 4 genutzt werden.
	 IN der Tabelle wird der Inhalt mit den entsprechenden Werten dargestellt.

	INHALT = 0 0 0 0 . 0 0 0 0			WERT = 0
	INHALT = 0 0 0 0 . 0 0 0 1			WERT = 1
	INHALT = 0 0 0 0 . 0 0 1 0			WERT = 2
	INHALT = 0 0 0 0 . 0 1 0 0			WERT = 3
	INHALT = 0 0 0 0 . 1 0 0 0			WERT = 4

	Eine Inkrementoperation auf 
	INHALT = 0 0 0 0 . 0 1 0 0			WERT = 3
	sieht wie folgt aus:
	INHALT = 0 0 0 0 . 1 0 0 0			WERT = 4

	*/

	; setzte das bit $(priority_reg +1) in i1_reg

	;wenn priority_reg leer ist dann setze das 0te bit also maximal die größe 3 erreicht hat
	;wenn nicht leer ist, dann linksschieben


	sbrc priority_reg, 2 ; Wenn das bit 2 in priority_reg == 0 ist dann wird übersprungen
		jmp IST_NICHT_LEER_CHECK_I1
	sbrc priority_reg, 1 ; Wenn das bit 1 in priority_reg == 0 ist dann wird übersprungen
		jmp IST_NICHT_LEER_CHECK_I1
	sbrc priority_reg, 0 ; Wenn das bit 0 in priority_reg == 0 ist dann wird übersprungen
		jmp IST_NICHT_LEER_CHECK_I1

	jmp IST_LEER_CHECK_I1 ; ok. kein bit in priority_reg ist gesetzt. ; rjmp nur zur übersicht

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		IST_LEER_CHECK_I1:
		; wenn es leer ist dann aktiviere das 1te bit in t1_reg
			sbr i1_reg, 2 ;setzte hier das 1te bit
			sbr priority_reg, 1 ;setzte bit 0 in priority_reg

			jmp WEITER_GEHTS_MIT_DER_ROUTINE_CHECK_I1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

		IST_NICHT_LEER_CHECK_I1:
			
			;z.b. i1_reg vorher 0b00000101
			lsl i1_reg ;linksschieben
			; nacher i1_reg 0b00001010
			cbr i1_reg, 2 ;cleare also 1tes bit 
			;nacher i1_reg 0b00001000
			sbr i1_reg, 1 ;und setzte 0tes bit
			;nacher i1_reg 0b00001001

			;jetzt inkrementire priority_reg
			lsl priority_reg ;linkschiebung von priority_reg
			
			jmp WEITER_GEHTS_MIT_DER_ROUTINE_CHECK_I1 ;rjmp nur zur übersicht
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


	WEITER_GEHTS_MIT_DER_ROUTINE_CHECK_I1:
		ret ; go back




CHECK_I2: ; unterprog für reed i2
	
	in temp, PINC ;lade pin register in temp register
	; wenn nicht gedrückt dann sieht temp so aus : 0b00001000

	;i2 an pc3 angeschlossen
	sbrc temp, PC3 ;überprüfe ob i2 gerade gedrückt wird
		ret		; wird ausgeführt wenn bit 1 in pinc gesetzt ist!

	; hier ist klar das der taster gedrückt wurde

	sbrc i2_reg, 0; jetzt wird geprüft ob das 0te bit in i2_reg gesetzt ist. Wenn es gesetzt ist, dann führe ein return aus.
		ret ;führe return aus, wenn bit 0 in i2_reg gesetzt ist

	; an dieser Stelle ist klar das es nicht gesetzt ist


	; überprüfe nun ob das priority_reg == 4 ist. Wenn dies der Fall ist dann führe return aus.
	; Wenn das priority_reg einen Wert besitzt der etweder 3 , 2, 1, oder 0 ist dann überspringe.
	; es wird nun überprüft ob das 3te bit in priority_reg nicht gesetzt ist. Denn dann ist der Wert dieses Registers
	; ganz sicher nicht 4. Die bits 3,4,5,6,7 können nicht gesetzt werden weil es der Programmablauf so vorsieht.
	sbrc priority_reg, 3 
		ret ; return

	
	sbr i2_reg, 1 ; setzte bit 0 in i2_reg	
	
	/* das prioritäts register ist wie folgt aufgebaut.
	 
	 Es besteht aus 8 bit von denen aber nur die ersten 4 genutzt werden.
	 IN der Tabelle wird der Inhalt mit den entsprechenden Werten dargestellt.

	INHALT = 0 0 0 0 . 0 0 0 0			WERT = 0
	INHALT = 0 0 0 0 . 0 0 0 1			WERT = 1
	INHALT = 0 0 0 0 . 0 0 1 0			WERT = 2
	INHALT = 0 0 0 0 . 0 1 0 0			WERT = 3
	INHALT = 0 0 0 0 . 1 0 0 0			WERT = 4

	Eine Inkrementoperation auf 
	INHALT = 0 0 0 0 . 0 1 0 0			WERT = 3
	sieht wie folgt aus:
	INHALT = 0 0 0 0 . 1 0 0 0			WERT = 4

	*/

	; setzte das bit $(priority_reg +1) in i2_reg

	;wenn priority_reg leer ist dann setze das 0te bit also maximal die größe 3 erreicht hat
	;wenn nicht leer ist, dann linksschieben


	sbrc priority_reg, 2 ; Wenn das bit 2 in priority_reg == 0 ist dann wird übersprungen
		jmp IST_NICHT_LEER_CHECK_I2
	sbrc priority_reg, 1 ; Wenn das bit 1 in priority_reg == 0 ist dann wird übersprungen
		jmp IST_NICHT_LEER_CHECK_I2
	sbrc priority_reg, 0 ; Wenn das bit 0 in priority_reg == 0 ist dann wird übersprungen
		jmp IST_NICHT_LEER_CHECK_I2

	jmp IST_LEER_CHECK_I2 ; ok. kein bit in priority_reg ist gesetzt. ; rjmp nur zur übersicht

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		IST_LEER_CHECK_I2:
			sbr i2_reg, 2 ;setzte hier das 1te bit
			sbr priority_reg, 1 ;setzte bit 0 in priority_reg

			jmp WEITER_GEHTS_MIT_DER_ROUTINE_CHECK_I2
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

		IST_NICHT_LEER_CHECK_I2:
			
			;z.b. i2_reg vorher 0b00000101
			lsl i2_reg ;linksschieben
			; nacher i2_reg 0b00001010
			cbr i2_reg, 2 ;cleare also 1tes bit 
			;nacher i2_reg 0b00001000
			sbr i2_reg, 1 ;und setzte 0tes bit
			;nacher i2_reg 0b00001001

			;jetzt inkrementire priority_reg
			lsl priority_reg ;linkschiebung von priority_reg
			
			jmp WEITER_GEHTS_MIT_DER_ROUTINE_CHECK_I2 ;rjmp nur zur übersicht
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


	WEITER_GEHTS_MIT_DER_ROUTINE_CHECK_I2:

	ret ; go back







/* Interrupt timer */


INIT_TC0_TIMER_FUER_10_SEKUNDEN_UND_STARTE: ;unterprog
	
	sei ;enable global interrupts
	ret ;go back







TC0_OVF_HANDLER_10_SEKUNDEN: ;wird aufgerufen von interruptvekortabelle und läuft 10 sekunden
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
	
	*/
	inc ovf_cnt ;inkrementiere den zähler 

	; wenn ovf_cnt == 38 ist, dann übespringe ansonsten führe weiter aus
	; zahl 38 in binär ist 0b00100110
	sbrs ovf_cnt, 5
		reti
	sbrs ovf_cnt, 2
		reti
	sbrs ovf_cnt, 1
		reti

	;ok. hier ist klar das ovf_cnt == 38 ist. also wird weiter gearbeitet
	 
	 ldi ovf_cnt, 0x00 ;ovf_cnt muss ressetet werden !!!!!!!!

	 /* Entscheide hier nun welches unterprog ausgeführt werden soll. 
		für das Register in dem das 1te bit gesetzt ist, wird das Unterprog ausgeführt das zu dem Register das in dem ja
		das 1te bit gesetzt ist, ausgeführt. ES MUSS EIN REGISTER GEBEN IN DEM DAS 1BIT GESETZT IST!!!!!
	 */
	 
	 sbrc t1_reg, 1 ;skip if bit 1 in register is cleared
		call T1_UNTERPROG; t1_unterprog
	 sbrc t2_reg, 1 ;skip if bit 1 in register is cleared
		call T2_UNTERPROG; t2_unterprog
	 sbrc i1_reg, 1 ;skip if bit 1 in register is cleared
		call I1_UNTERPROG; i1_unterprog
	 sbrc i2_reg, 1 ;skip if bit 1 in register is cleared
		call I2_UNTERPROG; i2_unterprog



	/* nachdem unterprog aufgerufen werde, führe folgendes aus: */

	call CHANGE_PRIORITY_OF_REGISTER ;jetzt passe die Prioritäten der anderen register an
	
	;nächste zeile eventuell unnötig -> nein doch nicht unnötig
	ori war_eben_ein_event, 1 << switch ; schreibe eine 1 in das 0te bit 


	;beide 2 zeilen bald löschen 
	;jetzt muss noch die globale interruptfreigabe deaktiviert werden. das wird mit einem register gemacht
	;ori interruptbit_clearen, 1 << switch ; switch ist == 0 ;; setzte bit 0 in interruptbit_clearen
	
	reti ;back to main programm position










/* hier kommen nun die unterprogramme hin die unter anderem von TC0_OVF_HANDLER_10_SEKUNDEN aufgerufen werden  */



T1_UNTERPROG: ; verändert die Lichtsignale usw.
	
	/* verändere die ports an den ampeln */
	
	call ALLE_AMPELN_ROT ; mache zuerst alles rot ; muss überarbeitet werden es muss ja
						;von grün nach gelb und dann nach rot gewechselt werden
	
	call WARTE_FUER_3_SEKUNDEN ; und dann warte 3 sekunden damit andere autos die kreuzung verlassen können

	; dann verändere Lichtzeichen
	;f1 grün und ag2 grün
	call MACHE_F1_GRUEN
	call MACHE_AG2_GRUEN


	;setzte wert für dectozero registerpaar !!!!!!
	ldi dectozero_low, LOW(9708) ; Beschreibung unten!
	ldi dectozero_high, HIGH(9708) ;
	/* REchnung:
	Alles was in der WAIT_AND_CHECK_ROUTINE unterhalb der wait instruktion ausgeführt wird, benötigt ca 30 takte wenn kein schalter
	(event von menschen ausgelöst) gedrückt wird.
	da die WAIT_AND_CHECK_ROUTINE 10 sekunden laufen soll wird gerechnet:
	30 µS (weil 30 takte) + 1 mS = 1,03 mS
	10 Sekunden / 1,03 mS = 9708
	
	*/

	;calle wait_and_check_routine
	call WAIT_AND_CHECK_ROUTINE ;dauert 10 sekunden 

	;ok. jetzt schalten wir die ampel wieder auf rot
	;zuerst als die gelben lampen an und die grünen aus
	; ag2 gelb machen 
	; ACHTUNG!!!! F1 HAT KEIN GELB ALSO NICHT GELB MACHEN!!!!
	call MACHE_AG2_GELB



	;Jetzt warten wir 3 sekunden.
	/*
		In der VwV-StVO (Deutschland) wird die Dauer der Gelblichtphase abhängig
		von der zulässigen Höchstgeschwindigkeit der Zufahrt folgendermaßen 
		empfohlen: 3 s bei zul. v?=?50 km/h, 4 s bei zul. v?=?60 km/h und 5 s bei zul. v?=?70 km/h 
		(siehe § 37 Punkt 17 IX. VwV zur StVO). Die Gelblichtphase wird Entleerungsphase und Räumungszeit 
		genannt, da es während dieser Zeit möglich sein sollte, 
		den nachfolgenden Straßenabschnitt für den Verkehr zu räumen, der die Grünphase erhalten wird.
		quelle: http://de.wikipedia.org/wiki/Ampel unter kategorie Verhalten im geschützten Bereich einer Ampelanlage -> Gelblicht
	*/


	call WARTE_FUER_3_SEKUNDEN ; in dieser zeit kann kein signal von passanten entgegen genommen werden ;(

	;Jetzt alle Ampel rot machen
	call ALLE_AMPELN_ROT

	
	lsr priority_reg ; jetzt dekrementiere priority reg (rechtsverschiebung)

	clr t1_reg; jetzt cleare das t1_reg

	



	ret




T2_UNTERPROG: ; verändert die Lichtsignale usw.

	/* verändere die ports an den ampeln */
	
	call ALLE_AMPELN_ROT ; mache zuerst alles rot ; muss überarbeitet werden es muss ja
						;von grün nach gelb und dann nach rot gewechselt werden
	
	call WARTE_FUER_3_SEKUNDEN ; und dann warte 3 sekunden damit andere autos die kreuzung verlassen können

	; dann verändere Lichtzeichen
	;f2 grün und a1 grün
	call MACHE_F2_GRUEN
	call MACHE_A1_GRUEN


	;setzte wert für dectozero registerpaar !!!!!!
	ldi dectozero_low, LOW(9708) ; Beschreibung unten!
	ldi dectozero_high, HIGH(9708) ;
	/* REchnung:
	Alles was in der WAIT_AND_CHECK_ROUTINE unterhalb der wait instruktion ausgeführt wird, benötigt ca 30 takte wenn kein schalter
	(event von menschen ausgelöst) gedrückt wird.
	da die WAIT_AND_CHECK_ROUTINE 10 sekunden laufen soll wird gerechnet:
	30 µS (weil 30 takte) + 1 mS = 1,03 mS
	10 Sekunden / 1,03 mS = 9708
	
	*/

	;calle wait_and_check_routine
	call WAIT_AND_CHECK_ROUTINE ;dauert 10 sekunden 

	;ok. jetzt schalten wir die ampel wieder auf rot
	;zuerst als die gelben lampen an und die grünen aus
	; a1 gelb machen 
	; ACHTUNG!!!! F2 HAT KEIN GELB ALSO NICHT GELB MACHEN!!!!
	call MACHE_A1_GELB



	;Jetzt warten wir 3 sekunden.
	/*
		In der VwV-StVO (Deutschland) wird die Dauer der Gelblichtphase abhängig
		von der zulässigen Höchstgeschwindigkeit der Zufahrt folgendermaßen 
		empfohlen: 3 s bei zul. v?=?50 km/h, 4 s bei zul. v?=?60 km/h und 5 s bei zul. v?=?70 km/h 
		(siehe § 37 Punkt 17 IX. VwV zur StVO). Die Gelblichtphase wird Entleerungsphase und Räumungszeit 
		genannt, da es während dieser Zeit möglich sein sollte, 
		den nachfolgenden Straßenabschnitt für den Verkehr zu räumen, der die Grünphase erhalten wird.
		quelle: http://de.wikipedia.org/wiki/Ampel unter kategorie Verhalten im geschützten Bereich einer Ampelanlage -> Gelblicht
	*/


	call WARTE_FUER_3_SEKUNDEN ; in dieser zeit kann kein signal von passanten entgegen genommen werden ;(

	;Jetzt alle Ampel rot machen
	call ALLE_AMPELN_ROT

	
	lsr priority_reg ; jetzt dekrementiere priority reg (rechtsverschiebung)

	clr t2_reg; jetzt cleare das t2_reg

	



	ret




I1_UNTERPROG: ; verändert die Lichtsignale usw.


	/* verändere die ports an den ampeln */
	
	call ALLE_AMPELN_ROT ; mache zuerst alles rot ; muss überarbeitet werden es muss ja
						;von grün nach gelb und dann nach rot gewechselt werden
	
	call WARTE_FUER_3_SEKUNDEN ; und dann warte 3 sekunden damit andere autos die kreuzung verlassen können

	; dann verändere Lichtzeichen
	; a1 grün
	
	call MACHE_A1_GRUEN


	;setzte wert für dectozero registerpaar !!!!!!
	ldi dectozero_low, LOW(9708) ; Beschreibung unten!
	ldi dectozero_high, HIGH(9708) ;
	/* REchnung:
	Alles was in der WAIT_AND_CHECK_ROUTINE unterhalb der wait instruktion ausgeführt wird, benötigt ca 30 takte wenn kein schalter
	(event von menschen ausgelöst) gedrückt wird.
	da die WAIT_AND_CHECK_ROUTINE 10 sekunden laufen soll wird gerechnet:
	30 µS (weil 30 takte) + 1 mS = 1,03 mS
	10 Sekunden / 1,03 mS = 9708
	
	*/

	;calle wait_and_check_routine
	call WAIT_AND_CHECK_ROUTINE ;dauert 10 sekunden 

	;ok. jetzt schalten wir die ampel wieder auf rot
	;zuerst als die gelben lampen an und die grünen aus
	; a1 gelb machen 
	
	call MACHE_A1_GELB



	;Jetzt warten wir 3 sekunden.
	/*
		In der VwV-StVO (Deutschland) wird die Dauer der Gelblichtphase abhängig
		von der zulässigen Höchstgeschwindigkeit der Zufahrt folgendermaßen 
		empfohlen: 3 s bei zul. v?=?50 km/h, 4 s bei zul. v?=?60 km/h und 5 s bei zul. v?=?70 km/h 
		(siehe § 37 Punkt 17 IX. VwV zur StVO). Die Gelblichtphase wird Entleerungsphase und Räumungszeit 
		genannt, da es während dieser Zeit möglich sein sollte, 
		den nachfolgenden Straßenabschnitt für den Verkehr zu räumen, der die Grünphase erhalten wird.
		quelle: http://de.wikipedia.org/wiki/Ampel unter kategorie Verhalten im geschützten Bereich einer Ampelanlage -> Gelblicht
	*/


	call WARTE_FUER_3_SEKUNDEN ; in dieser zeit kann kein signal von passanten entgegen genommen werden ;(

	;Jetzt alle Ampel rot machen
	call ALLE_AMPELN_ROT

	
	lsr priority_reg ; jetzt dekrementiere priority reg (rechtsverschiebung)

	clr i1_reg; jetzt cleare das i1_reg

	



	ret








I2_UNTERPROG: ; verändert die Lichtsignale usw.



	/* verändere die ports an den ampeln */
	
	call ALLE_AMPELN_ROT ; mache zuerst alles rot ; muss überarbeitet werden es muss ja
						;von grün nach gelb und dann nach rot gewechselt werden
	
	call WARTE_FUER_3_SEKUNDEN ; und dann warte 3 sekunden damit andere autos die kreuzung verlassen können

	; dann verändere Lichtzeichen
	;ar2 grün und ag2 grün 
	call MACHE_AR2_GRUEN
	call MACHE_AG2_GRUEN


	;setzte wert für dectozero registerpaar !!!!!!
	ldi dectozero_low, LOW(9708) ; Beschreibung unten!
	ldi dectozero_high, HIGH(9708) ;
	/* REchnung:
	Alles was in der WAIT_AND_CHECK_ROUTINE unterhalb der wait instruktion ausgeführt wird, benötigt ca 30 takte wenn kein schalter
	(event von menschen ausgelöst) gedrückt wird.
	da die WAIT_AND_CHECK_ROUTINE 10 sekunden laufen soll wird gerechnet:
	30 µS (weil 30 takte) + 1 mS = 1,03 mS
	10 Sekunden / 1,03 mS = 9708
	
	*/

	;calle wait_and_check_routine
	call WAIT_AND_CHECK_ROUTINE ;dauert 10 sekunden 

	;ok. jetzt schalten wir die ampel wieder auf rot
	;zuerst als die gelben lampen an und die grünen aus
	; ar2 gelb machen und ag2 gelb machen 
	
	call MACHE_AR2_GELB
	call MACHE_AR2_GELB


	;Jetzt warten wir 3 sekunden.
	/*
		In der VwV-StVO (Deutschland) wird die Dauer der Gelblichtphase abhängig
		von der zulässigen Höchstgeschwindigkeit der Zufahrt folgendermaßen 
		empfohlen: 3 s bei zul. v?=?50 km/h, 4 s bei zul. v?=?60 km/h und 5 s bei zul. v?=?70 km/h 
		(siehe § 37 Punkt 17 IX. VwV zur StVO). Die Gelblichtphase wird Entleerungsphase und Räumungszeit 
		genannt, da es während dieser Zeit möglich sein sollte, 
		den nachfolgenden Straßenabschnitt für den Verkehr zu räumen, der die Grünphase erhalten wird.
		quelle: http://de.wikipedia.org/wiki/Ampel unter kategorie Verhalten im geschützten Bereich einer Ampelanlage -> Gelblicht
	*/


	call WARTE_FUER_3_SEKUNDEN ; in dieser zeit kann kein signal von passanten entgegen genommen werden ;(

	;Jetzt alle Ampel rot machen
	call ALLE_AMPELN_ROT

	
	lsr priority_reg ; jetzt dekrementiere priority reg (rechtsverschiebung)

	clr i2_reg; jetzt cleare das i2_reg


	ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

CHANGE_PRIORITY_OF_REGISTER:
	sbrc t1_reg, 0 ;skip if bit 0 in t1_reg is cleared
		call CHANGE_PRIORITY_OF_REGISTER_T1_REG;
	sbrc t2_reg, 0 ;skip if bit 0 in t2_reg is cleared
		call CHANGE_PRIORITY_OF_REGISTER_T2_REG
	sbrc i1_reg, 0 ;skip if bit 0 in i1_reg is cleared
		call CHANGE_PRIORITY_OF_REGISTER_I1_REG
	sbrc i2_reg, 0 ;skip if bit 0 in i2_reg is cleared
		call CHANGE_PRIORITY_OF_REGISTER_I2_REG


	ret ; wenn kein register existiert in dem das 0te bit gesetzt ist, return


CHANGE_PRIORITY_OF_REGISTER_T1_REG: 
	lsr t1_reg ; rechtsverschiebung . hierbei wird das 0te bit gecleared.
	sbr t1_reg, 1 ;darum muss es wieder gesetzt werden
	ret ; go back



CHANGE_PRIORITY_OF_REGISTER_T2_REG: 
	lsr t2_reg ; rechtsverschiebung . hierbei wird das 0te bit gecleared.
	sbr t2_reg, 1 ;darum muss es wieder gesetzt werden
	ret ; go back



CHANGE_PRIORITY_OF_REGISTER_I1_REG: 
	lsr i1_reg ; rechtsverschiebung . hierbei wird das 0te bit gecleared.
	sbr i1_reg, 1 ;darum muss es wieder gesetzt werden
	ret ; go back



CHANGE_PRIORITY_OF_REGISTER_I2_REG: 
	lsr I2_reg ; rechtsverschiebung . hierbei wird das 0te bit gecleared.
	sbr I2_reg, 1 ;darum muss es wieder gesetzt werden
	ret ; go back



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


WAIT_AND_CHECK_ROUTINE:
	;erstmal 1ms warten
	call WARTE_FUER_1_MS


	/*
		Überprüfung ob insgesamt 10 Sekunden vergangen sind.
		Für jeden Durchlauf der "1ms Warteschleife" wird "dectozero" REgisterpaar dekrementiert.
		Wenn der Wert 0 erreicht, dann wird die "wait & check routine" beendet.
	*/

	/* dekrementiere dectozero */
	
	sbiw dectozero_high:dectozero_low, 1 ; sbiw takes 2 clocks

	breq RETURN_FROM_WAIT_AND_CHECK_ROUTINE ; wenn dectozero == 0 dann breche aus WAIT_AND_CHECK_ROUTINE
	


	
	

	/* überprüfung ob event's ausgelöst wurden */

	call CHECK_T1
	call CHECK_T2
	call CHECK_I1
	call CHECK_I2



	rjmp WAIT_AND_CHECK_ROUTINE



	


RETURN_FROM_WAIT_AND_CHECK_ROUTINE:
	;WICHTIG!!!!! SETZTE dectozero registerpaar zurück !!!!!
	ldi dectozero_low, LOW(9708) ; setze zurück
	ldi dectozero_high, HIGH(9708) ;

	ret

#endif
