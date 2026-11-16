
	//printf("\nSKYfall\n");
	
	//R = redundants_finds(second_dominating_set,Nodeno,diagraph,nodeweightarr);
		// for(i=0;i<Nodeno;i++){
		// 	redundant_nodes[i]=R[i];
		// }
		// for(i=0;i<Nodeno;i++){
		// 	dominating_set_node[i]=second_dominating_set[i];
		// }
	
	// }
	
	//free(second_dominating_set);

	// printf("redundant_nodes_after cover\n");
	// for(i=0;i<Nodeno;i++){
	// 	printf("%d ",redundant_nodes[i]);
	// }
	// count=0;
	// for(i=0;i<Nodeno;i++){
	// 	if(redundant_nodes[i]==1){
	// 		count++;
	// 	}
	// }
	
/*

	fitness=0;
	for(i=0;i<Nodeno;i++){
		fitness += dominating_set_node[i];
	}
	if(fitness<chromosome_fitness){
		return dominating_set_node;
	}
	else{
		
		if(count==0){
			return dominating_set_node;
		}
		else{
			//second stage
			int outdegree[Nodeno];
			int* out_deg=outdegree_calculation(Nodeno,diagraph);
			for(i=0;i<Nodeno;i++){
				outdegree[i]=out_deg[i];
			}
			while(count!=0){
				int final_redundant;
				float red_prob=u01;
				float Pr=0.3;
				if(red_prob>Pr){

					float ratio_arr[Nodeno];
					for(i=0;i<Nodeno;i++){
						if(redundant_nodes[i]==1){
							ratio_arr[i]=(float)nodeweightarr[i] / (float)outdegree[i];
						}
					}
					float max_ratio=ratio_arr[0];
					int max_ratio_index=0;
					for(i=1;i<Nodeno;i++){
						if(ratio_arr[i]>max_ratio){
							max_ratio=ratio_arr[i];
							max_ratio_index = i;
						}
					}
					final_redundant=max_ratio_index;
				}
				else{
					int redundant_set[Nodeno];
					int r=0;
					for(i=0;i<Nodeno;i++){
						if(redundant_nodes[i]==1){
							redundant_set[r]=i;
							r++;
						}
					}
					int random_redundant = u01*r;
					final_redundant=redundant_set[random_redundant];

				}
				redundant_nodes[final_redundant]=0;
				for(i=0;i<Nodeno;i++){
					if(redundant_nodes[i]==1){
						dominating_set_node[i]=1;
					}
				}
				int c =0;
				R = redundants_finds(dominating_set_node,Nodeno,diagraph,nodeweightarr);
				for(i=0;i<Nodeno;i++){
					redundant_nodes[i]=R[i];
					if(redundant_nodes[i]==1){
						c++;
					}
				}
				count = c;
			}
			printf("\n+a100\n");
			return dominating_set_node;
		}
	}

*/	






















//redundant find


	// int* dominated_set_node=(int*)malloc((Nodeno) * sizeof(int));
	// // printf("\n+a4\n");
	// for(i=0;i<Nodeno;i++){
	// 	if(final_redundant_node_set[i]!=1){
	// 		dominated_set_node[i]=chromosome[i];
	// 	}
	// 	else{
	// 		dominated_set_node[i]=0;
	// 	}
	// }

	// for(i=0;i<Nodeno;i++){
	// 	if(final_redundant_node_set[i]==1){
	// 		// printf("red:%d \n",i);
	// 		for(j=0;j<Nodeno;j++){
	// 			if(dominated_set_node[j]==1){
	// 				// printf("dom:%d  %d",j,directed_graph[j][i]);

	// 				if(directed_graph[j][i]==1){
	// 					final_redundant_node_set[i]=0;
	// 					// printf("\n %d covered by %d\n",i,j);
	// 					break;
	// 				}
	// 			}
	// 		}
	// 	}
	// }
	// free(dominating_set_node);
	// free(dominated_set_node);
	// free(redundant_nodes);













	//open neighbourhood 
	/*for(i=0;i<k;i++){
		int neighbour_v_node[Nodeno];
		int m=0;
		
		for(j=0;j<Nodeno;j++){
			neighbour_v_node[j]=-1;
		}
		
		printf("\nneighbour of %d >>",dominating_set_node[i]);
		for(j=0;j<Nodeno;j++){
			if(directed_graph[dominating_set_node[i]][j]==1){
				int in_dom_set=0;
				int l;
				for(l=0;l<k;l++){
					if(j== dominating_set_node[l]){
						in_dom_set=1;
						break;
					}

				}
				if(in_dom_set==0){
					neighbour_v_node[m]=j;
					printf("%d ",neighbour_v_node[m]);
					m++;
				}
			}
		}
		
		neighbour_v_node[m]=dominating_set_node[i];
		printf("%d\n",neighbour_v_node[m]);
		m++;
		int total_neighbours_v = m;
		printf("total_neighbours_v: %d\n",total_neighbours_v);
		int l;
		int connection_exist=0;
		for(l=0;l<m;l++){
			int connect_count=0;
			for(j=0;j<k;j++){
				if(dominating_set_node[j]!=-1 && directed_graph[dominating_set_node[j]][neighbour_v_node[l]]==1 && dominating_set_node[j]!=dominating_set_node[i]){
					
					connect_count++;
					printf("%d covered by %d\n",neighbour_v_node[l],dominating_set_node[j]);
					break;
				}
			}
			if(connect_count>=1){
				connection_exist++;
			}
			else{
				printf("%d not covered\n",neighbour_v_node[l]);
			}


		}
		// printf("\n******\n");
		if(connection_exist==total_neighbours_v){
			redundant_nodes[x] = dominating_set_node[i];
			dominating_set_node[i]=-1;
			x++;
		}
	}

	int* final_redundant_node_set=(int*)malloc((Nodeno)*sizeof(int));
	for(i=0;i<Nodeno;i++){
		final_redundant_node_set[i]=0;
	}
	
	for(j=0;j<x;j++){
		final_redundant_node_set[redundant_nodes[j]]=1;
	}
	// printf("final_redundant_node_set\n");
	// for(i=0;i<Nodeno;i++){
	// 	printf("%d ",final_redundant_node_set[i]);
	// }
	// printf("\n");
*/