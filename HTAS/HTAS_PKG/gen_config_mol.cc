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


#define MAX_ATOMS 100000

#define LINE_CELL_A  9 //10
#define LINE_CELL_B  10 //11
#define LINE_CELL_C  11 //12
#define LINE_ALPHA	12 //13
#define LINE_BETA	13 //14
#define LINE_GAMMA	14 //15
#define LINE_COORD_START  30 //25 

typedef struct{
	int id; //index
	double x;
	double y;
	double z;
	int element; // C H O ...
	float mass;
} ATOM_TYPE;
/*********************************************************************************/
/*                              ATOMIC INFO.                                     */
/*********************************************************************************/

const double atomic_radii[118] = {1.2, 1.4, 1.82, 1.53, 1.92, 1.7, 1.55, 1.52, 1.47, 1.54,
				2.27, 1.73, 1.84, 2.1, 1.8, 1.8, 1.75, 1.88, 2.75, 2.31,
				2.11, 0.0,  0.0,  0.0, 0.0, 0.0,  0.0, 1.63, 1.4, 1.39,
				1.87, 2.11, 1.85, 1.9, 1.85, 2.02, 3.03, 2.49, 0.0, 0.0,       
				 0.0, 0.0,  0.0, 0.0,  0.0, 1.63,  1.72, 1.58, 1.93, 2.17,
				2.06, 2.06, 1.98, 2.16, 3.43, 2.68,  0.0, 0.0, 0.0,  0.0, 
				 0.0, 0.0, 0.0,  0.0,  0.0, 0.0, 0.0,  0.0, 0.0, 0.0,
				 0.0, 0.0, 0.0,  0.0,  0.0, 0.0, 0.0,  1.75, 1.66, 1.55,
				1.96, 2.02, 2.07, 1.97, 2.02, 2.2, 3.48, 2.83, 0.0, 0.0,
				0.0, 1.86,   0.0, 0.0, 0.0,  0.0,  0.0, 0.0, 0.0, 0.0,
				 0.0, 0.0, 0.0,  0.0,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
				0.0, 0.0, 0.0,  0.0,  0.0, 0.0, 0.0, 0.0}; 	 

const double atomic_mass[118] = {1.00794, 4.002602, 6.941, 9.012182, 10.811, 12.0107, 14.00674, 15.9994, 18.9984032, 20.1797,
				22.98976928, 24.3050, 26.9815386, 28.0855, 30.973762, 32.066, 35.4527, 39.948, 39.0983, 40.078,
				44.955912, 47.867, 50.9415, 51.9961, 54.938045, 55.845, 58.933195, 58.6934, 63.546, 65.39, 
				69.723, 72.61, 74.92160, 78.96, 79.904, 83.80, 85.4678, 87.62, 88.90585, 91.224,
				92.90638, 95.94, 97.9072, 101.07, 102.90550, 106.42, 107.8682, 112.411, 114.818, 118.710, 
				121.760, 127.60, 126.90447, 131.29, 132.9054519, 137.327, 178.49, 180.94788, 183.84, 186.207, 
				190.23, 192.217, 195.084, 196.966569, 200.59, 204.3833, 207.2, 208.98040, 208.9824, 209.9871, 
				222.0176, 138.90547, 140.116, 140.90765, 144.242, 144.9127, 150.36, 151.964, 157.25, 158.92535, 
				162.500, 164.93032, 167.259, 168.93421, 173.04, 174.967, 223.0197, 226.0254, 263.1125, 262.1144, 
				266.1219, 264.1247, 269.1341, 268.1388, 272.1463, 272.1535, 277.0, 284.0, 289.0, 288.0, 
				292.0, 292.0, 101.3, 227.0277, 232.03806, 231.03588, 238.02891, 237.0482, 244.0642, 243.0614, 
				247.0703, 247.0703, 251.0796, 252.0830, 257.0951, 258.0984, 259.1011, 262.110};



const char* atomic_char[70] = {"H", "He", "Li", "Be", "B", "C" , "N", "O", "F", "Ne",
				"Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar", "K", "Ca",
				"Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn",
				"Ga", "Ge", "As", "Se", "Br", "Kr", "Rb", "Sr", "Y", "Zr",       
				"Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn",
				"Sb", "Te", "I", "Xe", "Cs", "Ba",  "*", "Hf", "Ta",  "W", 
				"Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po"};




using namespace std;



int map_atom_number ( const char* atom_str, int size_atomic_char ) {
	for ( int j = 0; j < size_atomic_char; j++ ) {
		if ( strcmp ( atom_str, atomic_char[j] ) == 0) {
			return j;
		}
	}
	return 0;
}

int main(int argc, char *argv[]){
 

    //Tell the user how to run the program
  	if (argc != 4) { 
    	std::cerr << "Usage: " << argv[0] << " INPUT_CIF INPUT_XYZ MOL_NAME" << endl;
   	 	return 1;
  	}


	unsigned int size_atomic_char = sizeof(atomic_char)/sizeof(*atomic_char);	

	double cell_length_a, cell_length_b, cell_length_c;
	double alpha, beta, gamma;

	ATOM_TYPE *atoms = new ATOM_TYPE[MAX_ATOMS];


	string line, col1, col2, col3, col4, col5, col6, col7, col8;

	unsigned int num_atoms=0;
	unsigned int num_line=0;
	
	istringstream ss;

	int ii=0;
	double tempf;
	
	ifstream file(argv[1]);
	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
			num_line++;
			if (num_line == 3){
				ss.str (line);
				ss >> col1 >> col2;
				ss.clear();

			}

			if (num_line == LINE_CELL_A ){
				ss.str (line);
				ss >> col1 >> col2;
				ss.clear();

				cell_length_a = atof(col2.c_str());
			}
			else if (num_line == LINE_CELL_B ){
				ss.str (line);
				ss >> col1 >> col2;
				ss.clear();

				cell_length_b = atof(col2.c_str());
			}
			else if (num_line == LINE_CELL_C ){
				ss.str (line);
				ss >> col1 >> col2;
				ss.clear();

				cell_length_c = atof(col2.c_str());
			}

			else if (num_line == LINE_ALPHA ){
				ss.str (line);
				ss >> col1 >> col2;
				ss.clear();

				alpha = atof(col2.c_str());
			}
			else if (num_line == LINE_BETA ){
				ss.str (line);
				ss >> col1 >> col2;
				ss.clear();

				beta = atof(col2.c_str());
			}
			else if (num_line == LINE_GAMMA ){
				ss.str (line);
				ss >> col1 >> col2;
				ss.clear();

				gamma = atof(col2.c_str());
			}
	
	}
	file.close();


	ifstream file(argv[2]);

	num_line = 0;
	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
			num_line++;
			if (num_line == 1){
				ss.str (line);
				ss >> col1 ;
				ss.clear();
				num_atoms = atoi(col1.c_str());
			}

			else if (num_line >= 3 ) {
					ss.str (line);

					ss >> col1 >> col2 >> col3 >> col4 >> col5;
					ss.clear();
					atoms[ii].id = ii+1;
					atoms[ii].element = map_atom_number(col1.c_str(), size_atomic_char); 
					atoms[ii].mass =  atomic_mass[atoms[ii].element];

					tempf = atof(col2.c_str());
					atoms[ii].x = tempf;
					tempf = atof(col3.c_str());
					atoms[ii].y = tempf;
					tempf = atof(col4.c_str());
					atoms[ii].z = tempf;
					ii++;
				}

				if(ii == num_atoms) break;
			}
		
		}
	
	}
	file.close();


	printf("Number of Atoms: %d\n",num_atoms);

	char str[100];
	strcpy(str,argv[3]);
	strcat(str,".mol");


	char strxyz[100];
	strcpy(strxyz,argv[3]);
	strcat(strxyz,".xyz");

	printf("molecule file name: %s\n",str);

	FILE *file_mol = fopen(str,"w");

	fprintf(file_mol,"Molecule_name: %s\n\n",argv[3]);
	fprintf(file_mol," Coord_Info: Listed Cartesian Rigid\n");
	fprintf(file_mol,"%12d\n",num_atoms);
	for (int i = 0; i < num_atoms; i++ ) {
		float xx = atoms[i].x; float yy = atoms[i].y; float zz = atoms[i].z;
		fprintf(file_mol,"%5d %8.5f %8.5f %8.5f   %-11s0.00  0  0\n",i+1, xx, yy, zz, atomic_char[atoms[i].element]); 

	}

	
	fprintf(file_mol,"\n\n\n");
	fprintf(file_mol,"    Fundcell_Info: Listed\n");
	fprintf(file_mol,"%15.5f%15.5f%15.5f\n",cell_length_a,cell_length_b,cell_length_c);
	fprintf(file_mol,"%15.5f%15.5f%15.5f\n",alpha,beta,gamma);
	fprintf(file_mol,"%15.5f%15.5f%15.5f\n",0.0,0.0,0.0);
	fprintf(file_mol,"%15.5f%15.5f%15.5f\n",cell_length_a,cell_length_b,cell_length_c);

 	fclose(file_mol);

	return 0; 
}
