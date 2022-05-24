#include "OrgChart.hpp"
#include <iostream>


namespace ariel{
    OrgChart::OrgChart(){
        this->root = NULL;
        this->size = 0;
    }
    ///////////////////////  cheak  /////////////////////////////////////////////
    OrgChart::OrgChart(const OrgChart& other){
        this->root = other.root;
        this->size = other.size;
    }
    pnode createNode(std::string s){
        pnode newNode = new node();
        newNode->data = std::move(s);
        newNode->children = {}; 
        newNode->next = NULL;
        newNode->prev = NULL;
        newNode->visit = false;
        return newNode;
    }
    // add the head of the chart
    OrgChart& OrgChart::add_root(const std::string &s){
        if (s.length() <1 || s == "/t" || s == "/r" || s == "/n"){
            throw std::invalid_argument("cant enter empty string");
        }        
        if(this->root != NULL){
            this->root->data = s;
        }
        else{
            pnode head = createNode(s);
            this->root = head;
            this->size += 1;
        }    
        return *this;
    }
    // add new node to the chart. the new node must work with bos in the chart already
    OrgChart& OrgChart::add_sub(const std::string& s1, const std::string& s2){
        if (this->getSize() == 0){
            throw std::runtime_error("cant add sub before root");
        }
        // check is string is empty
        if (s1.length() <1 || s1 == "/t" || s1 == "/r" || s1 == "/n"){
            throw std::invalid_argument("cant enter empty string");
        }
        if(s2.length() < 1 || s2 == "/t" || s2 == "/r" || s2 == "/n" ){
            throw std::invalid_argument("cant enter empty string");
        }
        // serch the bos in the chart and enter the sub
        std::list<pnode> p;
        p.push_back(this->getRoot());
        while(!(p.empty())){
            pnode tmp = p.front();
            p.pop_front();
            if(tmp->data == s1){
                pnode newOved = createNode(s2);
                tmp->children.push_back(newOved);
                size += 1;
                return *this;
            }
            // continue to search s1
            for (size_t i=0; i<tmp->children.size(); i++){
                p.push_back(tmp->children.at(i));
            }
        }
        throw std::runtime_error("no exist oved s1");
    }
    OrgChart& OrgChart::operator=(const OrgChart& other){
        OrgChart chart = OrgChart(other);
        return *this;

    }
    // OrgChart& OrgChart::operator=(OrgChart&& other) noexcept{

    // }
    // operator out
    std::ostream& operator<<(std::ostream& os, const OrgChart& orgChart){
        std::list<pnode> p;
        if((orgChart.root == NULL)){
            throw std::runtime_error("orgChart is empty");
        }
        p.push_back(orgChart.root);
        while(!(p.empty())){
            for (size_t i=0; i<p.size(); i++){
                pnode tmp = p.front();
                p.pop_front();
                os << tmp->data << " ";
                if (!(tmp->children.empty())){
                    for (size_t i=0; i<tmp->children.size(); i++){
                        p.push_back(tmp->children.at(i));
                    }
                }
            }
            os << std::endl;
        }
        return os;
    }
    OrgChart::myIterator::myIterator(const myIterator& other){
        this->queue = other.queue;
        this->curr = other.curr;
        this->current = other.current;
    }
    // constractor
    OrgChart::myIterator::myIterator(OrgChart& head, const char& c, bool sORe){
        if (c == 'A'){
            this->BFS(head.getRoot());
            if (sORe){
                this->current = 0;
                this->curr = this->queue.front();
            }
            else{
                this->current = queue.size()-1;
                this->curr = this->queue.at(current);
            }
        }
        else if (c == 'B'){
            this->reverse(head.getRoot());
            if (sORe){
                this->current = 0;
                this->curr = this->queue.front();
            }
            else{
                this->current = this->queue.size()-1;
                this->curr = this->queue.at(current);
            }
        }
        else if (c == 'C'){
            this->DFS(head.getRoot());
            this->queue.push_back(nullptr);
            if (sORe){
                this->current = 0;
                this->curr = head.getRoot();
            }
            else{
                this->current = this->queue.size()-1;
                this->curr = this->queue.at(current);
            }
        }
        // else{
        //     char x = c;
        // }
    }
    // for level order. using BFS algo
    void OrgChart::myIterator::BFS(pnode root){;
        std::list<pnode>p;
        p.push_back(root);
        while(!(p.empty())){
            pnode temp = p.front();
            p.pop_front();
            this->queue.push_back(temp);
            for (size_t i = 0; i < temp->children.size(); i++){
                    p.push_back(temp->children.at(i));
            }
        }
        this->queue.push_back(nullptr); // nullptr
    }
    // order the reverse base on BFS algo
    void OrgChart::myIterator::reverse(pnode root){
        std::list<pnode>p;
        std::stack<pnode>s;
        p.push_back(root);
        while(!(p.empty())){
            pnode temp = p.front();
            p.pop_front();
            s.push(temp);
            int tempSize = temp->children.size();
            for (int i = (tempSize-1); i >= 0; i--){
                    p.push_back(temp->children.at((size_t)i));
            }
        }
        while(!(s.empty())){
            pnode temp = s.top();
            s.pop();
            this->queue.push_back(temp);
        }
        this->queue.push_back(nullptr); // nullptr
    }
    // order the pre order with DFS algo
    void OrgChart::myIterator::DFS(pnode root){
        this->queue.push_back(root);
        // size_t size = ;
        for(size_t i=0; i < root->children.size(); i++){
            OrgChart::myIterator::DFS(root->children.at((size_t)i));
        }
    }
    bool OrgChart::myIterator::operator!=(const myIterator& other)const {
        return (this->curr != other.curr);
    }
    bool OrgChart::myIterator::operator==(const myIterator& other)const {
        return (this->curr == other.curr);
    }
    OrgChart::myIterator& OrgChart::myIterator::operator++(){
        this->queue.erase(this->queue.begin());
        this->curr = this->queue.front();
        return *this; 
    }
    std::string operator*(const OrgChart::myIterator& other) {
        return other.curr->data;
    }
    std::string* OrgChart::myIterator::operator->()const{
        // Iterator* pre = new Iterator(*this);
        // return &pre->queue_pre.at(0)->data;
        return &(this->curr->data);
    }
    // std::string OrgChart::myIterator::operator->()const{
    //     // Iterator* pre = new Iterator(*this);
    //     // return &pre->queue_pre.at(0)->data;
    //     return (this->curr->data);
    // }

    // int OrgChart::myIterator::size(){
    //     // return (*this)->curr->data.length();
    //     return 
    // }
    // first item in level order
    OrgChart::myIterator OrgChart::begin_level_order(){
        if (getSize() == 0){
            throw std::runtime_error("tree is empty");
        }
        return OrgChart::myIterator(*this, 'A', true);
    }
    // last item in level order
    OrgChart::myIterator OrgChart::end_level_order(){
        if (getSize() == 0){
            throw std::runtime_error("tree is empty");
        }
        return OrgChart::myIterator(*this, 'A', false);
    }
    // first item in reverse order
    OrgChart::myIterator OrgChart::begin_reverse_order(){
        if (getSize() == 0){
            throw std::runtime_error("tree is empty");
        }
        return OrgChart::myIterator(*this, 'B', true);
    }
    // last item in reverse order
    OrgChart::myIterator OrgChart::reverse_order(){
        if (getSize() == 0){
            throw std::runtime_error("tree is empty");
        }
        return OrgChart::myIterator(*this, 'B', false);
    }
    // first order in pre order
    OrgChart::myIterator OrgChart::begin_preorder(){
        if (getSize() == 0){
            throw std::runtime_error("tree is empty");
        }
        return OrgChart::myIterator(*this, 'C', true);
    }
    // last item in pre order
    OrgChart::myIterator OrgChart::end_preorder(){
        if (getSize() == 0){
            throw std::runtime_error("tree is empty");
        }
        return OrgChart::myIterator(*this, 'C', false);
    }
    // first item
    OrgChart::myIterator OrgChart::begin(){
        if (getSize() == 0){
            throw std::runtime_error("tree is empty");
        }
        return this->begin_level_order();
    }
    // last item 
    OrgChart::myIterator OrgChart::end(){
        if (getSize() == 0){
            throw std::runtime_error("tree is empty");
        }
        return this->end_level_order();
    }    
    

}    