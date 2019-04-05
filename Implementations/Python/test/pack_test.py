import sys, os
sys.path.append(os.path.abspath('../'))

from util import pack_sequence, unpack_sequence, pack_byte, unpack_byte

def test_seq_packing():
    seq = 'ATATATATGTCACGTCA'
    print('Sequence:\n', seq, sep='')
    packed = pack_sequence(seq)
    print('Packed:\n', packed, sep='')
    unpacked = unpack_sequence(packed)
    print('Unpacked:\n', unpacked, sep='')

def test_byte_packing():
    seq = 'AAAA'
    packed = pack_byte(seq)
    unpacked = unpack_byte(packed)

    print(seq)
    print(packed)
    print(unpacked)

if __name__ == '__main__':
    test_seq_packing()
    #test_byte_packing()