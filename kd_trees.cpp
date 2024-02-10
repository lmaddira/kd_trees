/**
 * Implements the functionality of KD trees
*/

#include "kd_trees.h"
#include <cmath>

namespace kd_trees
{
    void Point::print()
    {   
        std::cout<< " pt : ";
        for (int i = 0; i < kDimensions; ++i)
        {
            std::cout<< this->coordinates_[i] <<",";
        }
        std::cout<<std::endl;
    }

    double& Point::operator[](int index)
    {
        if(index < 0 || index >= kDimensions)
            throw std::out_of_range("index is out of range");

        return this->coordinates_[index];
    }

    const double& Point::operator[](int index) const
    {
        if(index < 0 || index >= kDimensions)
            throw std::out_of_range("index is out of range");

        return this->coordinates_[index];
    }

    bool Point::operator==(const Point& other)const
    {
        for (int i = 0; i < kDimensions; ++i)
        {
            if(this->coordinates_[i] != other.coordinates_[i])
                return false;
        }
        return true;
    }

    double distance(const Point& from_pt, const Point& to_point)
    {
        double distance = 0;
        for (int i = 0; i < kDimensions; ++i)
        {
            double d = from_pt.coordinates_[i] - to_point.coordinates_[i];
            distance += d*d;
        }
        return std::sqrt(distance);
    }

    void KDTree::insertRec(std::shared_ptr<KDNode>& node, Point& pt, size_t depth)
    {
        if (node == nullptr)
        {
            node = std::make_shared<KDNode>(pt);
            return;
        }

        int cd = depth % kDimensions;
        // std::cout<<" cd "<< cd <<" depth "<< depth << " pt "<<pt.coordinates_[cd] <<" node pt "<< node->pt_.coordinates_[cd]<<std::endl;

        if (pt.coordinates_[cd] < node->pt_.coordinates_[cd])
        {
            // std::cout<<"going left"<<std::endl;
            insertRec(node->left_ptr_, pt, depth+1);
        }
        else
        {
            // std::cout<<"going right"<<std::endl;
            insertRec(node->right_ptr_, pt, depth+1);
        }
    }

    void KDTree::insert(Point& pt)
    {
        insertRec(root_, pt, 0);
    }

    void KDTree::nearestRec(const std::shared_ptr<KDNode>& node, const Point& target, size_t depth, double& min_dist, std::shared_ptr<KDNode>& nearest_node)
    {
        if(!node) return;

        double curr_dist = distance(node->pt_, target);
        if (curr_dist < min_dist)
        {
            min_dist = curr_dist;
            nearest_node = node;
        }
        int cd = depth % kDimensions;

        double dx = target.coordinates_[cd] - node->pt_.coordinates_[cd];
        std::shared_ptr<KDNode> next_branch = dx < 0 ? node->left_ptr_ : node->right_ptr_;
        std::shared_ptr<KDNode> opposite_branch = dx < 0 ? node->right_ptr_ : node->left_ptr_;

        nearestRec(next_branch, target, depth+1, min_dist, nearest_node);

        if (abs(dx) < min_dist)
        {
            nearestRec(opposite_branch, target, depth+1, min_dist, nearest_node);
        }
    }

    Point KDTree::nearest(const Point& pt)
    {
        if(!root_)
        {
            std::cout<<"Nearest node is null as tree doesn't have any points !!!!!!!!! "<<std::endl;
            throw std::logic_error("tree is empty!");
        }    
        auto nearest_node = root_;
        double min_dist = distance(nearest_node->pt_, pt);
        nearestRec(root_, pt, 0, min_dist, nearest_node);
        return nearest_node->pt_;
    }

    bool KDTree::searchRec(const std::shared_ptr<KDNode>& node, const Point& target, size_t depth)
    {
        if(!node) return false;
        if(node->pt_ == target) return true;
        int cd = depth % kDimensions;
        if(target.coordinates_[cd] < node->pt_.coordinates_[cd])
            return searchRec(node->left_ptr_, target, depth+1);
        return searchRec(node->right_ptr_, target, depth+1);
    }

    bool KDTree::search(const Point& pt)
    {
        return searchRec(root_, pt, 0);
    }

    void KDTree::print(const std::shared_ptr<KDNode>& node)
    {
        if(!node) return;
        node->pt_.print();
        std::cout<<"left";
        print(node->left_ptr_);
        std::cout<<"right";
        print(node->right_ptr_);
    }

    void KDTree::print()
    {
        auto curr_node = root_;
        print(curr_node);
    }

} // namespace kd_trees