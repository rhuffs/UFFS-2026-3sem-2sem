typedef struct
{
    int dia, mes, ano;
} data;

void setDate(data *, int, int, int);

void showDate(data);

int dataComp(data, data);

int getDate(data, char);

int getDiff(data, data);

int isLeapYear(data);

int totalDaysyear(data);

int getDayFromYear(data);