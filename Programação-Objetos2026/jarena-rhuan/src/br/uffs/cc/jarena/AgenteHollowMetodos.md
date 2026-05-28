
Rhuan Leandro Paiva

O objetivo do hollow na arena é explorar o mapa , encontrar cogumelos e ajudar aliados, e sobreviver o maior tempo possivel 

O comportamento do agente é baseado em:

nível de energia
comunicação com outros agentes
tempo de execução (turnos) acada vez que o metodo pensa é chamado acrescenta um em turnos, é uma tenativa de  ter como saber o que fazer com base no tempo de meus agentes na arena

Atributos

Coordenadas
cogumeloX, cogumeloY
Armazenam a posição de um cogumelo conhecido.
Usados para guiar o agente quando ele precisa recuperar energia.

ajudaX, ajudaY
Armazenam a posição de um pedido de ajuda recebido.
Usados quando o agente decide ajudar outro aliado.

Estados do agente

achouCogumelo
Indica se o agente conhece a posição de algum cogumelo. Foi necessario porque o Hollow bugava no cogumemlo quando ele sumia, e ele ficava parado rodando 
Ativado ao receber energia ou mensagem de outro agente.

recebendoEnergia
Indica se o agente recebeu energia no turno atual.
Usado para detectar se ainda está sobre um cogumelo. ele tambem bugava :(

paradoNoCogumelo
Indica se o agente está parado absorvendo energia.
Tive essa ideia porque o cogumelo anda e para, e parado, gasta menos energia então quando ele chega no cogumelo é chamado o metodo para.

indoAjudar
Indica se o agente está se deslocando para ajudar outro agente.



Métodos

Construtor
AgenteHollow(Integer x, Integer y, Integer energia)

Função:

Inicializa o agente.
Define direção inicial com base em getId() % 4, criando espalhamento inicial.

Lógica:

Divide os agentes em 4 grupos:
direita, esquerda, cima, baixo.

exemplo :
ID	ID % 4
0	0 = Direita
1	1 = Esquerda
2	2 = Cima
3   3 = Baixo

4	0 = Direita
5	1 = Esquerda
6	2 = Cima
7	3 = Baixo

Foi usado metodo get id


Método principal

pensa()

Função:

Define o comportamento do agente a cada turno.
Etapas principais:
Incremento do tempo
turnos++;
Verifica se ainda está recebendo energia
Se não estiver mais → sai do cogumelo.
Gerenciamento de energia
Energia baixa → busca cogumelo ou foge.
Energia média/alta → explora.
Espalhamento inicial
if (turnos < 12)
Nos primeiros turnos, força dispersão dos agentes.
Divisão
Se energia alta → pode criar novo agente.
Ajuda
Se indoAjudar == true → vai até o local.


Movimento
espalharEexplorar()
Move o agente aleatoriamente.
Garante que ele sempre encontre um caminho válido. com um for fazendo tenativas de movimentação

irParaCogumelo()
Move o agente em direção ao cogumelo conhecido.
Usa coordenadas armazenadas.

irParaAjuda()
Move o agente até a posição de ajuda.

fugir()
Envia mensagem de ajuda.
Tenta se mover para longe.


recebeuEnergia()
Atualiza posição do cogumelo.
Marca que está recebendo energia.
Envia mensagem para aliados.

tomouDano(int energiaRestanteInimigo)
Se mais forte → continua parado (lutando).
Se mais fraco → foge.

ganhouCombate()
Envia mensagem de vitória.
Pode dividir.
Volta a explorar.

recebeuMensagem(String msg)
Interpreta mensagens:
"cogumelo:" → atualiza posição de energia
"Ajudaaaa:" → ativa modo ajuda
"Ganheeii:" → comemora e volta a explorar

Identificação
getEquipe()
Retorna o nome da equipe: "Hollow"

Métodos herdados utilizados

O Hollow utiliza métodos da classe base Agente, como:

podeMoverPara(int direcao)
setDirecao(int direcao)
geraDirecaoAleatoria()
divide()
para()
enviaMensagem(String msg)
getEnergia()
getX(), getY()
getId()

Estratégia 

O Hollow segue três fases principais:

Início (turnos < 12)
Espalhamento no mapa
Evita concentração de agentes

Meio do jogo
Exploração
Busca de cogumelos
Cooperação via mensagens

Situações críticas
Energia baixa → busca energia ou foge
Combate → decide lutar ou fugir

Foi uma implementação de um agente que prioriza cooperatividade e Valorizar a vida :)
