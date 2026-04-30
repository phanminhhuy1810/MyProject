#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;

const string SEP(50, '-');

void printArr(const vector<int>& a) {
    cout << "[";
    for (int i = 0; i < (int)a.size(); i++)
        cout << a[i] << (i + 1 < (int)a.size() ? ", " : "");
    cout << "]";
}

// ══════════════════════════════════════════════════════
// 1. BUBBLE SORT — O(n²)
// ══════════════════════════════════════════════════════
void bubbleSort(vector<int> a) {
    int n = a.size();
    cout << "1. BUBBLE SORT  O(n²)\n";
    cout << "   Ban đầu: "; printArr(a); cout << "\n";
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                cout << "   đổi → "; printArr(a); cout << "\n";
            }
    cout << "   Kết quả: "; printArr(a); cout << "\n\n";
}

// ══════════════════════════════════════════════════════
// 2. SELECTION SORT — O(n²)
// ══════════════════════════════════════════════════════
void selectionSort(vector<int> a) {
    int n = a.size();
    cout << "2. SELECTION SORT  O(n²)\n";
    cout << "   Ban đầu: "; printArr(a); cout << "\n";
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[minIdx]) minIdx = j;
        swap(a[i], a[minIdx]);
        cout << "   vị trí " << i << ": min=" << a[i] << " → "; printArr(a); cout << "\n";
    }
    cout << "   Kết quả: "; printArr(a); cout << "\n\n";
}

// ══════════════════════════════════════════════════════
// 3. INSERTION SORT — O(n²)
// ══════════════════════════════════════════════════════
void insertionSort(vector<int> a) {
    int n = a.size();
    cout << "3. INSERTION SORT  O(n²)\n";
    cout << "   Ban đầu: "; printArr(a); cout << "\n";
    for (int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;
        while (j >= 0 && a[j] > key) { a[j + 1] = a[j]; j--; }
        a[j + 1] = key;
        cout << "   chèn " << key << " → "; printArr(a); cout << "\n";
    }
    cout << "   Kết quả: "; printArr(a); cout << "\n\n";
}

// ══════════════════════════════════════════════════════
// 4. QUICK SORT — O(n log n) avg, O(n²) worst
// ══════════════════════════════════════════════════════
void _quickSort(vector<int>& a, int lo, int hi, int depth) {
    if (lo >= hi) return;
    int pivot = a[hi], i = lo - 1;
    for (int j = lo; j < hi; j++)
        if (a[j] <= pivot) { i++; swap(a[i], a[j]); }
    swap(a[i + 1], a[hi]);
    int p = i + 1;
    string indent(3 + depth * 2, ' ');
    cout << indent << "pivot=" << pivot << " → [";
    for (int k = lo; k <= hi; k++) cout << a[k] << (k < hi ? ", " : "");
    cout << "]\n";
    _quickSort(a, lo, p - 1, depth + 1);
    _quickSort(a, p + 1, hi, depth + 1);
}

void quickSort(vector<int> a) {
    cout << "4. QUICK SORT  O(n log n) avg\n";
    cout << "   Ban đầu: "; printArr(a); cout << "\n";
    _quickSort(a, 0, a.size() - 1, 0);
    cout << "   Kết quả: "; printArr(a); cout << "\n\n";
}

// ══════════════════════════════════════════════════════
// 5. MERGE SORT — O(n log n)
// ══════════════════════════════════════════════════════
vector<int> _mergeSort(vector<int> a) {
    if (a.size() <= 1) return a;
    int mid = a.size() / 2;
    vector<int> L = _mergeSort({a.begin(), a.begin() + mid});
    vector<int> R = _mergeSort({a.begin() + mid, a.end()});
    vector<int> merged;
    int i = 0, j = 0;
    while (i < (int)L.size() && j < (int)R.size())
        merged.push_back(L[i] <= R[j] ? L[i++] : R[j++]);
    while (i < (int)L.size()) merged.push_back(L[i++]);
    while (j < (int)R.size()) merged.push_back(R[j++]);
    cout << "   merge "; printArr(L); cout << " + "; printArr(R);
    cout << " → "; printArr(merged); cout << "\n";
    return merged;
}

void mergeSort(vector<int> a) {
    cout << "5. MERGE SORT  O(n log n)\n";
    cout << "   Ban đầu: "; printArr(a); cout << "\n";
    vector<int> result = _mergeSort(a);
    cout << "   Kết quả: "; printArr(result); cout << "\n\n";
}

// ══════════════════════════════════════════════════════
// 6. COUNTING SORT — O(n + k)
// ══════════════════════════════════════════════════════
void countingSort(vector<int> a) {
    int lo = *min_element(a.begin(), a.end());
    int hi = *max_element(a.begin(), a.end());
    vector<int> count(hi - lo + 1, 0);
    for (int x : a) count[x - lo]++;
    cout << "6. COUNTING SORT  O(n + k)\n";
    cout << "   Ban đầu: "; printArr(a); cout << "\n";
    cout << "   đếm [" << lo << ".." << hi << "]: "; printArr(count); cout << "\n";
    vector<int> result;
    for (int i = 0; i < (int)count.size(); i++)
        for (int j = 0; j < count[i]; j++)
            result.push_back(i + lo);
    cout << "   Kết quả: "; printArr(result); cout << "\n\n";
}

// ══════════════════════════════════════════════════════
// 7. QUICK SELECT — Phần tử lớn thứ k — O(n) avg
// ══════════════════════════════════════════════════════
int _quickSelect(vector<int>& a, int lo, int hi, int target) {
    if (lo == hi) return a[lo];
    int pivot = a[hi], i = lo - 1;
    for (int j = lo; j < hi; j++)
        if (a[j] <= pivot) { i++; swap(a[i], a[j]); }
    swap(a[i + 1], a[hi]);
    int p = i + 1;
    cout << "   pivot=" << pivot << ", p=" << p << " → [";
    for (int k = lo; k <= hi; k++) cout << a[k] << (k < hi ? ", " : "");
    cout << "]\n";
    if (p == target) return a[p];
    return target < p ? _quickSelect(a, lo, p - 1, target)
                      : _quickSelect(a, p + 1, hi, target);
}

void quickSelect(vector<int> arr, int k) {
    int n = arr.size();
    cout << "7. QUICK SELECT — phần tử lớn thứ " << k << "  O(n) avg\n";
    cout << "   Ban đầu: "; printArr(arr); cout << "\n";
    int result = _quickSelect(arr, 0, n - 1, n - k);
    cout << "   → Phần tử lớn thứ " << k << " = " << result << "\n\n";
}

// ══════════════════════════════════════════════════════
// 8. K-TH LARGEST BẰNG MIN-HEAP — O(n log k)
// ══════════════════════════════════════════════════════
void kthLargestHeap(vector<int> arr, int k) {
    cout << "8. K-TH LARGEST BẰNG HEAP  O(n log k)\n";
    cout << "   Ban đầu: "; printArr(arr); cout << "\n";
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int x : arr) {
        minHeap.push(x);
        if ((int)minHeap.size() > k) {
            int removed = minHeap.top(); minHeap.pop();
            cout << "   +" << x << ", -" << removed << " → heap top=" << minHeap.top() << "\n";
        } else {
            cout << "   +" << x << "       → heap top=" << minHeap.top() << "\n";
        }
    }
    cout << "   → Phần tử lớn thứ " << k << " = " << minHeap.top() << "\n\n";
}

// ══════════════════════════════════════════════════════
// 9. ĐẾM NGHỊCH THẾ — O(n log n)
// ══════════════════════════════════════════════════════
pair<vector<int>, long long> _mergeCount(vector<int> a) {
    if (a.size() <= 1) return {a, 0};
    int mid = a.size() / 2;
    auto [L, lc] = _mergeCount({a.begin(), a.begin() + mid});
    auto [R, rc] = _mergeCount({a.begin() + mid, a.end()});
    vector<int> merged;
    long long inv = lc + rc;
    int i = 0, j = 0;
    while (i < (int)L.size() && j < (int)R.size()) {
        if (L[i] <= R[j]) merged.push_back(L[i++]);
        else { inv += L.size() - i; merged.push_back(R[j++]); }
    }
    while (i < (int)L.size()) merged.push_back(L[i++]);
    while (j < (int)R.size()) merged.push_back(R[j++]);
    long long extra = inv - lc - rc;
    if (extra > 0) {
        cout << "   merge "; printArr(L); cout << " + "; printArr(R);
        cout << " → "; printArr(merged);
        cout << "  (+" << extra << " nghịch thế)\n";
    }
    return {merged, inv};
}

void countInversions(vector<int> arr) {
    cout << "9. ĐẾM NGHỊCH THẾ  O(n log n)\n";
    cout << "   Ban đầu: "; printArr(arr); cout << "\n";
    auto [_, total] = _mergeCount(arr);
    cout << "   → Tổng nghịch thế = " << total << "\n\n";
}

// ══════════════════════════════════════════════════════
// 10. SỐ LẺ TRƯỚC, SỐ CHẴN SAU — O(n), stable
// ══════════════════════════════════════════════════════
void oddBeforeEven(vector<int> arr) {
    vector<int> odds, evens;
    for (int x : arr) (x % 2 != 0 ? odds : evens).push_back(x);
    vector<int> result = odds;
    result.insert(result.end(), evens.begin(), evens.end());
    cout << "10. SỐ LẺ TRƯỚC, SỐ CHẴN SAU  O(n)\n";
    cout << "    Ban đầu: "; printArr(arr); cout << "\n";
    cout << "    lẻ:   "; printArr(odds); cout << "\n";
    cout << "    chẵn: "; printArr(evens); cout << "\n";
    cout << "    Kết quả: "; printArr(result); cout << "\n\n";
}

// ══════════════════════════════════════════════════════
// 11. SẮP XẾP NHIỀU TIÊU CHÍ
// ══════════════════════════════════════════════════════
struct Student {
    string name, grade;
    int score;
};

void multiCriteriaSort() {
    vector<Student> students = {
        {"An",   "B", 78},
        {"Binh", "A", 92},
        {"Chi",  "B", 85},
        {"Duy",  "A", 92},
        {"Em",   "C", 60},
        {"Phuc", "A", 88},
    };

    cout << "11. SẮP XẾP NHIỀU TIÊU CHÍ\n";
    cout << "    Dữ liệu gốc:\n";
    for (auto& s : students)
        cout << "      " << s.grade << "  " << s.score << "  " << s.name << "\n";

    // Cách 1: lambda — grade ↑, score ↓, name ↑
    auto byCriteria = [](const Student& a, const Student& b) {
        if (a.grade != b.grade) return a.grade < b.grade;
        if (a.score != b.score) return a.score > b.score;  // desc
        return a.name < b.name;
    };

    vector<Student> r1 = students;
    sort(r1.begin(), r1.end(), byCriteria);
    cout << "\n    Kết quả (grade ↑, score ↓, name ↑):\n";
    for (auto& s : r1)
        cout << "      " << s.grade << "  " << s.score << "  " << s.name << "\n";
    cout << "\n";
}

// ══════════════════════════════════════════════════════
// MAIN
// ══════════════════════════════════════════════════════
int main() {
    vector<int> data = {5, 3, 8, 1, 9, 2, 7, 4, 6};
    int K = 3;

    cout << SEP << "\n"; bubbleSort(data);
    cout << SEP << "\n"; selectionSort(data);
    cout << SEP << "\n"; insertionSort(data);
    cout << SEP << "\n"; quickSort(data);
    cout << SEP << "\n"; mergeSort(data);
    cout << SEP << "\n"; countingSort(data);
    cout << SEP << "\n"; quickSelect(data, K);
    cout << SEP << "\n"; kthLargestHeap(data, K);
    cout << SEP << "\n"; countInversions(data);
    cout << SEP << "\n"; oddBeforeEven(data);
    cout << SEP << "\n"; multiCriteriaSort();
    cout << SEP << "\n";

    return 0;
}
