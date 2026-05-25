Maquinas de estado finitos, os estados são situacões, e dependendo de um determinado evento, vai para outro estado.


Tipo Sequencial:
-Sincronas 
-Assincronas

maquinas de estado do tipo Moore e Mealy.

FOrmato Geral: Moore
entradas : i                    clock   
Logica de PROXIMO Estado -> Estado atual -> Logica da saida
    |                           |
    <----------------------------

Mealy - As entradas Afetam A saida.
Moore - As entradas nao afetam A saida.

def: M = (S,i,O,delta, Gamma) // mude os Sibolos 
    onde  :
    .S é o conjunto finito de estados
    .I é o cojunto finito de entradas
    .O é o Conjunto Finito de saidas
    .delta: S x I -> S é a funcao de transicao de estados
    .gamma: é a funcao de saida : gamma = S x I -> O(mealy) ou delta = S -> O(Moore).




Formato Geral Mealy:
entradas : i                    clock          entrada
Logica de PROXIMO Estado -> Estado atual -> Logica da saida
    |                           |
    <----------------------------
As entradas aleram a saida

==================================================================================


Projeto de Uma MEF
codificadores:
    2^x = S ex: 2³ = 8 // é possivel fazer uma maquina de ate 8 estados
    Grey
    One-Hot: ex: 5 estados = 5 flipflops, pois somente um deles estará em nivel logico alto ex: 00001, 00010, 00100,01000,10000


exercicio 

entradas : W , Z
Borda de subida
quando W = 0 -> Z <= 0;
quando W = 1 Durante duas bordas de clock Z <= 1;

Exercicio 1: projete o circuito sequencial capaz de detectar a sequencia de entrada ....1101...
Toda vez que essa sequncia ocorre , a saida h deera ligar e passao ao estado de espera de uma nova sequncia

q1
i
