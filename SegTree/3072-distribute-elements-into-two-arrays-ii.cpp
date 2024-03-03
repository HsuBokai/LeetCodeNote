class SegTree {
public:
    SegTree *left;
    SegTree *right;
    int l;
    int r;
    int value;
    SegTree(int a, int b, int v) {
        left = NULL;
        right = NULL;
        l = a;
        r = b;
        value = v;
    }
    
    // update value+1 at v
    void update(int v) {
        int mid = l + (r-l)/2;
        //cout << l << ':' << r << endl;
        if (left == NULL || right == NULL) {
            if (l == r) {
                value++;
            } else {
                left = new SegTree(l, mid, value);
                right = new SegTree(mid+1, r, value);
                if (v <= mid) {
                    left->update(v);
                } else {
                    right->update(v);
                }
                value++;
            }
        } else {
            int mid = left->r;
            if (v <= mid) {
                left->update(v);
            } else {
                right->update(v);
            }
            value++;
        }
    }
    
    // query sum value of [a:b]
    int query(int a, int b) {
        if (l == a && r == b) return value;
        int mid = l + (r-l)/2;
        if (left == NULL || right == NULL) {
            return value;
        } else {
            if (b <= mid) {
                return left->query(a,b);
            } else if (a > mid) {
                return right->query(a,b);
            } else {
                return left->query(a,mid) + right->query(mid+1,b);
            }
        }
    }
};

class Solution {
public:
    vector<int> resultArray(vector<int>& nums) {
        SegTree *rootA = new SegTree(1, 1e9+1, 0);
        SegTree *rootB = new SegTree(1, 1e9+1, 0);
        rootA->update(nums[0]);
        rootB->update(nums[1]);
        vector<int> arr1(1, nums[0]);
        vector<int> arr2(1, nums[1]);
        for (int i = 2; i < nums.size(); ++i) {
            int v = nums[i];
            int sa = rootA->query(v+1, 1e9+1);
            int sb = rootB->query(v+1, 1e9+1);
            //cout << sa << ',' << sb << endl;
            if (sa > sb) {
                arr1.push_back(v);
                rootA->update(v);
            } else if (sa < sb) {
                arr2.push_back(v);
                rootB->update(v);
            } else {
                if (arr1.size() <= arr2.size()) {
                    arr1.push_back(v);
                    rootA->update(v);
                } else {
                    arr2.push_back(v);
                    rootB->update(v);
                }
            }
        }
        for (auto& v : arr2) arr1.push_back(v);
        return arr1;
    }
};