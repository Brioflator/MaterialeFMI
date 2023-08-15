import Data.List

myInt :: Integer
myInt = 5555555555555555555555555555555555555555555555555555555555555555555555555555555555555

double :: Integer -> Integer
double x = x+x


maxim :: Integer -> Integer -> Integer
maxim x y = if (x > y)
               then x
          else y

max3 :: Integer -> Integer -> Integer -> Integer
max3 x y z = let
             u = maxim x y
             in (maxim  u z)


max4 :: Integer -> Integer -> Integer -> Integer -> Integer
max4 x y z a =let
    b = maxim x y
    c = maxim z a
    in maxim b c

sqr :: Integer -> Integer -> Integer
sqr x y = let 
        a = x*x; 
        b= y*y
        in a+b

par :: Integral a => a -> IO ()
par x = let y = mod x 2
        in if y == 1
            then print "impar"
            else print "par"


fact :: (Integral a) => a -> a
fact 0 = 1
fact n = n * fact(n-1)

maxsqr :: (Ord a, Num a) => a -> a -> IO ()
maxsqr x y = let z=y*y
    in if x>z 
        then print "este"
        else print "nu este"