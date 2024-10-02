// Booleanos:
console.log("****************** Booleanos ******************");

let esdudiasteJS: boolean = true;

if (esdudiasteJS) {
    console.log('Excelente');
} else {
    console.log('Tienes que estudiarlo');
}

console.log("***********************************************");

// Number
console.log("******************  Numeros  ******************");

let goles_barca : number = 4;
let goles_madrid : number = 3;

function jugar(team1: [number, string], team2: [number, string]) {
    if (team1[0] > team2[0]) {
        const str = `Gana ${team1[1]}, pierde ${team2[1]}`;
        console.log(str);
    } else if (team1 < team2) {
        const str = 'Gana ${team2[1]}, pierde ${team1[1]}';
        console.log(str);
    } else {
        console.log("Empate");
    }
}

jugar([goles_barca, "Barcelona"], [goles_madrid, "Real Madrid"])

console.log("***********************************************");

