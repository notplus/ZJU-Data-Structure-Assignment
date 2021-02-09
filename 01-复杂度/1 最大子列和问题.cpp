#include <iostream>

int main()
{
    int num = 0;
    std::cin >> num;
    int *arr = new int[num];
    for (int i = 0; i < num; i++)
    {
        std::cin >> arr[i];
    }
    int max_sum = arr[0];
    int this_sum = 0;
    for (int i = 0; i < num; i++)
    {
        this_sum += arr[i];
        if (this_sum > max_sum)
            max_sum = this_sum;
        else if (this_sum < 0)
            this_sum = 0;
    }

    if (max_sum < 0)
        std::cout << 0;
    else
        std::cout << max_sum;

    return 0;
}