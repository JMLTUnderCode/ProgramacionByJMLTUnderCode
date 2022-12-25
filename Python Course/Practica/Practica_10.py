#Name: Junior Lara
#Practica 10

# Escribe un programa que dibuje un peine de tamaño N. El tamaño debe ser un valor 
# positivo impar. Características del peine:

# - Debe tener una altura de N filas.
# - Todas las filas deben tener una anchura también de N.
# - Todas las filas impares deben usar el carácter = y al final mostrar el número 
#   de la fila. El número de la fila que aparece en el dibujo debe tener sólo un 
#   dígito, en cuanto supera el valor de 9 se iniciará nuevamente por 1.
# - Las filas pares deben usar el carácter blanco y al final el carácter +
# - Una vez finalizado el gráfico debe mostrarse en pantalla el número de caracteres
#   que se han usado para hacer el gráfico, concretamente el número de caracteres 
#   diferentes a blanco que se han usado para hacer el dibujo.

# Nota: Al inicio hay que hacer la comprobación en la entrada de datos, asegurando 
# que el número es positivo y impar. El programa insistirá hasta obtener el número 
# con estas propiedades.

# Ejemplo si escribimos 9:

# ========1
#         +
# ========3
#         +
# ========5
#         +
# ========7
#         +
# ========9

print('')
print('________________________________________________________________________________')
print('')

print('                               DIBUJANDO UN PEINE ')
print('')

print('IMPORTANTE: Se pide un numero POSITIVO e IMPAR.')
tamaño=int(input('Inserte el numero: '))
print('')

while (tamaño<0 or tamaño%2==0):
    print('¡ERROR! Se espera un numero IMPAR y POSITIVO: ')
    tamaño=int(input('Intente nuevamente: '))
    print('')

for i in range(1,tamaño+1):
    if i%2 != 0:
        l_impar=' '
        for p_impar in range(tamaño-1):
            l_impar=l_impar+'='
        l_impar=l_impar+f'{i%10}'
        print(l_impar)
    else:
        l_par=' '
        for p_par in range(tamaño-1):
            l_par=l_par+' '
        l_par=l_par+'+'
        print(l_par)
print('')
print('________________________________________________________________________________')

    