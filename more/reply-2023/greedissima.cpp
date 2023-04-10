#include "template.cpp"

int place_best(vector<int> &A, int n, int l)
{
    int start = -1, best = 0;
    for (int i = 0; i < n; i++)
    {
        //cerr<<i<<" "<<n<<" "<<A.size()<<"\n";
        if (A[i] == WORMHOLE || A[(i + l - 1 + n) % n] == WORMHOLE)
            continue;
        int sum = A[i];
        for (int j = i + 1; j < i + l; j++)
        {
            int val = A[j % n];
            if (val == WORMHOLE)
                val = 0;
            sum += val;
        }
        if (sum > best)
        {
            best = sum;
            start = i;
        }
    }
    return start;
}

void solve(int C, int R, int S, vector<int> lengths, vector<vector<int>> matrix, vector<pair<int, int>> wormholes, vector<vector<int>> &output)
{
    for (int i = 0; i < S; i++)
    {
        int l = lengths[i];
        if (i >= R || l > C)
        {
            continue;
        }
        int start = place_best(matrix[i], C, l);
        if (start == -1)
            continue;
        else
        {
            output[i].push_back(start);
            output[i].push_back(i);
            for (int j = start; j < start + l - 1; j++)
            {
                if (matrix[i][j % C] != WORMHOLE)
                {
                    output[i].push_back(RIGHT);
                }
                else
                {
                    output[i].push_back(j % C);
                    output[i].push_back(i);
                    output[i].push_back(RIGHT);
                }
            }
        }
    }
}
