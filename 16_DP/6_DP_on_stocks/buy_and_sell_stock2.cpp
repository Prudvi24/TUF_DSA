#include<bits/stdc++.h>

using namespace std;

//Recursive
int buy_sell_stock2(vector<int>&arr, int idx, int buy){
	if(idx==arr.size()){
		return 0;
	}
	int profit = 0;
	if(buy){
		// we take the maximum of buying and not buying the stock
		// on a specific day
		profit = max(-arr[idx]+buy_sell_stock2(arr, idx+1, 0),
			          0+buy_sell_stock2(arr, idx+1, 1));
	}
	else{
		// we take the maximum of selling and not selling the stock
		// on a specific day		
		profit = max(arr[idx]+buy_sell_stock2(arr, idx+1, 1),
			          0+buy_sell_stock2(arr, idx+1, 0));
	}
	return profit;
}

void solve_recursive(vector<int>&arr){
	int buy = 1;
	cout<<"Recursion output: "<<buy_sell_stock2(arr, 0, buy)<<endl;
}

//Memoization
int memoization(vector<int>&arr, int idx, int buy, vector<vector<int>>&dp){
	if(idx==arr.size()){
		return 0;
	}
	if(dp[idx][buy]!=-1){
		return dp[idx][buy];
	}
	int profit = 0;
	if(buy){
		// we take the maximum of buying and not buying the stock
		// on a specific day
		profit = max(-arr[idx]+memoization(arr, idx+1, 0, dp),
			          0+memoization(arr, idx+1, 1, dp));
	}
	else{
		// we take the maximum of selling and not selling the stock
		// on a specific day		
		profit = max(arr[idx]+memoization(arr, idx+1, 1, dp),
			          0+memoization(arr, idx+1, 0, dp));
	}
	return dp[idx][buy]=profit;
}

void solve_memoization(vector<int>&arr){
	vector<vector<int>>dp(arr.size()+1, vector<int>(2, -1));
	int res = memoization(arr,0, 1, dp);
	cout<<"memoization output: "<<res<<endl;
}

//Tabulation
int tabulation(vector<int>&arr, vector<vector<int>>&dp){
	dp[arr.size()][0] = 0;
	dp[arr.size()][1] = 0;
	for(int idx=arr.size()-1; idx>=0; idx--){
		for(int buy=1; buy>=0; buy--){
			if(buy){
				// we take the maximum of buying and not buying the stock
				// on a specific day
				dp[idx][buy] = max(-arr[idx]+dp[idx+1][0],
					          0+dp[idx+1][1]);
			}
			else{
				// we take the maximum of selling and not selling the stock
				// on a specific day		
				dp[idx][buy] = max(arr[idx]+dp[idx+1][1],
					          0+dp[idx+1][0]);
			}			
		}
	}
	return (dp[0][1]);
}

void solve_tabulation(vector<int>&arr){
	vector<vector<int>>dp(arr.size()+1, vector<int>(2, 0));
	int ans = tabulation(arr, dp);
	cout<<"Tabulation: "<<ans<<endl;
}

//space optimization
//2D --->  1D

int space_optimzation(vector<int>&arr){
	vector<int>next(2, 0), cur(2, 0);
	next[0]=0; next[1]=0;
	for(int idx=arr.size()-1; idx>=0; idx--){
		for(int buy=1; buy>=0; buy--){
			if(buy){
				// we take the maximum of buying and not buying the stock
				// on a specific day
				cur[buy] = max(-arr[idx]+next[0],
					          0+next[1]);
			}
			else{
				// we take the maximum of selling and not selling the stock
				// on a specific day		
				cur[buy] = max(arr[idx]+next[1],
					          0+next[0]);
			}			
		}
		next = cur;
	}
	return (next[1]);
}

int main(){
	int n;
	cin>>n;
	vector<int>arr(n,0);
	for(int i=0;i<n;i++){
		cin>>arr[i];
	}
	solve_recursive(arr);
	solve_memoization(arr);
	solve_tabulation(arr);
	cout<<"Space space_optimzation: "<<space_optimzation(arr)<<endl;
	return 0;
}