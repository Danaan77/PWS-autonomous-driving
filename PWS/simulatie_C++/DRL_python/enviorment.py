import pygame
import os
from SAC_necesities import Agent


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

colision1 = False
colision2 = False

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

    def get_state(self):
        return self.x, self.v

    def move(self, action='none'):
        keys = pygame.key.get_pressed()
        if keys[pygame.K_RIGHT] or action == 'right':
            self.v += 10
        if keys[pygame.K_LEFT] or action == 'left':
            self.v -= 10

        self.x_ = self.x
        self.x += self.v * dt
        
        screen.blit(Jeft_AI, (self.x, self.y))

        return self.x, self.v

    def hitbox(self, Wall, Wall2):
        self.Jeft_AI_hitbox = pygame.Rect(self.x, self.y, Jeft_AI.get_width(), Jeft_AI.get_height())

        self.collision1 = self.Jeft_AI_hitbox.colliderect(Wall)
        if self.x < 0:
            self.collision1 = True
        
        self.collision2 = self.Jeft_AI_hitbox.colliderect(Wall2)
        if self.x > screen.get_width():
            self.collision2 = True


        return self.Jeft_AI_hitbox, self.collision1, self.collision2

    
    def rewarding(self):
        self.reward = (((screen.get_width() / 2) / 100) ** 2) - (((abs(self.x - (screen.get_width() / 2)) / 100) ** 2) * 1.5)

        if self.collision1 or self.collision2:
            self.death_tim += dt
            if self.death_tim > 20:
                self.terminated = True
                self.reward -= 100
        else: 
            self.death_tim = 0

        return self.reward, self.terminated



class Enviorment():
    def __init__(self):
        self.running = True
        self.agents = [
        JeftAI(y=450, x=screen.get_width()/2, v=0),
        JeftAI(y=350, x=screen.get_width()/2-50, v=5),
        JeftAI(y=250, x=screen.get_width()/2-20, v=2),
        JeftAI(y=150, x=screen.get_width()/2+30, v=-3)
        ]
    
    def level_1(self):
        screen.fill((200,150,200))
        self.Wall = pygame.Rect(0, 0, 30, screen.get_height())
        self.Wall2 = pygame.Rect(screen.get_width() - 30, 0, 30, screen.get_height())

        pygame.draw.rect(screen, (255, 255 ,0), self.Wall)
        pygame.draw.rect(screen, (255, 255 ,0), self.Wall2)

    def gather_DATA(self):
        for agent in self.agents:
            state = agent.get_state()
            action = None #choose_action(state)
            reward, done = agent.rewarding()
            state_ = agent.move(action)
            #store_transition(state, action, reward, state_, done)
            print(state)

        return

    def run_level(self):

        self.level_1()
        self.gather_DATA()

        pygame.display.flip()

        dt = clock.tick(60) / 1000
        dt = max(0.001, min(0.1, dt))

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.running = False
        return self.running



env = Enviorment()

while running:
    
    running = env.run_level()





pygame.quit()

