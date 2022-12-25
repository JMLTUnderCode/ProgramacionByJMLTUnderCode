# Ejercicio 3: Obtener la fecha y la hora actuales en el sistema.

import datetime

Now=datetime.datetime.now()

print(Now)

print(type(Now))

print(Now.strftime('%d/%m/%Y %H:%M:%S'))