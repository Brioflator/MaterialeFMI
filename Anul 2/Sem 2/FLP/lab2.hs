import Control.Applicative
import Data.Char

newtype Parser a = Parser { apply :: String -> [(a, String)] }

satisfy :: (Char -> Bool) -> Parser Char
satisfy p = Parser go
  where
    go [] = []   -- imposibil de parsat șirul vid
    go (c:input)
      | p c = [(c, input)]   -- dacă predicatul ține, întoarce c și restul șirului de intrare
      | otherwise = []       -- în caz contrar, imposibil de parsat

--- | Acceptă orice caracter
anychar :: Parser Char
anychar = satisfy (const True)

--- | acceptă doar caracterul dat ca argument
char :: Char -> Parser Char
char s = satisfy (== s)

--- | acceptă o cifră
digit :: Parser Char
digit = satisfy isDigit

--- | acceptă un spațiu (sau tab, sau sfârșit de linie -- vedeți funcția din Data.Char )
space :: Parser Char
space = satisfy isSpace

--- | succes doar dacă am șirul de intrare este vid 
endOfInput :: Parser ()
endOfInput  = Parser go
  where
    go "" = [((), "")]
    go _ = []

instance Functor Parser where
    fmap f pa = Parser (\input -> [(f a, rest) | (a, rest) <- apply pa input])

instance Applicative Parser where
    pure a = Parser (\input -> [(a, input)])
    pf <*> pa = Parser (\input -> [(f a, resta) | (f, restf) <- apply pf input, (a, resta) <- apply pa restf])

parse :: Parser a -> String -> Either String a
parse p s= go (apply (p<* endOfInput) s)
        where 
            go [(x, _)] = Right x
            go _ = Left "Parse error"

instance Monad Parser where
    pa >>= k = Parser (\input -> [(b, restb) | (a, resta) <- apply pa input, (b, restb) <- apply (k a) resta])

cifraSemn :: Parser Int
-- cifraSemn = do
--     semn <- satisfy (`elem` "+-")
--     ch_cf <- digit
--     let cifra = digitToInt ch_cf
--     case semn of 
--         '+' -> return cifra
--         '-' -> return (-cifra)
cifraSemn = pure (\x y -> if x == '+' then y else -y) <*> (satisfy (`elem` "+-")) <*> (digitToInt <$> digit)

string :: String -> Parser String
string "" = return []
string (h:t) = do
    x <- char h
    xs <- string t
    return (x:xs)

instance Alternative Parser where
    empty = Parser (const [])
    p <|> p' = Parser (\input -> apply p input ++ apply p' input)

stringToInt:: String -> Int
stringToInt = foldl (\acc x -> acc * 10 + digitToInt x) 0

naiveNatural :: Parser [Char]
naiveNatural = pure(:)<*>digit<*>naiveNatural <|> pure (:[]) <*> digit

-- | Elimină zero sau mai multe apariții ale lui `space`
whiteSpace :: Parser ()
whiteSpace = do 
    _ <- many space
    return ()

-- | parses a natural number (one or more digits)

nat :: Parser Int
--nat = stringToInt <$> some digit
nat = stringToInt <$> naiveNatural

-- | aplică un parser, și elimină spațiile de după
lexeme :: Parser a -> Parser a
lexeme p = p <* whiteSpace

-- | parses a natural number and skips the space after it
natural :: Parser Int
natural = nat <* whiteSpace

-- | Parses the string and skips whiteSpace after it
symbol :: String -> Parser String
symbol s = string s<* whiteSpace

-- | Parses the string, skips whiteSpace, returns unit
reserved :: String -> Parser ()
reserved s = symbol s *> whiteSpace

-- | parsează virgulă, eliminând spațiile de după
comma :: Parser ()
comma = reserved ";" <* whiteSpace

-- | parsează argumentul intre paranteze rotunde
--   elimină spațiile de după paranteze
parens :: Parser a -> Parser a
parens p = reserved "(" *> p <* reserved ")"

-- | parsează argumentul intre paranteze pătrate
--   elimină spațiile de după paranteze
brackets :: Parser a -> Parser a
brackets p = reserved "[" *> p <* reserved "]"

-- | una sau mai multe instanțe, separate de virgulă,
--   cu eliminarea spațiilor de după fiecare virgulă
--   intoarce lista obiectelor parsate
commaSep1 :: Parser a -> Parser [a]
--commaSep1 p = (:) <$> p <*> many (comma *> p) 
commaSep1 p = do 
    x <- p
    xs <- many (comma *> p)
    return (x:xs)

-- | zero sau mai multe instanțe, separate de virgulă,
--   cu eliminarea spațiilor de după fiecare virgulă
--   intoarce lista obiectelor parsate
commaSep :: Parser a -> Parser [a]
commaSep p = commaSep1 p <|> pure []

-- | date fiind parsere pentru prima literă si pentru felul literelor următoare
--   scrieți un parser pentru un identificator
ident :: Parser Char -> Parser Char -> Parser String
ident identStart identLetter = do 
    x <- identStart
    xs <- many identLetter
    return (x:xs)

-- | ca mai sus, dar elimină spatiile de după
identifier :: Parser Char -> Parser Char -> Parser String
identifier start letter = lexeme (ident start letter)
