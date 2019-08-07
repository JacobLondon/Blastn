from sys import argv

from util import *

def blastn(query_file, data_file, split_len, minscore, dust_threshold, sw_match, sw_mismatch, sw_gap):
    # format data into a dictionary
    # {name : {word : [indices], word : [indices], ...}}
    formatted_query = prepare_sequence(path=query_file, length=split_len)
    formatted_data  = prepare_sequence(path=data_file, length=split_len)

    # remove low scoring query words
    scored_query = \
        remove_low_sw(data=formatted_query,
                      minscore=minscore,
                      match=sw_match,
                      mismatch=sw_mismatch,
                      gap=sw_gap)
    # dust filter out words below the threshold
    filtered_query = dust(data=scored_query, threshold=dust_threshold)

    # find all exact matches of every filtered_query in formatted_data
    # {dname : {qname : Match(word, dindices, qindices), ...}, ...}
    exact_matches = match(query=filtered_query, data=formatted_data)
    
    if exact_matches is not None:
        for dataset, quers in exact_matches.items():
            print(dataset, ':', sep='')
            for quer, matches in quers.items():
                print('\t', quer, ':', sep='')
                for m in matches:
                    print('\t', m)


"""
input arg example:
-q util/data/query_small.fa -db util/data/data_small.fasta -l 3 -m 5 -dt 2 -ma 2 -mi -1 -g -1
-q util/data/SRR7236689--ARG830.fa -db util/data/Gn-SRR7236689_contigs.fasta -l 11 -m 5 -dt 2 -ma 2 -mi -1 -g -1
"""
if __name__ == '__main__':
    query_file = None
    data_file = None
    split_len = None
    minscore = None
    dust_threshold = None
    sw_match = None
    sw_mismatch = None
    sw_gap = None

    args = iter(argv)
    try:
        for arg in args:
            if arg == '-q':
                query_file = next(args)
            elif arg == '-db':
                data_file = next(args)
            elif arg == '-l':
                split_len = int(next(args))
            elif arg == '-m':
                minscore = int(next(args))
            elif arg == '-dt':
                dust_threshold = int(next(args))
            elif arg == '-ma':
                sw_match = int(next(args))
            elif arg == '-mi':
                sw_mismatch = int(next(args))
            elif arg == '-g':
                sw_gap = int(next(args))
    except:
        print('Failure: invalid argument(s)')
        exit(-1)

    blastn(query_file=query_file,
           data_file=data_file,
           split_len=split_len,
           minscore=minscore,
           dust_threshold=dust_threshold,
           sw_match=sw_match,
           sw_mismatch=sw_mismatch,
           sw_gap=sw_gap)
