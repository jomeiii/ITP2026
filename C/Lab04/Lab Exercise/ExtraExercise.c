#include <stdio.h>

struct Recipe {
    char name[100];
    char ingredients[10][100];
    int ingredient_count;
};

void print_cookbook(struct Recipe cookbook[], int recipe_count) {
    for (int i = 0; i < recipe_count; i++) {
        printf("Recipe: %s\n", cookbook[i].name);
        printf("Ingredients:\n");

        for (int j = 0; j < cookbook[i].ingredient_count; j++) {
            printf("- %s\n", cookbook[i].ingredients[j]);
        }

        printf("\n");
    }
}

int main() {
    struct Recipe cookbook[3] = {
        {
            "Pasta",
            {"pasta", "tomato", "cheese"},
            3
        },
        {
            "Omelette",
            {"eggs", "milk", "cheese"},
            3
        },
        {
            "Salad",
            {"tomato", "cucumber", "lettuce", "cheese"},
            4
        }
    };

    print_cookbook(cookbook, 3);

    return 0;
}