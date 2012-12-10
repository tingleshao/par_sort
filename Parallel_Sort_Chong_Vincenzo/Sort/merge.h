void merge(int *left, int *right, int *result, int left_size, int right_size, int total)
{

    int x = 0;
    int y = 0;
    int i = 0;
    for (i = 0; i < total; i++)
    {
       if (x == left_size || y == right_size)
       {
           break;
       }
       if (left[x] < right[y])
       {
            result[i] = left[x];
            x++;
       }
       else
       {
            result[i] = right[y];
            y++;
       }
    }
    if (x == left_size)
    {
        for (y; y < right_size; y++);
        {
            result[i] = right[y];
            i++;
        }
    }
    else {
        if ( y == right_size)
        {
            for (x; x < left_size; x++)
            {
                result[i] = left[x];
                i++;
            }
        }
         
        }
}