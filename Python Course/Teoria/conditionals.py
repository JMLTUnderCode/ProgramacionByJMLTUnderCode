#Name: Junior Lara
#Ejercicio 7: Uso de los Condiconales.
print('')

# Condicionales
x=10
if x==10:
    print('El valor si es igual a 10.')

print('')
print('________________________________________________________________________________')

# Condicionales con ELSE.
x=10
if x<10:
    print('El valor si es menor que 10.')
else:
    print('El valor es mayor o igual que 10')

print('')
print('________________________________________________________________________________')

# Condicionales con ELSE y ELIF
x=100
if x>200:
    print('El valor mayor a 200.')
elif x==100:
    print('El valor es igual a 100.')
else:
    print('Ninguno de los anteriores.')

print('')
print('________________________________________________________________________________')

# Condicionales Anidadas.
Name='Junior'
LName='Lara'

if Name=='Junior':
    if LName=='Lara':
        print('Bienvenido Amo.')
    else:
        print('Sal de aqui impostor')
else:
    print('Quien chingaos sos pendejo :v?')

print('')
print('________________________________________________________________________________')

# Condicionales pero compactas.
Name='Junior'
LName='Torres'

if (Name=='Junior' and LName=='Lara'):
    print('Bienvenido Amo.')
else:
    print('Quien chingaos sos pendejo :v?')

print('')
print('________________________________________________________________________________')

# Operadores Logicos
x=5
y=10
if x>2 and x<10:
    print('x is greater than two and less than or equal to 10.')

if x>2 or x<10:
    print('x is greater than two or less than or equal to 10.')

if (not(x==y)): # Negacion de la preposicion.
    print('x is not equal to y.')

print('')
print('________________________________________________________________________________')