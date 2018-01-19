//
// Created by Administrator on 2018/1/19.
//

#include <assert.h>
#include <vector>
#include <AutoDiff/autodiff.h>

using namespace std;

void test_add_by_const()
{
    ad::Node x = ad::Variable("x");
    auto y = x + 5;
    auto grads = ad::Gradients(y, vector<ad::Node>{x});
    ad::FeedDict feed_dict;
    feed_dict[x] = 10;
    ad::Executor e(vector<ad::Node> { y, grads[0] });
    auto ans = e.run(feed_dict);
    assert(ans[0]==15);
    assert(ans[1]==1);
}

//TODO: Add Tests

int main()
{
    test_add_by_const();
}