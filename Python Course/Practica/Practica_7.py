#Name: Junior Lara
#Practica: 7
print('')

# 1) Pintar una escalera con *

print('Esta seccion creara una escalera con el simbolo (*).')
escalones=int(input('Ingrese el numero de peldaños: '))
print('')

peldaños=''
if escalones > 0:
    for i in range(escalones):
        peldaños=peldaños+'* '
        print(peldaños)
else:
    print('No es posible crear una escalera con ese numero.')

print('')
print('________________________________________________________________________________')
print('')

print('Esta seccion creara un recuadro con el simbolo (*).')
longitud=int(input('Ingrese el tamaño del cuadro deseado: '))
print('')

if longitud > 0:
    for i in range(longitud):
        if i==0 or i==(longitud-1):
            sup=''
            for b_sup in range(longitud):
                sup=sup+'* '
            print(sup)
        else:
            lado='* '
            for relleno in range(longitud-2):
                lado=lado+'  '
            lado=lado+'*'
            print(lado)
else:
    print('No es posible crear un recuadro con ese numero.')

print('')
print('________________________________________________________________________________')
print('')