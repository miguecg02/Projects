module Practicas02 (module Practicas02) where

enumerationwithPattern :: [[Int]] -> [[Int]]
enumerationwithPattern  [] = []
enumerationwithPattern [xs, ys, zs] 
 | null xs || null ys || null zs = []
 | otherwise = take (minlength xs ys zs) (zipWith3 createlist xs ys zs)
 where
    minlength a b c = minimum [length a, length b , length c]
    createlist m n r = [m,n..r]


enumerationwithPattern2 :: [Int]-> [Int]-> [Int]->[[Int]]
enumerationwithPattern2 = zipWith3 enumFromThenTo


multiplesof :: Int ->[Int] -> [(Bool, Int)]
multiplesof n lst
 | null  lst  = error " Se necesita que la lista contenga al menos un elemento"
 |n == 0 = map(\m -> (True, m)) lst --cero = True otherwise False
 |otherwise = map  (\m ->(m  `mod` n == 0, m)) lst


oppositeInverse :: [Double] -> [Double]
oppositeInverse lst
 |null lst = []
 |otherwise = map (\x -> if x/=0 then -(1/x) else 0) lst


oppositeInverse2 :: (Fractional a) => [a] -> [a]
oppositeInverse2 lst = map g lst
                  where
                    g :: (Fractional a) => a ->a
                    g n = recip.negate $ n


multiplesofFind :: Int -> [Int] ->[Int]
multiplesofFind n lst
 | n == 0 =[]
 | null lst = []
 |otherwise = filter ( multiplo) lst
 where
  multiplo = (\m -> (m `mod` n == 0))


longr :: [Int] -> Int
longr  = foldr (\x acc -> acc+1 ) 0


longl :: [Int] -> Int
longl  = foldl (\acc x -> acc+1 ) 0


revl ::[a] -> [a]
revl = foldl (\xs x -> x:xs) []

revr :: [a] -> [a]
revr = foldr ( \x acc  -> acc ++ [x]) []

revel :: Int -> String -> String
revel n xs = (reversePart ++ rest)
 where
 reversePart = foldl(flip (:)) [] (take n xs)
 rest = drop n xs

