//
//  Name:- Ghanshyam Savaliya
//  Student ID:- 200486455
//

#include "History.h"
#include <cassert>

History::History() { head = nullptr; }

bool History::isAtLeast1Long() const { return head != nullptr; }

bool History::isAtLeast2Long() const {
  if (head != nullptr) {
    return head->p_next != nullptr;
  }
  return false;
}

bool History::isAtLeast3Long() const {
  if (head != nullptr && head->p_next != nullptr) {
    return head->p_next->p_next != nullptr;
  }
  return false;
}

void History::addAtHead(const Board &board_in) {
  HistoryNode *node = new HistoryNode;
  node->data = board_in;
  node->p_next = head;
  head = node;
}

const Board &History::getFirst() const {
  assert(head != nullptr);
  return head->data;
}

const Board &History::getSecond() const {
  assert(head != nullptr);
  return head->p_next->data;
}

void History::removeAtHead() {
  if (head != nullptr) {
    HistoryNode *p_temp = head;
    head = head->p_next;
    delete p_temp;
  }
}

bool History::isInList(const Board &board_in) const {
  HistoryNode *p_list = head;
  while (p_list != nullptr) {
    if (p_list->data == board_in) {
      return true;
    }
    p_list = p_list->p_next;
  }
  return false;
}

void destroyLinkedList(HistoryNode *p_head_in) {
  HistoryNode *p_current = nullptr;
  HistoryNode *pNext = p_head_in;
  while (pNext != nullptr) 
  {
    p_current = pNext;
    pNext = p_current->p_next;
    delete p_current;
  }
}

History::~History(){
  destroyLinkedList(head);
}

void History::removeAll(){
  destroyLinkedList(head);
  head = nullptr;
}

HistoryNode* copyLinkedList (const HistoryNode* p_old_head_in){
  if(p_old_head_in == nullptr){
    return nullptr;
  }
  HistoryNode *p_head = new HistoryNode;
  p_head->data = p_old_head_in->data;
  
  HistoryNode *p_new = p_head;
  const HistoryNode *p_old = p_old_head_in;
  while (p_old->p_next != nullptr)  
  {
    p_new->p_next = new HistoryNode;
    p_new = p_new->p_next;
    p_old = p_old->p_next;
    p_new->data = p_old->data;
  }

  p_new->p_next = nullptr;

  return p_head;

}

History::History (const History& history_in){
  head = copyLinkedList(history_in.head);
}

History& History::operator= (const History& history_in){
  if(this != &history_in){
    destroyLinkedList(head);
    head = copyLinkedList(history_in.head);
  }
  return *this;
}