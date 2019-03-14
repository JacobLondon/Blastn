'''
Created by Alex Chan
March 4, 2019

Given an unorganized list of (DNA, score) tuples
Sort it by score

References:
https://interactivepython.org/courselib/static/pythonds/SortSearch/TheQuickSort.html
'''
import random

from .sequence import generate_words, create_sequence

def quicksort(match_list):
   quick_sort_helper(match_list, first=0, last=len(match_list) - 1)

def quick_sort_helper(match_list, first, last):
   if first < last:

       splitpoint = partition(match_list, first, last)

       quick_sort_helper(match_list, first, splitpoint - 1)
       quick_sort_helper(match_list, splitpoint + 1, last)

def partition(match_list, first, last):
    pivotvalue = match_list[first][1]

    leftmark = (first + 1)
    rightmark = last

    done = False
    while not done:

       while leftmark <= rightmark and match_list[leftmark][1] <= pivotvalue:
           leftmark = leftmark + 1

       while match_list[rightmark][1] >= pivotvalue and rightmark >= leftmark:
           rightmark = rightmark - 1

       if rightmark < leftmark:
           done = True
       else:
           """temp = match_list[leftmark]
           match_list[leftmark] = match_list[rightmark]
           match_list[rightmark] = temp"""
           match_list[leftmark], match_list[rightmark] = match_list[rightmark], match_list[leftmark]

    """temp = match_list[first]
    match_list[first] = match_list[rightmark]
    match_list[rightmark] = temp"""
    match_list[first], match_list[rightmark] = match_list[rightmark], match_list[first]

    return rightmark

def create_sample_data():
    words = []
    for _ in range(10):
        word = generate_words(1, 11)
        rng = random.randint(1, 101)
        words.append((word, rng))
    return words

def main():
    match_list = create_sample_data()
    print(match_list)
    quicksort(match_list)
    print(match_list)

if __name__ == '__main__':
    main()
