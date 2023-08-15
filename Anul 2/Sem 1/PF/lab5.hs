import Data.List
import Data.Char

--suma patratelor elem impare dintr-o lista
f1::[Int] -> Int
f1 l = foldr (+) 0 (map(^2) (filter(odd ) l))

--verifica daca toate elementele din lista sunt True
f2:: [Bool] -> Bool
f2 l = foldr (&&) True l

--verifica daca toate elem dintr-o lista satisfac o proprietate data ca parametru
f3:: (Int->Bool) -> [Int] -> Bool
f3 p l = foldr (\x  acc -> p x || acc) False l

--verifica daca exista un element care sa satisfaca o proprietate data ca parametru 
f4:: (Int->Bool) -> [Int] -> Bool
f4 p l = foldr (\x  acc -> p x && acc) False l

--transforma lista intr-un numar
f6:: [Int] -> Int
f6 l = foldl (\acc x -> acc*10+x) 0 l

--elimina un caracter din sir
f7:: Char-> String ->String
f7 a l = filter (/=a) l

--elimina toate caracterele din s2 care exista in s1 folosindu-se de f7
f8:: String->String->String
f8 "" s2 = s2
f8 (x:s1) s2 = f8 s1 (f7 x  s2)

--elimina toate caracterele din s2 care exista in s1 folosindu-se de f7(fara recursie)
f9:: String->String->String
f9 s1 s2 = foldr f7 s2 s1