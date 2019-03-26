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

#define PI 3.14159265

#define FOUT_FLAG 0

#define MAX_ATOMS 100000
#define MAX_TYPE  1000

#define LINE_CELL_A  10
#define LINE_CELL_B  11
#define LINE_CELL_C  12
#define LINE_ALPHA	13
#define LINE_BETA	14
#define LINE_GAMMA	15
#define LINE_COORD_START  25 

typedef struct{
	int id; //index
	double x;
	double y;
	double z;
	int element; // C H O ...
} ATOM_TYPE;

typedef struct{
	double x;
	double y;
	double z;
} POINT;


/*********************************************************************************/
/*                              ATOMIC RADII                                     */
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



int map_atom_number ( const char* atom_str, int size_atomic_char ) {
	for ( int j = 0; j < size_atomic_char; j++ ) {
		if ( strcmp ( atom_str, atomic_char[j] ) == 0) {
			return j;
		}
	}
	return 0;
}


float convert_f2c_x ( float xx, float yy, float zz, float cell_length_a, float cell_length_b, float cell_length_c, float alpha, float beta, float gamma, float V ) {

	return cell_length_a*xx+cell_length_b*cos(gamma*PI/180.0)*yy+cell_length_c*cos(beta*PI/180.0)*zz;
	
}


float convert_f2c_y ( float xx, float yy, float zz, float cell_length_a, float cell_length_b, float cell_length_c, float alpha, float beta, float gamma, float V ) {


	return cell_length_b*sin(gamma*PI/180.0)*yy+cell_length_c*((cos(alpha*PI/180.0)-cos(beta*PI/180.0)*cos(gamma*PI/180.0))/sin(gamma*PI/180.0))*zz;
	
}


float convert_f2c_z ( float xx, float yy, float zz, float cell_length_a, float cell_length_b, float cell_length_c, float alpha, float beta, float gamma, float V ) {


	return (V/(cell_length_a*cell_length_b*sin(gamma*PI/180.0)))*zz;

}


	


using namespace std;


/**************************************************************/
int main(int argc, char *argv[]){
 
	//unsigned int size_atomic_char = sizeof(atomic_char)/sizeof(*atomic_char);	

  	if (argc != 3 ) { 
    	//tell the user how to run the program
    	std::cerr << "Usage: " << argv[0] << " INPUT_CIF OUTPUT_NAME" << endl;

   	 	return 1;
  	}

	string mark_end = "loop_";

	unsigned int size_atomic_char = sizeof(atomic_char)/sizeof(*atomic_char);	

	double cell_length_a, cell_length_b, cell_length_c;
	double alpha, beta, gamma;

	ATOM_TYPE *atoms = new ATOM_TYPE[MAX_ATOMS];

	ifstream file(argv[1]);
	string line, col1, col2, col3, col4, col5, col6, col7, col8, col9, col10;

	unsigned int num_atoms=0;
	unsigned int num_line=0, end_num_line=0;
	
	int coord_status = 1;
	
	istringstream ss;

    char str[100];

 
	FILE *output = fopen(argv[2],"w");;

	//FILE *output_xyz = fopen("testxyz_frac.xyz","w");;

	float tempx[100000], tempy[100000], tempz[100000];
	int  tempe[100000];

	int idx = 0;

	for ( int i = 0; i < 100000; i++ ) {
		tempx[i] = 0; tempy[i] = 0; tempz[i] = 0;

	}
	int flag = 0;

	int atom_geometry_start = 0;
	int atom_geometry_line = 0;


	float cart_x, cart_y, cart_z;

	float prev_frac_x, prev_frac_y, prev_frac_z;

	float diffx, diffy, diffz;
	float dist, cov_radius;

	float wflag;

	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
			num_line++;

			ss.str(line);
			ss >> col1 >> col2;
			ss.clear();
/*
			if( num_line == 3 ){

				strcpy(str,line.c_str());
				strcat(str, ".cif");
			
				output = fopen(str,"w");

				fprintf(output,line.c_str());
				fprintf(output,"\n");
				fprintf(output,"audit_creation_date              2014-11-11\n");
				fprintf(output,"audit_creation_method            'Materials Studio'\n");
				fprintf(output,"_symmetry_space_group_name_H-M    'P1'\n");
				fprintf(output,"_symmetry_Int_Tables_number       1\n");
				fprintf(output,"_symmetry_cell_setting            triclinic\n");
				fprintf(output,"loop_\n");
				fprintf(output,"_symmetry_equiv_pos_as_xyz\n");
				fprintf(output,"  x,y,z\n");


			}
*/

			if( atom_geometry_start == 0 ) {
					wflag = 0;

					if( col1.compare("_cell_length_a") == 0 ){
						//cout << "find" << endl;
						//cout << col2 << endl;
						//cout << atof(col2.c_str()) << endl;
						cell_length_a = atof(col2.c_str());
						fprintf(output,"_cell_length_a               %9.4f\n",cell_length_a);
						wflag = 1;
					}

					if( col1.compare("_cell_length_b") == 0 ){
						//cout << "find" << endl;
						//cout << col2 << endl;
						//cout << atof(col2.c_str()) << endl;
						cell_length_b = atof(col2.c_str());
						fprintf(output,"_cell_length_b               %9.4f\n",cell_length_b);
						wflag = 1;
					}

					if( col1.compare("_cell_length_c") == 0 ){
						//cout << "find" << endl;
						//cout << col2 << endl;
						//cout << atof(col2.c_str()) << endl;
						cell_length_c = atof(col2.c_str());
						fprintf(output,"_cell_length_c               %9.4f\n",cell_length_c);
						wflag = 1;
					}

					if( col1.compare("_cell_angle_alpha") == 0 ){
						//cout << "find" << endl;
						//cout << col2 << endl;
						//cout << atof(col2.c_str()) << endl;
						alpha = atof(col2.c_str());
						fprintf(output,"_cell_angle_alpha               %9.4f\n",alpha);
						wflag = 1;

					}

					if( col1.compare("_cell_angle_beta") == 0 ){
						//cout << "find" << endl;
						//cout << col2 << endl;
						//cout << atof(col2.c_str()) << endl;
						beta = atof(col2.c_str());
						fprintf(output,"_cell_angle_beta               %9.4f\n",beta);
						wflag = 1;

					}

					if( col1.compare("_cell_angle_gamma") == 0 ){
						//cout << "find" << endl;
						//cout << col2 << endl;
						//cout << atof(col2.c_str()) << endl;
						gamma = atof(col2.c_str());
						fprintf(output,"_cell_angle_gamma               %9.4f\n",gamma);
						wflag = 1;

					}

					if( col1.compare("_atom_site_label") == 0 ){
						atom_geometry_start = 1;
						atom_geometry_line = 0;
/*
						fprintf(output,"_cell_angle_alpha            %9.4f\n",alpha);
						fprintf(output,"_cell_angle_beta             %9.4f\n",beta);
						fprintf(output,"_cell_angle_gamma            %9.4f\n",gamma);
						fprintf(output,"loop_\n");
						fprintf(output,"_atom_site_label\n");
						fprintf(output,"_atom_site_type_symbol\n");
						fprintf(output,"_atom_site_fract_x\n");
						fprintf(output,"_atom_site_fract_y\n");
						fprintf(output,"_atom_site_fract_z\n");
						fprintf(output,"_atom_site_U_iso_or_equiv\n");
						fprintf(output,"_atom_site_adp_type\n");
						fprintf(output,"_atom_site_occupancy\n");
*/

					}
					if (wflag == 0)
						fprintf(output,"%s\n",line.c_str());
			}

			else {
				if ( col1.compare("loop_") == 0 ){

					fprintf(output,"%s\n",line.c_str());
					break;
				}


				atom_geometry_line++;
				if ( atom_geometry_line > 4 ) {

	
					ss.str(line);
					ss >> col1 >> col2 >> col3 >> col4 >> col5;
					ss.clear();
				
					//cout << "string size: " << strlen(col1.c_str()) << endl;
/*
					char *tempstr = strdup(col1.c_str());

					char *name=(char*)malloc(10*sizeof(char));
					//int start = 0;
					for ( int i = 0; i < strlen(col1.c_str()); i++ ) {


						if ( (tempstr[i] >=65 && tempstr[i] <= 90) || (tempstr[i] >=97 && tempstr[i] <=122 ) ) {

							if (start == 0) {
							
								`strcpy(name,(const char)tempstr[i]);
								start = 1;
							}
							else
								strcat(name,(const char)tempstr[i]);

							name[i] = tempstr[i];
						}

					}
*/


					//if ( atof(col3.c_str()) <= cell_length_a ) {
					//if ( atof(col4.c_str()) <= cell_length_b ) {
					//if ( atof(col5.c_str()) <= cell_length_c ) {


					//cart_x = atof(col3.c_str());
					//cart_y = atof(col4.c_str());
					//cart_z = atof(col5.c_str());

					

/*
					float V = cell_length_a*cell_length_b*cell_length_c*sqrt(1-cos(alpha*PI/180.0)*cos(alpha*PI/180)-cos(beta*PI/180.0)*cos(beta*PI/180)-cos(gamma*PI/180.0)*cos(gamma*PI/180.0)*cos(gamma*PI/180.0)+2*cos(alpha*PI/180.0)*cos(beta*PI/180.0)*cos(gamma*PI/180.0));  					
					float frac_x = atof(col3.c_str());
					float frac_y = atof(col4.c_str());
					float frac_z = atof(col5.c_str());


					if ( frac_x == prev_frac_x && frac_y == prev_frac_y && frac_z == prev_frac_z ) {
					}

					else{
										for ( int i = 0; i < 2; i++ ) {
										for ( int j = 0; j < 2; j++ ) {
										for ( int k = 0; k < 2; k++ ) {
									
											float tx = convert_f2c_x ( frac_x+(float)i, frac_y+(float)j, frac_z+(float)k, cell_length_a, cell_length_b, cell_length_c, alpha, beta, gamma, V );
											float ty = convert_f2c_y ( frac_x+(float)i, frac_y+(float)j, frac_z+(float)k, cell_length_a, cell_length_b, cell_length_c, alpha, beta, gamma, V );
											float tz = convert_f2c_z ( frac_x+(float)i, frac_y+(float)j, frac_z+(float)k, cell_length_a, cell_length_b, cell_length_c, alpha, beta, gamma, V );

										
											fprintf(output,"%7s%5s%10.5f%10.5f%10.5f\n",col2.c_str(),col2.c_str(),tx,ty,tz);
	



										}
										}
										}
*/
						float frac_x = atof(col3.c_str());
						float frac_y = atof(col4.c_str());
						float frac_z = atof(col5.c_str());


					if ( frac_x == prev_frac_x && frac_y == prev_frac_y && frac_z == prev_frac_z ) {
					}

					else{


						fprintf(output,"%7s%5s%10.5f%10.5f%10.5f\n",col2.c_str(),col2.c_str(),frac_x,frac_y,frac_z);

						prev_frac_x = frac_x; prev_frac_y = frac_y; prev_frac_z = frac_z;
					}
/*
					float V = cell_length_a*cell_length_b*cell_length_c*sqrt(1-cos(alpha*PI/180.0)*cos(alpha*PI/180)-cos(beta*PI/180.0)*cos(beta*PI/180)-cos(gamma*PI/180.0)*cos(gamma*PI/180.0)*cos(gamma*PI/180.0)+2*cos(alpha*PI/180.0)*cos(beta*PI/180.0)*cos(gamma*PI/180.0));  					

					float frac_x = (1/cell_length_a)*cart_x+(-cos(gamma*PI/180.0)/(cell_length_a*sin(gamma*PI/180.0)))*cart_y+((cell_length_b*cell_length_c*cos(gamma*PI/180.0)*(cos(alpha*PI/180.0)-cos(beta*PI/180.0)*cos(gamma*PI/180.0))/sin(gamma*PI/180.0))-cell_length_b*cell_length_c*cos(beta*PI/180.0)*sin(gamma*PI/180.0))*(1/V)*cart_z;
					float frac_y = (1/(cell_length_b*sin(gamma*PI/180.0)))*cart_y+(-cell_length_a*cell_length_c*(cos(alpha*PI/180.0)-cos(beta*PI/180.0)*cos(gamma*PI/180.0))/(V*sin(gamma*PI/180.0)))*cart_z;
					float frac_z = (cell_length_a*cell_length_b*sin(gamma*PI/180.0)/V)*cart_z;					

*/

					//printf("x: %f, y: %f, z: %f\n",frac_x,frac_y,frac_z);

/*
					if (start==0){
						fprintf(output,"%7s%5s%10.2f%10.2f%10.2f\n",col1.c_str(),col1.c_str(),frac_x,frac_y,frac_z);
										
						fprintf(output_xyz,"%7s%10.5f%10.5f%10.5f\n",col1.c_str(),cart_x,cart_y,cart_z);

						tempx[idx] = cart_x; tempy[idx] = cart_y; tempz[idx] = cart_z; tempe[idx] = map_atom_number(col1.c_str(),size_atomic_char);
						idx++;
						start = 1;
						prev_cart_x = cart_x; prev_cart_y = cart_y; prev_cart_z = cart_z;
					}
*/
					//else{
					//printf("aaa\n");


					//if (prev_cart_x==cart_x&&prev_cart_y==cart_y&&prev_cart_z==cart_z) { //remove duplicates
						

					//}
					//else{
					


				//	}
				//	}
				//	}

					//}
					//prev_cart_x = cart_x; prev_cart_y = cart_y; prev_cart_z = cart_z;
					//free(name);

					//}


				} 	
				else {

					fprintf(output,"%s\n",line.c_str());
				}



			}


		}
	
	}
	file.close();	


	//fpritnf(output,"data_\n");

	//printf("Number of Atoms: %d\n",num_atoms);
	//printf("Number of Type: %d\n",nspecies);


	fclose(output);
	//fclose(output_xyz);
	return 0; 
}
