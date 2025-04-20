module Practica3 (module Practica3) where
import Data.Time (fromGregorian, Day ,   toGregorian)



data DiaSemana = Lunes | Martes | Miercoles | Jueves | Viernes | Sabado | Domingo
               deriving Show


numdia :: Int -> DiaSemana
numdia 2=Lunes 
numdia 3 = Martes
numdia  4= Miercoles
numdia 5= Jueves
numdia 6 = Viernes
numdia 0= Sabado
numdia 1= Domingo


data DiaNum = Dia DiaSemana | Num Integer deriving Show



dia_seman_gregoriano :: Day -> DiaSemana
dia_seman_gregoriano fecha = numdia (h+1)
 where
  (anio,mes,dia) = toGregorian fecha
  (m, k, j) = if mes < 3
                then (mes + 12, (anio - 1) `mod` 100, (anio - 1) `div` 100)
                else (mes, anio `mod`100, anio `div` 100)
  h = (dia+(((mes+1)*13)`div` 5)+fromInteger(k) +((fromInteger k) `div`4) +  ((fromInteger (j))`div` 4) + fromInteger(k) * 5) `mod`7

dia_seman_juliano :: Day -> DiaSemana
dia_seman_juliano fecha = numdia h
 where
  (anio,mes,dia) = toGregorian fecha
  (m, k, j) = if mes < 3
                then (mes + 12, (anio - 1) `mod` 100, (anio - 1) `div` 100)
                else (mes, anio `mod`100, anio `div` 100)
  h =(dia+(((mes+1)*13)`div` 5)+fromInteger(k) +((fromInteger k) `div`4) +5 + fromInteger(k) * 6) `mod`7



data Conv = FtoC  Float | CtoF  Float deriving Show

conversor :: Conv -> Float
conversor (CtoF a ) =(( a*9) /  5.0)+32
conversor (FtoC b) =((b-32)*5) /  9.0


data Point = Point Float Float deriving Show

data Shape = Circle Point Float | Rectangle Point Point deriving Show


baseCircle :: Shape -> Float
baseCircle (Circle _ r)= pi * r^2

baseRect  :: Shape -> Float 
baseRect (Rectangle (Point 0 0 ) (Point x2 y2)) =  (abs $ x2 - 0) * (abs $ y2 - 0)

nudge :: Shape -> Float ->Float -> Shape
nudge (Rectangle (Point 0 0 ) (Point x2 y2)) a b = Rectangle (Point (0+a)(0+b )) (Point x2 y2)


data Triangle = Triangle Double Double deriving Show

area :: Triangle -> Double
area (Triangle b h) = (b*h) / 2

data Auto = Auto{
marca :: String,
matricula :: Int,
color :: String,
precio :: Float
} deriving Show

descripcion_auto ::  Auto -> String
descripcion_auto coche = "Este" ++ show (marca coche) ++  "de color" ++ show(marca coche)++
                         " tiene la matricula:  " ++ show (matricula coche) ++ 
                         "  y cuesta " ++ show (precio coche) ++ " euros."



data Vector a = Vector [a] deriving Show

productEscalar :: Num a => Vector a  -> Vector a  -> a
productEscalar (Vector ys) (Vector xs ) = sum (zipWith (*) ys xs)

productVectorial ::  Num a => Vector a  -> Vector a  ->  Vector a
productVectorial    (Vector [v1, v2, v3]) (Vector [w1, w2, w3])= Vector [(v2*w3 -v3*w2),(v3*w1 -v1*w3),(v1*w2-v2+w1)]



{-
data Nat = Cero | Suc Nat deriving  Show

divNat :: Nat -> Nat -> Nat
divNat Cero _ = Cero  
divNat _ Cero = error "División por cero"
divNat (Suc a) (Suc b)
    | a < b     = Cero 
    | otherwise = Suc (divNat (subtract-(Suc b)) (Suc b))
-}



data Complex a = Complex a a  deriving Show

modulo :: Floating a => Complex a -> a
modulo (Complex x y) = sqrt(x^2 y^2)


suma :: Floating a = > Complex a -> Complex a -> Complex a
suma (Complex x1 y1) (Complex x2 y2) = Complex (x1+x2) (y1+y2)

resta  :: Floating a = > Complex a -> Complex a -> Complex 
resta  (Complex x1 y1) (Complex x2 y2) = Complex (x1-x2) (y1-y2)

multiplicar :: Num a => Complex a -> Complex a -> Complex a
multiplicar (Complex x1 y1) (Complex x2 y2) = Complex (x1 * x2 - y1 * y2) (x1 * y2 + y1 * x2)



