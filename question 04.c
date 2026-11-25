#include <stdio.h>
#include <string.h>

int main()
{
    FILE *fp;
    int choice, room, nights, no, stay, i, found;
    char status, name[21], guest[21];
    float rate;
    char guests[10][21];
    int rooms[10];

    fp = fopen("hotel.txt", "wb");
    if (fp == NULL)
    {
        printf("Could not create file\n");
        return 1;
    }
    for (room = 101; room <= 110; room++)
        fprintf(fp, "%3d %c %-20s %2d %8.2f\n", room, 'F', "-", 0, 8000.00);
    fclose(fp);

    fp = fopen("hotel.txt", "rb+");
    if (fp == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    while (1)
    {
        printf("\n1. Check-in\n2. Search guest\n3. Check-out\n4. Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("Check-in room: ");
            scanf("%d", &room);
            if (room < 101 || room > 110)
            {
                printf("No such room\n");
                continue;
            }
            printf("Name: ");
            scanf("%20s", guest);
            printf("Nights: ");
            scanf("%d", &nights);

            fseek(fp, (room - 101) * 39, SEEK_SET);
            fscanf(fp, "%d %c %s %d %f", &no, &status, name, &stay, &rate);
            if (status == 'F')
            {
                fseek(fp, (room - 101) * 39, SEEK_SET);
                fprintf(fp, "%3d %c %-20s %2d %8.2f\n", room, 'B', guest, nights, rate);
                printf("Room %d booked\n", room);
            }
            else
            {
                printf("Room already booked\n");
            }
        }
        else if (choice == 2)
        {
            printf("Search name: ");
            scanf("%20s", guest);

            rewind(fp);
            for (i = 0; i < 10; i++)
            {
                fscanf(fp, "%d %c %s %d %f", &rooms[i], &status, guests[i], &stay, &rate);
            }

            found = 0;
            for (i = 0; i < 10; i++)
            {
                if (strcmp(guests[i], guest) == 0)
                {
                    printf("%s is in room %d\n", guest, rooms[i]);
                    found = 1;
                    break;
                }
            }
            if (found == 0)
                printf("%s not found\n", guest);
        }
        else if (choice == 3)
        {
            printf("Check-out room: ");
            scanf("%d", &room);
            if (room < 101 || room > 110)
            {
                printf("No such room\n");
                continue;
            }

            fseek(fp, (room - 101) * 39, SEEK_SET);
            fscanf(fp, "%d %c %s %d %f", &no, &status, name, &stay, &rate);
            if (status == 'B')
            {
                printf("Bill: %d x %.2f = %.2f\n", stay, rate, stay * rate);
                fseek(fp, (room - 101) * 39, SEEK_SET);
                fprintf(fp, "%3d %c %-20s %2d %8.2f\n", room, 'F', "-", 0, rate);
            }
            else
            {
                printf("Room is already free\n");
            }
        }
        else if (choice == 4)
        {
            break;
        }
        else
        {
            printf("Wrong choice\n");
        }
    }

    fclose(fp);
    return 0;
}
