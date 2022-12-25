#Name: Junior Lara
#Ejercicio 8: Loops (Bucles)
print('')

# Bucle FOR con listas.
lista=['Cheese','Grapes','Milk','Bread','Apples','Bananas']

for i in lista:
    print(i)

print('')

for i in lista:
    if i=='Grapes':
        print('You have to buy this article.')
    print(i)


print('')
print('________________________________________________________________________________')

# Si se desea parar el bucle en determinada condicion.

for i in lista:
    if i=='Apples':
        print('No more articles.')
        break
    print(i)

print('')
print('________________________________________________________________________________')

# Si no se desea ejecutar las lineas de codigo en determinada condicion.

for i in lista:
    if i=='Apples':
        print('This articles, no.')
        continue
    print(i)

print('')
print('________________________________________________________________________________')

# Iterar en un rango.

for i in range(1,10):
    print(i)

print('')
print('________________________________________________________________________________')

# Iterar en un string.

for i in 'Junior Lara':
    print(i)

print('')
print('________________________________________________________________________________')

# Bucle WHILE
count=0

while (count >= 0 and count <= 10):
    print(count)
    count+=1

print('')
print('________________________________________________________________________________')