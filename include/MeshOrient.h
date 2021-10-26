#include <vector>
#define NON_MANIFOLD_EDGE_TAG -1
namespace TIGER {
    int resetOrientation(std::vector<std::vector<double>> &point_list, std::vector<std::vector<int>> &facet_list, std::vector<int> &blockMark);
};