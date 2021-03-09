BinTree Insert(BinTree BST, ElementType X)
{
    if (!BST)
    {
        BST = (BinTree)malloc(sizeof(struct TNode));
        BST->Left = BST->Right = NULL;
        BST->Data = X;
    }
    else
    {
        if (X < BST->Data)
            BST->Left = Insert(BST->Left, X);
        else if (X > BST->Data)
            BST->Right = Insert(BST->Right, X);
    }
    return BST;
}

BinTree Delete(BinTree BST, ElementType X)
{
    Position tmp;
    if (!BST)
        printf("Not Found\n");
    else if (X < BST->Data)
        BST->Left = Delete(BST->Left, X);
    else if (X > BST->Data)
        BST->Right = Delete(BST->Right, X);
    else
    {
        if (BST->Left && BST->Right)
        {
            tmp = FindMin(BST->Right);
            BST->Data = tmp->Data;
            BST->Right = Delete(BST->Right, tmp->Data);
        }
        else
        {
            tmp = BST;
            if (!BST->Left)
                BST = BST->Right;
            else if (!BST->Right)
                BST = BST->Left;
            free(tmp);
        }
    }
    return BST;
}

Position Find(BinTree BST, ElementType X)
{
    while (BST)
    {
        if (X < BST->Data)
            BST = BST->Left;
        else if (X > BST->Data)
            BST = BST->Right;
        else
            return BST;
    }
    return NULL;
}

Position FindMin(BinTree BST)
{
    if (BST)
        while (BST->Left)
            BST = BST->Left;
    return BST;
}

Position FindMax(BinTree BST)
{
    if (BST)
        while (BST->Right)
            BST = BST->Right;
    return BST;
}