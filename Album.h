//Header file for the Album class

struct Album{

    short top;
    short size;
    struct ImageStack **images;

};

struct Album *newAlbum();

void checkAndResize(struct Album *a);

void removeLast(struct Album *a);

void addToAlbum(struct Album *a, struct ImageStack *ims);

void freeAlbum(struct Album *a);

int AlbumSize(struct Album *a);

struct ImageStack *GetImage(struct Album *a, int idx);

