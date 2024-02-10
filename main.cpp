#include "kd_trees.h"
#include <iostream>
#include <vector>

int main(int argc, char** argv)
{
    kd_trees::KDTree tree;
    std::vector<kd_trees::Point> points = {kd_trees::Point({2, 3}), kd_trees::Point({5, 4}), kd_trees::Point({9, 6}), kd_trees::Point({4, 7}), 
                                            kd_trees::Point({8, 1}), kd_trees::Point({7, 2})};
    
    // auto node = std::make_shared<kd_trees::KDNode>(points[0]);
    for (auto point : points)
    {
        // std::cout<<" next pt"<<std::endl;
        tree.insert(point);
    }
    kd_trees::Point target({9, 2});
    kd_trees::Point nearest = tree.nearest(target);
    nearest.print();
    std::cout<< " printing the tree "<<std::endl;
    tree.print();
    return 1;
}