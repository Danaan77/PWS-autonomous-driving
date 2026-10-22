import pygame
import os

pygame.init()

screen = pygame.display.set_mode((640,640))

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
Jeft_AI = pygame.image.load(os.path.join(BASE_DIR, 'Sexy.png')).convert_alpha()
Jeft_AI = pygame.transform.scale(Jeft_AI, (Jeft_AI.get_width() // 5, Jeft_AI.get_height() // 5))

running = True
clock = pygame.time.Clock()

death_tim = 0
x = 250
v = 0
dt = 0.1

class JeftAI():
    def __init__(self, y=400, x=screen.get_width()/2, v=0):
        self.y = y
        self.x = x
        self.v = v
        self.reward = 0
        self.death_tim = 0
        self.terminated = False
        self.Jeft_AI_hitbox = pygame.Rect(self.x, self.y, Jeft_AI.get_width(), Jeft_AI.get_height())
        screen.blit(Jeft_AI, (self.x, self.y))

    def move(self, action='none'):
        keys = pygame.key.get_pressed()
        if keys[pygame.K_RIGHT] or action == 'right':
            self.v += 10
        if keys[pygame.K_LEFT] or action == 'left':
            self.v -= 10
        
        self.x += self.v * dt
        
        screen.blit(Jeft_AI, (self.x, self.y))

        return self.x, self.v

    def hitbox(self):
        self.Jeft_AI_hitbox = pygame.Rect(self.x, self.y, Jeft_AI.get_width(), Jeft_AI.get_height())

        self.collision1 = self.Jeft_AI_hitbox.colliderect(Wall)
        if x < 0:
            self.collision1 = True
        
        self.collision2 = self.Jeft_AI_hitbox.colliderect(Wall2)
        if x > screen.get_width():
            self.collision2 = True

        return self.Jeft_AI_hitbox, self.collision1, self.collision2

    
    def rewarding(self):
        self.reward = (((screen.get_width() / 2) / 100) ** 2) - (((abs(self.x - (screen.get_width() / 2)) / 100) ** 2) * 1.5)

        if collision1 or collision2:
            self.death_tim += dt
            if self.death_tim > 20:
                self.terminated = True
                self.reward -= 100
        else: 
            death_tim = 0

        return self.reward, self.terminated

agent = JeftAI()

while running:
    screen.fill((200,150,200))

    Wall = pygame.Rect(0, 0, 30, screen.get_height())
    Wall2 = pygame.Rect(screen.get_width() - 30, 0, 30, screen.get_height())

    agent_x, agent_y = agent.move()
    agent_hitbox, collision1, collision2 = agent.hitbox()
    agent_reward, terminated = agent.rewarding()

    pygame.draw.rect(screen, (255 * collision1 , 255 * (1 - collision1) ,0), Wall)
    pygame.draw.rect(screen, (255 * collision2 , 255 * (1 - collision2) ,0), Wall2)

    pygame.display.flip()

    dt = clock.tick(60) / 1000
    dt = max(0.001, min(0.1, dt))

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False


pygame.quit()

