module Criba (module Criba) where

criba :: [Integer] -> [Integer]
criba (p:xs) = [x | x <- xs, p `noDivideA` x]
                      where m `noDivideA` n = mod n m /= 0

primos :: [Integer]
primos = map head (iterate criba [2..])

-- [primos !! x | x <- [0..15]]

lprimos :: [[Integer]]
lprimos = [2..] : map criba lprimos

-- map (take 5) (take 10 lprimos)

primosEq :: [Integer]
primosEq = map head lprimos 
           where lprimos = [2..] : map criba lprimos
