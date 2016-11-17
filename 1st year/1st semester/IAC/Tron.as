;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Grupo 51			;
; 78682 - Francisco Duarte 	;
; 80996 - Joao Silvestre   	;
; 81418 - Goncalo Soares   	;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;Temporizador;;;;;;;;;;;;;;
COUNT_TIMER	EQU FFF6h	;
CONTROL_TIMER	EQU FFF7h	;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;Janela de Texto;;;;;;;;;;;
IO_STATUS	 EQU FFFDh	; Porto de Estado
IO_CONTROL	 EQU FFFCh	; Porto de Controlo	
IO_WRITE	 EQU FFFEh	; Porto de Escrita
IO_READ		 EQU FFFFh	; Porto de Leitura
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;Display;;;;;;;;;;;;;;;
NIBBLE_MASK EQU 000fh		;
NUM_NIBBLES EQU 4		;
BITS_PER_NIBBLE EQU 4		;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;LCD;;;;;;;;;;;;;;;;;;;;;;;
LCD_CONTR 	EQU FFF4h 	; Porto de controlo no LCD
LCD_WR 		EQU FFF5h 	; Porto de escrita no LCD
LCD1_0		EQU 8000h 	; Primeira linha e coluna do LCD
LCD1_11		EQU 800Bh	; Primeira linha e 12 coluna do LCD
LCD1_12		EQU 800Ch	; Primeira linha e 13 coluna do LCD
LCD1_13		EQU 800Dh	; Primeira linha e 14 coluna do LCD
LCD1_14		EQU 800Eh	; Primeira linha e 15 coluna do LCD
LCD1_15		EQU 800Fh	; Primeira linha e 16 coluna do LCD
LCD2_0		EQU 8010h	; Segunda linha e primeira coluna do LCD
LCD2_4		EQU 8014h	; Segunda linha e 5 coluna do LCD
LCD2_10		EQU 801Ah	; Segunda linha e 11 coluna do LCD
LCD2_14		EQU 801Dh	; Segunda linha e 15 coluna do LCD
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;Interrupcoes;;;;;;;;
INT_MASK_ADD	EQU FFFAh	; 
INT_MASK1	EQU 0002h	; Controla a interrupcao I1
INT_MASK2	EQU 8A81h	; Jogador 1, 2 e temporizador 
INT_MASK3	EQU 8801h	; Jogador 2 e o temporizador
INT_MASK4	EQU 8280h	; Jogador 1 e o temporizador
INT_MASK5	EQU 8000h	; Controla as interrupcoes do temporizador										
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;;;;Interruptor;;;;;;;;;
INTER_MASK_ADD	EQU FFF9h	;
INTER_MASK1 	EQU 0080h	;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;;;;;;;;;LEDS;;;;;;;;;;;
LED_MASK_N1	EQU 000Fh	; Acender os 4 LEDS da direita
LED_MASK_N2	EQU 00FFh	; Acender os 8 LEDS da direita
LED_MASK_N3	EQU 0FFFh	; Acender os 12 LEDS da direita
LED_MASK_N4	EQU FFFFh	; Acender os 16 LEDS da direita
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;Dados;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	ORIG	8000h
				
				
;;;;;;;;;Constantes;;;;;;;;;;;;;;
CIMA		EQU	FF00h	;
BAIXO		EQU	0100h	; 
ESQ		EQU	FFFFh	; 
DIR		EQU	0001h	; 
CODESP		EQU	0020h	; Codigo ASCII de espaço
COD| 		EQU 	007Ch	; Codigo ASCII de simbolo |
CODLIN		EQU 	002Dh	; Codigo ASCII de simbolo -
CODMAIS		EQU	002Bh	; Codigo ASCII de simbolo +
CODA		EQU	0023h	; Código ASCII de simbolo X
CODC		EQU	0058h	; Codigo ASCII de simbolo #
LEDS		EQU	FFF8h	; Endereco do conunto de 16 LEDS
DISPLAY		EQU	FFF0h	; Endereco do de 7 LEDS da direita do display de 7 segmentos
COMECA		WORD 	0000h	;
ESQ1		WORD	0001h	;	
DIR1		WORD	0002h	;
ESQ2		WORD	0003h	;
DIR2		WORD	0004h	;
TEMPO		WORD	0005h	; Tempo de o temporizador dar uma interrupcao
TICK		WORD 	0000h	; Ciclos de 0.1s provocando a mudanca de nivel
NIVEL		WORD	0000h	; Intervalo de tempo de cada ciclo de jogo
FIM_JOGO	WORD	0000h	; Indica se o jogo acabou ou nao
SEGUNDO		WORD	0000h	; 
TIMER		WORD    0000h	; Comparado com 10 ciclos de 0.1s
RELOGIO     	WORD    0000h	; Tempo atual do jogo		
T_MAX		WORD 	0000h	; Tempo maximo registado na funcao relogio		
VITORIAS1	WORD 	0000h	; N de vitorias do jogador 1
VITORIAS2	WORD	0000h	; N de vitorias do jogador 2
T_REC     	WORD	0000h	; Tempo maximo registado no LCD
DEZENAS1   	WORD	0000h	; A parte das dezenas do n de vitorias do jogador 1
DEZENAS2    	WORD	0000h	; A parte das dezenas do n de vitorias do jogador 2
PAUSAZINHA	WORD	0000h	; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
					
					
;;;;;;;;;;;;;;;;;;;;Mensagens;;;;;;;;;;;;;;;;;;;;;;;;;;;;
MSG1 	STR 'Bem-vindo ao TRON@'			;
MSG2 	STR 'Prima o interruptor I1 para comecar@'	;
MSG3	STR 'Fim do jogo@'				;
MSG4	STR 'Pressione I1 para recomecar@' 		;
MSG5	STR 'TEMPO MAX: 0000s@'				;
MSG6	STR 'J1: 00@'					;
MSG7 	STR 'J2: 00@'					;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	


;;;;;;Tabela de Interrupcoes;;;;;
	ORIG 	FE00h		;
INT0	WORD	ESQUERDA1	;
INT1 	WORD 	COMECAR		;
				;
	ORIG	FE07h		;
INT7	WORD 	ESQUERDA2	;
				;
	ORIG	FE09h		;
INT9	WORD 	DIREITA2	;
				;
	ORIG	FE0Bh		;
INTB	WORD	DIREITA1	;
				;
	ORIG	FE0Fh		;
INT15	WORD	TEMPORIZADOR	;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;			
;;Inicializacoes;;
;;;;;;;;;;;;;;;;;;

	ORIG 	0000h
	MOV 	R1, FFFFh		; Inicializa o cursor da janela de texto
	MOV	M[IO_CONTROL], R1
	MOV	R1, FDFFh		; Inicializa a pilha
	MOV	SP, R1
	MOV	R1, INT_MASK1
	MOV	M[INT_MASK_ADD], R1 	; Ativa so a interrupcao I1
				
	JMP	INICIO
	ORIG 	3000h
				
;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;Interrupcoes;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;

;---------------------------------------------------------------------------------------------------------------------------------------------------------
;COMECAR: Rotina que incrementa a variavel COMECA
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: ----
;	Saidas: ----
;	Efeitos: Alteracao do conteudo da posicao de memoria M[COMECA]
;---------------------------------------------------------------------------------------------------------------------------------------------------------
			
COMECAR:	INC 	M[COMECA]
		RTI
				
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;PAUSA: Rotina que incrementa a variavel PAUSAZINHA
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: M[PAUSAZINHA]
;	Saidas: ----
;	Efeitos: Alteracao do conteudo da posicao de memoria M[PAUSAZINHA]
;---------------------------------------------------------------------------------------------------------------------------------------------------------

PAUSA:		INC	M[PAUSAZINHA]
		RET
			
		
;---------------------------------------------------------------------------------------------------------------------------------------------------------
; TESTEPAUSA: Rotina que verifica se foi seleccionada a opcao pausa
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: M[PAUSAZINHA]
;	Saidas:	----
;	Efeitos: ----
;---------------------------------------------------------------------------------------------------------------------------------------------------------

TESTEPAUSA:	PUSH	R1
		PUSH	R2
		MOV 	R2,M[INTER_MASK_ADD]
		AND 	R2, INTER_MASK1
		CALL.NZ PAUSA 
		MOV	R1, 1h
		CMP 	M[PAUSAZINHA],R1
		CALL.Z	PAROU
		INC	R1
		CMP	M[PAUSAZINHA],R1
		CALL.Z	SAIPAUSA
		POP 	R2
		POP	R1
		RET

;---------------------------------------------------------------------------------------------------------------------------------------------------------
; SAIPAUSA: Rotina responsavel pela reposicao das condicoes normais de jogo apos a saida do modo pausa.
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: ----
;	Saidas:	----
;	Efeitos: ----
;---------------------------------------------------------------------------------------------------------------------------------------------------------

SAIPAUSA:	MOV	M[PAUSAZINHA], R0
		ENI
		RET		

;---------------------------------------------------------------------------------------------------------------------------------------------------------
; PAROU: Rotina responsavel pela estagnacao das variaveis e das condicoes de jogo quando pressionado o interruptor IA.
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: ----
;	Saidas:	----
;	Efeitos: ----
;---------------------------------------------------------------------------------------------------------------------------------------------------------

PAROU:		PUSH	R1
		PUSH	R2
		PUSH 	R3
		DSI
Fica:		MOV R2,M[INTER_MASK_ADD]
		AND R2, INTER_MASK1
		CALL.Z PAUSA
		MOV	R3,2d
		CMP	M[PAUSAZINHA],R3
		JMP.NZ	Fica
		POP R3
		POP	R2
		POP	R1
		RET			

;---------------------------------------------------------------------------------------------------------------------------------------------------------
;ESQUERDA1: Rotina responsavel por virar a particula 1 a esquerda
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: ----
;	Saidas: ----
;	Efeitos: Vira a particula 1 para a esquerda
;---------------------------------------------------------------------------------------------------------------------------------------------------------

ESQUERDA1:	INC M[ESQ1]
		RTI

;---------------------------------------------------------------------------------------------------------------------------------------------------------
;DIREITA1: Rotina responsavel por virar a particula 1 a direita
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: ----
;	Saidas: ----
;	Efeitos: Vira a particula 1 para a direita
;---------------------------------------------------------------------------------------------------------------------------------------------------------				

DIREITA1:	INC M[DIR1]
		RTI

;---------------------------------------------------------------------------------------------------------------------------------------------------------
;ESQUERDA2: Rotina responsavel por virar a particula 2 a esquerda
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: ----
;	Saidas: ----
;	Efeitos: Vira a particula 2 para a esquerda
;---------------------------------------------------------------------------------------------------------------------------------------------------------				

ESQUERDA2:	INC M[ESQ2]
		RTI

;---------------------------------------------------------------------------------------------------------------------------------------------------------
;DIREITA2: Rotina responsavel por virar a particula 2 a direita
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: ----
;	Saidas: ----
;	Efeitos: Vira a particula 2 para a direita
;---------------------------------------------------------------------------------------------------------------------------------------------------------					

DIREITA2:	INC M[DIR2]
		RTI
				
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;TEMPORIZADOR: Rotina responsavel por incrementar o TICK, NIVEL e TIMER a cada ciclo de 0.1s
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: ----
;	Saidas: ----
;	Efeitos: 
;---------------------------------------------------------------------------------------------------------------------------------------------------------					

TEMPORIZADOR:	PUSH 	R1
		INC	M[TICK]
		INC	M[NIVEL]
		INC	M[TIMER]
		MOV 	R1, M[TEMPO]
		MOV 	M[COUNT_TIMER], R1
		MOV 	R1, 1h
		MOV 	M[CONTROL_TIMER], R1
		POP 	R1
		RTI
				
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;D_RELOGIO: Rotina responsavel por contar o tempo decorrido 
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: ----
;	Saidas: ----
;	Efeitos: Efetua a contagem do tempo
;---------------------------------------------------------------------------------------------------------------------------------------------------------
							
D_RELOGIO: 	PUSH R1
		PUSH R2
		PUSH R3
		PUSH R4
		INC M[RELOGIO]
		MOV R2, NUM_NIBBLES
		MOV R3, DISPLAY
Proximodisp: 	MOV R1, M[RELOGIO]
		AND R1, NIBBLE_MASK
		CMP R1, 000Ah
		CALL.Z MUDA
		MOV M[R3], R1
		ROR M[RELOGIO], BITS_PER_NIBBLE
		INC R3
		DEC R2
		BR.NZ  Proximodisp
		MOV M[T_MAX], R1
		MOV M[TIMER], R0
		POP R4
		POP R3
		POP R2
		POP R1
		RET						
				
MUDA: 		ADD R1,6d
		MOV R4,6d
		ADD M[RELOGIO], R4
		RET
				
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;MSG_BV: Rotina responsavel pela escrita da mensagem inicial do jogo 
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: ----
;	Saidas: ----
;	Efeitos: Escreve a mensagem inicial do jogo
;---------------------------------------------------------------------------------------------------------------------------------------------------------

MSG_BV:		MOV 	R1, 0C1Fh	; Onde escreve a primeira mensagem
		MOV	R2, MSG1 
		MOV	R3, M[R2]
		CALL	ESCREVE_MSG
		MOV	R1, 0D16h	; Onde escreve a segunda mensagem
		MOV	R2, MSG2
		MOV	R3, M[R2]
		CALL	ESCREVE_MSG
		RET

;---------------------------------------------------------------------------------------------------------------------------------------------------------
;ESCREVE_MSG: Rotina responsavel pela escrita de mensagens na janela de texto
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: R1, R2, R3
;	Saidas: ----
;	Efeitos: Escreve mensagens na janela de texto
;---------------------------------------------------------------------------------------------------------------------------------------------------------
	
ESCREVE_MSG:	MOV 	M[IO_CONTROL], R1
		MOV 	M[IO_WRITE], R3
		INC 	R1
		INC 	R2
		MOV 	R3, M[R2]
		CMP	R3, 0040h
		BR.NZ	ESCREVE_MSG
		RET
	
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;LIMPA_MAPA: Rotina responsavel por apagar o campo de jogo
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: ----
;	Saidas: ----
;	Efeitos: Coloca o caracater ' ' em todas as posicoes  do campo de jogo
;---------------------------------------------------------------------------------------------------------------------------------------------------------

LIMPA_MAPA:	MOV R2, 0001h
		MOV R1, CODESP
		MOV R4, 1501h
CICLO_LIMPA:	CALL APAGA_LINHA
		ADD R2, 0100h
		CMP R2, R4
		BR.NZ CICLO_LIMPA
		RET

;---------------------------------------------------------------------------------------------------------------------------------------------------------
;ESCREVE_MAPA: Rotina responsavel pela escrita do campo de novo jogo
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: ----
;	Saidas: ----
;	Efeitos: Coloca os bordos no novo campo de jogo
;---------------------------------------------------------------------------------------------------------------------------------------------------------

ESCREVE_MAPA: 	MOV R2, 020Fh
		CALL ESCREVE_COLUNA
		MOV R2, 0240h
		CALL ESCREVE_COLUNA
		MOV R2, 0110h
		MOV R1, CODLIN
		CALL ESCREVE_LINHA
		MOV R2, 1610h
		CALL ESCREVE_LINHA
		CALL ESCREVE_CANTOS
		MOV R1, 0B18h
		MOV R3, 0B37h
		CALL ESCREVE_PARTICULAS
		RET
				
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;ESCREVE_COLUNA: Rotina responsavel pela escrita de uma coluna no campo de jogo
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: R2
;	Saidas: ----
;	Efeitos: Preenche uma coluna com o caracter '|' 
;---------------------------------------------------------------------------------------------------------------------------------------------------------

ESCREVE_COLUNA:	MOV R1, COD|
		MOV R3, R2
		ADD R3, 1400h
CICLO_C:	MOV M[IO_CONTROL], R2
		MOV M[IO_WRITE], R1
		MOV M[R2], R1
		ADD R2, 0100h
		CMP R2, R3
		BR.NZ CICLO_C
		RET

;---------------------------------------------------------------------------------------------------------------------------------------------------------
;APAGA_LINHA: Rotina responsavel por apagar uma linha no campo de jogo
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: R2
;	Saidas: ----
;	Efeitos: Preenche uma linha com o caracter ' ' 
;---------------------------------------------------------------------------------------------------------------------------------------------------------				

APAGA_LINHA:	MOV R3, R2
		ADD R3, 0030h
CICLO_L2:	MOV M[IO_CONTROL], R2
		MOV M[IO_WRITE], R1
		INC R2
		CMP R2, R3
		BR.NZ CICLO_L2
		RET

;---------------------------------------------------------------------------------------------------------------------------------------------------------
;ESCREVE_LINHA: Rotina responsavel pela escrita de uma linha no campo de jogo
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: R2
;	Saidas: ----
;	Efeitos: Preenche uma linha com o caracter '-' 
;---------------------------------------------------------------------------------------------------------------------------------------------------------

ESCREVE_LINHA:	MOV R3, R2
		ADD R3, 0030h
CICLO_L1:	MOV M[IO_CONTROL], R2
		MOV M[IO_WRITE], R1
		MOV M[R2], R1
		INC R2
		CMP R2, R3
		BR.NZ CICLO_L1
		RET

;---------------------------------------------------------------------------------------------------------------------------------------------------------
;ESCREVE_CANTOS: Rotina responsavel pela escrita dos cantos no campo de jogo
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: ----
;	Saidas: ----
;	Efeitos: Preenche numa posicao definida o caracter '+' 
;---------------------------------------------------------------------------------------------------------------------------------------------------------

ESCREVE_CANTOS:	MOV R1, 010Fh
		MOV R2, CODMAIS
		MOV M[IO_CONTROL], R1
		MOV M[IO_WRITE], R2
		MOV R1, 160Fh
		MOV M[IO_CONTROL], R1
		MOV M[IO_WRITE], R2
		MOV R1, 0140h
		MOV M[IO_CONTROL], R1
		MOV M[IO_WRITE], R2
		MOV R1, 1640h
		MOV M[IO_CONTROL], R1
		MOV M[IO_WRITE], R2				
		RET

;---------------------------------------------------------------------------------------------------------------------------------------------------------
;ESCREVE_PARTICULAS: Rotina responsavel de uma particula no campo de jogo
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: R1, R3
;	Saidas: ----
;	Efeitos: Preenche nas posicaos dadas os caracteres '#' e 'X'
;---------------------------------------------------------------------------------------------------------------------------------------------------------				

ESCREVE_PARTICULAS:	PUSH R6
			PUSH R5
			MOV R5, CODA
			MOV R6, CODC
			MOV M[IO_CONTROL], R1
			MOV M[IO_WRITE], R5
			MOV M[IO_CONTROL], R3
			MOV M[IO_WRITE], R6
			MOV M[R1],  R5
			MOV M[R3], R5
			POP R5
			POP R6
			RET

;---------------------------------------------------------------------------------------------------------------------------------------------------------
;VAI_COMECAR: Rotina responsavel pelo o inicio do jogo
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: ----
;	Saidas: R1, R2, R3 , R4, R5, R6, R7
;	Efeitos: 	R1-->Posicao inicial da particula1, R2-->Direcao da particula1, 
;			R3-->Posicao inicial da particula2, R4-->Direcao da particula2, 
;			R5-->Inicializa ciclo de 1 segundo, R6-->Tempo para comecar o segundo nivel, 
;     			R7-->Intervalo de tempo em cada ciclo de jogo no primeiro nivel
;---------------------------------------------------------------------------------------------------------------------------------------------------------

VAI_COMECAR:	MOV R3, 1d
		MOV M[TEMPO], R3
		MOV R1, INT_MASK2
		MOV M[INT_MASK_ADD], R1
		MOV R1, M[TEMPO]
		MOV M[COUNT_TIMER], R1
		MOV R1, 1
		MOV M[CONTROL_TIMER], R1
		MOV R1, 0B18h
		MOV R2, BAIXO
		MOV R3, 0B37h
		MOV R4, CIMA
		MOV R5, 000Ah
		MOV R6, 0064h
		MOV R7, 0007h
		RET
						
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;VIRAR_DIR1: Rotina responsavel pela mudanca de direcao da particula 1 para a direita
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: R2
;	Saidas: R2
;	Efeitos: Verifica a direcao da particula 1 e muda a sua direcao para a direita em relacao a posicao anterior
;---------------------------------------------------------------------------------------------------------------------------------------------------------		

VIRAR_DIR1: 	DSI
		DEC M[DIR1]
		CMP R2, CIMA
		BR.NZ D_COMP_DIR1
		MOV R2, DIR
		BR D_1_INT
D_COMP_DIR1:	CMP R2, DIR
		BR.NZ D_COMP_BAIXO1
		MOV R2, BAIXO
		BR D_1_INT
D_COMP_BAIXO1:	CMP R2, BAIXO
		BR.NZ D_COMP_ESQ1
		MOV R2, ESQ
		BR D_1_INT
D_COMP_ESQ1:	MOV R2, CIMA
D_1_INT:	CALL PARA_INT1	
		ENI
		RET				
				
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;VIRAR_ESQ1: Rotina responsavel pela mudanca de direcao da particula 1 para a esquerda
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: R2
;	Saidas: R2
;	Efeitos: Verifica a direcao da particula 1 e muda a sua direcao para a esquerda em relacao a posicao anterior
;---------------------------------------------------------------------------------------------------------------------------------------------------------

VIRAR_ESQ1: 	DSI
		DEC M[ESQ1]
		CMP R2, CIMA
		BR.NZ E_COMP_DIR1
		MOV R2, ESQ
		BR E_1_INT
E_COMP_DIR1:	CMP R2, DIR
		BR.NZ E_COMP_BAIXO1
		MOV R2, CIMA
		BR E_1_INT
E_COMP_BAIXO1:	CMP R2, BAIXO
		BR.NZ E_COMP_ESQ1
		MOV R2, DIR
		BR E_1_INT
E_COMP_ESQ1:	MOV R2, BAIXO
E_1_INT:	CALL PARA_INT1
		ENI
		RET		

;---------------------------------------------------------------------------------------------------------------------------------------------------------
;VIRAR_DIR2: Rotina responsavel pela mudanca de direcao da particula 2 para a direita
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: R4
;	Saidas: R4
;	Efeitos: Verifica a direcao da particula 2 e muda a sua direcao para a direita em relacao a posicao anterior
;---------------------------------------------------------------------------------------------------------------------------------------------------------


VIRAR_DIR2: 	DSI
		DEC M[DIR2]
		CMP R4, CIMA
		BR.NZ D_COMP_DIR2
		MOV R4, DIR
		BR D_2_INT
D_COMP_DIR2:	CMP R4, DIR
		BR.NZ D_COMP_BAIXO2
		MOV R4, BAIXO
		BR D_2_INT
D_COMP_BAIXO2:	CMP R4, BAIXO
		BR.NZ D_COMP_ESQ2
		MOV R4, ESQ
		BR D_2_INT
D_COMP_ESQ2:	MOV R4, CIMA
D_2_INT:	CALL PARA_INT2
		ENI
		RET		

;---------------------------------------------------------------------------------------------------------------------------------------------------------
;VIRAR_ESQ2: Rotina responsavel pela mudanca de direcao da particula 2 para a esquerda
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: R4
;	Saidas: R4
;	Efeitos: Verifica a direcao da particula 2 e muda a sua direcao para a esquerda em relacao a posicao anterior
;---------------------------------------------------------------------------------------------------------------------------------------------------------

VIRAR_ESQ2: 	DSI
		DEC M[ESQ2]
		CMP R4, CIMA
		BR.NZ E_COMP_DIR2
		MOV R4, ESQ
		BR E_2_INT
E_COMP_DIR2:	CMP R4, DIR
		BR.NZ E_COMP_BAIXO2
		MOV R4, CIMA
		BR E_2_INT
E_COMP_BAIXO2:	CMP R4, BAIXO
		BR.NZ E_COMP_ESQ2
		MOV R4, DIR
		BR E_2_INT
E_COMP_ESQ2:	MOV R4, BAIXO
E_2_INT:	CALL PARA_INT2
		ENI
		RET		

;---------------------------------------------------------------------------------------------------------------------------------------------------------
;PARA_INT1: Rotina responsavel por impedir o jogador 1 de jogar mais que uma vez no mesmo ciclo
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: ----
;	Saidas: ----
;	Efeitos: Muda de mascara de interrupcoes tendo em conta se o jogador 2 ja jogou 
;---------------------------------------------------------------------------------------------------------------------------------------------------------			

PARA_INT1:	PUSH R6
		MOV R6, INT_MASK2
		CMP M[INT_MASK_ADD], R6
		BR.Z SELF_BLOCK1
		MOV R6, INT_MASK4
		MOV M[INT_MASK_ADD], R6
		POP R6
		RET
SELF_BLOCK1:	MOV R6, INT_MASK5
		MOV M[INT_MASK_ADD], R6
		POP R6
		RET

;---------------------------------------------------------------------------------------------------------------------------------------------------------
;PARA_INT1: Rotina responsável por impedir o jogador 2 de jogar mais que uma vez no mesmo ciclo
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: ----
;	Saidas: ----
;	Efeitos: Muda de mascara de interrupções tendo em conta se o jogador 1 já jogou 
;---------------------------------------------------------------------------------------------------------------------------------------------------------

PARA_INT2:	PUSH R6
		MOV R6, INT_MASK2
		CMP M[INT_MASK_ADD], R6
		BR.Z SELF_BLOCK2
		MOV R6, INT_MASK3
		MOV M[INT_MASK_ADD], R6
		POP R6
		RET
SELF_BLOCK2:	MOV R6, INT_MASK5
		MOV M[INT_MASK_ADD], R6
		POP R6
		RET
				
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;TESTA_BOTOES: Rotina responsável por verificar se alguma interrupção foi premida e da call na função respetiva
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: ----
;	Saidas: ----
;	Efeitos: Chama a rotina que altera a direção dos jogadores de acordo com a interrupção realizada
;---------------------------------------------------------------------------------------------------------------------------------------------------------				

TESTA_BOTOES:	PUSH R5
		MOV R5, 0001h
		CMP M[ESQ1], R5
		CALL.NZ VIRAR_ESQ1
		MOV R5, 0003h
		CMP M[ESQ2], R5
		CALL.NZ VIRAR_ESQ2
		MOV R5, 0002h
		CMP M[DIR1], R5
		CALL.NZ VIRAR_DIR1
		MOV R5, 0004h
		CMP M[DIR2], R5
		CALL.NZ VIRAR_DIR2
		POP R5
		RET
				
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;DEFINE_POSICAO1: Rotina responsável por definir as coordenadas da proxima posição da particula 1
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: R1, R2
;	Saidas: R1
;	Efeitos: Verifica qual é a direção da particula 1 e define a próxima posição tendo em conta a sua direção 
;---------------------------------------------------------------------------------------------------------------------------------------------------------

DEFINE_POSICAO1:CMP R2, CIMA
		BR.NZ P_DIR1
		SUB R1, 0100h
		RET
P_DIR1:		CMP R2, DIR
		BR.NZ P_BAIXO1
		INC R1
		RET
P_BAIXO1:	CMP R2, BAIXO
		BR.NZ P_ESQ1
		ADD R1, 0100h
		RET
P_ESQ1:		DEC R1
		RET
				
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;DEFINE_POSICAO2: Rotina responsável por definir as coordenadas da proxima posição da particula 2
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: R3, R4
;	Saidas: R3
;	Efeitos: Verifica qual é a direção da particula 2 e define a próxima posição tendo em conta a sua direção 
;---------------------------------------------------------------------------------------------------------------------------------------------------------

DEFINE_POSICAO2:CMP R4, CIMA
		BR.NZ P_DIR2
		SUB R3, 0100h
		RET
P_DIR2:		CMP R4, DIR
		BR.NZ P_BAIXO2
		INC R3
		RET
P_BAIXO2:	CMP R4, BAIXO
		BR.NZ P_ESQ2
		ADD R3, 0100h
		RET
P_ESQ2:		DEC R3
		RET

;---------------------------------------------------------------------------------------------------------------------------------------------------------
;VERIF_COLISAO1: Rotina responsável por verificar se houve alguma colisão por parte das duas particulas
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: M[R1], M[R3]
;	Saidas: ----
;	Efeitos: Compara as posições das duas particulas com a 'matriz' que contem os valores registados das posições preenchidas
;---------------------------------------------------------------------------------------------------------------------------------------------------------
			
VERIF_COLISAO1:	CMP M[R1], R0
		BR.NZ PONTUACAO1
		RET
PONTUACAO1:	INC M[VITORIAS2]
		CALL JOGO_TERMINOU
		RET

VERIF_COLISAO2:	CMP M[R3], R0
		CALL.NZ PONTUACAO2
		RET
PONTUACAO2:	INC M[VITORIAS1]
		CALL JOGO_TERMINOU
		RET
					
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;NOVA_MASCARA_INT: Rotina responsável por ligar as interrupções
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: ----
;	Saidas: ----
;	Efeitos: Coloca uma nova máscara que liga todas a interrupções
;---------------------------------------------------------------------------------------------------------------------------------------------------------

NOVA_MASCARA_INT:	PUSH R5
			MOV R5, INT_MASK2
			MOV M[INT_MASK_ADD], R5
			POP R5
			RET
					
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;JOGO_TERMINOU: Rotina responsável pela escrita da mensagem final do jogo 
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: ----
;	Saidas: ----
;	Efeitos: Escreve a mensagem final do jogo
;---------------------------------------------------------------------------------------------------------------------------------------------------------		

JOGO_TERMINOU:	MOV	R1, 0923h			
		MOV	R2, MSG3
		MOV	R3, M[R2]
		CALL	ESCREVE_MSG
		MOV	R1, 0A1Bh			
		MOV	R2, MSG4
		MOV	R3, M[R2]
		CALL	ESCREVE_MSG
		INC 	M[FIM_JOGO]
		RET

;---------------------------------------------------------------------------------------------------------------------------------------------------------
;LIMPA_MATRIZ: Rotina responsável por limpar a 'Matriz' dos valores para as colisões
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: ----
;	Saidas: ----
;	Efeitos: Coloca a zero todas os valores da 'Matriz'
;---------------------------------------------------------------------------------------------------------------------------------------------------------				
	
LIMPA_MATRIZ:	PUSH R1
		PUSH R2
		MOV R1, 1640h
		MOV R2, 010Fh
CICLO_MATRIZ:	MOV M[R2], R0
		INC R2
		CMP R2, R1
		BR.NZ  CICLO_MATRIZ
		POP R2
		POP R1
		RET
	
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;PROXIMO_NIVEL: Rotina responsável por alterar o nivel actual para o nivel seguinte, diminuindo o tempo entre ciclos de jogo
;				e alterando quando será a próxima mudança de nivel
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: R7
;	Saidas: ----
;	Efeitos: Recebe a velocidade do ciclo e altera cada vez que se atinge o tempo 10s, 20s, 40s, 60s, modificando tambem os LEDS
;---------------------------------------------------------------------------------------------------------------------------------------------------------	

PROXIMO_NIVEL:	PUSH R5
		CMP R7, 0007h
		BR.NZ NIVEL_2
		MOV R7, 0005h
		MOV R5, LED_MASK_N1
		MOV M[LEDS], R5				
		MOV M[TICK], R0
		POP R5
		RET 
NIVEL_2:	CMP R7, 0005h
		BR.NZ NIVEL_3
		MOV R7, 0003h
		MOV R6, 00C8h
		MOV R5, LED_MASK_N2
		MOV M[LEDS], R5
		MOV M[TICK], R0
		POP R5
		RET
NIVEL_3:	CMP R7, 0003h
		BR.NZ NIVEL_4
		MOV R7, 0002h
		MOV R6, 00C8h
		MOV R5, LED_MASK_N3
		MOV M[LEDS], R5
		MOV M[TICK], R0
		POP R5
		RET
NIVEL_4:	CMP R7, 0002h
		BR.NZ NIVEL_5
		MOV R7, 0001h
		MOV R6, 00C8h
		MOV R5, LED_MASK_N4
		MOV M[LEDS], R5
		MOV M[TICK], R0
		POP R5
			RET
NIVEL_5:	MOV R6, 00C8h
		MOV M[TICK], R0
		POP R5
		RET

;---------------------------------------------------------------------------------------------------------------------------------------------------------
;ACENDE_PLACA: Rotina responsável por escrever as mensagens pretendidas no LCD
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: ----
;	Saidas: ----
;	Efeitos: Escreve as mensagens definidas no LCD
;---------------------------------------------------------------------------------------------------------------------------------------------------------				

ACENDE_PLACA:	PUSH R1
		PUSH R2
		PUSH R3
		PUSH R4
		
		MOV R1, LCD1_0
		MOV R2, MSG5
		MOV R3, M[R2]
		CALL ESCREVE_LCD
		
		MOV R1, LCD2_0
		MOV R2, MSG6
		MOV R3, M[R2]
		CALL ESCREVE_LCD
		
		MOV R1, LCD2_10
		MOV R2, MSG7
		MOV R3, M[R2]
		CALL ESCREVE_LCD
		POP R4
		POP R3
		POP R2
		POP R1
		RET
				
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;ESCREVE_LCD: Rotina responsável por escrever as mensagens no LCD
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: R1, R2, R3
;	Saidas: ----
;	Efeitos: Escreve as mensagens no LCD
;---------------------------------------------------------------------------------------------------------------------------------------------------------					

ESCREVE_LCD:	MOV 	M[LCD_CONTR], R1
		MOV 	M[LCD_WR], R3
		INC 	R1
		INC 	R2
		MOV 	R3, M[R2]
		CMP		R3, 0040h
		BR.NZ	ESCREVE_LCD
		
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;ACT_LCD1: Rotina responsável por atualizar o LCD
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: ----
;	Saidas: ----
;	Efeitos: Atualiza o numero de vitorias de cada jogador
;---------------------------------------------------------------------------------------------------------------------------------------------------------						

ACT_LCD1:	PUSH R1
		PUSH R2
		PUSH R3
		PUSH R4
		
		MOV R1, 8015h
		MOV R2, M[VITORIAS1]
		
		CMP R2, 000Ah
		CALL.Z 	CHEGA_DEZ1
		ADD R2, 0030h
		MOV 	M[LCD_CONTR], R1
		MOV 	M[LCD_WR], R2				
		POP R4
		POP R3
		POP R2
		POP R1
		RET
				
CHEGA_DEZ1:	MOV R3, 8014h
		INC M[DEZENAS1]
		MOV R4, M[DEZENAS1]
		ADD R4, 0030h
		MOV M[LCD_CONTR], R3
		MOV M[LCD_WR], R4
		MOV R2, R0
		MOV M[VITORIAS1], R0
		
		RET
				
ACT_LCD2:	PUSH R1
		PUSH R2
		PUSH R3
		PUSH R4
		
		
		MOV R1, 801Fh
		MOV R2, M[VITORIAS2]
		
		CMP R2, 000Ah
		CALL.Z CHEGA_DEZ2
		ADD R2, 0030h
		MOV 	M[LCD_CONTR], R1
		MOV 	M[LCD_WR], R2				
		POP R4
		POP R3
		POP R2
		POP R1
		RET
				
CHEGA_DEZ2:	MOV R3, 801Dh
		INC M[DEZENAS2]
		MOV R4, M[DEZENAS2]
		ADD R4, 0030h
		MOV M[LCD_CONTR], R3
		MOV M[LCD_WR], R4
		MOV R2, R0
		MOV M[VITORIAS2], R0
		
		RET

;---------------------------------------------------------------------------------------------------------------------------------------------------------
;RESET_TEMPO: Rotina responsável por colocar o relógio a zero
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: ----
;	Saidas: ----
;	Efeitos: Coloca a zero o relógio e apaga os LEDS
;---------------------------------------------------------------------------------------------------------------------------------------------------------					
			
RESET_TEMPO:	PUSH R1				
		MOV R1, DISPLAY
		MOV M[RELOGIO], R0
		MOV M[R1], R0
		INC R1
		MOV M[R1], R0
		INC R1
		MOV M[R1], R0
		INC R1
		MOV M[R1], R0
		MOV M[LEDS], R0
		MOV M[TIMER], R0
		POP R1
		RET

;---------------------------------------------------------------------------------------------------------------------------------------------------------
;VERIFICA_MAX: Rotina responsável por verificar se há um novo máximo, e se houver, altera na placa
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: ----
;	Saidas: ----
;	Efeitos: Compara o tempo máximo com o atual, e se o atual for maior, é definido como o novo máximo
;---------------------------------------------------------------------------------------------------------------------------------------------------------	

VERIFICA_MAX:	PUSH R1
		PUSH R2
		MOV R1, M[T_REC]
		MOV R2, M[RELOGIO]
		SUB R1, R2
		BR.N NOVO_MAXIMO
		POP R2
		POP R1
		RET
NOVO_MAXIMO:	MOV R1, M[T_REC]
		MOV R2, M[RELOGIO]
		MOV M[T_REC], R2
		CALL ESCREVE_MAXIMO
		POP R2
		POP R1
		RET

;---------------------------------------------------------------------------------------------------------------------------------------------------------
;ESCREVE_MAXIMO: Rotina responsável por mandar escrever o novo máximo na placa
;---------------------------------------------------------------------------------------------------------------------------------------------------------
;	Entradas: R2
;	Saidas: ----
;	Efeitos: Recebe o novo tempo máximo e escreve na placa
;---------------------------------------------------------------------------------------------------------------------------------------------------------	

ESCREVE_MAXIMO:	PUSH R3	
		MOV R1, R2
		MOV R2, 1000h
MILHARES:	DIV R1, R2
		ADD R1, 0030h
		MOV R3, LCD1_11
		MOV M[LCD_CONTR], R3
		MOV M[LCD_WR], R1
				
		MOV R1, 0100h
CENTENAS:	DIV R2, R1
DIG_CENTENAS:	ADD R2, 0030h
		MOV R3, LCD1_12
		MOV M[LCD_CONTR], R3
		MOV M[LCD_WR], R2
				
		MOV R2, 0010h
DEZENAS:	DIV R1, R2
DIG_DEZENAS:	ADD R1, 0030h
		MOV R3, LCD1_13
		MOV M[LCD_CONTR], R3
		MOV M[LCD_WR], R1
	
DIG_UNIDADES:	ADD R2, 0030h
		MOV R3, LCD1_14
		MOV M[LCD_CONTR], R3
		MOV M[LCD_WR], R2
		POP R3
		RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;Main Code;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


INICIO:		CALL MSG_BV
		CALL ACENDE_PLACA
		ENI
				
REINICIO:	CMP M[COMECA], R0
		BR.Z REINICIO
		DSI
		DEC M[COMECA]
		CALL LIMPA_MAPA
		CALL ESCREVE_MAPA
		CALL RESET_TEMPO
		CALL VAI_COMECAR
		MOV M[TICK], R0
		ENI						
				
CICLO_TEMPO1:	CMP M[NIVEL], R7
		BR.NZ CICLO_TEMPO1
		MOV M[NIVEL], R0
				
CICLO_JOGO:	DSI
		CALL DEFINE_POSICAO1
		CALL DEFINE_POSICAO2
		CALL VERIF_COLISAO1
		CALL VERIF_COLISAO2
		CMP M[FIM_JOGO], R0
		BR.NZ REINICIO2
		CALL ESCREVE_PARTICULAS
		CALL NOVA_MASCARA_INT
		ENI
CICLO_TEMPO2:	CALL TESTA_BOTOES
		CALL TESTEPAUSA
		CMP M[TIMER], R5
		CALL.Z D_RELOGIO
		CMP M[TICK], R6
		CALL.Z PROXIMO_NIVEL
		CMP M[NIVEL],R7
		BR.NZ CICLO_TEMPO2
		MOV M[NIVEL], R0
		JMP CICLO_JOGO
		
REINICIO2:	DEC M[FIM_JOGO]
		DEC M[SEGUNDO]
		CALL VERIFICA_MAX
		CALL ACT_LCD1
		CALL ACT_LCD2
		MOV	R1, INT_MASK1
		MOV	M[INT_MASK_ADD], R1
		CALL LIMPA_MATRIZ
		ENI
		JMP REINICIO