/**
 * @file main.cpp
 * @author notplus (notplus@163.com)
 * @brief 
 * @version 0.1
 * @date 2021-02-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>

struct Node
{
    int coep;
    int expon;
    Node *next;
};

Node *readPoly();
Node *polyAdd(Node *p1, Node *p2);
Node *polyMul(Node *p1, Node *p2);
void attach(Node *p1, Node *p2);
void printPoly(Node *poly);
void clearPoly(Node *poly);

int main()
{
    Node *p1 = readPoly();
    Node *p2 = readPoly();
    printPoly(polyMul(p1, p2));
    printPoly(polyAdd(p1, p2));
    return 0;
}

/**
 * @brief 
 * 
 * @return Node* 
 */
Node *readPoly()
{
    int n;
    std::cin >> n;
    Node *res = new Node();
    Node *p = res;
    for (int i = 0; i < n; i++)
    {
        Node *tmp = new Node();
        int coep, expon;
        std::cin >> coep >> expon;
        tmp->coep = coep;
        tmp->expon = expon;
        p->next = tmp;
        p = tmp;
    }
    return res;
}

Node *polyAdd(Node *p1, Node *p2)
{
    Node *res = new Node();
    p1 = p1->next;
    p2 = p2->next;
    Node *p = res;
    while (p1 && p2)
    {
        if (p1->expon > p2->expon)
        {
            Node *tmp = new Node();
            tmp->coep = p1->coep;
            tmp->expon = p1->expon;
            p->next = tmp;
            p = tmp;
            p1 = p1->next;
        }
        else if (p1->expon < p2->expon)
        {
            Node *tmp = new Node();
            tmp->coep = p2->coep;
            tmp->expon = p2->expon;
            p->next = tmp;
            p = tmp;
            p2 = p2->next;
        }
        else
        {
            if ((p1->coep + p2->coep) != 0)
            {
                Node *tmp = new Node();
                tmp->coep = p1->coep + p2->coep;
                tmp->expon = p1->expon;
                p->next = tmp;
                p = tmp;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    if (p1)
        attach(p, p1);
    if (p2)
        attach(p, p2);
    if (res->next==NULL)
    {
        res->next=new Node();
        res->next->coep=0;
        res->next->expon=0;
    }
    return res;
}

Node *polyMul(Node *p1, Node *p2)
{
    p1 = p1->next;
    Node *single_mul_res = new Node();
    Node *previous_result = new Node();

    while (p1)
    {
        Node *p2p = p2->next;
        Node *single_mul_res_p = single_mul_res;
        while (p2p)
        {
            Node *temp = new Node();
            temp->coep = p1->coep * p2p->coep;
            temp->expon = p1->expon + p2p->expon;
            single_mul_res_p->next = temp;
            single_mul_res_p = temp;
            p2p = p2p->next;
        }
        previous_result = polyAdd(previous_result, single_mul_res);
        clearPoly(single_mul_res);
        p1 = p1->next;
    }
    if (previous_result->next==NULL)
    {
        previous_result->next=new Node();
        previous_result->next->coep=0;
        previous_result->next->expon=0;
    }
    return previous_result;
}

void attach(Node *p1, Node *p2)
{
    while (p2)
    {
        Node *tmp = new Node();
        tmp->coep = p2->coep;
        tmp->expon = p2->expon;
        p1->next = tmp;
        p1 = tmp;
        p2 = p2->next;
    }
}

void printPoly(Node *poly)
{
    poly = poly->next;
    while (poly->next)
    {
        std::cout << poly->coep << " " << poly->expon << " ";
        poly = poly->next;
    }
    std::cout << poly->coep << " " << poly->expon << std::endl;
}

void clearPoly(Node *poly)
{
    while (true)
    {
        Node *p = poly->next;
        if (!poly->next)
        {
            poly = p->next;
            delete p;
        }
        else
        {
            delete p;
            break;
        }
    }
}