// Knapecz, Adam - 1DAE11
#include "LinkedList.h"

Node::Node(int value, Node* pNext)
    : value{value}
      , pNext{pNext}
{
}

LinkedList::LinkedList()
    : m_pFirstNode{nullptr}
      , m_Size{}
{
}

LinkedList::~LinkedList()
{
    while (m_pFirstNode)
    {
        PopFront();
    }
}

// Wrap the value in a new Node object and add it as first Node of the list
void LinkedList::PushFront(int value)
{
    Node* pNewNode;
    if (m_pFirstNode)
    {
        pNewNode = new Node(value, m_pFirstNode);
        m_pFirstNode = pNewNode;
    }
    else
    {
        pNewNode = new Node(value);
        m_pFirstNode = pNewNode;
    }
    ++m_Size;
}

// Remove and delete first Node
void LinkedList::PopFront()
{
    if (m_pFirstNode)
    {
        Node* pNext = m_pFirstNode->pNext;
        if (pNext)
        {
            delete m_pFirstNode;
            m_pFirstNode = pNext;
        }
        else
        {
            delete m_pFirstNode;
            m_pFirstNode = nullptr;
        }
        --m_Size;
    }
}

// Remove all Nodes having this value
void LinkedList::Remove(int value)
{
    Node *previous, *current, *next;
    previous =  next = nullptr;
    current = m_pFirstNode;
    while (current)
    {
        next = current->pNext;
        // node to delete
        if (current->value == value)
        {
            delete current;
            current = nullptr;
            if (previous == nullptr and next == nullptr)
            {
                m_pFirstNode = nullptr;
            }
            else if (previous == nullptr and next)
            {
                m_pFirstNode = next;
            }
            else if (previous and next == nullptr)
            {
                previous->pNext = nullptr;
            }
            else if (previous and next)
            {
                previous->pNext = next;
                current = previous;
            }
            --m_Size;
        }
        previous = current;
        current = next;
    }
}

// Wrap the value in a new Node object and insert it after the specified Node 
void LinkedList::InsertAfter(Node* pBefore, int value)
{
    Node* pNewNode = new Node(value);
    Node* pNext = pBefore->pNext;
    pBefore->pNext = pNewNode;
    if (pNext)
    {
        pNewNode->pNext = pNext;
    }
    ++m_Size;
}

// Return pointer to first Node
Node* LinkedList::Begin() const
{
    return m_pFirstNode;
}

// Return number of Node objects in the list
size_t LinkedList::Size() const
{
    return m_Size;
}

// Send the values of the list to the out object, use a space as element separator
std::ostream& operator<<(std::ostream& out, const LinkedList& list)
{
    const Node* pCurrentNode = list.Begin();
    while (pCurrentNode)
    {
        out << pCurrentNode->value << " ";
        pCurrentNode = pCurrentNode->pNext;
    }
    return out;
}
