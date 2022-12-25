#
#Ejercicio 4: Strings

#Funciones que se pueden aplicar a los Strings.

myStr="Junior Miguel Lara Torres"

#print(dir(myStr)) #Para ver todas las funciones que se le pueden aplicar.

print(myStr.upper()) #Mayusculas

print(myStr.lower()) #Minusculas

print(myStr.swapcase()) #Cambia Mayusculas por Minusculas y Viceversa.

print(myStr.capitalize()) #Cambia la primera letra a Mayusculas.

print(myStr.replace('Miguel','Shivo')) #Reemplaza una pieza del string por uno deseado

print(myStr.replace('Miguel','Shivo').upper()) #Metodo encadenado, definir uno despues de otro.

print(myStr.count('r')) #Cuenta la cantidad del caracter dentro del String.

print(myStr.startswith('Junior')) #Output Bool, Saber si comienza o no con el caracter o string en cuestion.
print(myStr.startswith('Miguel'))
print(myStr.startswith('J'))

print(myStr.endswith('Lara')) #Output Bool, Saber si termina o no con el caracter o string en cuestion.
print(myStr.endswith('Torres'))
print(myStr.endswith('s'))

print(myStr.split()) #Separa las palabras segun espacio en blanco haya.
print(myStr.split('r')) #Separa las palabras segun el caracter seleccionado.

print(myStr.find('r')) #Busca la posicion del caracter, pero es el primero que encuentra.
                        #Arroja -1 si no encuentra nada.

#Tamaño de un String, comando: LEN
print(len(myStr))

print(myStr.index('r')) #Output indice del caracter en cuestion.
 
print(myStr.isnumeric()) #Pregunta si "myStr" es numerico, Output Bool.

print(myStr.isalpha()) #Pregunta si "mystr" solo tiene letras y almenos 1. Output Bool.

print(myStr[0]) #Pide el caracter que se encuentra en la posicion 6.
print(myStr[7])
print(myStr[14])
print(myStr[19])

print(myStr[-1]) #Pide la ultima posicion, de atras hacia el principio.
print(myStr[-4])
print(myStr[-20])

print('My Name is: '+myStr) #Concatenacion de String con el signo +.

print(f'My Name is: {myStr}') #Concatenacion con comando 'f' y llaves {}.

print('My Name is: {0}, Edad: {1}'.format(myStr,'21')) #Concatenacion con FORMAT.