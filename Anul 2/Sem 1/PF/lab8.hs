import Data.List
import Data.Char
import System.Win32 (xBUTTON1)

data Punct = Pt [Int]

instance Show Punct where
 show :: Punct -> String
 show (Pt l) = "(" ++ afis l ++ ")"
  where 
    afis[]=""
    afis[x]=show x
    afis(x:y:xs) = show x ++ "," ++ afis (y:xs)

data Arb = Vid | F Int | N Arb Arb
          deriving Show

class ToFromArb a where
  toArb :: a -> Arb
  fromArb :: Arb -> a

instance ToFromArb Punct where
 toArb :: Punct -> Arb
 toArb (Pt []) = Vid
 toArb (Pt [x] ) = F x
 toArb (Pt (x:xs)) = N (F x) (toArb (Pt xs))
 fromArb :: Arb -> Punct
 fromArb (Vid ) = Pt []
 fromArb (F x) = Pt (x:[])
 --fromArb (N x y) = Pt [x]
 
 
-- Pt [1,2,3]
-- (1, 2, 3)

-- Pt []
-- ()

-- toArb (Pt [1,2,3])
-- N (F 1) (N (F 2) (N (F 3) Vid))
-- fromArb $ N (F 1) (N (F 2) (N (F 3) Vid)) :: Punct
--  (1,2,3)
data Geo a = Square a | Rectangle a a | Circle a
    deriving Show

class GeoOps g where
  perimeter :: (Floating a) => g a -> a
  area :: (Floating a) =>  g a -> a

instance GeoOps Geo where
  perimeter :: (Floating a) => Geo a ->a
  perimeter (Square a) = 4*a
  perimeter (Rectangle a b) = 2*(a+b)
  perimeter (Circle a) = 2*pi*a 
  area :: (Floating a) =>  Geo a -> a
  area (Square a) = a*a
  area (Rectangle a b) = a*b
  area (Circle a) = pi*a*a 
-- ghci> pi
-- 3.141592653589793
