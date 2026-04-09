typedef struct data{
    int dia, mes, ano;
} data;

void setDate(data*,int d, int m, int a);

int getDate(data d1, char info );

void showDate(data);

int dataComp(data, data);

int getDaysOfMonth(data d1);

int getDiff(data d1, data d2);

int isLeapYear(data d1);

int getDayFromYear(data d1);



