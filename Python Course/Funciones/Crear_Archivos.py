def Crear_Archivos(directorio,nombre):

    import sys
    import io
 
    for i in range(1,11):
        name = nombre+f'{i}'+'.py'
        archivo=open(directorio + name,'w')
        archivo.close()

Crear_Archivos('C:/Users/JuniorLara/Desktop/Python Course/Ejercicios/','Exercise_')