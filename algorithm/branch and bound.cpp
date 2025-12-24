#include <bits/stdc++.h>
#include <windows.h>        // 仅 Windows 用
using namespace std;

/* ========== 分支限界法部分 ========== */
struct NodeType {
    int i;                      // 已分配完前 i 个人
    vector<int> x;              // x[k]=给第k个人分配的任务号
    vector<bool> worker;        // 任务是否已被分配
    int cost;                   // 已产生成本
    int lb;                     // 下界
    bool operator<(const NodeType& s) const { return lb > s.lb; }
};

const int INF = INT_MAX;
int n;
int mincost;
vector<int> bestx;
vector<vector<int>> c;          // 代价矩阵，c[1..n][1..n]

/* 下界：后面每行在仍可用任务里选最小代价 */
void bound(NodeType& e) {
    int minsum = 0;
    for (int row = e.i + 1; row <= n; ++row) {
        int minc = INF;
        for (int col = 1; col <= n; ++col)
            if (!e.worker[col] && c[row][col] < minc)
                minc = c[row][col];
        minsum += minc;
    }
    e.lb = e.cost + minsum;
}

void bfs() {
    priority_queue<NodeType> pq;

    NodeType root;
    root.i = 0;
    root.x.assign(n + 1, 0);
    root.worker.assign(n + 1, false);
    root.cost = 0;
    bound(root);
    pq.push(root);

    while (!pq.empty()) {
        NodeType e = pq.top(); pq.pop();
        if (e.lb > mincost) continue;

        if (e.i == n) {                 // 全部分配完
            if (e.cost < mincost) {
                mincost = e.cost;
                bestx   = e.x;
            }
            continue;
        }
        /* 扩展第 e.i+1 个人 */
        for (int j = 1; j <= n; ++j) {
            if (e.worker[j]) continue;
            NodeType ne = e;
            ne.i        = e.i + 1;
            ne.x[ne.i]  = j;
            ne.worker[j]= true;
            ne.cost     = e.cost + c[ne.i][j];
            bound(ne);
            if (ne.lb < mincost) pq.push(ne);
        }
    }
}

/* ========== 随机生成 & 输出 ========== */
void generate() {
    c.resize(n + 1, vector<int>(n + 1, 0));
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(1, 9);

    cout << "生成的代价矩阵 c（1-based）：\n";
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            c[i][j] = dist(rng);
            cout << setw(3) << c[i][j];
        }
        cout << '\n';
    }
    cout << '\n';
}

/* ========== 主流程 ========== */
int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    cout << "请输入 n：";
    if (!(cin >> n) || n <= 0) {
        cerr << "n 必须是正整数！\n";
        return 0;
    }

    generate();             // 随机生成 c 并打印

    bestx.resize(n + 1);
    mincost = INF;
    bfs();                  // 分支限界法

    cout << "最小成本 = " << mincost << '\n';
    cout << "分配方案（人员 1..n 对应任务）：";
    for (int i = 1; i <= n; ++i) cout << bestx[i] << " \n"[i == n];

    cout << "\n按 Enter 退出...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    return 0;
}