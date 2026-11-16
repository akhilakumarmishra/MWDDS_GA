void random_heuristics(){
	int random_heuristic=(int)(u01*4);
	heuristics_number=(random_heuristic+1);
	// printf("r_h:%d",heuristics_number);
}
int* repairing(int chromosome[],int Nodeno,int** directed_graph,int nodeweightarr[],int heuristic){
	// atexit(report_mem_leak);
	// printf("\n***start of repairing function***\n");
	// printf("heuristics_number_R:%d\n",heuristics_number);
	// int* color = (int*)malloc(Nodeno*sizeof(int));
	int color[Nodeno];
	int i,j;
	
	for(i=0;i<Nodeno;i++){
		// printf("%d ",chromosome[i]);
		if(chromosome[i]!=1&&chromosome[i]!=0){
			printf("ERROR----->>%d has ODD VALUE:-  pos:%d \n",i,chromosome[i]); fflush(stdout);sleep(10);
		}
	}
	// printf("\n");
	int* chromosome_repairing=(int*)malloc(Nodeno*sizeof(int));
	for(i=0;i<Nodeno;i++){
		chromosome_repairing[i]=0;
	}
	for(i=0;i<Nodeno;i++){
		color[i]=1;
	}
	for(i=0;i<Nodeno;i++){
		if(chromosome[i]==1){
			color[i]=0;
			int k;
			for(k=0;k<Nodeno;k++){
				if(directed_graph[i][k]==1){
					color[k]=0;
				}
			}	
		}
	}
	int white_color_nodes=0;
	for(i=0;i<Nodeno;i++){
		if(color[i]==1)
		{
			white_color_nodes++;
		}
	}
	random_heuristics();
	
	// printf("r1=H%d\n",heuristics_number );
	int k;
//	float Ph=0.6;
	// float p =u01;
	float pp =u01;
	// printf("pp: %f",pp);
	//float PPh=0.4;
	if(pp< PPh){
		// printf("REPAIRING: heuristics:\n");
		// //int request=0;
		// int* chromosome_string=heuristics_H2(chromosome, Nodeno, directed_graph, nodeweightarr, color, white_color_nodes);
		// // printf("end of repairing\n");
		// for(i=0;i<Nodeno;i++){
		// 	chromosome[i]=chromosome_string[i];
		// }
		// // return chromosome_string;
		// printf("heuristics_number_Rm:%d\n",heuristics_number);
		if(heuristics_number==1){
			// printf("heuristics_number_Rx:%d\n",heuristics_number);printf("Anm1\n");
			// printf("REPAIRING: heuristics-1:\n");
			int* chromosome_string=heuristics_H1(chromosome, Nodeno, directed_graph, nodeweightarr, color, white_color_nodes);
			// printf("end of repairing\n");
			for(i=0;i<Nodeno;i++){
				chromosome_repairing[i]=chromosome_string[i];
			}
			// printf("Am1\n");
			free(chromosome_string);
		}
		else if(heuristics_number==2){
			// printf("REPAIRING: heuristics-2:\n");
			//int request=0;
			int* chromosome_string=heuristics_H2(chromosome, Nodeno, directed_graph, nodeweightarr, color, white_color_nodes);
			// printf("end of repairing\n");
			for(i=0;i<Nodeno;i++){
				chromosome_repairing[i]=chromosome_string[i];
			}
			// printf("Am2\n");
			free(chromosome_string);
		}
		else if(heuristics_number==3){
			// printf("REPAIRING: heuristics-3:\n");
			//int request=0;
			int* chromosome_string=heuristics_H3(chromosome, Nodeno, directed_graph, nodeweightarr, color, white_color_nodes);
			// printf("end of repairing\n");
			for(i=0;i<Nodeno;i++){
				chromosome_repairing[i]=chromosome_string[i];
			}
			// printf("Am3\n");
			free(chromosome_string);
		}
		else if(heuristics_number==4){
			// printf("REPAIRING:  heuristics-4:\n");
			//int request=0;
			int* chromosome_string=heuristics_H4(chromosome, Nodeno, directed_graph, nodeweightarr, color, white_color_nodes);
			// printf("end of repairing\n");
			for(i=0;i<Nodeno;i++){
				chromosome_repairing[i]=chromosome_string[i];
			}
			// printf("Am4\n");
			free(chromosome_string);
		}
		else{
			printf(" ERROR : choose correct heuristic\n");
		}


	}
	else{
		// printf("REPAIRING : random_node_repair\n");
			

			for(i=0;i<Nodeno;i++){
				chromosome_repairing[i]=chromosome[i];
				
			}
			for(i=0;i<Nodeno;i++){
				// printf("%d ",chromosome_repairing[i]);
				if(chromosome_repairing[i]!=1&&chromosome_repairing[i]!=0){
					printf("ERROR----->>%d has ODD VALUE:-  pos:%d \n",i,chromosome_repairing[i]); fflush(stdout);sleep(10);
				}
			}
			// printf("\n");
			int kk=0;
			int non_dominated_nodes_set[Nodeno];
			for(j=0;j<Nodeno;j++){
				if(chromosome_repairing[j]==0){
					non_dominated_nodes_set[kk]=j;
					kk++;
				}
			}
			// printf("kk=%d\n",kk);

			while(white_color_nodes!=0){

				// printf("in_while_in_else_RANDOM:%d\n",kk);
				// printf("white_color_nodes=%d\n",white_color_nodes);
				// int white_neighbour_sum[kk];
				// for(i=0;i<kk;i++){
				// 	int sum=0;
				// 	for(j=0;j<Nodeno;j++){
				// 		if(directed_graph[non_dominated_nodes_set[i]][j]==1 && color[j]==1){
				// 			sum+=nodeweightarr[j];
				// 		}
				// 	}
				// 	white_neighbour_sum[i]=sum;
				// }
				// float neighbourhood_ratio[kk];
					
				// for(j=0;j<kk;j++){
				// 	neighbourhood_ratio[j]=(float)white_neighbour_sum[j]/(float)nodeweightarr[non_dominated_nodes_set[j]];
				// }

				// float max=-1;
				// int max_indexno=-1;
				// for(j=0;j<kk;j++){
				// 	if(neighbourhood_ratio[j]>max){
				// 		max=neighbourhood_ratio[j];
				// 		max_indexno=non_dominated_nodes_set[j];
				// 	}
				// }
				// int max_nodes_arr[Nodeno];
				// int no_of_max_scores=0;
				
				// for(j=0;j<kk;j++){
				// 	if(max ==neighbourhood_ratio[j]){
				// 		max_nodes_arr[no_of_max_scores]=non_dominated_nodes_set[j];
				// 		no_of_max_scores++;
				// 	}
				// }
				// int random_node;
				// if(no_of_max_scores>1){
				// 	int random_node_x=(int)(u01*no_of_max_scores);
				// 	random_node=max_nodes_arr[random_node_x];
				// }
				// else{
				// 	random_node=non_dominated_nodes_set[max_indexno];
				// }


				
				// int outdegree[Nodeno];
				// int* out_deg=outdegree_calculation(Nodeno,diagraph);
				// for(i=0;i<Nodeno;i++){
				// 	outdegree[i]=out_deg[i];
				// }
				//***************
				int random_node = (int)(u01*kk);
				// printf("At %d random_node:%d color:%d\n",random_node,non_dominated_nodes_set[random_node],color[non_dominated_nodes_set[random_node]]);
				if(color[non_dominated_nodes_set[random_node]]==1){
					white_color_nodes--;
				}
				color[non_dominated_nodes_set[random_node]]=0;
				int rand_node_pos = non_dominated_nodes_set[random_node];
				chromosome_repairing[rand_node_pos]=1;
				
				
				for(j=random_node;j<kk;j++){
					non_dominated_nodes_set[j]=non_dominated_nodes_set[j+1];
				}
				kk =kk-1;
				for(j=0;j<Nodeno;j++){ 
					if(directed_graph[rand_node_pos][j]==1){
						if(color[j]!=0){
							color[j]=0; 		//grey color
							white_color_nodes--;
							
						}
					}

				}
				// printf(".\n");

			}
			// printf("end of repairing\n");
			// return chromosome;
	}
	for(i=0;i<Nodeno;i++){
		// printf("%d ",chromosome_repairing[i]);
		if(chromosome_repairing[i]!=1&&chromosome_repairing[i]!=0){
			printf("ERROR----->>%d has ODD VALUE:-  pos:%d \n",i,chromosome_repairing[i]); fflush(stdout);sleep(10);
		}
	}
	// printf("\n");
	return chromosome_repairing;
	
		
		
}

