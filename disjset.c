#include <stdio.h>
#include <stdlib.h>

int find_it(int parent[], int idx){
    if(parent[idx]==idx){
        return idx;
    }
    else{
        parent[idx] = find_it(parent, parent[idx]);
        return parent[idx];
    }
}

void union_it(int parent[], int x, int y){
    int parent_x = find_it(parent, x);
    int parent_y = find_it(parent, y);
    parent[parent_y] = parent_x;
}

void print_arr(int parent[], int parent_len){
    for(int i=0;i<parent_len;i++){
        printf("%d ",parent[i]);
    }
    printf("\n");
}

int convert_idx(int i, int j, int bre){
    int val = (i*bre) + j;
    return val;
}

void matrix2disj(int parent[], int* arr, int len, int bre){
    for(int i=0;i<len;i++){
        for(int j=0;j<bre;j++){
            if(*(arr+(i*bre)+j)==1){
                if(i-1>=0 && *(arr+((i-1)*bre)+j)==1){
                union_it(parent,convert_idx(i,j,bre),convert_idx(i-1,j,bre));
                }
                if(i+1<=len-1 && *(arr+((i+1)*bre)+j)==1){
                    union_it(parent,convert_idx(i,j,bre),convert_idx(i+1,j,bre));
                }
                if(j-1>=0 && *(arr+((i)*bre)+j-1)==1){
                    union_it(parent,convert_idx(i,j,bre),convert_idx(i,j-1,bre));
                }
                if(j+1<=bre-1 && *(arr+((i)*bre)+j+1)==1){
                    union_it(parent,convert_idx(i,j,bre),convert_idx(i,j+1,bre));
                }
                if((j-1>=0 && i-1>=0) && *(arr+((i-1)*bre)+j-1)){
                    union_it(parent,convert_idx(i,j,bre),convert_idx(i-1,j-1,bre));
                }
                if((j-1>=0 && i+1<=len-1) && *(arr+((i+1)*bre)+j-1)){
                    union_it(parent,convert_idx(i,j,bre),convert_idx(i+1,j-1,bre));
                }
                if((j+1<=bre-1 && i-1>=0) && *(arr+((i-1)*bre)+j+1)){
                    union_it(parent,convert_idx(i,j,bre),convert_idx(i-1,j+1,bre));
                }
                if((j+1<=bre-1 && i+1<=len-1) && *(arr+((i+1)*bre)+j+1)){
                    union_it(parent,convert_idx(i,j,bre),convert_idx(i+1,j+1,bre));
                }
            }
        }
    }
}

int count(int* arr, int bre, int parent[], int parent_len){
    int count = 0;
    const is_visited_len = parent_len;
    int is_visited[is_visited_len];
    for(int i=0;i<parent_len;i++){
        is_visited[i] = 0;
    }
    int r,c;
    for(int i=0;i<parent_len;i++){
        r = i/bre;
        c = i%bre;
        if(*(arr+(r*bre)+c)==1 && is_visited[i]==0){
            count++;
            for(int j=i;j<parent_len;j++){
                if(parent[j]==parent[i]){
                    is_visited[j] = 1;
                }
            }
        }
    }
    return count;
}

int main(){
    // -- If input is taken from user --
    // int len_inp,bre_inp;
    // printf("Enter the length and breadth: \n");
    // scanf("%d %d",&len_inp,&bre_inp);
    // const int len = len_inp;
    // const int bre = bre_inp;
    // int arr[len][bre];
    // for(int i=0;i<len;i++){
    //     for(int j=0;j<bre;j++){
    //         printf("Enter arr[%d][%d]: ",i,j);
    //         scanf("%d",&arr[i][j]);
    //     }
    // }

    // -- If input is taken directly --
    int len=5;
    int bre = 5;
    int arr[5][5] = {{1,1,0,0,0},{0,1,0,0,1},{1,0,0,1,1},{0,0,0,0,0},{1,0,1,0,1}};
    const int parent_len = len*bre;
    int parent[parent_len];
    for(int i=0;i<parent_len;i++){
        parent[i] = i;
    }
    matrix2disj(parent,&arr,len,bre);
    // print_arr(parent, parent_len);
    int num_islands = count(&arr,bre,parent,parent_len);
    printf("Number of islands is: %d\n",num_islands);
    return 0;
}