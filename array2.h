struct array {
    char **vals;
    int size;
};

struct array *newArrayString();

char *getVal(struct array *a, int index);
void setVal(struct array *a, int index, char *newVal);
void resize(struct array *a);

