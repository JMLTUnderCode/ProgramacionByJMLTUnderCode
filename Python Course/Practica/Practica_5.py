#Name: Junior Lara
#Practica 5

# 1) Pide dos cadenas por teclado, muestra ambas cadenas con un espacio entre ellas 
#y con los 2 primeros caracteres intercambiados. Por ejemplo, "hola mundo" pasaria a 
# "mula hondo"
str1=input('Ingrese primera palabra: ')
str2=input('Ingrese segunda palabra: ')

print(str2[:2]+str1[2:] + ' ' + str1[:2]+str2[2:])

print('')

# Segunda forma.
Str=input('Coloque las dos palabras: ')
Separacion=Str.split(' ') #Genera una LISTA.
print((Separacion[1])[:2]+(Separacion[0])[2:] + ' ' + (Separacion[0])[:2]+(Separacion[1])[2:])

print('')
print('________________________________________________________________________________')
print('')

# 2) Pide una cadena e indica si es un palíndromo o no.
cadena=input('Inserte la PALABRA: ')
cadena_r=cadena[::-1]

if cadena==cadena_r:
    print('Esta palabra es Palindroma.')
else:
    print('Esta palabra no es Palindroma')

print('')
# Segun da forma.
Str_1=input('Inserte la PALABRA: ')
Str_r=''
for i in range(len(Str_1)):
    Str_r=Str_r+Str_1[(len(Str_1)-1)-i]

if Str_r==Str_1:
    print('Esta palabra es Palindroma.')
else:
    print('Esta palabra no es Palindroma')

print('')
print('________________________________________________________________________________')
print('')