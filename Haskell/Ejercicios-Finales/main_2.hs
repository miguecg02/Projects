-- Main.hs
import Ejercicios_Finales_2
import Text.Read (readMaybe)

main :: IO ()
main = do
    putStrLn "Ingrese los lados del triángulo:"
    
    -- Pedir el primer lado
    putStr "Lado 1: "
    lado1Input <- getLine
    let lado1 = readMaybe lado1Input :: Maybe Double

    -- Pedir el segundo lado
    putStr "Lado 2: "
    lado2Input <- getLine
    let lado2 = readMaybe lado2Input :: Maybe Double

    -- Pedir el tercer lado
    putStr "Lado 3: "
    lado3Input <- getLine
    let lado3 = readMaybe lado3Input :: Maybe Double

    case (lado1, lado2, lado3) of
        (Just a, Just b, Just c) -> do
            if estriangulo a b c
                then case areaTriangulo a b c of
                    area -> putStrLn $ "El área del triángulo es: " ++ show area
                  
                else putStrLn "Los lados ingresados no forman un triángulo."
        _ -> putStrLn "Por favor, ingrese valores numéricos válidos."
