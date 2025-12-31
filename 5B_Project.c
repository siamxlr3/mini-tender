#include <stdio.h>
#include <string.h>

#define MAX_DEMANDS 20
#define MAX_MANUFACTURERS 5

typedef struct {
    char garment[20];
    char sleeve[20];
    char fabric[20];
    char closure[20];
    int quantity;
} Demand;

typedef struct {
    char name[30];
    float price[MAX_DEMANDS];   // price per demand
    int delivery_time;
    float total;
} Manufacturer;

/* ---------- BUYER DEMAND FUNCTION ---------- */
int takeDemand(Demand *d) {
    int g;

    printf("\nSelect Garment:\n");
    printf("1.Shirt  2.Pant  3.Sock  4.Polo  5.Sweater\n");
    printf("Choice: ");
    scanf("%d", &g);

    if (g < 1 || g > 5) {
        printf("Invalid garment!\n");
        return 1;
    }

    memset(d, 0, sizeof(Demand));

    if (g == 1) strcpy(d->garment, "Shirt");
    if (g == 2) strcpy(d->garment, "Pant");
    if (g == 3) strcpy(d->garment, "Sock");
    if (g == 4) strcpy(d->garment, "Polo");
    if (g == 5) strcpy(d->garment, "Sweater");

    /* Sleeve */
    if (g != 2) {
        int s;
        printf("Sleeve (1.Full / 2.Half): ");
        scanf("%d", &s);
        strcpy(d->sleeve, (s == 1) ? "Full" : "Half");
    }

    /* Fabric */
    if (g == 2) {
        int f;
        printf("Fabric (1.Jeans / 2.Gabardine): ");
        scanf("%d", &f);
        strcpy(d->fabric, (f == 1) ? "Jeans" : "Gabardine");
    }

    /* Closure */
    if (g == 1 || g == 2 || g == 4) {
        int c;
        printf("Closure (1.Chain / 2.Button): ");
        scanf("%d", &c);
        strcpy(d->closure, (c == 1) ? "Chain" : "Button");
    }

    printf("Quantity (pcs): ");
    scanf("%d", &d->quantity);

    printf("\n1 = Add more demand\n");
    printf("0 = Stop buyer\n");
    printf("-1 = Send to manufacturer\n");
    printf("Choice: ");

    int option;
    scanf("%d", &option);
    return option;
}

/* ---------- PRINT DEMAND ---------- */
void printDemand(Demand d, int i) {
    printf("\nDemand %d\n", i + 1);
    printf(" Garment : %s\n", d.garment);
    if (strlen(d.sleeve)) printf(" Sleeve  : %s\n", d.sleeve);
    if (strlen(d.fabric)) printf(" Fabric  : %s\n", d.fabric);
    if (strlen(d.closure)) printf(" Closure : %s\n", d.closure);
    printf(" Qty     : %d pcs\n", d.quantity);
}

/* ---------- MAIN ---------- */
int main() {
    Demand demands[MAX_DEMANDS];
    Manufacturer m[MAX_MANUFACTURERS];

    int dcount = 0;
    int flag;

    printf("====== BUYER ENTRY ======\n");

    while (1) {
        flag = takeDemand(&demands[dcount]);

        if (flag == 1) {
            dcount++;
        }
        else if (flag == 0) {
            dcount++;
            break;
        }
        else if (flag == -1) {
            dcount++;
            break;
        }
        else {
            printf("Invalid option!\n");
        }
    }

    /* PRINT DEMANDS */
    printf("\n====== BUYER REQUIREMENTS ======\n");
    for (int i = 0; i < dcount; i++) {
        printDemand(demands[i], i);
    }

    /* MANUFACTURER PHASE */
    int mcount;
    printf("\nHow many manufacturers (max 5): ");
    scanf("%d", &mcount);

    for (int i = 0; i < mcount; i++) {
        m[i].total = 0;

        printf("\nManufacturer %d Name: ", i + 1);
        scanf(" %[^\n]", m[i].name);

        for (int d = 0; d < dcount; d++) {
            printf("\n%s %d pcs price (BDT): ",
                   demands[d].garment,
                   demands[d].quantity);

            scanf("%f", &m[i].price[d]);

            m[i].total += m[i].price[d] * demands[d].quantity;
        }

        printf("Delivery time (days): ");
        scanf("%d", &m[i].delivery_time);
    }

    /* WINNER */
    int win = 0;
    for (int i = 1; i < mcount; i++) {
        if (m[i].total < m[win].total ||
           (m[i].total == m[win].total &&
            m[i].delivery_time < m[win].delivery_time)) {
            win = i;
        }
    }

    printf("\n====== WINNER ======\n");
    printf("Company: %s\n", m[win].name);
    printf("Total : %.2f BDT\n", m[win].total);
    printf("Time  : %d days\n", m[win].delivery_time);

    return 0;
}
