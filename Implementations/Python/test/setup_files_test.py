import sys, os
sys.path.append(os.path.abspath('../'))

from util import setup_data

def main():
    path = '../util/SRR7236689--ARG830.fa'
    #path = 'Gn-SRR7236689_contigs.fasta'
    setup_data(path)

if __name__ == '__main__':
    main()
