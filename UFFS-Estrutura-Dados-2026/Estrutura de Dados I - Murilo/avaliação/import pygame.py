import pygame
import sys
import math

# Inicialização do Pygame
pygame.init()

# Configurações da tela
largura, altura = 800, 600
tela = pygame.display.set_mode((largura, altura))
pygame.display.set_caption("Hello World dando um mortal")

# Fonte
fonte = pygame.font.SysFont('Arial', 60)
texto = "Hello World"

# Cores
branco = (255, 255, 255)
preto = (0, 0, 0)

# Parâmetros da animação
angulo = 0
tempo = 0
centro_x = largura // 2
centro_y_base = altura // 2
amplitude_salto = 150
velocidade = 0.05

# Loop principal
clock = pygame.time.Clock()
while True:
    for evento in pygame.event.get():
        if evento.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

    # Atualiza ângulo e tempo
    angulo += 5  # grau
    tempo += velocidade

    # Calcula altura (simulando salto em parábola)
    y_offset = -math.sin(tempo * math.pi) * amplitude_salto
    centro_y = centro_y_base + y_offset

    # Renderiza texto
    texto_renderizado = fonte.render(texto, True, branco)
    texto_rotacionado = pygame.transform.rotate(texto_renderizado, angulo)
    rect = texto_rotacionado.get_rect(center=(centro_x, centro_y))

    # Preenche fundo e desenha texto
    tela.fill(preto)
    tela.blit(texto_rotacionado, rect)
    pygame.display.flip()
    clock.tick(60)  # 60 FPS
