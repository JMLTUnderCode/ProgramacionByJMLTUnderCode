"use strict";
// En este Script se muestra el uso de los tipos de datos en TypeScript.
// Se crea una funcion con parametros variados y se muestra el uso de los tipos de datos.
console.log("************************************************");
console.log("********** Tipos de Datos: Primitivos **********\n\n");
let barcelona = 'Barcelona';
let goles_barca = 4;
let real_madrid = 'Real Madrid';
let goles_madrid = 3;
let messi = 'Leonel Messi';
function jugar(team1, team2, jugadorEstrella) {
    if (team1[0] && team2[0]) { // Verificamos si esta definido.
        let message = '';
        if (team1[0] > team2[0])
            message = `Gana ${team1[1]} contra ${team2[1]}`;
        else if (team1[0] < team2[0])
            message = `Gana ${team2[1]} contra ${team1[1]}`;
        else
            message = 'Empate';
        if (jugadorEstrella) {
            let motivo = `, porque juega ${jugadorEstrella}.`;
            message = message + motivo;
        }
        console.log(message);
    }
    else {
        console.log("Falta los datos de algun equipo.");
    }
}
console.log(` __________ Marcador _________`);
console.log(`| ${barcelona} ${goles_barca} - ${goles_madrid} ${real_madrid} |`);
console.log(`|_____________________________|`);
jugar([goles_barca, barcelona], [goles_madrid, real_madrid], messi);
console.log("\n************************************************\n\n");
console.log("************************************************");
console.log("************** Tipos de Datos: Any *************\n\n");
// Se usa para saltar las validaciones de tipado de TS. (No recomendado)
let disney; // Esto es un tipo de dato any.
disney = 'Mickey Mouse';
console.log(disney); // Aca TS infiere que es un string.
disney = 100;
console.log(disney); // Aca TS infiere que es un number.
disney = true;
console.log(disney); // Aca TS infiere que es un boolean.
console.log("\n************************************************\n\n");
console.log("************************************************");
console.log("************* Tipos de Datos: ARRAY ************\n\n");
let etapas = [1, 2, 3, 4, 5];
let nombres = ['Juan', 'Maria', 'Pedro'];
console.log(etapas[1].toExponential(3));
console.log(nombres[2].indexOf(`o`));
console.log("\n************************************************\n\n");
console.log("************************************************");
console.log("************* Tipos de Datos: OBJECT ***********\n\n");
// TS infiere los tipos de datos.
let program = {
    name: `Hacking`,
    version: 1.0,
    author: `Junior Lara`,
    status: true,
    script: null
};
// Para sobrescribir un objeto debemos escribir todos los atributos.
program = {
    name: `Hacking2`,
    version: 2.0,
    author: `Junior Lara`,
    status: false,
    script: null
};
console.log(program);
console.log("\n************************************************\n\n");
console.log("************************************************");
console.log("************* Tipos de Datos: TYPES ************\n\n");
// Ahora si podemos tipar el objeto antes creado.
let program2 = {
    name: `HackingPRO`,
    version: 3.0,
    author: `Junior Lara`,
    status: true,
    script: null
};
let junior_lara = {
    name: `JMLTUnderCode`,
    languages: ['JavaScript', 'TypeScript', 'Python']
};
let juan_andres = {
    name: `Juan1999`,
    age: null,
    languages: ['JavaScript', 'TypeScript', 'Python']
};
console.log(junior_lara);
console.log("\n************************************************\n\n");
console.log("************************************************");
console.log("*********** Tipos de Datos: INTERFACE **********\n\n");
let developer = {
    name: `Junior Lara`,
    age: null,
    languages: ['JavaScript', 'TypeScript', 'Python']
};
let developer2 = {
    name: `Juan1999`,
    age: null,
    languages: ['JavaScript', 'TypeScript', 'Python']
};
// Tiene todos los atributos de la Interface con algunos adicionales.
// Esto permite que el backend agregue mas atributos y poder seguir trabajando.
let developer3 = {
    name: `Carlito`,
    lastname: `Lopez`,
    age: null,
    languages: ['JavaScript', 'TypeScript']
};
function getDeveloper(developer) {
    console.log(`${developer.name} es un desarrollador.`);
}
getDeveloper(developer);
getDeveloper(developer2);
getDeveloper(developer3);
console.log("\n************************************************\n\n");
console.log("************************************************");
console.log("************* Tipos de Datos: CLASS ************\n\n");
class Pelicula {
    ;
    constructor(nombre, actores, director, fecha) {
        this.transmision = false;
        this.nombre = nombre;
        this.actores = actores;
        this.director = director;
        this.fecha = fecha;
    }
    info() {
        console.log(`\"${this.nombre}\" es una pelicula de ${this.director}.`);
        console.log(`Actores: ${this.actores}`);
        console.log(`Fecha de estreno: ${this.fecha}`);
    }
    iniciarTransmision() {
        console.log(`Iniciando transmision...`);
        this.transmision = true;
    }
    finalizarTransmision() {
        console.log(`Finalizando transmision...`);
        this.transmision = false;
    }
    estado() {
        console.log(`Estado: ${this.transmision ? `En transmision` : `No transmitiendo`}`);
    }
}
let pelicula1 = new Pelicula(`El Padrino`, [`Marlon Brando`, `Al Pacino`, `Robert Duvall`], `Francis Ford Coppola`, new Date(1972, 11, 24));
pelicula1.info();
pelicula1.iniciarTransmision();
pelicula1.estado();
pelicula1.finalizarTransmision();
pelicula1.estado();
console.log("\n************************************************\n\n");
console.log("************************************************");
console.log("******** Tipos de Datos: Encapsulamientos ******\n\n");
class Estudiantes {
    constructor(nombre) {
        this.nombre = nombre;
    }
    ;
    setInfo(edad, carrera) {
        this.edad = edad;
        this.carrera = carrera;
    }
    ;
    getInfo() {
        return {
            nombre: this.nombre,
            edad: this.edad,
            carrera: this.carrera
        };
    }
    printInfo() {
        console.log(`\nDatos del estudiante:`);
        console.log(`Nombre: ${this.nombre}`);
        console.log(`Edad: ${this.edad}`);
        console.log(`Carrera: ${this.carrera}`);
    }
}
let estudiante1 = new Estudiantes(`Junior Lara`);
estudiante1.setInfo(25, `0800 Ingeniería de Computación`);
estudiante1.printInfo();
console.log(estudiante1.getInfo());
console.log(estudiante1);
console.log("\n************************************************\n\n");
