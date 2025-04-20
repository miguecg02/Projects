module Pila (TPila, mete, saca, vacia, muestra) where

data TPila a = PilaVacia | Apila a (TPila a) deriving Show

mete :: a -> TPila a -> TPila a
mete x p = Apila x p

saca :: TPila a -> TPila a
saca PilaVacia = error "Sacando elementos de pila vacía"
saca (Apila _ p) = p

vacia :: TPila a
vacia = PilaVacia

muestra :: (Show a) => TPila a -> String
muestra PilaVacia = " "
muestra (Apila x p) = " " ++ show x ++ muestra p
