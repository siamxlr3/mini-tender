#include <stdio.h>
#include <string.h>

#define MAX_BUYERS 5
#define MAX_DEMANDS 20
#define MAX_MANUFACTURERS 5

struct Demand {
    int buyerID;
    char garment[30];
    char sleeve[20];
    char closure[20];
    int quantity;
};

struct Bid {
    char name[50];
    float price;
    int time;
    float total;
};

// Winner selection function
int selectWinner(struct Bid bids[], int n) {
    int w = 0;
    for (int i = 1; i < n; i++) {
        if (bids[i].price < bids[w].price ||
           (bids[i].price == bids[w].price &&
            bids[i].time < bids[w].time)) {
            w = i;
        }
    }
    return w;
}

int main() {
    struct Demand demands[MAX_DEMANDS];
    int demandCount = 0;

    printf("====== GARMENTS TENDER SYSTEM ======\n");

    /* ================= BUYER PHASE ================= */
    for (int buyer = 1; buyer <= MAX_BUYERS; buyer++) {
        int choice;
        printf("\n=== Buyer %d Started ===\n", buyer);

        while (1) {
            printf("\nBuyer %d Menu:\n", buyer);
            printf("1. Add Demand\n");
            printf("0. Quit Buyer (Next Buyer)\n");
            printf("-1. Quit All Buyers (Go to Manufacturers)\n");
            printf("Choice: ");
            scanf("%d", &choice);

            if (choice == 0) break;
            if (choice == -1) goto MANUFACTURER_PHASE;
            if (choice != 1 || demandCount >= MAX_DEMANDS) continue;

            int g, s, c;
            demands[demandCount].buyerID = buyer;

            printf("\nSelect Garment:\n");
            printf("1.Shirt 2.Pant 3.Socks 4.Polo 5.Sweater\n");
            scanf("%d", &g);

            switch (g) {
                case 1: strcpy(demands[demandCount].garment, "Shirt"); break;
                case 2: strcpy(demands[demandCount].garment, "Pant"); break;
                case 3: strcpy(demands[demandCount].garment, "Socks"); break;
                case 4: strcpy(demands[demandCount].garment, "Polo"); break;
                case 5: strcpy(demands[demandCount].garment, "Sweater"); break;
                default: continue;
            }

            if (g != 3) {
                printf("Sleeve: 1.Half 2.Full: ");
                scanf("%d", &s);
                strcpy(demands[demandCount].sleeve,
                       (s == 1) ? "Half Sleeve" : "Full Sleeve");
            } else strcpy(demands[demandCount].sleeve, "N/A");

            if (g == 1 || g == 2 || g == 4) {
                printf("Closure: 1.Button 2.Chain: ");
                scanf("%d", &c);
                strcpy(demands[demandCount].closure,
                       (c == 1) ? "Button" : "Chain");
            } else strcpy(demands[demandCount].closure, "N/A");

            printf("Quantity: ");
            scanf("%d", &demands[demandCount].quantity);

            demandCount++;
            printf("Demand added successfully!\n");
        }
    }

MANUFACTURER_PHASE:
    /* ================= MANUFACTURER PHASE ================= */
    printf("\n====== MANUFACTURER BIDDING PHASE ======\n");

    for (int d = 0; d < demandCount; d++) {
        printf("\n--- Demand %d (Buyer %d) ---\n",
               d + 1, demands[d].buyerID);
        printf("Garment : %s\n", demands[d].garment);
        printf("Sleeve  : %s\n", demands[d].sleeve);
        printf("Closure : %s\n", demands[d].closure);
        printf("Qty     : %d\n", demands[d].quantity);

        int m;
        printf("How many manufacturers (max %d)? ", MAX_MANUFACTURERS);
        scanf("%d", &m);

        struct Bid bids[m];

        for (int i = 0; i < m; i++) {
            printf("\nManufacturer %d Name: ", i + 1);
            scanf(" %[^\n]", bids[i].name);

            printf("Price per piece (BDT): ৳");
            scanf("%f", &bids[i].price);

            printf("Delivery time (days): ");
            scanf("%d", &bids[i].time);

            bids[i].total = bids[i].price * demands[d].quantity;
        }

        int win = selectWinner(bids, m);

        printf("\n>>> WINNER <<<\n");
        printf("Factory : %s\n", bids[win].name);
        printf("Price   : ৳%.2f\n", bids[win].price);
        printf("Total   : ৳%.2f BDT\n", bids[win].total);
        printf("Time    : %d days\n", bids[win].time);
    }

    printf("\n====== MANUFACTURERS QUIT ======\n");
    printf("Tender System Closed Successfully.\n");

    return 0;
}
