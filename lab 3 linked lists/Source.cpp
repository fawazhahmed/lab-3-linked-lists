#include<iostream>
#include<fstream>
#include<string>
#include<list>

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

    // add at head: add a new element to the head position of linked list 
    // empty linked list proof. 
    // O(1)
    void addAtHead(int num) {
        // create a new node 
        NodePtr newNode = new Node(num);

        // set newNode next to current head 
        newNode->next = head;

        // update head to newNode 
        head = newNode;
    }

    // add at tail: find the tail first then append a new node 
    // O(n) as we need to find the tail node. 
    // it can be done in O(1) if you store tail node pointer. 
    void addAtTail(int num) {
        if (head == nullptr) {
            addAtHead(num);
            return;
        }

        auto iter{ head };
        while (iter && iter->next != nullptr) {
            iter = iter->next;
        }
        //now iter should point to tail node.
        iter->next = new Node(num);
    }

    void traverse() {
        NodePtr iter{ head };
        //std::cout << "start addr: " << iter << std::endl;

        while (iter != nullptr) {
            //std::cout << "addr: " << iter << std::endl;

            std::cout << iter->num << " ";
            iter = iter->next;      // V.I.S
        }
        //std::cout << "end addr: " << iter << std::endl;

        std::cout << std::endl;
    }

    // search function: to return a pointer of found node
    // return nullptr if not found 
    NodePtr search(int num) {
        NodePtr iter{ head };
        while (iter && iter->num != num) {
            iter = iter->next;
        }
        return iter;
    }

    //insert after: insert new node after given node
    //if give node is nullptr; do nothing.
    void insertAfter(NodePtr node, int num)
    {
        //verify node is good
        if (!node)return;

        //create new node 
        NodePtr newNode = new Node(num);
        newNode->next = node->next;  // set newNode's next with node->next
        node->next = newNode;
    }
    // find the node after the current 
    //assign node-> next->next to current->next
    //node must not be null ptr

    //if given node is nullptr, do nothing
    //if node is tail node, do nothing
    
    void removeAfter(NodePtr node)
    {
        if (!node) return;

        auto nodeToDel = node->next;
        if (nodeToDel == nullptr) return;

        node->next = nodeToDel->next;
        delete nodeToDel;
    }


    //delete num from LL 
    //1. LL is empty
    //2. head node to be deleted
    //3. non-head node to be deleted
    //4. cant find target

    void del(int target)
    {
        //case 1 LL is empty
        if (!head) {return;}

        //case 2 head node to be deleted
        if (head && head->num == target)
        {
            auto temp{ head };
            head = head->next;
            delete temp;
            return;
        }

        //case 3 search for target and delete
        NodePtr prev{ nullptr };
        NodePtr curr{ head };
        while (curr && curr->num != target)
        {
            prev = curr;
            curr = curr->next;
        }
        //after this while loop, it either curr is nullptr or we have match

        //case 4: no match found
        if (curr == nullptr){return;}

        //case 3 cont:found target node
        prev->next = curr->next;
        delete curr;

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


//HW 3 
//make sure file is good
// create linked list and load first number
//void readFile()
//{
//    std::ifstream file("nums.txt");
//    if (!file.is_open())
//    {
//        std::cerr << "File could not be opened. " << std::endl;
//    }
//   //need to read each line in string
//    std::string line;
//    while (std::getline(file, line))
//    {
//        std::cout << "line: " << line << std::endl;
//    }
//
//    file.close();
//}


int main()
{
   // MyLinkedList myList;

   // myList.del(10); //case 1: ll is empty

   // myList.addAtHead(10);
   // myList.addAtHead(20);
   // myList.addAtHead(30);

   // myList.addAtTail(100);
   // myList.addAtTail(200);
   // myList.addAtTail(300);

   //// // search function 
   //// /*auto ptr1 = myList.search(20);
   //// auto ptrNode20 = myList.head->next->next;
   //// std::cout << std::boolalpha << (ptr1 == ptrNode20) << std::endl;
   //// ptr1 = myList.search(500);
   //// std::cout << ptr1 << std::endl;*/


   ////// auto node300 = myList.search(300);
   ////// myList.insertAfter(node300, 25);

   //// auto targetNode = myList.search(200);
   //// myList.removeAfter(targetNode);

   // myList.del(30); //case 2: head node
   // myList.traverse();

   // myList.del(100); //case 3:found and delete
   // myList.traverse();

   // myList.del(-1); //case 4 not found
   // myList.traverse();


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
             

    Odd(list3);
    print(list3);
    
    //hw 3
    //std::ifstream file("nums.txt");
    //if (!file.is_open())
    //{
    //    std::cerr << "File could not be opened. " << std::endl;
    //}

    ////create list object
    //std::list<int> result;


    ////need to read each line in string
    //std::string line;
    //while (std::getline(file, line))
    //{
    //    //std::cout << "line: " << line << std::endl;
    //    //for (auto it = line.begin(); it != line.end(); it++)
    //    //{
    //    //    int a = *it - '0'; //off set by '0' to retrieve real digit
    //    //    //std::cout << a << "-";
    //    //}
    //    //std::cout << std::endl;

    //    //if result list is empty: load first number
    //    if (result.empty())
    //    {
    //         for (auto it = line.begin(); it != line.end(); it++)
    //         {
    //           ///int a = *it - '0'; //off set by '0' to retrieve real digit
    //            //std::cout << a << "-";
    //             result.push_front(*it - '0');
    //         }         
    //    }
    //    else  
    //    {//add new number to the list, one digit at a time
    //        int carry{ 0 };
    //        int i{ 0 };
    //        for (auto it = result.begin(); it!=result.end(); it++)
    //        {
    //            //add digit from list node to newly read digit

    //            int newDigit = line { line.size() - 1 - i } - '0'; //bug
    //            int sum = carry + *it + newDigit;

    //            //store one digit back to iterator
    //            *it = sum % 10;

    //            //update carry
    //            carry = sum / 10;
    //        }
    //    }
    //    for (auto it = result.begin(); it != result.end(); it++)
    //    {
    //        std::cout << *it;
    //    }
    //    std::cout << std::endl;
    //}

    //file.close();
   


   /* int a = 1;
    while (a < 10)
    {
        if (a == 4)
        {
            a++;
            continue;
        }
        std::cout << a << " ";
        a++;
    }*/

}