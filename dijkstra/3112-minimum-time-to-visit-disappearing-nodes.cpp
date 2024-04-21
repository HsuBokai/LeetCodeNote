class Solution {
    vector<vector<pair<int,int>>> next;
    vector<int> min_cost;
public:
    vector<int> minimumTime(int n, vector<vector<int>>& edges, vector<int>& disappear) {
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
            for (auto& ch : next[parent]) {
                int i = ch.first;
				int weight = ch.second;
                if (min_cost[i] != -1) continue;
                int newcost = parent_cost + weight;
                if (cost.find(i) == cost.end()) {
                    if (newcost < disappear[i]) {
                        q.insert({newcost, i});
                        cost[i] = newcost;    
                    }
                } else {
                    if (newcost < disappear[i] && newcost < cost[i]) {
                        q.erase({cost[i], i});
                        q.insert({newcost, i});
                        cost[i] = newcost;
                    }
                }
            }
        }
        return min_cost;
    }
};