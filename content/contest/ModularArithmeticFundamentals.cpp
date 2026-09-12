const int mod = 1000000007;
int powmod(int b,int p,int md){
    int r=1;
    for(;p;p/=2){
        if(p&1)(r*=b)%=md;
        (b*=b)%=md;
    }
    return r;
}
int invert(int x){
    return powmod(x,mod-2,mod);
}
const int F = 2000001;
int fac[F];
int ifac[F];
void setup(){
	fac[0]=1;
	rep(i,1,F)fac[i]=(i*fac[i-1])%mod;
	ifac[F-1]=invert(fac[F-1]);
	rev(i,1,F-1)ifac[i-1]=(i*ifac[i])%mod;
}
int comb(int n,int k){
	if(n<0 || k<0 || k>n)return 0;
	int x=(fac[n]*ifac[k])%mod;
	return(x*ifac[n-k])%mod;
}