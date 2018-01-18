# AutoDiff
A C++ library of automatic differentiation based on static computational graph.

## Demo

```cpp
#include <AutoDiff/autodiff.h>

#include <iostream>
#include <vector>

using namespace std;

void test_backward() {
    ad::Node x1 = ad::Variable("x1");
    ad::Node x2 = ad::Variable("x2");
    ad::Node y = 3 * x1 + 4 * x2 + 5;
    auto t = Gradients(y, vector<ad::Node>{x1, x2});
    ad::Executor e(vector<ad::Node> { y, t[0], t[1] });
    ad::FeedDict feed_dict;
    vector<ad::Ctype> ans;
    feed_dict[x1] = 5;
    feed_dict[x2] = 5;
    ans = e.run(feed_dict);

    cout << "y: " << ans[0] << endl;
    cout << "dy/dx1: " << ans[1] << endl;
    cout << "dy/dx2: " << ans[2] << endl;

    feed_dict[x1] = 2;
    feed_dict[x2] = 6;
    ans = e.run(feed_dict);

    cout << "y: " << ans[0] << endl;
    cout << "dy/dx1: " << ans[1] << endl;
    cout << "dy/dx2: " << ans[2] << endl;
}

int main() {
    test_backward();
    return 0;
}
```