"use strict";
//*************************************************************************************************//
// STRING
// Comillas dobles
const str1 = "Cadena de comillas dobles";
// Comillas simples
const str2 = 'Cadena de comillas simples';
// Template literals (backticks) (Concatenación de cadenas:):
const nombre = 'Junior';
const apellido = 'Lara';
const edad = 25;
const str3 = `Hola, mi nombre es ${nombre} ${apellido} y tengo ${edad} años.`;
//*************************************************************************************************//
// NUMBER
// Numeros enteros:
const num1 = 42;
// Numeros decimales:
const num2 = 3.14;
// Numero exponenciales:
const num3 = 3.14e5; // 3.14 x 10^5
// Numeros exponenciales negativos:
const num4 = 1.23e-4; // 1.23 x 10^-4
// Numeros Hexadecimales (base 16) utilizando el prefijo '0x':
const num5 = 0xA; // 10 en decimal
// Numeros Octales (base 8) utilizando el prefijo '0o':
const num6 = 0o12; // 10 en decimal
// Numeros Binarios (base 2) utilizando el prefijo '0b':
const num7 = 0b1010; // 10 en decimal
//*************************************************************************************************//
// BOOLEAN
// Valor booleano true:
const verdadero = true;
// Valor booleano false:
const falso = false;
//*************************************************************************************************//
// UNDEFINED
// Declaración de una variable con valor undefined:
let indefinido;
// Asignación de valor undefined a la variable:
indefinido = undefined;
//*************************************************************************************************//
// NULL
// Declaración de una variable con valor null:
let nulo;
// Asignación de valor null a la variable:
nulo = null;
//*************************************************************************************************//
// OBJECT
const info_programador = {
    nombre: 'Junior Lara',
    casado: false,
    lenguajes: ['JavaScript', 'TypeScript', 'Python'],
    salario: 5000,
    trabajo: null,
    actividad: undefined
};
//*************************************************************************************************//
// ARRAY
// Arreglo de numeros;
const numeros = [1, 2, 3, 4, 5];
// Arreglo de cadenas de texto:
const serie_datos = ['Dato1', 'Dato2', 'Dato3'];
// Arreglo de booleanos:
const booleanos = [true, false, true];
// Arreglo de objetos:
const objetos = [
    { nombre: 'Juan', edad: 25 },
    { nombre: 'Maria', edad: 30 }
];
//*************************************************************************************************//
// ENUM
// Definición de un enum para dias de la semana:
var DiasSemana;
(function (DiasSemana) {
    DiasSemana[DiasSemana["Lunes"] = 0] = "Lunes";
    DiasSemana[DiasSemana["Martes"] = 1] = "Martes";
    DiasSemana[DiasSemana["Miercoles"] = 2] = "Miercoles";
    DiasSemana[DiasSemana["Jueves"] = 3] = "Jueves";
    DiasSemana[DiasSemana["Viernes"] = 4] = "Viernes";
    DiasSemana[DiasSemana["Sabado"] = 5] = "Sabado";
    DiasSemana[DiasSemana["Domingo"] = 6] = "Domingo";
})(DiasSemana || (DiasSemana = {}));
// Enum con valores de cadena (String Enums):
var datos_importantes;
(function (datos_importantes) {
    datos_importantes["dato1_importante"] = "dato1";
    datos_importantes["dato2_importante"] = "dato2";
    datos_importantes["dato3_importante"] = "dato3";
})(datos_importantes || (datos_importantes = {}));
//*************************************************************************************************//
// FUNCTION
// Declaracion de funcion con tipado explicito:
function Cuadrado(a, b) {
    return a * a + 2 * a * b + b * b;
}
// Funciones flecha con retorno implicito (inferido por TypeScript):
const division = (a, b) => a / b;
// Funciones con parametros opcionales:
function saludar2(nombre, apellido) {
    if (apellido !== undefined) {
        return `Hola, ${nombre} ${apellido}`;
    }
    else {
        return `Hola, ${nombre}`;
    }
}
// Forma mas corta y elegante.
function saludar1(nombre, apellido) {
    return `Hola, ${nombre} ${apellido || ''}`;
}
// Funciones con parametros por defecto:
function saludar3(nombre, apellido = 'Lara') {
    return `Hola, ${nombre} ${apellido}`;
}
//*************************************************************************************************//
// CLASS
// Definición de una clase con propiedades y métodos:
class Persona {
    constructor(nombre, edad) {
        this.nombre = nombre;
        this.edad = edad;
    }
    saludar() {
        console.log(`Hola, mi nombre es ${this.nombre} y tengo ${this.edad} años.`);
    }
}
