/*
Project:     WUDESIM ver. 1 BETA
File:        Classes.h
Author:      Ahmed Abokifa
Date:        10/25/2016
*/

#pragma once

#include <vector> 

using namespace std;
class all_coords {
public:
	string id;
	float x;
	float y;
	bool exist;
};

class all_links {
public:
	string id;			       //Pipe ID
	double length;			   //Pipe length
	double diameter;		   //Pipe diameter
	string node_1;			   //node 1 of pipe
	string node_2;			   //node 2 of pipe
	int node_1_conn;		   //number of pipe connections to node 1
	int node_2_conn;	       //number of pipe connections to node 2

	all_coords FirstVertex;
	all_coords LastVertex;
	//constructor
	all_links();
};

class all_nodes {
public:
	string id;
	double elev;
	double bulkmix;
	double demand;
};

class all_pumps {
public:
	string id;
	string start;
	string end;
};

class all_valves {
public:
	string id;
	string start;
	string end;
};

class all_cross_junctions {
public:
	int node_index;
	bool is_cross_junction;
	int fast_in_link;
	int fast_out_link;
	int slow_in_link;
	int slow_out_link;
	float fast_in_conc; // Quality of 'fast' inflow
	float slow_in_conc; // Quality of 'slow' outflow
};
class all_options {
public:
	double Rel_Diffusivity;
	double Rel_Viscosity;
	string Flow_UNITS;
	string QUAL_TAG;
	string QUAL_UNIT;

	double Flow_unit_conv;
	int unit_sys;  //0-US 1-SI

	//constructor
	all_options();
};

class all_times {
public:
	int Duration_hr;
	int Duration_min;
	int Hyd_step_hr;
	int Hyd_step_min;
	int Qual_step_hr;
	int Qual_step_min;
	int Rep_step_hr;
	int Rep_step_min;
	int Rep_start_hr;
	int Rep_start_min;
	int N_steps;
	int N_steps_rep;

	//constructor
	all_times();
};

class all_reactions {
public:
	double Bulk_coeff;
	double Wall_coeff;
	double Bulk_order;
	double Wall_order;
	double Lim_pot;

	//constructor
	all_reactions();
};

class dead_end_options {
public:
	// correction factors
	int    Corr_Fact_fl; //0 = no correction; 1 = flow-based correction; 2 = spacing-based correction
	
	double conn_demand;
	double seg_length;
	
	int flow_corr_fl;  //0 = no correction; 1 = flow correction is implemented
	int disp_corr_fl;  //0 = no correction; 1 = flow correction is implemented
	int Rw_corr_fl;    //0 = no correction; 1 = flow correction is implemented
	int calc_meth_fl;  //0 = approximate; 1 = exact 

	// stochastic demands
	bool Stoc_dem_fl; //1=True, 0=False
	double u1;
	double u2;
	double s1;
	double s2;
	double avg_int;
	int N_steps_WUDESIM;

	// Dispersive transport
	int LAM_Dispersion_fl;
	int TUR_Dispersion_fl;

	// Simulated branches
	vector<double> simulated_branches;

	// Constructor
	dead_end_options();
};

class dead_end_branch {
public:
	// Branch ID
	string branch_id;
	int branch_size;						    //Number of pipes in the DE branch;

	// Pipe id
	vector<string> pipe_id;						//IDs of the pipes in the DE branch
	vector<int> pipe_index;					    //Indices of the pipes in the DE branch

	// Pipe properties
	vector<double> length;						//Lengths of pipes in the DE branch
	vector<double> diameter;					//Diameters of pipes in the DE branch

	// Node IDs
	vector<string> terminal_id;					//IDs of the terminal junctions in the DE branch
	vector<string> bound_id;					//IDs of the boundary (inlet) junctions in the DE branch

	// Correction factors
	vector<int>    N_segment;				    //Number of segments for correction factors for each pipe in the DE branch
	vector<double> Flow_Correction_factor;      //Flow Correction Factors
	vector<double> Disp_Correction_factor;      //Dispersion Correction Factors
	vector<double> Rw_Correction_factor;        //Wall demand Correction Factors

	// EPANET Results
	vector<vector<double> > boundary_C_EPANET;	//Boundary condition profile  (row=pipe/ column=concentration@time)
	vector<vector<double> > terminal_C_EPANET;  //terminal concentration profile as simulated by EPANET (row=pipe/ column=concentration@time)
	vector<vector<double> > Reynolds_EPANET;    //Reynolds number as calculated by EPANET
	vector<vector<double> > Res_time_EPANET;	//Residence Time as calculated by EPANET

	// WUDESIM Results
	vector<vector<double> > terminal_C_WUDESIM;       //new terminal concentration as simulated by WUDESIM saved at each actual step (could be stochastic)
	vector<vector<double> > Peclet_WUDESIM;		      //Peclet number as calculated by WUDESIM
	vector<vector<double> > Reynolds_WUDESIM;         //Reynolds number as calculated by WUDESIM
	vector<vector<double> > Res_time_WUDESIM;	      //Residence Time as calculated by WUDESIM

	vector<vector<double> > terminal_C_WUDESIM_WRITE; //WUDESIM concentrations saved at each EPANET step	
	vector<vector<double> > Peclet_WUDESIM_WRITE;
	vector<vector<double> > Reynolds_WUDESIM_WRITE;   //Reynolds number as calculated by WUDESIM
	vector<vector<double> > Res_time_WUDESIM_WRITE;	  //Residence Time as calculated by WUDESIM

	// EPANET flow/demand
	vector<vector<double> > pipe_flow_EPANET;	//Flow profile of the pipes in the DE branch (row=pipe/ column=flow@EPANET timestep)
	vector<vector<double> > node_demand_EPANET;	//Flow profile of the pipes in the DE branch (row=pipe/ column=flow@EPANET timestep)

	// Stochastic flow/demand
	vector<vector<double> > pipe_flow_STOC;	          //Flow profile of the pipes in the DE branch (row=pipe/ column=flow@time)
	vector<vector<double> > node_demand_STOC;	          //Flow profile of the pipes in the DE branch (row=node/ column=flow@time)

	//constructor
	dead_end_branch();
};


class Network {
public:
	const char* EPANET_INP;        
	const char* EPANET_RPT;
	const char* WUDESIM_INP;	
	const char* WUDESIM_RPT;

	vector<all_links>       pipes;
	vector<all_coords>		coords;
	vector<all_nodes>       junctions;
	vector<all_cross_junctions> cross_junctions;
	vector<string>          demand_sources;
	vector<string>          quality_sources;
	vector<string>          tanks;
	vector<string>          reservoirs;
	vector<all_pumps>       pumps;
	vector<all_valves>      valves;
	all_options             options;
	dead_end_options        DE_options;
	all_times               times;
	all_reactions           reactions;
	vector<dead_end_branch> DE_branches;
	vector<string>          XJunctions;

	~Network();
};
