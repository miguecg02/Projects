module Orden (module Orden) where

qsort :: (Ord a) => [a] -> [a]
qsort [] = []
qsort (x:xs) = qsort (filter (< x) xs) ++ [x] ++ qsort (filter (>= x) xs)

qsort_Sr :: (Ord a) => [a] -> [a]
qsort_Sr [] = []
qsort_Sr (x:xs) = qsort_Sr (filter (< x) xs) ++ [x] ++ qsort_Sr (filter (> x) xs)
