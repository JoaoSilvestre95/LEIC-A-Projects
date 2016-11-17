%Grupo 15
%João Pedro Piçarra Silvestre, nº 80996
%Nuno Cartier Soares Tomás, nº 81718

%-------------------------------------------------

% transformacao/2
% transformacao(C1, C2) em que C1 e C2 sao configuracoes representadas por listas
transformacao([A, B, C, D, E, F, G, H, I], 
              [J, K, L, M, N, O, P, Q, R]) :- write('Transformacao desejada:'), nl, 
                                              escreve(A), escreve(B), escreve(C),  
                                              write('    '), 
                                              escreve(J), escreve(K), escreve(L),nl, 
                                              escreve(D), escreve(E), escreve(F), 
                                              write(' -> '), 
                                              escreve(M), escreve(N), escreve(O), nl,
                                              escreve(G), escreve(H), escreve(I), 
                                              write('    '), 
                                              escreve(P), escreve(Q), escreve(R), nl.

%--------------------------------------------------

%escreve/1 Escreve o tabuleiro do jogo
escreve([A, B, C, D, E, F, G, H, I]) :- escreve(A), escreve(B), escreve(C), nl,
                                        escreve(D), escreve(E), escreve(F), nl,
                                        escreve(G), escreve(H), escreve(I), nl.

escreve(S) :- S = 0, write('   ').
escreve(S) :- S < 10, write(' '), write(S), write(' ').

%-------------------------------------------------

% escreve_solucao/1
% escreve_solucao(M) em que M e uma lista de movimentos e um movimento e um par (Mov, Peca) 
escreve_solucao([M, P| []]) :- write('mova a peca '), 
                                write(P), 
                                traduz(M, Mp), 
                                write(Mp),
                                write('.'),
                                nl.

escreve_solucao([M, P| R]) :- write('mova a peca '), 
                                write(P), 
                                traduz(M, Mp), 
                                write(Mp),
                                nl, 
                                escreve_solucao(R).

%-------------------------------------------------

% traduz/2 e um predicado auxiliar de escreve_solucao/1
traduz(c, ' para cima').
traduz(b, ' para baixo').
traduz(e, ' para a esquerda').
traduz(d, ' para a direita').

%---------------------------------------------------

%posicao(L, N, P)/3 Devolve a posicao do numero que esta no tabueleiro
posicao([E|_], E, 0):- !.
posicao([_|L], N, P):- 	posicao(L, N, P1),
						            !,
  						          P is P1 + 1.

%----------------------------------------------------

%inv_posicao(L, P, N)/3 Devolve o numero que esta na posicao P
inv_posicao([E|_], 0, N) :- N is E, !.
inv_posicao([_|R], P, N) :- P1 is P-1, inv_posicao(R, P1, N).

%------------------------------------------------------

%swap(L, N, R)/3 Troca o N com o 0 na lista L e devolve a lista R alterada
swap([], _, []).
swap([A|L], N, [B|L1]) :- 	A =:= N,
							B is 0,
							swap(L, N, L1), !.
swap([A|L], N, [B|L1]) :- 	A =:= 0,
							B is N,
							swap(L, N, L1), !.
swap([A|L], N, [A|L1]) :-  A =\= N, swap(L, N, L1).

%--------------------------------------------------------

%mov_legal(C1, M, P, C2)/4 Movimentos M que podem ser gerados na configuracao C1, movendo a peca P, devolvendo C2
mov_legal(C1, c, P, C2) :- mov_possi(C1, c), posicao(C1, 0, P1), P2 is P1+3, inv_posicao(C1, P2, P), swap(C1, P, C2).
mov_legal(C1, b, P, C2) :- mov_possi(C1, b), posicao(C1, 0, P1), P2 is P1-3, inv_posicao(C1, P2, P), swap(C1, P, C2).
mov_legal(C1, e, P, C2) :- mov_possi(C1, e), posicao(C1, 0, P1), P2 is P1+1, inv_posicao(C1, P2, P), swap(C1, P, C2).
mov_legal(C1, d, P, C2) :- mov_possi(C1, d), posicao(C1, 0, P1), P2 is P1-1, inv_posicao(C1, P2, P), swap(C1, P, C2).


%---------------------------------------------------------

%mov_possi(L,M)verifica se a joagada é possivel
mov_possi(L, d) :- posicao(L, 0, P), compara([1,2,4,5,7,8], P),!.
mov_possi(L, e) :- posicao(L, 0, P), compara([0,1,3,4,6,7], P),!.
mov_possi(L, c) :- posicao(L, 0, P), compara([0,1,2,3,4,5], P),!.
mov_possi(L, b) :- posicao(L, 0, P), compara([3,4,5,6,7,8], P).

%compara(L, N)/2 Compara um numero com um elemento da lista para ver se sao iguais
compara([N|_], N) :- !.
compara([_|L], N) :- compara(L,N).

%---------------------------------------------------------
%----------------------------------------------------------

%resolve_manual(C1,C2)/2
resolve_manual(C1,C2) :- transformacao(C1, C2),nl, resolve_manual1(C1,C2),!.
resolve_manual1(C1,C2) :- C1 = C2, write('Parabens!').
resolve_manual1(C1,C2) :- write('Qual o seu movimento?'), 
                          nl, 
                          read(M), 
                          mov_legal(C1, M, _, R), 
                          escreve(R), 
                          nl, 
                          resolve_manual1(R, C2).
resolve_manual1(C1,C2) :- write('Movimento ilegal'),
                          nl, 
                          resolve_manual1(C1,C2).

%-----------------------------------------------------------
%------------------------------------------------------------

%resolve_cego(C1, C2)/2
resolve_cego(C1,C2) :- transformacao(C1, C2),
                        nl, 
                        resolve_cego(C1,C2, [C1],[]),
                        !.
resolve_cego(C1, C2, _, Mo) :- C1 = C2, inverte(Mo, I), escreve_solucao(I).
resolve_cego(C1, C2, T, Mo) :- mov_legal(C1, M, P, R), 
                                not(lista_existe(R, T)), 
                                M1 = [M,P|Mo], 
                                resolve_cego(R,C2, [R|T], M1).

%------------------------------------------------------------
%---------------------------------------------------------

%lista_existe(L, Le)/2 Verifica se existe uma lista L dentro de outra lista Le
lista_existe(L, [L1|_]) :- L = L1, !.
lista_existe(L, [_|R]) :- lista_existe(L, R).

%-----------------------------------------------------------

%hamming(L, L1, N)/3 Calcula a distancia de hamming entre L e L1, devolvendo o resultado em N
hamming([],[],0) :- !.
hamming([H|T], [H1|T1], N) :- H =\= H1, 
                              hamming(T, T1, N1), 
                              !, 
                              N is N1 + 1.
hamming([H|T], [H1|T1], N) :- H =:= H1, hamming(T, T1, N).

%----------------------------------------------------------
%---------------------------------------------------------

%resolve_info_h(L, L1)/2
resolve_info_h(C1, C2) :- transformacao(C1, C2),
                          nl, 
                          hamming(C1 , C2, N), 
                          R = [C1 , N, 0, N,[]],
						              resolve_info_h(C2, [R], []),
                          !.
resolve_info_h(_, [],_) :- write('Impossivel').
resolve_info_h(C2, A, _) :- menor_f(A, Min), get_c(Min, C1), C1 = C2, get_m(Min, I), inverte(I, M), escreve_solucao(M).
resolve_info_h(C2, A, F) :- transfere(A, F, Ra, Rf, Min),
							               get_c(Min, C),
							               findall([Cn, Fn, Gn, Hn,[Mo,P|M]],
							               calcula_tudo(C,C2, Min, Cn, Fn, Gn, Hn, Mo, P, M),
							               Bag),
							               compara_insere(Bag, Ra, Rf, A1), 
                             resolve_info_h(C2, A1, Rf).
%----------------------------------------------------------------
%----------------------------------------------------------------
%calcula_tudo(C, C2, Min, Cn, Fn, Gn, Hn, Mo, P, M)/10 Recebe a configuracao atual(C) e a final(C2) e o no com o menor F
%calculando os novos no, F, G, H, movimentos e peca
calcula_tudo(C, C2, Min, Cn, Fn, Gn, Hn, Mo, P, M) :- mov_legal(C, Mo, P, Cn),
													                             get_m(Min, M),
													                             hamming(Cn, C2, Hn),
													                             get_g(Min, G),
													                             Gn is G+1,
													                             Fn is Gn + Hn.
%------------------------------------------------------------

%compara_insere(L1, L2, F)/3 Ve se a lista L1 tem elementos que ja estao na lista L2, caso não, insere-os e retorna F
compara_insere([],A,_,A) :- !.
compara_insere([H|T], A, F, Aux) :- not(lista_existe(H, A)), not(lista_existe(H, F)), 
                                    junta([H], A, A1), 
                                    compara_insere(T, A1, F, Aux),
                                    !.
compara_insere([_|T], A, F, Aux) :- compara_insere(T, A, F, Aux).

%----------------------------------

%get_f(L1, L2, F1, F2)/4 Vai buscar is Fs de cada no e retorna-os
get_f([_,F1|_], [_,F2|_], R1, R2) :- R1 is F1, R2 is F2.

%----------------------------------

%get_g(No, G)/2 Vai buscar o G do no
get_g([_,_,G|_], G) :- !.

%------------------------------------

%get_c(No, C) Vai buscar o C do no
get_c([C|_], C) :- !.

%-----------------------------------

%get_m(No, M) Vai buscar o M do no
get_m([_,_,_,_,M], M) :- !.

%--------------------------------------

%menor_f(A, M)/2 Calcula o menor F da lista de Abertos
menor_f([H|T], M) :- menor_f(T, M, H),!.
menor_f([], M, M) :- !.
menor_f([H|T], M, Aux) :- get_f(H, Aux, F1, F2), F1 < F2, menor_f(T, M, H).
menor_f([_|T], M, Aux) :- menor_f(T, M, Aux).

%---------------------------------------

%junta(L1, L2, F)junta a lista L1 a lista L2 e devolve F
junta([], L, L) :- !.
junta([P | R], L1, [P | L2]) :- junta(R, L1, L2).

%-----------------------------------------

%remove_lista(L, E, T)/3 Remove o E da lista L e devolve T
remove_lista([], _, _) :- !.
remove_lista([E|T], E,T) :- remove_lista(T,E,T).
remove_lista([H|T], E, [H|T1]):- remove_lista(T, E,T1).

%----------------------------------------

%inverte_mov(L1, L2)/2 inverte a lista L1 e devolve a L2, tendo a lista L1 os movimentos gerados
inverte([], []) :- !.
inverte([M,P| R], I) :- inverte(R, I1), junta(I1,[M,P], I).

%----------------------------------------

%transfere(A, F, Ra, Rf)/5 Transfere o menor f de abertos (devolvendo-o) para a fechada e devolve a lista das fechadas e abertas
transfere(A, F, Ra, Rf, M) :- menor_f(A, M), remove_lista(A, M, Ra), junta([M], F, Rf),!.

%-----------------------------------------

%transformacao_possivel/2 compara duas listas e verifica se e possivel transformar uma na outra
transformacao_possivel(C1,C2):- aux(C1,1,Tran,0), aux(C2,1,Tran2,0), Tran mod 2 =:= Tran2 mod 2,!.

%------------------------------------------

%aux/4 Conta os numeros que se encontram fora da sua posicao final.
aux(_,8,Tran,Tran):-!.
aux(L,Cont,Tran,Aux):- posicao(L,Cont,P), Aux1 is Aux+P, delete(Cont,L,Nova_lista), Cont2 is Cont+1,
            aux(Nova_lista,Cont2,Tran,Aux1),!.

%------------------------------------------

%delete(E, L1, L2)/3 Remove o E da lista L1 e devolve L2
delete(A, [A|B], B).
delete(A, [B, C|D], [B|E]) :- delete(A, [C|D], E).


