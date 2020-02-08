#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " <<

#define fi first
#define se second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
  
const int MAXN = 1e5;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Group {
    int n;
    vector<pii> points;
    pii lo_point, hi_point;
};

void scatter_points(vector<pii>& points) {
    int n = points.size();
    vector<int> x(MAXN), y(MAXN);
    for (int i = 0; i < MAXN; i++) x[i] = y[i] = i + 1;
    shuffle(x.begin(), x.end(), rng);
    shuffle(y.begin(), y.end(), rng);
    sort(x.begin(), x.begin() + n);
    sort(y.begin(), y.begin() + n);
    for (auto& p : points) {
        p.fi = x[p.fi];
        p.se = y[p.se];
    }
}

void validate(vector<pii>& points) {
    vector<int> cnt0(MAXN, 0), cnt1(MAXN, 0);
    bool ok;
    for (auto& p : points) {
        assert(1 <= p.fi && p.fi <= MAXN);
        assert(1 <= p.se && p.se <= MAXN);
        cnt0[p.fi - 1]++;
        cnt1[p.se - 1]++;
    }
    for (int c : cnt0) assert(c <= 2);
    for (int c : cnt1) assert(c <= 2);
}

void validate(Group& g) {
    vector<int> cnt0(g.n, 0), cnt1(g.n, 0);
    bool ok;
    for (auto& p : g.points) {
        assert(0 <= p.fi && p.fi < g.n);
        assert(0 <= p.se && p.se < g.n);
        cnt0[p.fi]++;
        cnt1[p.se]++;
    }
    for (int c : cnt0) assert(c <= 2);
    for (int c : cnt1) assert(c <= 2);
    assert(g.lo_point.fi != g.hi_point.fi);
    assert(g.lo_point.se != g.hi_point.se);
    assert(cnt0[g.lo_point.fi] == 0);
    assert(cnt1[g.lo_point.se] == 0);
    assert(cnt0[g.hi_point.fi] == 0);
    assert(cnt1[g.hi_point.se] == 0);
}

void print(vector<pii>& points) {
    scatter_points(points);
    validate(points);
    shuffle(points.begin(), points.end(), rng);
    cout << points.size() << "\n";
    for (auto p : points) cout << p.fi << " " << p.se << "\n";
}

void make_space(Group& g, pii& q) {
    for (auto& p : g.points) {
        if (p.fi >= q.fi) p.fi++;
        if (p.se >= q.se) p.se++;
    }
    if (g.lo_point.fi >= q.fi) g.lo_point.fi++;
    if (g.lo_point.se >= q.se) g.lo_point.se++;
    if (g.hi_point.fi >= q.fi) g.hi_point.fi++;
    if (g.hi_point.se >= q.se) g.hi_point.se++;
}

Group generate_group(int n) {
    assert(n % 2 == 0 && n >= 4);
    vector<int> x(n);
    for (int i = 0; i < n; i++) x[i] = i;
    x.erase(x.begin() + n / 2);
    x.erase(x.begin() + n / 2 - 1);
    auto y = x;
    shuffle(x.begin(), x.end(), rng);
    shuffle(y.begin(), y.end(), rng);

    exponential_distribution<> d(1.0 / sqrt(n));
    vector<pii> points;
    int m = n;
    while (m >= 4) {
        int k = max(4, min(m, (int)d(rng)));
        if (m - k < 4) k = m;
        k -= k % 2;
        
        int st = n - m;
        for (int i = 0; i < k; i++) {
            pii p;
            p.fi = x[st + i / 2];
            if (i == k - 1) p.se = y[st];
            else p.se = y[st + (i + 1) / 2];
            points.push_back(p);
        }

        m -= k;
    }
    assert(points.size() == n);
    
    return Group({n, points, make_pair(n / 2 - 1, n / 2 - 1), make_pair(n / 2, n / 2)});
}

void link_groups(Group& a, Group& b) {
    for (auto& p : b.points) {
        p.fi += a.n;
        p.se += a.n;
    }
    b.lo_point.fi += a.n;
    b.lo_point.se += a.n;
    b.hi_point.fi += a.n;
    b.hi_point.se += a.n;
    a.points.insert(a.points.end(), b.points.begin(), b.points.end());

    for (int x : {a.hi_point.fi, b.lo_point.fi})
        for (int y : {a.hi_point.se, b.lo_point.se})
            a.points.push_back(make_pair(x, y));
    a.hi_point = b.hi_point;
    a.n += b.n + 4;
    b.points.clear();
}

void force_orientation(Group& a, bool o, bool two_extra_points = false) {
    pii p1 = {rng() % a.n, rng() % a.n};
    pii p2 = p1;
    if (o) p2.fi = a.n + 1;
    else p2.se = a.n + 1;
    make_space(a, p1);

    a.n += 2;
    a.points.push_back(p1);
    a.points.push_back(p2);

    if (two_extra_points) {
        pii p3 = {a.n + 1, a.n + 1};
        pii p4 = p3;
        if (o) p4.fi++;
        else p4.se++;
        a.points.push_back(p3);
        a.points.push_back(p4);
        a.n += 2;
    }
}

vector<pii> generate_big_group(int n, bool force, bool bad) {
    int m, p;
    if (n <= 40) {
        m = 1;
        if (n <= 10 && !bad) p = 1;
        else p = 2;
    } else {
        m = sqrt(n);
        p = 4;
    }

    if (bad) force = false;
    bool o = rng() % 2;

    assert(n % 2 == 0);

    Group a;
    int sum_sz = 0;
    for (int i = 0; i < m; i++) {
        int sz = n / m;
        sz -= sz % 2;
        if (i == m - 1) sz = n - sum_sz;
        sum_sz += sz;
        if (i > 0) sz -= 4;

        assert(sz % 2 == 0);
        
        Group b;
        if (force && (i == 0 || i == m - 1)) {
            b = generate_group(sz - 2 * p);
            for (int j = 0; j < p; j++) force_orientation(b, o);
        } else if (bad && (i == 0 || i == m - 1)) {
            b = generate_group(sz - 2 * p);
            if (m == 1) {
                assert(p == 2);
                force_orientation(b, false);
                force_orientation(b, true);
            } else for (int j = 0; j < p; j++) force_orientation(b, o ^ (i == 0));
        } else {
            b = generate_group(sz);
        }

        if (i == 0) a = b;
        else link_groups(a, b);
    }

    assert(a.n == n);
    return a.points;
}

vector<pii> generate_testcase(int n, bool ans) {
    int k;
    if (n <= 10) k = 1;
    else if (n <= 40) k = 2;
    else k = 10;

    int bad_group = -1;
    if (!ans) bad_group = rand() % k;

    vector<pii> points;
    int max_xy = -1;
    int sum_sz = 0;
    for (int i = 0; i < k; i++) {
        int sz = n / k;
        sz -= sz % 2;
        if (i == k - 1) sz = n - sum_sz;
        sum_sz += sz;
        bool force;
        if (k == 1) force = true;
        else if (k == 2) force = i;
        else force = rng() % 2;
        auto a = generate_big_group(sz, force, i == bad_group);
        assert(max_xy < sum_sz - sz);
        for (auto& p : a) {
            p.fi += sum_sz - sz;
            p.se += sum_sz - sz; 
            max_xy = max(max_xy, max(p.fi, p.se));
        }
        points.insert(points.end(), a.begin(), a.end());
    }

    assert(points.size() == n);
    return points;
}


void make_space(vector<pii>& points, int x, int y, int dx, int dy) {
    for (auto& p : points) {
        if (p.fi >= x) p.fi += dx;
        if (p.se >= y) p.se += dy;
    }
}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    assert(argc == 3);
    int n = atoi(argv[1]);
    string testcase_type = argv[2];

    if (testcase_type == "only_cycles") {
        auto a = generate_group(n);
        print(a.points);
    } else if (testcase_type == "yes") {
        auto a = generate_testcase(n, true);
        print(a);
    } else if (testcase_type == "no") {
        auto a = generate_testcase(n, false);
        print(a);
    } else if (testcase_type == "intersecting_paths") {
        auto a = generate_testcase(n - 4, true);
        int x = rng() % n, y = rng() % n;
        make_space(a, x, y, 3, 3);
        a.push_back(make_pair(x + 1, y));
        a.push_back(make_pair(x + 1, y + 2));
        a.push_back(make_pair(x, y + 1));
        a.push_back(make_pair(x + 2, y + 1));
        print(a);
    } else if (testcase_type == "odd_paths") {
        auto a = generate_testcase(n - 6, true);
        for (int i : {0, 1}) {
            int x = rng() % (n - 6), y = rng() % (n - 6);
            make_space(a, x, y, 2, 2);
            a.push_back(make_pair(x, y));
            a.push_back(make_pair(x + 1, y));
            a.push_back(make_pair(x + 1, y + 1));
        }
        print(a);
    } else if (testcase_type == "odd_point") {
        auto a = generate_testcase(n - 2, true);
        for (int i : {0, 1}) {
            int x = rng() % (n - 2), y = rng() % (n - 2);
            make_space(a, x, y, 1, 1);
            a.push_back(make_pair(x, y));
        }
        print(a);
    } else {
        assert(false);
        
    }

    return 0;
}

