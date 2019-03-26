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
  	if (argc != 7 ) { 
    		std::cerr << "Usage: " << argv[0] << " A B FLAG a b c" << endl;
   	 	return 1;
  	}



	FILE *fout = fopen("POSCAR.out","w");



	// FCC
	if ( atoi(argv[3]) == 1 ) {
		fprintf(fout," %2s2 %2s2\n",argv[1],argv[2]);
		fprintf(fout,"1.0\n");
		fprintf(fout," %10.6f %10.6f %10.6f\n",atof(argv[4]),0.0,0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,atof(argv[4]),0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,0.0,atof(argv[4]));
		fprintf(fout," %2s %2s\n",argv[1],argv[2]);
		fprintf(fout," %3d %3d\n",2,2);
		fprintf(fout,"Direct\n");
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,0.0,0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,0.5,0.5);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.5,0.0,0.5);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.5,0.5,0.0);
	}


	// CsCl
	if ( atoi(argv[3]) == 2 ) {
		fprintf(fout," %2s4 %2s4\n",argv[1],argv[2]);
		fprintf(fout,"1.0\n");
		fprintf(fout," %10.6f %10.6f %10.6f\n",atof(argv[4]),0.0,0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,atof(argv[4]),0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,0.0,atof(argv[4]));
		fprintf(fout," %2s %2s\n",argv[1],argv[2]);
		fprintf(fout," %3d %3d\n",1,1);
		fprintf(fout,"Direct\n");
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,0.0,0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.5,0.5,0.5);
	}


	// NaCl
	if ( atoi(argv[3]) == 3 ) {
		fprintf(fout," %2s4 %2s4\n",argv[1],argv[2]);
		fprintf(fout,"1.0\n");
		fprintf(fout," %10.6f %10.6f %10.6f\n",atof(argv[4]),0.0,0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,atof(argv[4]),0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,0.0,atof(argv[4]));
		fprintf(fout," %2s %2s\n",argv[1],argv[2]);
		fprintf(fout," %3d %3d\n",4,4);
		fprintf(fout,"Direct\n");
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,0.0,0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,0.5,0.5);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.5,0.0,0.5);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.5,0.5,0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,0.0,0.5);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,0.5,0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.5,0.0,0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.5,0.5,0.5);
	}


	// Wurtzite
	if ( atoi(argv[3]) == 4 ) {
		fprintf(fout," %2s2 %2s2\n",argv[1],argv[2]);
		fprintf(fout,"1.0\n");
		fprintf(fout," %10.6f %10.6f %10.6f\n",atof(argv[4]),0.0,0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",-0.5*atof(argv[4]),0.5*sqrt(3)*atof(argv[4]),0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,0.0,atof(argv[5]));
		fprintf(fout," %2s %2s\n",argv[1],argv[2]);
		fprintf(fout," %3d %3d\n",2,2);
		fprintf(fout,"Direct\n");
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.333333,0.666667,0.000146);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.666667,0.333333,0.500146);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.333333,0.666667,0.374854);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.666667,0.333333,0.874854);
	}


	// Zinc Blende
	if ( atoi(argv[3]) == 5 ) {
		fprintf(fout," %2s4 %2s4\n",argv[1],argv[2]);
		fprintf(fout,"1.0\n");
		fprintf(fout," %10.6f %10.6f %10.6f\n",atof(argv[4]),0.0,0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,atof(argv[4]),0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,0.0,atof(argv[4]));
		fprintf(fout," %2s %2s\n",argv[1],argv[2]);
		fprintf(fout," %3d %3d\n",4,4);
		fprintf(fout,"Direct\n");
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,0.0,0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,0.5,0.5);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.5,0.0,0.5);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.5,0.5,0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.25,0.75,0.75);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.25,0.25,0.25);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.75,0.75,0.25);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.75,0.25,0.75);
	}

	// HCP
	if ( atoi(argv[3]) == 6 ) {
		fprintf(fout," %2s2 %2s2\n",argv[1],argv[2]);
		fprintf(fout,"1.0\n");
		fprintf(fout," %10.6f %10.6f %10.6f\n",atof(argv[4]),0.0,0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",-0.5*atof(argv[4]),0.5*sqrt(3)*atof(argv[4]),0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,0.0,atof(argv[5]));
		fprintf(fout," %2s %2s\n",argv[1],argv[2]);
		fprintf(fout," %3d %3d\n",1,1);
		fprintf(fout,"Direct\n");
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.333333,0.666667,0.250000);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.666667,0.333333,0.750000);
	}



	// CrB,  B33
	if ( atoi(argv[3]) == 7 ) {
		fprintf(fout," %2s4 %2s4\n",argv[1],argv[2]);
		fprintf(fout,"1.0\n");
		fprintf(fout," %10.6f %10.6f %10.6f\n",atof(argv[4]),0.0,0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,atof(argv[5]),0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,0.0,atof(argv[6]));
		fprintf(fout," %2s %2s\n",argv[1],argv[2]);
		fprintf(fout," %3d %3d\n",4,4);
		fprintf(fout,"Direct\n");
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,0.145467,0.750000);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,0.854533,0.250000);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.5,0.645467,0.750000);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.5,0.354533,0.250000);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.5,0.935574,0.750000);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.5,0.064426,0.250000);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,0.435574,0.750000);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,0.564426,0.250000);

	}


	// CdAu,    B19
	if ( atoi(argv[3]) == 8 ) {
		fprintf(fout," %2s4 %2s4\n",argv[1],argv[2]);
		fprintf(fout,"1.0\n");
		fprintf(fout," %10.6f %10.6f %10.6f\n",atof(argv[4]),0.0,0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,atof(argv[5]),0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,0.0,atof(argv[6]));
		fprintf(fout," %2s %2s\n",argv[1],argv[2]);
		fprintf(fout," %3d %3d\n",2,2);
		fprintf(fout,"Direct\n");
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,0.75,0.305845);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,0.25,0.694155);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.5,0.75,0.810741);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.5,0.25,0.189259);

	}


	// TiCu,     B11
	if ( atoi(argv[3]) == 9 ) {
		fprintf(fout," %2s2 %2s2\n",argv[1],argv[2]);
		fprintf(fout,"1.0\n");
		fprintf(fout," %10.6f %10.6f %10.6f\n",atof(argv[4]),0.0,0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,atof(argv[4]),0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,0.0,atof(argv[5]));
		fprintf(fout," %2s %2s\n",argv[1],argv[2]);
		fprintf(fout," %3d %3d\n",2,2);
		fprintf(fout,"Direct\n");
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.500000,0.000000,0.355763);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.000000,0.500000,0.644237);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.500000,0.000000,0.889079);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.000000,0.500000,0.110921);
	}


	// FeB,      B27
	if ( atoi(argv[3]) == 10 ) {
		fprintf(fout," %2s4 %2s4\n",argv[1],argv[2]);
		fprintf(fout,"1.0\n");
		fprintf(fout," %10.6f %10.6f %10.6f\n",atof(argv[4]),0.0,0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,atof(argv[5]),0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,0.0,atof(argv[6]));
		fprintf(fout," %2s %2s\n",argv[1],argv[2]);
		fprintf(fout," %3d %3d\n",4,4);
		fprintf(fout,"Direct\n");
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.250000,0.379927,0.678145);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.750000,0.620073,0.321855);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.750000,0.879927,0.821855);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.250000,0.120073,0.178145);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.250000,0.881326,0.534234);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.750000,0.118674,0.465766);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.750000,0.381326,0.965766);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.250000,0.618674,0.034234);

	}


	// CuPt,       L1_1
	if ( atoi(argv[3]) == 11 ) {
		fprintf(fout," %2s3 %2s3\n",argv[1],argv[2]);
		fprintf(fout,"1.0\n");
		fprintf(fout," %10.6f %10.6f %10.6f\n",atof(argv[4]),0.0,0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",-0.5*atof(argv[4]),0.5*sqrt(3)*atof(argv[4]),0.0);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.0,0.0,atof(argv[6]));

		fprintf(fout," %2s %2s\n",argv[1],argv[2]);
		fprintf(fout," %3d %3d\n",3,3);
		fprintf(fout,"Direct\n");
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.000000,0.000000,0.000000);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.666667,0.333333,0.333333);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.333333,0.666667,0.666667);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.666667,0.333333,0.833333);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.333333,0.666667,0.166667);
		fprintf(fout," %10.6f %10.6f %10.6f\n",0.000000,0.000000,0.500000);
	}



	fclose(fout);

	return 0;

}
