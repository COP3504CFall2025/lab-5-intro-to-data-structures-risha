#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
private:
	// Stores pointers to first and last nodes and count
	
	struct Node {
    	T data;
    	Node* prev;
    	Node* next;
	};
	Node* head;
	Node* tail;
	unsigned int count;
public:
	// Behaviors
	void printForward() const{
		for(Node* i = head; i!=nullptr; i = i->next){
        	std::cout<<i->data<<std::endl;
    	}
	}
	void printReverse() const{
		for(Node* i = tail; i!=nullptr; i = i->prev){
        	std::cout<<i->data<<std::endl;
    	}
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const{
		return count;
	}
	Node* getHead(){
		return head;
	}
	const Node* getHead() const{
		return head;
	}
	Node* getTail(){
		if(count==0){
			return nullptr;
		}
		return tail;
	}
	const Node* getTail() const{
		return tail;
	}

	// Insertion
	void addHead(const T& data){
		Node* x = new Node;
		x->prev = nullptr;
		x->data = data;
		x->next = head;
		if(head!=nullptr){
			head->prev = x;
		}
		else{
			tail = x;
		}
		head = x;
		count++;
	}
	void addTail(const T& data){
		Node* x = new Node;
		x->next = nullptr;
		x->data = data;
		x->prev = tail;
		if(tail!=nullptr){
			tail->next =x;
		}
		else{
			head = x;
		}
		tail = x;
		count++;
	}

	// Removal
	bool removeHead(){
		if(!head){
			return false;
		}
		if(head->next){
			head = head->next;
			delete head->prev;
			head->prev = nullptr;
		}
		else{
			delete head;
			head = nullptr;
		}
		count--;
		return true;
	}
	bool removeTail(){
		if(!tail){
			return false;
		}
		if(tail->prev){
			tail = tail->prev;
			delete tail->next;
			tail->next = nullptr;
		}
		else{
			delete tail;
			tail = nullptr;
		}
		count--;
		return true;

	}
	void clear(){
		int x = count;
		for(int i = 0; i<x; i++){
			removeHead();
		}
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept{
		if (this == &other){
			return *this;
		}
		clear();
		head = other.head;
		tail = other.tail;
		count = other.count;
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
		return *this;
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs){
		if(this==&rhs){
			return *this;
		}
		clear();
		for(Node* i = rhs.head; i!=nullptr; i = i->next){
			addTail(i->data);
		}
		return *this;
	}

	// Construction/Destruction
	LinkedList(): head(nullptr), tail(nullptr), count(0){}
	LinkedList(const LinkedList<T>& list){
		for(Node* i = list.head; i!=nullptr; i = i->next){
			addTail(i->data);
		}
	}
	LinkedList(LinkedList<T>&& other) noexcept{
		head = other.head;
		tail = other.tail;
		count = other.count;
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}
	~LinkedList(){
		clear();
	}


};