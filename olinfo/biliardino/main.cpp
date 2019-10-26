#include<bits/stdc++.h>
using si = int64_t;
using namespace std;

template<class T>
ostream& operator<<(ostream& out, const vector<T>& e) {
    out<<"[";
    for(size_t i=0;i<e.size();++i){
        if(i!=0) out<<", ";
        out<<e[i];
    }
    out<<"]";
    return out;
}
template<class A, class B>
ostream& operator<<(ostream& out, const pair<A, B>& e) {
    out<<"{";
    out<<e.first;
    out<<", ";
    out<<e.second;
    out<<"}";
    return out;
}

struct SegmentTree {
    vector<si> data;
    SegmentTree(const vector<si>& init) {
        assert((si)init.size() - ((si)init.size() & (-(si)init.size())) == 0); // la dimensione deve essere potenza di 2
        data.resize(2*init.size());
        copy(init.begin(), init.end(), data.begin()+init.size());
        build(1, 0, data.size()/2);
        //cerr<<"ST data: "<<data<<"\n";
    }

    void build(si i, si L, si R) {
        if (L==(R-1)) {
            assert(i>=(si)data.size()/2);
            return;
        }

        build(i*2,   L, (L+R)/2);
        build(i*2+1, (L+R)/2, R);
        data[i] = min(data[2*i], data[2*i+1]);
    }

    si queryMin(si i, si L, si R, si x, si y) {
        if (L>=y || R<=x) return numeric_limits<si>::max();
        if (L>=x && R<=y) return data[i];

        return min(queryMin(i*2,   L, (L+R)/2, x, y),
                   queryMin(i*2+1, (L+R)/2, R, x, y));
    }

    si queryNextLower(si i, si L, si R, si from, si num) {
        //cerr<<i<<" L="<<L<<" R="<<R<<"\n";
        if (R<=from || data[i]>=num) return -1;
        // quindi data[i]<num

        if (L==(R-1)) {
            assert(i>=(si)data.size()/2);
            return i - data.size()/2;
        }

        si resleft = queryNextLower(i*2, L, (L+R)/2, from, num);
        if (resleft != -1) return resleft;
        return queryNextLower(i*2+1, (L+R)/2, R, from, num);
    }

    si queryMin(si x, si y) {
        return queryMin(1, 0, data.size()/2, x, y);
    }

    si queryNextLower(si from, si num) {
        si res = queryNextLower(1, 0, data.size()/2, from, num);
        if (res == -1) {
            return data.size()/2;
        } else {
            return res;
        }
    }
};

SegmentTree* st_ptr;
vector<si> sums;
si N;

void inizia(int N_, int T[]) {
    N=N_;
    vector<si> vecT{T, T+N};
    vecT.resize(1 << ((si)log2(N) + 1));
    //cerr<<"vecT:    "<<vecT<<"\n";

    st_ptr = new SegmentTree(vecT);
    SegmentTree& st = *st_ptr;

    sums.resize(N);
    for(si i=N-1; i>=0; --i) {
        si nextLower = st.queryNextLower(i, T[i]);
        if (nextLower >= N) {
            sums[i] = T[i]*(N-i);
        } else {
            sums[i] = T[i]*(nextLower-i) + sums[nextLower];
        }
    }

    //cerr<<"Sums:    "<<sums<<"\n";

    /*cerr<<"min(1,3)="<<st.queryMin(1,3)<<"\n";
    cerr<<"min(0,3)="<<st.queryMin(0,3)<<"\n";
    cerr<<"min(0,4)="<<st.queryMin(0,4)<<"\n";
    cerr<<"min(2,4)="<<st.queryMin(2,4)<<"\n";
    cerr<<"min(3,4)="<<st.queryMin(3,4)<<"\n";*/

    /*cerr<<"qnl(0,0)="<<st.queryNextLower(0,0)<<"\n";
    cerr<<"qnl(0,2)="<<st.queryNextLower(0,2)<<"\n";
    cerr<<"qnl(0,4)="<<st.queryNextLower(0,4)<<"\n";
    cerr<<"qnl(0,5)="<<st.queryNextLower(0,5)<<"\n";
    cerr<<"qnl(3,5)="<<st.queryNextLower(3,5)<<"\n";*/

    //cerr<<st.queryNextLower(0,4)<<"\n";
}

long long passaggio(int L, int R) {
    SegmentTree& st = *st_ptr;
    
    si m = st.queryMin(L,R);
    si nextLower = st.queryNextLower(R,m);

    if (nextLower >= N) {
        return sums[L] - m*(N-R);
    } else {
        return sums[L] - m*(nextLower-R) - sums[nextLower];
    }    
}
/*
int main() {
    int a[] = {5,7,6,4,9};
    inizia(5, a);
    cerr<<passaggio(0,4)<<"\n";
    cerr<<passaggio(1,5)<<"\n";
}*/