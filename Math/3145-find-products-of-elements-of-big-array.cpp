    int pow(long long base, long long x, long long m) {
        long long ans = 1;
        long long p = base;
        while (x > 0) {
            if ((x%2) == 1) {
                ans = ((ans * p) % m);
            }
            p = ((p * p) % m);
            x /= 2;
        }
        return ans % m;
    }

    long long total_1_of_x(long long x) {
        long long total = 0;
        while (x > 0) {
            x = x & (x-1);
            total++;
        }
        return total;
    }

    long long total_1_below_x(long long x) {
        long long total = total_1_of_x(x);
        long long index = 0;
        long long count_of_1 = 0;
        while (x > 0) {
            if (x%2 == 1) {
                total--;
                if (index > 0)
                    count_of_1 += index * ((long long)1)<<(index-1);
                count_of_1 += (total * (((long long)1)<<index));
            }
            x /= 2;
            index++;
        }
        return count_of_1;
    }
    
    long long total_2_pow_of_x(long long x) {
        long long index = 0;
        long long total = 0;
        while (x > 0) {
            if (x%2 == 1) {
                total += (index);
            }
            x /= 2;
            index++;
        }
        return total;
    }

    long long total_2_pow_below_x(long long x) {
        long long total = total_2_pow_of_x(x);
        long long count_of_2_pow = 0;
        long long index = 0;
        while (x > 0) {
            if (x%2 == 1) {
                total -= (index);
                if (index >= 2)
                    count_of_2_pow += (index-1) * index * (((long long)1)<<(index-2));
                count_of_2_pow += (total * (((long long)1)<<index));
            }
            x /= 2;
            index++;
        }
        return count_of_2_pow;
    }

class Solution {
public:
    vector<int> findProductsOfElements(vector<vector<long long>>& queries) {
        vector<int> ret;
        for (auto& q : queries) {
            long long from = q[0];
            long long to = q[1];
            long long x = get2(to) - get2(from-1);
            //cout << x << endl;
            ret.push_back(pow(2, x, q[2]));
        }
        return ret;
    }
    long long get2(long long x) {
        if (x == -1) return 0;
        if (x == 0) return 0;
        long long l = 1;
        long long r = (((long long)1)<<50);
        long long diff = 0;
        while (l < r) {
            long long mid = r - (r-l)/2;
            long long count_of_1 = total_1_below_x(mid);
            if (count_of_1 <= x) {
                diff = x - count_of_1;
                l = mid;
            } else {
                r = mid-1;
            }
        }
        //cout << r << endl;
        long long count_of_2_pow = total_2_pow_below_x(r);
        //cout << diff << endl;
        //cout << count_of_2_pow << endl;
        long long index = 0;
        long long mm = r;
        while (mm > 0) {
            if (mm%2 == 1) {
                count_of_2_pow += index;
                diff--;
                if (diff < 0) return count_of_2_pow;
            }
            mm /= 2;
            index++;
        }
        return count_of_2_pow;
    }
};