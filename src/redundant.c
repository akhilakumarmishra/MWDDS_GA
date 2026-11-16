int* neighbour_redundants_finds(int chromosome[],int Nodeno,int** directed_graph,int nodeweightarr[]){
	int i,j,k=0; 
	int dom_count=0;
	int dominating_set_node[Nodeno];
	for(i=0;i<Nodeno;i++){
		if(chromosome[i]==1){
			dominating_set_node[dom_count]=i;
			dom_count++;
		}
	}
	int redundant_nodes[Nodeno];
	for(i=0;i<dom_count;i++){
		int remove_node=dominating_set_node[i];
		dominating_set_node[i]=-1;
		close_neightbour[Nodeno];
		open_neighbour[Nodeno];
		close_neightbour[remove_node]=1;
		int close_count=0;
		close_count++;
		for(j=0;j<Nodeno;j++){
			if(directed_graph[remove_node][j]==1){
				close_neightbour[j]=1;
				close_count++;
			}
		}
		for(j=0;j<dom_count;j++){
			if(dominating_set_node[j]!=-1){
				for(k=0;k<Nodeno;k++){
					if(directed_graph[dominating_set_node[j]][k]==1){
						open_neighbour[k]=1;
					}
				}
			}
		}
		int count =0;
		for(j=0;j<Nodeno;j++){
			if(close_neightbour[j]==1 && open_neighbour[j]==1){
				count++;
			}
		}
		if(close_count==count){
			redundant_nodes[remove_node]=1;
		}
		else{
			dominating_set_node[i]=remove_node;
		}
		for(j=0;j<Nodeno;j++){
			close_neightbour[j]=0;
			open_neighbour[j]=0;
		}
		
	}
	int* final_redundant_node_set=(int*)malloc((Nodeno)*sizeof(int));
	for(i=0;i<Nodeno;i++){
		final_redundant_node_set[i]=0;
	}
	
	for(j=0;j<x;j++){
		final_redundant_node_set[j]=redundant_nodes[j];
	}
	
	return final_redundant_node_set;

}