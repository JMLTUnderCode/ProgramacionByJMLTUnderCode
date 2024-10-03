// En este Script se muestra el uso de los tipos de datos en TypeScript.
// Se crea una funcion con parametros variados y se muestra el uso de los tipos de datos.

console.log("************************************************");
console.log("********** Tipos de Datos: Primitivos **********\n\n");

let barcelona : string = 'Barcelona';
let goles_barca : number | undefined = 4;
let real_madrid : string = 'Real Madrid';
let goles_madrid : number | undefined = 3;
let messi : string | null = 'Leonel Messi';

function jugar(team1: [number | undefined, string], team2: [number | undefined, string], jugadorEstrella: string | null) {
    if (team1[0] && team2[0]) { // Verificamos si esta definido.
        let message : string = '';
        if (team1[0] > team2[0]) message = `Gana ${team1[1]} contra ${team2[1]}`;
        else if (team1[0] < team2[0]) message = `Gana ${team2[1]} contra ${team1[1]}`;
        else message = 'Empate';

        if (jugadorEstrella){
            let motivo : string = `, porque juega ${jugadorEstrella}.`;
            message = message + motivo;
        }

        console.log(message);
    } else {
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

let etapas : number[] = [1, 2, 3, 4, 5];

let nombres : string[] = ['Juan', 'Maria', 'Pedro'];

console.log(etapas[1].toExponential(3)) 
console.log(nombres[2].indexOf(`o`));

console.log("\n************************************************\n\n");

console.log("************************************************");
console.log("************* Tipos de Datos: OBJECT ***********\n\n");

// TS infiere los tipos de datos.
let program = {
    name : `Hacking`,
    version : 1.0,
    author : `Junior Lara`,
    status : true,
    script : null
}

// Para sobrescribir un objeto debemos escribir todos los atributos.
program = {
    name : `Hacking2`,
    version : 2.0,
    author : `Junior Lara`,
    status : false,
    script : null
}

console.log(program);

console.log("\n************************************************\n\n");

console.log("************************************************");
console.log("************* Tipos de Datos: TYPES ************\n\n");

// Los types, interfaces y clases comienzan con mayuscula.
type type_program = {
    name : string,
    version : number,
    author : string,
    status : boolean,
    script : null
}

// Ahora si podemos tipar el objeto antes creado.
let program2 : type_program = {
    name : `HackingPRO`,
    version : 3.0,
    author : `Junior Lara`,
    status : true,
    script : null
}

// En caso de que el backend no siempre envia un dato.
type Programmer = {
    name : string,
    age? : number | null,
    languages : string[]
}
let junior_lara : Programmer = {
    name : `JMLTUnderCode`,
    languages : ['JavaScript', 'TypeScript', 'Python']
}

let juan_andres : Programmer = {
    name : `Juan1999`,
    age : null,
    languages : ['JavaScript', 'TypeScript', 'Python']
}

console.log(junior_lara);

console.log("\n************************************************\n\n");

console.log("************************************************");
console.log("*********** Tipos de Datos: INTERFACE **********\n\n");

interface Programmer2 {
    name : string,
    age? : number | null,
    languages : string[]
}

let developer : Programmer2 = {
    name : `Junior Lara`,
    age : null,
    languages : ['JavaScript', 'TypeScript', 'Python']
}

let developer2 : Programmer2 = {
    name : `Juan1999`,
    age : null,
    languages : ['JavaScript', 'TypeScript', 'Python']
}
 // Tiene todos los atributos de la Interface con algunos adicionales.
 // Esto permite que el backend agregue mas atributos y poder seguir trabajando.
let developer3 = {
    name : `Carlito`,
    lastname : `Lopez`,
    age : null,
    languages : ['JavaScript', 'TypeScript']
}

function getDeveloper(developer : Programmer2) {
    console.log(`${developer.name} es un desarrollador.`);
}

getDeveloper(developer);
getDeveloper(developer2);
getDeveloper(developer3);

console.log("\n************************************************\n\n");

