import System.Win32 (xBUTTON1, aCCESS_SYSTEM_SECURITY)
data Expr = Const Int -- integer constant
          | Expr :+: Expr -- addition
          | Expr :*: Expr -- multiplication
           deriving Eq

-- instantiati clasa Show pt tipul de date Expr a afisa mai simplu expressile 
instance Show Expr where
    show(Const x) = show x
    show(a :+:b) = "("++show a ++"+"++ show b++ ")"
    show(a :*:b) = "("++ show a ++"*"++ show b++ ")"

data Operation = Add | Mult deriving (Eq, Show)

data Tree = Lf Int -- leaf
          | Node Operation Tree Tree -- branch
           deriving (Eq, Show)

--evalueaza o expresie si determina valoarea acesteia
evalExp :: Expr -> Int
evalExp (Const a) = a
evalExp ( a :+: b) = evalExp( a) + evalExp( b)
evalExp ( a :*: b) = evalExp( a) * evalExp( b)

exp1 = ((Const 2 :*: Const 3) :+: (Const 0 :*: Const 5))
exp2 = (Const 2 :*: (Const 3 :+: Const 4))
exp3 = (Const 4 :+: (Const 3 :*: Const 3))
exp4 = (((Const 1 :*: Const 2) :*: (Const 3 :+: Const 1)) :*: Const 2)
test11 = evalExp exp1 == 6
test12 = evalExp exp2 == 14
test13 = evalExp exp3 == 13
test14 = evalExp exp4 == 16

--evalueaza o expresie modelata sub forma de arbore si det valoarea acesteia
evalArb :: Tree -> Int
evalArb (Lf x) = x
evalArb (Node Add a b) = evalArb(a) + evalArb(b)
evalArb (Node Mult a b) = evalArb(a) * evalArb(b)

arb1 = Node Add (Node Mult (Lf 2) (Lf 3)) (Node Mult (Lf 0)(Lf 5))
arb2 = Node Mult (Lf 2) (Node Add (Lf 3)(Lf 4))
arb3 = Node Add (Lf 4) (Node Mult (Lf 3)(Lf 3))
arb4 = Node Mult (Node Mult (Node Mult (Lf 1) (Lf 2)) (Node Add (Lf 3)(Lf 1))) (Lf 2)

test21 = evalArb arb1 == 6
test22 = evalArb arb2 == 14
test23 = evalArb arb3 == 13
test24 = evalArb arb4 == 16

--transforma o expresie in arborele corespunzator
expToArb :: Expr -> Tree
expToArb (Const a) = Lf a
expToArb ( a :+: b) = Node Add (expToArb a) (expToArb b)
expToArb ( a :*: b) = Node Mult (expToArb a) (expToArb b)

class Collection c where
  empty :: c key value
  singleton :: key -> value -> c key value
  insert :: Ord key => key -> value -> c key value -> c key value
  clookup :: Ord key => key -> c key value -> Maybe value
  delete :: Ord key => key -> c key value -> c key value
  keys :: c key value -> [key]
  values :: c key value -> [value]
  toList :: c key value -> [(key, value)]
  fromList :: Ord key => [(key, value)] -> c key value
  keys c = [fst p | p <- toList c]
  values c = [snd p | p <- toList c]
  fromList [] = empty
  fromList ((k, v) : l) = insert k v (fromList l)

--tipul litselor de perechi de forma key, value
newtype PairList k v = PairList {getPairList :: [(k, v)]}

--PairList devine instanta a clasei Collection
instance Collection PairList where 
    empty :: PairList key value
    empty= PairList []
    singleton :: key -> value -> PairList key value
    singleton k v= PairList[(k,v)]
    insert :: Ord key => key -> value -> PairList key value -> PairList key value
    insert k v (PairList l)= PairList((k,v):(filter(\x->fst x/=k) l))
    clookup :: Ord key => key -> PairList key value -> Maybe value
    clookup k (PairList l) = lookup k l
    delete :: Ord key => key -> PairList key value -> PairList key value
    delete k (PairList l) = PairList(filter(\x->fst x/=k) l)
    toList :: PairList key value -> [(key, value)]
    toList (PairList l) = l
    -- toList = getPairList

data SearchTree key value
  = Empty
  | BNode
      (SearchTree key value) -- elemente cu cheia mai mica
      key -- cheia elementului
      (Maybe value) -- valoarea elementului
      (SearchTree key value) -- elemente cu cheia mai mare