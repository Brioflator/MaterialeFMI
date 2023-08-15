import Data.List
import Data.Char

palindrom :: String -> Bool
palindrom s = s == reverse s

vocale :: String -> Int
vocale "" =0
vocale (c:s) 
    | c `elem` "aeiouAEIOU" = 1 + vocale s
    | otherwise = vocale s
nrVocale :: [String] -> Int
nrVocale [] =0
nrVocale (s:l)
    | palindrom s = vocale s + nrVocale l
    | otherwise = nrVocale l

--------------------------------------------------------------------
ex2 :: Int -> [Int] -> [Int]
ex2 n [] = [] 
ex2 n (s:l)
    | even s = [s,n] ++ ex2 n l
    | otherwise = s : ex2 n l

-------------------------------------------------------------------

divizori :: Int -> [Int]
divizori n =[d | d <-[1..n], n `mod` d ==0]

-------------------------------------------------------------------

ex4 :: [Int] -> [[Int]]
ex4 l=[divizori n | n<-l]

--------------------------------------------------------------------

ex5 :: Int->Int->[Int]->[Int]
ex5 a b l =[d | d<-l, d `elem` [a..b] ]
--------------------------------------------------------------------

ex6R :: [Int] ->Int
ex6R [] =0
ex6R (h:t)
    | h>0 =1 + ex6R t
    | otherwise = ex6R t

ex6C :: [Int]->Int
ex6C l = length([d | d<-l, d>=0 ])

--------------------------------------------------------------------

ex7C :: [Int] -> [Int]
ex7C l = [p | (d, p) <- zip l [0..], d `mod` 2 ==1 ]



aux7R :: [Int] -> [Int] -> [Int]
aux7R [] l =[]
aux7R (h:t) l 
    | odd h = [(length l) - (length t) -1] ++ aux7R t l 
    | otherwise = aux7R t l
    
ex7R :: [Int] -> [Int]
ex7R l = aux7R l l

---------------------------------------------------------------------------

ex8C :: String -> Int
ex8C s = product([ digitToInt l | l<-s, isDigit l ])

ex8R :: String -> Int
ex8R ""=1
ex8R (h:t)
    | isDigit h = digitToInt h * ex8R t
    | otherwise = ex8R t