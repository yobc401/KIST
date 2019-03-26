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

#define MAX_COUNT 200


using namespace std;


int main(int argc, char *argv[])
{
  	// Check argument
  	if (argc != 5) { 
    		std::cerr << "Usage: " << argv[0] << " A B INCAR ENCUT " << endl;

   	 	return 1;
  	}

  	istringstream ss;
	string line;



	bool read_status;
	unsigned int num_line;
	


	FILE *fout = fopen("INCAR.out","w");

	// Read all atoms information
	ifstream INCAR(argv[3]);
	read_status = true;
	num_line = 0;
	if ( INCAR.is_open() ) {
		while ((read_status=getline(INCAR,line))==true){
			ss.str (line);
			num_line++;
			if ( num_line == 1 ) {
				fprintf(fout," SYSTEM      =    %s %s\n",argv[1],argv[2]);

			}

			else if (num_line == 11 ) {
				fprintf(fout," ENCUT      =    %f eV\n",atof(argv[4]));
			}
			else {
				fprintf(fout,"%s\n",line.c_str());
			}		
		}
	}

/*
	fprintf(fout,"  SYSTEM     =    %s%s\n\n",argv[1],argv[2]);
	fprintf(fout,"  NSW        =    5000\n\n");
	fprintf(fout,"  ISIF       =    3\n");
	fprintf(fout,"  IBRION     =    2\n");
	fprintf(fout,"  IREAL      =    False\n\n");
	fprintf(fout,"  ENCUT      =    %f\n\n",atof(argv[3].c_str()));
	fprintf(fout,"  EDIFF      =    1E-5\n");
	fprintf(fout,"  EDIFFG     =    -0.01\n\n");
	fprintf(fout,"  ISMEAR     =    0\n");
	fprintf(fout,"  SIGMA      =    0.01\n");

*/

	fclose(fout);

	return 0;

}
