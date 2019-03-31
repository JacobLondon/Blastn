import sys, os
sys.path.append(os.path.abspath('../'))

from util import sw

def main():
    seq1 = 'ATCGAC'
    seq2 = 'ACCGGC'
    sw(seq1, seq2, printing=True, match=3, mismatch=-1, gap=0)

if __name__ == '__main__':
    main()
