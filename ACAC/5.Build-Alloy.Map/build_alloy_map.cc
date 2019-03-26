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

#define MAX_COUNT 1000
#define MAX_STRUCT 11

using namespace std;

typedef struct {
	string name1;
	string name2;
	float E_form[MAX_STRUCT];  
	float E_form_HCP;
	float DOS_sim[MAX_STRUCT];
	int flag;
} ALLOY;


int map_str_int(string name) {

	if ( name.compare("FCC") == 0 ) return 0;
	if ( name.compare("CsCl") == 0 ) return 1;
	if ( name.compare("NaCl") == 0 ) return 2;
	if ( name.compare("Wurt") == 0 ) return 3;
	if ( name.compare("Zinc") == 0 ) return 4;
	if ( name.compare("HCP") == 0 ) return 5;
	if ( name.compare("B33") == 0 ) return 6;
	if ( name.compare("B19") == 0 ) return 7;
	if ( name.compare("B11") == 0 ) return 8;
	if ( name.compare("B27") == 0 ) return 9;
	if ( name.compare("L11") == 0 ) return 10;


}



int main(int argc, char *argv[])
{
  	// Check argument
  	if (argc != 5) { 
    		std::cerr << "Usage: " << argv[0] << " INPUT_A TOT_E TOT_E-HCP DOS_SIM-VALUE " << endl;

   	 	return 1;
  	}

	// Set variables

	int idx1, idx2;

	string table[MAX_COUNT];
	float table_E[MAX_COUNT];
	ALLOY map[MAX_COUNT][MAX_COUNT];
	unsigned int table_len = 0;

	float N_unitAtom[MAX_STRUCT] = {2.0, 1.0, 4.0, 2.0, 4.0, 1.0, 4.0, 2.0, 2.0, 4.0, 3.0};

	unsigned int DOSsim_hist_num = 100;
	float DOSsim_hist_max = 30;
	float DOSsim_hist_unit = DOSsim_hist_max / (float)(DOSsim_hist_num);

	unsigned int DOSsim_hist[DOSsim_hist_num];
	
	
	printf("Histogram MAX: %f\n",DOSsim_hist_max);
	printf("Histogram Unit: %f\n",DOSsim_hist_unit);

	for ( int i = 0; i < DOSsim_hist_num; i++ ) {
		DOSsim_hist[i] = 0;
	}


  	istringstream ss;
	string line, col1, col2, col3, col4, col5, col6, col7, col8, col9;

	bool read_status;
  	int num_line;

	// Read all atoms information
	ifstream INPUT_A(argv[1]);
	read_status = true;
	num_line = 0;
	if ( INPUT_A.is_open() ) {
		while ((read_status=getline(INPUT_A,line))==true){
			num_line++;
			if ( num_line > 0 ) {
				ss.str (line);
				ss >> col1;
				ss.clear();
	
				table[num_line-1] = col1;

			}		
		}
	}

	table_len = num_line;


	for ( int i = 0; i < table_len; i++ ) {

		for ( int j = 0; j < table_len; j++ ) {
			for ( int k = 0; k < MAX_STRUCT; k++ ) {
				map[i][j].E_form[k] = 0.0;
				map[i][j].DOS_sim[k] = 0.0;
			}
			map[i][j].E_form_HCP = 0.0;
			map[i][j].flag = 0;


		}


	}

	// Read all atoms in LIST A
	ifstream TOT_E(argv[2]);
	read_status = true;
	num_line = 0;
	if ( TOT_E.is_open() ) {
		while ((read_status=getline(TOT_E,line))==true){
			num_line++;
			if ( num_line > 0 ) {
				ss.str (line);
				ss >> col1 >> col2 >> col3 >> col4;
				ss.clear();

				for ( int i = 0; i < table_len; i++ ) {
					if ( table[i].compare(col1) == 0 ) {
						idx1 = i;
						break;
					}

				}

				for ( int i = 0; i < table_len; i++ ) {
					if ( table[i].compare(col2) == 0 ) {
						idx2 = i;
						break;
					}

				}

				map[idx1][idx2].name1 = col1;	
				map[idx1][idx2].name2 = col2;	

				
				map[idx1][idx2].E_form[map_str_int(col3)] = atof(col4.c_str())/N_unitAtom[map_str_int(col3)];	
				map[idx1][idx2].flag++;			

			}		
		}
	}

	for ( int i = 0; i < table_len; i++ ) {

		for ( int j = 0; j < table_len; j++ ) {
			if (i != j )map[i][j].flag++;


		}


	}


	// Read all atoms in LIST B
	ifstream TOT_E_HCP(argv[3]);
	read_status = true;
	num_line = 0;
	if ( TOT_E_HCP.is_open() ) {
		while ((read_status=getline(TOT_E_HCP,line))==true){
			num_line++;
			if ( num_line > 0 ) {
				ss.str (line);
				ss >> col1 >> col2 >> col3 >> col4;
				ss.clear();
	
				for ( int i = 0; i < table_len; i++ ) {
					if ( table[i].compare(col1) == 0 ) {
						idx1 = i;
						break;
					}

				}

				for ( int i = 0; i < table_len; i++ ) {
					if ( table[i].compare(col2) == 0 ) {
						idx2 = i;
						break;
					}

				}

				map[idx1][idx2].E_form_HCP = atof(col4.c_str());	
				map[idx1][idx2].flag++;			
			}		
		}
	}


	// Read all atoms in LIST B
	ifstream DOS_Sim_VALUE(argv[4]);
	read_status = true;
	num_line = 0;
	if ( DOS_Sim_VALUE.is_open() ) {
		while ((read_status=getline(DOS_Sim_VALUE,line))==true){
			num_line++;
			if ( num_line > 0 ) {
				ss.str (line);
				ss >> col1 >> col2 >> col3 >> col4;
				ss.clear();
	
				for ( int i = 0; i < table_len; i++ ) {
					if ( table[i].compare(col1) == 0 ) {
						idx1 = i;
						break;
					}

				}

				for ( int i = 0; i < table_len; i++ ) {
					if ( table[i].compare(col2) == 0 ) {
						idx2 = i;
						break;
					}

				}

				map[idx1][idx2].DOS_sim[map_str_int(col3)] = atof(col4.c_str());

			}		
		}
	}

	float E_lowest;
	int k_lowest;

	for ( int i = 0; i < table_len; i++ ) {
	
			table_E[i] = 0.0;		
			k_lowest = 0;
			E_lowest = map[i][i].E_form[0];
			for ( int k = 0; k < MAX_STRUCT; k++ ) {
				if ( map[i][i].E_form[k] <= E_lowest ) {
					E_lowest = map[i][i].E_form[k];			
					k_lowest = k;
				} 

			}
	
			if ( map[i][i].E_form_HCP < E_lowest ) {
				E_lowest = map[i][i].E_form_HCP;
				k_lowest = 5;



			}

			if ( map[i][i].flag >= MAX_STRUCT )
				table_E[i] = E_lowest/2.0;
	}

	// Write output of all compounds
	FILE *OUTFILE0 = fopen("OUTFILE0.dat","w");
	FILE *OUTFILE1 = fopen("OUTFILE1.dat","w");
	FILE *OUTFILE2 = fopen("OUTFILE2.dat","w");
	FILE *OUTFILE3 = fopen("OUTFILE3.dat","w");
	FILE *OUTFILE4 = fopen("OUTFILE4.dat","w");
	FILE *OUTFILE5 = fopen("OUTFILE5.dat","w");

	fprintf(OUTFILE1,"%8s","TABLE");
	fprintf(OUTFILE2,"%8s","TABLE");
	fprintf(OUTFILE3,"%8s","TABLE");
	fprintf(OUTFILE4,"%8s","TABLE");


	for ( int i = 0; i < table_len; i++ ) {

		fprintf(OUTFILE1,"%8s",table[i].c_str());
		fprintf(OUTFILE2,"%8s",table[i].c_str());
		fprintf(OUTFILE3,"%8s",table[i].c_str());
		fprintf(OUTFILE4,"%8s",table[i].c_str());

	}

	fprintf(OUTFILE1,"\n","");
	fprintf(OUTFILE2,"\n","");
	fprintf(OUTFILE3,"\n","");
	fprintf(OUTFILE4,"\n","");


	for ( int i = 0; i < table_len; i++ ) {

	
		fprintf(OUTFILE1,"%8s",table[i].c_str());
		fprintf(OUTFILE2,"%8s",table[i].c_str());
		fprintf(OUTFILE3,"%8s",table[i].c_str());
		fprintf(OUTFILE4,"%8s",table[i].c_str());


		for ( int j = 0; j < table_len; j++ ) {

			fprintf(OUTFILE0,"%2s %2s %5s %8.3f\n",  table[i].c_str(), table[j].c_str(), "FCC", map[i][j].E_form[0]);
			fprintf(OUTFILE0,"%2s %2s %5s %8.3f\n",  table[i].c_str(), table[j].c_str(), "CsCl", map[i][j].E_form[1]);
			fprintf(OUTFILE0,"%2s %2s %5s %8.3f\n",  table[i].c_str(), table[j].c_str(), "NaCl", map[i][j].E_form[2]);
			fprintf(OUTFILE0,"%2s %2s %5s %8.3f\n",  table[i].c_str(), table[j].c_str(), "Wurt", map[i][j].E_form[3]);
			fprintf(OUTFILE0,"%2s %2s %5s %8.3f\n",  table[i].c_str(), table[j].c_str(), "Zinc", map[i][j].E_form[4]);
			fprintf(OUTFILE0,"%2s %2s %5s %8.3f\n",  table[i].c_str(), table[j].c_str(), "HCP", map[i][j].E_form_HCP);
			fprintf(OUTFILE0,"%2s %2s %5s %8.3f\n",  table[i].c_str(), table[j].c_str(), "B33", map[i][j].E_form[6]);
			fprintf(OUTFILE0,"%2s %2s %5s %8.3f\n",  table[i].c_str(), table[j].c_str(), "B19", map[i][j].E_form[7]);
			fprintf(OUTFILE0,"%2s %2s %5s %8.3f\n",  table[i].c_str(), table[j].c_str(), "B11", map[i][j].E_form[8]);
			fprintf(OUTFILE0,"%2s %2s %5s %8.3f\n",  table[i].c_str(), table[j].c_str(), "B27", map[i][j].E_form[9]);
			fprintf(OUTFILE0,"%2s %2s %5s %8.3f\n",  table[i].c_str(), table[j].c_str(), "L11", map[i][j].E_form[10]);



			k_lowest = 0;
			E_lowest = map[i][j].E_form[0];
			for ( int k = 0; k < MAX_STRUCT; k++ ) {
				if ( map[i][j].E_form[k] <= E_lowest ) {
					E_lowest = map[i][j].E_form[k];			
					k_lowest = k;
				} 

			}
	
			if ( map[i][j].E_form_HCP < E_lowest ) {
				E_lowest = map[i][j].E_form_HCP;
				k_lowest = 5;



			}

			if ( j >= i && map[i][j].flag >= 5) {
			fprintf(OUTFILE1,"%8.1f", E_lowest);

			if ( k_lowest == 0 ) 	fprintf(OUTFILE2,"%8s", "FCC");
			if ( k_lowest == 1 && i != j ) 	fprintf(OUTFILE2,"%8s", "CsCl");
			if ( k_lowest == 1 && i == j ) 	fprintf(OUTFILE2,"%8s", "BCC");
			if ( k_lowest == 2 && i != j ) 	fprintf(OUTFILE2,"%8s", "NaCl");
			if ( k_lowest == 2 && i == j ) 	fprintf(OUTFILE2,"%8s", "SC");
			if ( k_lowest == 3 ) 	fprintf(OUTFILE2,"%8s", "Wurt");
			if ( k_lowest == 4 ) 	fprintf(OUTFILE2,"%8s", "Zinc");
			if ( k_lowest == 5 ) 	fprintf(OUTFILE2,"%8s", "HCP");
			if ( k_lowest == 6 ) 	fprintf(OUTFILE2,"%8s", "B33");
			if ( k_lowest == 7 ) 	fprintf(OUTFILE2,"%8s", "B19");
			if ( k_lowest == 8 ) 	fprintf(OUTFILE2,"%8s", "B11");
			if ( k_lowest == 9 ) 	fprintf(OUTFILE2,"%8s", "B27");
			if ( k_lowest == 10 ) 	fprintf(OUTFILE2,"%8s", "L11");





			if ( table_E[i] != 0 && table_E[j] != 0 )
				fprintf(OUTFILE3,"%8.3f",-table_E[i]-table_E[j]+E_lowest);
			else
				fprintf(OUTFILE3,"%8s","X");
/*
			if ( k_lowest == 0 ) 	fprintf(OUTFILE3,"%8.3f", E_lowest);
			if ( k_lowest == 1 ) 	fprintf(OUTFILE3,"%8.3f", map[i][j].DOS_sim[1]);
			if ( k_lowest == 2 ) 	fprintf(OUTFILE3,"%8.3f", map[i][j].DOS_sim[2]);
			if ( k_lowest == 3 ) 	fprintf(OUTFILE3,"%8.3f", map[i][j].DOS_sim[3]);
			if ( k_lowest == 4 ) 	fprintf(OUTFILE3,"%8.3f", map[i][j].DOS_sim[4]);
			if ( k_lowest == 5 ) 	fprintf(OUTFILE3,"%8.3f", map[i][j].DOS_sim[5]);

*/

			if ( k_lowest == 0 ) 	fprintf(OUTFILE4,"%8.3f", map[i][j].DOS_sim[0]);
			if ( k_lowest == 1 ) 	fprintf(OUTFILE4,"%8.3f", map[i][j].DOS_sim[1]);
			if ( k_lowest == 2 ) 	fprintf(OUTFILE4,"%8.3f", map[i][j].DOS_sim[2]);
			if ( k_lowest == 3 ) 	fprintf(OUTFILE4,"%8.3f", map[i][j].DOS_sim[3]);
			if ( k_lowest == 4 ) 	fprintf(OUTFILE4,"%8.3f", map[i][j].DOS_sim[4]);
			if ( k_lowest == 5 ) 	fprintf(OUTFILE4,"%8.3f", map[i][j].DOS_sim[5]);
			if ( k_lowest == 6 ) 	fprintf(OUTFILE4,"%8.3f", map[i][j].DOS_sim[6]);
			if ( k_lowest == 7 ) 	fprintf(OUTFILE4,"%8.3f", map[i][j].DOS_sim[7]);
			if ( k_lowest == 8 ) 	fprintf(OUTFILE4,"%8.3f", map[i][j].DOS_sim[8]);
			if ( k_lowest == 9 ) 	fprintf(OUTFILE4,"%8.3f", map[i][j].DOS_sim[9]);
			if ( k_lowest == 10 ) 	fprintf(OUTFILE4,"%8.3f", map[i][j].DOS_sim[10]);
			
				for ( int hi = 0; hi < DOSsim_hist_num; hi++ ) {

					if ( map[i][j].DOS_sim[k_lowest] >= DOSsim_hist_unit*(float)hi && map[i][j].DOS_sim[k_lowest] < DOSsim_hist_unit*(float)(hi+1) )		 
						DOSsim_hist[hi]++;

				}
				
				if ( map[i][j].DOS_sim[k_lowest] >= DOSsim_hist_unit*(float)(DOSsim_hist_num) )	
					DOSsim_hist[DOSsim_hist_num-1]++;	 

			}

			else if ( j < i ) {

				fprintf(OUTFILE1,"%8s","-");			
				fprintf(OUTFILE2,"%8s","-");			
				fprintf(OUTFILE3,"%8s","-");			
				fprintf(OUTFILE4,"%8s","-");			
			}

			else {

				fprintf(OUTFILE1,"%8s","X");			
				fprintf(OUTFILE2,"%8s","X");			
				fprintf(OUTFILE3,"%8s","X");			
				fprintf(OUTFILE4,"%8s","X");			
			}


		}


		fprintf(OUTFILE1,"\n");
		fprintf(OUTFILE2,"\n");
		fprintf(OUTFILE3,"\n");
		fprintf(OUTFILE4,"\n");
	}

	DOSsim_hist[0] = 1;

	for ( int hi = 0; hi < DOSsim_hist_num; hi++ ) {
		fprintf(OUTFILE5,"%f %d\n",(float)hi*DOSsim_hist_unit,DOSsim_hist[hi]);

	}
	


	fclose(OUTFILE0);
	fclose(OUTFILE1);
	fclose(OUTFILE2);
	fclose(OUTFILE3);
	fclose(OUTFILE4);
	fclose(OUTFILE5);


	return 0;

}
