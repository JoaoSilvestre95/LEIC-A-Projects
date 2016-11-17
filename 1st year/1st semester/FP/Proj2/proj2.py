#Goncalo Soares, 81418; Joao Silvestre, 80996; Grupo: al083
from random import random

def cria_coordenada(l,c):
    """cria_coordenada: int x int ---> coordenada
    Constroi uma coordenada (l,c) a partir de dois inteiros entre 1 e 4"""
    
    if e_coordenada((l,c)):
        return l,c
    else:
        raise ValueError('cria_coordenada: argumentos invalidos')

def coordenada_linha(lc):
    """coordenada_linha: coordenada ---> inteiro
    Seleciona o inteiro correspondente a linha da coordenada"""
    
    return lc[0]

def coordenada_coluna(lc):
    """coordenada_coluna: coordenada ---> inteiro
        Seleciona o inteiro correspondente a coluna da coordenada"""    
    
    return lc[1]

def e_coordenada(coord):
    """e_coordenada: universal ---> logico
    Reconhece se o argumento e do tipo coordenada"""
    
    return isinstance(coord, tuple) and len(coord) == 2 and \
           coordenada_linha(coord) in (1,2,3,4) and coordenada_coluna(coord) in (1,2,3,4)
              
def coordenadas_iguais(coord1, coord2):
    """coordenadas_iguais: coordenada x coordenada ---> logico
    Testa se os dois argumentos do tipo coordenada sao iguais"""
    
    if e_coordenada(coord1) and e_coordenada(coord2):
        return coord1 == coord2
    else:
        return False
    
def cria_tabuleiro():
    """cria_tabuleiro: {} ---> tabuleiro
    Constroi um tabuleiro com as posicoes e a pontuacao a zero"""
    #A representacao interna escolhida do tabuleiro 4x4 e uma lista 
    #Em que dentro da lista, contem 4 listas correspondentes as linhas do tabuleiro
    
    return [[0, 0, 0, 0], 
            [0, 0, 0, 0], 
            [0, 0, 0, 0], 
            [0, 0, 0, 0], 0]    

def tabuleiro_posicao(t, c):
    """tabuleiro_posicao: tabuleiro x coordenada ---> inteiro
    Seleciona o valor da posicao correspondente a coordenada de um tabuleiro"""
    
    if e_coordenada(c):
        return t[coordenada_linha(c)-1][coordenada_coluna(c)-1]
    else:
        raise ValueError('tabuleiro_posicao: argumentos invalidos')
    
def tabuleiro_pontuacao(t):
    """tabuleiro_pontuacao: tabuleiro ---> inteiro
    Seleciona o valor correspondente a pontuacao atual do jogo"""    
    
    return t[4]

def tabuleiro_posicoes_vazias(t):
    """tabuleiro_posicoes_vazias: tabuleiro ---> lista
    Seleciona as coordenadas que contem valor zero e coloca numa lista"""
    
    vazias = []
    for l in range(1,5):
        for c in range(1,5):
            coord = cria_coordenada(l,c)
            if tabuleiro_posicao(t, coord) == 0:
                vazias = vazias + [coord]
    return vazias

def tabuleiro_preenche_posicao(t, c, v):
    """tabuleiro_preenche_posicao: tabuleiro x coordenada x inteiro ---> tabuleiro
    Substitui o valor da coordenada do tabuleiro com um inteiro"""
    
    if e_coordenada(c) and isinstance(v, int):
        t[coordenada_linha(c) - 1][coordenada_coluna(c) - 1] = v
        return t
    else:
        raise ValueError('tabuleiro_preenche_posicao: argumentos invalidos')
        
def tabuleiro_actualiza_pontuacao(t, v):
    """tabuleiro_actualiza_pontuacao: tabuleiro x inteiro ---> tabuleiro
    Modifica o valor da pontuacao de um tabuleiro, somando um inteiro nao negativo multiplo de 4"""
    
    if isinstance(v, int) and v >= 0 and v % 4 == 0:
        t[4] = t[4] + v
        return t
    else:
        raise ValueError('tabuleiro_actualiza_pontuacao: argumentos invalidos')

def tabuleiro_reduz(t, d):
    """tabuleiro_reduz: tabuleiro x cad. caracteres ---> tabuleiro
    Modifica o tabuleiro de acordo com a jogada efetuada"""
    
    if d == 'W':
        #Desloca os paineis de acordo com a orientacao escolhida
        move(t, range(1,5), range(1,4), 0, 1)
        #Soma dois paineis com o mesmo valor consecutivos de acordo com a orientacao escolhida
        soma(t, range(1,5), range(1,4), 0, 1)
        #Desloca os paineis novamente para remover os espacos deixados pela soma
        move(t, range(1,5), range(1,4), 0, 1)
        return t
    elif d == 'E':
        move(t, range(1,5), range(4,1,-1), 0, -1)
        soma(t, range(1,5), range(4,1,-1), 0, -1)
        move(t, range(1,5), range(4,1,-1), 0, -1)
        return t
    elif d == 'S':
        move(t, range(4,1,-1), range(1,5), -1, 0)
        soma(t, range(4,1,-1), range(1,5), -1, 0)
        move(t, range(4,1,-1), range(1,5), -1, 0)
        return t
    elif d == 'N':
        move(t, range(1,4), range(1,5), 1, 0)
        soma(t, range(1,4), range(1,5), 1, 0)
        move(t, range(1,4), range(1,5), 1, 0)
        return t
    else:
        raise ValueError('tabuleiro_reduz: argumentos invalidos')


def move(t, seg_perco1, seg_perco2, desl1, desl2):
    """Funcao auxiliar da funcao tabuleiro_reduz, que movimenta os paineis""" 
    x = copia_tabuleiro(t)
    for l in seg_perco1:
        for c in seg_perco2: 
            #Ordem pela qual as coordenadas sao percorridas
            coord = cria_coordenada(l,c)
            prox_coord = cria_coordenada(coordenada_linha(coord) + desl1, coordenada_coluna(coord) + desl2)
            #Define a proxima coordenada a comparar
            if tabuleiro_posicao(t, coord) == 0:
                if prox_coord not in tabuleiro_posicoes_vazias(t):
                    tabuleiro_preenche_posicao(t, coord, tabuleiro_posicao(t, prox_coord))
                    tabuleiro_preenche_posicao(t, prox_coord, 0)
                    #Coloca na coordenada atual o valor da proxima coordenada, 
                    #colocando a anterior a zero
    if t == x:
        #Em caso de nao haver alteracao do tabuleiro, para a deslocacao 
        return t
    else:
        return move(t, seg_perco1, seg_perco2, desl1, desl2)
        
def soma(t, seg_perco1, seg_perco2, desl1, desl2):
    """Soma o valor das coordenadas consecutivas, caso elas sejam iguais, 
    se a jogada o permitir"""
    
    for l in seg_perco1:
        for c in seg_perco2:
            coord = cria_coordenada(l,c)
            prox_coord = cria_coordenada(l + desl1, c + desl2)
            if tabuleiro_posicao(t, coord) == tabuleiro_posicao(t, prox_coord):
                tabuleiro_preenche_posicao(t, coord, 2 * tabuleiro_posicao(t, coord))
                tabuleiro_actualiza_pontuacao(t, tabuleiro_posicao(t, coord))
                tabuleiro_preenche_posicao(t, prox_coord, 0)
                #Soma a coordenada atual com a proxima, caso sejam iguais
                #Coloca valor zero na anterior
    return t

def e_tabuleiro(t):
    """e_tabuleiro: universal ---> logico
    Reconhece se o argumento e do tipo tabuleiro"""

    if isinstance(t, list) and len(t) == 5:
        for l in range(1,5):
            for c in range(1,5):
                coord = cria_coordenada(l,c)
                if isinstance(tabuleiro_posicao(t, coord), int) == False or tabuleiro_posicao(t, coord) < 0 or isinstance(tabuleiro_pontuacao(t), int) == False or tabuleiro_pontuacao(t) < 0:
                    return False
        return True 
    else:
        return False

def tabuleiro_terminado(t):
    """tabuleiro_terminado: tabuleiro ---> logico
    Reconhece se o tabuleiro esta cheio e nao seja possissel mais movimentos"""
    
    return tabuleiro_posicoes_vazias(t) == [] and \
           tabuleiros_iguais(t, tabuleiro_reduz(copia_tabuleiro(t), 'N')) and \
           tabuleiros_iguais(t, tabuleiro_reduz(copia_tabuleiro(t), 'E')) and \
           tabuleiros_iguais(t, tabuleiro_reduz(copia_tabuleiro(t), 'W')) and \
           tabuleiros_iguais(t, tabuleiro_reduz(copia_tabuleiro(t), 'S'))

def copia_tabuleiro(t):
    """copia_tabuleiro: tabuleiro ---> tabuleiro
    Recebe um tabuleiro e faz uma copia do mesmo"""
    
    copia = cria_tabuleiro()
    for l in range(1, 5):
        for c in range(1, 5):
            coord = cria_coordenada(l,c)
            tabuleiro_preenche_posicao(copia, coord, tabuleiro_posicao(t, coord))
    copia[4] = tabuleiro_pontuacao(t)
    return copia

def tabuleiros_iguais(t1, t2):
    """tabuleiros_iguais: tabuleiro x tabuleiro ---> logico
    Testa se os dois tabuleiros recebidos sao iguais"""
    
    for l in range(1,5):
        for c in range(1,5):
            coord = cria_coordenada(l,c)
            if tabuleiro_posicao(t1, coord) != tabuleiro_posicao(t2, coord) or tabuleiro_pontuacao(t1) != tabuleiro_pontuacao(t2):
                return False
    return True
        
def escreve_tabuleiro(t):
    """escreve_tabuleiro: tabuleiro ---> {}
    Transcreve para o ecra a representacao externa do tabuleiro"""
    
    if e_tabuleiro(t):
        for l in range(1, 5):
            print('[', tabuleiro_posicao(t, cria_coordenada(l,1)), '] [', tabuleiro_posicao(t, cria_coordenada(l,2)), '] [', tabuleiro_posicao(t, cria_coordenada(l,3)), '] [', tabuleiro_posicao(t, cria_coordenada(l,4)), '] ')
        print('Pontuacao:', tabuleiro_pontuacao(t))
    else:
        raise ValueError('escreve_tabuleiro: argumentos invalidos')

def pede_jogada():
    """pede_jogada: {} ---> cad. caracteres
    Pede ao utilizador uma direcao (N, S, E, W) ate que receba uma valida"""
    
    jogada = str(input('Introduza uma jogada (N, S, E, W): '))
    if jogada not in ('N', 'S', 'E', 'W'):
        print('Jogada invalida.')
        return pede_jogada()
    else: 
        return jogada
    
def jogo_2048():
    """jogo_2048: {} ---> {}
    Funcao que permite jogar um jogo completo de 2048 com todas as suas funcionalidades"""
    
    t = cria_tabuleiro()
    preenche_posicao_aleatoria(t)
    preenche_posicao_aleatoria(t)
    escreve_tabuleiro(t)
    while tabuleiro_terminado(t) == False:
        j = pede_jogada()
        a = tabuleiro_reduz(copia_tabuleiro(t), j)
        if tabuleiros_iguais(t, a):
            escreve_tabuleiro(t)
        else:
            tabuleiro_reduz(t, j)
            preenche_posicao_aleatoria(t)
            escreve_tabuleiro(t)           
    
def preenche_posicao_aleatoria(t):
    """preenche_posicao_aleatoria: tabuleiro ---> tabuleiro
    Recebe um tabuleiro e coloca o valor 2 ou 4 com as respetivas probabilidades
    de 80% e 20%, numa posicao aleatoria do tabuleiro"""
    l_vazias = tabuleiro_posicoes_vazias(t)
    t_aleatorias = (2, 2, 2, 2, 4)  
    #probabilidade de 2 (0.8) ou 4 (0.2) sair
    if l_vazias != []:
        i = int(random()*len(l_vazias))
        j = int(random()*5)
        tabuleiro_preenche_posicao(t, l_vazias[i], t_aleatorias[j])
    return t