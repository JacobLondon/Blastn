# Blastn

## Input Arguments
* python3 main.py
  * runs Blastn with no extra timing tools
* python3 main.py cprofile
  * runs Blastn with cProfile tool
* python3 main.py timeit
  * runs Blastn once and displays the total time
* python3 main.py timeit <times>
  * runs Blastn a given number of times and gives the average

## Current Progress Steps
* Randomly create query and data sequences
* Split query into words of a given length
* WIP: DUST Filtering on the split query
* Turn data sequences into a Python dictionary
  * Get all words of query length in the data sequence
  * Each word (key) is mapped to a list of indices it appears at in the data sequence (value)
* Get all permutations of the query words
* WIP: DUST Filtering on those permutations
* Find the intersection of the filtered permutations and data sequence words
* Remove matches not found enough times in the data sequence
* Get all pairs of matches which are close
* WIP: align pairs with Smith-Waterman

## Future
* Search from a database such as Genbank
* Implement faster dataset solution than a Python dictionary
* Research faster/different options than Python itertools' permutations package
* GPU accelerated options
