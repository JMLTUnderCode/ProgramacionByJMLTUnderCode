#Name: Junior Lara
#Ejercicio 6: Uso del comando IMPUT

#Pedir al usuario informacion.

Name=input('Insert your first name: ')
LName=input('Insert your last name: ')
Age=input('Insert your Age: ')
Weight=input('Insert your Weight: ')
Height=input('Insert your Height: ')

#Mostrando una TUPLA de datos de la persona.
print('')
Tabla_info=(Name,LName,Age,Weight,Height)
print(Tabla_info)

#
# IMPORTANTE: Todo la informacion o datos proporcionada por el usuario es leida como STRING.
#

#Ejemplo: Nueva tabla de informacion de la persona.
print('')
Age=int(Age)+5 #Transformamos el tipo de dato a ENTERO para poder SUMAR.
Weight=int(Weight)+10
Height=float(Height)+0.02 #Transformamos el tipo de dato a FLOAT para poder SUMAR.

Tabla_info1=(Name,LName,Age,Weight,Height)
print('La informacion de la persona en 5 años sera: ',Tabla_info1)