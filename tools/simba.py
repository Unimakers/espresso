import os

os.environ["PYGAME_HIDE_SUPPORT_PROMPT"] = "hide"
import pygame  # noqa: E402


def main():
    pygame.init()
    bg = load_background()
    print(bg.get_size())
    screen = pygame.display.set_mode((1000, 720))
    clock = pygame.time.Clock()
    running = True
    x = 0
    y = 0
    while running:
        # poll for events
        # pygame.QUIT event means the user clicked X to close your window
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
        # fill the screen with a color to wipe away anything from last frame
        screen.fill("blue")
        # RENDER YOUR GAME HERE

        screen.blit(bg, (0, 53))
        draw_robot(screen, x, y)
        # flip() the display to put your work on screen
        pygame.display.flip()
        x += 1
        y += 1
        clock.tick(60)
    pygame.quit()


def load_background():
    bg = pygame.image.load("assets/table.png")
    return bg


def draw_robot(screen: pygame.Surface, x: int, y: int):
    pygame.draw.rect(screen, "black", (x, y + 53, 150, 150))


if __name__ == "__main__":
    main()
