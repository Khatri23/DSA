#include<iostream>
#include<vector>

bool Valid(std::vector<std::vector<int>>&grid,int x,int y){
    return x >=0 && x < grid.size() && y>=0 && y<grid.size() &&(!grid[x][y] || grid[x][y]==-1);
}
//greedy approach to choose the shortes move toward the knight.
std::pair<int,int> minimum_moves(std::vector<std::vector<int>>&grid,int x,int y,std::vector<int>&XMoves,std::vector<int>&Ymoves,const int& x_enemy,const int& y_enemy){
    
    std::pair<int,int>result={x,y};
    int min=INT_MAX;
    for(int i=0;i<XMoves.size();i++){
        int temp_x=x+XMoves[i]; //next possible moves.
        int temp_y=y+Ymoves[i];
        if(Valid(grid,temp_x,temp_y)){
            int dist=abs(x_enemy-temp_x)+abs(y_enemy-temp_y);//simple distance formula.
            if(dist==0){
                return {temp_x,temp_y};//the problem is solved.
            }
            else if(dist < min){ //checking if my selected next move is optimal.
                min=dist;
                result={temp_x,temp_y};
            }
        }
    }
    return result; //minimum pair.
}
bool check_mate(std::vector<std::vector<int>>&grid,int x,int y,int& enemy_x,int& enemy_y,std::vector<int>&XMoves,std::vector<int>&Ymoves,int moves){
     if(x==enemy_x && y==enemy_y) return true;
    std::pair<int,int>next=minimum_moves(grid,x,y,XMoves,Ymoves,enemy_x,enemy_y);
    grid[next.first][next.second]=moves;
    
    if(check_mate(grid,next.first,next.second,enemy_x,enemy_y,XMoves,Ymoves,moves+1))
    return true;
    else
    grid[next.first][next.second]=0; //backtracking.
    return false;
}
void solution(){
    std::vector<std::vector<int>> grid(8,std::vector<int>(8,0));
    grid[0][0]=-2;//denote the horse.
    int x=7,y=0;
    grid[x][y]=-1; //denotes the king. 
    //knight move.
    std::vector<int> XMove = { 2, 1, -1, -2, -2, -1, 1, 2 };
    std::vector<int> YMove = { 1, 2, 2, 1, -1, -2, -2, -1 };
    if(check_mate(grid,0,0,x,y,XMove,YMove,1)){
        for(auto x:grid){
            for(auto y: x)
            std::cout<<y<<"\t ";
            std::cout<<std::endl;
        }
    }
}
int main(){
    solution();
    return 0;
}