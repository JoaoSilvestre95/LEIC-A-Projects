#Joao Silvestre, 80996
from random import random 

def calc_soma(num):
    """Calcula a soma dos digitos de um numero(sem o digito de verificacao), de acordo com o logaritmo de Luhn"""
    invertido=''
    multiplicados=''
    soma=0
    for i in range(len(num)):               #inverte a cadeia de caracteres
        invertido=num[i]+invertido
    for i in range(len(invertido)):         #Multiplica os digitos em posicoes impares por 2       
        if i%2==0:
            impar=eval(invertido[i])*2
            if impar>9:                     #se a multiplicacao for maior que 9, subtrai por 9
                impar=impar-9
            impar=str(impar)
            multiplicados=multiplicados+impar
        else:
            multiplicados=multiplicados+invertido[i]
    for i in range(len(multiplicados)):     
        soma= soma+eval(multiplicados[i])   #soma de todos os digitos
    return soma
        
def luhn_verifica(ncartao):
    """Verifica se um numero de cartao de credito e valido, aplicando o algoritmo de luhn"""
    dverifica=ncartao[-1]                                         #Guarda o digito de verificacao
    if len(ncartao)>1:
        if (calc_soma(ncartao[0:-1])+eval(dverifica))%10==0:      #executa o calc_soma e adiciona o numero de verificacao, se o resto da divisao por 10 for 0, retorna True
            return True
        else:
            return False
    else:
        return False
  
def comeca_por(cad1, cad2):
    """Verifica se uma cadeia de caracteres comeca pela outra""" 
    if len(cad2)>len(cad1):                 #Pre-condicao: a segunda cadeia nao pode ser maior do que a primeira
            return False    
    else:
        for i in range(len(cad2)):      
            if cad1[i]!=cad2[i]:            #Compara os i digitos de cada cadeia
                return False
        return True
  
def comeca_por_um(cad, t_cads):
    """Verifica se uma cadeia de caracteres comeca por um ou mais elementos de um tuplo"""
    for i in t_cads:
        if comeca_por(cad, i)==True:        #Aplica a funcao comeca_por a cada elemento do tuplo
            return True
    return False

def valida_iin(ncartao):
    """Diz qual a emissora do cartao de credito, recebendo um numero de cartao de credito"""
    ndigitos = len(ncartao)
    cartoes = ('American Express', 'Diners Club International', 'Discover Card', 'Maestro', 'Master Card','Visa Electron','Visa','')
    digIni=(('34', '37'),('309', '36', '38', '39'),('65',), ('5018', '5020', '5038'),('50', '51', '52', '53', '54', '19'),('4026', '426', '4405', '4508'),('4024', '4532', '4556'))
    #Utilizando a funcao comeca_por_um verifica se um cartao comeca por um dos prefixos do tuplo digIni e tem o numero de digitos correto, retornando qual a emissora desse cartao
    if (comeca_por_um(ncartao, digIni[0])==True and (ndigitos==15)):
        return cartoes[0]
    elif (comeca_por_um(ncartao, digIni[1])==True and ndigitos==14):
        return cartoes[1]
    elif (comeca_por_um(ncartao, digIni[2])==True and ndigitos==16):
        return cartoes[2]
    elif (comeca_por_um(ncartao, digIni[3])==True and (ndigitos==13 or ndigitos==19)):
        return cartoes[3]
    elif (comeca_por_um(ncartao, digIni[4])==True and ndigitos==16):
        return cartoes[4]
    elif (comeca_por_um(ncartao, digIni[5])==True and ndigitos==16):
        return cartoes[5]
    elif (comeca_por_um(ncartao, digIni[6])==True and (ndigitos==13 or ndigitos==16)):
        return cartoes[6]
    else:
        return cartoes[7]

def categoria(num):
    """A partir do primeiro digito, diz qual e a categoria de uma cadeia de caracteres correspondente a um numero"""
    C=('Companhias aereas', 'Companhias aereas e outras tarefas futuras da industria', 'Viagens e entretenimento e bancario / financeiro', 'Servicos bancarios e financeiros', 'Merchandising e bancario / financeiro', 'Petroleo e outras atribuicoes futuras da industria', 'Saude, telecomunicacoes e outras atribuicoes futuras da industria', 'Atribuicao nacional', 'Categoria Inexistente')
    MMI=num[0]          #Seleciona o primeiro carcater correspondente ao primeiro algarismo do numero
    if MMI=='1':
        return C[0]
    elif MMI=='2':
        return C[1]
    elif MMI=='3':
        return C[2]
    elif MMI=='4':
        return C[3]
    elif MMI=='5':
        return C[3]
    elif MMI=='6':
        return C[4]
    elif MMI=='7':
        return C[5]
    elif MMI=='8':
        return C[6]
    elif MMI=='9':
        return C[7]
    else:
        return C[8]

def verifica_cc(cartao):
    """Verifica se o cartao de credito passa no algoritmo de Luhn e retorna qual a categoria e a emissora do cartao, caso ele exista"""
    cartao=str(cartao)
    if luhn_verifica(cartao)==True and valida_iin(cartao)!='':      #Passando no logaritmo de Luhn e o cartao pertencer a uma rede emissora, retorna a categoria e a emissora
        return (categoria(cartao), valida_iin(cartao))
    else:
        return 'cartao invalido'
    
def digito_verificacao(ncartao):        
    """A partir de um numero de cartao de credito sem o ultimo digito, calcula o valor do ultimo digito, de modo a respeitar o algoritmo de Luhn"""
    somancartao=calc_soma(ncartao)
    if somancartao%10==0:                   #Se a soma acabar com o algarismo zero, o digito de verificacao e zero
        return '0'
    else:
        digveri=10-(somancartao%10)     #O digito de verificacao sera o que falta somar a soma para acabar em zero
        return str(digveri)

def gera_num_cc(abre):
    """Gera um numero de cartao de credito correto"""
    digIni=(('34', '37'),('309', '36', '38', '39'),('65'),('5018', '5020', '5038'),('50', '51', '52', '53', '54', '19'),('4026', '426', '4405', '4508'),('4024', '4532', '4556'))
     #Escolha de um prefixo e o restantes numeros, sem o digito de verificacao
    if abre=='AE':
        comprimento = 14
        prefixo = escolha_random(digIni[0])                   #Escolhe aleatoriamente os prefixos de um tuplo
        iniciomeio = inicio_meio(comprimento, prefixo)        #Gera um numero de cartao com o prefixo escolhido e de comprimento correspondente ao numero da rede emissora escolhida
        cartaofinal = (iniciomeio*10)+eval(digito_verificacao(str(iniciomeio)))     #E adicionado o numero de verificacao ao numero de cartao de credito de modo a ser valido
        return cartaofinal
    elif abre=='DCI':
        comprimento = 13
        prefixo = escolha_random(digIni[1])
        iniciomeio = inicio_meio(comprimento, prefixo)
        cartaofinal = (iniciomeio*10)+eval(digito_verificacao(str(iniciomeio)))
        return cartaofinal        
    elif abre=='DC':
        comprimento=15
        prefixo=digIni[2]
        iniciomeio=inicio_meio(comprimento,prefixo)
        cartaofinal = (iniciomeio*10)+eval(digito_verificacao(str(iniciomeio)))
        return cartaofinal        
    elif abre=='M':
        tupM = (13, 19)
        comprimento = escolha_random(tupM)-1
        prefixo = escolha_random(digIni[3])
        iniciomeio = inicio_meio(comprimento,prefixo)
        cartaofinal = (iniciomeio*10)+eval(digito_verificacao(str(iniciomeio)))
        return cartaofinal        
    elif abre=='MC':
        comprimento = 15
        prefixo = escolha_random(digIni[4])
        iniciomeio = inicio_meio(comprimento, prefixo)
        cartaofinal = (iniciomeio*10)+eval(digito_verificacao(str(iniciomeio)))
        return cartaofinal        
    elif abre=='VE':
        comprimento = 15
        prefixo = escolha_random(digIni[5])
        iniciomeio = inicio_meio(comprimento, prefixo)
        cartaofinal = (iniciomeio*10)+eval(digito_verificacao(str(iniciomeio)))
        return cartaofinal        
    elif abre=='V':
        tupV=(13, 16)
        comprimento = escolha_random(tupV)-1
        prefixo = escolha_random(digIni[6])
        iniciomeio = inicio_meio(comprimento, prefixo)
        cartaofinal = (iniciomeio*10)+eval(digito_verificacao(str(iniciomeio)))
        return cartaofinal        
    else:
        return 'Abreviatura nao corresponde a nenhuma rede emissora'

def escolha_random(t):
    """Escolhe um numero aleatoriamento indicado no argumento"""
    return t[int(random()*len(t))]      #Escolhe o numero do tuplo aleatoriamente

def inicio_meio(comprimento,prefixo):
    """Gera um numero de cartao de credito com o prefixo e o comprimento indicado"""
    final = int(prefixo)
    comprimento = comprimento - len(prefixo)        #comprimento do cartao sem o prefixo
    for i in range(comprimento):
        final = final*10 + int(random()*10)         #Adiciona digitos aleatorios ao numero do cartao ate ter o comprimento sem o ultimo digito de verificacao
    return final