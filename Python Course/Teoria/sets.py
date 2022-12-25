#Name: Junior Lara
#Ejercicio 7: Uso de los SETS.
print('')

# Definicion de SET manualmente.
colors={'Green','Yellow','Black'}
print(colors)
# IMPORTANTE: Un SET no contiene orden y no se pueden acceder los elementos por indices.
print('')
print('________________________________________________________________________________')

# Saber si un elemento esta en un set.
print('Black' in colors)
print('White' in colors)

print('')
print('________________________________________________________________________________')

# Agregar elementos a un SET. NOTA: Se agregan al inicio del set, pues no existe orden.
colors.add('Violet')
print(colors)

print('')
print('________________________________________________________________________________')

# Remover elementos de un set. 
colors.remove('Green')
print(colors)

print('')
print('________________________________________________________________________________')

# Limpiar o vaciar un SET.
colors.clear()
print(colors)

print('')
print('________________________________________________________________________________')

# Eliminar un set.
x={1,2,3,4,5,6}
print(x)
del x
print('Se borrò.')

print('')
print('________________________________________________________________________________')

print('')
print('________________________________________________________________________________')