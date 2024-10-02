//*************************************************************************************************//

// STRING

// Comillas dobles
const str1: string = "Cadena de comillas dobles";

// Comillas simples
const str2: string = 'Cadena de comillas simples';

// Template literals (backticks) (Concatenación de cadenas:):
const nombre: string = 'Junior';
const apellido: string = 'Lara';
const edad : number = 25;

const str3: string = `Hola, mi nombre es ${nombre} ${apellido} y tengo ${edad} años.`;

//*************************************************************************************************//

// NUMBER

// Numeros enteros:
const num1: number = 42;

// Numeros decimales:
const num2: number = 3.14;

// Numero exponenciales:
const num3: number = 3.14e5; // 3.14 x 10^5

// Numeros exponenciales negativos:
const num4: number = 1.23e-4; // 1.23 x 10^-4

// Numeros Hexadecimales (base 16) utilizando el prefijo '0x':
const num5: number = 0xA // 10 en decimal

// Numeros Octales (base 8) utilizando el prefijo '0o':
const num6: number = 0o12 // 10 en decimal

// Numeros Binarios (base 2) utilizando el prefijo '0b':
const num7: number = 0b1010 // 10 en decimal

//*************************************************************************************************//

// BOOLEAN

// Valor booleano true:
const verdadero: boolean = true;

// Valor booleano false:
const falso: boolean = false;

//*************************************************************************************************//

// UNDEFINED

// Declaración de una variable con valor undefined:
let indefinido: undefined;

// Asignación de valor undefined a la variable:
indefinido = undefined;

//*************************************************************************************************//

// NULL

// Declaración de una variable con valor null:
let nulo: null;

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
const numeros: number[] = [1, 2, 3, 4, 5];

// Arreglo de cadenas de texto:
const serie_datos: string[] = ['Dato1', 'Dato2', 'Dato3'];

// Arreglo de booleanos:
const booleanos: boolean[] = [true, false, true];

// Arreglo de objetos:
const objetos: { nombre: string, edad: number }[] = [
    { nombre: 'Juan', edad: 25 },
    { nombre: 'Maria', edad: 30 }
];

//*************************************************************************************************//

// ENUM

// Definición de un enum para dias de la semana:
enum DiasSemana {
    Lunes,
    Martes,
    Miercoles,
    Jueves,
    Viernes,
    Sabado,
    Domingo
}

// Enum con valores de cadena (String Enums):
enum datos_importantes {
    dato1_importante = 'dato1',
    dato2_importante = 'dato2',
    dato3_importante = 'dato3'
}

//*************************************************************************************************//

// FUNCTION

// Declaracion de funcion con tipado explicito:
function Cuadrado(a: number, b: number): number {
    return a*a + 2*a*b + b*b;
}

// Funciones flecha con retorno implicito (inferido por TypeScript):
const division = (a: number, b: number) => a / b;

// Funciones con parametros opcionales:
function saludar2(nombre: string, apellido?: string): string {
    if (apellido !== undefined) {
        return `Hola, ${nombre} ${apellido}`;
    } else {
        return `Hola, ${nombre}`;
    }
}
// Forma mas corta y elegante.
function saludar1(nombre: string, apellido?: string): string {
    return `Hola, ${nombre} ${apellido || ''}`;
}

// Funciones con parametros por defecto:
function saludar3(nombre: string, apellido: string = 'Lara'): string {
    return `Hola, ${nombre} ${apellido}`;
}

//*************************************************************************************************//

// CLASS

// Definición de una clase con propiedades y métodos:
class Persona {
    nombre: string;
    edad: number;
    constructor(nombre: string, edad: number) {
        this.nombre = nombre;
        this.edad = edad;
    }

    saludar() {
        console.log(`Hola, mi nombre es ${this.nombre} y tengo ${this.edad} años.`);
    } 
}

//*************************************************************************************************//

// INTERFACE

// Interface básica:
interface Persona1 {
    nombre: string;
    edad: number;
}

// Interface con propiedades opcionales:
interface Persona2 {
    nombre: string;
    edad: number;
    direccion?: string;
}

// Interface para funciones:
interface Calculadora {
    (a: number, b: number): number;
}

// Interface para clases (class interfaces):
interface Cuadrado {
    lado: number
    calcularArea(): number;
}

//*************************************************************************************************//

// TYPE

// Type básico:
type Nombre = string;
type Numero = number;

// Type basico objeto literal:
type Persona3 = {
    nombre: string;
    edad: number;
};

// Type con union types:
type NumeroOLetra = string | number;

// Type con propiedes opcionales:
type Persona4 = {
    nombre: string;
    edad: number;
    direccion?: string;
};

// Type para funciones:
type Calculadora2 = {
    (a: number, b: number): number;
}

// Type para clases (class Types):
type Cuadrado2 = {
    lado: number
    calcularArea(): number;
}