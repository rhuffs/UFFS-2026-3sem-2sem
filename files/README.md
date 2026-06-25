# Atividade 1 — Multiplicação por Somas e Deslocamentos

## Estrutura do projeto

```
mult_fsm/
├── fsm_mult.v        ← FSM de controle (módulo principal da atividade)
├── datapath.v        ← Datapath fornecido (top-level: RF + ULA + MUX)
├── register_file.v   ← Banco de registradores (fornecido)
├── ula.v             ← ULA 10 bits (fornecida)
├── debounce.v        ← Filtro de bouncing para KEY
├── bin2bcd_20.v      ← Conversor binário → BCD (Double Dabble)
├── bcd_7seg.v        ← Decodificador BCD → 7 segmentos
├── top_mult.v        ← Top-level para DE10-Lite
├── tb_fsm_mult.v     ← Testbench da FSM
└── de10_lite.qsf     ← Constraints de pinos (Quartus)
```

---

## Algoritmo implementado (shift-and-add, LSB-first)

```
acumulador ← 0
B_temp     ← B          (cópia do multiplicador)
A_shifted  ← A          (multiplicando deslocado progressivamente)
contador   ← 0

repete 10 vezes:
    se (B_temp AND 1) == 1:
        acumulador ← acumulador + A_shifted
    A_shifted ← A_shifted << 1
    B_temp    ← B_temp    >> 1
    contador  ← contador + 1
```

Complexidade: exatamente **10 iterações** (um por bit do multiplicador).

---

## Mapeamento no banco de registradores

| Registrador | Conteúdo                          |
|:-----------:|-----------------------------------|
| R0          | Operando A (multiplicando) — carga prévia |
| R1          | Operando B (multiplicador) — carga prévia |
| R2          | **Acumulador / Resultado final**   |
| R3          | Cópia de B sendo deslocada (→ direita) |
| R4          | Constante 1 (máscara LSB e incremento) |
| R5          | A deslocado progressivamente (← esquerda) |
| R6          | Contador de iterações (0–10)       |
| R7          | Constante 10 (limite do loop)      |

---

## Diagrama de estados da FSM

```
                    ┌──────────────────────────────────────────────────────┐
                    ▼                                                        │
  RESET ──► IDLE ──(inicio=1)──► INIT_R2 ──► INIT_R3 ──► INIT_R4           │
                                                               │             │
                                                          INIT_R5            │
                                                               │             │
                                                          INIT_CTR           │
                                                               │             │
                                                          CHECK_DONE ──(Z=1)─┘
                                                               │
                                                           (Z=0)
                                                               │
                                                          TEST_LSB
                                                          /         \
                                                    (LSB=1)        (LSB=0)
                                                       │                │
                                                  ADD_PARTIAL           │
                                                       │                │
                                                  SAVE_ACC              │
                                                       └───────┬────────┘
                                                               │
                                                          SHIFT_A ──► SAVE_SHIFT_A
                                                                           │
                                                          SHIFT_B ◄────────┘
                                                               │
                                                          SAVE_SHIFT_B
                                                               │
                                                          INC_CTR ──► SAVE_CTR ──► CHECK_DONE
```

---

## Uso na DE10-Lite

### Modo de Carga (SW[9] = 0)
1. Coloque SW[8]=0, ajuste SW[7:0] com o valor de **A**
2. Pressione **KEY[0]** → A é gravado em R0
3. Coloque SW[8]=1, ajuste SW[7:0] com o valor de **B**
4. Pressione **KEY[0]** → B é gravado em R1

### Modo de Multiplicação (SW[9] = 1)
1. Vire SW[9]=1 → a FSM inicia automaticamente
2. Pressione **KEY[0]** para avançar um estado por vez (clock manual)
3. Aguarde **LEDR[9]** acender (pronto)
4. O resultado aparece em **HEX3–HEX0** em decimal
5. Se **LEDR[8]** acender, houve overflow (resultado > 1023)

### Reset
- Pressione **KEY[1]** a qualquer momento para reiniciar

---

## Simulação com ModelSim / Icarus

```bash
# Icarus Verilog
iverilog -o sim_mult tb_fsm_mult.v
vvp sim_mult

# Visualizar no GTKWave
gtkwave tb_fsm_mult.vcd
```

---

## Observações de implementação

- O banco de registradores do `register_file.v` fornecido usa `posedge escreve`
  como clock de escrita. A FSM gera o pulso `escreve=1` apenas no estado de
  salvamento, garantindo escrita síncrona em um único ciclo.
- O teste do LSB usa `AND R3, R4` (R4=1). O flag `z_flag=0` indica LSB=1.
- O overflow é detectado incrementalmente: qualquer carry na soma parcial
  acende o flag permanente `overflow_acc`.
- O debounce filtra bouncing de ~20 ms a 50 MHz (1 000 000 ciclos).

---

## Plataforma alvo

| Campo          | Valor                   |
|----------------|-------------------------|
| FPGA           | Cyclone II EP2C20F484C7 |
| Placa          | Altera DE2              |
| Ferramenta     | Quartus 13.0 ou superior |
| Clock sistema  | 50 MHz (PIN_N2)         |
| Clock FSM      | KEY[0] — push-button, ativo-baixo, com debounce de 20 ms |
| Reset          | KEY[1] — ativo-baixo    |

### Uso na bancada (DE2)

**Fase 1 — Carga dos operandos (SW[9] = 0)**
1. SW[8]=0, SW[7:0] = valor de **A** → pressione KEY[0] → grava R0
2. SW[8]=1, SW[7:0] = valor de **B** → pressione KEY[0] → grava R1

**Fase 2 — Multiplicação (SW[9] = 1)**
1. Vire SW[9]=1 → FSM sai do IDLE na próxima borda de KEY[0]
2. Pressione KEY[0] repetidamente (ou mantenha pressionado) para avançar
3. LEDG[9] acende quando concluído
4. Resultado aparece em HEX3–HEX0 (decimal)
5. LEDG[8] acende se overflow (resultado > 1023)

**Reset a qualquer momento:** KEY[1]
