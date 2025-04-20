module Ejercicios_Finales_1 (module Ejercicios_Finales_1) where


{-El tipo de dato conjunto representa una colección de elementos en la que cada elemento es único
(no hay elementos repetidos) y no se impone un orden específico sobre los elementos.-}


data Conjunto a = Vacio | Nodo a (Conjunto a) deriving Show

-- Agregar un elemento al conjunto
add :: (Eq a) => a -> Conjunto a -> Conjunto a
add x Vacio = Nodo x Vacio  -- Caso base: si el conjunto es vacio
add x conjunto@(Nodo y resto)
 |x == y  = conjunto -- Si ya se encuentra en el conjunto no se agrega
 |otherwise = Nodo y (add x resto) --En otro caso se añade el nado x a el resto del conjunto




-- Eliminar  un elemento al conjunto
delete :: (Eq a) => a -> Conjunto a -> Conjunto a
delete  x Vacio =  Vacio  -- Si el conjunto es vacio no hay nada que eliminar
delete x conjunto@(Nodo y resto)
 |x == y  = resto  --Si el elemento x coincide con y devolvemos el resto
 |otherwise = Nodo y (delete  x resto) --En otro caso hacemos llamada recursiva a la funcion


--Verifica si todos los elementos de un conjunto conjunto  están contenidos en otro conjunto conjunto
inclusion :: (Eq a )=>  Conjunto a -> Conjunto a -> Bool
inclusion Vacio _ = True  --Si el primer conjunto es Vacio devuelve True.
inclusion (Nodo x resto) conjuntob
  | pertenece x conjuntob = inclusion resto conjuntob -- Si x pertenece a conjuntob verificamos recursivamente si el resto también está incluido en conjuntob
  | otherwise  = False



--Combina dos conjuntos asegurándose de no duplicar elementos
union :: (Eq a) => Conjunto a -> Conjunto a -> Conjunto a
union Vacio conjuntob  = conjuntob -- Si el primer conjunto es vacio la unión es  el segundo conjunto.
union (Nodo x resto) conjuntob
 | pertenece x conjuntob = union resto conjuntob --Si x ya pertenece a conjuntob omitimos x y continuamos con la unión del resto
 |otherwise = Nodo x (union resto conjuntob) --Si x no está en conjuntob añadimos x al resultado y hacemos la unión de resto y conjuntob.

--Devuelve un nuevo conjunto que contiene únicamente los elementos que se encuentran en ambos conjuntos
interseccion :: (Eq a) => Conjunto a -> Conjunto a -> Conjunto a
interseccion Vacio conjuntob = Vacio --Si el primer conjunto es Vacio la intersección también es Vacio, ya que no hay elementos para comparar.
interseccion (Nodo x resto) conjuntob
  | pertenece x conjuntob = Nodo x (interseccion resto conjuntob) --Si x está en conjuntob lo incluye en el resultado
  | otherwise             = interseccion resto conjuntob --Si x no está en conjuntob omite x y llama a interseccion con el resto


--Devuelve un nuevo conjunto que contiene los elementos que están en el primer conjunto, pero no en el segundo
diferencia :: (Eq a) => Conjunto a -> Conjunto a ->Conjunto a
diferencia Vacio conjuntob = Vacio --Si el primer conjunto es Vacio la diferencia también es Vacio
diferencia (Nodo x resto) conjuntob
 | pertenece x conjuntob = diferencia resto conjuntob --Si x está en conjuntob omite x y llama recursivamente a diferencia con el resto
 |otherwise = Nodo x (diferencia resto conjuntob) --Si x no está en conjuntob lo incluye en el resultado y llama a diferencia con el resto


--Calcula  los elementos que están en uno u otro de los dos conjuntos, pero no en ambos.
diferenciaSimetrica :: (Eq a) => Conjunto a -> Conjunto a -> Conjunto a
diferenciaSimetrica conjuntoA conjuntoB = union (diferencia conjuntoA conjuntoB) (diferencia conjuntoB conjuntoA) --La diferencia simétrica se calcula como la unión de dos diferencias


--Verifica si un elemento pertenece a un conjunto
pertenece :: (Eq a) => a -> Conjunto  a ->Bool
pertenece _ Vacio = False -- Si el conjunto es Vacio el elemento no pertenece
pertenece x (Nodo y resto)
  | x == y    = True --Si el elemento x es igual al primer elemento y del conjunto
  | otherwise = pertenece x resto --Si no es igual   realiza  llamada recursiva sobre el resto del conjunto

  --Calcula el número de elementos de un conjunto
cardinalidad :: Conjunto a  -> Int
cardinalidad Vacio = 0 --Si el conjunto es Vacio la cardinalidad es 0
cardinalidad (Nodo _ resto) = 1 + cardinalidad resto --Si el conjunto tiene al menos un elemento la cardinalidad es 1 más la cardinalidad del resto del conjunto

--Convierte un conjunto en una lista de elementos
hacerlist :: Conjunto a -> [a]
hacerlist Vacio = [] --Si el conjunto es Vacio la lista es []
hacerlist (Nodo x resto) = x : hacerlist resto --Si el conjunto tiene al menos un elementocoloca el elemento x al principio de la lista resultante y luego recursivamente convierte el resto del conjunto en una lista
