#include <iostream>
#include <deque>
#include <assert.h>

using namespace std;

struct Polygon {
  struct ColoredSequence {int color; deque<int> points;};
  
  int count[3];
  deque<ColoredSequence> compressed;
};

istream& operator>>(istream& in, Polygon& P){
  int n;
  string colors;
  in >> n >> colors;

  assert(n == (int)colors.size());

  P.count[0] = P.count[1] = P.count[2] = 0;

  for (int i = 0, j = 0; i < n; i = j){
    while (j < n && colors[i] == colors[j]) ++j;

    int color = colors[i] - '1';
    P.count[color] += j-i;

    Polygon::ColoredSequence sequence;
    sequence.color = color;
    for (int k = i; k <= j; ++k) sequence.points.push_back(k % n);

    P.compressed.push_back(sequence);
  }

  return in;
}

int main(){
  Polygon P;
  cin >> P;

  // NE condition
  if (P.compressed.size() == 1 ||
      P.count[0] % 2 != P.count[1] % 2 ||
      P.count[1] % 2 != P.count[2] % 2 ||
      P.count[2] % 2 != P.count[0] % 2){
    cout << "NE" << endl;
    return 0;
  }

  cout << "DA" << endl;
  // ending on a triangle
  while (P.count[0] + P.count[1] + P.count[2] != 3){
    // moving makes no copy, if we copied 
    auto first = move(P.compressed.front());
    P.compressed.pop_front();
    auto second = move(P.compressed.front());
    P.compressed.pop_front();

    // empty sequence, no edges
    if (first.points.size() == 1){
      P.compressed.push_front(move(second));
      continue;
    }

    if (second.points.size() == 1){
      P.compressed.push_front(move(first));
      continue;
    }

    if (first.color == second.color){
      // O(n^2) --> O(n log n)
      if (first.points.size() > second.points.size()){
	// begin()+1 because they share a single point
	first.points.insert(first.points.end(), second.points.begin()+1, second.points.end());
	P.compressed.push_front(move(first));
      } else {
	second.points.insert(second.points.begin(), first.points.begin(), first.points.end()-1);
	P.compressed.push_front(move(second));
      }
      continue;
    }

    // usual transformation leads to monochromatic polygon, need to avoid it
    // we just rotate, the big sequence will be next on the chopping block
    if (P.count[first.color] == 1 &&
        P.count[second.color] == 1) {
      P.compressed.push_back(move(first));
      P.compressed.push_back(move(second));
      continue;
    }

    --P.count[first.color];
    --P.count[second.color];
    ++P.count[3-first.color-second.color];

    first.points.pop_back(); // same point removed from first and second
    second.points.pop_front();
    Polygon::ColoredSequence middle;
    middle.color = 3-first.color-second.color;
    middle.points = {first.points.back(), second.points.front()};
    cout << middle.points.front()+1 << " " << middle.points.back()+1 << " " << middle.color+1 << endl;
    P.compressed.push_front(move(second));
    P.compressed.push_front(move(middle));
    P.compressed.push_front(move(first));
  }

  return 0;
}
