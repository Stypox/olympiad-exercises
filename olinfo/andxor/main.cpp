#include<bits/stdc++.h>
using namespace std;

signed main() {
    int N, Q;
    cin>>N>>Q;

    vector<bitset<20>> nums(N, bitset<20>(0)); // [col][rig]
    array<int, 20> onesCountAnd{0}; // [rig]
    array<array<int, 20>, 20> onesCountXor{array<int, 20>{0}}; // [rigFrom][rigTo]

    auto update = [&](int col, int v) {
        for(int i=0; i<20; ++i){
            bool b = v & (1<<i);

            if (nums[col][i] != b) {
                onesCountAnd[i] -= nums[col][i];
                onesCountAnd[i] += b;
                nums[col][i] = b;
                for(int j=0; j<20; ++j){
                    if (nums[col][j]) {
                        onesCountXor[i][j] += (b ? 1 : -1);
                        if (i!=j) {
                            onesCountXor[j][i] += (b ? 1 : -1);
                        }
                    }
                }
            }
        }
    };

    auto solve = [&]() {
        int maxCount = *max_element(onesCountAnd.begin(), onesCountAnd.end());
        if (maxCount % 2 == 1) {
            return maxCount;
        }

        int result = 0;
        for (int i=0;i<20;++i){
            bool doableFull=false;
            if(onesCountAnd[i] == maxCount) {
                for (int j=0;j<20;++j){
                    if (i!=j && onesCountXor[i][j]%2 == 1) {
                        doableFull = true;
                        break;
                    }
                }
            }

            if(doableFull) {
                result = maxCount;
                break;
            } else {
                result = maxCount - 1;
            }
        }

        return result;
    };

    for(int n=0;n<N;++n){
        int v;
        cin>>v;
        update(n, v);
    }

    //cerr << "Beginning:\n";
    cout << solve() << endl;
    for(int q=0;q<Q;++q){
        int col, v;
        cin>>col>>v;
        col--;
        update(col, v);
        //cerr << "\n(" << col << ", " << v << ")\n";
        cout << solve() << endl;
    }
}
