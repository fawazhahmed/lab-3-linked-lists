//test
#include<iostream>

struct Node {
    int num{};
    Node* next{};
    Node() = delete;
    Node(int number) : num{ number }, next{ nullptr } {}
};
using NodePtr = Node*;
struct MyLinkedList {
    NodePtr head{ nullptr };
    MyLinkedList() = default;

    void traverse() {
        NodePtr iter{ head };
        //std::cout << "start addr: " << iter << std::endl;

        while (iter != nullptr) {
            //std::cout << "addr: " << iter << std::endl;

            std::cout << iter->num << " ";
            iter = iter->next;      // V.I.S
        }
    }

};

// lab 2 question 1: merging two sorted lits
NodePtr mergeLists(NodePtr list1, NodePtr list2) {
    NodePtr result{ nullptr }; //set it to null first

    // check if any list is empty
    if (list1 == nullptr) {
        // copy from list2 and return copied list
        auto iter{ result };
        while (list2) { //while list is good
            if (result == nullptr) {
                result = new Node(list2->num); //set it to the next number
                iter = result;
                list2 = list2->next;   //keep moving through
                continue;
            }

            iter->next = new Node(list2->num); //do this if first condition is not met
            iter = iter->next;
            list2 = list2->next;
        }
        return result; //return whatever 
    }

    // TODO the symmetric for list2 is nullptr; 

    // both lists are not empty 
    auto it1{ list1 }, it2{ list2 }, itResult{ result };
    while (it1 && it2) {                        //while both lists are not done       
        if (it1->num < it2->num) {
            if (result == nullptr) {
                result = new Node(it1->num); //set it to this if that
                itResult = result;
            }
            else {
                itResult->next = new Node(it1->num); //do this if not
                itResult = itResult->next;
            }
            it1 = it1->next; //keep looping through
        }
        else {
            // symmetric for adding value from list2 
            if (result == nullptr)
            {
                result = new Node(it2->num); //do this stuff if it is true
                itResult = result;
            }
            else
            {
                itResult->next = new Node(it2->num);
                itResult = itResult->next;
            }
            it2 = it2->next; //keep going 

        }
    }

    // dump rest node from unfinished list
    if (it1 != nullptr) {
        // list2 is done. Need to process unfinihsed list2
        while (it1 != nullptr) {
            itResult->next = new Node(it1->num);
            itResult = itResult->next; //keep going through list
            it1 = it1->next;
        }
    }
    else {
        while (it1) { //if empty
            itResult->next = new Node(it1->num);
            itResult = itResult->next;
            it1 = it1->next; //push these values
        }
        while (it2)
        {
            itResult->next = new Node(it2->num); //or this
            itResult = itResult->next;
            it2 = it2->next;
        }
    }



    return result;
}

Node* Odd(Node* head)
{

    Node* even_b = NULL;
    Node* even_e = NULL;
    Node* odd_b = NULL;
    Node* odd_e = NULL; //set all of them to do this at first

    while (head != nullptr) //while list is not empty
    {
        if (head->num % 2 == 0) //check evens
        {
            if (even_b == NULL) //if it is empty go to next number
            {
                even_b = head;
                even_e = head;
                head = head->next;
            }
            else //or do this
            {
                even_e->next = head;
                even_e = head;
                head = head->next;
            }
        }
        else
        {
            if (odd_b == NULL)
            {
                odd_b = head;
                odd_e = head;
                head = head->next;
            }
            else //odds
            {
                odd_e->next = head;
                odd_e = head;
                head = head->next; //do this stuff
            }

        }
    }
    if (even_e != NULL)
    {
        even_e->next = NULL;  //move through the stuff
    }
    else
    {
        odd_e->next = NULL;
        return odd_b; //if null just return it 
    }
    if (odd_e != NULL)
    {
        odd_e->next = even_b;
        return odd_b; //same thing but odd
    }
    else
    {
        return even_b;
    }
}

void print(Node* head)
{
    Node* temp = head;
    while (temp != NULL)
    {
        std::cout << temp->num << " ";
        temp = temp->next; //loop through list and print it accordingly
    }
}

int main()
{
    //for lab 3: question 1
    NodePtr list1 = new Node(1);
    list1->next = new Node(3);
    list1->next->next = new Node(5);
    list1->next->next->next = new Node(7);
    // list1->next->next->next->next = new Node(200);


    NodePtr list2 = new Node(2);
    list2->next = new Node(4);
    list2->next->next = new Node(6);
    list2->next->next->next = new Node(8);
    // list2->next->next->next->next = new Node(99);

    auto merged = mergeLists(list1, list2);

    MyLinkedList q2{};
    q2.head = merged;
    q2.traverse();

    NodePtr list3 = new Node(1);
    list3->next = new Node(2);
    list3->next->next = new Node(5);
    list3->next->next->next = new Node(8);
    list3->next->next->next->next = new Node(3);
    list3->next->next->next->next->next = new Node(6);
    list3->next->next->next->next->next->next = new Node(7);
    list3->next->next->next->next->next->next->next = new Node(4);
    std::cout << std::endl;

    Odd(list3);
    print(list3);


    return 0;
}