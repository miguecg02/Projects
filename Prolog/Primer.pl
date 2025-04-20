/*
Algoritmo Torres de Hanói Complejidad Θ(2n−1)

Entrada: Número de discos, las tres torres(dos de ellas al principio vacias) origen, auxiliar, destino, con la torre origen ordenada, donde estan los discos al comienzo.

Salida: La torre destino

   1. si origen == { 1 }  entonces
       1. mover el disco 1 de torre origen a la torre destino (insertarlo arriba de la torre destino)
       2. terminar
   2. si no
        hanoi({ 1 , … , n − 1 },origen,destino, auxiliar)   -- mover todas las fichas menos la más grande (n) a la torre auxiliar

   3. mover disco n a destino        --mover la ficha grande hasta la torre final
   4. hanoi (auxiliar, origen, destino)          --mover todas las fichas restantes, 1...n–1, encima de la ficha grande (n)
   5. terminar
*/

% hanoi(N, Origen, Auxiliar, Destino, Movimientos)
% - N: número de discos
% - Origen: torre de la que queremos mover los discos
% - Auxiliar: torre auxiliar que usaremos como paso intermedio
% - Destino: torre a la que queremos mover los discos
% - Movimientos: lista de movimientos necesarios para resolver el problema

    hanoi(0, _, _, _, []) :- !.  % Caso base:no hay discos que mover y la lista de movimientos es vacía ([]).
    hanoi(N, Origen, Auxiliar, Destino, Movimientos) :- % Indica que el predicado es válido solo cuando N es mayor que 0.
    N > 0,
    N1 is N - 1, % Cada llamada recursiva reducimos el numero de discos a mover
% Paso 1: mover N-1 discos de Origen a Auxiliar usando Destino como auxiliar
    hanoi(N1, Origen, Destino, Auxiliar, Movimientos1),
% Paso 2: mover el disco más grande directamente de Origen a Destino
    MovimientoActual = [move(Origen, Destino)],
% Paso 3: mover N-1 discos de Auxiliar a Destino usando Origen como auxiliar
    hanoi(N1, Auxiliar, Origen, Destino, Movimientos2),
% Concatenar todos los movimientos
    append(Movimientos1, MovimientoActual, TempMovimientos),
    append(TempMovimientos, Movimientos2, Movimientos).

% Imprimir toda la secuencia de la lista movimientos
     mostrar_hanoi(N) :-
     hanoi(N, 'Origen', 'Auxiliar', 'Destino', Movimientos),
     write(Movimientos).
