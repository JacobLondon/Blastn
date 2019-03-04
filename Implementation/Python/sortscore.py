'''
Given an unorganized list of (DNA, score) tuples
Sort it by score
Created by Alex Chan
March 4, 2019

References:
https://interactivepython.org/courselib/static/pythonds/SortSearch/TheQuickSort.html
'''
import random
from sequence import generate_words, create_sequence

def create_sample_data():
    words = []
    for i in range(10):
        word = generate_words(1,11)
        rng = random.randint(1,101)
        words.append((word, rng))
    return words

def quick_sort(alist):
   quick_sort_helper(alist,0,len(alist)-1)

def quick_sort_helper(alist,first,last):
   if first<last:

       splitpoint = partition(alist,first,last)

       quick_sort_helper(alist,first,splitpoint-1)
       quick_sort_helper(alist,splitpoint+1,last)


def partition(alist,first,last):
   pivotvalue = alist[first][1]

   leftmark = (first+1)
   rightmark = last

   done = False
   while not done:

       while leftmark <= rightmark and alist[leftmark][1] <= pivotvalue:
           leftmark = leftmark + 1

       while alist[rightmark][1] >= pivotvalue and rightmark >= leftmark:
           rightmark = rightmark -1

       if rightmark < leftmark:
           done = True
       else:
           temp = alist[leftmark]
           alist[leftmark] = alist[rightmark]
           alist[rightmark] = temp

   temp = alist[first]
   alist[first] = alist[rightmark]
   alist[rightmark] = temp


   return rightmark

def main():
    alist = create_sample_data()
    print(alist)
    quick_sort(alist)
    print(alist)

if __name__ == '__main__':
    main()
