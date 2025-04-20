module Desde (module Desde) where

{-
desde es una función capaz de
dar como salida una instancia
no finita.-
-}

desde :: Integer -> [Integer]
desde n = [n..]

suma :: Integer -> [Integer] -> Integer
suma 0 _ = 0
-- suma _ [] = -1
-- suma _ [] = error "lista demasiado corta"
suma n (x:xs) = x + suma (n-1) xs

longitud :: [a] -> Integer
longitud [] = 0
longitud (x:xs) = 1 + longitud xs
-- longitud [] = 0

sumaB :: Integer -> [Integer] -> Integer
sumaB n lst@(x:xs)
 | n == 0    = 0
 | n > len   = error "lista demasiado corta."
 | otherwise = x + sumaB (n-1) xs
             where
               len = longitud lst
                   
