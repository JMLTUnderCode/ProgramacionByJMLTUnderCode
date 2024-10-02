"use strict";
// Booleanos:
console.log("****************** Booleanos ******************");
let esdudiasteJS = true;
if (esdudiasteJS) {
    console.log('Excelente');
}
else {
    console.log('Tienes que estudiarlo');
}
console.log("***********************************************");
// Number
console.log("******************  Numeros  ******************");
let goles_barca = 4;
let goles_madrid = 3;
function jugar(team1, team2) {
    if (team1[0] > team2[0]) {
        const str = `Gana ${team1[1]}, pierde ${team2[1]}`;
        console.log(str);
    }
    else if (team1 < team2) {
        const str = 'Gana ${team2[1]}, pierde ${team1[1]}';
        console.log(str);
    }
    else {
        console.log("Empate");
    }
}
jugar([goles_barca, "Barcelona"], [goles_madrid, "Real Madrid"]);
console.log("***********************************************");
