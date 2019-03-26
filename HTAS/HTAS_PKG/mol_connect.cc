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

#define PI  3.14159265 

#define PRINT_FLAG 1

#define FPRINT_FOUT 0 
#define FPRINT_FMOL 0
#define FPRINT_FCHEM 0

#define FPRINT_FXYZ 1 
#define FPRINT_FNEW 1

#define FPRINT_FNEWCIF 1


#define MAX_TYPE 200
// Line number
#define TIMESTEP  1
#define NUMBER_OF_ATOMS  4
#define BOX_X  6
#define BOX_Y  7
#define BOX_Z  8
#define LATTICE_CELL 9
#define LATTICE_ANGLE 10

#define LOCATION  10 

#define GRIDSIZE 2	
#define GRID  4

using namespace std;

//const string atomic_char[] = {"C", "H", "B", "N"};
//const string atomic_char[] = {"Li", "O", "C", "H"};
//const string atomic_char[] = {"H", "O", "Si", "Al", "Li"};

/*********************************************************************************/
/*                              ATOMIC RADII                                     */
/*********************************************************************************/

//const float atomic_radii[4] = {1.3825, 0.6867, 1.3484, 1.5520};


//const string atomic_char[4] = {"C", "H", "B", "N"};

/*
const float atomic_radii[70] = {0.6867, 0.0, 2.30, 1.05, 0.85, 1.3817, 1.2333, 1.2450, 0.50, 0.0,
				1.80, 1.50, 1.25, 1.10, 1.00, 1.9405, 1.00, 0.0, 2.20, 1.80,
				1.60, 1.40, 1.35, 1.40, 1.40, 1.40, 1.35, 1.35,1.35, 1.35,
				1.30, 1.25, 1.15, 1.15, 1.15, 0.0, 2.35, 2.00, 1.80, 1.55,       
				1.45, 1.45, 1.35, 1.30, 1.35, 1.40, 1.60, 1.55, 1.55, 1.45,
				1.45, 1.40, 1.40, 0.0, 2.60, 2.15,  0.0, 1.55, 1.45,  1.35, 
				1.35, 1.30, 1.35, 1.35, 1.35, 1.50, 1.90, 1.80, 1.60, 1.90};
*/
const float atomic_radii[70] = {0.31, 0.28, 1.28, 0.96, 0.84, 0.76, 0.71, 0.66, 0.57, 0.58,
								1.66, 1.41, 1.21, 1.11, 1.07, 1.05, 1.02, 1.06, 2.03, 1.76,
								1.70, 1.60, 1.53, 1.39, 1.61, 1.52, 1.50, 1.24, 1.32, 1.22,
								1.22, 1.20, 1.19, 1.15, 1.20, 1.16, 2.20, 1.95, 1.90, 1.75,       
								1.64, 1.54, 1.47, 1.46, 1.42, 1.39, 1.45, 1.44, 1.42, 1.39,
								1.39, 1.38, 1.39, 1.40, 2.44, 2.15,  0.0, 1.75, 1.70, 1.62, 
								1.51, 1.44, 1.41, 1.36, 1.36, 1.32, 1.45, 1.46, 1.48, 1.40};


const string atomic_char[70] = {"H", "He", "Li", "Be", "B", "C" , "N", "O", "F", "Ne",
				"Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar", "K", "Ca",
				"Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn",
				"Ga", "Ge", "As", "Se", "Br", "Kr", "Rb", "Sr", "Y", "Zr",       
				"Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn",
				"Sb", "Te", "I", "Xe", "Cs", "Ba",  "*", "Hf", "Ta",  "W", 
				"Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po"};


unsigned int size_atomic_char = sizeof(atomic_char)/sizeof(*atomic_char);

bool issame(const char *str1, const char *str2 ) {

	cout << str1 << ": " << sizeof(str1) << ", " << str2 << ": " <<  sizeof(str2) << endl;

	if ( sizeof(*str1) != sizeof(*str2) ){

			return 0;
	}



	else{
		for ( int i = 0; i < sizeof(*str1); i++ ) {
			if (str1[i] != str2[i])
				return 0;


		}

		return 1;

	}



}


int map_atom_number ( const char* atom_str, int size_atomic_char ) {
	
	string temp_i = atom_str;
	for ( int j = 0; j < size_atomic_char; j++ ) {
		string temp_j = atomic_char[j];	
		
		//if ( issame(atom_str, atomic_char[j]) ) {
		if ( temp_i.compare(temp_j) == 0 ) {
			return j;
		}
	}
	return 0;
}
	

//establish molecular list and ring size
int identify_solvent (int **mat_atm, int *type, int idx1, int idx2, int num_atoms, int start, int end, int* flag) {
	
	if ( end == 1 ) 
		return 0;

	else {

		while ( idx2 < num_atoms ) {
			//printf("idx1: %d, idx2: %d\n",idx1,idx2);
			//check whether matrix element is occupied or not.		
			if ( mat_atm[idx1][idx2] == 1 ) {
				/*
				//establish head of molecular connection list at idx1's atom. (Start)
				if ( start == 1 ) {
					vector < int >* bond = new vector < int >;					
					bond->push_back(idx1);
					bond->push_back(idx2);

					int* ring_cnt = new int;
					*ring_cnt = 0;
					molecule_list->push_back(bond);	molecule_list_ring->push_back(ring_cnt);
					start = 0;			
				}
			
				//concatenate tail of molecular connection list at idx1's atom. 
				else {
					vector < int >* bond2 = *(molecule_list->end() - 1);
					int* ring_cnt2 = *(molecule_list_ring->end() - 1);
					
					int same = 0;
					int same2 = 0;

					//firstly check whether it counts duplicate 'idx2' atom in 'idx1's molecular list.
					for ( vector< int >::iterator IterPos = bond2->begin(); IterPos != bond2->end(); ++IterPos ) {
						if ( idx2 == *IterPos ) {
							same = 1;
							break;
						}
					}
					if ( same == 0 ) bond2->push_back(idx2); //if no one is 'idx2' atom in 'idx1's molecular list. 
					else{ //if 'idx2' has already included in 'idx1's molecular list, 
						//secondly check whether ring exist in 'idx1's molecular list.
						for ( vector< int >::iterator IterPos = bond2->begin(); IterPos != bond2->end(); ++IterPos ) {
							if ( mat_atm[idx1][*IterPos] == 1 ) {
								same2++;
								mat_atm[idx1][*IterPos] = 0;
								mat_atm[*IterPos][idx1] = 0;
							}
						}
						if (rflag) {
					    //count ring due to duplicate 'idx2' atom in the list. 			
							if ( (*ring_cnt2) == 0 ) (*ring_cnt2)++;
							else {//due to prevent checking for duplicate ring count.						
								if ( same2 <= 1 ) (*ring_cnt2)++;
							}
						}
					}	
				}
				mat_atm[idx1][idx2] = 0;
				mat_atm[idx2][idx1] = 0;
				*/
				//if ( type[idx2] == 29 ) *flag = 1;

				mat_atm[idx1][idx2] = 0;
				mat_atm[idx2][idx1] = 0;

				//if (type[idx2] == map_atom_number("Y",size_atomic_char)+1) *flag = 1;
	
				if (type[idx2] != map_atom_number("H",size_atomic_char)+1  && \
					type[idx2] != map_atom_number("C",size_atomic_char)+1  && \
					type[idx2] != map_atom_number("N",size_atomic_char)+1  && \
					type[idx2] != map_atom_number("O",size_atomic_char)+1  && \
					type[idx2] != map_atom_number("P",size_atomic_char)+1  && \
					type[idx2] != map_atom_number("S",size_atomic_char)+1 ){
					*flag = 1;
				}

				identify_solvent ( mat_atm, type, idx2, 0, num_atoms, start, end, flag);
				
			} //check whether matrix is occupied or not.
			idx2++;

		} //while ( idx2 < num_atoms )
		end = 1;
	} //else
}



//establish molecular list and ring size
int connection (int **mat_atm, vector < vector < int >* >* molecule_list, vector < int* >* molecule_list_ring, \
				int idx1, int idx2, int num_atoms, int start, int end, int rflag) {
	
	if ( end == 1 ) 
		return 0;

	else {

		while ( idx2 < num_atoms ) {

			//check whether matrix element is occupied or not.		
			if ( mat_atm[idx1][idx2] == 1 ) {

				//establish head of molecular connection list at idx1's atom. (Start)
				if ( start == 1 ) {
					vector < int >* bond = new vector < int >;					
					bond->push_back(idx1);
					bond->push_back(idx2);

					int* ring_cnt = new int;
					*ring_cnt = 0;
					molecule_list->push_back(bond);	molecule_list_ring->push_back(ring_cnt);
					start = 0;			
				}
			
				//concatenate tail of molecular connection list at idx1's atom. 
				else {
					vector < int >* bond2 = *(molecule_list->end() - 1);
					int* ring_cnt2 = *(molecule_list_ring->end() - 1);
					
					int same = 0;
					int same2 = 0;

					//firstly check whether it counts duplicate 'idx2' atom in 'idx1's molecular list.
					for ( vector< int >::iterator IterPos = bond2->begin(); IterPos != bond2->end(); ++IterPos ) {
						if ( idx2 == *IterPos ) {
							same = 1;
							break;
						}
					}
					if ( same == 0 ) bond2->push_back(idx2); //if no one is 'idx2' atom in 'idx1's molecular list. 
					else{ //if 'idx2' has already included in 'idx1's molecular list, 
						//secondly check whether ring exist in 'idx1's molecular list.
						for ( vector< int >::iterator IterPos = bond2->begin(); IterPos != bond2->end(); ++IterPos ) {
							if ( mat_atm[idx1][*IterPos] == 1 ) {
								same2++;
								mat_atm[idx1][*IterPos] = 0;
								mat_atm[*IterPos][idx1] = 0;
							}
						}
						if (rflag) {
					    //count ring due to duplicate 'idx2' atom in the list. 			
							if ( (*ring_cnt2) == 0 ) (*ring_cnt2)++;
							else {//due to prevent checking for duplicate ring count.						
								if ( same2 <= 1 ) (*ring_cnt2)++;
							}
						}
					}	
				}
				mat_atm[idx1][idx2] = 0;
				mat_atm[idx2][idx1] = 0;
				connection ( mat_atm, molecule_list, molecule_list_ring, idx2, 0, num_atoms, start, end, rflag);
				
			} //check whether matrix is occupied or not.
			idx2++;

		} //while ( idx2 < num_atoms )
		end = 1;
	} //else
}

float calculate_bond_length(float x1, float x2, float y1, float y2, float z1, float z2) {
	float diff_x = x1 - x2; float diff_y = y1 - y2; float diff_z = z1 - z2;

	float bond_length = sqrt(diff_x*diff_x+diff_y*diff_y+diff_z*diff_z);

	return bond_length;

}
void showhelpinfo(char *s)
{
	cout<<"Usage:   "<<s<<" [-option] [argument]"<<endl;
	cout<<"option:  "<<"-h  show help information"<<endl;
	cout<<"         "<<"-r  show ring count"<<endl;
	cout<<"         "<<"-z  do not fill zero "<<endl;
}

int main(int argc, char *argv[]){
 



  	unsigned int timestep;
  	unsigned int num_atoms;

  	float box_x, box_y, box_z;


	//unsigned int size_atomic_char = sizeof(atomic_char)/sizeof(*atomic_char);
	unsigned int size_atomic_radii = sizeof(atomic_radii)/sizeof(*atomic_radii);


  	//check the number of parameters
  	if (argc != 4) { 
    	//tell the user how to run the program
    	std::cerr << "Usage: " << argv[0] << " INPUT_FILE_NAME(~.mol) OFFSET INPUT_FILE(~.cif)" << endl;

   	 	return 1;
  	}


	double offset = atof(argv[2]);

  	istringstream ss;
	string line, col1, col2, col3, col4, col5, col6, col7, col8;

	bool read_status = true;

  	int num_line = 0;
	//construct atom table's information

//	string *atomic_char = new string [MAX_TYPE];
	//char **atomic_char = new char *[MAX_TYPE];
	//float *atomic_radii = new float [MAX_TYPE];
	//float *atomic_masses = new float [MAX_TYPE];

	//initialization of variables
  	ifstream file(argv[1]);
  	//string line, col1, col2, col3, col4, col5;
  	int idx_atom, x_axis, y_axis, z_axis;


	int write_structure_on = 1;

  	float *coord_x;
  	float *coord_y;
  	float *coord_z;
  	int *type;

  	float *coord_x_saved;
  	float *coord_y_saved;
  	float *coord_z_saved;
  	int *type_saved;

	//unsigned int size_atomic_char = sizeof(atomic_char) / sizeof(*atomic_char);
	//unsigned int size_atomic_char = sizeof(atomic_char) / sizeof(*atomic_char);

	//unsigned int size_atomic_char = num_line-1;
	int atom_map[size_atomic_char];
	float *cov_radii = new float [size_atomic_char];


  	for ( int i = 0; i < size_atomic_char; i++ ) {
		string temp_i = atomic_char[i];
		for ( int j = 0; j < size_atomic_char; j++ ) {
			string temp_j = atomic_char[j];	
			//if ( issame(atomic_char[i],atomic_char[j] ) ){
			if ( temp_i.compare(temp_j) == 0 ) {
				atom_map[i] = j;
				cov_radii[i] = atomic_radii[j];
				break;
			}
		}
  	}


	vector < int * > *timestep_list = new vector < int * >;
	vector < int * > *molecule_type_list = new vector < int * > ;
	vector < vector < int * > * > *molecule_cnt_list = new vector < vector < int * > *>;

	unsigned int max_mol_num = 0;

#if FPRINT_FOUT
	FILE *fout = fopen("molcon_.out","w");
#endif

#if FPRINT_FMOL
	FILE *fmol = fopen("molfra_.out","w");
	fclose(fmol);
#endif 

#if FPRINT_FCHEM
	FILE *fchem = fopen("molchem.out","w");
	fclose(fchem);
#endif

	string mol_name;

	float alpha, beta, gamma;

	int rflag = 0;
	int zflag = 1;

	read_status = true;
  	num_line = 0;


	if (file.is_open()) {
		//read entire file
		while (read_status) {

#if FPRINT_FMOL	
			FILE *fmol = fopen("molfra_.out","a");		
#endif

#if FPRINT_FCHEM
			FILE *fchem = fopen("molchem.out","a");	

			
#endif	

			vector < int * > *molecule_cnt_list_tmp = new vector < int * >;
			vector< int * >::iterator IterPos_type_list; 

			if ( molecule_type_list->size() != 0 ) {
			
					for ( IterPos_type_list = molecule_type_list->begin(); IterPos_type_list != molecule_type_list->end(); ++IterPos_type_list) {
						
						int *temp = new int ;
						*temp = 0;
						molecule_cnt_list_tmp->push_back(temp);
			
					}
			}
	  		num_line = 0;
			//read each time step
			while ((read_status=getline(file,line))==true){
				if (++num_line == TIMESTEP){
					ss.str (line);
					ss >> col1 >> col2;
					ss.clear();
					mol_name = col2;
					timestep = std::atoi(col2.c_str());
						
				}
				else if (num_line == NUMBER_OF_ATOMS ){
					num_atoms = atoi(line.c_str());
					coord_x = new float [num_atoms];
					coord_y = new float [num_atoms];
					coord_z = new float [num_atoms];
					type = new int  [num_atoms];

					coord_x_saved = new float [num_atoms];
					coord_y_saved = new float [num_atoms];
					coord_z_saved = new float [num_atoms];
					type_saved = new int  [num_atoms];


				}
				else if (num_line >= 4 && num_line <= num_atoms + 4){
					ss.str (line);
					ss >> col1 >> col2 >> col3 >> col4 >> col5 >> col6 >> col7 >> col8;
					ss.clear();

					idx_atom = std::atoi(col1.c_str());
					type[idx_atom - 1] = map_atom_number(col5.c_str(),size_atomic_char)+1;
					coord_x[idx_atom - 1] = (float) std::atof(col2.c_str());
					coord_y[idx_atom - 1] = (float) std::atof(col3.c_str());
					coord_z[idx_atom - 1] = (float) std::atof(col4.c_str());
			
				  	//printf("type: %d, x: %f, y: %f, z: %f\n",type[idx_atom-1],coord_x[idx_atom-1],coord_y[idx_atom-1],coord_z[idx_atom-1]);	
					//if ((num_line + 1) == num_atoms + LOCATION) { 
					//	break;	
					//}
				}
				else if (num_line == LATTICE_CELL + num_atoms) {
					ss.str (line);
					ss >> col1 >> col2 >> col3;
					ss.clear();
					
					box_x = atof(col1.c_str()); 
					box_y = atof(col2.c_str());
					box_z = atof(col3.c_str());
				}
				else if (num_line == LATTICE_ANGLE + num_atoms) {
					ss.str (line);
					ss >> col1 >> col2 >> col3;
					ss.clear();


					alpha = atof(col1.c_str());
					beta = atof(col1.c_str());
					gamma = atof(col1.c_str());
				}

				else if (num_line == num_atoms + 10) {
					break;
	  			}
			
	  			
	  		}

			cout << "file prefix: " << mol_name << endl;

			char str_xyz[100], str_cif[100], str_cif_mol[100];
			strcpy(str_xyz,mol_name.c_str());
			strcat(str_xyz,".new.xyz");

			strcpy(str_cif,mol_name.c_str());
			strcat(str_cif,".new.cif");

			strcpy(str_cif_mol,mol_name.c_str());
			strcat(str_cif_mol,".new.mol");


#if FPRINT_FXYZ
			FILE *fxyz = fopen(str_xyz,"w");
#endif
			//FILE *fcif = fopen(str_cif,"w");

#if FPRINT_FNEW
			//if (write_structure_on==1)
			FILE *fcif_mol = fopen(str_cif_mol,"w"); 
#endif

#if FPRINT_FNEWCIF
			//if (write_structure_on==1)
			FILE *fnewcif = fopen(str_cif,"w"); 
#endif

			//cout << "test" << read_status << endl;	
	  		//if (read_status == false) break;	 

			for ( int i = 0; i < size_atomic_char; i++ ) {
				string temp_i = atomic_char[i];

	  			for ( int j = 0; j < size_atomic_char; j++ ) {
					string temp_j = atomic_char[j];	
		
					//if ( issame(atomic_char[i],atomic_char[j] )) {
					if ( temp_i.compare(temp_j) == 0 ) {
						atom_map[i] = j;
						cov_radii[i] = atomic_radii[j];
						//cout << atomic_char[j] << ": " << cov_radii[i] << "(" << i << ")" << endl;
						break;
					}
	  			}
	 		}


	 		//float *cov_radii = new float [size_atomic_char]; 
			/*
	  		cov_radii[0] = atomic_radii[0]; // H
 	  		cov_radii[1] = atomic_radii[7]; // O
	  		cov_radii[2] = atomic_radii[13]; // Si
	  		cov_radii[3] = atomic_radii[12]; // Al
	  		cov_radii[4] = atomic_radii[2]; // Li
			*/
			/*
	  		cov_radii[0] = 1.4;
	  		cov_radii[1] = 1.1;
	  		cov_radii[2] = 0.5;
	  		cov_radii[3] = 0.5;
			*/
			float bond_length, cov_length;

	 		//cout << "bond" << endl;
	  		int **mat_atm = new int *[num_atoms];  int **mat_atm_tmp = new int *[num_atoms];
	  		for ( int i = 0; i < num_atoms; i++ ){
				mat_atm[i] = new int [num_atoms]; mat_atm_tmp[i] = new int [num_atoms];
			}
			for ( int i = 0; i < num_atoms; i++ ) {
				for ( int j = 0; j < num_atoms; j++ ) {
					if ( i != j ) {
						int status = 0;						
						bond_length = calculate_bond_length(coord_x[i],coord_x[j],coord_y[i],coord_y[j],coord_z[i],coord_z[j]);
						cov_length = cov_radii[type[i]-1] + cov_radii[type[j]-1];
						//printf("i: %s j: %s cov_length: %f\n",atomic_char[type[i]-1].c_str(),atomic_char[type[j]-1].c_str(),cov_length);
						if ( bond_length <= cov_length + (offset * cov_length) ) {
								mat_atm[i][j] = 1;  mat_atm_tmp[i][j] = 1;
								mat_atm[j][i] = 1;  mat_atm_tmp[i][j] = 1;
								status = 1;

						}


						//if ( 0 ) {
						if (status != 1) {

								//printf("%f, %f, %f\n",coord_x[i],coord_y[i],coord_z[i] );
								float V = box_x * box_y * box_z * sqrt(1-cos(alpha*PI/180.0)*cos(alpha*PI/180)-cos(beta*PI/180.0)*cos(beta*PI/180)-cos(gamma*PI/180.0)*cos(gamma*PI/180.0)*cos(gamma*PI/180.0)+2*cos(alpha*PI/180.0)*cos(beta*PI/180.0)*cos(gamma*PI/180.0));  					

								float frac_x = (1/box_x)* coord_x[i]+(-cos(gamma*PI/180.0)/(box_x*sin(gamma*PI/180.0)))*coord_y[i]+((box_y*box_z*cos(gamma*PI/180.0)*(cos(alpha*PI/180.0)-cos(beta*PI/180.0)*cos(gamma*PI/180.0))/sin(gamma*PI/180.0))-box_y*box_z*cos(beta*PI/180.0)*sin(gamma*PI/180.0))*(1/V)*coord_z[i];
								float frac_y = (1/(box_y*sin(gamma*PI/180.0)))*coord_y[i]+(-box_x*box_z*(cos(alpha*PI/180.0)-cos(beta*PI/180.0)*cos(gamma*PI/180.0))/(V*sin(gamma*PI/180.0)))*coord_z[i];
								float frac_z = (box_x * box_y * sin(gamma*PI/180.0)/V)*coord_z[i];					

								//printf("before%f, %f, %f\n",frac_x,frac_y,frac_z );
								//int run_flag = 0;
								//for ( int a = -1; a <=1; a++ ){
								//for ( int b = -1; b <=1; b++ ){
								//for ( int c = -1; c <=1; c++ ){
								
								int loop_cnt = 0;
								int a, b, c;
								while ( loop_cnt < 4 ) {

								if ( loop_cnt == 0 ) {
									if ( frac_x > 0.5 ) a = 1; else a = -1;
									if ( frac_y > 0.5 ) b = 1; else b = -1;
									if ( frac_z > 0.5 ) c = 1; else c = -1;
								}
								if ( loop_cnt == 1 ) {
									if ( frac_x > 0.5 ) a = 1; else a = -1;
									b = 0; c = 0;
									//if ( frac_y > 0.5 ) b = 1; else b = -1;
									//if ( frac_z > 0.5 ) c = 1; else c = -1;
								}
								if ( loop_cnt == 2 ) {
									if ( frac_y > 0.5 ) b = 1; else b = -1;
									a = 0; c = 0;
									//if ( frac_y > 0.5 ) b = 1; else b = -1;
									//if ( frac_z > 0.5 ) c = 1; else c = -1;
								}
								if ( loop_cnt == 3 ) {
									if ( frac_z > 0.5 ) c = 1; else c = -1;
									a = 0; b = 0;
									//if ( frac_y > 0.5 ) b = 1; else b = -1;
									//if ( frac_z > 0.5 ) c = 1; else c = -1;
								}
								if ( loop_cnt == 4 ) {
									if ( frac_x > 0.5 ) a = 1; else a = -1;
									if ( frac_y > 0.5 ) b = 1; else b = -1;
									c = 0;
									//if ( frac_y > 0.5 ) b = 1; else b = -1;
									//if ( frac_z > 0.5 ) c = 1; else c = -1;
								}
								if ( loop_cnt == 5 ) {
									if ( frac_y > 0.5 ) b = 1; else b = -1;
									if ( frac_z > 0.5 ) c = 1; else c = -1;
									a = 0; 
									//if ( frac_y > 0.5 ) b = 1; else b = -1;
									//if ( frac_z > 0.5 ) c = 1; else c = -1;
								}
								if ( loop_cnt == 6 ) {
									if ( frac_z > 0.5 ) c = 1; else c = -1;
									if ( frac_x > 0.5 ) a = 1; else a = -1;
									b = 0;
									//if ( frac_y > 0.5 ) b = 1; else b = -1;
									//if ( frac_z > 0.5 ) c = 1; else c = -1;
								}

								loop_cnt++;
								
								a = -a; b = -b; c = -c;

							
								//int a = 0; int b = 0; int c = 0;
								float frac_x_exp = frac_x + ((float)a);
								float frac_y_exp = frac_y + ((float)b);
								float frac_z_exp = frac_z + ((float)c);

								float cosa = cos(alpha*PI/180.0);
								float sina = sin(alpha*PI/180.0);
								float cosb = cos(beta*PI/180.0);
								float sinb = sin(beta*PI/180.0);
								float cosg = cos(gamma*PI/180.0);
								float sing = sin(gamma*PI/180.0);

								float cosa2 = cosa * cosa;
								float cosb2 = cosb * cosb;
								float sing2 = sing * sing;

								float ax = box_x;

								float bx = box_y * cosg;
								float by = box_y * sing;

								float cx = box_z * cosb;
								float cy = box_z * (cosa - cosg*cosb) / sing;
								float cz = box_z * sqrt( 1 - (cosa2 + cosb2 - 2*cosg*cosb*cosa) / sing2 );


							    float xa = frac_x_exp * ax;  
    
  								float xb = frac_y_exp * bx;  
								float yb = frac_y_exp * by; 

								float xc = frac_z_exp * cx;  
							    float yc = frac_z_exp * cy;  
							    float zc = frac_z_exp * cz;  

							    float final_x = xa + xb + xc;
							    float final_y = yb + yc;
							    float final_z = zc;

						//		bond_length = calculate_bond_length(cart_x,coord_x[j],cart_y,coord_y[j],cart_z,coord_z[j]);

								


	
								float cart_x = final_x; //box_x*frac_x+box_y*cos(gamma*PI/180.0)*frac_y+box_z*cos(beta*PI/180.0)*frac_z;
								float cart_y = final_y; //box_y*sin(gamma*PI/180.0)*frac_y+box_z*((cos(alpha*PI/180.0)-cos(beta*PI/180.0)*cos(gamma*PI/180.0))/sin(gamma*PI/180.0))*frac_z;
								float cart_z = final_z; //(V/(box_x*box_y*sin(gamma*PI/180.0)))*frac_z;

								//printf("frac: %f, %f, %f\n",frac_x_exp,frac_y_exp, frac_z_exp);
								//printf("after: %f, %f, %f\n",cart_x,cart_y, cart_z);
								//printf("****************************************\n");
								bond_length = calculate_bond_length(cart_x,coord_x[j],cart_y,coord_y[j],cart_z,coord_z[j]);

							/*
								float sign_x, sign_y, sign_z;
								sign_x = 0; sign_y = 0; sign_z = 0;	
								if ( coord_x[i] > 0.5*box_x && coord_x[j] < 0.5*box_x ) {
									if ( coord_x[i] - coord_x[j] > 0.5*box_x ) 
										sign_x = 1;
								}
								if ( coord_x[i] < 0.5*box_x && coord_x[j] > 0.5*box_x ) {
									if ( coord_x[j] - coord_x[i] > 0.5*box_x ) 
										sign_x = -1;
								}

								if ( coord_y[i] > 0.5*box_y && coord_y[j] < 0.5*box_y ) {
									if ( coord_y[i] - coord_y[j] > 0.5*box_y ) 
										sign_y = 1;
								}
								if ( coord_y[i] < 0.5*box_y && coord_y[j] > 0.5*box_y ) {
									if ( coord_y[j] - coord_y[i] > 0.5*box_y ) 
										sign_y = -1;
								}
			
								if ( coord_z[i] > 0.5*box_z && coord_z[j] < 0.5*box_z ) {
									if ( coord_z[i] - coord_z[j] > 0.5*box_z ) 
										sign_z = 1;
								}
								if ( coord_z[i] < 0.5*box_z && coord_z[j] > 0.5*box_z ) {
									if ( coord_z[j] - coord_z[i] > 0.5*box_z ) 
										sign_z = -1;
								}
								bond_length = calculate_bond_length(coord_x[i],coord_x[j]+sign_x*box_x,coord_y[i],coord_y[j]+sign_y*box_y,coord_z[i],coord_z[j]+sign_z*box_z);

								*/




								cov_length = cov_radii[type[i]-1] + cov_radii[type[j]-1];
								if ( bond_length <= cov_length + (offset * cov_length) ) {
									mat_atm[i][j] = 1;
									mat_atm[j][i] = 1;
									//run_flag = 1;
								}
								//if (run_flag == 1) break;
								
								}
								//}
								//if (run_flag == 1) break;
								//}
								//if (run_flag == 1) break;
								//}
								
						}


					}
				}
	  		}

			//initialization of vector	
			vector < vector< int >* > * molecule_list = new vector < vector < int > *>;
			vector < int * > * molecule_list_ring = new vector < int * >;
			vector < int * > * molecule_type = new vector < int * >;
			vector < int * > * molecule_type_ring = new vector < int * >;
			vector < int * > * molecule_cnt = new vector < int * >;


			int *flag = new int;

			int connect_metal;
			int connect_metal_array[10000];

			for ( int i = 0; i < num_atoms; i++ ) {
				//if (type[i] == map_atom_number("Y",size_atomic_char)+1){
			
				if (type[i] != map_atom_number("H",size_atomic_char)+1  && \
					type[i] != map_atom_number("C",size_atomic_char)+1  && \
					type[i] != map_atom_number("N",size_atomic_char)+1  && \
					type[i] != map_atom_number("O",size_atomic_char)+1  && \
					type[i] != map_atom_number("P",size_atomic_char)+1  && \
					type[i] != map_atom_number("S",size_atomic_char)+1 ){
					//printf("bbb\n"); 
					connect_metal = 0;
					for ( int j = 0; j < num_atoms; j++ ) {
						if(mat_atm[i][j]==1){
							connect_metal_array[connect_metal] = j;
							connect_metal++;
							
						}

					}

					int remove_flag = 0;

					if ( connect_metal >  6 ) {
						remove_flag  = 1;
					}

					else if ( type[i] == map_atom_number("Cu",size_atomic_char)+1 && connect_metal > 5 ) {
						remove_flag = 1;
					}
	
					else if ( type[i] != map_atom_number("Zn",size_atomic_char)+1 && connect_metal > 4 ) { 
						remove_flag = 1;
					}

					if (remove_flag == 1){

					for ( int cc = 0; cc < connect_metal; cc++ ) {
						int j = connect_metal_array[cc];
					//for ( int j = 0; j < num_atoms; j++ ) {

						if ( mat_atm[i][j] == 1 ) {
							mat_atm[i][j] = 0; mat_atm[j][i] = 0; 
							mat_atm_tmp[i][j] = 0; mat_atm_tmp[j][i] = 0;
							*flag = 0;
							identify_solvent(mat_atm_tmp, type, j, 0, num_atoms, 1, 0, flag);
							//printf("aaa\n");
							//printf("flag: %d\n",*flag);	
							if ( *flag == 1 ){
								//printf("aaa\n");
								mat_atm[i][j] = 1; mat_atm[j][i] = 1;
							}
							for( int m = 0; m < num_atoms; m++ ) 
								for( int n = 0; n < num_atoms; n++ )
									mat_atm_tmp[m][n] = mat_atm[m][n];


						}


					}


					}
				}
			}

			delete mat_atm_tmp;


			for ( int i = 0; i < num_atoms; i++ ) {
				connection(mat_atm, molecule_list,  molecule_list_ring, i, i+1, num_atoms, 1, 0, rflag);
		 	}

	 		int atm_cnt[size_atomic_char];
	 		unsigned int match = 0;

			//establish molecular type list
	 		vector < vector < int >* >::iterator IterPos;
	 		vector < int * >::iterator IterPos_ring;
	 		for ( IterPos = molecule_list->begin(), IterPos_ring = molecule_list_ring->begin(); \
				IterPos != molecule_list->end(), IterPos_ring != molecule_list_ring->end(); \
				++IterPos, ++IterPos_ring ) {

				vector < int >* temp = *IterPos;

				//initialization of molecular array
				for ( int i = 0; i < size_atomic_char; i++ )
					atm_cnt[i] = 0;
		
				//assign molecular array
				for ( vector < int >::iterator subIterPos = temp->begin(); subIterPos != temp->end(); ++subIterPos )
					atm_cnt[type[*subIterPos]-1] = atm_cnt[type[*subIterPos]-1] + 1;
				
				vector< int * >::iterator temp_type_out = molecule_type->begin();
				vector< int * >::iterator temp_type_ring_out =molecule_type_ring->begin();
				vector< int * >::iterator temp_cnt_out = molecule_cnt->begin();
				
				
	
				int loc = 0; 

				vector< int * >::iterator IterPos_type;
				vector< int * >::iterator IterPos_type_ring;
				vector< int * >::iterator IterPos_cnt;

				//check for the match between saved molecule and present molecule
				for ( IterPos_type = molecule_type->begin(), IterPos_type_ring = molecule_type_ring->begin(), IterPos_cnt = molecule_cnt-> begin(); \
					IterPos_type != molecule_type->end(), IterPos_type_ring != molecule_type_ring->end(), IterPos_cnt != molecule_cnt->end(); \
					++IterPos_type, ++IterPos_type_ring, ++IterPos_cnt) {
		
					int* temp_type = *IterPos_type;
					temp_type_out = IterPos_type;
					temp_cnt_out = IterPos_type;
	
					match = 0;
	
					for ( int i = 0; i < size_atomic_char; i++ ) {
						if ( atm_cnt[i] == temp_type[i] )
							match++;
					}

					if ( *(*IterPos_ring) == *(*IterPos_type_ring) )
						match++;

					if ( match == size_atomic_char + 1 ) { //count +1 which means the match of ring count.
						temp_type_out = IterPos_type;
						break;
					}
					loc++;
				}

				//matched case between saved molecule and present molecule.
	        	if ( match == size_atomic_char + 1) { 
					int *temp_add_cnt = molecule_cnt->at(loc);
					(*temp_add_cnt)++;
				}
				//dismatched case between saved molecule and present molecule.
				else {
					int *temp_add_type = new int [size_atomic_char];
					int *temp_add_cnt = new int;
					int *temp_add_type_ring = new int;
	
					for ( int i = 0; i < size_atomic_char; i++ )
						temp_add_type[i] = atm_cnt[i];

					*temp_add_type_ring = *(*IterPos_ring);
					*temp_add_cnt = 0;
					(*temp_add_cnt)++;
			
					molecule_type->push_back(temp_add_type);
					molecule_type_ring->push_back(temp_add_type_ring);
					molecule_cnt->push_back(temp_add_cnt);
		  		}
			}

		  	vector< int * >::iterator IterPos_type, IterPos_type_next;
		  	vector< int * >::iterator IterPos_type_ring, IterPos_type_ring_next;
		  	vector< int *>::iterator IterPos_cnt, IterPos_cnt_next;


		  	//sorting operation 
		  	for ( IterPos_type = molecule_type->begin(), IterPos_type_ring = molecule_type_ring->begin(), IterPos_cnt = molecule_cnt-> begin(); \
					IterPos_type != molecule_type->end(), IterPos_type_ring != molecule_type_ring->end(), IterPos_cnt != molecule_cnt->end(); \
					++IterPos_type, ++IterPos_type_ring, ++IterPos_cnt) {

				vector< int * >::iterator IterPos_type_next;
				vector< int * >::iterator IterPos_type_ring_next;
				vector< int * >::iterator IterPos_cnt_next;
			
			 	for ( IterPos_type_next=molecule_type->begin(),IterPos_type_ring_next=molecule_type_ring->begin(),IterPos_cnt_next=molecule_cnt->begin(); 
					IterPos_type_next!=(molecule_type->end()-1),IterPos_type_ring_next!=(molecule_type_ring->end()-1),IterPos_cnt_next!=(molecule_cnt->end()-1);  
					++IterPos_type_next, ++IterPos_type_ring_next, ++IterPos_cnt_next) {

					int *temp_type = *IterPos_type_next;
					int *temp_type_ring = *IterPos_type_ring_next;
					int *temp_cnt = *IterPos_cnt_next;

				
					int *temp_type_next = *(IterPos_type_next+1);
					int *temp_type_ring_next = *(IterPos_type_ring_next+1);
					int *temp_cnt_next = *(IterPos_cnt_next+1); 
			
					unsigned int swap = 0;
					unsigned int non_zero = 0;
					for ( int i = 0; i < size_atomic_char; i++ ) {

						if ( temp_type[i] == 0 && temp_type_next[i] > 0 ) {
							if ( non_zero == 1 ) swap = 0;
							else swap = 1;
						
							break;
						}
							
						else if ( temp_type[i] > 0 && temp_type_next[i] == 0 ) {
							if ( non_zero == 1 ) swap = 1;
							else swap = 0;

							break;
						}

						if ( temp_type[i] >  temp_type_next[i] ) {
							swap = 1;
							break;
						}
						else if ( temp_type[i] < temp_type_next[i] ){
							swap = 0;
							break;
						}
					
						if ( temp_type[i] > 0 && temp_type[i] > 0 ) 
							non_zero = 1;
					}

					if ( swap == 1 ) {
						int * temp = *IterPos_type_next;
						*IterPos_type_next = *(IterPos_type_next+1);
						*(IterPos_type_next+1) = temp;

						int *temp2 = *IterPos_cnt_next;
						*IterPos_cnt_next = *(IterPos_cnt_next+1);
						*(IterPos_cnt_next+1) = temp2;

						int *temp3 = *IterPos_type_ring_next;
						*IterPos_type_ring_next = *(IterPos_type_ring_next+1);
						*(IterPos_type_ring_next+1) = temp3;
					}

				}
	  		}
			//print result
			//report timestep and number of atoms

#if PRINT_FLAG

	  		cout << "TIMESTEP: " << timestep << endl;
 	  		cout << "NUM ATOMS: " << num_atoms << endl;	  
			
#endif

			int *timestep_tmp = new int;
			*timestep_tmp = timestep;


			timestep_list->push_back(timestep_tmp);


			for ( int i = 0; i < size_atomic_char; i++ ) {
				string temp_i = atomic_char[i];

	  			for ( int j = 0; j < size_atomic_char; j++ ) {
					string temp_j = atomic_char[j];	
					//if ( issame(atomic_char[i],atomic_char[j] ) ){
					if ( temp_i.compare(temp_j) == 0 ) {
						atom_map[i] = j;
						cov_radii[i] = atomic_radii[j];
#if PRINT_FLAG

						//cout << atomic_char[j] << ": " << cov_radii[i] << "(" << i << ")" << endl;

#endif 
						break;
					}
	  			}
	 		}

			int number_of_molecules_chem = 0;
			if ( rflag == 1 ) {
					for ( IterPos_type = molecule_type->begin(), IterPos_type_ring = molecule_type_ring->begin(), IterPos_cnt = molecule_cnt-> begin(); \
						IterPos_type != molecule_type->end(), IterPos_type_ring != molecule_type_ring->end(), IterPos_cnt != molecule_cnt->end(); \
						++IterPos_type, ++IterPos_type_ring, ++IterPos_cnt) {

							int *temp_type = *IterPos_type;
							int *temp_type_ring = *IterPos_type_ring;
							int *temp_cnt = *IterPos_cnt;

							for ( int i = 0; i < size_atomic_char; i++ ) {
								if ( temp_type[i] != 0 ) 
									cout << atomic_char[atom_map[i]] << " " << temp_type[i] << " ";  
							}
					
#if PRINT_FLAG
	 						cout << "(RING: " << *temp_type_ring << ")";
							cout << ": " << *temp_cnt << endl;
#endif
					}
			}

			else {
					int *prev_temp_type = NULL; unsigned int prev_temp_cnt = 0;
						 
					int	*temp_type;
					int	*temp_type_ring;
					int	*temp_cnt;


				  	vector< int * >::iterator IterPos_type_list;
					vector< int * >::iterator IterPos_cnt_list_tmp; 
					int in_list = 0;


					for ( IterPos_type = molecule_type->begin(), IterPos_type_ring = molecule_type_ring->begin(), IterPos_cnt = molecule_cnt-> begin(); \
						IterPos_type != molecule_type->end(), IterPos_type_ring != molecule_type_ring->end(), IterPos_cnt != molecule_cnt->end(); \
						++IterPos_type, ++IterPos_type_ring, ++IterPos_cnt) {

						 
						temp_type = *IterPos_type;
						temp_type_ring = *IterPos_type_ring;
						temp_cnt = *IterPos_cnt;

						if ( prev_temp_type != NULL ) {

							int same_num = 0;
							for ( int i = 0; i < size_atomic_char; i++ ) {
								if ( prev_temp_type[i] == temp_type[i] ) {
									same_num++;
								}
							}
					
							if ( same_num != size_atomic_char ) {
		
								/*****************************************/	

								in_list = 0;
								int loc = 0;
								if ( molecule_type_list->size() != 0 ) {
										for ( IterPos_type_list = molecule_type_list->begin(); IterPos_type_list != molecule_type_list->end(); ++IterPos_type_list) {
									
												int *temp_type_list = *IterPos_type_list;
												
												int same_num2 = 0;
												for ( int i = 0; i < size_atomic_char; i++ ) {
													if ( temp_type_list[i] == prev_temp_type[i] ) {

														same_num2++;
													}

												}
												if ( same_num2 == size_atomic_char ) {

													in_list = 1;
													break;
												}
												loc++;
									
										}

								}
								int *temp_add_cnt;
								if ( in_list == 1 ) {
									temp_add_cnt = molecule_cnt_list_tmp->at(loc);
									*temp_add_cnt = prev_temp_cnt;

								}
								else {
									temp_add_cnt = new int;
									*temp_add_cnt = prev_temp_cnt;
								
									int *temp_add_type = new int [size_atomic_char];
	
									for ( int i = 0; i < size_atomic_char; i++ )
										temp_add_type[i] = prev_temp_type[i];

							
									molecule_type_list->push_back(temp_add_type);
									molecule_cnt_list_tmp->push_back(temp_add_cnt);

								}

#if PRINT_FLAG

								/************************************************/
								for ( int i = 0; i < size_atomic_char; i++ ) {
									if ( prev_temp_type[i] != 0 ) 
									cout << atomic_char[atom_map[i]] << " " << prev_temp_type[i] << " ";  
								}
								printf(": %d\n",prev_temp_cnt);
#endif
								number_of_molecules_chem++;
								//cout << "(RING: " << *temp_type_ring << ")";
								prev_temp_cnt = 0;
							}
							prev_temp_cnt += *temp_cnt;

						}
						else {
							prev_temp_cnt += *temp_cnt;
							
						}
							
						
						prev_temp_type = temp_type;


					}
					

					if ( prev_temp_type != NULL ) {


						in_list = 0;
						int loc = 0;
						if ( molecule_type_list->size() != 0 ) {
							
								for ( IterPos_type_list = molecule_type_list->begin(); IterPos_type_list != molecule_type_list->end(); ++IterPos_type_list) {
									int *temp_type_list = *IterPos_type_list;
									
									int same_num2 = 0;
									for ( int i = 0; i < size_atomic_char; i++ ) {
										if ( temp_type_list[i] == prev_temp_type[i] ) {
											same_num2++;
										}
									}
									
									if ( same_num2 == size_atomic_char ) {

										in_list = 1;
										break;
									}
									loc++;
									
								}

						}

						int *temp_add_cnt;
						if ( in_list == 1 ) {
							temp_add_cnt = molecule_cnt_list_tmp->at(loc);
							*temp_add_cnt = prev_temp_cnt;

						}
						else {

							temp_add_cnt = new int;
							*temp_add_cnt = prev_temp_cnt;
						//}

							int *temp_add_type = new int [size_atomic_char];
	
							for ( int i = 0; i < size_atomic_char; i++ )
								temp_add_type[i] = prev_temp_type[i];

							molecule_type_list->push_back(temp_add_type);
							molecule_cnt_list_tmp->push_back(temp_add_cnt);

						}
					
#if PRINT_FLAG

						for ( int i = 0; i < size_atomic_char; i++ ) {
							if ( prev_temp_type[i] != 0 ) 
								cout << atomic_char[atom_map[i]] << " " << prev_temp_type[i] << " ";  
						}
						//cout << "(RING: " << *temp_type_ring << ")";
						cout << ": " << prev_temp_cnt << endl;

#endif
						number_of_molecules_chem++;
						molecule_cnt_list->push_back(molecule_cnt_list_tmp);
					}


			}

#if FPRINT_FMOL
			fprintf(fmol,"Bond order cutoff:0.2500\n");
			fprintf(fmol,"Iteration Freq. Molecular formula               Molecular mass\n");

#endif
	
#if FPRINT_FCHEM		
			fprintf(fchem,"TIMESTEP %11d\n",timestep);
			fprintf(fchem,"CELL PARAMETERS %11.4f%11.4f%11.4f\n",box_x, box_y, box_z);
			fprintf(fchem,"TOTAL MOLECULES %11d\n",number_of_molecules_chem);			
#endif	

			string buf ; stringstream intStr; string tempstr;
			//vector< int * >::iterator IterPos_type_list;
			vector < vector < int * > * >::iterator IterPos_cnt_list;

			int number_of_molecules = 0; int number_of_atoms = 0; float system_mass = 0;
			int index = 0; int mol_index = 1;

			for ( IterPos_type_list = molecule_type_list->begin(); IterPos_type_list != molecule_type_list->end(); ++IterPos_type_list) {
	
				int *temp_type_list = *IterPos_type_list;
				int *temp_cnt = molecule_cnt_list_tmp->at(index++);


				buf = ""; 
				float molecule_mass = 0;
				for ( int i = 0; i < size_atomic_char; i++ ) {
					number_of_atoms += (*temp_cnt)*(temp_type_list[i]);			
					molecule_mass += 0; //(*temp_cnt)*atomic_masses[i]*temp_type_list[i];
					if ( temp_type_list[i] != 0 ) {
						intStr.clear();
						intStr << temp_type_list[i];
						tempstr = intStr.str();
						intStr.str("");
						buf = buf + atomic_char[atom_map[i]] + tempstr;
					
					}
				}
				system_mass += molecule_mass;
				number_of_molecules += *temp_cnt;

				if (*temp_cnt > 0){
#if FPRINT_FMOL					
					fprintf(fmol,"%8d%4d x  %-17s               %13.4f\n",timestep,*temp_cnt,buf.c_str(),molecule_mass);  
#endif

#if FPRINT_FCHEM			
					fprintf(fchem, "%8d%11s%8d\n",mol_index++,buf.c_str(),*temp_cnt);
#endif
				}
				
			}

			int num_atom_saved = 0;

			int mol_ind_index = 1;
			/* Print information of molecule */
	 		for ( IterPos = molecule_list->begin(), IterPos_ring = molecule_list_ring->begin(); \
				IterPos != molecule_list->end(), IterPos_ring != molecule_list_ring->end(); \
				++IterPos, ++IterPos_ring ) {

				vector < int >* temp = *IterPos;

				//initialization of molecular array
				for ( int i = 0; i < size_atomic_char; i++ )
					atm_cnt[i] = 0;
	

				float COM_x = 0; float COM_y = 0; float COM_z = 0;
	
				int num_atom_mol = 0;
				//assign molecular array
				for ( vector < int >::iterator subIterPos = temp->begin(); subIterPos != temp->end(); ++subIterPos ){
					atm_cnt[type[*subIterPos]-1]++;	
					COM_x += coord_x[*subIterPos]; COM_y += coord_y[*subIterPos]; COM_z += coord_z[*subIterPos];		
					num_atom_mol++;
					//fprintf(stdout,"%5d%5d%5d%11.4f%11.4f%11.4f\n",10,*subIterPos,type[*subIterPos],coord_x[*subIterPos],coord_y[*subIterPos],coord_z[*subIterPos]);
				}

				COM_x /= num_atom_mol; COM_y /= num_atom_mol; COM_z /= num_atom_mol;



				//vector< int * >::iterator temp_type_out = molecule_type->begin();
				//vector< int * >::iterator temp_type_ring_out =molecule_type_ring->begin();
				//vector< int * >::iterator temp_cnt_out = molecule_cnt->begin();
		
				int loc = 0; 

				vector< int * >::iterator IterPos_type;
				vector< int * >::iterator IterPos_type_ring;
				vector< int * >::iterator IterPos_cnt;

				int metal_flag = 0;

				//check for the match between saved molecule and present molecule
				for ( IterPos_type = molecule_type->begin(), IterPos_type_ring = molecule_type_ring->begin(), IterPos_cnt = molecule_cnt-> begin(); \
					IterPos_type != molecule_type->end(), IterPos_type_ring != molecule_type_ring->end(), IterPos_cnt != molecule_cnt->end(); \
					++IterPos_type, ++IterPos_type_ring, ++IterPos_cnt) {
		
					int* temp_type = *IterPos_type;
					//temp_type_out = IterPos_type;
					//temp_cnt_out = IterPos_type;
		

					match = 0;
	
					for ( int i = 0; i < size_atomic_char; i++ ) {
						if ( atm_cnt[i] == temp_type[i] ){
							match++;

							if ( atm_cnt[i] > 0 ){	
							if (i != map_atom_number("H",size_atomic_char)  && \
								i != map_atom_number("C",size_atomic_char)  && \
								i != map_atom_number("N",size_atomic_char)  && \
								i != map_atom_number("O",size_atomic_char)  && \
								i != map_atom_number("P",size_atomic_char)  && \
								i != map_atom_number("S",size_atomic_char) ){
									metal_flag = 1;
							}
							}
						}
					}

					//if ( *(*IterPos_ring) == *(*IterPos_type_ring) )
					//	match++;

					if ( match == size_atomic_char ) { //count +1 which means the match of ring count.
						//temp_type_out = IterPos_type;

						if (metal_flag == 1) write_structure_on = 1;


						break;
					}
					loc++;
				}
				//matched case between saved molecule and present molecule.

				int ii = 1;


	        	if ( match == size_atomic_char ) { 
					//int *temp_add_cnt = molecule_cnt->at(loc);
					//(*temp_add_cnt)++;

#if FPRINT_FCHEM					
					fprintf(fchem,"[MOL] TOT_MOL_INDEX | MOL_INDEX | COM_X | COM_Y | COM_Z\n");
					fprintf(fchem,"[MOL] %5d%5d%5d%11.4f%11.4f%11.4f\n",loc+1,mol_ind_index,num_atom_mol,COM_x,COM_y,COM_z);
					fprintf(fchem,"[ATM] MOL_INDEX | ATOM_INDEX | ATOM_TYPE | COORD_X | COORD_Y | COORD_Z\n");
#endif
					for ( vector < int >::iterator subIterPos = temp->begin(); subIterPos != temp->end(); ++subIterPos ){
#if FPRINT_FCHEM
						fprintf(fchem,"[ATM] %5d%5d%5d%11.4f%11.4f%11.4f\n",mol_ind_index,*subIterPos+1,type[*subIterPos],coord_x[*subIterPos],coord_y[*subIterPos],coord_z[*subIterPos]);
#endif

						if (write_structure_on==1){
							coord_x_saved[num_atom_saved] = coord_x[*subIterPos];
							coord_y_saved[num_atom_saved] = coord_y[*subIterPos];
							coord_z_saved[num_atom_saved] = coord_z[*subIterPos];
							type_saved[num_atom_saved] = type[*subIterPos];
							num_atom_saved++;
						}


					

					}

#if FPRINT_FCHEM
					fprintf(fchem,"\n");
#endif
					mol_ind_index++;

					write_structure_on = 0;
				}

			}
#if FPRINT_FCHEM
			fprintf(fchem," TOTAL MOLECULES%11d\n",number_of_molecules);

			fclose(fchem);
#endif



	
#if FPRINT_FXYZ
			//if (write_structure_on==1){
			fprintf(fxyz,"%d\n",num_atom_saved);
			fprintf(fxyz,"%s\n",mol_name.c_str());
			//}
#endif

#if FPRINT_FNEW
			
			//if (write_structure_on==1){
			fprintf(fcif_mol,"Molecule_name: %s\n",mol_name.c_str());
			fprintf(fcif_mol," Coord_Info: Listed Cartesian None\n");
			fprintf(fcif_mol,"%12d\n",num_atom_saved);

			//	}
#endif


#if FPRINT_FNEWCIF

	ifstream file(argv[3]);
	string line, col1, col2, col3, col4, col5, col6, col7, col8, col9, col10;

	istringstream ss;
	int num_newline = 0;
	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
			num_newline++;

			ss.str(line);
			ss >> col1 >> col2;
			ss.clear();
			if ( num_newline < 30 ) 
				fprintf(fnewcif,"%s\n",line.c_str());

		}

	}
	file.close();

#endif



			for( int ss = 0; ss < num_atom_saved; ss++ ) {
#if FPRINT_FXYZ
		//	if (write_structure_on==1){
				fprintf(fxyz,"%-5s %-8.3f%-8.3f%-8.3f\n",atomic_char[type_saved[ss]-1].c_str(),coord_x_saved[ss],coord_y_saved[ss],coord_z_saved[ss]);

		//	}
#endif



#if FPRINT_FNEW
					
		//	if (write_structure_on==1){
				fprintf(fcif_mol,"%5d %8.5f %8.5f %8.5f   %-11s0.00  0  0\n",ss+1, atomic_char[type_saved[ss]-1].c_str(),coord_x_saved[ss],coord_y_saved[ss],coord_z_saved[ss],atomic_char[type_saved[ss]-1].c_str());

		//	}
#endif
	
#if FPRINT_FNEWCIF
					
		//	if (write_structure_on==1){
				fprintf(fnewcif,"%7s%5s%10.5f%10.5f%10.5f\n",atomic_char[type_saved[ss]-1].c_str(),atomic_char[type_saved[ss]-1].c_str(),coord_x_saved[ss],coord_y_saved[ss],coord_z_saved[ss],atomic_char[type_saved[ss]-1].c_str());

		//	}
#endif

			}

#if FPRINT_FNEW	

			fprintf(fcif_mol,"\n\n\n");
			fprintf(fcif_mol,"    Fundcell_Info: Listed\n");
			fprintf(fcif_mol,"%15.5f%15.5f%15.5f\n",box_x,box_y,box_z);
			fprintf(fcif_mol,"%15.5f%15.5f%15.5f\n",alpha,beta,gamma);
			fprintf(fcif_mol,"%15.5f%15.5f%15.5f\n",0.0,0.0,0.0);
			fprintf(fcif_mol,"%15.5f%15.5f%15.5f\n",box_x,box_y,box_z);
#endif

#if FPRINT_FXYZ
			fclose(fxyz);
#endif
			//fclose(fcif);
#if FPRINT_FNEW
			fclose(fcif_mol);
#endif

#if FPRINT_FNEWCIF
			fclose(fnewcif);
#endif


#if FPRINT_FMOL
			fprintf(fmol," Total number of molecules: %d\n",number_of_molecules);
			fprintf(fmol," Total number of atoms: %d\n",number_of_atoms);
			fprintf(fmol," Total system mass:   %.0f\n",system_mass); 
		
			fclose(fmol);
#endif



	
			delete molecule_list;
			delete molecule_list_ring;
			delete molecule_type;
			delete molecule_type_ring;
			delete molecule_cnt; 
	 		 
	  		for ( int i = 0; i < num_atoms; i++ ) {
				delete [] mat_atm[i];
	  		}
	  		delete [] mat_atm;




			//delete molecule_cnt_list_tmp;
			
		} //while (file.good())


		// Construct data structure of created molecules

	}//if (file.is_open())

#if FPRINT_FOUT
	fprintf(fout, "%11s", "TIMESTEP.");
	
	

	string buf ; stringstream intStr; string tempstr;
	vector< int * >::iterator IterPos_type_list;
	int *temp_type_list;
	for ( IterPos_type_list = molecule_type_list->begin(); IterPos_type_list != molecule_type_list->end(); ++IterPos_type_list) {
		
		string buf ; stringstream intStr; string tempstr;
		temp_type_list = *IterPos_type_list;

		buf = ""; 
		
		for ( int i = 0; i < size_atomic_char; i++ ) {
			
			if ( temp_type_list[i] != 0 ) {
					intStr.clear();
					intStr << temp_type_list[i];
					tempstr = intStr.str();
					intStr.str("");
					buf = buf + atomic_char[atom_map[i]] + tempstr;
					
			}
		}
		fprintf(fout,"%15s",buf.c_str());

	}
	

	fprintf(fout,"\n");

	int *temp_cnt_list;

	vector < vector < int * > * >::iterator IterPos_cnt_list;
	vector < int * >::iterator IterPos_timestep_list;
		
	int index = 0;
	
	for ( IterPos_timestep_list = timestep_list->begin(), IterPos_cnt_list = molecule_cnt_list->begin(); IterPos_timestep_list != timestep_list->end(), IterPos_cnt_list != molecule_cnt_list->end(); ++IterPos_timestep_list, ++IterPos_cnt_list) {

		int *temp_timestep = timestep_list->at(index++);
		fprintf(fout, "%11d",*temp_timestep);
	
	

		vector< int * >::iterator IterPos_cnt;
		int index2 =0;


		if ( zflag == 0 ) {	
				for ( IterPos_cnt = (*IterPos_cnt_list)->begin(); IterPos_cnt != (*IterPos_cnt_list)->end(); ++IterPos_cnt ) {
					int *temp_cnt = (*IterPos_cnt_list)->at(index2++);

					fprintf(fout, "%15d",*temp_cnt);

				}
		}
		else {
				IterPos_cnt = (*IterPos_cnt_list)->begin();
				for ( IterPos_type_list = molecule_type_list->begin(); IterPos_type_list != molecule_type_list->end(); ++IterPos_type_list) {


					if ( index2 == (*IterPos_cnt_list)->size() ) 
						fprintf(fout, "%15d",0);

					else{
						int *temp_cnt = (*IterPos_cnt_list)->at(index2++);
						fprintf(fout, "%15d",*temp_cnt);
					}
			
				}

		}
		fprintf(fout,"\n");		
	
	}



	fclose(fout);

#endif

	file.close();
	return 0; 
}
