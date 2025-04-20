module PruebaNat (module PruebaNat) where

import Data.Maybe

data Nat = Cero | Suc Nat deriving Show

uno :: Nat
uno = Suc Cero

dos :: Nat
dos = Suc (Suc Cero)    -- podríamos haber escrito Suc uno

tres :: Nat
tres = Suc dos

indefinidoN :: Nat
indefinidoN = undefined

esCero :: Nat -> Bool
esCero Cero = True
esCero _    = False

infinitoN :: Nat
infinitoN = Suc infinitoN

esPar :: Nat -> Bool
esPar Cero    = True
esPar (Suc x) = not.esPar $ x

eP :: Nat -> Bool
eP Cero = True
eP (Suc x) = eI x 

eI :: Nat -> Bool
eI Cero = False
eI (Suc x) = eP x 

construirNAux :: Int -> Nat
construirNAux 0 = Cero
construirNAux n = Suc (construirNAux (n-1))

construirN :: Int -> Maybe Nat
construirN n
  | n < 0  = Nothing
  | n == 0 = Just Cero
  | n > 0  = Just (Suc (construirNAux (n-1)))

desmontarN :: Nat -> Int
desmontarN Cero    = 0
desmontarN (Suc x) = 1 + desmontarN x

desmontarNM :: Maybe Nat -> Int
desmontarNM Nothing = -1
desmontarNM (Just Cero) = 0
desmontarNM (Just (Suc x)) = 1 + desmontarN x

infixl 6 <+>
(<+>)         :: Nat -> Nat -> Nat
Cero <+> n    = n 
(Suc m) <+> n = Suc (m <+> n)  -- (m + 1) + n = (m + n) + 1

{-
infixl 6 <+>
(<+>)         :: Nat -> Nat -> Nat
m <+> Cero    = m
m <+> (Suc n) = Suc (m <+> n) 
-}

infixl 7 <**> --  <*> está reservado en el núcleo
(<**>)         :: Nat -> Nat -> Nat
m <**> Cero    = Cero 
m <**> (Suc n) = m <**> n <+> m         -- ya que m*(n+1)=m*n+m

infixr 8  <^>
(<^>)          :: Nat -> Nat -> Nat
m <^> Cero     = uno
m <^> (Suc n)  = m <**> m <^> n  -- ya que m^(n+1)=m*m^n

newtype Natural = ANatural Integer deriving Show

toNatural :: Maybe Integer -> Maybe Natural
toNatural m
  | isNothing m || isJust m  && fromJust m < 0 = Nothing
  | otherwise = Just (ANatural (fromJust m))

fromNatural :: Maybe Natural -> Maybe Integer
fromNatural m  = case m of
  Nothing -> Nothing
  Just (ANatural n) -> Just n

from_natural :: Maybe Natural -> Maybe Integer
from_natural Nothing = Nothing
from_natural (Just (ANatural n)) = Just n
