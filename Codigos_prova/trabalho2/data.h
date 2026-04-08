typedef struct data{
    int dia, mes, ano;
} data;

/*- Funções a serem implementadas:

setDate (atribui dia, mês e ano para o tipo data criado), 
getDate (retorna o dia ou o mês ou o ano de uma data passada como parâmetro. 
O tipo de retorno deve ser passado como parâmetro também),
showDate (mostra a data em um formato amigável para o usuário), 
dataComp (recebe duas datas como parâmetro é retorna 1 se a
 primeira data é maior que a segunda, 
 -1 caso contrário e 0 se forem iguais), 
getDiff (recebe duas datas como parâmetro é retorna a diferença absoluta de 
dias entre elas. Como absoluto é: retornar sempre valores positivos).
getDiff (recebe duas datas como parâmetro é retorna a diferença absoluta de dias entre elas. 
Como absoluto é: retornar sempre valores positivos), 
isLeapYear (retorna 1 se o ano da data passada por parâmetro é bissexto, e 0 se não for), 
getDayFromYear (deve retornar o número de dias trasncorridos desde o início do ano até a data passada como parâmetro).*/

void setDate(data*,int d, int m, int a);
int getDate(data d1, char info );
void showDate(data);
int dataComp(data*, data*);
int getDiff(data d1, data d2);
int isLeapyear(data d1);
int getDayFromYear(data d1, data d2);



