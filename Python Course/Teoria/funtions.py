#Name: Junior Lara
#Ejercicio 9: Funciones
print('')

# Definir una funcion.

def hello(): # Definir la funcion.
    print('Hola menol.')

hello() # Llamar a la funcion creada.

print('')
print('________________________________________________________________________________')

# Definir funciones con parametros.

def hello(x):
    print('Hello '+x)

hello('Junior')

# Forma mas complicada.
hello(input('Ingrese su nombre: '))

print('')
print('________________________________________________________________________________')

# Definir funciones con parametros y la ocacion por defecto.

def hello(x='Person'):
    print('Hello '+x)

hello('Junior')
hello()

print('')
print('________________________________________________________________________________')

# Definicion funciones que retornen valores o elementos.

def app(n1=0,n2=0):
    return [f'Suma:{n1+n2}',f'Resta:{n1-n2}'] # Devuelve una LISTA.

def app1(n1=0,n2=0):
    return f'Suma:{n1+n2}',f'Resta:{n1-n2}' # Devuelve una TUPLA

print(app(34,29))
print(app())
print(app1(34,29))

print('')
print('________________________________________________________________________________')

# Funcion LAMBDA ayuda a minimizar las lineas de codigo y es mas compacta.

app = lambda n1,n2: [n1+n2,n1-n2] # Devuelve todo lo que se encuentra despues de :

print(app(123,100))

print('')
print('________________________________________________________________________________')