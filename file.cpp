#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

vector <int> color;
vector<vector<int>> adj;

bool dfs(int u){
    color[u-1] = 1;
    for (int v: adj[u-1]){
        if (color[v-1] == 1){
            return false;
        }
        else if (color[v-1] == 0)
            if (!dfs(v))
                return false;
    }
    color[u-1] = 2;
    return true;
}

bool acyclic_graph(int v){
    color.assign(v, 0);
    for (int i = 1; i <= v; i++){
        if (color[i-1] == 0){
            if (!dfs(i)){
                return false;
            }
        }
    }
    return true;
}

void ancestrais(int n, int v1, int v2){
    queue<int> q;
    vector<char> color_v1;
    color_v1.assign(n, 0);
    q.push(v1);
    while(!q.empty()){
        int v_aux = q.front();
        q.pop();
        for(int u: adj[v_aux-1]){
            if(color_v1[u-1] == 0){
                q.push(u);
                color_v1[u-1] = 1;
            }
        }
        color_v1[v_aux-1] = 2;
    }
    vector<char> color_v2;
    color_v2.assign(n, 0);
    q.push(v2);
    vector<char> c;
    c.assign(n, 0);
    while(!q.empty()){
        int v_aux = q.front();
        q.pop();
        if(color_v1[v_aux-1] == 2 && c[v_aux-1] == 0){
            c[v_aux-1] = 1;
        }
        for(int u: adj[v_aux-1]){
            if(color_v2[u-1] == 0){
                q.push(u);
                color_v2[u-1] = 1;
            }
            if(c[v_aux-1] != 0){
                c[u-1] = 2;
            }
        }
        color_v2[v_aux-1] = 2;
    }
    char empty = 1;
    for(int i = 0; i<n; i++){
        if(c[i]==1){
            printf("%d ", i+1);
            empty = 0;
        }
    }
    if(empty){
        printf("-");
    }
    printf("\n");
}

int main(){
    int v1, v2, v, e;
    scanf("%d %d", &v1, &v2);
    scanf("%d %d", &v, &e);
    adj = vector<vector<int>>(v, vector<int>());
    color = vector<int> (v);
    vector<int> n_adj;
    n_adj.assign(v+1, 0);
    for(int i=0; i < e; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        if(++n_adj[y] > 2){
            n_adj[0] = -1;
        }
        adj[y-1].push_back(x);
    }

    if(n_adj[0] == 0 && acyclic_graph(v)){
        ancestrais(v, v1, v2);
    }
    else{
        printf("0\n");
    }
    return 0;
}