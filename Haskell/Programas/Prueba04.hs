module Prueba04 (module Prueba04) where

import Data.Monoid
import Data.Tuple -- para tener swap
import Data.Maybe -- para tener fromJust

-- https://www.rapidtables.com/web/color/RGB_Color.html

data RGB = Red | Green | Blue deriving Read

instance Eq RGB where
 Blue  == Blue  = True
 Red   == Red   = True
 Green == Green = True
 _ == _         = False

-- $ read "Blue"  > Red
--True

newtype LexInt = LexInt [Int] -- ints in reverse digit order

instance Eq LexInt where
    (==) (LexInt lst) (LexInt mst) = lst == mst

{-
instance Eq LexInt where
    (==) (LexInt []) (LexInt []) = True
    (==) (LexInt (l:ls)) (LexInt (r:rs)) = (l == r) && ((LexInt ls) == (LexInt rs))
    (==) _ _ = False
-}

instance Show RGB where
 show Red = show (255,0,0)
 show Green = show (0,255,0)
 show Blue = show (0,0,255)

instance Ord RGB where
  Red < Green = True
  Red < Blue  = True
  Green < Blue = True
  _ < _        = False
  x <= y = (x == y) || (x < y)

-- $ read "Blue"  > Red
--True

data RVA = Rojo | Verde | Azul deriving (Read,Eq)

instance Ord RVA where
    compare m n
     | m == n = EQ
--     | m == Rojo = LT
     | m == Rojo || m == Verde && n == Azul = LT
--     | m == Verde && n == Azul = LT
     | otherwise = GT
     
-- https://stackoverflow.com/questions/32907458/defining-a-special-ord-for-a-data-type-in-haskell
-- https://stackoverflow.com/questions/16927710/type-constraints-for-automatic-function-constraint-deduction-in-haskell

data Point = Point Int Int -- deriving (Eq,Ord)

instance Eq Point where
    Point x1 y1 == Point x2 y2 = (x1==x2 && y1==y2)

-- https://stackoverflow.com/questions/32907458/defining-a-special-ord-for-a-data-type-in-haskell

{- Ordering está en Monoid como sigue:

mempty = EQ
 LT <> _ = LT
 GT <> _ = GT
 EQ <> x = x
-}

instance Ord Point where
    compare (Point x1 x2) (Point y1 y2) = (compare x1 y1) <> (compare x2 y2)

-- https://stackoverflow.com/questions/6000511/better-way-to-define-an-enum-in-haskell

data MyDataType = Foo | Bar | Baz
                deriving (Show,Eq)

-- data MyDataType = Foo | Bar | Baz | Raz
--                deriving (Show,Eq)

{-
instance Enum MyDataType where
 toEnum 0 = Foo
 toEnum 1 = Bar
 toEnum 2 = Baz

 fromEnum Foo = 0
 fromEnum Bar = 1
 fromEnum Baz = 2 

 -}

-- {-
table = [(Foo, 0), (Bar, 1), (Baz, 2)] -- zip [Foo, Bar, Baz] [0,1,2]
instance Enum MyDataType where
    fromEnum = fromJust . flip lookup table
    toEnum = fromJust . flip lookup (map swap table)
-- -}
