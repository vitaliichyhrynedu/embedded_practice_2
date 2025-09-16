#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double deg_to_rad(double angle) {
    return angle * M_PI / 180.;
}

double z_1(double alpha) {
    return 1. - (0.25 * pow(sin(2. * alpha), 2.)) + cos(2. * alpha);
}

double z_2(double alpha) {
    return pow(cos(alpha), 2.) + pow(cos(alpha), 4.);
}

int main() {
    char buf[24] = "";
    double alpha = 0.;

    printf("Enter alpha (in degrees): ");

    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        fprintf(stderr, "error: failed to read stdin\n");
        return EXIT_FAILURE;
    }

    if (strchr(buf, '\n') == NULL) {
        fprintf(stderr, "error: buffer overflow\n");
        return EXIT_FAILURE;
    }
    buf[strcspn(buf, "\n")] = 0;

    if (buf[0] == 0) {
        fprintf(stderr, "error: no input provided\n");
        return EXIT_FAILURE;
    }

    char* endptr = NULL;
    errno = 0;
    alpha = strtod(buf, &endptr);

    if (*endptr != 0) {
        fprintf(stderr, "error: failed to parse input\n");
        return EXIT_FAILURE;
    }

    if (errno == ERANGE) {
        fprintf(stderr, "error: value out of range\n");
        return EXIT_FAILURE;
    }

    double alpha_rad = deg_to_rad(alpha);
    double z_1_val = z_1(alpha_rad);
    double z_2_val = z_2(alpha_rad);

    printf("z_1(%f°) = %f\n", alpha, z_1_val);
    printf("z_2(%f°) = %f\n", alpha, z_2_val);

    return EXIT_SUCCESS;
}
