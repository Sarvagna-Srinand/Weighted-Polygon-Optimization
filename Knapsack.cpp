    
#include <cmath> 
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <time.h>
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
#define ld long double
#define S second
#define B begin
int inf =  1e15 ; 

const int MAXN  =  100 ; 
namespace myrandom {
	uint64_t seed = 1234567891234567891;
	uint64_t xorshift64() {
		seed ^= seed << 13;
		seed ^= seed >> 7;
		seed ^= seed << 17;
		return seed;
	}
	int64_t next_int(int64_t l, int64_t r) {
		assert(l <= r);
		return l + xorshift64() % (r - l);
	}
	double next_double(double l, double r) {
		double z = double(xorshift64()) / double(uint64_t(-1));
		return l + z * (r - l);
	}
}
int score = 0 ; 
int cnt = 0 ;
int e = 0 ; 
void dfs(vector <vector <int>>& grid , vector <vector <bool>>& visited , vector <vector <int>>& num,  int x , int y ){
	visited[x][y] = true ; 
	score += grid[x][y] ; 
	num[x][y] = cnt ; 
	for(int j = -1 ; j <=1 ; j++){
		for(int k = - 1 ; k <=1 ; k ++){
			if(abs(j) + abs(k) == 1){
				if(x + j >= 0 and x + j < MAXN and y + k >= 0 and y + k < MAXN and !visited[x + j][y + k] and grid[x + j][y + k] >= 0){
					dfs(grid , visited , num , x + j , y + k) ; 
				}
			}
		}
	}
}

void dfs_holes(vector <vector <int>>& grid , vector <vector <bool>>& visited , vector <vector <int>>& num,  int x , int y , set <int>& neigh){
    visited[x][y] = true ; 
    score += grid[x][y] ; 
    num[x][y] = cnt ; 
    if(x == 0 or y == 0 or x == MAXN - 1 or y == MAXN - 1){
        e = 1 ; 
        
    }
    for(int j = -1 ; j <= 1 ; j ++){
        for(int k = -1 ; k <= 1 ; k ++){
            if((abs(j) + abs(k)) == 1){
                if(x + j >= 0 and x + j < MAXN and y + k >= 0 and y + k < MAXN and !visited[x + j][y + k] and grid[x + j][y + k] <= 0){
                    dfs_holes(grid , visited , num , x + j , y + k , neigh) ; 
                }
				if(x + j >= 0 and x + j < MAXN and y + k >= 0 and y + k < MAXN and grid[x + j][y + k] >= 0 and num[x + j][y + k] > 0){
                    neigh.insert(num[x + j][y + k]) ;
                }

            }
        }
    }
}

bool is_vertex(int x , int y , int z , int w , vector <vector <int>>& num){
	if(x  == z and y == w){
        int e = 0 ; int e1 = 0 ; 
		if(x > 0 and num[x - 1][y] == num[x][y]){e ++ ;}
		if(y > 0 and num[x][y - 1] == num[x][y]){e ++ ; }
        if(x > 0 and y > 0  and num[x - 1][y - 1] == num[x][y]){e1 ++  ; }
        if(e == 1 and e1 == 0){return false ; }
        if(e == 2 and e1 == 1){return false ; }
	}
	if(x == z and y == w - 1){
        int e = 0 ; int e1 = 0 ; 
		if(x > 0 and num[x - 1][y] == num[x][y]){e++  ;  }
		if(y < MAXN-1 and num[x][y + 1] == num[x][y]){e++ ; }
        if(x > 0 and y < MAXN - 1 and num[x - 1][y + 1] == num[x][y]){e1 ++ ; }
        if(e == 1 and e1 == 0){return false ; }
        if(e == 2 and e1 == 1){return false ; }
	}
	if(x == z - 1 and y == w){
        int e = 0 ;  int e1 = 0 ; 
		if(x < MAXN-1 and num[x + 1][y] == num[x][y]){e++ ; }
		if(y > 0 and num[x][y - 1] == num[x][y]){e++ ; }
		if(x < MAXN - 1 and y > 0 and num[x + 1][y - 1] == num[x][y]){e1 ++ ; }
        if(e == 1 and e1 == 0){return false ; }
        if(e == 2 and e1 == 1){return false ; }
	}
	if(x == z - 1 and y == w - 1){
        int e = 0 ; int e1 = 0 ; 
		if(x < MAXN-1 and num[x + 1][y] == num[x][y]){e ++  ; }
		if(y < MAXN-1 and num[x][y + 1] == num[x][y]){e ++ ; }
		if(x < MAXN - 1 and y < MAXN - 1 and num[x + 1][y + 1] == num[x][y]){e1 ++ ; }
        if(e == 1 and e1 == 0){return false ; }
        if(e == 2 and e1 == 1){return false ; }
	}
    return true ;
}

int32_t main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
    freopen("./final_input/input19.txt", "r", stdin); 
	// freopen("./chanduOutput.txt", "w", stdout);
    int n ; 
	cin >> n ; 
	int sum = 0 ; 
	vector <pair <pair <int , int> , int>> arr(1e4 + 5) ; 
	for(int i = 0 ; i < n ; i++){
		cin >> arr[i].first.first >> arr[i].first.second >> arr[i].second ; 
		sum += arr[i].second ; 
	}
	int m ; 
	cin >> m  ; 
	for(int j = 0 ; j < m ; j ++){
		ll a , b , c ;
		cin >> a >> b >> c ; 
		arr[n + j] = {{a , b} , -c} ;
	}

	
	vector <vector <int>> grid(MAXN + 5, vector <int> (MAXN  + 5, 0)) ;
	vector <vector <bool>> visited(MAXN + 5 , vector <bool> (MAXN + 5 , false)) ;
	vector <vector <int>> num(MAXN + 5 , vector <int> (MAXN + 5 , 0)) ;
	for(int j =  0 ; j < (n + m) ; j ++){
		int x = arr[j].first.first / ((10000 + MAXN ) / MAXN) ; 
		int y = arr[j].first.second / ((10000 + MAXN ) / MAXN); 
		grid[x][y] += arr[j].second ; 
	}
	vector <pair <int , int>> cluster_data ; 
	
	cnt = 1 ; 
	int pos_cnt = 0  ;
	cluster_data.push_back({0 , 0}) ; 
	for(int j = 0 ; j < MAXN ; j ++){
		for(int k = 0 ; k < MAXN ; k ++){
			if(grid[j][k] > 0){pos_cnt ++ ; }
			if(grid[j][k] > 0 and !visited[j][k]){
				score = 0 ; 
				dfs(grid , visited , num , j , k ) ; 
				cluster_data.push_back({score , 1}) ; 
				cnt ++ ; 
			}
		}
	}
    int pos = cnt ; 
	set <pair <int , int>> s[MAXN * MAXN + 1] ; 
	set <pair <int , int>> vertices_overall ; 
	for(int j = 0 ; j < MAXN ; j ++){
		for(int k = 0 ; k < MAXN ; k ++){
			if(num[j][k]){
				if(is_vertex(j , k , j  , k , num)){
					s[num[j][k]].insert({j , k}) ; 
					vertices_overall.insert({j , k}) ;
				}
				if(is_vertex(j , k , j   , k + 1 , num)){
					s[num[j][k]].insert({j , k + 1}) ; 
					vertices_overall.insert({j , k + 1}) ;
				}
				if(is_vertex(j , k , j + 1  , k , num)){
					s[num[j][k]].insert({j + 1 , k }) ; 
					vertices_overall.insert({j + 1 , k}) ;
				}
				if(is_vertex(j , k , j +1 , k  + 1, num)){
					s[num[j][k]].insert({j + 1, k + 1}) ; 
					vertices_overall.insert({j + 1 , k + 1}) ;
				}
			}
		}
	}
    int tot_verti = 0 ; 
    int pos_score = 0 ; 
	for(int j  = 1 ; j < cluster_data.size() ; j++){
		cluster_data[j].second = s[j].size() ;
        tot_verti += s[j].size() ;
        pos_score += cluster_data[j].first ;
	}
	int tot = vertices_overall.size() ;
	cout << tot << endl ; 
	cout << "Priniting the cluster data" << endl ;

	cout << tot_verti << " " << pos_score << " " << cluster_data.size() - 1 <<  endl ; 
	// for(int j =1 ; j < cluster_data.size() ; j ++){
	// 	cout << cluster_data[j].first << " " << cluster_data[j].second  << endl ; 
	// }

	// for(int j = 0 ; j < MAXN ; j ++){
	// 	for(int k = 0 ; k  < MAXN ; k ++){
	// 		cout << (visited[j][k] ? "#" : ".") ;
	// 	}
	// 	cout << endl ; 
	// }
    vector <pair <int ,int>> cluster_holes ; 
	cluster_holes.push_back({0 , 0 }) ; 
	int startHoles = cnt ;
	vector <int> hole_num ; 
	hole_num.push_back(0) ; 
    for(int j = 0 ; j  < MAXN ; j ++){
        for(int k = 0 ; k < MAXN ; k ++){
            if(grid[j][k] <= 0 and !visited[j][k]){
                score = 0 ; 
                e = 0 ; 
				set <int> neigh ; 
				dfs_holes(grid , visited , num , j , k , neigh) ; 
                if(e == 0){
					hole_num.push_back(cnt) ; 
					cluster_holes.push_back({-score , cnt}) ; 
				}
                cnt ++ ; 
            }
        }
    }
	
    for(int j = 0 ; j < MAXN ; j ++){
		for(int k = 0 ; k < MAXN ; k ++){
			if(num[j][k] >= pos){
				if(is_vertex(j , k , j  , k , num)){
					s[num[j][k]].insert({j , k}) ; 
				}
				if(is_vertex(j , k , j   , k + 1 , num)){
					s[num[j][k]].insert({j , k + 1}) ; 
				}
				if(is_vertex(j , k , j + 1  , k , num)){
					s[num[j][k]].insert({j + 1 , k }) ; 
				}
				if(is_vertex(j , k , j +1 , k  + 1, num)){
					s[num[j][k]].insert({j + 1, k + 1}) ; 
				}
			}
		}
	}
    int hole_sum  = 0 ; 
    for(int j = 1 ; j < cluster_holes.size() ; j++){
        cluster_holes[j].second = s[cluster_holes[j].second].size() + 2 ;
		hole_sum += cluster_holes[j].first ; 
    }

	cout << "Printing the cluster holes" << endl ;
	cout << cluster_holes.size() - 1 << " " << hole_sum << endl ; 
	for(int j = 1 ; j < cluster_holes.size() ; j ++){
		// cout << cluster_holes[j].second << " " << cluster_holes[j].first << endl ;
	}
    

     
    // Reverse Knapsack
	int hole_cnt = cluster_holes.size() - 1  ; 
    int tar = max(tot_verti + (hole_cnt)*2 - 550 , 0LL) ; 
	cout << tar << endl ; 
    vector <vector <int>> dp1(cluster_holes.size() + 1 , vector <int> (tar + 5 , inf)) ;


    dp1[0][0] = 0 ; 
    for(int j = 1 ; j < cluster_holes.size() ; j++ ){
        for(int k = 0 ; k <= (tar + 2) ; k ++){
            dp1[j][k] = dp1[j - 1][k] ; 
            if(k <= cluster_holes[j].second){
                dp1[j][k] = min(dp1[j][k] , cluster_holes[j].first) ; 
            }
            else{
                dp1[j][k] = min(dp1[j][k] , dp1[j - 1][k - cluster_holes[j].second] + cluster_holes[j].first) ;
            }
		}

    }

    int curTarget = tar ;
	set<int> backtrackedholes;
	for(int j = cluster_holes.size() - 1 ; j >= 1 ; j --){
		if(curTarget >= cluster_holes[j].second and dp1[j][curTarget] >= dp1[j - 1][curTarget - cluster_holes[j].second] + cluster_holes[j].first){
			curTarget -= cluster_holes[j].second ; 
			backtrackedholes.insert(hole_num[j]) ;
		}
		else if(curTarget <= cluster_holes[j].second and dp1[j][curTarget] >=  cluster_holes[j].first){
			curTarget -= 0; 
			backtrackedholes.insert(hole_num[j]) ;
			break;
		}
	}

	int actualvalue = 0  ;

	vector<vector<int>> finalBoutput ( MAXN, vector<int> (MAXN , 0))  ; 
	for(int j = 0 ; j < MAXN ; j++){
		for(int k  = 0 ; k <MAXN ; k++){
			if(backtrackedholes.find(num[j][k]) != backtrackedholes.end()){
				finalBoutput[j][k] = 1 ; 
				actualvalue += grid[j][k] ;
			}
			else if (num[j][k] >= 1 && num[j][k] <= pos){
				finalBoutput[j][k] = 1 ; 
				actualvalue += grid[j][k] ;
			}
		}
	}

	set<pair<int,int>> finalVertices ; 
	for(int j = 0 ; j < MAXN ; j ++){
		for(int k = 0 ; k < MAXN ; k ++){
			if(finalBoutput[j][k]){
				if(is_vertex(j , k , j  , k , finalBoutput)){
					finalVertices.insert({j , k}) ; 
				}
				if(is_vertex(j , k , j   , k + 1 , finalBoutput)){
					finalVertices.insert({j , k + 1}) ; 
				}
				if(is_vertex(j , k , j + 1  , k , finalBoutput)){
					finalVertices.insert({j + 1 , k }) ;
				}
				if(is_vertex(j , k , j +1 , k  + 1, finalBoutput)){
					finalVertices.insert({j + 1, k + 1}) ; 
				}
			}
		}
	}

	cerr << "curtarget " <<  curTarget << endl ; 
	cerr << "finalvertice " << finalVertices.size() << endl; 


	freopen("./output.txt", "w", stdout);

	for(int j = 0 ; j < MAXN ; j ++){
		for(int k = 0 ; k < MAXN ; k ++){
			cout << (finalBoutput[j][k] ) << " " ; 
		}
		cout << endl ; 
	}

	fclose(stdout) ;

	


	cout << "Reverse Knapsack answer" << endl ;
    if(dp1[cluster_holes.size() - 1][tar] >= inf){
        cout << "No Solution" << endl ; 
    }
    else{
        cout << pos_score -dp1[cluster_holes.size() - 1][tar] << endl ; 
        cout << (((pos_score -dp1[cluster_holes.size() - 1][tar] ) * 1.0) / sum) << endl << endl << endl  ; 
        cout << (((actualvalue) * 1.0) / sum) << endl << endl << endl  ; 

    }


	// dp exact 


	 
	return 0;
    
}