class Solution {
    vector<vector<pair<int,int>>> next;
    vector<int> min_cost;
    vector<vector<int>> prev;
    vector<bool> ret;
    unordered_map<long long, int> find_i;
public:
    long long geti(int a, int b) {
        long long ret = min(a,b);
        ret = ret << 20;
        ret += max(a,b);
        return ret;
    }
    
    vector<bool> findAnswer(int n, vector<vector<int>>& edges) {
        ret = vector<bool>(edges.size(), false);
        prev = vector<vector<int>>(n);
        min_cost = vector<int>(n, -1);
        next = vector<vector<pair<int,int>>>(n);
        for (auto& e : edges) {
            next[e[0]].push_back({e[1], e[2]});
            next[e[1]].push_back({e[0], e[2]});
        }
        unordered_map<int,int> cost;
        set<pair<int,int>> q;
        q.insert({0, 0});
        while (!q.empty()) {
            auto it = q.begin();
            int parent = it->second;
            int parent_cost = it->first;
            //cout << parent << ',' << parent_cost << endl;
            q.erase({parent_cost, parent});
            if (min_cost[parent] != -1) continue;
            min_cost[parent] = parent_cost;
            if (parent == (n-1)) break;
            for (auto& ch : next[parent]) {
                int i = ch.first;
				int weight = ch.second;
                if (min_cost[i] != -1) continue;
                int newcost = parent_cost + weight;
                if (cost.find(i) == cost.end()) {
                    prev[i].push_back(parent);
                    q.insert({newcost, i});
                    cost[i] = newcost;    
                } else {
                    if (newcost == cost[i]) {
                        prev[i].push_back(parent);
                    } else if (newcost < cost[i]) {
                        prev[i].clear();
                        prev[i].push_back(parent);
                        q.erase({cost[i], i});
                        q.insert({newcost, i});
                        cost[i] = newcost;
                    }
                }
            }
        }
        for (int i = 0; i < edges.size(); ++i) {
            find_i[geti(edges[i][0], edges[i][1])] = i;
        }
        dfs(n-1, -1);
        return ret;
    }
    
    void dfs(int i, int p) {
        for (auto& ch : prev[i]) {
            if (ch == p) continue;
            ret[find_i[geti(i, ch)]] = true;
            dfs(ch, i);
        }
    }
};