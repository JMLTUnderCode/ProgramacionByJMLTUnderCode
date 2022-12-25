#Name: Junior Lara
#Ejercicio 10: MODULOS (Librerias)
print('')

# Modulos pre-construidos (Modulos de Python)

# Ejemplo: Para saber la fecha y hora.

import datetime # Importa TODOS los metodos que existen en el Modulo.

print(datetime.date.today())

# Para saber los modulos que existen en python colocar "Python Modules Index" en Google.
# IMPORTANTE: Se pueden descargar modulos desde otras paginas, compañias, etc.

print('')
print('________________________________________________________________________________')

# Para transformar de minutos a horas.

print(datetime.timedelta(minutes=100))

print('')
print('________________________________________________________________________________')

# Otra manera de importar, importa una funcionalidad especificica.

from datetime import timedelta

print(timedelta(minutes=80)) # Se simplifica el comando a timedelta pues se importo directamente.

print('')
print('________________________________________________________________________________')

# Importar mas de una funcionalidad.

from datetime import timedelta,date

print(timedelta(minutes=250))
print(date.today())

print('')
print('________________________________________________________________________________')

# Crear un modulo (Cree uno llamado fcalc: Una calculadora )

import fcalc

fcalc.add(90,100)
fcalc.sust(90,100)
fcalc.mult(90,100)
fcalc.div(90,100)
fcalc.divv(90,100)
fcalc.mod(90,100)

print('')
print('________________________________________________________________________________')

# Importar modulos de manera tal que sea mas sencilla de trabajar.

from fcalc import *

add(90,100)
sust(90,100)
mult(90,100)
div(90,100)
divv(90,100)
mod(90,100)

print('')
print('________________________________________________________________________________')