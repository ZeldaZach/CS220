unsigned int my_strncpy(char *src, char *dst, unsigned int num_bytes)
{
    int i = 0;
    
    for (i = 0; ; i++)
    {
        dst[i] = '\0';
        if (src[i] == '\0')
            break;
    }
    
    for (i = 0; i < num_bytes; i++)
    {
        if (i == num_bytes || src[i] == '\0')
            break;
        
        dst[i] = src[i];
    }
    return i;
}

void swap_temp(int *num1, int *num2)
{
    int *tmp = *num1;
    *num1 = *num2;
    *num2 = tmp;
}

void swap_notemp(int *num1, int *num2)
{
    *num1 ^= *num2;
    *num2 ^= *num1;
    *num1 ^= *num2;
}