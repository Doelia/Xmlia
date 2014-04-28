#!/usr/bin/python

import re
import os

sortie = open('listing.tex','w')
sortie.write("\\chapter{Listing}\n")

c = re.compile(".*\.c$")

files = list()
for file in os.listdir("../"):
	result = c.match(file)
	if result:
		files.append(file)

files.sort()
for file in files:
	sortie.write("\\section{" + file + "}\n")
	
	sortie.write("\\lstinputlisting{../" + file + "}\n")
	'''
	implementation = open("../" + file,'r')
	sortie.write(implementation.read())
	implementation.close()
	
	sortie.write("\\end{lstlisting}\n")
	'''
sortie.close()
