#Name: Junior Lara
#Ejercicio 7: Uso de los Diccionarios.
print('')

# Definicion de DICTIONARY
producto={
    'Name':'Caraota',
    'Quantity':100,
    'Price': 3.69
}
print(producto)

print('')
print('________________________________________________________________________________')

# Para saber las funciones aplicables sobre un Dictionary.
print(dir(producto))

print('')
print('________________________________________________________________________________')

# Para Acceder a las LLAVES del Dictionary.
print(producto.keys())

print('')
print('________________________________________________________________________________')

# Para Acceder a los valores o elementos del Dictionary.
print(producto.items())

print('')
print('________________________________________________________________________________')

# Limpiar o vaciar el Dictionary
print(producto.clear())

print('')
print('________________________________________________________________________________')
# Consejo para definir una lista larga de elementos, con el uso de Lists y Dictionaries.
producto=[
    {'Name':'Azucar',      'Quantity':120,  'Price':3.80},
    {'Name':'Caraotas',    'Quantity':90,   'Price':2.50},
    {'Name':'Cafe',        'Quantity':50,   'Price':5.25},
    {'Name':'Pan Harina',  'Quantity':200,  'Price':10.0},
    {'Name':'Atun',        'Quantity':50,   'Price':1.50}
]
print(producto)

print('')
print('________________________________________________________________________________')


print('')
print('________________________________________________________________________________')