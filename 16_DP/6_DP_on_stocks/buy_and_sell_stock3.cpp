// buy and sell atmost 2 times with max profit and no overlap
#include<bits/stdc++.h>

using namespace std;

//Recursion
int solve_recursion(vector<int>&prices, int idx, int buy, int k){
	if(idx==prices.size() || k==0){
		return 0;
	}

    int profit = 0;
	if(buy){
		profit = max(-prices[idx]+solve_recursion(prices, idx+1, 0, k), 
			         0 + solve_recursion(prices, idx+1, 1, k));
	}
	else{
		profit = max(prices[idx]+solve_recursion(prices, idx+1, 1, k-1),
			         0 + solve_recursion(prices, idx+1, 0, k));
	}
	return profit;
}

// Memoization
int memoization(vector<int>&prices, int idx, int buy, int k,
	   				vector<vector<vector<int>>>&dp){
	if(idx==prices.size() || k==0){
		return 0;
	}
	if(dp[idx][buy][k]!=-1){
		return dp[idx][buy][k];
	}

	int profit = 0;
	if(buy){
		profit = max(-prices[idx]+memoization(prices, idx+1, 0, k, dp), 
			         0 + memoization(prices, idx+1, 1, k, dp));
	}
	else{
		profit = max(prices[idx]+memoization(prices, idx+1, 1, k-1, dp),
			         0 + memoization(prices, idx+1, 0, k, dp));
	}
	return dp[idx][buy][k] = profit;
}

void solve_memoization(vector<int>&prices){
	vector<vector<vector<int>>>dp(prices.size()+1, vector<vector<int>>(2, vector<int>(3, -1)));
	cout<<"memoization solution: "<<memoization(prices, 0, 1, 2, dp)<<endl;
}

//Tabulation

int tabulation(vector<int>&prices, vector<vector<vector<int>>>&dp){
	//base case idx==prices.size()
	for(int buy=0; buy<=1; buy++){
		for(int k=0;k<=2;k++){
			dp[prices.size()][buy][k]=0;
		}
	}

    //base case k==0
	for(int idx=prices.size(); idx>=0; idx--){
		for(int buy=0; buy<=1; buy++){
			dp[idx][buy][0] = 0;
		}
	}

	for(int idx=prices.size()-1; idx>=0; idx--){
		for(int buy = 0; buy<=1; buy++){
			for(int k=1; k<=2; k++){
				if(buy){
				    dp[idx][buy][k] = max(-prices[idx]+dp[idx+1][0][k], 
					                     0 + dp[idx+1][1][k]);
			    }
			    else{
				    dp[idx][buy][k] = max(prices[idx]+dp[idx+1][1][k-1],
					                     0 + dp[idx+1][0][k]);
			    }	
			}
		}
	}
	return dp[0][1][2]; 
}

void solve_tabulation(vector<int>&prices){
	vector<vector<vector<int>>>dp(prices.size()+1, vector<vector<int>>(2, vector<int>(3, -1)));
	cout<<"tabulation solution: "<<tabulation(prices, dp)<<endl;
}

int main(){
	int n;
	cin>>n;
	vector<int>prices(n,0);
	for(int i=0;i<n;i++){
		cin>>prices[i];
	}
	cout<<"Recursion solution: "<<solve_recursion(prices,0,1,2)<<endl;
	solve_memoization(prices);
	solve_tabulation(prices);
	return 0;
}