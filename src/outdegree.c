int* outdegree_calculation(int Nodeno,int** diagraph){
	int* outdegree=(int*)malloc(Nodeno *sizeof(int));
	int i,j;
	for(i=0;i<Nodeno;i++){
		outdegree[i]=0;
	}
	for(i=0;i<Nodeno;i++){
		int node_outdegree=0;
		for(j=0;j<Nodeno;j++){
			if(diagraph[i][j]==1){
				node_outdegree+=1;
			}
		}
		outdegree[i]=node_outdegree;
	}
	return outdegree;
}


int* indegree_calculation(int Nodeno,int** diagraph){
	int* indegree=(int*)malloc(Nodeno * sizeof(int));
	int i,j;
	for(i=0;i<Nodeno;i++){
		indegree[i]=0;
	}
	for(i=0;i<Nodeno;i++){
		for(j=0;j<Nodeno;j++){
			if(diagraph[j][i]==1){
				indegree[i]+=1;
			}
		}
	}
	return indegree;
/*Done*/
}

int wrost_fit_chromosome(int fitness_arr[],int pop_size){
	
	int max = fitness_arr[0];
	int index =0;
	int i;
	for(i=1;i<pop_size;i++){
		if(fitness_arr[i]>max){
			max = fitness_arr[i];
			index= i;
		}
	}
	return index;
}

int unique(int offspring[],int offspring_fitness,int Nodeno, int pop_size,int** population,int pop_fitness_array[]){
	
	int i,j;
	int match=0;
	int count=0;
	for(i=0;i<pop_size;i++){
		if(offspring_fitness==pop_fitness_array[i]){
			match++;
			int flag=0;
			for(j=0;j<Nodeno;j++){
				if(offspring[j]!=population[i][j]){
					flag=1;
					break;
					// flag++;
				}	
			}
			if(flag==1){
				count++;
				flag=0;
			}		
		}
	}
	if(count == match){
		return 0;
	}
	return 1;
}

int unique_population(int offspring[],int offspring_fitness,int Nodeno, int pop_size,int** population,int pop_fitness_array[]){
	
	int i,j;
	int match=0;
	int count=0;
	for(i=0;i<pop_size;i++){
		if(offspring_fitness==pop_fitness_array[i]){
			return 1;		
		}
	}
	
	return 0;
}

int unique_similar(int offspring[],int Nodeno,int similar_count,int** similar_fit_chromosome){
	int i,j;
	int match=0;
	int count=0;
	for(i=0;i<similar_count;i++){
		// if(offspring_fitness==pop_fitness_array[i]){
			match++;
			int flag=0;
			for(j=0;j<Nodeno;j++){
				if(offspring[j]!=similar_fit_chromosome[i][j]){
					flag=1;
					break;
					// flag++;
				}	
			}
			if(flag==1){
				count++;
				flag=0;
			}		
		// }
	}
	if(count == match){
		return 0;
	}
	return 1;
}
