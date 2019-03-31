
import os, tqdm

def sequence(path, sep='>'):
    in_file = open(path, 'r')

    # make a directory to output the files to
    path = path[0:path.index('.')]

    print(f'Creating output directory: {path}')

    try:
        os.mkdir(path)
    except OSError as e:
        print(e)
        response = input('Continue anyway? y/n ')
        if response.lower() != 'y':
            return

    print('Building file list')

    # read the lines into files
    for line in tqdm.tqdm(in_file.readlines()):
        if line[0] == sep:
            out_file = open(path + '/' + line[1:line.index('\n')] + '.txt', 'w')
            continue
        
        out_file.write(line)

if __name__ == '__main__':
    f_in = 'SRR7236689--ARG830.fa'
    #f_in = 'Gn-SRR7236689_contigs.fasta'
    sequence(f_in)
