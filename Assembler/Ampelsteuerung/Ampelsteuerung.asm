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

#include <m16def.inc>
#include "init_def.inc"
#include "unterprogramme.inc"

/* todo:
	es muss noch eine umschaltroutine geschrieben werden die die ampeln umschaltet 
 */

 
;Alle Ampeln sind rot
MAIN:
	call ALLE_AMPELN_ROT ; mache alle ampeln rot. definition steht in init_def.inc
	
	call MACHE_A3_GRUEN ;mache A3 grün
	call MACHE_AG2_GRUEN ;mache Ag2 grün 
	


	
	cli ; globale interruptfreigabe clearen






MAIN_CHECK: ;hier wird abgefragt ob etwas gedrückt/betätigt wurde. Z.B. Taster t1 oder reed kontakt i1
	
	
	
	call CHECK_T1
	call CHECK_T2
	call CHECK_I1
	call CHECK_I2
	



	CHECK_PRIORITY_REG_NULL:
	; überprüfe hier ob priority_reg == 0 ist
		sbrc priority_reg, 3 ;skip if bit is cleared
			jmp CHECK_PRIORITY_REG_NULL_PRIORITY_REG_IST_NICHT_NULL
		sbrc priority_reg, 2
			jmp CHECK_PRIORITY_REG_NULL_PRIORITY_REG_IST_NICHT_NULL
		sbrc priority_reg, 1
			jmp CHECK_PRIORITY_REG_NULL_PRIORITY_REG_IST_NICHT_NULL
		sbrc priority_reg, 0
			jmp CHECK_PRIORITY_REG_NULL_PRIORITY_REG_IST_NICHT_NULL

		jmp CHECK_PRIORITY_REG_NULL_PRIORITY_REG_IST_NULL ;wenn dies hier aufgerufen, dann ist das priority register == 0

	CHECK_PRIORITY_REG_NULL_PRIORITY_REG_IST_NULL:
		







		jmp MAIN_CHECK ;springe zurück, damit weiter pins geprüft werden können


	CHECK_PRIORITY_REG_NULL_PRIORITY_REG_IST_NICHT_NULL: ;priority_reg ist nicht 0
		;hier gehts weiter mit der verarbeitung








	;überprüfung ob eben ein event war. wenn ja dann jmp MAIN
	sbrc war_eben_ein_event, switch ;switch == 0 ; skip if bit 0 in register is cleared
		jmp MAIN

	;überprüfe nun ob die globale interruptfreigabe aktiviert ist. wenn ja dann jmp to MAIN_CHECK
	brie MAIN_CHECK ;branch if global interrupt bit is set ;ok fehler ; er brancht nicht wenn das interruptbit gesetzt ist.

	;simulator brancht hier nicht wenn interrupt bit gesetzt ist????? Der Simulator ist kaputt ! ;(
	; Im avr studio 4 funktioniert es 

	/*
		setzte nun den interrupt timer für 10 sekunden und aktiviere ihn!
	*/
	call INIT_TC0_TIMER_FUER_10_SEKUNDEN_UND_STARTE ;setze timer auf 10 sekunden und starte ihn.
	;globale interruptfreigabe existiert also danach
	;jetzt wird weiter überprüft und bald schon wird der timerinterrupt ausgelöst. 

	jmp MAIN_CHECK ; springe zurück um weiter zu überprüfen.
