#pragma once
#include <map>

const int INF = 10e6;

template <typename T>
class BinominalHeap;

//Class for implementation heap node
template <typename T>
class Node 
{
private:
    Node* parent;
    Node* sibling;
    Node* child;
    T     value;
    int   degree{};
public:
    //Constructors
    Node() : parent(nullptr), sibling(nullptr), child(nullptr), value({}), degree(0) {};

    explicit Node(T newValue) : Node() 
    {
        value = newValue;
    }

    //Conection between nodes
    void Link(Node* other) 
    {
        this->parent = other;
        this->sibling = other->child;
        other->child = this;
        other->degree++;
    }

    //Outputing heap in console
    void Print(int countTabs) const
    {
        for (int i = 0; i < countTabs; i++)
            std::cout << '\t';
        std::cout << "Value: " << value << "; Degree: " << degree;
        if (child != nullptr)
        {
            std::cout << std::endl;
            child->Print(countTabs + 1);
        }
        if (sibling != nullptr) {
            std::cout << std::endl;
            sibling->Print(countTabs);
        }
        std::cout << std::endl;
    }

    friend std::ostream& operator<< (std::ostream& out, const Node& node) 
    {
        out << node.value;
        return out;
    }

    friend BinominalHeap<T>;
};

//Class for implementation binominal heap
template <typename T>
class BinominalHeap {
private:
    Node<T>* head;

    //Function for merging 2 heaps
    void Merge(BinominalHeap<T>* first, BinominalHeap<T>* second)
    {
        if (first->head == nullptr)
        {
            head = second->head;
            return;
        }
        if (second->head == nullptr)
        {
            head = first->head;
            return;
        }

        Node<T>* firstTemp = first->head,
            * secondTemp = second->head;

        if (firstTemp->degree <= secondTemp->degree)
        {
            head = firstTemp;
            firstTemp = firstTemp->sibling;
        }
        else
        {
            head = secondTemp;
            secondTemp = secondTemp->sibling;
        }

        Node<T>* temp = head;

        while (firstTemp != nullptr && secondTemp != nullptr)
        {
            if (firstTemp->degree < secondTemp->degree)
            {
                temp->sibling = firstTemp;
                temp = temp->sibling;
                firstTemp = firstTemp->sibling;
            }
            else
            {
                temp->sibling = secondTemp;
                temp = temp->sibling;
                secondTemp = secondTemp->sibling;
            }
        }

        while (firstTemp != nullptr)
        {
            temp->sibling = firstTemp;
            temp = temp->sibling;
            firstTemp = firstTemp->sibling;
        }

        while (secondTemp != nullptr)
        {
            temp->sibling = secondTemp;
            temp = temp->sibling;
            secondTemp = secondTemp->sibling;
        }
    }

    //Function for union 2 heaps
    void UnionHeaps(BinominalHeap<T>* first, BinominalHeap<T>* second)
    {
        Merge(first, second);
        if (head == nullptr)
            return;
        Node<T>* prevX = nullptr,
            * X = head,
            * nextX = X->sibling;
        while (nextX != nullptr)
        {
            if (X->degree != nextX->degree || (nextX->sibling != nullptr && nextX->sibling->degree == X->degree))
            {
                prevX = X;
                X = nextX;
            }
            else if (X->value <= nextX->value)
            {
                X->sibling = nextX->sibling;
                nextX->Link(X);
            }
            else
            {
                if (prevX == nullptr)
                    head = nextX;
                else
                    prevX->sibling = nextX;
                X->Link(nextX);
                X = nextX;
            }
            nextX = X->sibling;
        }
    }

    //Function for finding the smallest node
    [[nodiscard]] Node<T>* MinNode() const
    {
        Node<T>* minimal = head;
        Node<T>* temp = head->sibling;

        while (temp != nullptr)
        {
            if (temp->value < minimal->value)
                minimal = temp;
            temp = temp->sibling;
        }
        return minimal;
    }

    [[nodiscard]] Node<T>* PrevMinNode() const
    {
        Node<T>* tempPrev = head;
        Node<T>* prev = nullptr;
        Node<T>* minimal = head;
        Node<T>* temp = head->sibling;

        while (temp != nullptr)
        {
            if (temp->value < minimal->value)
            {
                prev = tempPrev;
                minimal = temp;
            }

            tempPrev = tempPrev != nullptr ? tempPrev->sibling : head;
            temp = temp->sibling;
        }

        return prev;
    }
public:
    //Constructors
    BinominalHeap() : head(nullptr) {};

    explicit BinominalHeap(T newValue) 
    {
        head = new Node<T>(newValue);
    }

    //Destructor
    ~BinominalHeap() = default;

    //Function for outputing heap
    void Print() const 
    {
        head->Print(0);
    }
    
    //Insertion new element
    void Insert(const T& value) 
    {
        auto tree = new BinominalHeap<T>(value);
        UnionHeaps(this, tree);
        delete tree;
    }

    //Function for deletion the smallest element from heap
    void ExtractMin() 
    {
        if (head == nullptr)
            return;
        Node<T>* min = MinNode();
        Node<T>* prevMin = PrevMinNode();

        if (prevMin != nullptr) 
            prevMin->sibling = min->sibling;
        else head = min->sibling;

        if (min->child == nullptr)
            return;

        Node<T>* first = nullptr,
            * second = min->child,
            * third = second->sibling;
        while (second != nullptr) 
        {
            second->parent = nullptr;
            second->sibling = first;

            first = second;
            second = third;
            third = third == nullptr ? nullptr : third->sibling;
        }

        BinominalHeap<T> tree;
        tree.head = first;
        UnionHeaps(this, &tree);
        delete min;
    }

    //Function for decreasing key
    void DecreaseKey(Node<T>* node, T newValue) 
    {
        if (newValue > node->value)
        {
            std::cout << "New value is more than old one\n";
            return;
        }
        node->value = newValue;

        Node<T>* temp = node,
            * parent = node->parent;

        while (parent != nullptr && parent->value > temp->value)
        {
            T tempValue = parent->value;
            parent->value = temp->value;
            temp->value = tempValue;

            temp = parent;
            parent = parent->parent;
        }
    }

    //Function for deletion any node
    void Erase(Node<T>* node)
    {
        DecreaseKey(node, -INF);
        ExtractMin();
    }
};
