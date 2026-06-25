// ------- lista dupla -------

struct tdup {
    float info;
    struct tdup *next;
    struct tdup *prev;
};
typedef struct tdup tdup;

struct tsentdup {
    tdup *first;
    tdup *last;
};
typedef struct tsentdup tsentdup;
