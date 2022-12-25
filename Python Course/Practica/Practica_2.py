#Name: Junior Lara
#Practica 2 - Variables y uso del condicional IF

# 1) De dos numeros saber cual es el mayor.
a=3
b=5

if(a<=b):
    print('A es menor que B')
else:
    print('A es mayor que B')

print('')
print('________________________________________________________________________________')
print('')

# 2) Decir si una variable numerica esta entre 1 y 10.

c=9

if (c>1 and c<10):
    print('El valor esta entre 0 y 10')
else:
    print('El valor NO esta entre 0 y 10')

print('')
print('________________________________________________________________________________')
print('')

# 3) Decir si una variable numerica esta entre 21 y 30 o entre 11 y 20.

d=22

#Primera forma.
if (d>11 and d<20):
    print('El valor esta entre 11 y 20')
elif (d>21 and d<30):
    print('El valor esta entre 21 y 30')
else:
    print('El valor NO esta en ningun rango')

#Segunda forma.
if((d>11 and d<20) or (d>21 and d<30)):
    print('El valor se encuentra en uno de los rangos.')
else:
    print('El valor no esta en ningun rango dado')

print('')
print('________________________________________________________________________________')
print('')