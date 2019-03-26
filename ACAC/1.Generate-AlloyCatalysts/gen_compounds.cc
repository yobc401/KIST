#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

#define MAX_COUNT 10000


using namespace std;

typedef struct {
	string name;
	float rad;
} ATOM;

typedef struct {
	string A;
	string B; 
	float a_param;
	float b_param;
	float c_param;
	int crystal_index;
} COMPOUND;

float map_atomic_radii ( string atom_str, ATOM *atomic_info,  float atomic_info_len ) {
    string temp_i = atom_str;
    for ( int i = 0; i < atomic_info_len; i++ ) {
        string temp_j = atomic_info[i].name;

        //if ( issame(atom_str, atomic_char[j]) ) {
        if ( temp_i.compare(temp_j) == 0 ) {

            return atomic_info[i].rad;

        }

    }

    return 0;

}

float max_float ( float a, float b ) {
	if ( a >= b )
		return a;

	else
		return b;
}
float mean_float ( float a, float b ){
	return (float)((a+b)/(2.0));
}



int main(int argc, char *argv[])
{
  	// Check argument
  	if (argc < 3) { 
    		std::cerr << "Usage: " << argv[0] << " ATOM_INFO. TOTAL_AB " << endl;

   	 	return 1;
  	}



	// Set variables
	ATOM atomic_info[MAX_COUNT];
	unsigned int atomic_info_len = 0;

	string atomic_A[MAX_COUNT];
	string atomic_B[MAX_COUNT];
	string atomic_X[MAX_COUNT];
	unsigned int num_AB;


	unsigned int num_C;

	int ii = 0;
	int flag = 0;
	float rad_A, rad_B;
	float rad_max;


  	istringstream ss;
	string line, col1, col2, col3, col4, col5, col6, col7, col8, col9;

	bool read_status;
  	int num_line;

	// Read all atoms information
	ifstream ATOMINFO(argv[1]);
	read_status = true;
	num_line = 0;
	if ( ATOMINFO.is_open() ) {
		while ((read_status=getline(ATOMINFO,line))==true){
			num_line++;
			if ( num_line > 1 ) {
				ss.str (line);
				ss >> col1 >> col2 >> col3 >> col4 >> col5 >> col6 >> col7 >> col8 >> col9;
				ss.clear();
	
				atomic_info[atoi(col1.c_str())].name = col2;
				atomic_info[atoi(col1.c_str())].rad = atof(col5.c_str())*0.01;
				atomic_info_len++;
			}		
		}
	}


	// Read all atoms in SELECT_AB
	ifstream SELECT_AB(argv[2]);
	read_status = true;
	num_line = 0;
	if ( SELECT_AB.is_open() ) {
		while ((read_status=getline(SELECT_AB,line))==true){
			num_line++;
			if ( num_line > 0 ) {
				ss.str (line);
				ss >> col1 >> col2 >> col3;
				ss.clear();
				atomic_A[num_line-1] = col1;
				atomic_B[num_line-1] = col2;
				atomic_X[num_line-1] = col3;
			}		
		}
	}
	num_AB = num_line;
	printf("The number of elements in AB: %d\n",num_AB);

	COMPOUND compounds[num_AB];

	ii = 0;
	// Write output of all compounds
	FILE *OUT_COMPOUNDS = fopen("COMPOUNDS_LIST","w");
	for ( int i = 0; i < num_AB; i++ ) {


				rad_A = map_atomic_radii(atomic_A[i],atomic_info,atomic_info_len);
				rad_B = map_atomic_radii(atomic_B[i],atomic_info,atomic_info_len);

				rad_max = max_float(rad_A, rad_B);

				compounds[i].A = atomic_A[i];
				compounds[i].B = atomic_B[i];

				if ( atomic_X[i].compare("FCC") == 0 ) {
					compounds[i].a_param = 4.0*rad_max/sqrt(2.0);
					compounds[i].b_param = 4.0*rad_max/sqrt(2.0);
					compounds[i].c_param = 4.0*rad_max/sqrt(2.0);
					compounds[i].crystal_index = 1;
				}
				
				if ( atomic_X[i].compare("CsCl") == 0 ) {
					compounds[i].a_param = 2.0*(rad_A+rad_B)/sqrt(3.0);
					compounds[i].b_param = 2.0*(rad_A+rad_B)/sqrt(3.0);
					compounds[i].c_param = 2.0*(rad_A+rad_B)/sqrt(3.0);
;
					compounds[i].crystal_index = 2;
				}
					
				if ( atomic_X[i].compare("NaCl") == 0 ) {
					compounds[i].a_param = 2.0*(rad_A+rad_B);
					compounds[i].b_param = 2.0*(rad_A+rad_B);
					compounds[i].c_param = 2.0*(rad_A+rad_B);
					compounds[i].crystal_index = 3;
				}

				if ( atomic_X[i].compare("Wurt") == 0 ) {
					compounds[i].a_param = (rad_A+rad_B); 
					compounds[i].b_param = (rad_A+rad_B); 
					compounds[i].c_param = 1.5*(rad_A+rad_B); 
					compounds[i].crystal_index = 4;
				}

				if ( atomic_X[i].compare("Zinc") == 0 ) {
					compounds[i].a_param = 4.0*rad_max/sqrt(2.0);
					compounds[i].b_param = 4.0*rad_max/sqrt(2.0);
					compounds[i].c_param = 4.0*rad_max/sqrt(2.0);
					compounds[i].crystal_index = 5;
				}

				if ( atomic_X[i].compare("HCP") == 0 ) {
					compounds[i].a_param = 4.0*rad_max/sqrt(2.0);
					compounds[i].b_param = 4.0*rad_max/sqrt(2.0);
					compounds[i].c_param = 4.0*rad_max/sqrt(2.0);
					compounds[i].crystal_index = 6;
				}


				if ( atomic_X[i].compare("B33") == 0 ) {
					compounds[i].a_param = 2.0*(rad_A+rad_B);
					compounds[i].b_param = 4.0*(rad_A+rad_B);
					compounds[i].c_param = 2.0*(rad_A+rad_B);
					compounds[i].crystal_index = 7;
				}
				
				if ( atomic_X[i].compare("B19") == 0 ) {
					compounds[i].a_param = 2.0*(rad_A+rad_B);
					compounds[i].b_param = 4.0*rad_max;
					compounds[i].c_param = 4.0*rad_max;
					compounds[i].crystal_index = 8;
				}
					
				if ( atomic_X[i].compare("B11") == 0 ) {
					compounds[i].a_param = 2.0*rad_A;
					compounds[i].b_param = 2.0*rad_B;
					compounds[i].c_param = 3.0*(rad_A+rad_B);
					compounds[i].crystal_index = 9;
				}

				if ( atomic_X[i].compare("B27") == 0 ) {
					compounds[i].a_param = 2.0*(rad_A+rad_B); 
					compounds[i].b_param = 4.0*(rad_A+rad_B); 
					compounds[i].c_param = 6.0*(rad_A+rad_B); 
					compounds[i].crystal_index = 10;
				}


				if ( atomic_X[i].compare("L11") == 0 ) {
					compounds[i].a_param = 2.0*(rad_A+rad_B);
					compounds[i].b_param = 2.0*(rad_A+rad_B);
					compounds[i].c_param = 6.0*(rad_A+rad_B);
					compounds[i].crystal_index = 11;
				}


				fprintf(OUT_COMPOUNDS,"%5s%5s%5s%5d%8.3f%8.3f%8.3f\n", compounds[i].A.c_str(),  \
										compounds[i].B.c_str(), \
										atomic_X[i].c_str(), \
										compounds[i].crystal_index, \
										compounds[i].a_param, \
										compounds[i].b_param, \
										compounds[i].c_param \
										);


	

	}






	fclose(OUT_COMPOUNDS);









	return 0;

}
