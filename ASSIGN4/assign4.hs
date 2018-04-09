import System.Environment
import Data.List
import Data.Foldable
import Data.Char

assign4 filename word = do
	file <- readFile filename
	let list1 = filter (/= '\r') file
	let list = lines list1
	let xs = map (anagram word) list
	let list2 = filter (not . null) xs
	return list2

anagram a b
	| (sort (map toLower a)) == (sort (map toLower b)) = (map toLower b)
	| (sort (map toLower a)) /= (sort (map toLower b)) = ""
