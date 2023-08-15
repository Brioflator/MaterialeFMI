{-# LANGUAGE BlockArguments #-}
import Data.List
import System.Win32 (xBUTTON1)
import Distribution.Simple.Command (OptDescr(BoolOpt))
import System.Console.Haskeline (Interrupt)

poly2 :: Double ->Double -> Double -> Double -> Double
poly2 a b c x = a*x*x+b*x+c

eeny :: Integer -> String
eeny a  
    | even a = "eeny"
    | otherwise = "meeny"

fizzbuzz :: Integer -> String
fizzbuzz a
    | mod a 15 == 0 ="FizzBuzz"
    | mod a 3 == 0 = "Fizz"
    | mod a 5 == 0 = "Buzz"
    | otherwise = ""

tribonacci :: Integer -> Integer
tribonacci n
    | n<2 = n
    | n==3=2
    | otherwise = tribonacci (n-1) + tribonacci (n-2) + tribonacci (n-3)

fibonacciCazuri :: Integer -> Integer
fibonacciCazuri n
    | n < 2 = n
    | otherwise = fibonacciCazuri (n - 1) + fibonacciCazuri (n - 2)


binomial :: (Integer, Integer) -> Integer
binomial (n, k)
    | n==0=0
    | k==0=1
    | otherwise= binomial ((n-1),  k) + binomial((n-1), (k-1))

lL :: [Int] -> Integer
lL [] = 0
lL (_:xs)= 1 + lL xs

verifL :: [Int] -> Bool
verifL xs = even (lL xs) 

takefinal :: [Int] -> Int -> [Int]
takefinal xs n =  reverse (take n (reverse xs))
-- -- semiPareRec [0,2,1,7,8,56,17,18] == [0,1,4,28,9]
-- semiPareRec :: [Int] -> [Int]
-- semiPareRec [] = []
-- semiPareRec (h:t)
--  | even h    = h `div` 2 : t'
--  | otherwise = t'
--  where t' = semiPareRec t
-- totalLen :: [String] -> Int
-- totalLen = undefined


