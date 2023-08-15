f :: String -> String -> String
f [] _ = []
f _ [] = []
f (x:xs) (y:ys) = if x==y then x:f xs ys else f xs ys

ecuatie :: [Int] -> [Int] -> Int
ecuatie xs ys = 
    if length xs == length ys then 
        sum [x^2*y^2| (x,y)<- zip xs ys] 
    else error "Lungimi diferite"
