#Name: Junior Lara
#Practica 9: JUEGOS DE DADOS.
print('')

# Escribe un programa de un juego de dados. El juego permite jugar a dos jugadores
# y consiste en implementar la siguiente dinámica:

# 1. Se lanza un dado, y el número que sale es el objetivo de la partida.

# 2. Por orden, los dos jugadores lanzan dos dados cada uno. Gana la partida el 
# jugador que la suma de los dados que ha lanzado coincide con el objetivo. 
# Podemos ganar los dos, uno o ninguno de los jugadores.

# 3. El juego finaliza cuando un jugador gana 2 partidas. El programa debe 
# implementar el juego descrito y cada partida, el programa pregunta si se desea 
# continuar o parar el juego.

# El juego finaliza cuando uno de los dos jugadores gana o bien cuando se indica 
# que no se quiere jugar más. Tenga en cuenta que el programa al principio pide el 
# nombre de los dos jugadores y muestra la información partida a partida indicando 
# el número de partida, el objetivo de la partida, qué dados han sacado cada uno 
# los jugadores, quien gana la partida y al final del juego indica quién ha ganado 
# el juego y cuántas partidas se han jugado.

print('')
print('                                JUEGO DE DADOS')
print('                                   EA GAMES')
print(' ______________________________________________________________________________')
print('|                                                                              |')
print('| Aplicacion inspirada en los juegos de azar.                                  |')
print('| Patrocinado:                                                                 |')
print('| By Casinos Mexico. CA.                                                       |')
print('| By Microsoft Company                                                         |')
print('| Programer: JuniorUnderCode                                                   |')
print('|______________________________________________________________________________|')
print('')
player_1=input('NickName para el Player 1: ')
print('¡Gracias por participar! '+player_1.upper());print('')
player_2=input('NickName para el Player 2: ')
print('¡Genial, ya tenemos contrincante! Y es '+player_2.upper());print('')

from os import system
from random import *
objetivo=randint(2,9)

print('                            Estatus de Participantes')
print(' _____________________________________________________________________________')
print(f'             {player_1.upper()}                                 {player_2.upper()}              ')
print('|  Partidas ganadas: 0                  |    Partidas ganadas: 0              |')
print(f'|  Objetivo: {objetivo}                          |    Objetivo: {objetivo}                      |')
print('|  Dados sacados: Ninguno               |    Dados sacados: Ninguno           |')
print('|_______________________________________|_____________________________________|')

print('')

p1ganadas=0
p2ganadas=0
count_partidas=1

salir=int(input('¡¿Iniciar Juego?! ( SI=1 o NO=0): '))
while salir != 0 and salir != 1:
    salir=int(input('Por favor, ingrese ( SI=1 o NO=0): '))

while p1ganadas != 2 and p2ganadas !=2 and (salir == 1):
    print('')
    print('-------------------------------------------------------------------------------')
    print('')
    print(f'                                  PARTIDA {count_partidas}')
    print('')
    count_partidas+=1

    dado1_1=randint(1,6)
    dado2_1=randint(1,6)
    suma1=dado1_1+dado2_1

    dado1_2=randint(1,6)
    dado2_2=randint(1,6)
    suma2=dado1_2+dado2_2

    print(f'    {player_1.upper()} a obtenido {dado1_1} y {dado2_1}                     {player_2} a obtenido {dado1_2} y {dado2_2}')

    if (suma1==objetivo and suma2==objetivo):
        p1ganadas+=1
        p2ganadas+=1
        print('')
        print(f'                  ¡{player_1.upper()} y {player_2.upper()} HAN GANADO LA PARTIDA!')
        print(' _____________________________________________________________________________')
        print(f'             {player_1}                                 {player_2}              ')
        print(f'|  Partidas ganadas: {p1ganadas}                  |    Partidas ganadas: {p2ganadas}              |')
        print(f'|  Objetivo: {objetivo}                          |    Objetivo: {objetivo}                      |')
        print(f'|  Dados sacados: {dado1_1} , {dado2_1}                 |    Dados sacados: {dado1_2} , {dado2_2}             |')
        print('|_______________________________________|_____________________________________|')   
        print('')
        if p2ganadas==2 and p1ganadas==2:
            print('              ¡TENEMOS GANADORES! Felicidades a '+player_1.upper()+' y '+player_2.upper())
            print('                                ¡Gracias por jugar!')
            break
        elif p1ganadas==2:
            print('                      ¡TENEMOS GANADOR! Felicidades a '+player_1.upper())
            print('                                ¡Gracias por jugar!')
            break
        elif p2ganadas==2:
            print('                      ¡TENEMOS GANADOR! Felicidades a '+player_2.upper())
            print('                                ¡Gracias por jugar!')
            break
    
    elif (suma1==objetivo):
        p1ganadas+=1
        print('')
        print(f'                           ¡{player_1.upper()} HA GANADO LA PARTIDA!')
        print(' _____________________________________________________________________________')
        print(f'             {player_1.upper()}                                 {player_2.upper()}              ')
        print(f'|  Partidas ganadas: {p1ganadas}                  |    Partidas ganadas: {p2ganadas}              |')
        print(f'|  Objetivo: {objetivo}                          |    Objetivo: {objetivo}                      |')
        print(f'|  Dados sacados: {dado1_1} , {dado2_1}                 |    Dados sacados: {dado1_2} , {dado2_2}             |')
        print('|_______________________________________|_____________________________________|')   
        print('')
        if p1ganadas==2:
            print('                      ¡TENEMOS GANADOR! Felicidades a '+player_1.upper())
            print('                                 ¡Gracias por jugar!')
            break

    elif (suma2==objetivo):
        p2ganadas+=1
        print('')
        print(f'                           ¡{player_2.upper()} HA GANADO LA PARTIDA!')
        print(' _____________________________________________________________________________')
        print(f'             {player_1.upper()}                                 {player_2.upper()}              ')
        print(f'|  Partidas ganadas: {p1ganadas}                  |    Partidas ganadas: {p2ganadas}              |')
        print(f'|  Objetivo: {objetivo}                          |    Objetivo: {objetivo}                      |')
        print(f'|  Dados sacados: {dado1_1} , {dado2_1}                 |    Dados sacados: {dado1_2} , {dado2_2}             |')
        print('|_______________________________________|_____________________________________|')   
        print('')
        if p2ganadas==2:
            print('                      ¡TENEMOS GANADOR! Felicidades a '+player_2.upper())
            print('                                 ¡Gracias por jugar!')
            break

    else:
        print('')
        print(f'                           ¡NADIE HA GANADO LA PARTIDA!')
        print(' _____________________________________________________________________________')
        print(f'             {player_1.upper()}                                 {player_2.upper()}              ')
        print(f'|  Partidas ganadas: {p1ganadas}                  |    Partidas ganadas: {p2ganadas}              |')
        print(f'|  Objetivo: {objetivo}                          |    Objetivo: {objetivo}                      |')
        print(f'|  Dados sacados: {dado1_1} , {dado2_1}                 |    Dados sacados: {dado1_2} , {dado2_2}             |')
        print('|_______________________________________|_____________________________________|')   
        print('')
        
    print('')
    salir=int(input('¡¿Siguiente Partida?! ( SI=1 o NO=0): '))
    while salir != 0 and salir != 1:
        salir=int(input('Por favor, ingrese ( SI=1 o NO=0): '))

if salir==0:
    print('')
    print('            Uno de los jugadores abandonò la partida. ¡Gracias por jugar!')

print('')
print('________________________________________________________________________________')
print('')