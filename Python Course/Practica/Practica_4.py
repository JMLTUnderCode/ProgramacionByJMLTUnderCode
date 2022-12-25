#Name: Junior Lara
#Practica 4: RANGE

# 1) Generar un rango de 1 al 10.
rango_0=list(range(10))
print(rango_0)

print('')
print('________________________________________________________________________________')
print('')

# 2) Generar un rango de 1 al 10, incluido el 10.
rango_1=list(range(11))
print(rango_1)

print('')
print('________________________________________________________________________________')
print('')

# 3) Generar un rango de 5 al 15, incluido el 15.
rango_2=list(range(5,16))
print(rango_2)

print('')
print('________________________________________________________________________________')
print('')

# 4) Generar un rango de 10 a 0, incluido el 0.
rango_3=list(range(10,-1,-1))
print(rango_3)

print('')
print('________________________________________________________________________________')
print('')

# 5) Generar un rango de 0 al 10 y de 15 a 20, incluidos 10 y 20.
rango_4=list(range(11))+list(range(15,21))
print(rango_4)

print('')
print('________________________________________________________________________________')
print('')

# 6) Generar un rango desde 0 hasta la longitud de la cadena “Hola mundo”
l=len('Hola Mundo')
r=list(range(l))
print(r)

print('')
print('________________________________________________________________________________')
print('')