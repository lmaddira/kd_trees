/**
 * implement the structure of kd_trees
*/

#ifndef KD_TREES_H
#define KD_TREES_H


#include <iostream>
#include <array>
#include <memory>



namespace kd_tress{
    constexpr size_t kDimensions = 5; // define dimensions during compile time

    struct Point
    {
        std::array<double, kDimensions> coordinates_;
        Point(std::array<double, kDimensions> coordinates) : coordinates_(std::move(coordinates)) {}  
    };

    double distance(const Point& from_pt, const Point& to_point);

    class KDNode
    {
    public:
        Point pt_;
        std::shared_ptr<KDNode> left_ptr_, right_ptr_;
        KDNode(Point pt) : pt_(std::move(pt)), left_ptr_(nullptr), right_ptr_(nullptr){}
    };

    class KDTree
    {
    public:
        std::shared_ptr<KDNode> root_;
        
        KDTree() : root_(nullptr){}

        ~KDTree() = default;

        /**
         * @details insert the \p pt as node in the KDTree
         * @param node is the current node to check if \p pt belongs to right or left ptr
         * @param depth is the depth of the current recursion at which \p pt is being checked to insert
         * @param pt to be inserted in the tree   
        */
        void insertRec(std::shared_ptr<KDNode>& node, const Point& pt, size_t depth);

        /**
         * @details inserts \p pt in the tree 
        */
        void insert(const Point& pt);

        /**
         * @details finds and returns the nearest node to \p pt in the tree recursively
         * @param node is the current node to check distance from \p pt and send it to right or left tree recursively
         * @param depth is the depth of the current recursion at which \p pt is being checked for distance
         * @param pt to be inserted in the tree  
         * @param min_dist is the current min_dist
        */
        void nearestRec(const std::shared_ptr<KDNode>& node, const Point& pt, size_t depth, double& min_dist, std::shared_ptr<KDNode>& nearest_node);

        /**
         * @details finds and returns the nearest node to \p pt in the tree
        */
        std::shared_ptr<KDNode> nearest(const Point& pt);

        /**
         * @details searaches the tree to find if the point is in the tree recursively
        */
        bool search(const std::shared_ptr<KDNode>& node, const Point& pt, size_t depth);

        /**
         * @details searaches the tree to find if the point is in the tree
        */
        bool search(const Point& pt);
    };
} // namespace kd_trees



#endif 