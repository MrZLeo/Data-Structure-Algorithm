#include "heap.hpp"
#include "lcsubstring.h"
#include "shortest_path.h"
#include <iostream>
#include <ostream>

int main()
{
    using std::cout;
    using std::endl;

    auto t = Graph("/Users/mrzleo/CLionProjects/Data-Structure-Algorithm/cpp/g.txt");
    auto res = t.shortest_path(0);
    for (int i = 0; i < res.size(); ++i) {
        cout << i << ": " << res[i] << endl;
    }

    /* std::string a = "xzyzzyx"; */
    /* std::string b = "zxyyzxz"; */

    /* int res = algo::lcss(a, b); */
    /* std::cout << "res = " << res << std::endl; */
}
