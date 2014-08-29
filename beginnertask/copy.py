#!/usr/bin/python

import sys, os, shutil
if len(sys.argv) < 3:
    print "Usage: copy.py src dest"
    exit()
src = sys.argv[1]
dest = sys.argv[2]
shutil.copy(src, dest)
