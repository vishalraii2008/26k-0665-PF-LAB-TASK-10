#include <stdio.h>
#include <string.h>

int countRepeat(char s[], int i)
{
    if (s[i + 1] == s[i])
        return 1 + countRepeat(s, i + 1);
    return 1;
}

void compress(char s[], int i, char out[], int j)
{
    int n;
    if (s[i] == '\0')
    {
        out[j] = '\0';
        return;
    }
    n = countRepeat(s, i);
    out[j] = s[i];
    out[j + 1] = '0' + n;
    compress(s, i + n, out, j + 2);
}

void expand(char in[], int i, char out[], int j)
{
    int n, k;
    if (in[i] == '\0')
    {
        out[j] = '\0';
        return;
    }
    n = in[i + 1] - '0';
    for (k = 0; k < n; k++)
        out[j + k] = in[i];
    expand(in, i + 2, out, j + n);
}

int main()
{
    char original[100], compressed[200], expanded[100];

    printf("Enter a string: ");
    scanf("%99s", original);

    compress(original, 0, compressed, 0);
    expand(compressed, 0, expanded, 0);

    printf("Original:   %s\n", original);
    printf("Compressed: %s\n", compressed);
    printf("Expanded:   %s\n", expanded);
    if (strcmp(original, expanded) == 0)
        printf("Match: Yes\n");
    else
        printf("Match: No\n");

    return 0;
}
