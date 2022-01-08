1) 0/1 KnapSack Problem
Input:
N = 4
W = 6
values[] = {1,2,3,4}
weight[] = {4,5,2,3}
Output: 7(wt == 2 && wt == 3 wla maal)
A.Top Down
int dp[1001][1001];
int knapSack(int W, int wt[], int val[], int n){
         
       if(n == 0 || W == 0) return 0;
       
       if(dp[n][W] != -1) return dp[n][W];
       
       
       if(wt[n-1] > W)
           //when dont select this current maal
           return dp[n][W] = knapSack1(W,wt,val,n-1);
       else
           //You have option to either select or unselect this maal
           return dp[n][W] = max(knapSack1(W,wt,val,n-1),
           val[n-1]+knapSack1(W-wt[n-1],wt,val,n-1));
           }
B. Bottom Up
int knapSack(int W, int wt[], int val[], int n){
    vector<vector<int>>dp(n+1,vector<int>(W+1,0));
    //dp[i][j] will store i size of array and weight of bag is j me max kitna maal daal skte
    //i ---> size of array and j ---> bag capacity
    for(int i = 1 ; i <= n ;i++){
       for(int j = 1 ; j <= W ; j++){
          //if current wght is high than bag then dont include this maal
          if(wt[i-1] > j) dp[i][j] = dp[i-1][j];
          else
          //else include max of ya include ya not include.
            dp[i][j] = max(dp[i-1][j], val[i-1] + dp[i-1][j-wt[i-1]);
       }
    }
    return dp[n][W];
}
2.Subset Sum
M-1 : Memoize/Top Down
 int isSubsetSum2(int N,int arr[],int sum,vector<vector<int>>&dp){
        if(sum == 0) return 1;
        if(N == 0) return 0;
        if(dp[N][sum] != -1)
           return dp[N][sum];
        
        if(arr[N-1] > sum) 
            return dp[N][sum] = isSubsetSum2(N-1,arr,sum,dp);
        else{
            return dp[N][sum] = isSubsetSum2(N-1,arr,sum,dp) || isSubsetSum2(N-1,arr,sum-arr[N-1],dp);
        }
        
        
    }
    bool isSubsetSum(int N, int arr[], int sum){
        
        vector<vector<int>>dp(N+1,vector<int>(sum+1,-1));
        return isSubsetSum2(N,arr,sum,dp);
    }
 M-2: Tabulation / Bottom Up
 bool isSubsetWithGivenSum(int arr[],int n,int sum){
   bool dp[n+1][sum+1];
   //i ---> size of array and j ---> sum

   //When size of array == 0 then false irrespective of sum except sum == 0.
   for(int i = 0,j=0; j <=sum ;j++) dp[i][j] = false;
   //When sum == 0 then true irrespective of size bcoz empty subsequence is for even n == 0.
   for(int i = 0 , j = 0 ; i <= n ;i++) dp[i][j] = true;

   for(int i = 1 ; i <= n ; i++){
      for(int j = 1 ; j <= sum ;j++)
         //if curr maal arr[i-1] is > then given sum i.e, j then ignore this maal
         if(arr[i-1] > j) dp[i][j] = dp[i-1][j];
         else
            //2 options ya to maal ko lo ya matiyao
            dp[i][j] = dp[i-1][j] || dp[i-1][j-arr[i-1]];
   }

   return dp[n][sum];      
  }
  Var-1
  bool isSubsetWithGivenDiff(int arr[],int n,int diff){
   int sum = accumulate(arr,arr+n,0);

   int val = (sum+diff)/2;

   return isSubsetWithGivenSum(arr,n,val);
}
Var-2 : Equal sum partition---> if sum is odd return false else find isSubsetWithGivenSum(arr,n,sum/2)
Var-3 : Count Subsets ----> Just Replace || with + sign.
  
  3. Minimum Subset Difference
  //The idea is to just find a subset as close as possible to sum/2.
  int minSubsetDifference(int n ,int arr[]){
   int sum = accumulate(arr,arr+n,0);
   int temp_sum = sum;
   sum = sum/2;
   bool dp[n+1][sum+1];
   //i--->sizeof array and j ---> sum
   for(int i = 0,j = 0; j < sum+1;j++) dp[i][j] = false;
   for(int i =0,j = 0 ; i < n+1;i++) dp[i][j] = true;
   
   for(int i = 1 ; i < n+1;i++){
      for(int j = 1; j < sum+1;j++){
         if(arr[i-1] > j) dp[i][j] = dp[i-1][j];
         else dp[i][j] = dp[i-1][j] || dp[i-1][j-arr[i-1]];
      }
   }
   int maxi_sum = 0;
   for(int i = n , j =sum ; j>= 0;j--){
      if(dp[i][j]){
         maxi_sum = j;
         break;
      }
   }
   int ans = abs(temp_sum - 2*maxi_sum);
   return ans;  
}
  
