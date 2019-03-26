#!/usr/bin/python
#
# Python script in terms of Principal Components Analysis (PCA)
# 
#
# Copyright (C) 2017  Byungchul Yeo
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#                              Written by Byungchul Yeo
#                              Version 11-Apr-2017


import numpy as N
import numpy as np
import numpy.matlib
from numpy import linalg as LA



def pca_fnc(data):

	dataSize = N.shape(data)


	#for i in range(0,100):
	#	print(' %.10f %.10f' %(data.item(i,0), data.item(i,1)))


	#print '--------------'


	# Subtract off the mean for each dimension
	mn = data.mean(axis=1)
	mn = np.array([mn])
	mn = mn.T
	#print mn 

	mn_rep = np.matlib.repmat(mn,1,dataSize[1])
	
	#for i in range(0,100):
	#	print(' %.10f %.10f' %(mn_rep.item(i,0), mn_rep.item(i,1)))


	#print '--------------'


	a = numpy.matrix(data)
	b = numpy.matrix(mn_rep)

	data = a - b

	#dataSize2 = N.shape(data)

	#print dataSize2

	#for i in range(0,10):
	#	print(' %.10f' %data.item(i))


	#print '--------------'


	# Calculate the covariance matrix
	covariance = 1.0/float(dataSize[1]-1)*data*data.T
	
	#print N.shape(covariance)

	# Find the eigenvectors and eigenvalues
	v, PC = LA.eig(covariance)

	#for i in range(0,10):
	#	print(' %.10f' %covariance[i,i])

	#print '--------------'

	#print N.shape(PC)
	#print N.shape(v)

	# Extract diagonal of matrix as vector
	#v = np.diag(v)

	# Sort the variances in decreasing order
	rindices = (-v).argsort()[:]

	#for i in range(0,10):
	#	print(' %.20f' %v[i])

	#print v
	v = v[rindices]

	#print N.shape(PC)
	#print len(rindices)

	PC = PC[:,rindices]
	PC = PC.real
	#print '-----------------'

	#for i in range(1115,1130):
	#	print PC[i,:]

	#PC = PC[rindices]
	#print PC
	#print v 

	# Project the original data set
	PC = np.array(PC)
	data = np.array(data.real)

	#print PC.T
	#print data

	#print N.shape(PC)
	#print N.shape(data)

	signals = np.dot(PC.T,data)

	#print N.shape(signals)

	return signals, PC, v
	

