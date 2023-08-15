import Data.List
import Data.Char
-- --ex 1
-- data Fruct = 
--     Mar String Bool
--     | Portocala String Int

-- ionatanFaraVierme :: Fruct
-- ionatanFaraVierme = Mar "Ionatan" False
-- goldenCuVierme :: Fruct
-- goldenCuVierme = Mar "Golden Delicious" True
-- portocalaSicilia10 :: Fruct
-- portocalaSicilia10 = Portocala "Sanguinello" 10
-- listaFructe :: [Fruct]
-- listaFructe = [
--     Mar "Ionatan" False,
--     Portocala "Sanguinello" 10,
--     Portocala "Valencia" 22,
--     Mar "Golden Delicious" True,
--     Portocala "Sanguinello" 15,
--     Portocala "Moro" 12,
--     Portocala "Tarocco" 3,
--     Portocala "Moro" 12,
--     Portocala "Valencia" 2,
--     Mar "Golden Delicious" False,
--     Mar "Golden" False,
--     Mar "Golden" True]
-- --a
-- -- e portocala de sicilia
-- ePDS :: Fruct -> Bool
-- ePDS (Portocala s n) = s `elem` ["Tarocco", "Moro", "Sanguinello"]
-- --b
-- --calculeaza numarul de felii din portoclele de sicilia
-- nFS :: [Fruct] -> Int
-- nFS ls = sum [n | Portocala s n <- ls, ePDS(Portocala s n)]
-- --c
-- -- calculeaza numarul de mere cu viermi
-- nMV :: [Fruct] -> Int
-- nMV ls = sum[1| Mar s b <-ls, b]

--2
type NumeA = String
type Rasa = String
data Animal = Pisica NumeA | Caine NumeA Rasa
    deriving Show
--a
vorbeste :: Animal -> String
vorbeste (Pisica _) = "Meow!"
vorbeste (Caine _ r) = "Woof!"
--b
rasa::Animal -> Maybe String
rasa (Caine _ r) = Just r
rasa (Pisica _ ) = Nothing

--3
data Linie = L [Int]
    deriving Show
data Matrice = M [Linie]
    deriving Show
--a
--vf daca suma tuturor elementelor de pe fiecare linie e n
verifica:: Matrice -> Int -> Bool
verifica (M mat) n = foldr (&&) True [sum lin==n|(L lin)<-mat]

--b
--verifica daca elementele unei linii sunt pozitive
positive:: Linie -> Bool
positive (L l) = filter (>0) l == l

--verifica daca toate liniile de lungime n sunt pozitive
doarPozN:: Matrice -> Int -> Bool
doarPozN (M mat) n = foldr (&&) True (map positive liniiN)
    where liniiN=filter(\(L l)->length l==n) mat

--c
--verifica daca toate liniile din matrice au aceeasi lungime
corect:: Matrice -> Bool
corect (M []) = True
corect (M [x]) = True
corect (M(L l1:(L l2) : list)) = 
    length l1==length l2 && corect (M(L l2 : list))