import Data.Monoid

--foldMap :: (Monoid m, Foldable f) => (a -> m) -> f a -> m
----          ^^^^^^^^^^^^^^^^^^^^     ^^^^^^^     ^^^
----          |- We've seen this       |           |
----                                   |           |- A 'Set' of a's which can be collapse into a single value
----                                   |- A function to convert a's into a monoid


elem1 :: (Foldable t, Eq a) => a -> t a -> Bool
elem1 x tx = getAny(foldMap (\y -> Any(y==x)) (tx))

null1 :: (Foldable t) => t a -> Bool
null1 tx = getAll (foldMap (\x -> All False) tx)

length1 :: (Foldable t) => t a -> Int
length1 tx = getSum (foldMap (\x -> Sum 1) tx)

toList1 :: (Foldable t) => t a -> [a]
toList1 tx = foldMap(:[]) tx

fold1 :: (Foldable t, Monoid m) => t m -> m
fold1 = foldMap id -- Hint: folosiți foldMap

data Constant a b = Constant b
instance Foldable (Constant a) where
    foldMap f (Constant b) = f b

data Two a b = Two a b
instance Foldable (Two a) where
    foldMap f (Two a b) = f b

data Three a b c = Three a b c
instance Foldable (Three a b ) where
    foldMap f (Three a b c) = f c

data Three' a b = Three' a b b
instance Foldable (Three' a) where
    foldMap f(Three' x1 x2 x3 )= f x2 <> f x3

data Four' a b = Four' a b b b
instance Foldable (Four' a) where
    foldMap f(Four' x1 x2 x3 x4)= f x2 <> f x3 <> f x4

data GoatLord a = NoGoat | OneGoat a | MoreGoats (GoatLord a) (GoatLord a) (GoatLord a)
instance Foldable GoatLord where
    foldMap f NoGoat = mempty
    foldMap f (OneGoat x) = f x
    foldMap f (MoreGoats x1 x2 x3) = foldMap f x1 <> foldMap f x2 <> foldMap f x3