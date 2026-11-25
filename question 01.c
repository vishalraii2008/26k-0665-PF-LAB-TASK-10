#include <stdio.h>

int main()
{
    FILE *fp;
    int itemNo, qty, no, stock;
    char name[21];
    float price, total = 0;

    fp = fopen("items.txt", "wb");
    if (fp == NULL)
    {
        printf("Could not create file\n");
        return 1;
    }
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 1, "Rice", 250.00, 40);
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 2, "Sugar", 160.00, 25);
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 3, "Milk", 220.00, 30);
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 4, "CookingOil", 560.00, 12);
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 5, "Tea", 450.00, 18);
    fclose(fp);

    fp = fopen("items.txt", "rb+");
    if (fp == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    while (1)
    {
        printf("Item no: ");
        scanf("%d", &itemNo);
        if (itemNo == 0)
            break;
        if (itemNo < 1 || itemNo > 5)
        {
            printf("No such item\n");
            continue;
        }
        printf("Quantity: ");
        scanf("%d", &qty);

        fseek(fp, (itemNo - 1) * 42, SEEK_SET);
        fscanf(fp, "%d %s %f %d", &no, name, &price, &stock);

        if (qty <= stock)
        {
            printf("%-10s %3d x %.2f = %.2f\n", name, qty, price, qty * price);
            total = total + qty * price;
            stock = stock - qty;
            fseek(fp, (itemNo - 1) * 42, SEEK_SET);
            fprintf(fp, "%-4d %-20s %9.2f %5d\n", no, name, price, stock);
        }
        else
        {
            printf("Only %d %s in stock\n", stock, name);
        }
    }

    printf("Total bill: %.2f\n", total);
    fclose(fp);
    return 0;
}
