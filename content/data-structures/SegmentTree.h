/**
 * Author: Andrew Tam
 * Date: 2025-8-11
 * Description: Minimum segment tree.
 * Can be changed to other things.
 * Time: O(\log N).
 * Status: trusted
 */
#pragma once

template<typename Data>
class SegmentTree{
private:
	int n;
	vector<Data>t;
	void build(int L,int R,int v,const vector<Data>&a){
		if(L==R){
			t[v]=a[L];return;
		}
		int M=(L+R)/2;
		build(L,M,2*v,a);
		build(M+1,R,2*v+1,a);
		t[v]=Data::merge(t[2*v],t[2*v+1]);
	}
	void update(int qI,const Data&val,int L,int R,int v){
		if(L==R){
			t[v]=val;return;
		}
		int M=(L+R)/2;
		if(qI<=M)update(qI,val,L,M,2*v);
		else update(qI,val,M+1,R,2*v+1);
		t[v]=Data::merge(t[2*v],t[2*v+1]);
	}
	Data query(int qL,int qR,int L,int R,int v){
		if(qL<=L && R<=qR)return t[v];
		if(qR<L || R<qL)return Data();
		int M=(L+R)/2;
		return Data::merge(query(qL,qR,L,M,2*v),query(qL,qR,M+1,R,2*v+1));
	}
public:
	SegmentTree(int n):n(n){
		t.resize(4*n);
	}SegmentTree(int n,const vector<Data>&a):n(n){
		t.resize(4*n);
		build(1,n,1,a);
	}void update(int qI,const Data&val){update(qI,val,1,n,1);}
	Data query(int qL,int qR){return query(qL,qR,1,n,1);}
};

struct Data{
	int v;
	Data(int v):v(v){}
	Data():v(inf){}
	static Data merge(const Data&data1,const Data&data2){
		return Data(min(data1.v,data2.v));
	};
};