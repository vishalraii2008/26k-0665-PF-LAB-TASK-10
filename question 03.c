#include <stdio.h>

int main()
{
    FILE *fp;
    int i, n;
    char name[11], hotName[11];
    float temp, hotTemp = -1000;

    fp = fopen("temperature.txt", "wb");
    if (fp == NULL)
    {
        printf("Could not create file\n");
        return 1;
    }
    for (i = 1; i <= 5; i++)
    {
        printf("City %d name: ", i);
        scanf("%10s", name);
        printf("City %d temperature: ", i);
        scanf("%f", &temp);
        fprintf(fp, "%-10s %5.1f\n", name, temp);
    }
    fclose(fp);

    fp = fopen("temperature.txt", "rb+");
    if (fp == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    printf("City number: ");
    scanf("%d", &n);
    if (n < 1 || n > 5)
    {
        printf("No such city\n");
        fclose(fp);
        return 1;
    }
    fseek(fp, (n - 1) * 17, SEEK_SET);
    fscanf(fp, "%s %f", name, &temp);
    printf("%s %.1f\n", name, temp);

    printf("City number to correct: ");
    scanf("%d", &n);
    printf("New temperature: ");
    scanf("%f", &temp);
    if (n < 1 || n > 5)
    {
        printf("No such city\n");
        fclose(fp);
        return 1;
    }
    fseek(fp, (n - 1) * 17, SEEK_SET);
    fscanf(fp, "%s %*f", name);
    fseek(fp, (n - 1) * 17, SEEK_SET);
    fprintf(fp, "%-10s %5.1f\n", name, temp);
    printf("%s updated to %.1f\n", name, temp);

    rewind(fp);
    for (i = 0; i < 5; i++)
    {
        fscanf(fp, "%s %f", name, &temp);
        if (temp > hotTemp)
        {
            hotTemp = temp;
            sprintf(hotName, "%s", name);
        }
    }
    printf("Hottest city: %s (%.1f)\n", hotName, hotTemp);

    fclose(fp);
    return 0;
}
