import pygame
import csv

# Dimensiones de la ventana y los caracteres
WINDOW_WIDTH = 640
WINDOW_HEIGHT = 640

# Inicialización de Pygame
pygame.init()
window = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
pygame.display.set_caption('Juego estructura de datos')

# Carga las fuentes de texto
font_title = pygame.font.Font(None, 36)
font_subtitle = pygame.font.Font(None, 24)
font_text = pygame.font.Font(None, 18)

# Carga las imágenes
wall_image = pygame.image.load('wall.png').convert()
player_images = [pygame.image.load('p1.png').convert_alpha(),
                 pygame.image.load('p2.png').convert_alpha(),
                 pygame.image.load('p3.png').convert_alpha()]  # Replace with your actual frames
door_image = pygame.image.load('door.png').convert()
item_image = pygame.image.load('item.png').convert()
enemy_image = pygame.image.load('enemy.png').convert()
lava_image = pygame.image.load('lava.png').convert()
floor_image = pygame.image.load('empty.png').convert()

# Carga el mapa desde el archivo CSV
def load_map(file_path):
    with open(file_path, newline='') as file:
        reader = csv.reader(file)
        return list(reader)

# Dibuja el mapa en la ventana
def draw_map(map_data):
    window.fill((0, 0, 0))

    for y in range(len(map_data)):
        for x in range(len(map_data[y])):
            cell = map_data[y][x]
            if cell == '#':
                image = wall_image
            elif cell == '@':
                image = player_images[frame_index]  # Use current frame image
            elif cell == 'i':
                image = item_image
            elif cell == 'l':
                image = lava_image
            elif cell == 'e':
                image = enemy_image
            elif cell == 'd':
                image = door_image
            else:
                image = floor_image

            window.blit(image, (x * 32, y * 32))

    pygame.display.flip()

# Guarda la acción en el archivo accion.txt
def save_action(action):
    with open('accion.txt', 'a') as file:
        file.write(action + "\n")

# Estado inicial
estado = "nombre"

running = True

# Animation variables
frame_index = 0
animation_delay = 200  # Delay between animation frames in milliseconds
last_frame_time = pygame.time.get_ticks()

# Bucle principal
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    if estado == "mapa":
        # Mostrar pantalla del mapa
        map_data = load_map("mapatemp.csv")
        draw_map(map_data)

        # Animation frame timing
        current_time = pygame.time.get_ticks()
        if current_time - last_frame_time >= animation_delay:
            frame_index = (frame_index + 1) % len(player_images)
            last_frame_time = current_time

        # Leer el archivo "estado.txt" cada 5 segundos
        pygame.time.wait(200)  # Espera 200 milisegundos (0.2 segundos)

        with open("estado.txt", "r") as file:
            contenido = file.read().strip()

        if contenido == "nombre":
            estado = "nombre"
            pygame.time.wait(200)  # Espera 200 milisegundos (0.2 segundos)

        else:
            # Verifica las teclas presionadas para los movimientos
            keys = pygame.key.get_pressed()
            if keys[pygame.K_w]:
                save_action('w')
            elif keys[pygame.K_a]:
                save_action('a')
            elif keys[pygame.K_s]:
                save_action('s')
            elif keys[pygame.K_d]:
                save_action('d')

    elif estado == "nombre":
        # Mostrar pantalla para ingresar el nombre del jugador
        window.fill((0, 0, 0))

        title_text = font_title.render("Juego estructura de datos", True, (255, 255, 255))
        window.blit(title_text, (50, 50))

        subtitle_text = font_subtitle.render("Ingresa el nombre del jugador", True, (255, 255, 255))
        window.blit(subtitle_text, (50, 100))

        pygame.draw.rect(window, (255, 255, 255), pygame.Rect(50, 150, 200, 30))
        pygame.draw.rect(window, (0, 0, 0), pygame.Rect(52, 152, 196, 26))

        input_text = ""
        while estado == "nombre":
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
                    estado = "salir"
                elif event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_RETURN:
                        estado = "mapa"
                        with open("nombre.txt", "w") as file:
                            file.write(input_text)
                        with open("estado.txt", "w") as file:
                            file.write("mapa")
                    elif event.key == pygame.K_BACKSPACE:
                        input_text = input_text[:-1]
                    else:
                        input_text += event.unicode

            text_surface = font_text.render(input_text, True, (255, 255, 255))
            window.blit(text_surface, (55, 155))

            pygame.display.flip()

# Finaliza Pygame
pygame.quit()
