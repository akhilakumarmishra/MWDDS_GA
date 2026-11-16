#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
int yahoo=0;
int yoo=0;
int heuristics_number=2;
#include "global_variables.c"
#include "outdegree.c"
#include "heuristics_H1.c"
#include "heuristics_H2.c"
#include "heuristics_H3.c"
#include "heuristics_H4.c"
#include "repairing.c"
#include "redundant_repair.c"
// #include "redundant_find_function.c"//**********
#include "second_stage_redundant_find.c"
// #include "minimization_stage_two.c"
#include "minimization_stage_one.c"
#include "minimize_heuristics.c"
#include "minimizing.c"
// #include "redundant_find_function.c"
// #include "minimization_stage.c"

// #include "leak_detector_c.h"



int main(){
	// atexit(report_mem_leak);
	clock_t main_start = clock();
	srand(time(0));
	// FILE *wf;wf=fopen("results_H1.txt","a");
	// wf=fopen("resultT1_50_1000.txt","w");
	int filestime=0;
	
	FILE *ptr;
	ptr=fopen("input_files.txt","r");
	if(ptr!=NULL){

		char newline[200];

		for(int a=0;a<200;a++){
			newline[a]='\0';
		}

		
		int filenamer=0;
		int file_count=0;
		int file_best_value_arr[10];
		while (fgets(newline, sizeof(newline), ptr) != NULL) /* read a line */
	    {	

	    	filenamer++;
	    	// if(filenamer>2&&filenamer<6){
	    	// 	heuristics_number=1;
	    	// }
	    	// else if(filenamer>5){
	    	// 	heuristics_number=3;
	    	// }
	    	// else{
	    	// 	heuristics_number=2;
	    	// }
			printf("--------->> FILENAME:%d\n",filenamer);
			
			clock_t begin = clock();
			int lineNumber = 1500;
			int nodenoline=1;
			int Nodeno=0;	//NUMBER OF NUMBERS
			
			char filename[200];
			int ii;
	    	for(ii=0;ii<200;ii++){
	    		filename[ii]='\0';
	    	}
	    	for(ii=0;ii<strlen(newline)-1;ii++){
	    		filename[ii]=newline[ii];
	    	}

			FILE *file = fopen(filename, "r");
			printf("%s\n",filename);
			int lineno = 0;
			int count=0;
			int nodeweightarr[1000]; //NODE WEIGHT ARRAY
			for(int a=0;a<1000;a++){
				nodeweightarr[a]=0;
			}

			int i,k=0,j=0,x=0;
			int diagraph[1100][1100]; // DIRECTED GRAPH 
			// for(i=0;i<1100;i++){
			// 	for(j=0;j<1100;j++){
			// 		diagraph[i][j]=0;
			// 	}
			// }
			int a,b;
			
			int onecount=0;

			//DATA INPUT 
			if ( file != NULL )
			{	
		    		char line[2560];
					char l[250],m[5];
		    		while (fgets(line, sizeof(line), file) != NULL) 
		    		{	
		    			//INPUT node no
		    			if(lineno == nodenoline){
		    				for(i=0;i<strlen(line)-1;i++){
		    					Nodeno = (Nodeno*10) + ((int)line[i]-48);
		    					
		    				}
		    				lineno++;
		    			//	printf("%d\n\n\n",Nodeno);
		    			}// END Node no

		    			// INPUT Node weight array
		    			if(lineno>4 && lineno<=Nodeno+4){
		    				int spaceindex;
		    				for(i=0;i<strlen(line)-1;i++){
		    					if(line[i]==' '){
		    						spaceindex = i;
		    					}
		    				}
		    				int nodeweight=0;
		    				for(i=0;i<strlen(line)-1;i++){
		    					
		    					if(i>spaceindex){
		    						nodeweight = (nodeweight*10)+((int)line[i]-48);
		    				
		    					}
		    				} 
		    				nodeweightarr[k]=nodeweight;
		    				k++;
		    				lineno++;
		    				
		    			}// END of Node Weight array
		    			// INPUT matrix 
		    			else if(lineno>Nodeno+5){
		    				
		    				int q=-1;
		    				for(i=0;i<strlen(line);i++){
		    					if(line[i]=='0' || line[i]=='1'){
		    						q=q+1;
		    						diagraph[j][q]=line[i]-48;

		    					}
		    					if(line[i]=='1'){
		    						onecount++;
		    					}
		    				}
		    				j++;
		    				lineno++;
		    			}
		    			else{
		    				lineno++;

		    			}
		    			
		    		}
		    		fclose(file);
		 
			}
			else
			{
		    		printf("file doesn't exist\n");
		    		continue;
			}

			// int** d_graph = (int **)malloc(Nodeno * sizeof(int *));
			// //printf("*\n");
			// for(k=0;k<Nodeno;k++){
			// 	d_graph[k] = (int *)malloc(Nodeno *sizeof(int));
			// 	for(j=0;j<Nodeno;j++){
			// 		d_graph[k][j] = diagraph[k][j];
			// 	}
			// }
			// printf("*\n");

			// printf("\n");
			// return 0;
			int** directed_graph=(int **)malloc(Nodeno* sizeof(int *));
			int** adjacency_list=(int **)malloc(Nodeno* sizeof(int *));
			// printf("\n    adjacency_list:\n\n");
			for(k=0;k<Nodeno;k++){
				directed_graph[k] = (int *)malloc(Nodeno*sizeof(int));
				adjacency_list[k] = (int *)malloc(Nodeno*sizeof(int));
				for(j=0;j<Nodeno;j++){
					adjacency_list[k][j]=-1;
				}
				int cn=1;
				for(j=0;j<Nodeno;j++){
					directed_graph[k][j] = diagraph[k][j];
					if(diagraph[k][j]==1){
						adjacency_list[k][cn]=j;
						cn++;
					}
				}
				adjacency_list[k][0]=cn-1;
				// printf("%d-->",k);
				// for(j=0;j<cn;j++){
				// 	printf("%d ",adjacency_list[k][j]);
					
				// }
				// printf("\n");
			}
			// int* parent_count_arr=(int *)malloc(Nodeno*sizeof(int));
			int**parent_nodes=(int**)malloc(Nodeno*sizeof(int *));
			// printf("\n    parent_nodes:\n\n");
			for(i=0;i<Nodeno;i++){
				parent_nodes[i]=(int*)malloc(Nodeno*sizeof(int));

				for(j=0;j<Nodeno;j++){
					parent_nodes[i][j]=-1;
				}
				int pn=1;
				for(j=0;j<Nodeno;j++){
					if(directed_graph[j][i]==1){
						parent_nodes[i][pn]=j;
						pn++;
					}
				}
				parent_nodes[i][0]=pn-1;
				// printf("%d<--",i);
				// for(j=0;j<pn;j++){
				// 	printf("%d ",parent_nodes[i][j]);
					
				// }
				// printf("\n");

			}
			// printf("\n");
/*
			printf("     nodeweightarr:\n\n");
			int max_node_weight=0;
			for(i=0;i<Nodeno;i++){
				if(nodeweightarr[i]>max_node_weight){
					max_node_weight=nodeweightarr[i];
				}
				// printf("%d --> %d\n",i,nodeweightarr[i]);
			}
			int visiting_nodes[Nodeno];
			int dom_x[Nodeno];
			for(i=0;i<Nodeno;i++){
				visiting_nodes[i]=0;
			}
			for(i=0;i<Nodeno;i++){
				dom_x[i]=0;
			}
			for(i=0;i<max_node_weight;i++){
				int xyz=0;
				for(j=0;j<Nodeno;j++){
					if(nodeweightarr[j]==i){
						printf("%d",j);
						xyz++;
						printf("[");
						int k;
						for(k=0;k<Nodeno;k++){
							if(directed_graph[j][k]==1 && visiting_nodes[k]==0){
								visiting_nodes[j]=1;
								dom_x[j]=1;
								visiting_nodes[k]=1;
								printf("%d,",k);
							}
						}
						printf("] ");
					}
				}
				if(xyz>0)
					printf("\n<<<<----nodeweight:%d(count:%d)\n\n",i,xyz );
			}
			for(i=0;i<Nodeno;i++){
				if(visiting_nodes[i]==0){
					printf("%d ",i);
					dom_x[i]=1;
				}
			}
			int fit_x=0;
			for(i=0;i<Nodeno;i++){
				if(dom_x[i]==1){
					fit_x+=dom_x[i]*nodeweightarr[i];
				}
			}
			printf("fit_x:%d",fit_x);

		*/

			
			//END DATA READING

			// for(int i=0;i<Nodeno;i++){
			// 	printf("%d : %d\n",i,nodeweightarr[i]);
			// }
			// printf("\n\n\n Diagraph\n\n\n");
			// int p,q;
			// for(p=0;p<Nodeno;p++){
			// 	// printf("%d>> ",p);
			// 	for(q=0;q<Nodeno;q++){
			// 		if(directed_graph[p][q]==1)
			// 		printf("%d ",q);
			// 		fflush(stdout);
			// 	}
			// 	printf("\n");
				
			// }

			// printf("data input done\n");
						
			//INDEGREE calculation for each node
			
			
			// int* indegree = indegree_calculation(Nodeno,directed_graph);
			
			
			// for(i=0;i<Nodeno;i++){
			// 	printf("%d >>",i);
			// 	for(j=0;j<Nodeno;j++){
			// 		if(directed_graph[i][j]==1){
			// 			printf("%d, ",j);
			// 		}
			// 	}
			// 	printf("\n");
			// }
		
			
			// printf("\nSTART OF population genearation\n");
			//START OF POPULATION GENERATION
			// int total_node_weight_sum=0;
			// for(i=0;i<Nodeno;i++){
			// 	total_node_weight_sum+=nodeweightarr[i];
			// }

			// int outdegree[Nodeno];
			// int* out_deg=outdegree_calculation(Nodeno,directed_graph);
			// for(i=0;i<Nodeno;i++){
			// 	outdegree[i]=out_deg[i];
			// }
			
			// float out_weight_ratio[Nodeno];
			// for(i=0;i<Nodeno;i++){
			// 	out_weight_ratio[i]=-1;
			// }
						
			// // printf("\n\nredundant_nodes_in_stage:2\n");
			// for(i=0;i<Nodeno;i++){
			// 	out_weight_ratio[i]= (float)outdegree[i] / (float)nodeweightarr[i];
					
			// }
			
			int** population;
			population = (int**)malloc(pop_size * sizeof(int *));
			
			//IN POPULATION, 
			//	1 = IN DOMINATION SET,
			//	0 = NOT IN DOMINATING SET.
			
			int fitness_arr[pop_size];
	
			for(i=0;i<pop_size;i++){
				// printf("		\n--------------->>> \n***START OF POP :%d\n",i);
				// printf("\n\n##########################################\n-------------\n---------------\n");
				// printf(    "#     POPULATION NUMBER : %d    #\n-------------\n---------------\n",i);
				// printf("##########################################\n\n");
				// fflush(stdout);
				population[i]=(int*)malloc(Nodeno*sizeof(int));
				


				if(i==0){
					////NEW addition : initial_randomness
					//***************FIRST CHROMOSOME*****************
			
					int color[Nodeno];
					for(j=0;j<Nodeno;j++){
						color[j]=1;
					}
					
					int one_count=0;
					for(j=0;j<Nodeno;j++){
						population[i][j]=0;
					}
					float white_neighbour_sum_arr[Nodeno];
					for(j=0;j<Nodeno;j++){
						white_neighbour_sum_arr[j]=0;
					}
					for(j=0;j<Nodeno;j++){

						float white_neighbour_sum=0;
						int k;
						for(k=0;k<Nodeno;k++){
							if(j!=k &&directed_graph[j][k]==1){
								white_neighbour_sum+=(float)nodeweightarr[k]*color[k];
							}
						}
						white_neighbour_sum_arr[j]=white_neighbour_sum;
					}
					float neighbourhood_ratio[Nodeno];
					
					for(j=0;j<Nodeno;j++){
						neighbourhood_ratio[j]=(float)white_neighbour_sum_arr[j]/(float)nodeweightarr[j];
						// neighbourhood_ratio[j]=(float)outdegree[j]/(float)nodeweightarr[j];
					}

					float max=neighbourhood_ratio[0];
					int max_indexno=0;
					for(j=1;j<Nodeno;j++){
						if(neighbourhood_ratio[j]>max){
							max=neighbourhood_ratio[j];
							max_indexno=j;
						}
					}
					int same_max_nodes[Nodeno];
					int same_max=0;
					for(j=0;j<Nodeno;j++){
						if(max==neighbourhood_ratio[j]){
							same_max_nodes[same_max]=j;
							same_max++;
						}
					}
					if(same_max>1){
						int rand_pt=(int)(u01*same_max);
						max_indexno=same_max_nodes[rand_pt];
					}
					
					population[i][max_indexno]=1;
					
					// printf("max_indexno:%d   %f\n",max_indexno,max);
					for(j=0;j<Nodeno;j++){
						float pinit=u01;
						if(pinit < init_pop_prob && j!=max_indexno){
							population[i][j]=1;
						}
					}
					

					// COLORING THE NODES 
					// 	0 = IF A NODE IS IN DOMINATING SET(BLACK) OR DIRECTLY CONNECTED TO THE NODE THAT IN DOMINATING SET (GREY)
					//  1 = OTHERWISE (WHITE)

					// for(j=0;j<Nodeno;j++){
					// 	if(temp_population_memeber[j]==1)
					// 		printf("%d ",j );
					// }
					// printf("\n");
					int node_arr[Nodeno];
					
					for(j=0;j<Nodeno;j++){
						node_arr[j] = population[i][j];
					}
					
					
					int* repairing_chromosome;
					repairing_chromosome = repairing(node_arr,Nodeno,directed_graph,nodeweightarr,heuristics_number);
					
					//***************
					// check(Nodeno,repairing_chromosome,directed_graph,1,i,1);
					// printf("rx100\n");
					// for(j=0;j<Nodeno;j++){
					// 	printf("%d ",repairing_chromosome[j]);
					// }
					// printf("\n");
					//***************
					// sleep(10);
					//minimization function
					int* minimized_offspring;
					minimized_offspring= minimization(repairing_chromosome,Nodeno,directed_graph,nodeweightarr,adjacency_list,parent_nodes);
					
					//***************
					// check(Nodeno,minimized_offspring,directed_graph,1,i,2);
					//***************
					


					
					int min_chromosome_fitness=0;
					for(j=0;j<Nodeno;j++){
						min_chromosome_fitness+=nodeweightarr[j]*minimized_offspring[j];
					}
					// printf("fitness_1 :%d\n",fitness_one);

					
					//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

					
					// int minimized_offspring[Nodeno];
					for(j=0;j<Nodeno;j++){
						population[i][j]=minimized_offspring[j];
					}
					fitness_arr[i]=min_chromosome_fitness;

					// if(fitness_one<=fitness_two){
					
					// 	for(j=0;j<Nodeno;j++){
					// 		population[i][j]=minimized_offspring_one[j];
					// 	}
					// 	fitness_arr[i]=fitness_one;
					// }
					// else{
					// 	for(j=0;j<Nodeno;j++){
					// 		population[i][j]=minimized_offspring_two[j];
					// 	}
					// 	fitness_arr[i]=fitness_two;	
					// }
					
					
					// sleep(10);

					//*******************************END **********************

					// for(j=0;j<Nodeno;j++){
					// 	population[i][j]=minimized_offspring[j];
					// }
					// int min_chromosome_fitness=0;
					// for(j=0;j<Nodeno;j++){
					// 	min_chromosome_fitness+=nodeweightarr[j]*minimized_offspring[j];
					// }
					// fitness_arr[i]=min_chromosome_fitness;
					// printf("fitness :%d\n",fitness_arr[i]);
					free(repairing_chromosome);
					// printf("fitness :%d\n",fitness_arr[i]);
					free(minimized_offspring);
					
				}
				else{
					int itr=0;
					int max_pop_itr=50;
					int store_itr=0;
					
					while(itr<max_pop_itr){

						////NEW addition : initial_randomness
					
						int color[Nodeno];
						for(j=0;j<Nodeno;j++){
							color[j]=1;
						}
						

						for(j=0;j<Nodeno;j++){
							population[i][j]=0;
						}
						
						int white_neighbour_sum_arr[Nodeno];
						for(j=0;j<Nodeno;j++){
							white_neighbour_sum_arr[j]=0;
						}
						for(j=0;j<Nodeno;j++){

							float white_neighbour_sum=0;
							int k;
							for(k=0;k<Nodeno;k++){
								if(j!=k &&directed_graph[j][k]==1){
									white_neighbour_sum+=nodeweightarr[k]*color[k];
								}
							}
							white_neighbour_sum_arr[j]=white_neighbour_sum;
							// printf("node:%d  white_neighbour_sum:%d  nodeweight:%d\n",j,white_neighbour_sum_arr[j],nodeweightarr[j]);
							// fflush(stdout);
						}
						// printf("\n");
						float neighbourhood_ratio[Nodeno];
						
						for(j=0;j<Nodeno;j++){
							neighbourhood_ratio[j]=(float)white_neighbour_sum_arr[j]/(float)nodeweightarr[j];
							// neighbourhood_ratio[j]=(float)outdegree[j]/(float)nodeweightarr[j];
						}

						float max=neighbourhood_ratio[0];
						int max_indexno=0;
						for(j=1;j<Nodeno;j++){
							if(neighbourhood_ratio[j]>max){
								max=neighbourhood_ratio[j];
								max_indexno=j;
							}
						}
						int same_max_nodes[Nodeno];
						int same_max=0;
						for(j=0;j<Nodeno;j++){
							if(max==neighbourhood_ratio[j]){
								same_max_nodes[same_max]=j;
								same_max++;
							}
						}
						if(same_max>1){
							int rand_pt=(int)(u01*same_max);
							max_indexno=same_max_nodes[rand_pt];
						}
						population[i][max_indexno]=1;
						
						for(j=0;j<Nodeno;j++){
							float pinit=u01;
							if(pinit < init_pop_prob && j!=max_indexno){
								population[i][j]=1;
							}
						}
						
						// COLORING THE NODES 
						// 	0 = IF A NODE IS IN DOMINATING SET(BLACK) OR DIRECTLY CONNECTED TO THE NODE THAT IN DOMINATING SET (GREY)
						//  1 = OTHERWISE (WHITE)

						
						int node_arr[Nodeno];
						
						for(j=0;j<Nodeno;j++){
							node_arr[j] = population[i][j];
						}
					
						//repairing function
						int repaired_chromosome[Nodeno];
						for(j=0;j<Nodeno;j++){
							repaired_chromosome[j]=0;
						}
						int repairing_chromosome[Nodeno];
						for(j=0;j<Nodeno;j++){
							repairing_chromosome[j]=0;
						}
						int* rep_chromosome= repairing(node_arr,Nodeno,directed_graph,nodeweightarr,heuristics_number);
						for(j=0;j<Nodeno;j++){
							repairing_chromosome[j]=rep_chromosome[j];
						}
						// printf("rxy200\n");
						// for(j=0;j<Nodeno;j++){
						// 	printf("%d ",rep_chromosome[j]);
						// }
						// printf("\n");
						

						//***************
						// check(Nodeno,repairing_chromosome,directed_graph,1,i,1);
						//***************
						// printf("rxy100\n");
						for(j=0;j<Nodeno;j++){
							// printf("%d ",repairing_chromosome[j]);fflush(stdout);
							if(repairing_chromosome[j]!=1&&repairing_chromosome[j]!=0){
								printf("ERROR----->>%d has ODD VALUE:-  pos:%d \n",j,repairing_chromosome[j]); fflush(stdout);sleep(10);
							}
						}
						// printf("\nxxxxxx+++++xxxxx\n");fflush(stdout);
						// sleep(1);
						// printf("\n");

						//minimization function
						int* minimized_offspring;
						minimized_offspring = minimization(repairing_chromosome,Nodeno,directed_graph,nodeweightarr,adjacency_list,parent_nodes);
						// printf("\n*******\n+8+\n");
						
						//***************
						// check(Nodeno,minimized_offspring,directed_graph,1,i,2);
						//***************
						for(j=0;j<Nodeno;j++){
							if(minimized_offspring[j]!=1 && minimized_offspring[j]!=0){
								printf("ERROR-----not valid chromosome-1\n");sleep(10);
							}
						}

						int min_chromosome_fitness=0;
						for(j=0;j<Nodeno;j++){
							min_chromosome_fitness+=nodeweightarr[j]*minimized_offspring[j];
						}

				

						int unique_check = unique(minimized_offspring,min_chromosome_fitness,Nodeno,i,population,fitness_arr);
						if(unique_check==0){
							fitness_arr[i]=min_chromosome_fitness;
							for(j=0;j<Nodeno;j++){
								population[i][j]=minimized_offspring[j];
							}
							break;
						}
						else{
							itr++;

						}
						store_itr=itr;
						free(rep_chromosome);
						free(minimized_offspring);

					}
					if(store_itr==max_pop_itr){
						pop_size=i;
						break;
					}
				}
				
				
			}//END OF POPULATION GENERATION
			
// ####################################### END OF POPULATION GENERATION ################
			//-------------------------------------------------
			//PRINTING POPULATION
			// printf("Population\n");
			// for(i=0;i<pop_size;i++){
			// 	for(j=0;j<Nodeno;j++){
			// 		printf("%d ",population[i][j]);
			// 	}
			// 	printf("\n");
			// }
			
			// printf("\nPopulation DONE\nfitness array:\n");
			// for(i=0;i<pop_size;i++){
			// 	printf("%d, ",fitness_arr[i]);
			// }
			// printf("\n");
			
			
			
			int best_fitness_value = fitness_arr[0];
			int best_fit_chromosome_index =0;
			for(i=1;i<pop_size;i++){
				if(fitness_arr[i]<best_fitness_value){
					best_fitness_value = fitness_arr[i];
					best_fit_chromosome_index= i;
				}
			}
//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
		
			///similar best fit value chromosomes
			// int unique_fitness_arr[total_node_weight_sum][similar_set_max_size+1];
			// for(i=0;i<total_node_weight_sum;i++){
			// 	unique_fitness_arr[i][0]=0;
			// 	for(j=1;j<similar_set_max_size;j++){
			// 		unique_fitness_arr[i][j]=-1;
			// 	}
			// }
			// int similar_count=0;
			// int** global_unique_chromosome;
			// global_unique_chromosome=(int**)malloc(50000*sizeof(int*));
		
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
			int local_pt=0;
			int unique_array[unicon];
			int unique_chromosome_array[unicon][Nodeno];
//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA			
			// printf("init_best_fit_val=%d\n",best_fitness_value);
			// printf("init_best_fit_ind=%d\n",best_fit_chromosome_index);
			// printf("B\n");
			
			// sleep(10);
			//GENETIC ALGORITHM
			int local_fitness_value=0;
			int gen=0;
			
			int local_count=0;
			int* offspring=(int*)malloc(Nodeno * sizeof(int));
			while(gen < MAX_GEN){

				float p = u01;
				// printf("\nfile :%d Gen :%d \t",filenamer,gen); 

				if(p < Pc){

					// printf("in_genetic\n");

					//SELECTION OPERATOR
					int s1,s2;
					//SELECTION OF PARENT1
					
					s1 = (int)(u01*pop_size);
					do{
						s2=(int)(u01*pop_size);
					}while(s1==s2);
					int node_weight_sum=0;
					for(i=0;i<Nodeno;i++){
						if(population[s1][i]==1){
							node_weight_sum+=nodeweightarr[i];
						}
					}
					int s1_fitness=node_weight_sum;
					
					node_weight_sum=0;
					for(i=0;i<Nodeno;i++){
						if(population[s2][i]==1){
							node_weight_sum+=nodeweightarr[i];
						}
					}
					int s2_fitness = node_weight_sum;

					int parent1 = ((s1_fitness<=s2_fitness)?((u01<=prob_select)?s1:s2):((u01>prob_select)?s1:s2));
					// printf("parent1 : %d\n",parent1);
					//SELECTION OF PARENT2
					
					s1 = (int)(u01*pop_size);
					do{
						s2=(int)(u01*pop_size);
					}while(s1==s2);
					node_weight_sum=0;
					for(i=0;i<Nodeno;i++){
						if(population[s1][i]==1){
							node_weight_sum+=nodeweightarr[i];
						}
					}
					s1_fitness=node_weight_sum;
					
					node_weight_sum=0;
					for(i=0;i<Nodeno;i++){
						if(population[s2][i]==1){
							node_weight_sum+=nodeweightarr[i];
						}
					}
					s2_fitness = node_weight_sum;

					int parent2 = ((s1_fitness<s2_fitness)?((u01<=prob_select)?s1:s2):((u01>prob_select)?s1:s2));
					
					//Selection END



					//CROSSOVER OPERATOR
				/*	
					//fitness based crossover
					node_weight_sum=0;
					for(i=0;i<Nodeno;i++){
						if(population[parent1][i]==1){
							node_weight_sum+=nodeweightarr[i];
						}
					}
					int parent1_fitness = node_weight_sum;
					// printf("Fp1=%d\n",parent1_fitness);
					node_weight_sum=0;
					for(i=0;i<Nodeno;i++){
						if(population[parent2][i]==1){
							node_weight_sum+=nodeweightarr[i];
						}
					}
					int parent2_fitness = node_weight_sum;
					// printf("Fp2=%d\n",parent2_fitness);
					


					float prob_value1 = parent2_fitness / (parent1_fitness + parent2_fitness);
					float prob_value2 =1-prob_value1;
					for(i=0;i<Nodeno;i++){
						if(population[parent1][i]==population[parent2][i]){
							offspring[i]=population[parent1][i];
						}
						else{
							if(prob_value1 > prob_value2){
								offspring[i] = population[parent1][i];
							} 
							else{
								offspring[i] = population[parent2][i];
							}
						}	
					}
					int offspring_weight_sum=0;
					for(i=0;i<Nodeno;i++){
						if(population[parent2][i]==1){
							offspring_weight_sum+=nodeweightarr[i];
						}
					}
					// printf("crossover offspringfit: %d\n",offspring_weight_sum);
				*/
					//crossover END
					//k-point crossover
			/*		node_weight_sum=0;
					for(i=0;i<Nodeno;i++){
						if(population[parent1][i]==1){
							node_weight_sum+=nodeweightarr[i];
						}
					}
					int parent1_fitness = node_weight_sum;
					// printf("Fp1=%d\n",parent1_fitness);
					node_weight_sum=0;
					for(i=0;i<Nodeno;i++){
						if(population[parent2][i]==1){
							node_weight_sum+=nodeweightarr[i];
						}
					}
					int parent2_fitness = node_weight_sum;
					int px1,px2;
					if(parent2_fitness<parent1_fitness){
						px1=parent2;
						px2=parent1;
					}
					else{
						px1=parent1;
						px2=parent2;	
					}
					parent1=px1;parent2=px2;
			*/		

					int node_points[Nodeno];
					for(i=0;i<Nodeno;i++){
						node_points[i]=0;
					}
					int crossover_pos[k_points];
					int random_pts=u01*(Nodeno-1);
					crossover_pos[0]=random_pts;
					node_points[random_pts]=1;
					for(i=1;i<k_points;i++){
						random_pts=u01*(Nodeno-1);
						while(node_points[random_pts]==1){
							random_pts=u01*(Nodeno-1);
						}
						crossover_pos[i]=random_pts;
						node_points[random_pts]=1;
					}

					for (i = 0; i <k_points ; i++){
						for (j = i + 1; j < k_points; j++){
							if (crossover_pos[i] > crossover_pos[j]){
								int a =  crossover_pos[i];
								crossover_pos[i] = crossover_pos[j];
								crossover_pos[j] = a;
							}
						}
					}
					int crossover_point_sets[k_points+2];
					crossover_point_sets[0]=0;
					for(i=0;i<k_points;i++){
						crossover_point_sets[i+1]=crossover_pos[i];
					}
					crossover_point_sets[k_points+1]=Nodeno;

					
					for(j=0;j<k_points+1;j++){
						if(j%2==0){
							int start=crossover_point_sets[j];
							int end=crossover_point_sets[j+1];
							for(i=start;i<end;i++){
								offspring[i]=population[parent1][i];
							}
						}
						else{
							int start=crossover_point_sets[j];
							int end=crossover_point_sets[j+1];
							for(i=start;i<end;i++){
								offspring[i]=population[parent2][i];
							}
						}
						
						
					}
					

					//END K-POINT CROSSOVER

					

					//MUTATION
					//float Pm=0.6;
					
					for(i=0;i<Nodeno;i++){
						float prob_mutation=u01;
						if(prob_mutation<Pm ){
							offspring[i]=1-offspring[i];
						}
					}
					//mutation END
				}
				else{
					//random
					// printf("\ninrandom\n");

					for(i=0;i<Nodeno;i++){
						
						offspring[i]=(int)(u01*2);
					}
				
					// int incl_nodes=(int)(perc_value*Nodeno);
					// for(i=0;i<Nodeno;i++){
					// 	int rand_val=u01*2;
					// 	if(rand_val==1 && incl_nodes>0){
					// 		offspring[i]=1;
					// 		incl_nodes--;
					// 	}
					// 	if(incl_nodes==0){
					// 		break;
					// 	}

					// }
				
				}
				// printf("\nOUT\n");
				// return 0;
				
				int* repaired_offspring;
				repaired_offspring = repairing(offspring,Nodeno,directed_graph,nodeweightarr,heuristics_number);
				for(i=0;i<Nodeno;i++){
					offspring[i]=repaired_offspring[i];
				}
				//***************
				// check(Nodeno,repaired_offspring,directed_graph,2,gen,1);
				//***************
				int* min_offspring;
				min_offspring = minimization(offspring,Nodeno,directed_graph,nodeweightarr,adjacency_list,parent_nodes);
				for(i=0;i<Nodeno;i++){
					offspring[i]=min_offspring[i];
				}
				//***************
				 // check(Nodeno,min_offspring,directed_graph,2,gen,2);
				//***************
				// for(j=0;j<Nodeno;j++){
				// 	if(min_offspring[j]!=1 && min_offspring[j]!=0){
				// 		printf("ERROR-----not valid chromosome-1\n");
				// 	}
				// }
				int offspring_fitness=0;
				for(i=0;i<Nodeno;i++){
					offspring_fitness +=offspring[i]*nodeweightarr[i];
				}
				
				// for(i=0;i<total_node_weight_sum;i++){
					
				// 	if(unique_fitness_arr[i][0]>0){
				// 		printf("%d : < %d >\t",i,unique_fitness_arr[i][0]);
					

				// 		for(j=1;j<similar_set_max_size+1;j++){
				// 			printf("%d ",unique_fitness_arr[i][j]);
				// 		}
				// 		printf("\n");
				// 	}
				// }
				// printf("\n");

				int gc=0;
				int uniqueness = unique(offspring,offspring_fitness,Nodeno,pop_size,population,fitness_arr);//check with population

//######################################### SIMILAR SET CHECKER ############################
		/*		int uniqueness=1;

				int unique_one = unique(offspring,offspring_fitness,Nodeno,pop_size,population,fitness_arr);
				// printf("\nA:%d\n",unique_one);
				// printf("offspring_fitness:%d \n",offspring_fitness);
				if(unique_one==0){
					
					if(unique_fitness_arr[offspring_fitness][0]>0){
						
						int sizer=unique_fitness_arr[offspring_fitness][0];
						int** individual_fitness_chromosomes=(int**)malloc(sizer * sizeof(int*));
						for(i=1;i<sizer+1;i++){
							int row_no=unique_fitness_arr[offspring_fitness][i];
							individual_fitness_chromosomes[i-1]=(int*)malloc(Nodeno*sizeof(int));
							for(j=0;j<Nodeno;j++){
								individual_fitness_chromosomes[i-1][j]=global_unique_chromosome[row_no][j];
							}
						}
						int unique_two=unique_similar(offspring,Nodeno,sizer,individual_fitness_chromosomes);
						// printf("unique_two:%d \n",unique_two );
						if(unique_two==0){
							if(sizer<similar_set_max_size){
								global_unique_chromosome[similar_count]=(int*)malloc(Nodeno*sizeof(int));
								for(i=0;i<Nodeno;i++){
									global_unique_chromosome[similar_count][i]=offspring[i];
								}
								unique_fitness_arr[offspring_fitness][0]++;
								int sizex=unique_fitness_arr[offspring_fitness][0];
								unique_fitness_arr[offspring_fitness][sizex]=similar_count;
								similar_count++;

							}
							uniqueness=0;
						}
						for(i=0;i<sizer;i++){
							free(individual_fitness_chromosomes[i]);
						}
						free(individual_fitness_chromosomes);
							
					}
					else{
						// printf("\nA:%d\n",unique_fitness_arr[offspring_fitness][0]);
						global_unique_chromosome[similar_count]=(int*)malloc(Nodeno*sizeof(int));
						for(i=0;i<Nodeno;i++){
							global_unique_chromosome[similar_count][i]=offspring[i];
							// printf("%d ",global_unique_chromosome[similar_count][i]);
						}
						unique_fitness_arr[offspring_fitness][0]++;
						// int sizer=unique_fitness_arr[offspring_fitness][0];
						unique_fitness_arr[offspring_fitness][1]=similar_count;
						similar_count++;
						// printf("\nsimilar_count:%d\n",similar_count);
						uniqueness=0;

					}
					
					
				}
				
			*/					
			
//################################################## END ####################################
//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
				// int uniqueness=1;
				// int unique_one=unique(offspring,offspring_fitness,Nodeno,pop_size,population,fitness_arr);//check with population
				// if(unique_one==0){
				// 	if(local_pt<unicon){
				// 		uniqueness=1;
				// 		unique_array[local_pt]=offspring_fitness;
				// 		for(i=0;i<Nodeno;i++){
				// 			unique_chromosome_array[local_pt][i]=offspring[i];
				// 		}
				// 		local_pt++;
				// 	}
				// 	if(local_pt==unicon){
				// 		uniqueness=0;
				// 		int rand_pt=u01*unicon;
				// 		offspring_fitness=unique_array[rand_pt];
				// 		for(i=0;i<Nodeno;i++){
				// 			offspring[i]=unique_chromosome_array[rand_pt][i];
				// 		}
				// 	}
											
				// }
//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
				if(uniqueness==0){
					// if(offspring_fitness==best_fitness_value){
					// 	local_count++;
					// }
					// if(local_count<11){
						int wrost_chromosome_index=wrost_fit_chromosome(fitness_arr,pop_size);
						for(i=0;i<Nodeno;i++){
							population[wrost_chromosome_index][i]=offspring[i];
						}
						fitness_arr[wrost_chromosome_index]=offspring_fitness;
						// gen++;
						// gc++;
					// }
					if(offspring_fitness<best_fitness_value){
						best_fitness_value=offspring_fitness;
						best_fit_chromosome_index=wrost_chromosome_index;
						// local_count=0;
						// gen++;
						// int* parturbated_chromosome=()


					}
					// printf("best_fit_val=%d\n",best_fitness_value);fflush(stdout);
					// printf("offspring_fit=%d\n",offspring_fitness);
					// fflush(stdout);
					gen++;
					gc++;
				}
				// printf("\nfile :%d Gen :%d \t",filenamer,gen);
				// if(gc==1){printf("best_fit_val=%d\n",best_fitness_value);fflush(stdout);}else{printf("\n");}
				// printf("\n\n\n*****New genearation:%d*****\n\n\n",gen);
				// free(min_offspring);
				// for(i=0;i<sizeof(filename);i++){
				// 	if(i>50){printf("%c",filename[i]);fflush(stdout);}
				// }
				free(repaired_offspring);
				free(min_offspring);

			}//end of genetic algorithm

	

			// printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			printf("filename:	");
			for(i=0;i<sizeof(filename);i++){
				printf("%c",filename[i]);
			}
			printf("\n\n******FINAL RESULT******\n\n");
			fflush(stdout);
			printf("best_fitness_value =%d\n",best_fitness_value);
			//printf("[");
			//for(i=0;i<Nodeno;i++){
				//if(population[best_fit_chromosome_index][i]==1){
					//printf("%d, ",i);
					//fflush(stdout);
				//}
			//}
			// check(Nodeno,population[best_fit_chromosome_index],directed_graph,1,i,2);
			clock_t end = clock();
			double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
			printf("total time: %f sec\n",time_spent);
			fflush(stdout);
			double total_time=time_spent;
			filestime+=total_time;
			printf("final_fit :%d\n",best_fitness_value);
			fflush(stdout);

			file_best_value_arr[file_count]=best_fitness_value;
			file_count++;
			double avg_value;
			if(file_count==10){
				int summation=0;
				for(int avg=0;avg<10;avg++){
					summation+=file_best_value_arr[avg];
				}
				avg_value=(float)(summation)/10.0;
				

			}


			FILE *wf;
			wf=fopen("hit_and_trail.txt","a");
			char strx[300];
			if(heuristics_number==1){
				strcpy(strx,"H1: ");
			}
			else if(heuristics_number==2){
				strcpy(strx,"H2 :  ");
			}
			else if(heuristics_number==3){
				strcpy(strx,"H3 :  ");
			}
			else if(heuristics_number==4){
				strcpy(strx,"H4 :  ");
			}
			else{
				printf("wrong heuristics\n");
				return 0;
			}
			
			char timer[20];
			sprintf(timer,"%.3f",total_time);
			strcat(strx,timer);
			strcat(strx,"   ");
			strcpy(timer," ");
			sprintf(timer,"%d",filestime);
			strcat(strx,timer);
			strcat(strx,"   ");
			strcat(strx,filename);
			strcat(strx," :");
			char bf_value[20];
			sprintf(bf_value,"%d",best_fitness_value);
			strcat(strx,bf_value);
			if(file_count==10){
				strcat(strx,"   ");
				char value[20];
				sprintf(value,"%f",avg_value);
				strcat(strx,value);
				file_count=0;
				for(int avg=0;avg<10;avg++){
					file_best_value_arr[avg]=0;
				}

			}
			fprintf(wf, "%s\n",strx);
			strcpy(strx," ");
			fclose(wf);

			//free memory
			for(j=0;j<Nodeno;j++){
				int *pointer=directed_graph[j];
				free(pointer);
			}
			free(directed_graph);
			for(j=0;j<Nodeno;j++){
				int *pointer=adjacency_list[j];
				free(pointer);
			}
			free(adjacency_list);
			for(j=0;j<Nodeno;j++){
				int *pointer=parent_nodes[j];
				free(pointer);
			}
			free(parent_nodes);
			for(j=0;j<pop_size;j++){
				int *pointer=population[j];
				free(pointer);
			}
			free(population);

			
			free(offspring);

			
		
		}
		// report_mem_leak();

	}
	clock_t main_end = clock();
	double main_time_spent = (double)(main_end - main_start) / CLOCKS_PER_SEC;
	printf("main_total_time : %d\n",(int)main_time_spent);
	printf("%d 		%d\n",pop_size,MAX_GEN);
	printf("	%f\n",init_pop_prob);
	printf("	%f",PPh);
	printf("%f 	%f 	%f\n",Pc,prob_select,Pm);

	fflush(stdout);
	printf("yahoo:%d\nyoo:%d\n",yahoo,yoo);
	return 0;

}






