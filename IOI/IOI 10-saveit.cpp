/*
    Author: Nguyen Tan Bao
    Status: AC after reading editorial
    Idea: https://ioi2010.org/competitiontask/day2/saveit/index.html
*/

// -------------- encoder.cpp -----------------------------------------------------------------------------
#include <bits/stdc++.h>
#include "grader.h"
#include "encoder.h"
using namespace std;

vector<int> a[1010];
int d[1010][1010], p[1010][1010];

void encode(int N, int H, int M, int *A, int *B) {
    // create edges
    for (int i = 0; i < M; i++) {
        int u = A[i], v = B[i];
        a[u].push_back(v);
        a[v].push_back(u);
    }
    
    // bfs from each hub to get shortest length
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < N; j++) d[i][j] = 1000000000;
        d[i][i] = 0;
        queue<int> q;
        q.push(i);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int j = 0; j < int(a[u].size()); j++) {
                int v = a[u][j];
                if (d[i][v] > d[i][u] + 1) {
                    d[i][v] = d[i][u] + 1;
                    p[i][v] = u;
                    q.push(v);
                }
            }
        }
    }
    
    // encode and send spanning tree
    // 10000 calls
    for (int i = 1; i < N; i++)
        for (int k = 0; k < 10; k++) {
            if (p[0][i] & (1<<k)) encode_bit(1);
            else encode_bit(0);
        }
    
    // encode and send info of each hub from 1 to H-1
    int cnt = 0;
    int val = 0;
    for (int i = 1; i < H; i++) {
        for (int j = 1; j < N; j++) {
            int par = p[0][j];
            // 3 possibilities of e 
            int e = d[i][j] - d[i][par] + 1;
            cnt++;
            val = val * 3 + e;
            // map 3 ternary decisions (27 choices) to 5 bits (32 possibilities)
            if (cnt == 3) {
                for (int k = 0; k < 5; k++) {
                    if (val & (1<<k)) encode_bit(1);
                    else encode_bit(0);
                }
                cnt = 0;
                val = 0;
            }
        }
    }
    // send remaining info
    if (cnt) {
        for (int k = 0; k < 5; k++) {
            if (val & (1<<k)) encode_bit(1);
            else encode_bit(0);
        }
    }
}


// -------------- decoder.cpp -----------------------------------------------------------------------------

#include <bits/stdc++.h>
#include "grader.h"
#include "decoder.h"
using namespace std;

int pa[1010], diff[1010], dist[1010], dc[1010][1010];
vector<int> aa[1010];

void dfs(int u) {
    for (int i = 0; i < int(aa[u].size()); i++) {
        int v = aa[u][i];
        dist[v] = dist[u] + diff[v];
        dfs(v);
    }
}

void decode(int N, int H) {
    // get spanning tree and create edge
    for (int i = 1; i < N; i++) {
        pa[i] = 0;
        for (int k = 0; k < 10; k++) pa[i] += (decode_bit() * (1<<k));
        aa[pa[i]].push_back(i);
        // diff is array to save the difference between dist[i] and dist[parent[i]]
        diff[i] = 1;
    }
    // dist is array to save distance between 0 and i
    dist[0] = 0;
    dfs(0);
    // call hops for hub 0 first
    for (int i = 0; i < N; i++) hops(0,i,dist[i]);

    // get and parse information from hub 1 to H-1, save to dc[i][j]
    int cnt = 0;
    for (int i = 1; i < H; i++)
        for (int j = 1; j < N; j++) {
            cnt++;
            if (cnt == 3) {
                int e = 0;
                for (int k = 0; k < 5; k++) e += (decode_bit() * (1<<k));
                int u = i, v = j;
                for (int k = 0; k < cnt; k++) {
                    dc[u][v] = e % 3;
                    e /= 3;
                    v--;
                    if (v == 0) {
                        v = N-1;
                        u--;
                    }
                }
                cnt = 0;
            }
        }
    if (cnt) {
        int e = 0;
        for (int k = 0; k < 5; k++) e += (decode_bit() * (1<<k));
        int u = H-1, v = N-1;
        for (int k = 0; k < cnt; k++) {
            dc[u][v] = e % 3;
            e /= 3;
            v--;
            if (v == 0) {
                v = N-1;
                u--;
            }
        }
    }

    // get diff, dfs to get dist and simply call hops
    for (int i = 1; i < H; i++) {
        for (int j = 1; j < N; j++) diff[j] = dc[i][j] - 1;
        dfs(0);
        for (int j = 0; j < N; j++) hops(i, j, dist[j] - dist[i]);
    }
}
