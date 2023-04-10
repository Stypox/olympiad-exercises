#include "template.cpp"

typedef pair<int, int> ii;

pair<int, int> maxsum(vector<int> A, int n) {
    int maxSoFar = 0;
    int maxHere = 0;
    int tmp_l = 0;
    int l = 0;
    int r = -1;
    for(int i = 0; i < n; i++) {
        int increase = A[i]==WORMHOLE ? 0 : A[i];
        if(maxHere+increase < 0 || A[i] == WORMHOLE) {
            tmp_l = i+1;
        }
        maxHere = max(maxHere+increase, (int) 0);
        if(maxHere > maxSoFar) {
            r = i;
            maxSoFar = maxHere;
            l = tmp_l;
        }
    }
    while(A[l]==WORMHOLE && l<r) {
        l++;
    }
    while(r>=0 && A[r]==WORMHOLE && l<r) {
        r--;
    }

    return make_pair(l, r);
}

void solve(int C, int R, int S, vector<int> lengths, vector<vector<int>> matrix, vector<pair<int,int>> wormholes, vector<vector<int>>& output) {
    vector<bool> presi(lengths.size());
    vector<ii> serpenti;
    for(int i = 0; i < lengths.size(); i++) {
        serpenti.push_back(make_pair(lengths[i], i));
    }
    sort(serpenti.rbegin(), serpenti.rend());
    for(int i = 0; i < matrix.size(); i++) {
        int snake = 0;
        pair<int, int> indice = maxsum(matrix[i], matrix[i].size());
        while(snake < serpenti.size() && (serpenti[snake].first > indice.second+1-indice.first || presi[serpenti[snake].second])) {
            snake++;
        }
        if(snake >= serpenti.size()) {
            deb("errore");
            continue;
        }
        if (matrix[i][indice.first] == WORMHOLE) {
            continue;
        }
        output[serpenti[snake].second].push_back(indice.first);
        output[serpenti[snake].second].push_back(i);
        int j = indice.first;
        for(int k = 0; k < serpenti[snake].first-1; k++) {
            output[serpenti[snake].second].push_back(RIGHT);
            j++;
            j %= C;
            if(matrix[i][j] == WORMHOLE) {
                output[serpenti[snake].second].push_back(j);
                output[serpenti[snake].second].push_back(i);
            }
        }
        if (matrix[i][j] == WORMHOLE) {
            output[serpenti[snake].second].resize(0);
            continue;
        }
        presi[serpenti[snake].second] = true;
    }
}