# -*- coding: utf-8 -*-
"""
Created on Sun Dec 19 00:14:57 2021

@author: Juan Diego OCANDO RUIZ

Participantes: Luis Becerra (19-10557), Anthony Hernandez (18-10035) y Lorena Rojas (19-10469)
"""

import math
from pickletools import uint8
import numpy as np
import matplotlib.pyplot as plt
import random
import os
import numpy as np
from PIL import Image


def cargar_imagenes(route):
    """
    carga imagenes en una carpeta, la cual transformara en matrices numpy
    y los devolvera en una lista 
    route -> direccion absoluta donde se encuentran las imagenes
    images -> lista de matrices de numpy ndarray
    """
    imagenes = []
    directory = os.fsencode(route)
    os.chdir(route)
    for file in os.listdir(directory): 
        filename  = os.fsdecode(file)
        if filename.endswith(".jpg"): 
            img = Image.open(filename)
            img.load()
            data = np.asarray(img,dtype="uint8")
            print(data.shape)
            imagenes.append(data)
            continue
        else:
            continue
    print("Se cargaron ", len(imagenes), "imagenes")
    return imagenes

def gris (p) -> np.uint8:

    promedio = np.mean(p.shape)
    resultado = np.uint8(promedio)
    if resultado==0:
        return np.uint8(0)
    if resultado<=26:
        return np.uint8(26)
    if resultado<=52:
        return np.uint8(52)
    if resultado<=77:
        return np.uint8(77)
    if resultado<=102:
        return np.uint8(102)
    if resultado<=128:
        return np.uint8(128)
    if resultado<=153:
        return np.uint8(153)
    if resultado<=180:
        return np.uint8(180)
    if resultado<=204:
        return np.uint8(204)
    if resultado<=231:
        return np.uint8(231)
    if resultado==255:
        return np.uint8(255)

def conversion(a):
    # Calculamos dimensiones
    H,W = a.shape

    # Inicializamos variable de escala de gris
    img = np.zeros((H,W), np.uint8)
    
    for x in range(H):
        for y in range(W):
            img[x][y]=gris(a[x][y])

    return img


def vecinoProximo(A : np.ndarray, w : int, h :int) -> np.ndarray:

    # Inicializamos variable de redimension
    a=np.zeros((w,h),np.uint8)

    # Determinamos dimensiones y valor de relacion de tamaños
    H,W = A.shape
    ph,pw = H//h, W//w

    for x in range(H):
        for y in range(W):
            a[x,y]=A[x*ph,y*pw]

    return a


def mediaLocal(A : np.ndarray, w : int, h :int):

    a = np.empty((h,w), np.uint8)
    H,W = A.shape
    ph,pw = H//h, W//w
    for I in range(0,H,ph):
        print(I)
        for J in range(0,W,pw):
            a[I//ph,J//pw]=round(np.mean(A[I:I+ph, J:J+pw]))
    return a

def TablaSuma(A : np.ndarray) -> np.ndarray:

    # Determinamos dimensiones e inicializamos variables
    H,W = A.shape
    S=np.ndarray((H+1,W+1),np.ndarray)

    for l in range(H+1):
        for c in range(W+1):
            S[l][c] = sum( sum ( A[x][y] for y in range(0,c) ) for x in range(0,l) )

    return S

def reduccionSumas1(A, S:np.ndarray, w:int, h:int) :

    # Inicializamos variable
    a=np.empty((h,w),np.uint8)

    # Calculamos dimensiones y relacion de tamaños
    H, W = A.shape
    ph, pw = H//h, W//w
    nbp = ph*pw

    for I in range(0, H, ph):
        for J in range(0, W, pw):
            X = (S[I+ph, J+pw] - S[I+ph, J]) -  (S[I, J+pw] - S[I, J])
            a[I // ph, J // pw] = round( X / nbp)
    return a

def reduccionSumas2(A, S:np.ndarray, w:int, h:int) :
    H, W = A.shape
    ph, pw = H//h, W//w
    sred = S[0:H+1:ph, 0:W+1:pw]
    dc = sred[:, 1:] - sred[:, :-1]
    dl = dc[1:, :] - dc[:-1, :]
    d = dl / (ph*pw)
    return np.uint8(d.round())


def listaRGBtoGris(A):

    # Inicializamos variable
    grispicture = []

    for x in A:
        grispicture=grispicture.append(gris(x))

    return grispicture
    

def listaRedim(A : np.ndarray, w:int, h:int) :

    # Inicializamos variable
    redimpicture = []
    
    for x in A:
        redimpicture = redimpicture.append(mediaLocal(x))
    
    return redimpicture

def initMosaico(source, w:int, h:int, p:int):
    pass

def L1(a,b):
    pass

def escogerMiniatura(bloque: np.ndarray, miniaturas ):
    pass

def construirMosaico(source, vignettes, p):    
    pass

"I. Pixeles e imagenes"


"1.1 Pixeles"

#################################### Respuesta 1 #####################################            
# Un solo pixel de 8 bits cuenta con 256 posibles valores, lo que significa más de 
# 16 millones de combinaciones de colores.


#################################### Respuesta 2 #####################################
pixelBlanco = np.ndarray( [255,255,255], dtype=np.uint8) #Pixel de color blanco


#################################### Respuesta 3 #####################################       
a = np.uint8(280) #La variable "a" vale 24
b = np.uint8(240) #La variable "b" vale 240
np.add(a,b) #a+b vale 8
np.subtract(a,b) #a-b vale 40
np.floor_divide(a,b) #a//b vale 0
np.divide(a,b) #a/b vale 0.1


#################################### Respuesta 4 #####################################
print(gris(pixelBlanco))  


"1.2 Imágenes"

#################################### Respuesta 5 #####################################

# Funcion " def conversion(a :np.ndarray) -> image: " definida arriba.


"II Redimensión de imágenes"


"2.1 Algoritmo de Interpolación por el vecino más cercano"

#################################### Respuesta 6 #####################################

# Funcion " def vecinoProximo(A :imagen, w :int, h :int) -> imagen : " definida arriba.


"2.2 Algoritmo de reducción por medias locales"
#################################### Respuesta 7 #####################################

# Se calculan los valores de relacion entre el tamaño de la imagen dada y la imagen
# redimencionada. Luego se realiza un recorrido por el alto y ancho de la imagen
# dada, este recorrido permite seleccionar y asignar un promedio de pixeles determinado
# por el valor de relacion calculado.   


"2.3 Optimizacion de la reducción por medias locales"
#################################### Respuesta 8 #####################################

# Funcion " def tablaSuma(A :image)-> np. ndarray : " definida arriba.


#################################### Respuesta 9 #####################################



#################################### Respuesta 10 #####################################


"III   Preparando el banco de imágenes "
# Colocar las direccion de la carpeta contenedora de las imaganes
# dentro de las comullas.
pictures = cargar_imagenes(r"direccion")
#################################### Respuesta 11 #####################################

# Funcion " def  listaRGBtoGris(A  :[np.ndarray])->  [image]  : " definida arriba.
grispictures = listaRGBtoGris(pictures)


#################################### Respuesta 12 #####################################

# Funcion " def  listaRedim(A  :[image],h,w)->  [image]  : " definida arriba.
redimpictures = listaRedim(grispictures)


#################################### Respuesta 13 #####################################

# Se quiere un fotomosaico de 50 miniaturas de cada lado, es decir se quiere 50 miniaturas
# de alto y 50 miniaturas de ancho. Este fotomosaico debe tener una dimension de 3750 de alto
# por 5000 de ancho. Entonces, el ALTO de la miniatura debe ser 3750/50 = 75 pixeles, para
# el ANCHO de la miniatura debe ser 5000/50 = 100 pixeles, es decir 75x100.
# La redimension viene dado por

MiniRedim = []
for x in pictures:
    MiniRedim = MiniRedim.append(mediaLocal(x, 100, 50))

#################################### Respuesta 14 #####################################
