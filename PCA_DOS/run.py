#!/usr/bin/python


import sys
import time
import datetime
import numpy as np
from pca import pca_fnc
import math

def load_data(fNameIn):

	data = []
	try:
		# Open the DOS file
		f = open(fNameIn, 'r')
		lineNr = 0

		# Read lines one by one
		for line in f:
			# Keep track of line number
			lineNr += 1

			# Split into columns
			cols = line.split()

			if (len(cols) != 3): continue

			else:
				data.append([float(cols[0]),float(cols[1]),float(cols[2])])
							
	# Throw error if anything goes wrong.
	except:
		print('could not read file "%s"' % fNameIn)

	f.close()

	# Return the data
	return data

def write_data(dataOut,fNameOut):

	try:
		f = open(fNameOut,'w')
	
		for i in range(len(dataOut[:,0])):
			#print dataOut[i,0]
			f.write('%20.8f %20.8f\n' %(dataOut[i,0],dataOut[i,1]))

	except:
		print('could not write file "%s"' % fNameOut)

	f.close()


def sample(maxE,minE,N_E,maxDOS,minDOS,N_DOS,spin,input):

	interval_E = float(maxE-minE)/float(N_E)
	interval_DOS = float(maxDOS-minDOS)/float(N_DOS)

	output = [0]*(N_E*N_DOS)

	#print len(input)	

	for k in range(0,len(input)):

		idx1 = int(math.floor((input[k][0]-minE)/interval_E))
		idx2 = int(math.floor((input[k][spin]-minDOS)/interval_DOS))

		if idx1 >= 0 and idx1 < N_E:
			if idx2 >= 0 and idx2 < N_DOS:
				output[idx1*N_DOS+idx2] = 1


	return output

def desample(maxE,minE,N_E,maxDOS,minDOS,N_DOS,input):

	interval_E = float(maxE-minE)/float(N_E)
	interval_DOS = float(maxDOS-minDOS)/float(N_DOS)

	temp_data = [[0.0]*N_DOS]*N_E
	temp_data = np.array(temp_data)

	for i in range(0,len(input)):

		temp_data[int(math.floor(float(i)/float(N_DOS))),int(i % N_DOS)] = input[i-1]


	output = [[0.0]*2]*(N_E)
	output = np.array(output)
	

	for i in range(0,N_E):
		for j in range(0,N_DOS):
	
			rangeA = float(i)*interval_E + minE
			rangeB = float(i+1)*interval_E + minE
		
			output[i,0] = rangeA			
	
			rangeC = float(j)*interval_DOS + minDOS
			rangeD = float(j+1)*interval_DOS + minDOS

			if temp_data[i,j] > 0:
				output[i,1] = rangeC


	return output

fNameIn = ''
fNameOut = ''

maxE = 10.0
minE = -5.0
N_E = 70

maxDOS = 10.0
minDOS = 0.0
N_DOS = 70


if __name__ == "__main__":


	if (len(sys.argv) != 4):
		print('Usage: ./run.py DOS_FILE1 DOS_FILE2 DOS_FILE3')
		
	else:
		#fNameIn = sys.argv[1] 	
		#data = load_data(fNameIn)
		data1 = load_data(sys.argv[1])
		#data2 = load_data('DOS_Cu75Ni25.dat')
		data3 = load_data(sys.argv[2])
		#data4 = load_data('DOS_Cu25Ni75.dat')
		data5 = load_data(sys.argv[3])
		
		spin = 1 # 1: Up-spin 2: Down-spin

		arr1 = sample(maxE,minE,N_E,maxDOS,minDOS,N_DOS,spin,data1)
		#arr2 = sample(maxE,minE,N_E,maxDOS,minDOS,N_DOS,spin,data2)
		arr3 = sample(maxE,minE,N_E,maxDOS,minDOS,N_DOS,spin,data3)
		#arr4 = sample(maxE,minE,N_E,maxDOS,minDOS,N_DOS,spin,data4)
		arr5 = sample(maxE,minE,N_E,maxDOS,minDOS,N_DOS,spin,data5)

		arrNew = np.c_[arr1, arr3, arr5]

		signals, PC, V = pca_fnc(arrNew)

		print V

		k = 2
		new_x = 0.21 
	
		## signals[PC index, data index]
	
		#DOSout1 = desample(maxE,minE,N_E,maxDOS,minDOS,N_DOS,np.dot(PC[:,0:k-1],signals[0:k-1,0]))
		#DOSout2 = desample(maxE,minE,N_E,maxDOS,minDOS,N_DOS,np.dot(PC[:,0:k-1],signals[0:k-1,1]))
		#DOSout3 = desample(maxE,minE,N_E,maxDOS,minDOS,N_DOS,np.dot(PC[:,0:k-1],signals[0:k-1,2]))
		#DOSout4 = desample(maxE,minE,N_E,maxDOS,minDOS,N_DOS,np.dot(PC[:,0:k-1],signals[0:k-1,3]))
		#DOSout5 = desample(maxE,minE,N_E,maxDOS,minDOS,N_DOS,np.dot(PC[:,0:k-1],signals[0:k-1,4]))

		#print DOSout1
	
		print signals[0,:]
		print signals[1,:]
		print signals[2,:]
		#print signals[3,:]

		#n_e = [0, 0.21, 0.33, 0.71, 1]
		n_e = [0, 0.33, 1]

	
		x = n_e
		xx = [ float(i)*0.01 for i in range(101) ]

		new_signals = [0]*k

		for i in range(k):
			y = signals[i,:]

			## Interpolation
			yy = np.interp(xx, x, y)  # linear

			new_signals[i] = yy[xx.index(new_x)]	
	
		#print new_signals

		temp_arr = np.array(new_signals)

	
		DOSout1 = desample(maxE,minE,N_E,maxDOS,minDOS,N_DOS,np.dot(PC[:,0:k],temp_arr.T))



		write_data(DOSout1,'DOSCAR.new')		

