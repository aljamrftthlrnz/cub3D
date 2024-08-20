#include <stdio.h>

int is_valid_map_char(char c)
{
    if(c == '1' || c == '0' || c == ' ' || c == 'N' || c == 'S' || c == 'w' || c == 'E')
        return (1); 
    return (0); 
}

int is_map_line(char *line)
{
    int i; 

    i = 0; 
    while(line[i])
    {
        if(!is_valid_map_char(line[i]))
            return (1); 
        i++; 
    }
    return(0);
}

int main()
{
    char s1[] ="100aaaaaaa0000001101010010001"; 
    char s2[] ="111111111011000001110000000000001"; 
    char s4[] ="        11111111111111111111aaa11"; 

   int res1, res2, res3, res4;
   res1 = is_map_line(s1);
   res2 = is_map_line(s2);  
   res4 = is_map_line(s4);
   printf("s1 is [%d], s2 is [%d],s4 is [%d]", res1, res2, res4); 
   return (0);  
}