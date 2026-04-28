#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int r;
    int g;
    int b;
} Pixel;

typedef struct {
    int width;
    int height;
    int max_value;
    Pixel *pixels;
} Image;

static int min_int(int a, int b) {
    return (a < b) ? a : b;
}

static int parse_flags(int argc, char *argv[], int *flip, int *sepia) {
    int i;

    *flip = 0;
    *sepia = 0;
    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == 'f' && argv[i][2] == '\0') {
            *flip = 1;
        } else if (argv[i][0] == '-' && argv[i][1] == 's' && argv[i][2] == '\0') {
            *sepia = 1;
        } else {
            return 0;
        }
    }
    return 1;
}

static int read_image(Image *img) {
    char magic[3];
    int count;
    int i;

    if (scanf("%2s", magic) != 1) {
        return 0;
    }
    if (!(magic[0] == 'P' && magic[1] == '3' && magic[2] == '\0')) {
        return 0;
    }
    if (scanf("%d %d", &img->width, &img->height) != 2) {
        return 0;
    }
    if (scanf("%d", &img->max_value) != 1) {
        return 0;
    }
    if (img->width <= 0 || img->height <= 0) {
        return 0;
    }

    count = img->width * img->height;
    img->pixels = malloc((size_t)count * sizeof(Pixel));
    if (img->pixels == NULL) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        if (scanf("%d %d %d", &img->pixels[i].r, &img->pixels[i].g, &img->pixels[i].b) != 3) {
            free(img->pixels);
            img->pixels = NULL;
            return 0;
        }
    }
    return 1;
}

static void apply_sepia(Image *img) {
    int i;
    int count = img->width * img->height;

    for (i = 0; i < count; i++) {
        Pixel p = img->pixels[i];
        int new_r = (int)(p.r * 0.393 + p.g * 0.769 + p.b * 0.189);
        int new_g = (int)(p.r * 0.349 + p.g * 0.686 + p.b * 0.168);
        int new_b = (int)(p.r * 0.272 + p.g * 0.534 + p.b * 0.131);

        img->pixels[i].r = min_int(255, new_r);
        img->pixels[i].g = min_int(255, new_g);
        img->pixels[i].b = min_int(255, new_b);
    }
}

static void apply_flip(Image *img) {
    int y;
    int x;

    for (y = 0; y < img->height; y++) {
        for (x = 0; x < img->width / 2; x++) {
            int left = y * img->width + x;
            int right = y * img->width + (img->width - 1 - x);
            Pixel temp = img->pixels[left];
            img->pixels[left] = img->pixels[right];
            img->pixels[right] = temp;
        }
    }
}

static void print_image(const Image *img) {
    int y;
    int x;

    printf("P3\n");
    printf("%d %d\n", img->width, img->height);
    printf("%d\n", img->max_value);

    for (y = 0; y < img->height; y++) {
        for (x = 0; x < img->width; x++) {
            int idx = y * img->width + x;
            printf("%d %d %d", img->pixels[idx].r, img->pixels[idx].g, img->pixels[idx].b);
            if (x < img->width - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    int flip;
    int sepia;
    Image img;

    img.width = 0;
    img.height = 0;
    img.max_value = 255;
    img.pixels = NULL;

    if (!parse_flags(argc, argv, &flip, &sepia)) {
        return 1;
    }
    if (!read_image(&img)) {
        return 1;
    }

    if (sepia) {
        apply_sepia(&img);
    }
    if (flip) {
        apply_flip(&img);
    }

    print_image(&img);
    free(img.pixels);
    return 0;
}
