#Name: Junior Lara
#Practica: 8
print('')

# 1) Pintar una escalera de numeros.

print('Esta seccion creara una escalera de numeros.')
altura=int(input('Ingrese la altura que desea: '))
print('')

if altura >0:
    for i in range(altura):
        pisos='     1 '
        for j in range(i):
            pisos=pisos+f'{j+2} '
            
        print(pisos)

else:
    print('No es posible crear una escalera con este numero.')

print('')
print('________________________________________________________________________________')
print('')

# 2) Pintar una piramide de numeros vertical.

print('Esta seccion creara una piramide de numeros vertical.')
altura=int(input('Ingrese la altura que desea: '))
print('')

if altura >0:
    for i in range((2*altura)-1):
        if i <= altura-1:
            pisos='     1 '
            for j in range(i):
                pisos=pisos+f'{j+2} '
            print(pisos)
        else:
            pisos='     '
            for l in range((2*altura-1)-i):
                pisos=pisos+f'{l+1} '
            print(pisos)
            
else:
    print('No es posible crear una escalera con este numero.')

print('')
print('________________________________________________________________________________')
print('')

# 3) Pintar una piramide de numeros horizontal.

print('Esta seccion creara una piramide de numeros horizontal.')
altura=int(input('Ingrese la altura que desea: '))
print('')

if altura >0:
    for i in range(altura):
        espacio='     '
        for j in range(altura-1-i):
            espacio=espacio+' '
        for l in range(i+1):
            espacio=espacio+f'{l+1} '
        print(espacio)
else:
     print('No es posible crear una escalera con este numero.')

print('')
print('________________________________________________________________________________')
print('')