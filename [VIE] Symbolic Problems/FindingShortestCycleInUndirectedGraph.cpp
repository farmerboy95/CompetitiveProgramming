/*
    Đề bài:
        - Cho một đồ thị vô hướng, hãy tìm chu trình đơn (simple cycle) ngắn nhất.
    Lời giải:
        - Đầu tiên lưu list các cạnh trong mảng "edges", gọi edgesFromNode[x] lưu chỉ số của cạnh có
        1 trong 2 endpoints là node x trong mảng "edges"
        - Xét tất cả các đỉnh trong đồ thi, xuất phát từ một đỉnh root nào đó. Tiến hành BFS từ root.
        - Đầu tiên, với đỉnh root, ta không set distance cho nó mà set distance cho các đỉnh kề với nó
        trước để việc quay về root trở nên thuận tiện hơn. Lưu chỉ số của cạnh kề root và chỉ số của 
        đỉnh kề trong edgesFromNode[root] vào làm 1 pair trong queue.
        - Khi BFS, từ queue ta lấy được 1 node, xét tất cả cạnh kề của node đó trong edgesFromNode[node],
        chú ý tránh cạnh được dùng để đi đến node (là cạnh ở trong queue vừa lấy ra), khi lấy được 1 cạnh
        mới, ta lấy node mới và pair để cho vào queue. 
        - Ở đây ta sẽ có 2 trường hợp:
            + Đi đến 1 node chưa thăm và node đó không phải root, ở đây đơn giản ta chỉ cần thăm node mới đó.
            + Đi đến 1 node thăm rồi hoặc node đó là root, vậy chỉ cần tối ưu result bằng cách lấy min của
            nó với dist[node] + dist[newNode] + 1
        - Lưu ý là việc tối ưu như trên có thể không chính xác với 1 số root, chẳng hạn như là khi ta
        đi từ root một hồi xong về lại 1 đỉnh newNode chính trên đường đi từ root đến node, tuy nhiên
        trường hợp này có thể được cover bằng cách xét 1 root khác trong chu trình đó.
        - Độ phức tạp O(n^2)
    Nguồn: 
        - https://codeforces.com/contest/1325/problem/E
        - https://codeforces.com/blog/entry/74235
*/

#include <bits/stdc++.h>
#define FI first
#define SE second
#define EPS 1e-9
#define ALL(a) a.begin(),a.end()
#define SZ(a) int((a).size())
#define MS(s, n) memset(s, n, sizeof(s))
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define FORE(i,a,b) for (int i = (a); i >= (b); i--)
#define FORALL(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)
//__builtin_ffs(x) return 1 + index of least significant 1-bit of x
//__builtin_clz(x) return number of leading zeros of x
//__builtin_ctz(x) return number of trailing zeros of x

using namespace std;
using ll = long long;
using ld = double;
typedef pair<int, int> II;
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

const ll MODBASE = 1000000007LL;
const int MAXN = 110;
const int MAXM = 1000010;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, dist[MAXN];
vector<int> edgesFromNode[MAXN];
vector<vector<int> > edges;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n >> m;
    FOR(i,0,m-1) {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});

        edgesFromNode[u].push_back(i);
        edgesFromNode[v].push_back(i);
    }

    int res = 1000000000;
    FOR(i,1,n) {
        FOR(j,1,n) dist[j] = 0;
        queue<II> q;

        FOR(j,0,SZ(edgesFromNode[i])-1) {
            int e = edgesFromNode[i][j];
            if (edges[e][0] != i) {
                q.push(II(e, 0));
                dist[edges[e][0]] = 1;
            }
            else {
                q.push(II(e, 1));
                dist[edges[e][1]] = 1;
            }
        }

        while (SZ(q)) {
            II r = q.front(); q.pop();
            int node = edges[r.FI][r.SE];
            FOR(j,0,SZ(edgesFromNode[node])-1) {
                int e = edgesFromNode[node][j];
                // không quay ngược lại
                if (e != r.FI) {
                    II np;
                    if (edges[e][0] != node) np = II(e, 0);
                    else np = II(e, 1);
                    int newNode = edges[np.FI][np.SE];

                    if (dist[newNode] == 0 && newNode != i) {
                        q.push(np);
                        dist[newNode] = dist[node] + 1;
                    } else {
                        res = min(res, dist[node] + dist[newNode] + 1);
                    }
                }
            }
        }
    }
    if (res == 1000000000) res = -1;
    cout << res;
    return 0;
}
