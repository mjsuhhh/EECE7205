#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <random>
#include <sstream>
#include <stdexcept>

using namespace std;

struct Interval {
    int start;
    int end;
};

struct Point {
    int x;
    int y;
};

static bool byStart(const Interval& a, const Interval& b) {
    if (a.start != b.start) return a.start < b.start;
    return a.end < b.end;
}

static string toText(const vector<int>& v) {
    if (v.empty()) return "[]  (empty)";
    string s = "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) s += ", ";
        s += to_string(v[i]);
    }
    return s + "]";
}

static string toText(const vector<Interval>& v) {
    if (v.empty()) return "[]  (empty)";
    string s = "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) s += ", ";
        s += "[" + to_string(v[i].start) + "," + to_string(v[i].end) + "]";
    }
    return s + "]";
}

static string toText(const vector<Point>& v) {
    if (v.empty()) return "[]  (empty)";
    string s = "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) s += ", ";
        s += "(" + to_string(v[i].x) + "," + to_string(v[i].y) + ")";
    }
    return s + "]";
}

static string toText(const vector<string>& v) {
    if (v.empty()) return "[]  (empty)";
    string s = "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) s += ", ";
        s += "\"" + v[i] + "\"";
    }
    return s + "]";
}

static string toText(const vector<vector<string>>& groups) {
    if (groups.empty()) return "[]  (empty)";
    string s = "[";
    for (size_t i = 0; i < groups.size(); ++i) {
        if (i) s += ", ";
        s += toText(groups[i]);
    }
    return s + "]";
}

static string toText(const vector<vector<int>>& lists) {
    if (lists.empty()) return "[]  (empty)";
    string s = "[";
    for (size_t i = 0; i < lists.size(); ++i) {
        if (i) s += ", ";
        s += lists[i].empty() ? "[]" : toText(lists[i]);
    }
    return s + "]";
}

static void testHeader(int number, const string& label) {
    cout << "\n  [Test " << number << "] " << label << "\n";
}

static void sectionHeader(int problem, const string& title) {
    cout << "\n============================================================\n";
    cout << " PROBLEM " << problem << ": " << title << "\n";
    cout << "============================================================\n";
}

//============================================================================
// PROBLEM 1 - Merge Overlapping Intervals
//============================================================================

vector<Interval> mergeIntervals(vector<Interval> intervals) {
    vector<Interval> merged;
    if (intervals.empty()) return merged;

    sort(intervals.begin(), intervals.end(), byStart);

    Interval current = intervals[0];
    for (size_t i = 1; i < intervals.size(); ++i) {
        const Interval& next = intervals[i];
        if (next.start <= current.end) {
            current.end = max(current.end, next.end);
        } else {
            merged.push_back(current);
            current = next;
        }
    }
    merged.push_back(current);
    return merged;
}

//============================================================================
// PROBLEM 2 - Sort an array of 0/1/2 in place (two independent solutions)
//============================================================================

void sortColorsCounting(vector<int>& a) {
    int count[3] = {0, 0, 0};
    for (int v : a) count[v]++;

    int index = 0;
    for (int category = 0; category < 3; ++category)
        for (int repeat = 0; repeat < count[category]; ++repeat)
            a[index++] = category;
}

void sortColorsDNF(vector<int>& a) {
    int low  = 0;
    int mid  = 0;
    int high = static_cast<int>(a.size()) - 1;

    while (mid <= high) {
        if (a[mid] == 0) {
            swap(a[low], a[mid]);
            ++low;
            ++mid;
        } else if (a[mid] == 1) {
            ++mid;
        } else {
            swap(a[mid], a[high]);
            --high;
        }
    }
}

//============================================================================
// PROBLEM 3 - Largest Number From Concatenation
//============================================================================

string largestNumber(const vector<int>& values) {
    if (values.empty()) return "";

    vector<string> tokens;
    tokens.reserve(values.size());
    for (int v : values) tokens.push_back(to_string(v));

    sort(tokens.begin(), tokens.end(),
         [](const string& a, const string& b) { return a + b > b + a; });

    if (tokens[0] == "0") return "0";
    string result;
    for (const string& t : tokens) result += t;
    return result;
}

//============================================================================
// PROBLEM 4 - Group Anagrams
//============================================================================

vector<vector<string>> groupAnagrams(const vector<string>& words) {
    unordered_map<string, size_t> slotOf;
    vector<vector<string>> groups;

    for (const string& word : words) {
        string signature = word;
        sort(signature.begin(), signature.end());

        auto it = slotOf.find(signature);
        if (it == slotOf.end()) {
            slotOf[signature] = groups.size();
            groups.push_back({word});
        } else {
            groups[it->second].push_back(word);
        }
    }
    return groups;
}

//============================================================================
// PROBLEM 5 - Meeting Rooms: can one person attend every meeting?
//============================================================================

bool canAttendAllMeetings(vector<Interval> meetings) {
    if (meetings.size() < 2) return true;

    sort(meetings.begin(), meetings.end(), byStart);

    for (size_t i = 1; i < meetings.size(); ++i)
        if (meetings[i].start < meetings[i - 1].end) return false;

    return true;
}

//============================================================================
// PROBLEM 6 - K Closest Points to Origin (two solutions to compare)
//============================================================================

static long long squaredDistance(const Point& p) {
    return 1LL * p.x * p.x + 1LL * p.y * p.y;
}

vector<Point> kClosestBySorting(vector<Point> points, int k) {
    if (k <= 0 || points.empty()) return {};
    if (k > static_cast<int>(points.size())) k = static_cast<int>(points.size());

    sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
        return squaredDistance(a) < squaredDistance(b);
    });
    return vector<Point>(points.begin(), points.begin() + k);
}

static bool sameDistances(vector<Point> a, vector<Point> b) {
    if (a.size() != b.size()) return false;
    vector<long long> da, db;
    for (const Point& p : a) da.push_back(squaredDistance(p));
    for (const Point& p : b) db.push_back(squaredDistance(p));
    sort(da.begin(), da.end());
    sort(db.begin(), db.end());
    return da == db;
}

struct FarthestOnTop {
    bool operator()(const pair<long long, Point>& a,
                    const pair<long long, Point>& b) const {
        return a.first < b.first;
    }
};

vector<Point> kClosestByHeap(const vector<Point>& points, int k) {
    if (k <= 0 || points.empty()) return {};
    if (k > static_cast<int>(points.size())) k = static_cast<int>(points.size());

    priority_queue<pair<long long, Point>,
                   vector<pair<long long, Point>>,
                   FarthestOnTop> heap;

    for (const Point& p : points) {
        heap.push({squaredDistance(p), p});
        if (static_cast<int>(heap.size()) > k) heap.pop();
    }

    vector<Point> result;
    result.reserve(heap.size());
    while (!heap.empty()) {
        result.push_back(heap.top().second);
        heap.pop();
    }
    reverse(result.begin(), result.end());
    return result;
}

//============================================================================
// PROBLEM 7 - Top K Frequent Elements
//============================================================================

vector<int> topKFrequent(const vector<int>& values, int k) {
    if (k <= 0 || values.empty()) return {};

    unordered_map<int, int> frequency;
    for (int v : values) frequency[v]++;

    vector<pair<int, int>> items(frequency.begin(), frequency.end());
    if (k > static_cast<int>(items.size())) k = static_cast<int>(items.size());

    sort(items.begin(), items.end(),
         [](const pair<int, int>& a, const pair<int, int>& b) {
             if (a.second != b.second) return a.second > b.second;
             return a.first < b.first;
         });

    vector<int> result;
    result.reserve(k);
    for (int i = 0; i < k; ++i) result.push_back(items[i].first);
    return result;
}

//============================================================================
// PROBLEM 8 - Merge K Sorted Arrays
//============================================================================

struct HeapNode {
    int value;
    int listIndex;
    int elementIndex;
};

struct SmallestOnTop {
    bool operator()(const HeapNode& a, const HeapNode& b) const {
        return a.value > b.value;
    }
};

vector<int> mergeKSortedArrays(const vector<vector<int>>& lists) {
    priority_queue<HeapNode, vector<HeapNode>, SmallestOnTop> heap;

    size_t total = 0;
    for (size_t i = 0; i < lists.size(); ++i) {
        total += lists[i].size();
        if (!lists[i].empty())
            heap.push({lists[i][0], static_cast<int>(i), 0});
    }

    vector<int> merged;
    merged.reserve(total);

    while (!heap.empty()) {
        HeapNode node = heap.top();
        heap.pop();
        merged.push_back(node.value);

        int nextIndex = node.elementIndex + 1;
        if (nextIndex < static_cast<int>(lists[node.listIndex].size()))
            heap.push({lists[node.listIndex][nextIndex], node.listIndex, nextIndex});
    }
    return merged;
}

//============================================================================
// PROBLEM 9 - Kth Largest Element (Quickselect)
//============================================================================

static mt19937 rng(12345);

static void threeWayPartition(vector<int>& a, int low, int high, int& lt, int& gt) {
    uniform_int_distribution<int> pick(low, high);
    int pivot = a[pick(rng)];

    lt = low;
    gt = high;
    int i = low;
    while (i <= gt) {
        if (a[i] < pivot)      swap(a[i++], a[lt++]);
        else if (a[i] > pivot) swap(a[i], a[gt--]);
        else                   ++i;
    }
}

int kthLargest(vector<int> values, int k) {
    int n = static_cast<int>(values.size());
    if (k < 1 || k > n) throw invalid_argument("k must satisfy 1 <= k <= n");

    int target = n - k;
    int low = 0, high = n - 1;
    while (low < high) {
        int lt = 0, gt = 0;
        threeWayPartition(values, low, high, lt, gt);
        if (target < lt)      high = lt - 1;
        else if (target > gt) low  = gt + 1;
        else                  return values[target];
    }
    return values[low];
}

//============================================================================
// PROBLEM 10 - Count Inversions (modified Merge Sort)
//============================================================================

long long countInversionsBruteForce(const vector<int>& a) {
    long long count = 0;
    for (size_t i = 0; i < a.size(); ++i)
        for (size_t j = i + 1; j < a.size(); ++j)
            if (a[i] > a[j]) ++count;
    return count;
}

static long long mergeAndCount(vector<int>& a, vector<int>& buffer,
                               int left, int mid, int right) {
    long long count = 0;
    int i = left, j = mid + 1, t = left;

    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) {
            buffer[t++] = a[i++];
        } else {
            count += (mid - i + 1);
            buffer[t++] = a[j++];
        }
    }
    while (i <= mid)   buffer[t++] = a[i++];
    while (j <= right) buffer[t++] = a[j++];
    for (int p = left; p <= right; ++p) a[p] = buffer[p];

    return count;
}

static long long sortAndCount(vector<int>& a, vector<int>& buffer,
                              int left, int right) {
    if (left >= right) return 0;
    int mid = left + (right - left) / 2;

    long long count  = sortAndCount(a, buffer, left, mid);
    count += sortAndCount(a, buffer, mid + 1, right);
    count += mergeAndCount(a, buffer, left, mid, right);
    return count;
}

long long countInversions(vector<int> values) {
    if (values.size() < 2) return 0;
    vector<int> buffer(values.size());
    return sortAndCount(values, buffer, 0, static_cast<int>(values.size()) - 1);
}

static vector<int> readIntLine(const string& prompt) {
    cout << prompt;
    cout.flush();
    string line;
    getline(cin, line);
    istringstream in(line);
    vector<int> values;
    int v;
    while (in >> v) values.push_back(v);
    return values;
}

static vector<string> readWordLine(const string& prompt) {
    cout << prompt;
    cout.flush();
    string line;
    getline(cin, line);
    istringstream in(line);
    vector<string> words;
    string w;
    while (in >> w) words.push_back(w);
    return words;
}

static int readSingleInt(const string& prompt, int fallback) {
    cout << prompt;
    cout.flush();
    string line;
    getline(cin, line);
    istringstream in(line);
    int v;
    if (in >> v) return v;
    cout << "  [!] Not a number, using " << fallback << ".\n";
    return fallback;
}

static vector<Interval> readIntervalLine(const string& prompt) {
    vector<int> flat = readIntLine(prompt);
    vector<Interval> intervals;
    if (flat.size() % 2 != 0) {
        cout << "  [!] Expected an even count of numbers. Input ignored.\n";
        return intervals;
    }
    for (size_t i = 0; i + 1 < flat.size(); i += 2) {
        if (flat[i] > flat[i + 1])
            cout << "  [!] Interval [" << flat[i] << "," << flat[i + 1]
                 << "] has start > end; the assumption start <= end is violated.\n";
        intervals.push_back({flat[i], flat[i + 1]});
    }
    return intervals;
}

static bool askYes(const string& prompt) {
    cout << prompt;
    cout.flush();
    string line;
    if (!getline(cin, line)) return false;
    return !line.empty() && (line[0] == 'y' || line[0] == 'Y');
}

static void runProblem1() {
    sectionHeader(1, "Merge Overlapping Intervals");

    vector<pair<string, vector<Interval>>> cases = {
        {"Provided example",                     {{1,3},{2,6},{8,10},{15,18}}},
        {"Unsorted, nested and touching blocks", {{4,5},{1,4},{2,3},{9,9}}},
        {"Edge case - empty input",              {}}
    };

    int n = 1;
    for (const auto& c : cases) {
        testHeader(n++, c.first);
        cout << "    Input : " << toText(c.second) << "\n";
        cout << "    Output: " << toText(mergeIntervals(c.second)) << "\n";
    }
}

static void runProblem2() {
    sectionHeader(2, "Sort Colors - Counting and Dutch National Flag");

    vector<pair<string, vector<int>>> cases = {
        {"Provided example",                {2,0,2,1,1,0}},
        {"Edge case - one category only",   {2,2,2}},
        {"Edge case - empty input",         {}}
    };

    int n = 1;
    for (const auto& c : cases) {
        testHeader(n++, c.first);
        cout << "    Input          : " << toText(c.second) << "\n";

        vector<int> byCounting = c.second;
        sortColorsCounting(byCounting);
        cout << "    Counting sort  : " << toText(byCounting) << "\n";

        vector<int> byDNF = c.second;
        sortColorsDNF(byDNF);
        cout << "    Dutch Nat. Flag: " << toText(byDNF) << "\n";
        cout << "    Both agree     : " << (byCounting == byDNF ? "yes" : "NO") << "\n";
    }
}

static void runProblem3() {
    sectionHeader(3, "Largest Number From Concatenation");

    vector<pair<string, vector<int>>> cases = {
        {"Provided example",                 {3,30,34,5,9}},
        {"Prefix comparison matters",        {10,2}},
        {"Edge case - every value is zero",  {0,0,0}}
    };

    int n = 1;
    for (const auto& c : cases) {
        testHeader(n++, c.first);
        cout << "    Input : " << toText(c.second) << "\n";
        string answer = largestNumber(c.second);
        cout << "    Output: \"" << answer << "\"\n";
    }

    testHeader(n, "Edge case - empty input");
    cout << "    Input : []  (empty)\n";
    cout << "    Output: \"" << largestNumber({}) << "\"  (empty string)\n";
}

static void runProblem4() {
    sectionHeader(4, "Group Anagrams");

    vector<pair<string, vector<string>>> cases = {
        {"Provided example",                  {"eat","tea","tan","ate","nat","bat"}},
        {"Duplicates and a repeated word",    {"abc","cba","abc","xyz"}},
        {"Edge case - empty string included", {"", "", "a"}}
    };

    int n = 1;
    for (const auto& c : cases) {
        testHeader(n++, c.first);
        cout << "    Input : " << toText(c.second) << "\n";
        cout << "    Output: " << toText(groupAnagrams(c.second)) << "\n";
    }

    testHeader(n, "Edge case - empty input");
    cout << "    Input : []  (empty)\n";
    cout << "    Output: " << toText(groupAnagrams({})) << "\n";
}

static void runProblem5() {
    sectionHeader(5, "Meeting Rooms - Can One Person Attend Every Meeting?");

    vector<pair<string, vector<Interval>>> cases = {
        {"Provided example - overlap exists",     {{0,30},{5,10},{15,20}}},
        {"Back-to-back meetings are allowed",     {{1,5},{5,9},{9,12}}},
        {"Unsorted input with a hidden conflict", {{7,10},{2,4},{3,8}}},
        {"Edge case - no meetings at all",        {}}
    };

    int n = 1;
    for (const auto& c : cases) {
        testHeader(n++, c.first);
        cout << "    Input : " << toText(c.second) << "\n";
        cout << "    Output: " << (canAttendAllMeetings(c.second) ? "true" : "false") << "\n";
    }
}

static void runProblem6() {
    sectionHeader(6, "K Closest Points to Origin - Sorting vs Heap");

    vector<tuple<string, vector<Point>, int>> cases = {
        {"Provided example",               {{1,3},{-2,2}}, 1},
        {"Mixed signs, k in the middle",   {{3,3},{5,-1},{-2,4}}, 2},
        {"Edge case - k equals n",         {{0,1},{1,0}}, 2},
        {"Edge case - k is zero",          {{1,1},{2,2}}, 0}
    };

    int n = 1;
    for (const auto& c : cases) {
        testHeader(n++, get<0>(c));
        cout << "    Input : points = " << toText(get<1>(c))
             << ", k = " << get<2>(c) << "\n";
        vector<Point> bySort = kClosestBySorting(get<1>(c), get<2>(c));
        vector<Point> byHeap = kClosestByHeap(get<1>(c), get<2>(c));
        cout << "    Sorting solution: " << toText(bySort) << "\n";
        cout << "    Heap solution   : " << toText(byHeap) << "\n";
        cout << "    Distances agree : "
             << (sameDistances(bySort, byHeap) ? "yes" : "NO") << "\n";
    }
}

static void runProblem7() {
    sectionHeader(7, "Top K Frequent Elements");

    vector<tuple<string, vector<int>, int>> cases = {
        {"Provided example",                      {1,1,1,2,2,3}, 2},
        {"Frequency tie - smaller value first",   {5,5,4,4,3}, 2},
        {"Edge case - k larger than distinct set",{9,9,9}, 5},
        {"Edge case - empty input",               {}, 3}
    };

    int n = 1;
    for (const auto& c : cases) {
        testHeader(n++, get<0>(c));
        cout << "    Input : " << toText(get<1>(c)) << ", k = " << get<2>(c) << "\n";
        cout << "    Output: " << toText(topKFrequent(get<1>(c), get<2>(c))) << "\n";
    }
}

static void runProblem8() {
    sectionHeader(8, "Merge K Sorted Arrays");

    vector<pair<string, vector<vector<int>>>> cases = {
        {"Provided example",                    {{1,4,5},{1,3,4},{2,6}}},
        {"Very uneven lengths with duplicates", {{-5},{0,0,0},{-9,-4,7,7}}},
        {"Edge case - some lists are empty",    {{},{2,8},{}}},
        {"Edge case - every list is empty",     {{},{}}}
    };

    int n = 1;
    for (const auto& c : cases) {
        testHeader(n++, c.first);
        cout << "    Input : " << toText(c.second) << "\n";
        cout << "    Output: " << toText(mergeKSortedArrays(c.second)) << "\n";
    }
}

static void runProblem9() {
    sectionHeader(9, "Kth Largest Element - Quickselect");

    vector<tuple<string, vector<int>, int>> cases = {
        {"Provided example",                        {3,2,1,5,6,4}, 2},
        {"Duplicates count as separate positions",  {3,2,3,1,2,4,5,5,6}, 4},
        {"Edge case - k equals n (the minimum)",    {7,7,2}, 3},
        {"Edge case - single element",              {42}, 1}
    };

    int n = 1;
    for (const auto& c : cases) {
        testHeader(n++, get<0>(c));
        cout << "    Input : " << toText(get<1>(c)) << ", k = " << get<2>(c) << "\n";
        try {
            int answer = kthLargest(get<1>(c), get<2>(c));
            cout << "    Output: " << answer << "\n";
        } catch (const exception& e) {
            cout << "    Output: rejected (" << e.what() << ")\n";
        }
    }

    testHeader(n, "Edge case - k out of range");
    cout << "    Input : " << toText({1,2,3}) << ", k = 7\n";
    try {
        int answer = kthLargest({1, 2, 3}, 7);
        cout << "    Output: " << answer << "\n";
    } catch (const exception& e) {
        cout << "    Output: rejected (" << e.what() << ")\n";
    }
}

static void runProblem10() {
    sectionHeader(10, "Count Inversions - Modified Merge Sort");

    vector<pair<string, vector<int>>> cases = {
        {"Provided example",                     {2,4,1,3,5}},
        {"Reverse-sorted input (worst case)",    {5,4,3,2,1}},
        {"Duplicates are not inversions",        {2,2,2,2}},
        {"Edge case - empty input",              {}}
    };

    int n = 1;
    for (const auto& c : cases) {
        testHeader(n++, c.first);
        long long fast  = countInversions(c.second);
        long long slow  = countInversionsBruteForce(c.second);
        cout << "    Input          : " << toText(c.second) << "\n";
        cout << "    Output         : " << fast << "\n";
        cout << "    Brute force    : " << slow
             << "  -> " << (fast == slow ? "match" : "MISMATCH") << "\n";
    }
}

static void customRun(int problem) {
    cout << "\n  ---- Custom input for Problem " << problem << " ----\n";
    switch (problem) {
        case 1: {
            vector<Interval> in = readIntervalLine(
                "    Intervals as 'start end start end ...': ");
            cout << "    Input : " << toText(in) << "\n";
            cout << "    Output: " << toText(mergeIntervals(in)) << "\n";
            break;
        }
        case 2: {
            vector<int> in = readIntLine("    Values (0, 1 and 2 only): ");
            bool valid = true;
            for (int v : in) if (v < 0 || v > 2) valid = false;
            if (!valid) { cout << "    [!] Only 0, 1 and 2 are allowed.\n"; break; }
            vector<int> byCounting = in, byDNF = in;
            sortColorsCounting(byCounting);
            sortColorsDNF(byDNF);
            cout << "    Input          : " << toText(in) << "\n";
            cout << "    Counting sort  : " << toText(byCounting) << "\n";
            cout << "    Dutch Nat. Flag: " << toText(byDNF) << "\n";
            break;
        }
        case 3: {
            vector<int> in = readIntLine("    Nonnegative integers: ");
            bool valid = true;
            for (int v : in) if (v < 0) valid = false;
            if (!valid) { cout << "    [!] Values must be nonnegative.\n"; break; }
            cout << "    Input : " << toText(in) << "\n";
            cout << "    Output: \"" << largestNumber(in) << "\"\n";
            break;
        }
        case 4: {
            vector<string> in = readWordLine("    Words separated by spaces: ");
            cout << "    Input : " << toText(in) << "\n";
            cout << "    Output: " << toText(groupAnagrams(in)) << "\n";
            break;
        }
        case 5: {
            vector<Interval> in = readIntervalLine(
                "    Meetings as 'start end start end ...': ");
            cout << "    Input : " << toText(in) << "\n";
            cout << "    Output: " << (canAttendAllMeetings(in) ? "true" : "false") << "\n";
            break;
        }
        case 6: {
            vector<int> flat = readIntLine("    Points as 'x y x y ...': ");
            if (flat.size() % 2 != 0) { cout << "    [!] Need an even count.\n"; break; }
            vector<Point> pts;
            for (size_t i = 0; i + 1 < flat.size(); i += 2)
                pts.push_back({flat[i], flat[i + 1]});
            int k = readSingleInt("    k: ", 1);
            cout << "    Input : points = " << toText(pts) << ", k = " << k << "\n";
            cout << "    Sorting solution: " << toText(kClosestBySorting(pts, k)) << "\n";
            cout << "    Heap solution   : " << toText(kClosestByHeap(pts, k)) << "\n";
            break;
        }
        case 7: {
            vector<int> in = readIntLine("    Values: ");
            int k = readSingleInt("    k: ", 1);
            cout << "    Input : " << toText(in) << ", k = " << k << "\n";
            cout << "    Output: " << toText(topKFrequent(in, k)) << "\n";
            break;
        }
        case 8: {
            int count = readSingleInt("    How many sorted arrays? ", 0);
            vector<vector<int>> lists;
            for (int i = 0; i < count; ++i)
                lists.push_back(readIntLine("      Array " + to_string(i + 1)
                                            + " (already sorted): "));
            cout << "    Input : " << toText(lists) << "\n";
            cout << "    Output: " << toText(mergeKSortedArrays(lists)) << "\n";
            break;
        }
        case 9: {
            vector<int> in = readIntLine("    Values: ");
            int k = readSingleInt("    k: ", 1);
            cout << "    Input : " << toText(in) << ", k = " << k << "\n";
            try {
                int answer = kthLargest(in, k);
                cout << "    Output: " << answer << "\n";
            } catch (const exception& e) {
                cout << "    Output: rejected (" << e.what() << ")\n";
            }
            break;
        }
        case 10: {
            vector<int> in = readIntLine("    Values: ");
            cout << "    Input      : " << toText(in) << "\n";
            cout << "    Output     : " << countInversions(in) << "\n";
            cout << "    Brute force: " << countInversionsBruteForce(in) << "\n";
            break;
        }
        default: break;
    }
}

static void runProblem(int problem) {
    switch (problem) {
        case 1:  runProblem1();  break;
        case 2:  runProblem2();  break;
        case 3:  runProblem3();  break;
        case 4:  runProblem4();  break;
        case 5:  runProblem5();  break;
        case 6:  runProblem6();  break;
        case 7:  runProblem7();  break;
        case 8:  runProblem8();  break;
        case 9:  runProblem9();  break;
        case 10: runProblem10(); break;
        default: break;
    }
}

static void printMenu() {
    cout << "\n";
    cout << "============================================================\n";
    cout << "  EECE 7205 - Assignment #01   |   MyungJin Suh\n";
    cout << "  Sorting-Based Interview Problems\n";
    cout << "============================================================\n";
    cout << "   1. Merge Overlapping Intervals\n";
    cout << "   2. Sort Colors (Counting + Dutch National Flag)\n";
    cout << "   3. Largest Number From Concatenation\n";
    cout << "   4. Group Anagrams\n";
    cout << "   5. Meeting Rooms - Can Attend All\n";
    cout << "   6. K Closest Points to Origin (Sorting vs Heap)\n";
    cout << "   7. Top K Frequent Elements\n";
    cout << "   8. Merge K Sorted Arrays\n";
    cout << "   9. Kth Largest Element (Quickselect)\n";
    cout << "  10. Count Inversions (Modified Merge Sort)\n";
    cout << "  11. Run every problem\n";
    cout << "   0. Exit\n";
    cout << "------------------------------------------------------------\n";
    cout << "  Select a problem [0-11]: ";
    cout.flush();
}

int main() {
    while (true) {
        printMenu();

        string line;
        if (!getline(cin, line)) {
            cout << "\n";
            break;
        }

        istringstream in(line);
        int choice;
        if (!(in >> choice) || choice < 0 || choice > 11) {
            cout << "\n  [!] Please enter a whole number between 0 and 11.\n";
            continue;
        }

        if (choice == 0) {
            cout << "\n  Goodbye.\n";
            break;
        }

        if (choice == 11) {
            for (int p = 1; p <= 10; ++p) runProblem(p);
            continue;
        }

        runProblem(choice);
        if (askYes("\n  Run Problem " + to_string(choice)
                   + " on your own input? [y/N]: "))
            customRun(choice);
    }
    return 0;
}
