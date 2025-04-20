module EjerciciosPrac03_hecho_clase (module EjerciciosPrac03_hecho_clase) where

import Data.List

type Fecha = (Int,Int,Int)
data DiaSemana = Lunes | Martes | Miercoles | Jueves | Viernes | Sabado | Domingo deriving Show

trad :: Int -> DiaSemana
trad 0 = Sabado
trad 1 = Domingo   
trad 2 = Lunes     
trad 3 = Martes    
trad 4 = Miercoles 
trad 5 = Jueves    
trad 6 = Viernes                -- patrón incompleto, pero no pasa nada

diaS :: Int -> Int -> Int -> Int
diaS q m a = (q+ ((((f m)+1)*26) `div` 10)+ (k m a) + ((k m a) `div` 4)
              + ((j m a) `div` 4) - 2*(j m a)) `mod` 7
  where
    f :: Int -> Int
    f  m
      | m <=2 = m + 12
      | otherwise = m
      
    k :: Int -> Int -> Int
    k m a
      | m <=2 = (a-1) `mod` 100 
      | otherwise = a `mod` 100
      
    j :: Int -> Int -> Int
    j m a
      | m <=2 = (a-1) `div` 100 
      | otherwise = a `div` 100

diaSemana :: Fecha -> DiaSemana
diaSemana (x,y,z) = trad.diaS x y $ z

-- Fórmula de Herón

{-
rotateLevAux :: [Float] -> [[Float]]
rotateLevAux xs = take len $ map (take len) $ tails $ cycle xs
    where
        len = length xs

rotateLev :: Int ->  [Float] -> [Float]
rotateLev n xs = (rotateLevAux xs) !! n

sumInit :: [Float] -> Float
sumInit lst = sum.init $ lst

compareLados :: [Float] -> Bool
compareLados lst = sumInit lst > last lst  
-}

sumInit :: [Float] -> Float
sumInit lst = sum.init $ lst

esTriangulo :: [Float] -> Bool
esTriangulo lst = sumInit mst > last mst
  where
    mst = sort lst

areaTriangulo :: Float -> Float -> Float -> Float
areaTriangulo x y z 
  | esTriangulo [x,y,z] == True = sqrt (s*(s-x)*(s-y)*(s-z))
  | otherwise = error "el argumento no es triángulo"
  where
    s = (x+y+z)/2
