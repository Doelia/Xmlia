#!/usr/bin/python

import re

sortie = open('manuel-de-reference.tex','w')
refman = open('latex/refman.tex','r')
lines = refman.readlines()

inputline = re.compile(".*input{(.*)")
chapterline = re.compile(".*chapter{(.*)")

found = False

for line in lines:
	result = inputline.match(line)
	if (result):
		line = "\\input{latex/" + result.group(1) + "\n"
		sortie.write(line)
	result = chapterline.match(line)
	if (result):
		sortie.write(line)

refman.close()
sortie.close()
