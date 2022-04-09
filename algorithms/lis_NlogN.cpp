#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n, a, res=0;
    vector<int> pesi, UltimoPreso;
    cin>>n;
    UltimoPreso.resize(n+1, numeric_limits<int>::max());
    UltimoPreso[0]=0;

    for(int i=0; i<n; i++)
    {
        cin>>a;
        pesi.push_back(a);
    }

    for(int i=0; i<n; i++)
    {
        int p = pesi[i];
        auto it = lower_bound(UltimoPreso.begin(), UltimoPreso.end(), p);

        *it = p;
    }

    auto it = lower_bound(UltimoPreso.begin(), UltimoPreso.end(), numeric_limits<int>::max());
    it--;
    res = it - UltimoPreso.begin();
    cout<<res;

    return 0;
}
