//
//  linkedList.hpp
//  oop5
//
//  Created by srnody on 18.11.2025.
//

#pragma once

#include <iostream>
#include <stdint.h>

template<typename ItemType>
class LinkedList
{
private:
    class ListNode;

public:
    LinkedList() = default;
    ~LinkedList();

    uint32_t getSize() const;
    bool isEmpty() const;
    void clear();

    void addToHead(const ItemType& value);
    void addToTail(const ItemType& value);

    void removeFromHead();
    void removeFromTail();

private:
    ListNode *headPtr_ = nullptr;
    ListNode *tailPtr_ = nullptr;
    uint32_t size_ = 0;
};

template<typename ItemType>
class LinkedList<ItemType>::ListNode
{
public:
    ListNode(ItemType value = ItemType(), ListNode* linkToNextNode = nullptr, ListNode* linkToPrevNode = nullptr);

    ItemType& getValue();
    const ItemType& getValue() const;

    ListNode* getLinkToNextNode();
    const ListNode* getLinkToNextNode() const;
    ListNode* getLinkToPrevNode();
    const ListNode* getLinkToPrevNode() const;

    void setLinkToNextNode(ListNode* newLink);
    void setLinkToPrevNode(ListNode* newLink);

private:
    ItemType value_;
    ListNode *linkToNextNode_;
    ListNode *linkToPrevNode_;
};


template<typename ItemType>
LinkedList<ItemType>::~LinkedList()
{
    clear();
}

template<typename ItemType>
uint32_t LinkedList<ItemType>::getSize() const
{
    return size_;
}

template<typename ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
    return size_ == 0;
}

template<typename ItemType>
void LinkedList<ItemType>::clear()
{
    while (!isEmpty())
    {
        removeFromHead();
    }
}

template<typename ItemType>
void LinkedList<ItemType>::addToHead(const ItemType& value)
{
    ListNode *newNode = new ListNode(value, headPtr_);

    if (headPtr_)
    {
        headPtr_->setLinkToPrevNode(newNode);
    }

    headPtr_ = newNode;

    if (!tailPtr_)
    {
        tailPtr_ = newNode;
    }

    ++size_;
}

template<typename ItemType>
void LinkedList<ItemType>::addToTail(const ItemType& value)
{
    ListNode *newNode = new ListNode(value, nullptr, tailPtr_);

    if (tailPtr_)
    {
        tailPtr_->setLinkToNextNode(newNode);
    }

    tailPtr_ = newNode;

    if (!headPtr_)
    {
        headPtr_ = newNode;
    }

    ++size_;
}

template<typename ItemType>
void LinkedList<ItemType>::removeFromHead()
{
    if (!headPtr_) return;

    ListNode* temp = headPtr_;
    headPtr_ = headPtr_->getLinkToNextNode();
    
    if (headPtr_)
    {
        headPtr_->setLinkToPrevNode(nullptr);
    }
    else
    {
        tailPtr_ = nullptr;
    }
    
    delete temp;
    --size_;
}

template<typename ItemType>
void LinkedList<ItemType>::removeFromTail()
{
    if (!tailPtr_) return;

    ListNode* temp = tailPtr_;
    tailPtr_ = tailPtr_->getLinkToPrevNode();
    
    if (tailPtr_)
    {
        tailPtr_->setLinkToNextNode(nullptr);
    }
    else
    {
        headPtr_ = nullptr;
    }
    
    delete temp;
    --size_;
}


template<typename ItemType>
LinkedList<ItemType>::ListNode::ListNode(ItemType value, ListNode* linkToNextNode, ListNode* linkToPrevNode) :
    value_(value), linkToNextNode_(linkToNextNode), linkToPrevNode_(linkToPrevNode) {}

template<typename ItemType>
ItemType& LinkedList<ItemType>::ListNode::getValue() { return value_; }

template<typename ItemType>
const ItemType& LinkedList<ItemType>::ListNode::getValue() const { return value_; }

template<typename ItemType>
typename LinkedList<ItemType>::ListNode* LinkedList<ItemType>::ListNode::getLinkToNextNode() { return linkToNextNode_; }

template<typename ItemType>
const typename LinkedList<ItemType>::ListNode* LinkedList<ItemType>::ListNode::getLinkToNextNode() const { return linkToNextNode_; }

template<typename ItemType>
typename LinkedList<ItemType>::ListNode* LinkedList<ItemType>::ListNode::getLinkToPrevNode() { return linkToPrevNode_;}

template<typename ItemType>
const typename LinkedList<ItemType>::ListNode* LinkedList<ItemType>::ListNode::getLinkToPrevNode() const { return linkToPrevNode_;}

template<typename ItemType>
void LinkedList<ItemType>::ListNode::setLinkToNextNode(ListNode* newLink) { linkToNextNode_ = newLink; }

template<typename ItemType>
void LinkedList<ItemType>::ListNode::setLinkToPrevNode(ListNode* newLink)  { linkToPrevNode_ = newLink; }
