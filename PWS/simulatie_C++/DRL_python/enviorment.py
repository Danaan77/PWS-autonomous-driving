import pygame
import os

pygame.init()

screen = pygame.display.set_mode((640,640))
BASE_DIR = os.path.dirname(os.path.abspath(__file__))

Jeft_AI = pygame.image.load(
    os.path.join(BASE_DIR, 'Sexy.png')
).convert_alpha()
Jeft_AI = pygame.transform.scale(Jeft_AI, (Jeft_AI.get_width() // 5, Jeft_AI.get_height() // 5))

running = True
clock = pygame.time.Clock()

death_tim = 0
x = 250
v = 0
dt = 0.1

while running:
    screen.fill((200,150,200))

    keys = pygame.key.get_pressed()
    if keys[pygame.K_RIGHT]:
        v += 10
    if keys[pygame.K_LEFT]:
        v -= 10
   

    screen.blit(Jeft_AI, (x - Jeft_AI.get_width()/2, 400))
    x += v * dt
    Jeft_AI_hitbox = pygame.Rect(x, 400, Jeft_AI.get_width(), Jeft_AI.get_height())

    Wall = pygame.Rect(0, 0, 30, screen.get_height())
    Wall2 = pygame.Rect(screen.get_width() - 30, 0, 30, screen.get_height())
    collision = Jeft_AI_hitbox.colliderect(Wall)
    if x < 0:
        collision = True
    collision2 = Jeft_AI_hitbox.colliderect(Wall2)
    if x > screen.get_width():
        collision2 = True
    pygame.draw.rect(screen, (255 * collision , 255 * (1 - collision) ,0), Wall)
    pygame.draw.rect(screen, (255 * collision2 , 255 * (1 - collision2) ,0), Wall2)

    reward = (((screen.get_width() / 2) / 100) ** 2) - (((abs(x - (screen.get_width() / 2)) / 100) ** 2) * 1.5)

    if collision or collision2:
        death_tim += dt
        if death_tim > 20:
            running = False
            reward -= 100
    else: 
        death_tim = 0
    
    print(reward)
    pygame.display.flip()

    dt = clock.tick(60) / 1000
    dt = max(0.001, min(0.1, dt))

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False


pygame.quit()

