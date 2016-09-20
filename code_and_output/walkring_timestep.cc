// 
// walkring_timestep.cc
//
// Time stepping module for 1d random walk on a ring
//

#include "walkring_timestep.h"
#include <random>

// perform a single time step for the random walkers
// pos: the positions of Z walkers. Z=pos.size()
// N: the number of grid points. All positions should remain between 0
//    and N-1, with periodic boundary conditions
// p: the probability to jump to the left. Also the probability to just right.
//    the probability to stay on the same spot is thus 1-2p.
void perform_time_step(rarray<int,1>& pos, int N, double p)
{
    // PART OF THE ASSIGNMENT!
    
    
    
    
	//Initializing number generator to generate a double between 0 and 1
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);
    
    
    //we iterate for each walker
    for(int i=0;i<pos.extent(0);i++){
    
    //we choose a double uniformly from 0 and 1
	double thisroll=dis(gen);
	
	/* if #<p, walker moves left, if p<#<2p, walker moves right, else walker stays in the same spot
	note that we use p<#<2p instead of p<=#<2p since this would give us one more number to move 
	right compared to left (this keeps it very slightly more balanced) */
	if(thisroll<p){pos[i]=pos[i]-1;
		if (pos[i]<0){pos[i]=pos[i]+N;}
		}
	else if (p<thisroll && thisroll<2*p){pos[i]=pos[i]+1;
		if (pos[i]>N-1){ pos[i]=pos[i]-N;}
		}
	
	}

}


