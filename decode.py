#!/usr/bin/env python

# Decodes passwords as stored in
# USERDIR\Application Data\SQLyog\sqlyog.ini
#
# @author Gregor Kralik <g.kralik@gmail.com>
# @license GPL-2.0

import sys
from base64 import b64decode

def usage():
    print("usage: {0} encrypted_password".format(sys.argv[0]))
    sys.exit(1)

def decode_password(encoded):
    tmp = bytearray(b64decode(encoded))

    for i in range(len(tmp)):
        tmp[i] = rotate_left(tmp[i], 8)

    return tmp.decode('utf-8')

# https://gist.github.com/cincodenada/6557582
def rotate_left(num, bits):
    bit = num & (1 << (bits-1))
    num <<= 1
    if(bit):
        num |= 1
    num &= (2**bits-1)

    return num

if __name__ == '__main__':
    if len(sys.argv) != 2:
        usage()

    print(decode_password(sys.argv[1]))
    sys.exit(0)
