/**
 * You should implement your solution in this file and submit it to gradescope.
 */

#ifndef __BANK_FUNDRAISER_H__
#define __BANK_FUNDRAISER_H__
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
namespace ICS45C {
namespace BankFundraiser {

template <typename T>
struct RankedNode {
  std::string name;
  T value;
  struct RankedNode* next;
};

template <typename T>
class FundraiserRank {
 private:
  const std::string name;
  RankedNode<T>* head;
  RankedNode<T>* tail;
  bool ascending;

 public:
  FundraiserRank(std::string name);                  // Constructor
  FundraiserRank(std::string name, bool ascending);  // Constructor
  ~FundraiserRank();
  bool isAscending();
  bool isEmpty();
  unsigned int length();
  unsigned int add(std::string name, T value);
  bool exists(T value);
  RankedNode<T>* find(std::string name);
  RankedNode<T>* get(int pos);
  void reverse();
  bool remove(std::string name);
  std::string printTop(unsigned int N);
  RankedNode<T>* operator[](int pos);
  void operator+(T value);
};

template <typename T>
FundraiserRank<T>::FundraiserRank(std::string name)
    : name(name), head(nullptr), tail(nullptr), ascending(true) {}

template <typename T>
FundraiserRank<T>::FundraiserRank(std::string name, bool ascending)
    : name(name), head(nullptr), tail(nullptr), ascending(ascending) {}

template <typename T>
FundraiserRank<T>::~FundraiserRank() {
  while (head) {
    tail = head->next;
    delete head;
    head = tail;
  }
  head = tail = nullptr;
}
template <typename T>
bool FundraiserRank<T>::isAscending() {
  if (ascending == true) {
    return true;
  } else {
    return false;
  }
}

template <typename T>
unsigned int FundraiserRank<T>::add(std::string name, T value) {
  unsigned int index = 0;
  RankedNode<T>* newNode = new RankedNode<T>;  // Create new node
  RankedNode<T>* temp = head;
  RankedNode<T>* current = head;
  newNode->value = value;
  newNode->name = name;
  if (temp == nullptr) {
    head = tail = newNode;
    tail->next = nullptr;
    return index;
  }
  while (temp->next == nullptr) {
    if (isAscending() == false) {
      if (newNode->value < temp->value) {  // tail
        tail->next = newNode;
        tail = newNode;
        tail->next = nullptr;
        index++;
        return index;
      }
      if (newNode->value >= temp->value) {  // head
        newNode->next = head;               // points to old head.
        head = newNode;
        return index;
      }
    } else {
      if (newNode->value > temp->value) {  // tail
        tail->next = newNode;
        tail = newNode;
        tail->next = nullptr;
        index++;
        return index;
      }
      if (newNode->value <= temp->value) {  // head
        newNode->next = head;               // points to old head.
        head = newNode;
        return index;
      }
    }
  }
  while (temp->next != nullptr) {
    if (isAscending() == false) {  // descending
      if (newNode->value >= temp->value &&
          index == 0) {  // if value of new node equals head node value
        newNode->next = head;
        head = newNode;
        return index;
      } else if ((newNode->value <= temp->value &&
                  newNode->value >= temp->next->value) &&
                 (index == 0)) {
        current = temp->next;
        temp->next = newNode;
        newNode->next = current;
        index++;
        return index;
      } else if ((newNode->value <= temp->value) &&
                 (newNode->value >= temp->next->value) &&
                 (temp->next != nullptr)) {
        current = temp->next;
        temp->next = newNode;
        newNode->next = current;
        index++;
        return index;
      } else {
        temp = temp->next;
        index++;
      }
    } else {  // Ascending
      if ((newNode->value <= temp->value) && (index == 0)) {
        newNode->next = head;
        head = newNode;
        return index;
      } else if ((newNode->value >= temp->value) &&
                 (newNode->value <= temp->next->value) && (index == 0)) {
        current = temp->next;
        temp->next = newNode;
        newNode->next = current;
        index++;
        return index;
      } else if ((newNode->value >= temp->value) &&
                 (newNode->value <= temp->next->value) &&
                 (temp->next != nullptr)) {
        current = temp->next;
        temp->next = newNode;
        newNode->next = current;
        index++;
        return index;
      } else {
        temp = temp->next;
        index++;
      }
    }
  }
  if (temp->next == nullptr) {
    tail->next = newNode;
    tail = newNode;
    tail->next = nullptr;
    index++;
    return index;
  }
  return index;
}
template <typename T>
bool FundraiserRank<T>::isEmpty() {
  if (head == nullptr) {
    return true;
  } else {
    return false;
  }
}
template <typename T>
unsigned int FundraiserRank<T>::length() {
  unsigned int length = 0;
  RankedNode<T>* temp = head;
  while (temp != nullptr) {
    length++;
    temp = temp->next;
  }
  return length;
}
template <typename T>
bool FundraiserRank<T>::exists(T value) {
  RankedNode<T>* temp = head;
  while (temp != nullptr) {
    if (temp->value == value) {
      return true;
    }
    temp = temp->next;
  }
  return false;
}
template <typename T>
RankedNode<T>* FundraiserRank<T>::find(std::string name) {
  RankedNode<T>* temp = head;
  while (temp != nullptr) {
    if (temp->name == name) {
      return temp;
    }
    temp = temp->next;
  }
  return nullptr;
}
template <typename T>
RankedNode<T>* FundraiserRank<T>::get(int pos) {
  RankedNode<T>* temp = head;
  RankedNode<T>* temp1 = head;
  int count = 0;
  unsigned int length = 0;
  while (temp != nullptr) {
    length++;  // count length of node
    temp = temp->next;
  }
  while (temp1 != nullptr) {
    if (pos >= 0) {
      if (count == pos) {
        return temp1;
      }
    }
    temp1 = temp1->next;
    count++;
  }
  return nullptr;
}
template <typename T>
bool FundraiserRank<T>::remove(std::string name) {
  RankedNode<T>* temp = head;
  RankedNode<T>* prev = NULL;
  if (temp != NULL && temp->name == name) {
    head = temp->next;
    delete temp;
    return true;
  } else {
    while (temp != nullptr && temp->name != name) {
      prev = temp;
      temp = temp->next;
    }
    if (temp == NULL) {
      return false;
    }
    prev->next = temp->next;
    delete temp;
    return true;
  }
  return false;
}
template <typename T>
void FundraiserRank<T>::reverse() {
  ascending = !ascending;
  RankedNode<T>* current = head;
  RankedNode<T>* next = NULL;
  RankedNode<T>* prev = NULL;
  while (current != NULL) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  head = prev;
}
template <typename T>
std::string FundraiserRank<T>::printTop(unsigned int N) {
  RankedNode<T>* temp = head;
  unsigned int count = 1;
  std::stringstream output;
  if (temp == nullptr) {
    output << "\n";
    return output.str();
  }
  while (temp != nullptr) {
    if (N == 0) {
      output << "\n";
    } else if (N > 0) {
      if (count < N) {
        if (count == 1) {
          output << temp->name << " (" << std::fixed << std::setprecision(2)
                 << temp->value << ")"
                 << " ->";
        } else {
          if (temp->next != nullptr) {
            output << " " << temp->name << " (" << std::fixed
                   << std::setprecision(2) << temp->value << ")"
                   << " ->";
          } else {
            output << " " << temp->name << " (" << std::fixed
                   << std::setprecision(2) << temp->value << ")"
                   << " -> \n";
          }
        }
      } else if (count == N) {
        output << " " << temp->name << " (" << std::fixed
               << std::setprecision(2) << temp->value << ")"
               << " -> \n";
      }
      count++;
    }
    temp = temp->next;
  }
  return output.str();
}
template <typename T>
RankedNode<T>* FundraiserRank<T>::operator[](int pos) {
  RankedNode<T>* t = head;
  int nNode = length();
  int index = 0;
  if (t == nullptr) {
    return nullptr;
  }
  while (t != nullptr) {
    if (pos >= 0) {
      if (index == pos) {
        return t;
      }
    } else {
      pos = pos % nNode;
      if (index == pos) {
        return t;
      }
    }
    t = t->next;
  }
  return t;
}

template <typename T>
void FundraiserRank<T>::operator+(T value) {
  RankedNode<T>* temp = head;
  if (temp == nullptr) {
    return;
  }
  while (temp != nullptr) {
    temp->value += value;
    temp = temp->next;
  }
  return;
}
}  // namespace BankFundraiser
}  // namespace ICS45C

#endif  // __BANK_FUNDRAISER_H__