#define main assignment_main_disabled
#include "../cpp/Assignment01_Suh.cpp"
#undef main

#include <functional>

static bool operator==(const Interval& a, const Interval& b) {
    return a.start == b.start && a.end == b.end;
}
static bool operator==(const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}

static string describe(bool v)                          { return v ? "true" : "false"; }
static string describe(int v)                           { return to_string(v); }
static string describe(long long v)                     { return to_string(v); }
static string describe(const string& s)                 { return "\"" + s + "\""; }
static string describe(const vector<int>& v)            { return toText(v); }
static string describe(const vector<Interval>& v)       { return toText(v); }
static string describe(const vector<Point>& v)          { return toText(v); }
static string describe(const vector<string>& v)         { return toText(v); }
static string describe(const vector<vector<string>>& v) { return toText(v); }
static string describe(const vector<vector<int>>& v)    { return toText(v); }

static int g_passed = 0;
static int g_failed = 0;

static void section(int number, const string& title) {
    cout << "\n============================================================\n"
         << " PROBLEM " << number << ": " << title << "\n"
         << "============================================================\n";
}

static void record(const string& name, const string& input,
                   const string& actual, const string& expected, bool ok) {
    if (ok) {
        ++g_passed;
        cout << "\n  [PASS] " << name << "\n"
             << "    Input : " << input  << "\n"
             << "    Output: " << actual << "\n";
    } else {
        ++g_failed;
        cout << "\n  [FAIL] " << name << "\n"
             << "    Input   : " << input    << "\n"
             << "    Expected: " << expected << "\n"
             << "    Actual  : " << actual   << "\n";
    }
}

template <typename T>
static void check(const string& name, const string& input,
                  const T& actual, const T& expected) {
    record(name, input, describe(actual), describe(expected), actual == expected);
}

//============================================================================
// PROBLEM 1 - Merge Overlapping Intervals
//============================================================================

static void checkMerge(const string& name, vector<Interval> input,
                       const vector<Interval>& expected) {
    check(name, toText(input), mergeIntervals(input), expected);
}

static void testProblem1() {
    section(1, "Merge Overlapping Intervals");
    checkMerge("Provided example",
               {{1,3},{2,6},{8,10},{15,18}}, {{1,6},{8,10},{15,18}});
    checkMerge("Unsorted, with a nested and a touching interval",
               {{4,5},{1,4},{2,3},{9,9}}, {{1,5},{9,9}});
    checkMerge("Edge case: empty input", {}, {});
}

//============================================================================
// PROBLEM 2 - Sort Colors (both implementations)
//============================================================================

static void checkSortColors(const string& name, vector<int> input,
                            const vector<int>& expected) {
    vector<int> byCounting = input;
    sortColorsCounting(byCounting);
    vector<int> byDNF = input;
    sortColorsDNF(byDNF);

    bool ok = (byCounting == expected) && (byDNF == expected);
    string actual = "counting = " + toText(byCounting)
                  + " | Dutch National Flag = " + toText(byDNF);
    record(name, toText(input), actual, describe(expected), ok);
}

static void testProblem2() {
    section(2, "Sort Colors - Counting and Dutch National Flag");
    checkSortColors("Provided example", {2,0,2,1,1,0}, {0,0,1,1,2,2});
    checkSortColors("Swapped-in value must be re-examined", {1,2,0}, {0,1,2});
    checkSortColors("Edge case: empty input", {}, {});
}

//============================================================================
// PROBLEM 3 - Largest Number From Concatenation
//============================================================================

static void checkLargest(const string& name, const vector<int>& input,
                         const string& expected) {
    check(name, toText(input), largestNumber(input), expected);
}

static void testProblem3() {
    section(3, "Largest Number From Concatenation");
    checkLargest("Provided example",               {3,30,34,5,9}, "9534330");
    checkLargest("Numeric order alone would fail", {10,2},        "210");
    checkLargest("Edge case: every value is zero", {0,0,0},       "0");
}

//============================================================================
// PROBLEM 4 - Group Anagrams
//============================================================================

static void checkAnagrams(const string& name, const vector<string>& input,
                          const vector<vector<string>>& expected) {
    check(name, toText(input), groupAnagrams(input), expected);
}

static void testProblem4() {
    section(4, "Group Anagrams");
    checkAnagrams("Provided example; input order kept inside each group",
                  {"eat","tea","tan","ate","nat","bat"},
                  {{"eat","tea","ate"},{"tan","nat"},{"bat"}});
    checkAnagrams("Duplicates are kept, not merged",
                  {"abc","cba","abc","xyz"}, {{"abc","cba","abc"},{"xyz"}});
    checkAnagrams("Edge case: empty strings group together",
                  {"","","a"}, {{"",""},{"a"}});
}

//============================================================================
// PROBLEM 5 - Meeting Rooms
//============================================================================

static void checkMeetings(const string& name, const vector<Interval>& input,
                          bool expected) {
    check(name, toText(input), canAttendAllMeetings(input), expected);
}

static void testProblem5() {
    section(5, "Meeting Rooms - Can One Person Attend Every Meeting?");
    checkMeetings("Provided example has an overlap",
                  {{0,30},{5,10},{15,20}}, false);
    checkMeetings("Back-to-back meetings are allowed",
                  {{1,5},{5,9},{9,12}}, true);
    checkMeetings("Edge case: no meetings at all", {}, true);
}

//============================================================================
// PROBLEM 6 - K Closest Points to the Origin
//============================================================================

static void checkKClosest(const string& name, const vector<Point>& points,
                          int k, const vector<Point>& expected) {
    vector<Point> bySort = kClosestBySorting(points, k);
    vector<Point> byHeap = kClosestByHeap(points, k);

    bool ok = sameDistances(bySort, expected) && sameDistances(byHeap, expected);
    string actual = "sorting = " + toText(bySort)
                  + " | heap = " + toText(byHeap);
    record(name, toText(points) + ", k = " + to_string(k),
           actual, describe(expected), ok);
}

static void testProblem6() {
    section(6, "K Closest Points to Origin - Sorting vs Heap");
    checkKClosest("Provided example", {{1,3},{-2,2}}, 1, {{-2,2}});
    checkKClosest("Mixed signs, k in the middle",
                  {{3,3},{5,-1},{-2,4}}, 2, {{3,3},{-2,4}});
    checkKClosest("Edge case: k is zero", {{1,1},{2,2}}, 0, {});
}

//============================================================================
// PROBLEM 7 - Top K Frequent Elements
//============================================================================

static void checkTopK(const string& name, const vector<int>& input,
                      int k, const vector<int>& expected) {
    check(name, toText(input) + ", k = " + to_string(k),
          topKFrequent(input, k), expected);
}

static void testProblem7() {
    section(7, "Top K Frequent Elements");
    checkTopK("Provided example",                       {1,1,1,2,2,3}, 2, {1,2});
    checkTopK("Frequency tie returns the smaller first",{5,5,4,4,3},   2, {4,5});
    checkTopK("Edge case: k exceeds the distinct count",{9,9,9},       5, {9});
}

//============================================================================
// PROBLEM 8 - Merge K Sorted Arrays
//============================================================================

static void checkMergeK(const string& name, const vector<vector<int>>& input,
                        const vector<int>& expected) {
    check(name, toText(input), mergeKSortedArrays(input), expected);
}

static void testProblem8() {
    section(8, "Merge K Sorted Arrays");
    checkMergeK("Provided example",
                {{1,4,5},{1,3,4},{2,6}}, {1,1,2,3,4,4,5,6});
    checkMergeK("Very uneven lengths and negatives",
                {{-5},{0,0,0},{-9,-4,7,7}}, {-9,-5,-4,0,0,0,7,7});
    checkMergeK("Edge case: some arrays empty", {{},{2,8},{}}, {2,8});
}

//============================================================================
// PROBLEM 9 - Kth Largest Element
//============================================================================

static void checkKth(const string& name, const vector<int>& input,
                     int k, int expected) {
    check(name, toText(input) + ", k = " + to_string(k),
          kthLargest(input, k), expected);
}

static void checkKthRejected(const string& name, const vector<int>& input, int k) {
    string in = toText(input) + ", k = " + to_string(k);
    try {
        int got = kthLargest(input, k);
        record(name, in, describe(got), "rejected with an exception", false);
    } catch (const exception& e) {
        record(name, in, string("rejected (") + e.what() + ")",
               "rejected with an exception", true);
    }
}

static void testProblem9() {
    section(9, "Kth Largest Element - Quickselect");
    checkKth("Provided example", {3,2,1,5,6,4}, 2, 5);
    checkKth("Duplicates count as separate positions",
             {3,2,3,1,2,4,5,5,6}, 4, 4);
    checkKthRejected("Edge case: k above n is rejected", {1,2,3}, 7);
}

//============================================================================
// PROBLEM 10 - Count Inversions
//============================================================================

static void checkInversions(const string& name, const vector<int>& input,
                            long long expected) {
    long long fast  = countInversions(input);
    long long slow  = countInversionsBruteForce(input);
    bool ok = (fast == expected) && (slow == expected);
    string actual = to_string(fast) + "  (brute force: " + to_string(slow)
                  + (fast == slow ? " - match)" : " - MISMATCH)");
    record(name, toText(input), actual, describe(expected), ok);
}

static void testProblem10() {
    section(10, "Count Inversions - Modified Merge Sort");
    checkInversions("Provided example",                {2,4,1,3,5},  3);
    checkInversions("Reverse sorted, the maximum n(n-1)/2",
                                                       {5,4,3,2,1}, 10);
    checkInversions("Edge case: equal values are not inversions",
                                                       {2,2,2,2},    0);
}

//============================================================================

int main(int argc, char** argv) {
    const vector<function<void()>> suites = {
        testProblem1, testProblem2, testProblem3, testProblem4, testProblem5,
        testProblem6, testProblem7, testProblem8, testProblem9, testProblem10
    };

    int only = 0;
    if (argc > 1) {
        only = atoi(argv[1]);
        if (only < 1 || only > 10) {
            cout << "Usage: " << argv[0] << " [problem number 1-10]\n";
            return 2;
        }
    }

    cout << "============================================================\n"
         << "  EECE 7205 - Assignment #01 | Test Results\n"
         << "  MyungJin Suh\n";
    if (only) cout << "  Running Problem " << only << " only\n";
    cout << "============================================================\n";

    if (only) suites[only - 1]();
    else      for (const auto& run : suites) run();

    cout << "\n============================================================\n"
         << "  RESULT: " << g_passed << " passed, " << g_failed << " failed\n"
         << "============================================================\n";

    return g_failed == 0 ? 0 : 1;
}
