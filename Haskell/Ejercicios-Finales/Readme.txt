-- Definimos dos conjuntos
let conjuntoA = Nodo 1 (Nodo 2 (Nodo 3 Vacio))
let conjuntoB = Nodo 2 (Nodo 3 (Nodo 4 Vacio))

-- Probar la unión de conjuntos
 union conjuntoA conjuntoB

-- Probar la intersección de conjuntos
 interseccion conjuntoA conjuntoB

-- Probar la diferencia A - B
 diferencia conjuntoA conjuntoB

--Probar la inclusion
 inclusion conjuntoA conjuntoB

--Probar la diferencia simetrica
diferenciaSimetrica conjuntoA conjuntoB


--Probar si pertenece a un conjunto
pertenece 2 conjuntoA


-- Probar la cardinalidad de conjuntoA
cardinalidad conjuntoA

-- Convertir conjuntoA en una lista
hacerlist conjuntoA

-------------------------------------------------------------------------------------------

let conjunto = Nodo 1 (Nodo 2 (Nodo 3 Vacio))

-- Probar la suma de conjuntosSuma
 add 6 conjunto
Nodo 1 (Nodo 2 (Nodo 3 (Nodo 6 Vacio)))

-- Probar la resta de conjuntos
delete  6 conjunto
Nodo 1 (Nodo 2 (Nodo 3 Vacio))
