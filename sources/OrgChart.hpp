#include<string>
#include <iostream>
#include <queue>
#include <list>
#include <vector>
#include <stack>

namespace ariel{
    typedef struct Node{
        std::string data;
        std::vector<Node*> children;
        Node* next;
        Node* prev;
        bool visit;
    }node, *pnode; 
    pnode createNode(std::string str);   
    class OrgChart{ 
    private:
        //std::string* node;
        pnode root;
        int size;
    public:
        OrgChart();
        OrgChart(const OrgChart& other); 
        ~OrgChart(){};
        pnode getRoot(){return this->root;}
        int getSize() const {return this->size;}
        OrgChart& add_root(const std::string& str); 
        OrgChart& add_sub(const std::string& s1, const std::string& s2); 
        OrgChart& operator=(const OrgChart& other);
        OrgChart& operator=(OrgChart&& other)noexcept;
        friend std::ostream& operator<<(std::ostream& os, const OrgChart& orgChart);
        
        class myIterator{
        private:
            // std::vector<pnode> queue_lev;
            // std::vector<pnode> queue_rev;
            // std::vector<pnode> queue_pre;
            std::vector<pnode> queue;
            pnode curr;
            size_t current;
        public:
            myIterator(OrgChart& head, const char& c, bool sORe);
            ~myIterator(){};
            myIterator(const myIterator& other);
            void BFS(pnode root); // fill the levek order queue
            void DFS(pnode root);
            void reverse(pnode root);
            bool operator!=(const myIterator& other) const;
            bool operator==(const myIterator& other) const;
            myIterator& operator++();
            friend std::string operator*(const myIterator& other);
            std::string* operator->() const;
            int size();
            // std::vector<pnode> getQueue(){return this->queue;}
            pnode getCurr(){return this->curr;} 
            
            myIterator &operator=(myIterator const &other) = default;
            myIterator &operator=(myIterator &&other) = default;
            myIterator(myIterator&) = default;
            myIterator(myIterator&&) = default;   
        };
        OrgChart::myIterator begin_level_order();
        OrgChart::myIterator end_level_order();
        OrgChart::myIterator begin_reverse_order();
        OrgChart::myIterator reverse_order();
        OrgChart::myIterator begin_preorder();
        OrgChart::myIterator end_preorder();
        OrgChart::myIterator begin();
        OrgChart::myIterator end();

        //OrgChart &operator=(OrgChart const &other) = default;
        //OrgChart &operator=(OrgChart &&other) = default;
        OrgChart(OrgChart&) = default;
        OrgChart(OrgChart&&) = default;
    };

}     