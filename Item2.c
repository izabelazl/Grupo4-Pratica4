#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	clock_t start, end;
	double cpu_time_used;

	FILE* infile, * outfile;
	char r, g, b, filetype[256], * ptri, * ptro, * img;
	int i;
	int width, height, depth, pixels;
	short n_1, n_2, n_3;

	if (argc < 3) {
		printf("Usage: %s input output", argv[0]);
		exit(1);
	}

	infile = fopen(argv[1], "rb");
	if (!infile) {
		printf("File %s not found!", argv[1]);
		exit(1);
	}

	outfile = fopen(argv[2], "wb");
	if (!outfile) {
		printf("Unable to create file %s!", argv[2]);
		exit(1);
	}

	fscanf(infile, "%s\n", filetype);
	fprintf(outfile, "%s%c", filetype, 10);

	fscanf(infile, "%d %d %d\n", &width, &height, &depth);
	fprintf(outfile, "%d %d %d%c", width, height, depth, 10);

	pixels = width * height;
	ptri = ptro = img = (char*)malloc(pixels * 3);

	fread(img, 3, pixels, infile);

	start = clock();
	for (i = 0; i < pixels; i++) {
		r = *ptri++;
		g = *ptri++;
		b = *ptri++;

		__asm {
			movzx ax, r
			movzx bx, g
			movzx cx, b
			mov   dx, 100
			add   ax, dx
			add   bx, dx
			add   cx, dx
			mov   n_1, ax
			mov   n_2, bx
			mov   n_3, cx
		}

		if (n_1 > 0b11111111) {
			n_1 = 0b11111111;
			n_1 = n_1;
		}

		if (n_2 > 0b11111111) {
			n_2 = 0b11111111;
			n_2 = n_2;
		}

		if (n_3 > 0b11111111) {
			n_3 = 0b11111111;
			n_3 = n_3;
		}

		*ptro++ = n_1;
		*ptro++ = n_2;
		*ptro++ = n_3;

	}
	end = clock();

	fwrite(img, 3, pixels, outfile);

	fclose(infile);
	fclose(outfile);
	free(img);

	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("time = %f seconds\n", cpu_time_used);
	return 0;
}
