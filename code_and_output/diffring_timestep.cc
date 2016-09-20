// 
// diffring_timestep.cc
//
// Time step module for 1d diffusion on a ring
//

#include "diffring_timestep.h"
#include <cblas.h>
#include <math.h>  

// perform a single time step for the density field
// F: matrix that describes the time evolution
// P: the density
void perform_time_step(const rarray<double,2>& F, rarray<double,1>& P)
{
    // PART OF THE ASSIGNMENT!
    
    
	//define a copy of P called PP so that we can use P as the output
	rarray<double,1> PP(P.extent(0));
	PP=P.copy();
	
	//doing the multiplication F*PP
	cblas_dgemv(CblasRowMajor, CblasNoTrans,
	F.extent(0), F.extent(1), 1.0, F.data(), P.extent(0), PP.data(), 1, 0.0,P.data(), 1);


}

// fill the matrix needed in perform_time_step
// F: matrix that describes the time evolution
// D: the diffusion constant
// dt: the time step to be used
// dx: the spatial resolution
void fill_time_step_matrix(rarray<double,2>& F, double D, double dt, double dx)
{
    // PART OF THE ASSIGNMENT!
    
    //define alpha just as in lecture 14
    double alpha= dt * D/pow(dx,2.0);
	
	//fill the F matrix with 0s initially
	for(int i = 0; i < F.extent(0); i++) {
	for(int j = 0; j < F.extent(1); j++){
	F[i][j] = 0.0;}}
	
	//fill in the non zero parts of the matrix. F is identical to lecture 14 except for the first and last row
	for (int i = 0; i < F.extent(0); i++){
	if (i == 0) {
		F[i][i] = 1.0 - 2.0*alpha;
		F[i][1]=alpha;
		F[i][F.extent(0)-1]=alpha;}
		
	else if ((i > 0) && (i < (F.extent(0) - 1))) {
	F[i][i-1] = alpha; F[i][i+1] = alpha;
	F[i][i] = 1.0 - 2.0 * alpha;
	}
	else{ 
		F[i][i] = 1.0-2.0*alpha;	
		F[i][i-1]=alpha;
		F[i][0]=alpha;}}


}
