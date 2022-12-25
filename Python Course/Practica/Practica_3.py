#Name: Junior Lara
#Practica 3 - BUCLES

# 1) Imprimir todos los numeros del 1 al 100 con el Bucle While

i=1 #Se declara la variables antes.
while(i<=100):
    print(i)
    i+=1


print('')
print('________________________________________________________________________________')
print('')

# 2) Imprimir todos los numeros del 1 al 100 con el Bucle For

for i in range(1,101):
    print(i)

#for i in range(101): (Va desde 0 como base.)
#    print(i)


print('')
print('________________________________________________________________________________')
print('')

# 3) Mostrar los caracteres de tu nombre completo.

for i in "Junior Miguel Lara Torres":
    print(i)

#Otra forma (Como for comienza en 0 entonces LEN dara un numero que parte desde el 1.)
myStr='Junior Miguel Lara Torres'
print('Longitud de myStr es: ',len(myStr))
for i in range(len(myStr)):
    print(myStr[i])

print('')
print('________________________________________________________________________________')
print('')

# 4) Mostrar numeros pares del 1 a 100.

#Primera forma.
#for i in range(2,101,2):
#    print(i)

#Segunda forma.
for i in range(1,101):
    if(i%2==0):
        print(i)

print('')
print('________________________________________________________________________________')
print('')