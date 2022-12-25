#Name: Junior Lara
#Ejercicio 7: Uso de las TUPLAS.
print('')

#Definicion de TUPLES.
t=(1,2,3,4,5,6)
meses=('Enero','Febrero','Marzo')
print(t)
print(meses)

print('')
print('________________________________________________________________________________')

#Definicion de tuplas por la funcion TUPLE.
x=tuple((1,2,3,4,5,6))
print(x)

print('')
print('________________________________________________________________________________')

# Saber funciones aplicables a una tupla.
print(dir(x)) # Recordar que una tupla no puede ser modificada.

print('')
print('________________________________________________________________________________')

# IMPORTANTE, si al definir una tupla se coloca 1 solo elemento entonces no se considera
# una tupla sino un valor ENTERO.

p_0=(1,2) # Si es una tupla
print(p_0)
p_1=(434) # No es una tupla, es un numero.
print(p_1)
p_2=(3,)  # Si es una Tupla.
print(p_2)
# La coma es IMPORTANTE dentro de la tupla

print('')
print('________________________________________________________________________________')

# Acceder a los valores de la tupla.
print(x[1])
print(x[4])

print('')
print('________________________________________________________________________________')

# Para borrar una TUPLA.
del p_0

print('')
print('________________________________________________________________________________')

# Otro tipo de uso para las Tuplas. En Diccionarios.
Hubicaciones={
    (234.9348,100.934):'Miranda',
    (-12.32434,123.123):'Petare',
    (12.34123,-78.3431):'Charallave'
}
print(Hubicaciones)

print('')
print('________________________________________________________________________________')


