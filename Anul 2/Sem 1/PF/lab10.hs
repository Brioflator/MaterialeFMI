import Data.List
import Data.Char
import Data.Either

instance Functor Pair where
    fmap f (Pair x1 x2) = Pair (f x1) (f x2)

instance Functor (Constant  a ) where
    fmap f (Constant x1) = Constant (f x1)

instance Functor (Two a) where
    fmap f (Two x1 x2) = Two x1 (f x2)

instance Functor (Three a b) where
    fmap f (Three x1 x2 x3) = Three x1 x2 (f x3)

instance Functor (Three' a) where 
    fmap f (Three' x1 x2 x3) = Three' x1 (f x2) (f x3)

instance Functor (Four a b c) where
    fmap f (Four x1 x2 x3 x4) = Four x1 x2 x3 (f x4)
    
instance Functor (Four'' a) where
    fmap f (Four'' x1 x2 x3 x4) = Four'' x1 x2 x3 (f x4)

instance Functor (Quant a) where
    fmap f Finance = Finance
    fmap _ (Desk x1) = Desk x1
    fmap f (Bloor x1) = Bloor (f x1)


newtype Identity a = Identity a

data Pair a = Pair a a

data Constant a b = Constant b

data Two a b = Two a b

data Three a b c = Three a b c

data Three' a b = Three' a b b


data Four a b c d = Four a b c d

data Four'' a b = Four'' a a a b

data Quant a b = Finance | Desk a | Bloor b



data LiftItOut f a = LiftItOut (f a)

instance (Functor f) => Functor (LiftItOut f) where
    fmap g (LiftItOut fa) = LiftItOut(fmap g fa)

data Parappa f g a = DaWrappa (f a) (g a)

instance (Functor f, Functor g) => Functor(Parappa f g) where
    fmap h (DaWrappa fa ga ) = DaWrappa (fmap h fa) (fmap h ga)

data IgnoreOne f g a b = IgnoringSomething (f a) (g b)
instance (Functor f, Functor g) => Functor(IgnoreOne f g a) where
    fmap h (IgnoringSomething fa gb ) = IgnoringSomething fa (fmap  h gb)
 
data Notorious g o a t = Notorious (g o) (g a) (g t)
instance (Functor g) => Functor(Notorious g o a) where
    fmap h (Notorious go ga gt) = Notorious go ga (fmap h gt)

data GoatLord a = NoGoat | OneGoat a | MoreGoats (GoatLord a) (GoatLord a) (GoatLord a)
instance Functor GoatLord where
    fmap _ NoGoat = NoGoat
    fmap f (OneGoat a) = OneGoat (f a)
    fmap f (MoreGoats x1 x2 x3) = MoreGoats (fmap f x1) (fmap f x2) (fmap f x3)

data TalkToMe a = Halt | Print String a | Read (String -> a)
instance Functor TalkToMe where
    fmap _ Halt = Halt
    