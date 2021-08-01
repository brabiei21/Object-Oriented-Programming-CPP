#ifndef linkedlist_h
#define linkedlist_h

namespace ECE17
{

  struct Node
  {
      int value;
      Node *next;
      static size_t nodeCount;

      explicit Node ( Node *nextVal = NULL)
      {
          //value =  val;
          next = nextVal;
      };

      ~Node() = default;

      void * operator new(size_t size)
      {
          nodeCount++;
          return ::new Node;
      }

      void operator delete(void * aNode)
      {
          nodeCount--;
          free(aNode);  //it's ok to call free _inside_ the delete method...
      }
  };

        
  class LinkedList
          {
  public:

      //You'll add OCF Methods here...
      LinkedList(Node *rootNew = nullptr, int newValue = 0)
      {
          root = rootNew;
          if (root != nullptr)
          {
              root->value = newValue;
              root->next = nullptr;
          }
      };
      LinkedList(LinkedList &aList)
      {
          Node* newNode = new Node;

          newNode->value = aList.root->value;
          newNode->next = aList.root->next;
          root = newNode;

          Node* theirNode = aList.root->next;
          newNode = root->next;

          while ( theirNode != nullptr)
          {
              newNode->value = theirNode->value;
              newNode = newNode -> next;
              theirNode = theirNode->next;
          }
          delete newNode;
      }



      ~LinkedList()
      {
          Node * temp;

          while(root != nullptr)
          {
              temp = root;
              root = root->next;
              delete temp;
          }
          delete root;

      }; // delete all pointers made


      Node*   first() const
      {
          return root;
      };  //retrieve first node in the list.

      size_t  size()
      {
          int counter = 0;
          Node *current = root;
          if (root == nullptr)
              return 0;
          if (root->next == nullptr)
              return 1;

          while(current != nullptr)
          {
              counter ++;
              current = current->next;
          }
         return counter;
      }//return # of items in the list...

      Node*   find(const int &aValue, Node *anOrigin=nullptr)
      {
          if (anOrigin ==nullptr)
          {
              Node *current = root;
              if(root == nullptr)
                  return root;
              if(root->value == aValue)
              {
                return root;
              }
              else
              {
                  while (current != nullptr)
                  {
                      if(current->value == aValue)
                          return current;

                          current = current->next;
                  }
                  return nullptr;
              }
          }
          else
          {
              Node *current = anOrigin;
              if(anOrigin == nullptr)
                  return nullptr;
              if(anOrigin->value == aValue)
              {
                  return anOrigin;
              }
              else
              {
                  while (current != nullptr)
                  {
                      if(current->value == aValue)
                          return current;

                          current = current->next;
                  }
                  return nullptr;
              }
          }
      };

      Node*   append(const int &aValue)
      {
          Node * current = root;
          Node* add = new Node;
          add->value = aValue;
          add->next = nullptr;
          if(root == nullptr)
          {
              root = add;
              return root;
          }

          while(current->next != nullptr)
              current = current->next;

          current->next = add;

          return add;

      };
      Node*   insertAfter(const int &aValue, Node *anOrigin=nullptr)
      {
          Node *add = new Node;
          add->value = aValue;
          if (anOrigin == nullptr)
          {
              if(root == nullptr)
              {
                  add->next= nullptr;
                  root = add;
                  return add;
              }
              add->next = root;
              root = add;
              return root;
          }

          if(anOrigin->next == nullptr)
          {
              anOrigin->next = add;
              add->next = nullptr;
              return add;
          }

          Node *temp = new Node;
          temp->next = anOrigin->next;
          anOrigin->next = add;
          add->next = temp->next;
          delete temp;
          return add;

      };
      Node*   remove(const int &aValue)
      {
          Node *lookingFor = find(aValue);

          if(lookingFor == nullptr)
          {
              return lookingFor;
          }

          if(lookingFor == root)
          {
              root = root->next;
              return lookingFor;
          }

          int counter = 0;
          Node *trail = root;
          Node *location = root;


          while (location != nullptr)
          {
              if(location->value == aValue)
              break;
              location = location->next;
              counter++;
          }
          if(location == nullptr)
              return nullptr;

          for(int i = 0; i < counter -1; i++)
          {
              trail= trail->next;
          }
          trail->next = location->next;
          return location;
      };


  protected:
        Node    *root;
  };
    size_t Node::nodeCount = 0; //initialize static member...

}

#endif /* linkedlist_h */

