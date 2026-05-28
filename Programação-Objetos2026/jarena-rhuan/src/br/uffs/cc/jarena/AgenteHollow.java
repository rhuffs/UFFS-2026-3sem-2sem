//Rhuan Leandro paiva
//A ideia da logica esta em AgenteHollowMetodos.md
package br.uffs.cc.jarena;

public class AgenteHollow extends Agente
{
    private int cogumeloX;
    private int cogumeloY;
    private int ajudaX;
    private int ajudaY;

    private boolean achouCogumelo;
    private boolean recebendoEnergia;
    private boolean paradoNoCogumelo;
    private boolean indoAjudar;

    private int turnos;

	public AgenteHollow(Integer x, Integer y, Integer energia) {
		super(x, y, energia);

        int resto = getId() % 4;

        if (resto == 0) {
            setDirecao(DIREITA);
        } else if (resto == 1) {
            setDirecao(ESQUERDA);
        } else if (resto == 2) {
            setDirecao(CIMA);
        } else {
            setDirecao(BAIXO);
        }

        cogumeloX = x;
        cogumeloY = y;
        ajudaX = x;
        ajudaY = y;

        achouCogumelo = false;
        recebendoEnergia = false;
        paradoNoCogumelo = false;
        indoAjudar = false;
        turnos = 0;
	}

// 	Abaixo estão os métodos que você pode chamar para criar a lógica dos seus agentes. Esses métodos devem ser
// chamados dentro do método pensa() do agente.
// Informações sobre o que cada um desses métodos faz podem ser encontradas nos arquivos Agente.java e
// Entidade.java. Existe um agente de exemplo implementado no arquivo AgenteDummy.java.
// boolean podeMoverPara(int direcao)
// boolean gastaEnergia(int quanto)
// boolean isParado()
// void para()
// int geraDirecaoAleatoria()
// boolean podeDividir()
// int getDirecao()
// void setDirecao(int direcao)
// boolean divide()
// void morre()
// void enviaMensagem(String msg)
// int getEnergia()
// int getX()
// int getY()
// int getId()
	
	@Override
	public void pensa() {
        turnos++;

        boolean recebeuEnergiaNesteTurno = recebendoEnergia;
        recebendoEnergia = false;

        if (paradoNoCogumelo && !recebeuEnergiaNesteTurno) {
            paradoNoCogumelo = false;
            achouCogumelo = false;
            setDirecao(geraDirecaoAleatoria());
        }

        if (recebeuEnergiaNesteTurno && getEnergia() < 700) {
            paradoNoCogumelo = true;
            para();
            return;
        }

        if (recebeuEnergiaNesteTurno && getEnergia() >= 700) {
            paradoNoCogumelo = false;
            setDirecao(geraDirecaoAleatoria());
        }

        if (turnos < 12) {
            int resto = getId() % 4;

            if (resto == 0 && podeMoverPara(DIREITA)) {
                setDirecao(DIREITA);
                return;
            }

            if (resto == 1 && podeMoverPara(ESQUERDA)) {
                setDirecao(ESQUERDA);
                return;
            }

            if (resto == 2 && podeMoverPara(CIMA)) {
                setDirecao(CIMA);
                return;
            }

            if (resto == 3 && podeMoverPara(BAIXO)) {
                setDirecao(BAIXO);
                return;
            }

            espalharEexplorar();
            return;
        }

		if (getEnergia() > 800 && podeDividir()){
			divide();
		}

        if (indoAjudar) {
            if (getX() == ajudaX && getY() == ajudaY) {
                indoAjudar = false;
                setDirecao(geraDirecaoAleatoria());
                espalharEexplorar();
                return;
            }

            irParaAjuda();
            return;
        }

		if (getEnergia() < 300){
            if (achouCogumelo) {
                irParaCogumelo();
            } else {
			    fugir();
            }
            return;
		}

        espalharEexplorar();
	}

	private void fugir(){
		enviaMensagem("Ajudaaaa:" + getX() + "," + getY());

		if (podeMoverPara(getDirecao())){
            return;
		}

        espalharEexplorar();
	}

    private void espalharEexplorar() {
        if (podeMoverPara(getDirecao())) {
            return;
        }

        for (int i = 0; i < 10; i++) {
            int lado = geraDirecaoAleatoria();
            if (podeMoverPara(lado)) {
                setDirecao(lado);
                return;
            }
        }

        setDirecao(geraDirecaoAleatoria());
    }

    private void irParaCogumelo() {
        if (cogumeloX > getX() && podeMoverPara(DIREITA)) {
            setDirecao(DIREITA);
            return;
        }

        if (cogumeloX < getX() && podeMoverPara(ESQUERDA)) {
            setDirecao(ESQUERDA);
            return;
        }

        if (cogumeloY > getY() && podeMoverPara(BAIXO)) {
            setDirecao(BAIXO);
            return;
        }

        if (cogumeloY < getY() && podeMoverPara(CIMA)) {
            setDirecao(CIMA);
            return;
        }

        espalharEexplorar();
    }

    private void irParaAjuda() {
        if (ajudaX > getX() && podeMoverPara(DIREITA)) {
            setDirecao(DIREITA);
            return;
        }

        if (ajudaX < getX() && podeMoverPara(ESQUERDA)) {
            setDirecao(ESQUERDA);
            return;
        }

        if (ajudaY > getY() && podeMoverPara(BAIXO)) {
            setDirecao(BAIXO);
            return;
        }

        if (ajudaY < getY() && podeMoverPara(CIMA)) {
            setDirecao(CIMA);
            return;
        }

        espalharEexplorar();
    }
	
    @Override
    public void recebeuEnergia() {
        cogumeloX = getX();
        cogumeloY = getY();
        achouCogumelo = true;
        recebendoEnergia = true;

        enviaMensagem("cogumelo:" + getX() + "," + getY());
    }

	@Override
    public void tomouDano(int energiaRestanteInimigo) {
        paradoNoCogumelo = false;
        indoAjudar = false;

        if (getEnergia() > energiaRestanteInimigo) {
            para();
        } else {
            setDirecao(geraDirecaoAleatoria());
            fugir();
        }
    }

	@Override
    public void ganhouCombate() {
        paradoNoCogumelo = false;
        indoAjudar = false;

        enviaMensagem("Ganheeii:" + getX() + "," + getY());
        setDirecao(geraDirecaoAleatoria());

        if (podeDividir() && getEnergia() > 700) {
            divide();
            espalharEexplorar();
        }
    }
	
	@Override
    public void recebeuMensagem(String msg) {
        if (msg.startsWith("cogumelo:")) {
            String dados = msg.substring(9);
            String[] partes = dados.split(",");

            cogumeloX = Integer.parseInt(partes[0]);
            cogumeloY = Integer.parseInt(partes[1]);
            achouCogumelo = true;
        }

        if (msg.startsWith("Ajudaaaa:")) {
            String dados = msg.substring(9);
            String[] partes = dados.split(",");

            int xAjuda = Integer.parseInt(partes[0]);
            int yAjuda = Integer.parseInt(partes[1]);

            if (getEnergia() > 500) {
                ajudaX = xAjuda;
                ajudaY = yAjuda;
                indoAjudar = true;
            }
        }

        if (msg.startsWith("Ganheeii:")) {
            System.out.println("Aeeeeeeee");
            indoAjudar = false;
            setDirecao(geraDirecaoAleatoria());
        }
    }
	
	@Override
	public String getEquipe() {
		return "Hollow";
	}
}