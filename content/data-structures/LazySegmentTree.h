/**
 * Author: Andrew Tam
 * Date: 2025-8-11
 * Description: Lazy segment tree that supports adding and setting intervals.
 * Can be changed to other things.
 * Time: O(\log N).
 * Status: trusted
 */
#pragma once

template<typename Data,typename Aux>
class LazySegmentTree{
private:
	int n;
	vector<Data>t;
	vector<Aux>lz;
	void build(int L,int R,int v,const vector<Data>&a){
		if(L==R){
			t[v]=a[L];return;
		}
		int M=(L+R)/2;
		build(L,M,2*v,a);
		build(M+1,R,2*v+1,a);
		t[v]=Data::merge(t[2*v],t[2*v+1]);
	}
	void push(int v,int len){
		lz[v].apply(t[2*v],lz[2*v],(len+1)/2);
		lz[v].apply(t[2*v+1],lz[2*v+1],len/2);
		lz[v]=Aux();
	}
	void update(int qL,int qR,const Aux&val,int L,int R,int v){
		if(qL<=L && R<=qR){
			val.apply(t[v],lz[v],R-L+1);return;
		}
		if(qR<L || R<qL)return;
		push(v,R-L+1);
		int M=(L+R)/2;
		update(qL,qR,val,L,M,2*v);
		update(qL,qR,val,M+1,R,2*v+1);
		t[v]=Data::merge(t[2*v],t[2*v+1]);
	}
	Data query(int qL,int qR,int L,int R,int v){
		if(qL<=L && R<=qR)return t[v];
		if(qR<L || R<qL)return Data();
		push(v,R-L+1);
		int M=(L+R)/2;
		return Data::merge(query(qL,qR,L,M,2*v),query(qL,qR,M+1,R,2*v+1));
	}
public:
	LazySegmentTree(int n):n(n){
		t.resize(4*n);lz.resize(4*n);
	}LazySegmentTree(int n,const vector<Data>&a):n(n){
		t.resize(4*n);lz.resize(4*n);
		build(1,n,1,a);
	}void update(int qL,int qR,const Aux&val){update(qL,qR,val,1,n,1);}
	Data query(int qL,int qR){return query(qL,qR,1,n,1);}
};

struct Data{
	int v;
	Data(int v):v(v){}
	Data():v(0){}
	static Data merge(const Data&data1,const Data&data2){
		return Data(data1.v+data2.v);
	};
};

struct Aux{
	int add,set;
	Aux(int add,int set):add(add),set(set){}
	Aux():add(0),set(-1){}
	void apply(Data&data,Aux&aux,int len) const{
		if(set!=-1){
			data.v=len*set;
			aux.set=set;
			aux.add=0;
			return;
		}
		data.v+=len*add;
		if(aux.set!=-1)aux.set+=add;
		else aux.add+=add;
	}
};