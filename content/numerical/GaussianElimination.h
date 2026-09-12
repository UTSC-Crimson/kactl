/**
 * Author: Evan Simanovskis
 * Date: 2025-7-15
 * Source: Thomas Kielstra
 * Description: Perform Gaussian Elimination on the input matrix
 * Return a pair consisting of the number of linearly independent column vectors in the first s columns and a vector pivot
 * where pivot[j] refers to the row i containing a 1 in the jth column and zeroes before (if such a row exists), and -1 otherwise.
 * Compare with epsilon if using floats
 * Time: O(n^3)
 * Status: Well trusted
 */
pair<int,vi>gaussian(vector<vector<int>>&mat,int s){
    if(mat.empty())return{0,{}};
    int n=sz(mat),m=sz(mat[0]),c=0;
    vi piv(s,-1);
    for(int i=0;i<s;i++){
        int r=c;
        while(r<n && mat[r][i]==0)r++; // compare with epsilon if using floats
        if(r==n)continue;
        piv[i]=c;
        rep(j,i,m)swap(mat[c][j],mat[r][j]);
        int iv=invert(mat[c][i]);
        rev(j,i,m-1)(mat[c][j]*=iv)%=mod;
        fox(j,n){
            if(j==c)continue;
            rev(k,i,m-1)(mat[j][k]+=mod-(mat[c][k]*mat[j][i])%mod)%=mod;
        }
        c++;
    }
    return{c,piv};
}