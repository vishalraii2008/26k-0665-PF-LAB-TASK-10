#include <stdio.h>

int main()
{
    FILE *fp;
    char category[13], other[13];
    float amount, total = 0;
    int entry, count;

    fp = fopen("expenses.txt", "wb");
    if (fp == NULL)
    {
        printf("Could not create file\n");
        return 1;
    }
    fprintf(fp, "%-12s %9.2f\n", "Food", 1200.00);
    fprintf(fp, "%-12s %9.2f\n", "Transport", 500.00);
    fprintf(fp, "%-12s %9.2f\n", "Books", 850.00);
    fprintf(fp, "%-12s %9.2f\n", "Mobile", 300.00);
    fclose(fp);

    printf("Category: ");
    scanf("%12s", category);
    printf("Amount: ");
    scanf("%f", &amount);

    fp = fopen("expenses.txt", "ab");
    if (fp == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }
    fprintf(fp, "%-12s %9.2f\n", category, amount);
    fclose(fp);

    fp = fopen("expenses.txt", "rb+");
    if (fp == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    fseek(fp, -2 * 23, SEEK_END);
    fscanf(fp, "%s %f", category, &amount);
    fscanf(fp, "%s %f", other, &total);
    printf("Latest two: %s %.2f, %s %.2f\n", category, amount, other, total);

    fseek(fp, 0, SEEK_END);
    count = ftell(fp) / 23;

    printf("Entry to fix: ");
    scanf("%d", &entry);
    printf("Correct amount: ");
    scanf("%f", &amount);
    if (entry < 1 || entry > count)
    {
        printf("No such entry\n");
        fclose(fp);
        return 1;
    }
    fseek(fp, (entry - 1) * 23, SEEK_SET);
    fscanf(fp, "%s %*f", category);
    fseek(fp, (entry - 1) * 23, SEEK_SET);
    fprintf(fp, "%-12s %9.2f\n", category, amount);

    total = 0;
    rewind(fp);
    while (fscanf(fp, "%s %f", category, &amount) == 2)
    {
        printf("%s %.2f\n", category, amount);
        total = total + amount;
    }
    printf("Total: %.2f\n", total);

    fclose(fp);
    return 0;
}
