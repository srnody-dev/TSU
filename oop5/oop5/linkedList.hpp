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
    void addAtPosition(uint32_t position, const ItemType& value);
    void addAfterKey(const ItemType& key, const ItemType& value);

    void removeFromHead();
    void removeFromTail();
    void removeAtPosition(uint32_t position);
    void removeByKey(const ItemType& key);
    void swap(LinkedList<ItemType>& other);
    
    ItemType* find(const ItemType& key);
    const ItemType* find(const ItemType& key) const;
    ItemType& findMax();
    const ItemType& findMax() const;
    ItemType& findMin();
    const ItemType& findMin() const;

private:
    ListNode *headPtr_ = nullptr;
    ListNode *tailPtr_ = nullptr;
    uint32_t size_ = 0;
    ListNode* getNodeAt(uint32_t position) const;
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
void LinkedList<ItemType>::addAtPosition(uint32_t position, const ItemType& value)
{
    if (position == 0)
    {
        addToHead(value);
    }
    else if (position >= size_)
    {
        addToTail(value);
    }
    else
    {
        ListNode* current = getNodeAt(position);
        ListNode* newNode = new ListNode(value, current, current->getLinkToPrevNode());
        
        current->getLinkToPrevNode()->setLinkToNextNode(newNode);
        current->setLinkToPrevNode(newNode);
        
        ++size_;
    }
}

template<typename ItemType>
void LinkedList<ItemType>::addAfterKey(const ItemType& key, const ItemType& value)
{
    ListNode* current = headPtr_;
    while (current != nullptr)
    {
        if (current->getValue() == key)
        {
            ListNode* newNode = new ListNode(value, current->getLinkToNextNode(), current);
            
            if (current->getLinkToNextNode())
            {
                current->getLinkToNextNode()->setLinkToPrevNode(newNode);
            }
            else
            {
                tailPtr_ = newNode;
            }
            
            current->setLinkToNextNode(newNode);
            ++size_;
            return;
        }
        current = current->getLinkToNextNode();
    }
    addToTail(value);
}

template<typename ItemType>
void LinkedList<ItemType>::removeAtPosition(uint32_t position)
{
    if (position >= size_) return;

    if (position == 0)
    {
        removeFromHead();
    }
    else if (position == size_ - 1)
    {
        removeFromTail();
    }
    else
    {
        ListNode* current = getNodeAt(position);
        current->getLinkToPrevNode()->setLinkToNextNode(current->getLinkToNextNode());
        current->getLinkToNextNode()->setLinkToPrevNode(current->getLinkToPrevNode());
        delete current;
        --size_;
    }
}

template<typename ItemType>
void LinkedList<ItemType>::removeByKey(const ItemType& key)
{
    ListNode* current = headPtr_;
    uint32_t position = 0;
    
    while (current != nullptr)
    {
        if (current->getValue() == key)
        {
            removeAtPosition(position);
            return;
        }
        current = current->getLinkToNextNode();
        ++position;
    }
}

template<typename ItemType>
ItemType* LinkedList<ItemType>::find(const ItemType& key)
{
    ListNode* current = headPtr_;
    while (current != nullptr)
    {
        if (current->getValue() == key)
        {
            return &(current->getValue());
        }
        current = current->getLinkToNextNode();
    }
    return nullptr;
}

template<typename ItemType>
const ItemType* LinkedList<ItemType>::find(const ItemType& key) const
{
    const ListNode* current = headPtr_;
    while (current != nullptr)
    {
        if (current->getValue() == key)
        {
            return &(current->getValue());
        }
        current = current->getLinkToNextNode();
    }
    return nullptr;
}

template<typename ItemType>
ItemType& LinkedList<ItemType>::findMax()
{
    if (isEmpty()) throw std::runtime_error("List is empty");

    ListNode* current = headPtr_;
    ListNode* maxNode = headPtr_;
    
    while (current != nullptr)
    {
        if (current->getValue() > maxNode->getValue())
        {
            maxNode = current;
        }
        current = current->getLinkToNextNode();
    }
    
    return maxNode->getValue();
}

template<typename ItemType>
const ItemType& LinkedList<ItemType>::findMax() const
{
    if (isEmpty()) throw std::runtime_error("List is empty");

    const ListNode* current = headPtr_;
    const ListNode* maxNode = headPtr_;
    
    while (current != nullptr)
    {
        if (current->getValue() > maxNode->getValue())
        {
            maxNode = current;
        }
        current = current->getLinkToNextNode();
    }
    
    return maxNode->getValue();
}
template<typename ItemType>
ItemType& LinkedList<ItemType>::findMin()
{
    if (isEmpty()) throw std::runtime_error("List is empty");

    ListNode* current = headPtr_;
    ListNode* minNode = headPtr_;
    
    while (current != nullptr)
    {
        if (current->getValue() < minNode->getValue())
        {
            minNode = current;
        }
        current = current->getLinkToNextNode();
    }
    
    return minNode->getValue();
}

template<typename ItemType>
const ItemType& LinkedList<ItemType>::findMin() const
{
    if (isEmpty()) throw std::runtime_error("List is empty");

    const ListNode* current = headPtr_;
    const ListNode* minNode = headPtr_;
    
    while (current != nullptr)
    {
        if (current->getValue() < minNode->getValue())
        {
            minNode = current;
        }
        current = current->getLinkToNextNode();
    }
    
    return minNode->getValue();
}

template<typename ItemType>
void LinkedList<ItemType>::swap(LinkedList<ItemType>& other)
{
    ListNode* tempHead = headPtr_;
    headPtr_ = other.headPtr_;
    other.headPtr_ = tempHead;
        
    ListNode* tempTail = tailPtr_;
    tailPtr_ = other.tailPtr_;
    other.tailPtr_ = tempTail;
        
    uint32_t tempSize = size_;
    size_ = other.size_;
    other.size_ = tempSize;
}


template<typename ItemType>
typename LinkedList<ItemType>::ListNode* LinkedList<ItemType>::getNodeAt(uint32_t position) const
{
    if (position >= size_) return nullptr;

    ListNode* current = headPtr_;
    for (uint32_t i = 0; i < position; ++i)
    {
        current = current->getLinkToNextNode();
    }
    return current;
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
