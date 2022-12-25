# Ejercicio 4: Solicitar al usuario el radio de un circulo para el calculo de area del mismo.

print()
print('    Este programa calcula el area de un circulo.')
print()
rate=int(input('    Ingrese un valor positivo: '))

while rate < 0:
    print()
    print('    ¡INVALIDO!')
    rate=int(input('    Ingrese un valor positivo: '))

from math import pi

area=pi*rate**2

print()
print('    El Radio dado fue {0} y el area del circulo es: {1}'.format(rate,area))