module Ejercicios_Finales_2 (module Ejercicios_Finales_2) where


-- Determina si tres números pueden ser los lados de un triángulo
estriangulo :: (Num a,  Ord a ) => a -> a -> a -> Bool
estriangulo a b c = a + b > c && a + c > b && b + c > a --Si la suma de dos lados no es mayor que el tercero no es un triangulo
---- Esta condición se cumple en la desigualdad triangular: la suma de cualquier par de lados debe ser mayor que el tercer lado

-- Calcula la raíz cuadrada usando el método de Newton
raizNewton :: (Fractional a, Ord a) => a -> a
raizNewton x = newton x x
  -- El primer x es el número al que le queremos calcular la raíz cuadrada,
  -- y el segundo x se usa como una aproximación inicial para el método de Newton

  where
     -- Definimos la función auxiliar newton que realiza las iteraciones del método
    newton :: (Fractional a, Ord a) => a -> a -> a
    newton n guess
      | abs (guess * guess - n) < 1e-10 = guess
       -- Si la diferencia entre el cuadrado de guess y n es muy pequeña (menor que 1e-10),
       -- se considera que hemos encontrado la raíz cuadrada y se devuelve guess
      | otherwise = newton n ((guess + n / guess) / 2)
       -- Si no hemos alcanzado el margen de error deseado, calculamos una nueva aproximación
       -- usando la fórmula del método de Newton para la raíz cuadrada


-- Calcula el área de un triángulo usando la fórmula de Herón
areaTriangulo :: (Floating a, Ord a) => a -> a -> a ->  a
areaTriangulo a b c  = raizNewton (s * (s - a) * (s - b) * (s - c))
-- Usamos la raíz cuadrada calculada por el método de Newton para obtener el área
-- s es el semiperímetro del triángulo, que es la mitad de la suma de sus lados
  where
    s = (a + b + c) / 2 -- s es el semiperímetro: la suma de los tres lados dividida entre 2

