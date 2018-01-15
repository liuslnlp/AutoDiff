#include <AutoDiff/autodiff.h>

#include <iostream>

using namespace std;
using ad::Node;
using ad::Ctype;


void test_forward() {
    Node x = ad::Variable("x");
    Node y = x + 3;
    Node z = y + 2;
    Node zz = x + y + z;

    vector<Node> vals{x, y, z, zz};
    ad::Executor e(vals);
    ad::FeedDict feed_dict;
    feed_dict[x] = 5;
    vector<Ctype> ans = e.run(feed_dict);
    for (auto &i : ans) {
        cout << i << " ";
    }
    cout << endl;
    cout << y.name << endl;
    cout << z.name << endl;
    cout << zz.name << endl;
}

void test_backward() {
    Node x1 = ad::Variable("x1");
    Node x2 = ad::Variable("x2");
    Node y = 3 * x1 + 4 * x2 + 5;
    auto t = Gradients(y, vector<Node>{x1, x2});
    ad::Executor e(vector<Node> { y, t[0], t[1] });
    ad::FeedDict feed_dict;
    vector<Ctype> ans;
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