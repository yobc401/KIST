#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <vector>

#include <sys/types.h>
#include <sys/wait.h>

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>


typedef struct{
	float E_level;
	float DOS_up; 
	float DOS_down;
} DOS_TYPE;

float interp( float x, float x0, float x1, float y0, float y1 ){
    return (y0 + (y1-y0)*(x-x0)/(x1-x0));

}


using namespace std;

int main(int argc, char *argv[]){

  	// Check argument
  	if (argc != 3) { 
    		std::cerr << "Usage: " << argv[0] << " DOSCAR1 DOSCAR2 " << endl;
   	 	return 1;
  	}


	bool read_status = true;
  	int num_line = 0;


//	float E_rangeI, E_rangeF, E_rangeT;

	float E_start1, E_end1, E_start2, E_end2;
	float E_fermi1, E_fermi2;
	int N_dos1, N_dos2;
	
	DOS_TYPE *DOS1;
	DOS_TYPE *DOS2;

	int num_index;
	
  	istringstream ss;
	string line, col1, col2, col3, col4, col5;

	ifstream DOSCAR1(argv[1]);
	if( DOSCAR1.is_open() ) {
		while ((read_status=getline(DOSCAR1,line))==true) {
			num_line++;
			if ( num_line == 6 ) {
				ss.str(line);
				ss >> col1 >> col2 >> col3 >> col4 >> col5;
				ss.clear();

				E_start1 = atof(col1.c_str());
				E_end1 = atof(col2.c_str());
				N_dos1 = atoi(col3.c_str());
				E_fermi1 = atof(col4.c_str());

				DOS1 = new DOS_TYPE [N_dos1];

				num_index = 0; 

			}

			// total information (DOS up-spin, DOS down-spin, ...)
			if ( num_line >= 7 && num_line < ((N_dos1+1)+6) ) {
				ss.str(line);
				ss >> col1 >> col2 >> col3 >> col4;
				ss.clear();
	
				DOS1[num_index].E_level = atof(col1.c_str())-E_fermi1;
				DOS1[num_index].DOS_up = atof(col2.c_str());
				DOS1[num_index].DOS_down = atof(col3.c_str());

				num_index++;

			}

		

		}
	}
	DOSCAR1.close();

	num_line = 0;
	ifstream DOSCAR2(argv[2]);
	if( DOSCAR2.is_open() ) {
		while ((read_status=getline(DOSCAR2,line))==true) {
			num_line++;
			if ( num_line == 6 ) {
				ss.str(line);
				ss >> col1 >> col2 >> col3 >> col4 >> col5;
				ss.clear();

				E_start2 = atof(col1.c_str());
				E_end2 = atof(col2.c_str());
				N_dos2 = atoi(col3.c_str());
				E_fermi2 = atof(col4.c_str());

				DOS2 = new DOS_TYPE [N_dos2];

				num_index = 0; 

			}

			// total information (DOS up-spin, DOS down-spin, ...)
			if ( num_line >= 7 && num_line < ((N_dos2+1)+6) ) {
				ss.str(line);
				ss >> col1 >> col2 >> col3 >> col4;
				ss.clear();
	
				DOS2[num_index].E_level = atof(col1.c_str())-E_fermi2;
				DOS2[num_index].DOS_up = atof(col2.c_str());
				DOS2[num_index].DOS_down = atof(col3.c_str());

				num_index++;

			}

		

		}
	}
	DOSCAR2.close();

	float E_temp;	
	float E_rangeI = -10.0;
	float E_rangeF = 40.0;
	int E_rangeN = 1000;
	float E_rangeT = (float)(E_rangeF-E_rangeI)/((float)(E_rangeN));

	DOS_TYPE *DOS1_range = new DOS_TYPE [E_rangeN];
	DOS_TYPE *DOS2_range = new DOS_TYPE [E_rangeN];

	int indexAfter, indexBefore;

/*
	for ( int i = 0; i < N_dos1; i++ ) {

		printf("%f, %f, %f\n",DOS1[i].E_level,DOS1[i].DOS_up,DOS1[i].DOS_down);


	}
*/

	for ( int i = 0; i < E_rangeN; i++ ) {
		E_temp = E_rangeI + (float)i*E_rangeT;

		if ( E_temp < DOS1[0].E_level || E_temp > DOS1[N_dos1-1].E_level  ) {
			DOS1_range[i].E_level = E_temp;
			DOS1_range[i].DOS_up = 0.0;
			DOS1_range[i].DOS_down = 0.0;

		}
		else {

			for ( int j = 0; j < N_dos1; j++ ){
				if ( DOS1[j].E_level >= E_temp ){
					indexAfter = j+1;
					indexBefore = j;
					break;
				}	

			}

			DOS1_range[i].E_level = E_temp;
			DOS1_range[i].DOS_up = interp(E_temp,DOS1[indexBefore].E_level,DOS1[indexAfter].E_level,DOS1[indexBefore].DOS_up,DOS1[indexAfter].DOS_up);
			DOS1_range[i].DOS_down = interp(E_temp,DOS1[indexBefore].E_level,DOS1[indexAfter].E_level,DOS1[indexBefore].DOS_down,DOS1[indexAfter].DOS_down);
		}

		if ( E_temp < DOS2[0].E_level || E_temp > DOS2[N_dos2-1].E_level ) {
			DOS2_range[i].E_level = E_temp;
			DOS2_range[i].DOS_up = 0.0;
			DOS2_range[i].DOS_down = 0.0;
		}

		else {

			for ( int j = 0; j < N_dos2; j++ ){
				if ( DOS2[j].E_level >= E_temp ){
					indexAfter = j+1;
					indexBefore = j;
					break;
				}		
			}

			DOS2_range[i].E_level = E_temp;
			DOS2_range[i].DOS_up = interp(E_temp,DOS2[indexBefore].E_level,DOS2[indexAfter].E_level,DOS2[indexBefore].DOS_up,DOS2[indexAfter].DOS_up);
			DOS2_range[i].DOS_down = interp(E_temp,DOS2[indexBefore].E_level,DOS2[indexAfter].E_level,DOS2[indexBefore].DOS_down,DOS2[indexAfter].DOS_down);
		}

		//printf("%f, %f, %f\n",DOS1_range[i].E_level,DOS1_range[i].DOS_up,DOS1_range[i].DOS_down);

	}
	
	float d1, t1, g, s;

	float sigma = 3;
	float dt_dos;

	s = 0;
	for ( int i = 0; i < E_rangeN; i++ ) {
		E_temp = E_rangeI + (float)i*E_rangeT;


		d1 = (DOS2_range[i].DOS_up+DOS2_range[i].DOS_down)-(DOS1_range[i].DOS_up+DOS1_range[i].DOS_down);
		//printf("d1 = %f d1^2 = %f\n",d1,d1*d1);	
		d1 = d1*d1;

		t1 = DOS2_range[i].E_level;
		t1 = t1*t1/(2*sigma*sigma);

		g = 1.0*exp(-t1)/(sigma*sqrt(2*M_PI));

		s += d1*g;//*E_rangeT;

	}

	//printf("s = %f\n",s);
	//printf("E-range= %f\n",E_rangeT);

	dt_dos = sqrt(s*E_rangeT);

	printf("DOS 2_1 = %f\n",1000*dt_dos);

	return 0; 
}
