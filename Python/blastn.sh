# run the blastn algorithm with settings specified here

TEST=true
# Python 3 binary
PYBIN=python3

if [ "$TEST" = true ]; then
    WORDLEN=4
    
    QUERY=../Data/query_small.fa
    DATABASE=../Data/data_small.fasta
else
    WORDLEN=11

    QUERY=../Data/SRR7236689--ARG830.fa
    DATABASE=../Data/Gn-SRR7236689_contigs.fasta
fi


# dust min score to filter
DUST_THRESHOLD=2
# smith waterman min score to filter
SW_MINSCORE=5
# smith waterman scoring
SW_MATCH=2
SW_MISMATCH=-1
SW_GAP=-1

$PYBIN main.py -q $QUERY -db $DATABASE -l $WORDLEN -m $SW_MINSCORE -dt $DUST_THRESHOLD -ma $SW_MATCH -mi $SW_MISMATCH -g $SW_GAP
