
	// sort, reverse, find, set_intersection/diff/union
	// nth_element

vector<int> v;
bool cmp(int &a, int &b) {
	// 5    3
	if (a > b) { return true; } 

	// 3     5
	if (a < b) { return true; }


}

sort(v.begin(), v.end(), less<int>());
sort(v.begin(), v.end(), greater<int>());

int v[100];
sort(v, v+n, less<int>());
sort(v + 1, v +1 + n, less<int>());

vector<int> v;
int x = 10;
auto it = find(v.begin(), v.end(), x);
if (it != v.end()) {
	// DA
} else {
	// NU
}

nth_element(v.begin(), v.begin() + k, v.end())



