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
#define FIX_LAYER 2
using namespace std;

typedef struct{
	string name;
	float x;
	float y;
	float z;
	int fix_tag;
} ATOM;

void make_positive(int *l, int n_layers){

	if (*l < 0 ){

		*l = *l + n_layers;
		 make_positive(l,n_layers);

		
	}

}



int main(int argc, char *argv[])
{
  	// Check argument
  	if (argc != 8) { 
    		std::cerr << "Usage: " << argv[0] << " POSCAR VECTOR VACUUM_H LAYERS_N EXPAND_X_TIMES EXPAND_Y_TIMES OPT_SQRT(3) " << endl;

   	 	return 1;
  	}

	float vec_p[3];

	float scale;
	float vec_a[3], vec_b[3], vec_c[3]; 
	string str1, str2;
	int num1, num2, tot_num;
	
	float vacuum_h = atof(argv[3]);
	int layers_n = atoi(argv[4]);


  	// Check argument
  	if (layers_n < FIX_LAYER) { 
    		std::cerr << " Set the number of layers more than the number of fixed layer " << FIX_LAYER << endl;

   	 	return 1;
  	}

	int exX_max = atoi(argv[5]);
	int exY_max = atoi(argv[6]);

	int orth_flag = 1;

	ATOM atoms[MAX_COUNT], atomsOn[MAX_COUNT], atomsNew[MAX_COUNT], atomsFin[MAX_COUNT], atomsConfig[MAX_COUNT];

	int i = 0;
	int ii = 0;
	unsigned numVecj = 0;
	
	double cutoff_value = 0.0001;
	double cutoff_value2 = 0.001;

	tot_num = 0;

	if ( atoi(argv[2]) == 1 ) {vec_p[0] = 0.0; vec_p[1] = 0.0; vec_p[2] = 1.0;}
	else if ( atoi(argv[2]) == 2 ) {vec_p[0] = 0.0; vec_p[1] = 1.0; vec_p[2] = 1.0;}
	else if ( atoi(argv[2]) == 3 ) {vec_p[0] = 1.0; vec_p[1] = 1.0; vec_p[2] = 1.0;}


	if ( atoi(argv[2]) == 2 ) { exX_max = 3; exY_max = 1; }
	if ( atoi(argv[7]) == 1 && atoi(argv[2]) == 3 ) { exX_max = 2; exY_max = 2; }

  	istringstream ss;
	string line, col1, col2, col3, col4, col5, col6, col7, col8, col9;

	string token;
	vector<string> linesplitvec;

	string strVec[MAX_COUNT]; unsigned int strVeci = 0;
	int numVec[MAX_COUNT]; unsigned int numVeci = 0;
	int numVecFin[MAX_COUNT];

	unsigned int atomsFinN ;
	unsigned int atomsConfigN;

	float aa, bb, cc;


	int layers_idx; 
	float z_temp, z_diff;


	int duplicate_flag;

	bool read_status;
  	int num_line;

	// Read all atoms information
	ifstream POSCARIN(argv[1]);
	read_status = true;
	num_line = 0;
	if ( POSCARIN.is_open() ) {
		while ((read_status=getline(POSCARIN,line))==true){
			num_line++;

			ss.str(line);

			if ( num_line == 2 ) {
				ss >> col1;
				ss.clear();
				scale=atof(col1.c_str());
			}
			

			if ( num_line == 3 ) {
				ss >> col1 >> col2 >> col3;
				ss.clear();
				vec_a[0]=atof(col1.c_str())*(float)(exX_max);
				vec_a[1]=atof(col2.c_str())*(float)(exX_max);
				vec_a[2]=atof(col3.c_str())*(float)(exX_max);

			}

			if ( num_line == 4 ) {
				ss >> col1 >> col2 >> col3;
				ss.clear();
				vec_b[0]=atof(col1.c_str())*(float)(exY_max);
				vec_b[1]=atof(col2.c_str())*(float)(exY_max);
				vec_b[2]=atof(col3.c_str())*(float)(exY_max);

				if ( vec_b[0] != 0 ) orth_flag = 0;
			}

			if ( num_line == 5 ) {
				ss >> col1 >> col2 >> col3;
				ss.clear();
				vec_c[0]=atof(col1.c_str());
				vec_c[1]=atof(col2.c_str());
				vec_c[2]=atof(col3.c_str());

			}

			if ( num_line == 6 ) {
				while(getline(ss, token, ' ')){
					linesplitvec.push_back(token);
					if ( token.compare("") != 0 ) {	
						strVec[strVeci++] = token;
					}
				}
				
				ss.clear();

			}

			if ( num_line == 7 ) {
				while(getline(ss, token, ' ')){
					linesplitvec.push_back(token);
					
					if ( atoi(token.c_str()) != 0 ) {
				
					numVec[numVeci++] = atoi(token.c_str());
					numVecFin[numVeci-1] = 0;
					tot_num += atoi(token.c_str());

					}
				}
	
				ss.clear();

			}

			

			if ( num_line >= 9 && num_line < 9 + tot_num ) {
				ss.str (line);
				ss >> col1 >> col2 >> col3 ;
				ss.clear();
	
				if ( i++ >= numVec[numVecj] ){
					numVecj++;
					i = 0;	

				}

				atoms[ii].name = strVec[numVecj];
				atoms[ii].x = atof(col1.c_str());
				atoms[ii].y = atof(col2.c_str());
				atoms[ii].z = atof(col3.c_str());
				
				ii++;

			}		
		}
	}


	// Choose the atoms on the plane
	float ix, iy, iz, fx, fy, fz;
	float s;
	float x, y, z;
	int o = 0;
	
	int nn;

	float theta;

	float fin_z;

	nn  = 0;
	if (vec_b[0] == 0 ) { // This is Cubic structures

		for ( int i = 0; i < tot_num; i++ ) {
			x = atoms[i].x; y = atoms[i].y; z = atoms[i].z;
			fx = x; fy = y; fz = z; 
			
			if ( x == 0.0 ) fx = 1.0;
			if ( y == 0.0 ) fy = 1.0;
			if ( z == 0.0 ) fz = 1.0;


			for ( float ix = x; ix <= fx; ix++ ) {
			for ( float iy = y; iy <= fy; iy++ ) {
			for ( float iz = z; iz <= fz; iz++ ) {
				s = vec_p[0]*ix + vec_p[1]*iy + vec_p[2]*iz;
				if ( s == 1 ) {
					atomsOn[o].x = ix; atomsOn[o].y = iy; atomsOn[o].z = iz; atomsOn[o].name = atoms[i].name;
					o++;	
				}
		
			}	
			}	
			}
		}

		float orgX = 0.0; float orgY = 0.0; float orgZ = 0.0;

		for ( int i = 0; i < o; i++ ) {
			if ( atomsOn[i].z > orgZ ) {
				orgX = atomsOn[i].x;
				orgY = atomsOn[i].y;
				orgZ = atomsOn[i].z;
			}
		}


		float max1X = 0.0; float max1Y = 0.0; float max1Z = 0.0;

		for ( int i = 0; i < o; i++ ) {
			if ( atomsOn[i].x > max1X ) {
				max1X = atomsOn[i].x;
				max1Y = atomsOn[i].y;
				max1Z = atomsOn[i].z;

			}
		}


		float max2X = 0.0; float max2Y = 0.0; float max2Z = 0.0;

		for ( int i = 0; i < o; i++ ) {
			if ( atomsOn[i].y > max2Y ) {
				max2X = atomsOn[i].x;
				max2Y = atomsOn[i].y;
				max2Z = atomsOn[i].z;

			}
		}

		float px, py, pz;
		
		float a[3][3], b[3], xx[3];
		float factor, sum;

		float p1[3], p2[3], p3[3];
		float p12, p23, p13;
		float sp1, sp2, sp3;
		float angle[3];

		float temp;
		float total_angle;

		float centerX, centerY, centerZ;


		float va[3], vb1[3], vb2[3];
		float va_vb1[3], va_vb2[3];
		float vbsq;

		float theta1, theta2, dist;
		float proj_b1, proj_b2, proj_c;

		float d, l1, l2;

		float nx, ny, nz;




		float total_vec_p = (float)(vec_p[0]+vec_p[1]+vec_p[2]);


		centerX = 1.0/(float)total_vec_p;
		centerY = 1.0/(float)total_vec_p;
		centerZ = 1.0/(float)total_vec_p;


		for ( int i = 0; i < tot_num; i++ ) {
			// Check orthogonality
			px = atoms[i].x; py = atoms[i].y; pz = atoms[i].z;
			fx = px; fy = py; fz = pz; 
			
			if ( px == 0.0 ) fx = 1.5;
			if ( py == 0.0 ) fy = 1.5;
			if ( pz == 0.0 ) fz = 1.5;

			fx = 2.0; fy = 2.0; fz = 2.0;
			for ( float ix = px; ix <= fx; ix++ ) {
			for ( float iy = py; iy <= fy; iy++ ) {
			for ( float iz = pz; iz <= fz; iz++ ) {
		
			a[0][0] = (orgX - centerX); a[0][1] = (orgY - centerY); a[0][2] = (orgZ - centerZ);
			a[1][0] = (max2X - centerX); a[1][1] = (max2Y - centerY); a[1][2] = (max2Z - centerZ); 
			a[2][0] = vec_p[0]; a[2][1] = vec_p[1]; a[2][2] = vec_p[2];

			b[0] = ix*a[0][0] + iy*a[0][1] + iz*a[0][2];
			b[1] = ix*a[1][0] + iy*a[1][1] + iz*a[1][2];
			b[2] = 1.0;
			// Gauss Elimination
			// Forward Elimination
			for ( int kk = 0; kk < 2; kk++ ) {
				for ( int ii = kk+1; ii < 3; ii++ ) {
					factor = a[ii][kk]/a[kk][kk];
					for ( int jj = kk; jj < 3; jj++ ) {
						a[ii][jj] = a[ii][jj] - factor*a[kk][jj];
					}
					b[ii] = b[ii] - factor*b[kk];
				}
			}
			xx[2] = b[2]/a[2][2];

			// Backward Elimination
			for ( int ii = 1; ii >= 0; ii-- ) {
				sum = 0;
				
				for ( int jj = ii+1; jj < 3; jj++ ){
					sum = sum + a[ii][jj]*xx[jj];

				}

				xx[ii] = (b[ii]-sum)/a[ii][ii];
			}

			// Check On-site

			p1[0] = orgX; p1[1] = orgY; p1[2] = orgZ;
			p2[0] = max1X; p2[1] = max1Y; p2[2] = max1Z;
			p3[0] = max2X; p3[1] = max2Y; p3[2] = max2Z;

			p12 = (p1[0]-p2[0])*(p1[0]-p2[0])+(p1[1]-p2[1])*(p1[1]-p2[1])+(p1[2]-p2[2])*(p1[2]-p2[2]);
			p23 = (p2[0]-p3[0])*(p2[0]-p3[0])+(p2[1]-p3[1])*(p2[1]-p3[1])+(p2[2]-p3[2])*(p2[2]-p3[2]);
			p13 = (p3[0]-p1[0])*(p3[0]-p1[0])+(p3[1]-p1[1])*(p3[1]-p1[1])+(p3[2]-p1[2])*(p3[2]-p1[2]);

			sp1 = (xx[0]-p1[0])*(xx[0]-p1[0])+(xx[1]-p1[1])*(xx[1]-p1[1])+(xx[2]-p1[2])*(xx[2]-p1[2]);
			sp2 = (xx[0]-p2[0])*(xx[0]-p2[0])+(xx[1]-p2[1])*(xx[1]-p2[1])+(xx[2]-p2[2])*(xx[2]-p2[2]);
			sp3 = (xx[0]-p3[0])*(xx[0]-p3[0])+(xx[1]-p3[1])*(xx[1]-p3[1])+(xx[2]-p3[2])*(xx[2]-p3[2]);

			if ( sp1 == 0 || sp2 == 0 || sp3 == 0 ) {
				total_angle = 360.0;

			}
			else {
				temp = (sp1+sp2-p12)/(2*sqrt(sp1)*sqrt(sp2));		
				if (temp == -1.00) temp += cutoff_value;
				angle[0] = 180*acos(temp)/M_PI;
				temp = (sp2+sp3-p23)/(2*sqrt(sp2)*sqrt(sp3));
				if (temp == -1.00) temp += cutoff_value;
				angle[1] = 180*acos(temp)/M_PI;
				temp = (sp1+sp3-p13)/(2*sqrt(sp1)*sqrt(sp3));
				if (temp == -1.00) temp += cutoff_value;
				angle[2] = 180*acos(temp)/M_PI;
				total_angle = angle[0]+angle[1]+angle[2];
			}
		

			d = sqrt((xx[0]-ix)*(xx[0]-ix)+(xx[1]-iy)*(xx[1]-iy)+(xx[2]-iz)*(xx[2]-iz));

			l1 = sqrt(xx[0]*xx[0]+xx[1]*xx[1]+xx[2]*xx[2]);
			l2 = sqrt(ix*ix+iy*iy+iz*iz); 

			float ans;
			if (fabs(total_angle-360.0) < 1 && (vec_p[0]*ix+vec_p[1]*iy+vec_p[2]*iz) > 0){

				bb = (xx[0]-orgX)*(xx[0]-orgX)+(xx[1]-orgY)*(xx[1]-orgY)+(xx[2]-orgZ)*(xx[2]-orgZ);
				cc = (max1X-orgX)*(max1X-orgX)+(max1Y-orgY)*(max1Y-orgY)+(max1Z-orgZ)*(max1Z-orgZ);
				aa = (max1X-xx[0])*(max1X-xx[0])+(max1Y-xx[1])*(max1Y-xx[1])+(max1Z-xx[2])*(max1Z-xx[2]);
			
				ans = (bb+cc-aa)/(2.0*sqrt(bb)*sqrt(cc));

				if ( ans >= 1 ) theta1 = 0.0;
				else if ( ans <= -1 ) theta1 = M_PI*0.5;
				else theta1 = acos((bb+cc-aa)/(2.0*sqrt(bb)*sqrt(cc)));

				
				if ( bb == 0 || cc == 0 ) theta1 = 0.0;

				bb = (max1X-orgX)*(max1X-orgX)+(max1Y-orgY)*(max1Y-orgY)+(max1Z-orgZ)*(max1Z-orgZ);
				cc = (max2X-max1X)*(max2X-max1X)+(max2Y-max1Y)*(max2Y-max1Y)+(max2Z-max1Z)*(max2Z-max1Z);
				aa = (max2X-orgX)*(max2X-orgX)+(max2Y-orgY)*(max2Y-orgY)+(max2Z-orgZ)*(max2Z-orgZ);

				ans = (bb+cc-aa)/(2.0*sqrt(bb)*sqrt(cc));

				if ( ans >= 1 ) theta2 = 0.0;
				else if ( ans <= -1 ) theta2 = M_PI*0.5;
				else theta2 = acos((bb+cc-aa)/(2.0*sqrt(bb)*sqrt(cc)));


				if ( bb == 0 || cc == 0 ) theta2 = 0.0;

				if ( vec_p[0] != 1 || vec_p[1] != 1 || vec_p[2] != 1 ) {
					theta2 = M_PI*0.5;

				}

				va[0] = xx[0] - orgX; va[1] = xx[1] - orgY; va[2] = xx[2] - orgZ;
				dist = sqrt(va[0]*va[0]+va[1]*va[1]+va[2]*va[2]);
			
				proj_b2 = dist * sin(theta1) / sin(theta2);
				proj_b1 = dist * cos(theta1) + proj_b2 * cos(theta2);


				vb1[0] = max1X - orgX; vb1[1] = max1Y - orgY; vb1[2] = max1Z - orgZ;
				vbsq = sqrt(vb1[0]*vb1[0]+vb1[1]*vb1[1]+vb1[2]*vb1[2]);

				proj_b1 = proj_b1 / vbsq;	
				vb2[0] = max2X - orgX; vb2[1] = max2Y - orgY; vb2[2] = max2Z - orgZ;
				vbsq = sqrt(vb2[0]*vb2[0]+vb2[1]*vb2[1]+vb2[2]*vb2[2]);

				proj_b2 = proj_b2 / vbsq;	

				proj_c = d/sqrt(vec_p[0]+vec_p[1]+vec_p[2]);		
		
				if ( proj_c < 1 ) {
			
					atomsNew[nn].x = proj_b1;
					atomsNew[nn].y = proj_b2;
					atomsNew[nn].z = proj_c;
					atomsNew[nn].name = atoms[i].name;

					nn++;

				}


				if ( vec_p[0] == 1 && vec_p[1] == 1 && vec_p[2] == 1 ) {
				if ( proj_b1 != 0.0 && proj_b1 != 1.0 && proj_b2 != 0.0 && proj_b2 != 0.0 && proj_c != 0.0 && proj_c != 0 ) {
					if ( proj_b1 != 5.0 && proj_b2 != 5.0 && proj_c != 5.0 ) {
		
						if ( proj_c < 1 ) {	
						atomsNew[nn].x = 1.0 - proj_b1;
						atomsNew[nn].y = 1.0 - proj_b2;
						atomsNew[nn].z = 1.0 - proj_c;
						atomsNew[nn].name = atoms[i].name;
						nn++;
						}
					}
	  
				}	
				}
			}

			}
			}
			}	
		

		}

		bb = (max1X-orgX)*(max1X-orgX)+(max1Y-orgY)*(max1Y-orgY)+(max1Z-orgZ)*(max1Z-orgZ);
		cc = (max2X-max1X)*(max2X-max1X)+(max2Y-max1Y)*(max2Y-max1Y)+(max2Z-max1Z)*(max2Z-max1Z);
		aa = (max2X-orgX)*(max2X-orgX)+(max2Y-orgY)*(max2Y-orgY)+(max2Z-orgZ)*(max2Z-orgZ);


		theta = acos((bb+cc-aa)/(2.0*sqrt(bb)*sqrt(cc)));

		if ( vec_p[0] != 1 || vec_p[1] != 1 || vec_p[2] != 1 ) {
			theta = M_PI*0.5;

		}

		vec_a[0] = sqrt(bb)*vec_a[0]; vec_a[1] = 0.0; vec_a[2] = 0.0;
		vec_b[0] = -1.0*sqrt(cc)*cos(theta)*vec_b[1]; vec_b[1] = sqrt(aa)*sin(theta)*vec_b[1]; vec_b[2] = 0.0;
		vec_c[0] = 0.0; vec_c[1] = 0.0;  vec_c[2] = sqrt(vec_p[0]+vec_p[1]+vec_p[2])*vec_c[2];

	} // Only Cubic structures 

	else{

		aa = vec_a[0]*vec_a[0];
		bb = aa;
		cc = vec_c[2]*vec_c[2];

		theta = asin(vec_b[1]/vec_a[0]);

		for ( int i = 0; i < tot_num; i++ ) {
			
			// Check orthogonality
			atomsNew[nn].x = atoms[i].x; atomsNew[nn].y = atoms[i].y; atomsNew[nn].z = atoms[i].z;
			atomsNew[nn].name = atoms[i].name;
			nn++;


		}

	}

	float layers[MAX_COUNT];
	int n_layers = 0;
	int n_items[MAX_COUNT];

	int flag;

	for ( int i = 0; i < nn; i++ ) {
		flag = 0;
		for ( int j = 0; j < n_layers; j++ ) {

			if ( fabs(layers[j] - atomsNew[i].z) < cutoff_value ) {
				flag = 1;
				break;
			}	
		}
		if ( flag == 0 ) layers[n_layers++] = atomsNew[i].z;
	
	}

	// Bubble sort
	float tmp;
	for ( int i = 0; i < n_layers; i++ ) {
		for ( int j = 0; j < n_layers-1; j++ ){

			
			if ( orth_flag == 1 ) {
				if ( layers[j] > layers[j+1] ) {
					tmp = layers[j];
					layers[j] = layers[j+1];
					layers[j+1] = tmp;
				}
			}
			else {
				if ( layers[j] < layers[j+1] ) {
					tmp = layers[j];
					layers[j] = layers[j+1];
					layers[j+1] = tmp;

				}


			}

		}

	}

	atomsFinN = 0;

	z_temp = 0;

	int dup_flag;

	for ( int l = layers_n-1; l >= 0 ; l-- ) {

		layers_idx = -l;
		make_positive(&layers_idx,n_layers);

		for ( int i = 0; i < nn; i++ ){
			if ( fabs(atomsNew[i].z - layers[layers_idx]) < cutoff_value ) {
				fin_z = (z_temp*vec_c[2]);
			
				dup_flag = 0;
				for ( int j = 0; j < nn; j++ ) {

					if ( i != j ) {
						
						if ( fabs(atomsNew[i].x - atomsNew[j].x) < cutoff_value || fabs(atomsNew[i].x - atomsNew[j].x-1.0) < cutoff_value ){

							if ( fabs(atomsNew[i].y - atomsNew[j].y) < cutoff_value || fabs(atomsNew[i].y - atomsNew[j].y-1.0) < cutoff_value ) {  
								if ( fabs(atomsNew[i].z - atomsNew[j].z) < cutoff_value || fabs(atomsNew[i].z - atomsNew[j].z-1.0) < cutoff_value  ) { 
 								dup_flag = 1;
								break;
								}
							}
						}
					}
				}
	
				if (dup_flag == 0){
					for ( int iexX = exX_max; iexX >= 1; iexX-- ) { 
						for ( int iexY = exY_max; iexY >= 1; iexY-- ) {
							atomsFin[atomsFinN].name = atomsNew[i].name;
							atomsFin[atomsFinN].x = atomsNew[i].x/(float)(exX_max)+(float)(exX_max-iexX)/(float)(exX_max); //fabs(atomsNew[i].x);
							atomsFin[atomsFinN].y = atomsNew[i].y/(float)(exY_max)+(float)(exY_max-iexY)/(float)(exY_max); //fabs(atomsNew[i].y);
							atomsFin[atomsFinN].z = fin_z;
							
							if ( l >= FIX_LAYER ) atomsFin[atomsFinN].fix_tag = 1;
							else atomsFin[atomsFinN].fix_tag = 0;

							for ( int stri = 0; stri < strVeci; stri++ ){
								if ( strVec[stri].compare(atomsFin[atomsFinN].name) == 0 ) {
									numVecFin[stri]++;
									break;
								}
							}
							atomsFinN++;
						}
					}
				}
			}
		}

		z_diff = layers[(layers_idx+1)%n_layers] - layers[layers_idx];
		if ( z_diff < 0 ) z_diff = z_diff + 1.0;
		z_temp = z_temp + z_diff;

	}


	float min_x = 10.0; float max_x = 0.0; float max_y = 0.0;
	int ll = 0;

	float newOrgX, newOrgY, newMax1X, newMax1Y, newMax2X, newMax2Y, newX, newY;
	float ans, theta1, theta2, proj_b1, proj_b2;
	float newdist, newXX, newYY;

	// (1 1 0) structure
	if ( atoi(argv[2]) == 2 ) {
		for ( int stri = 0; stri < strVeci; stri++ ){
			numVecFin[stri] = 0;

		}
		
		for ( int i = 0; i < atomsFinN; i++ ) {
			if ( atomsFin[i].z == fin_z ) {
				if ( atomsFin[i].x > 0 && atomsFin[i].x < min_x && atomsFin[i].y == 0.0) min_x = atomsFin[i].x;
				if ( atomsFin[i].y == 0 && atomsFin[i].x > max_x ) max_x = atomsFin[i].x;
				if ( atomsFin[i].y > max_y ) max_y = atomsFin[i].y;	

			}

		}

		for ( int i = 0; i < atomsFinN; i++ ) {
			if ( (atomsFin[i].x < min_x && atomsFin[i].y == 0.0) || atomsFin[i].x < cutoff_value ) {

			}
			else{
				atomsConfig[ll].name = atomsFin[i].name;
				atomsConfig[ll].x = atomsFin[i].x;
				atomsConfig[ll].y = atomsFin[i].y;
				atomsConfig[ll].z = atomsFin[i].z;
				atomsConfig[ll].fix_tag = atomsFin[i].fix_tag;
				ll++;


			}

			if ( atomsFin[i].z == fin_z ) {
				if ( atomsFin[i].x == min_x && atomsFin[i].y < cutoff_value ) { newOrgX = atomsFin[i].x; newOrgY = atomsFin[i].y; }			
				if ( atomsFin[i].x == max_x && atomsFin[i].y < cutoff_value ) { newMax1X = atomsFin[i].x; newMax1Y = atomsFin[i].y; }			
				if ( atomsFin[i].x < min_x && atomsFin[i].y == max_y ) { newMax2X = atomsFin[i].x; newMax2Y = atomsFin[i].y; }			
			
			}


		}
		atomsConfigN = ll;
		atomsFinN = 0;
		for ( int i = 0; i < atomsConfigN; i++ ) {

			newX = atomsConfig[i].x; newY = atomsConfig[i].y;

			bb = (newX-newOrgX)*(newX-newOrgX)+(newY-newOrgY)*(newY-newOrgY);
			cc = (newMax1X-newOrgX)*(newMax1X-newOrgX)+(newMax1Y-newOrgY)*(newMax1Y-newOrgY);
			aa = (newMax1X-newX)*(newMax1X-newX)+(newMax1Y-newY)*(newMax1Y-newY);
		
			ans = (bb+cc-aa)/(2.0*sqrt(bb)*sqrt(cc));

			if ( ans >= 1 ) theta1 = 0.0;
			else if ( ans <= -1 ) theta1 = M_PI*0.5;
			else theta1 = acos((bb+cc-aa)/(2.0*sqrt(bb)*sqrt(cc)));

			if ( bb == 0 || cc == 0 ) theta1 = 0.0;

			bb = (newMax1X-newOrgX)*(newMax1X-newOrgX)+(newMax1Y-newOrgY)*(newMax1Y-newOrgY);
			aa = (newMax2X-newMax1X)*(newMax2X-newMax1X)+(newMax2Y-newMax1Y)*(newMax2Y-newMax1Y);
			cc = (newMax2X-newOrgX)*(newMax2X-newOrgX)+(newMax2Y-newOrgY)*(newMax2Y-newOrgY);

			ans = (bb+cc-aa)/(2.0*sqrt(bb)*sqrt(cc));

			if ( ans >= 1 ) theta2 = 0.0;
			else if ( ans <= -1 ) theta2 = M_PI*0.5;
			else theta2 = acos((bb+cc-aa)/(2.0*sqrt(bb)*sqrt(cc)));


			if ( bb == 0 || cc == 0 ) theta2 = 0.0;
			theta2 = M_PI - theta2;

			exX_max = atoi(argv[5]);
			exY_max = atoi(argv[6]);


			newXX = newX - newOrgX; newYY = newY - newOrgY; 
			newdist = sqrt(newXX*newXX+newYY*newYY);
		
			proj_b2 = newdist*sin(theta1) / sin(theta2);
			proj_b1 = (newdist*cos(theta1) + proj_b2 * cos(theta2))/(newMax1X-newOrgX);
			proj_b2 = proj_b2/sqrt((newMax2Y-newOrgY)*(newMax2Y-newOrgY)+(newMax2X-newOrgX)*(newMax2X-newOrgX));

			if ( ((proj_b1 >= 0.0) && (proj_b1 < 1.0-cutoff_value)) && ((proj_b2 >=0.0) && (proj_b2 < 1.0-cutoff_value)) ) {
				for ( float exXi = 0.0; exXi < (float)exX_max; exXi++ ){
					for ( float exYi = 0.0; exYi < (float)exY_max; exYi++ ) {

						atomsFin[atomsFinN].name = atomsConfig[i].name;
						atomsFin[atomsFinN].x = (exXi+proj_b1)/(float)(exX_max);
						atomsFin[atomsFinN].y = (exYi+proj_b2)/(float)(exY_max);
						atomsFin[atomsFinN].z = atomsConfig[i].z;
						atomsFin[atomsFinN].fix_tag = atomsConfig[i].fix_tag;

						for ( int stri = 0; stri < strVeci; stri++ ){
							if ( strVec[stri].compare(atomsFin[atomsFinN].name) == 0 ) {
								numVecFin[stri]++;
								break;
							}
						}
						atomsFinN++;
					}
				}

			}

		}
		
		bb = (float)(exX_max*exX_max)*vec_a[0]*vec_a[0]*(newMax1X-newOrgX)*(newMax1X-newOrgX)+(float)(exY_max*exY_max)*vec_b[1]*vec_b[1]*(newMax1Y-newOrgY)*(newMax1Y-newOrgY);
		aa = (float)(exX_max*exX_max)*vec_a[0]*vec_a[0]*(newMax2X-newMax1X)*(newMax2X-newMax1X)+(float)(exY_max*exY_max)*vec_b[1]*vec_b[1]*(newMax2Y-newMax1Y)*(newMax2Y-newMax1Y);
		cc = (float)(exX_max*exX_max)*vec_a[0]*vec_a[0]*(newMax2X-newOrgX)*(newMax2X-newOrgX)+(float)(exY_max*exY_max)*vec_b[1]*vec_b[1]*(newMax2Y-newOrgY)*(newMax2Y-newOrgY);
		theta = acos((bb+cc-aa)/(2.0*sqrt(bb)*sqrt(cc)));
		vec_a[0] = sqrt(bb); vec_a[1] = 0.0; vec_a[2] = 0.0;
		vec_b[0] = 1.0*sqrt(cc)*cos(theta); vec_b[1] = sqrt(cc)*sin(theta); vec_b[2] = 0.0;
	}

	// create sqrt(3)Xsqrt(3) structure
	
	ll = 0;
	if ( atoi(argv[7]) == 1 && atoi(argv[2]) == 3) {
		for ( int stri = 0; stri < strVeci; stri++ ){
			numVecFin[stri] = 0;

		}
		
		for ( int i = 0; i < atomsFinN; i++ ) {
			if ( atomsFin[i].z == fin_z ) {
				if ( atomsFin[i].x > 0 && atomsFin[i].x < min_x && atomsFin[i].y == 0.0) min_x = atomsFin[i].x;
				if ( atomsFin[i].y == 0 && atomsFin[i].x > max_x ) max_x = atomsFin[i].x;
				if ( atomsFin[i].y > max_y ) max_y = atomsFin[i].y;	

			}
		}

		float theta_30degree = (float)30.0*M_PI/180.0;
		float xxx, yyy, zzz;
		for ( int i = 0; i < atomsFinN; i++ ) {

			if ( atomsFin[i].x == 1.0 ) atomsFin[i].x = 0.0;
	
			xxx = atomsFin[i].x*vec_a[0]+atomsFin[i].y*vec_b[0];
			yyy = atomsFin[i].y*vec_b[1]+atomsFin[i].x*vec_a[1];
			atomsConfig[ll].name = atomsFin[i].name;

			atomsConfig[ll].x = (xxx-min_x*vec_a[0])*cos(theta_30degree)+yyy*(sin(theta_30degree));
			atomsConfig[ll].y = (xxx-min_x*vec_a[0])*(-sin(theta_30degree))+yyy*cos(theta_30degree);

			atomsConfig[ll].z = atomsFin[i].z;
			atomsConfig[ll].fix_tag = atomsFin[i].fix_tag;

			ll++;

			if ( atomsFin[i].z == fin_z ) {
				if ( atomsFin[i].x == 0.25 && atomsFin[i].y == 0.0 ) { newOrgX = atomsConfig[i].x; newOrgY = atomsConfig[i].y; }			
				if ( atomsFin[i].x == 0.75 && atomsFin[i].y == 0.25 ) { newMax1X = atomsConfig[i].x; newMax1Y = atomsConfig[i].y; }			
				if ( atomsFin[i].x == 0.00 && atomsFin[i].y - 0.25 < 0.01 ) { newMax2X = atomsConfig[i].x; newMax2Y = atomsConfig[i].y; }			
			
			}

		}
		atomsConfigN = ll;

		atomsFinN = 0;
		for ( int i = 0; i < atomsConfigN; i++ ) {

			newX = atomsConfig[i].x; newY = atomsConfig[i].y;

			bb = (newX-newOrgX)*(newX-newOrgX)+(newY-newOrgY)*(newY-newOrgY);
			cc = (newMax1X-newOrgX)*(newMax1X-newOrgX)+(newMax1Y-newOrgY)*(newMax1Y-newOrgY);
			aa = (newMax1X-newX)*(newMax1X-newX)+(newMax1Y-newY)*(newMax1Y-newY);
		
			ans = (bb+cc-aa)/(2.0*sqrt(bb)*sqrt(cc));

			if ( ans >= 1 ) theta1 = 0.0;
			else if ( ans <= -1 ) theta1 = M_PI*0.5;
			else theta1 = acos((bb+cc-aa)/(2.0*sqrt(bb)*sqrt(cc)));

			
			if ( bb == 0 || cc == 0 ) theta1 = 0.0;

			bb = (newMax1X-newOrgX)*(newMax1X-newOrgX)+(newMax1Y-newOrgY)*(newMax1Y-newOrgY);
			aa = (newMax2X-newMax1X)*(newMax2X-newMax1X)+(newMax2Y-newMax1Y)*(newMax2Y-newMax1Y);
			cc = (newMax2X-newOrgX)*(newMax2X-newOrgX)+(newMax2Y-newOrgY)*(newMax2Y-newOrgY);

			ans = (bb+cc-aa)/(2.0*sqrt(bb)*sqrt(cc));

			if ( ans >= 1 ) theta2 = 0.0;
			else if ( ans <= -1 ) theta2 = M_PI*0.5;
			else theta2 = acos((bb+cc-aa)/(2.0*sqrt(bb)*sqrt(cc)));


			if ( bb == 0 || cc == 0 ) theta2 = 0.0;


			theta2 = M_PI - theta2;

			exX_max = atoi(argv[5]);
			exY_max = atoi(argv[6]);


			newXX = newX - newOrgX; newYY = newY - newOrgY; 
			newdist = sqrt(newXX*newXX+newYY*newYY);
		
			proj_b2 = newdist*sin(theta1) / sin(theta2);
			proj_b1 = (newdist*cos(theta1) + proj_b2 * cos(theta2))/(newMax1X-newOrgX);
			proj_b2 = proj_b2/sqrt((newMax2Y-newOrgY)*(newMax2Y-newOrgY)+(newMax2X-newOrgX)*(newMax2X-newOrgX));

			duplicate_flag = 0;

			if ( (newY >= 0.0) && ((proj_b1 >= 0.0) && (proj_b2 >=0.0) ) ) {

				if ( proj_b1 >= 1.0 ) { proj_b1 = proj_b1 - 1.0; }	
				if ( proj_b2 >= 1.0 ) { proj_b2 = proj_b2 - 1.0; }	

				if ( proj_b1 >= 1.0 - cutoff_value ) { proj_b1 = proj_b1 - 1.0; }	
				if ( proj_b2 >= 1.0 - cutoff_value ) { proj_b2 = proj_b2 - 1.0; }	

				for ( int j = 0; j < atomsFinN; j++ ) {
					if ( atomsFinN > 0 && (atomsFin[j].x - proj_b1/(float)(exX_max)) < cutoff_value2 && (atomsFin[j].y - proj_b2/(float)(exY_max)) < cutoff_value2 && (atomsFin[j].z - atomsConfig[i].z) < cutoff_value2 ) {
					if ( atomsFinN > 0 && (atomsFin[j].x - proj_b1/(float)(exX_max)) > -cutoff_value2 && (atomsFin[j].y - proj_b2/(float)(exY_max)) > -cutoff_value2 && (atomsFin[j].z - atomsConfig[i].z) > -cutoff_value2 ) {
						duplicate_flag = 1;
					}
					}
				}

				if ( duplicate_flag == 0 ) {
					for ( float exXi = 0.0; exXi < (float)exX_max; exXi++ ){
						for ( float exYi = 0.0; exYi < (float)exY_max; exYi++ ) {
							atomsFin[atomsFinN].name = atomsConfig[i].name;
							atomsFin[atomsFinN].x = (exXi+proj_b1)/(float)(exX_max);
							atomsFin[atomsFinN].y = (exYi+proj_b2)/(float)(exY_max);
							atomsFin[atomsFinN].z = atomsConfig[i].z;
							atomsFin[atomsFinN].fix_tag = atomsConfig[i].fix_tag;

							for ( int stri = 0; stri < strVeci; stri++ ){
								if ( strVec[stri].compare(atomsFin[atomsFinN].name) == 0 ) {

									numVecFin[stri]++;

									break;
								}

							}

							atomsFinN++;
						}
					}
				}
			}
		}

		bb = (float)(exX_max*exX_max)*(newMax1X-newOrgX)*(newMax1X-newOrgX)+(float)(exY_max*exY_max)*(newMax1Y-newOrgY)*(newMax1Y-newOrgY);
		aa = (float)(exX_max*exX_max)*(newMax2X-newMax1X)*(newMax2X-newMax1X)+(float)(exY_max*exY_max)*(newMax2Y-newMax1Y)*(newMax2Y-newMax1Y);
		cc = (float)(exX_max*exX_max)*(newMax2X-newOrgX)*(newMax2X-newOrgX)+(float)(exY_max*exY_max)*(newMax2Y-newOrgY)*(newMax2Y-newOrgY);
	
		theta = acos((bb+cc-aa)/(2.0*sqrt(bb)*sqrt(cc)));

		vec_a[0] = sqrt(bb); vec_a[1] = 0.0; vec_a[2] = 0.0;
		vec_b[0] = 1.0*sqrt(cc)*cos(theta); vec_b[1] = sqrt(cc)*sin(theta); vec_b[2] = 0.0;

	}


	// Write POSCAR output file
	FILE *POSCAROUT = fopen("POSCAR.out","w");

	for ( int i = 0; i < strVeci; i++ ) {
		fprintf(POSCAROUT,"%2s%d",strVec[i].c_str(),numVecFin[i]);

	}
	fprintf(POSCAROUT,"\n");

        fprintf(POSCAROUT," %10.6f\n",scale);
        fprintf(POSCAROUT," %10.5f %10.5f %10.5f\n",vec_a[0],vec_a[1],vec_a[2]);
        fprintf(POSCAROUT," %10.5f %10.5f %10.5f\n",vec_b[0],vec_b[1],vec_b[2]);
        fprintf(POSCAROUT," %10.5f %10.5f %10.5f\n",vec_c[0],vec_c[1],fin_z+vacuum_h);


	for ( int i = 0; i < strVeci; i++ ) {
		fprintf(POSCAROUT," %3s",strVec[i].c_str());

	}
	fprintf(POSCAROUT,"\n");


	for ( int i = 0; i < numVeci; i++ ) {
		fprintf(POSCAROUT," %3d",numVecFin[i]);

	}
	fprintf(POSCAROUT,"\n");

	fprintf(POSCAROUT,"Selective dynamics\n");
        fprintf(POSCAROUT,"Direct\n");


	for ( int i = 0; i < numVeci; i++ ) {
		for (int j = 0; j < atomsFinN; j++ ) {
			if ( strVec[i].compare(atomsFin[j].name) == 0 ){
				if ( atomsFin[j].fix_tag == 1 )
		        		fprintf(POSCAROUT," %10.4f %10.4f %10.4f %3s %3s %3s\n",fabs(atomsFin[j].x),fabs(atomsFin[j].y),fabs(atomsFin[j].z)/(float)(fin_z+vacuum_h),"F","F","F");
				else
		        		fprintf(POSCAROUT," %10.4f %10.4f %10.4f %3s %3s %3s\n",fabs(atomsFin[j].x),fabs(atomsFin[j].y),fabs(atomsFin[j].z)/(float)(fin_z+vacuum_h),"T","T","T");
			}

		}
	}


	fclose(POSCAROUT);

	return 0;

}
