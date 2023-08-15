import Data.List
import Data.Char

--lista divizorilor pozitivi a lui n
factori :: Int -> [Int]
factori n = [f | f <- [1..n], n `mod` f == 0 ]

--verifica daca n e prim folosindu de functia factori
prim :: Int -> Bool
prim n = length ( factori n) == 2

--gaseste toate numerele prime pana la n
nrPrime:: Int -> [Int]
nrPrime n =[p | p <- [2..n], prim p]

--functie de zip cu 3 argumente
myzip3:: [Int] -> [Int] -> [Int] -> [(Int,Int,Int)]
myzip3 a b c= [ (x,y,z) | (x,(y,z)) <- zip a (zip b c) ]

firstEl:: [(a,b)] -> [a]
firstEl = map fst

sumList:: [[Int]] -> [Int]
sumList = map sum 

prel2::[Int]->[Int]
prel2 = map(\x->if even x then x `div` 2 else x*2)

f8:: Char -> [String] -> [String]
f8 ch s = [el | el<-s, ch `elem` el]

f9::[Int]->[Int]
f9 = map(\x->if even x then x else x^2)

f10:: [Int]->[Int]
f10 l =map(\(a,b)->a^2) (filter(\(a,b)->odd b)(zip l [1..]))

f11::[String] ->[String]
f11 = map(filter(`elem` "aeiou"))
