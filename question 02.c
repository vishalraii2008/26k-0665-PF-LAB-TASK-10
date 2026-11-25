#include <stdio.h>

int main()
{
    FILE *fp;
    int roll, no, attended, extra;
    char name[16];
    float percent;

    fp = fopen("attendance.txt", "wb");
    if (fp == NULL)
    {
        printf("Could not create file\n");
        return 1;
    }
    fprintf(fp, "%-3d %-15s %3d\n", 1, "Ayesha", 18);
    fprintf(fp, "%-3d %-15s %3d\n", 2, "Bilal", 14);
    fprintf(fp, "%-3d %-15s %3d\n", 3, "Hamza", 20);
    fprintf(fp, "%-3d %-15s %3d\n", 4, "Sana", 12);
    fprintf(fp, "%-3d %-15s %3d\n", 5, "Zainab", 16);
    fclose(fp);

    fp = fopen("attendance.txt", "rb+");
    if (fp == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    printf("Roll number: ");
    scanf("%d", &roll);
    if (roll < 1 || roll > 5)
    {
        printf("No such student\n");
        fclose(fp);
        return 1;
    }
    fseek(fp, (roll - 1) * 24, SEEK_SET);
    fscanf(fp, "%d %s %d", &no, name, &attended);
    percent = attended * 100.0 / 20;
    printf("%s: %d / 20 (%.1f%%)", name, attended, percent);
    if (percent < 75)
        printf(" Short attendance");
    printf("\n");

    printf("Roll number for leave: ");
    scanf("%d", &roll);
    printf("Lectures: ");
    scanf("%d", &extra);
    if (roll < 1 || roll > 5)
    {
        printf("No such student\n");
        fclose(fp);
        return 1;
    }
    fseek(fp, (roll - 1) * 24, SEEK_SET);
    fscanf(fp, "%d %s %d", &no, name, &attended);
    attended = attended + extra;
    if (attended > 20)
        attended = 20;
    fseek(fp, (roll - 1) * 24, SEEK_SET);
    fprintf(fp, "%-3d %-15s %3d\n", no, name, attended);
    percent = attended * 100.0 / 20;
    printf("%s: now %d / 20 (%.1f%%)\n", name, attended, percent);

    fseek(fp, -24, SEEK_END);
    fscanf(fp, "%d %s %d", &no, name, &attended);
    printf("Last record: %d %s %d\n", no, name, attended);

    fclose(fp);
    return 0;
}
