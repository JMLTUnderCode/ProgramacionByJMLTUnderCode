#Name: Junior Lara
#Ejercicio 5: Operaciones con Numeros.

a=4
b=6.5

#Suma
Suma=a+b
print(Suma)
print(a+b)

#Resta
Resta=a-b
print(Resta)
print(a-b)

#Multiplicacion
Multi=a*b
print(Multi)
print(a*b)

#Division
Div=a/b
print(Div)
print(a/b)

#Division con decimales
DivD=a/b
#Division sin decimales, solo parte entera
DivE=a//b

#Exponenciacion
Exp=2**a
print(Exp)

Exp_1=(2**a)+(2**b)
print(Exp_1)

#Operador Modular (Devuelve el residuo de dividir con un numero)

Mod = a%2
print(Mod)
Mod_1 = b%2
print(Mod_1)

#Tabla de precedencia de operaciones.
# First: Exponenciacion.
# Second: Multiplicacion, Division y Porcentajes.
# Third: Restas y Sumas.
Preced=3-7+5/5*2**3
print(Preced)
#Usando parentesis se puede anterar el orden de operaciones.
Preced=(3-7)+(5/5)*(2**3)
print(Preced)


