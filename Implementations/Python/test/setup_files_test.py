import sys, os
sys.path.append(os.path.abspath('../'))

from util import sequence

def main():
    path = '../../../Data/SRR7236689--ARG830.fa'
    #path = 'Gn-SRR7236689_contigs.fasta'
    sequence(path)

if __name__ == '__main__':
    main()
