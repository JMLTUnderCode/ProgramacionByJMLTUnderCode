#Name: Junior Lara
#Practica 6
print('')

# 1) Juguemos al juego de adivinar el numero, generaremos un número entre 1 y 100.
# Nuestro objetivo es adivinar el número. 
# Si fallamos nos dirán si es mayor o menor que el número buscado.
# También poner el número de intentos requeridos.

from random import *
numero=randint(0,100)

numero_u=int(input('Pruebe su suerte: '))
intentos=0

while numero != numero_u:
    if numero_u > numero:
        print('El numero buscado es MENOR.')
        intentos+=1
    elif numero_u < numero:
        print('El numero buscado es MAYOR')
        intentos+=1
    numero_u=int(input('Pruebe su suerte, nuevamente: '))

print(f'Haz acertado!! El numero es {numero}, con un total de {intentos} intentos!!')

print('')
print('________________________________________________________________________________')