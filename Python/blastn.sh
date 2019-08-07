# run the blastn algorithm with settings specified here
#python main.py -q util/data/query_small.fa -db util/data/data_small.fasta -l 3 -m 5 -dt 2 -ma 2 -mi -1 -g -1
#python main.py -q util/data/SRR7236689--ARG830.fa -db util/data/Gn-SRR7236689_contigs.fasta -l 11 -m 5 -dt 2 -ma 2 -mi -1 -g -1
query=util/data/query_small.fa
database=util/data/data_small.fasta
split_length=3
sw_minscore=5
dust_threshold=2
sw_match_score=2
sw_mismatch_score=-1
sw_gap_score=-1
python3 main.py -q $query -db $database -l $split_length -m $sw_minscore -dt $dust_threshold -ma $sw_match_score -mi $sw_mismatch_score -g $sw_gap_score