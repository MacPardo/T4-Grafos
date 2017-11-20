#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <functional>
#include <algorithm>

#define DEBUG if(false)

using namespace std;
typedef vector<int> vi;
typedef vector<vi> graph;

template<typename T>
void print_contents(T const& coll) {
  for (typename T::const_iterator it = coll.begin(); it != coll.end(); it++) {
    cout << *it << ' ';
  }
  cout << '\n';
}

template<typename A, typename B>
bool share_elements(A const& a, B const& b) {
  for (typename A::const_iterator i = a.begin(); i != a.end(); i++) {
    for (typename B::const_iterator j = b.begin(); j != b.end(); j++) {
      if (*i == *j) return true;
    }
  }
  return false;
}

vi welsh_powell(graph g) {
  vi not_colored, color_scheme, now_colored;
  int color;

  for (int i = 0; i < g.size(); i++) {
    not_colored.push_back(i);
    color_scheme.push_back(0);
  }

  sort(not_colored.begin(), not_colored.end(), [&](int a, int b) {
      return g[a].size() > g[b].size();
    });

  color = 1;
  while (!not_colored.empty()) {
    for (int i = 0; i < not_colored.size(); i++) {
      if (!share_elements(g[not_colored[i]], now_colored)) {
	color_scheme[not_colored[i]] = color;
	now_colored.push_back(not_colored[i]);
	not_colored.erase(not_colored.begin() + i--);
	
	DEBUG {
	  cout << "NOT COLORED\n";
	  print_contents(not_colored);
	  cout << "NOW COLORED\n";
	  print_contents(now_colored);
	  cout << "COLOR SCHEME\n";
	  print_contents(color_scheme);
	  cout << "i = " << i << " size = " << not_colored.size() <<  '\n';
	  cout << "\n\n";
	}
      }
    }
    now_colored.clear();
    color++;
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
    cout << (char)('A' + i) << " -> " << color_scheme[i] <<
      '\n';
  }
  return 0;
}
