#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <functional>

using namespace std;
typedef vector<int> vi;
typedef vector<vi> graph;

vector<int> welsh_powell(graph g) {
  vector<int> color_scheme(g.size());
  set<int, function<bool (int, int)> > not_colored([&g](int a, int b) {
      return g[a].size() < g[b].size();
    });
  for (int i = 0; i < g.size(); i++) not_colored.insert(i);
  
  for (int color = 0; !not_colored.empty(); color++) {
    int previous = - 1;

    for (set<int>::iterator it = not_colored.begin(); it != not_colored.end(); it++) {
      cout << "PREVIOUS = " << previous << '\n';
      if (previous == -1 || not_colored.find(previous) == not_colored.end()) {
	color_scheme[*it] = color;
	previous = *it;
	not_colored.erase(it);
      }
    }
  }

  return color_scheme;
}

int main(void) {
  int v, e, a, b;
  cin >> v >> e;
  graph g(v);
  while (e--) {
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  vi color_scheme = welsh_powell(g);
  cout << "VERTICE -> COR\n";
  for (int i = 0; i < color_scheme.size(); i++) {
    cout << i << " -> " << color_scheme[i] <<
      '\n';
  }
  return 0;
}
