#include <iostream>
struct dummyStruct;
template<typename T>
class Red_Black_Tree{

    struct Node
    {
        Node() : pTParent(nullptr),pTLeftChild(nullptr),pTRightChild(nullptr),isBlack(true){}

        T pTData;
        Node* pTParent;
        Node* pTLeftChild;
        Node* pTRightChild;
        bool isBlack;

    private:
        bool operator<(const Node& firstNode)
        {
            return pTData < firstNode.pTData;
        }

        bool operator>(const Node& firstNode)
        {
            return pTData < firstNode.pTData;
        }
    };

    uint32_t TreeSize;
    Node* root;

public:
    Red_Black_Tree(): root(nullptr),TreeSize(0){}
    ~Red_Black_Tree(){delete root;}

    void add(const T& a_TData)
    {
        Node* node = new Node;
        node->pTData = a_TData;
        node->isBlack = false;
        node->pTParent = nullptr;
        node->pTLeftChild = nullptr;
        node->pTRightChild = nullptr;

        Node* treeNode = nullptr;
        Node* iteratorNode = root;

        while(iteratorNode != nullptr)
        {
            treeNode = iteratorNode;
            if(node->pTData == iteratorNode->pTData)
            {
                std::cout << " Element already in" << std::endl;
                break;
            }
            if(node->pTData < iteratorNode->pTData)
                iteratorNode = iteratorNode->pTLeftChild;
            else
                iteratorNode = iteratorNode->pTRightChild;
        }

        node->pTParent = treeNode;
        if(nullptr == treeNode)
        {
            root = node;
            root->isBlack = true;
            return;
        }
        else if(node->pTData < treeNode->pTData)
            treeNode->pTLeftChild = node;

        else if(node->pTData > treeNode->pTData)
            treeNode->pTRightChild = node;

        if(nullptr == node->pTParent->pTParent)
            return;

        fixTree(node);
    }

    void printTree()
    {
        if (root)
        {
            printHelper(root, "", true);
        }
    }

    T* findElement(T& check)
    {
        bool find = false;
        Node* tmp = root;

        while(!find)
        {
            if(tmp->pTData > check)
            {
                tmp = tmp->pTLeftChild;
            }
            else if(tmp->pTData < check)
            {
                tmp = tmp->pTRightChild;
            }

            if(tmp->pTData == check)
                find = true;
        }
        return &tmp->pTData;
    }

    void clear()
    {
        clearReq(root);
    }

    int getHigh()
    {
        return getHighReq(root);
    }

    void preOrder()
    {
        preOrderReq(root);
    }

    void inOrder()
    {
        inOrderReq(root);
    }


private:
    void fixTree(Node* node)
    {
        while(!node->pTParent->isBlack)
        {
            if(node->pTParent == node->pTParent->pTParent->pTLeftChild)
            {
                /*CASE I*/
                if(nullptr != node->pTParent->pTParent->pTRightChild && !node->pTParent->pTParent->pTRightChild->isBlack)
                {
                    node->pTParent->pTParent->pTLeftChild->isBlack = true;
                    node->pTParent->pTParent->pTRightChild->isBlack = true;
                    node->pTParent->pTParent->isBlack = false;

                    node = node->pTParent->pTParent;
                }
                    /*CASE II*/
                else
                {
                    if(node == node->pTParent->pTRightChild)
                    {
                        node = node->pTParent;
                        leftRotate(node);
                    }
                    /*CASE III*/
                    node->pTParent->isBlack = true;
                    node->pTParent->pTParent->isBlack = false;
                    rightRotate(node->pTParent->pTParent);
                }
            }
            else
            {
                if(nullptr != node->pTParent->pTParent->pTLeftChild && !node->pTParent->pTParent->pTLeftChild->isBlack)
                {
                    node->pTParent->pTParent->pTLeftChild->isBlack = true;
                    node->pTParent->pTParent->pTRightChild->isBlack = true;
                    node->pTParent->pTParent->isBlack = false;

                    node = node->pTParent->pTParent;
                }
                else
                {
                    if(node == node->pTParent->pTLeftChild)
                    {
                        node = node->pTParent;
                        rightRotate(node);
                    }
                    node->pTParent->isBlack = true;
                    node->pTParent->pTParent->isBlack = false;
                    leftRotate(node->pTParent->pTParent);
                }
            }
            if(nullptr != root)
                root->isBlack = true;

            if(nullptr == node->pTParent)
                break;
        }
    }

    void leftRotate(Node* parent)
    {
        Node* rightChild = parent->pTRightChild;

        parent->pTRightChild = rightChild->pTLeftChild;

        if(nullptr != rightChild->pTLeftChild)
        {
            rightChild->pTLeftChild->pTParent = parent;
        }

        rightChild->pTParent = parent->pTParent;

        if(nullptr == parent->pTParent)
        {
            root = rightChild;
        }
        else if(parent == parent->pTParent->pTLeftChild)
        {
            parent->pTParent->pTLeftChild = rightChild;
        }
        else
        {
            parent->pTParent->pTRightChild = rightChild;
        }
        rightChild->pTLeftChild = parent;
        parent->pTParent = rightChild;
    }

    void rightRotate(Node* parent)
    {
        Node* leftChild = parent->pTLeftChild;

        parent->pTLeftChild = leftChild->pTRightChild;

        if(nullptr != leftChild->pTRightChild)
        {
            leftChild->pTRightChild->pTParent = parent;
        }

        leftChild->pTParent = parent->pTParent;
        leftChild->pTParent = parent->pTParent;

        if(nullptr == parent->pTParent)
        {
            root = leftChild;
        }
        else if(parent == parent->pTParent->pTRightChild)
        {
            parent->pTParent->pTRightChild = leftChild;
        }
        else
        {
            parent->pTParent->pTLeftChild = leftChild;
        }
        leftChild->pTRightChild = parent;
        parent->pTParent = leftChild;
    }

    void printHelper(Node* root, std::string indent, bool isRight)
    {
        if (root != nullptr)
        {
            std::cout << indent;
            if(isRight)
            {
                if(root->pTParent == nullptr)
                    std::cout << "ROOT: ";
                else
                    std::cout << "R----";
                indent += "   ";
            }
            else
            {
                std::cout << "L----";
                indent += "|  ";
            }

            std::string sColor = root->isBlack ? "BLACK" : "RED";
            std::cout << root->pTData << "(" << sColor << ")" << std::endl;
            printHelper(root->pTLeftChild, indent, false);
            printHelper(root->pTRightChild, indent, true);
        }
    }

    void clearReq(Node* node)
    {
        if(nullptr != node)
        {
            clearReq(node->pTLeftChild);
            clearReq(node->pTRightChild);

            if(nullptr != node->pTParent)
            {
                delete node;
                node = nullptr;
            }
            if(root == node)
            {
                delete root;
                root = nullptr;
            }
        }
    }

    int getHighReq(Node* node)
    {
        int left = 0;
        int right = 0;
        if(nullptr != node)
        {
            right = getHighReq(node->pTRightChild);
            left  = getHighReq(node->pTLeftChild);

            return (right < left ? left : right) + 1;
        }
        return 0;
    }

    void preOrderReq(Node* node)
    {
        if(nullptr != node)
        {
            std::cout << "PRE-ORDER:  " << node->pTData << std::endl;
            preOrderReq(node->pTLeftChild);
            preOrderReq(node->pTRightChild);
        }
    }

    void inOrderReq(Node* node)
    {
        if(nullptr != node)
        {
            inOrderReq(node->pTLeftChild);
            std::cout << "IN-ORDER:  " << node->pTData << std::endl;
            inOrderReq(node->pTRightChild);
        }
    }
public:
    T& get_root_data()
    {
        return root->pTData;
    }
};


struct dummyStruct
{
    int      x;
    char     y;

    bool operator<(const dummyStruct& firstNode)
    {
        if(firstNode.x == x)
            return y < firstNode.y;
        else
            return x < firstNode.x;
    }

    bool operator>(const dummyStruct& firstNode)
    {
        if(firstNode.x == x)
            return y > firstNode.y;
        else
            return x > firstNode.x;
    }

    bool operator==(const dummyStruct& node)
    {
        return node.x == x && node.y ==y;
    }

};

std::ostream& operator<<(std::ostream& os, dummyStruct s)
{
    os << s.x;
    return os;
}

void myTests()
{
    dummyStruct one = {10,'A'};
    dummyStruct two = {6,'B'};
    dummyStruct three = {3,'C'};
    dummyStruct a = {5,'A'};
    dummyStruct done = {5,'A'};
    dummyStruct s = {12,'C'};
    dummyStruct x = {15,'A'};
    dummyStruct p = {100,'A'};
    dummyStruct o = {150,'A'};
    dummyStruct i = {1,'A'};
    dummyStruct u = {9,'A'};
    dummyStruct last = {14,'A'};

    Red_Black_Tree<dummyStruct> tree;
    tree.add(one);
    tree.add(two);
    tree.add(three);
    tree.add(x);
    tree.add(s);
    tree.add(a);
    tree.add(p);
    tree.add(i);
    tree.add(o);
    tree.add(u);
    tree.add(last);

    auto* check = tree.findElement(done);
    if(nullptr != check)
    {
        std::cout << "Element found : ";
        std::cout << check->x;
        std::cout << " " <<check->y << std::endl;
    }
    else
    {
        std::cout << "Element not found" << std::endl;
    }




    std::cout << tree.getHigh() << std::endl;
    tree.printTree();
//    tree.preOrder();
//    tree.inOrder();
//    tree.clear();
//    tree.printTree();
}

#include <map>
#include <vector>
#include <numeric>
#include <algorithm>
void test()
{
    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 0);
    std::map<int, int> heights, root_data;
    do
    {
        Red_Black_Tree<int> t;
        for (int i : v)
        {
            t.add(i);
//            t.printTree();
        }
        int check = t.getHigh();
        ++heights[t.getHigh()];
        ++root_data[t.get_root_data()];
    } while (std::next_permutation(v.begin(), v.end()));
    for (auto [height, cnt] : heights)
        std::cout << height << ": " << cnt << std::endl;
    std::cout << "***" << std::endl;
    for (auto [data, cnt] : root_data)
        std::cout << data << ": " << cnt << std::endl;
}

#include "math.h"
#include <random>
int main ()
{
    test();
    return 0;

    const int MAX_ORDER = 7;
    clock_t start,end;
    Red_Black_Tree<dummyStruct> tree;

    std::random_device rd;
    std::mt19937 gen(time(nullptr));
    std::uniform_int_distribution<> distr(65, 90);
    std::uniform_int_distribution<> DISTaa(0, 100);

    for (int i = 0; i < MAX_ORDER; ++i)
    {
        const int n = pow(10,i);
        for (int j = 0; j < n; ++j) {
            start = clock();
            char pp = distr(gen);
            int randomINT = DISTaa(gen);
            dummyStruct so = {randomINT,pp};
            tree.add(so);
            end = clock() - start;
            float val = (float)end/ CLOCKS_PER_SEC;
            //std::cout << "Add time: " << val << std::endl;
        }
    }

    tree.printTree();

    return 0;
}
