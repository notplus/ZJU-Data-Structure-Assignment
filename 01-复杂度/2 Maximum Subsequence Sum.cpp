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
    int max_sum = -1;
    int this_sum = 0;
    int step = 0;
    int step2 = 0;
    int last_index = 0;
    for (int i = 0; i < num; i++)
    {
        this_sum += arr[i];
        if (this_sum < 0)
        {
            this_sum = 0;
            step2 = 0;
        }
        else if (this_sum > max_sum)
        {
            max_sum = this_sum;
            step2++;
            last_index = i;
            step = step2;
        }
        else
        {
            step2++;
        }
    }

    if (max_sum <= 0)
    {
        if (max_sum == -1)
            std::cout << 0 << " " << arr[0] << " " << arr[num - 1];
        else
            std::cout << 0 << " " << 0 << " " << 0;
    }
    else
    {
        std::cout << max_sum << " " << arr[last_index - step + 1] << " " << arr[last_index];
    }

    return 0;
}