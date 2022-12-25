#Name: Junior Lara
#Ejercicio 7: Uso de las LISTAS.

#Definir listas manualmente.
my_list=[1,'hola',True,10.9,[1,2,3,4]]
print(my_list)
colors=['Green','Yellow','Orange','Black','White']
print(colors)

print('')
print('________________________________________________________________________________')
#Definicion por funcion LIST
number_list=list( (1,2,3,4,5,6,7,8,9) ) 
print(number_list)
# Al comando LIST debe tener una UNICA entrada, en este caso debe ser UN TUPLA.

print('')
print('________________________________________________________________________________')

#Formando LISTAS con comando RANGE.
#Range acepta desde 1 parametro hasta 3.
# First: INICIO
# Second: FINAL
# Third: PASOS A DAR.
r=list(range(1,10)) #Genera una lista desde 1 hasta FINAL menos 1.
print(r)

r_1=list(range(1,10,2)) #De 2 en 2.
print(r_1)

print('')
print('________________________________________________________________________________')

#Pedir informacion de las LISTAS. Tambien funciona colocando indices NEGATIVOS.
print(colors[4])
print(my_list[4])

print('')
print('________________________________________________________________________________')
#Saber si un elemento esta dentro de una lista. con funcion "IN"
print("green" in colors)
print("Green" in colors)

print('')
print('________________________________________________________________________________')
#Cambiar elemento de la lista.
colors[2]='Blue'
my_list[4]='White'
print(colors,my_list)

print('')
print('________________________________________________________________________________')

#Funciones sobre las LISTAS.

#Agregar UN elemento a la lista. Si se añade una tupla o lista como argumento entonces
#el elemento añadido sera una tupla o lista.
colors.append('violet')
print(colors)
my_list.append(['violet','Red'])
print(my_list)

print('')
print('________________________________________________________________________________')
#Para agregar varios elementos como elementos unicos de la lista.
colors.extend(['violet','Red'])
print(colors)

print('')
print('________________________________________________________________________________')
#Para INSERTAR un elemento en una posicion especifica.
colors.insert(1,'pink')
print(colors)

print('')
print('________________________________________________________________________________')
#Otra forma de INSERTAR elementos al final de la lista, con LEN.
my_list.insert(len(my_list),'Pink')
print(my_list)

print('')
print('________________________________________________________________________________')
#Para quitar el ultimo elemento de la lista.
colors.pop()
print(colors)

print('')
print('________________________________________________________________________________')
#Para quitar elementos por INDICE.
colors.pop(2)
print(colors)

print('')
print('________________________________________________________________________________')
#Para quitar un elemento en especifico.
colors.remove('Black')
print(colors)
my_list.remove(1)
print(my_list)

print('')
print('________________________________________________________________________________')
#Para ordenar ALFABETICAMENTE los elementos de la lista.
colors.sort()
print(colors)

print('')
print('________________________________________________________________________________')
#Para ordenar de manera inversa una LISTA..
colors.sort(reverse=True)
print(colors)

print('')
print('________________________________________________________________________________')
#Para extraer indices de los elementos de una lista.
print(colors)
print('El indice de Blue es: ',colors.index('Blue'))

print('')
print('________________________________________________________________________________')
#Para contar los elementos dentro de una lista.
print('La cantidad Blues es: ',colors.count('Blue'))

print('')
print('________________________________________________________________________________')
#Para limpiar la LISTA.
colors.clear()
print(colors)






