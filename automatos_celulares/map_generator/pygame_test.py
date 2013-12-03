def read_maps(filename):
    u"""Returns a dict containing all the maps and some more info."""


    map_data = {
        'maps': [],
        'n_maps': 0,
        'width': 0,
        'height': 0
    }

    curr_map = ""

    with open(filename) as input_file:
        configs = input_file.readline()
        
        while configs.find("(") == -1 and configs.find(")") == -1:
            configs = input_file.readline()

        map_data['n_maps'], map_data['width'], map_data['height'] = configs.strip().replace("(", "").replace(")", "").split(",")
        
        map_data['n_maps'] = int(map_data['n_maps'])
        map_data['width'] = int(map_data['width'])
        map_data['height'] = int(map_data['height'])
        
        # reading an extra blank line to get it out of the way
        input_file.readline()

        for i, line in enumerate(input_file):
            if line.isspace():
                # end of a map
                map_data['maps'].append(list(curr_map))
                curr_map = []
                continue
                
            curr_map += line.strip()

    return map_data

def start_game(filename):
    import pygame

    map_bundle = read_maps(filename)
    
    map_idx = 0
    
    pygame.init()

    size = width, height = 1280, 960

    screen = pygame.display.set_mode(size)

    cell = pygame.image.load("./images/cell.bmp")

    cell_rect= cell.get_rect()
    while 1:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    sys.exit()
        print "index: ", map_idx

        if map_idx >= map_bundle['n_maps']:
            sys.exit()
        else:
            curr_map = map_bundle['maps'][map_idx]
        
        screen.fill((0, 0, 0))
        for pos, grid_cell in enumerate(curr_map):
            if grid_cell == '@':
               pos = ((pos % map_bundle['width'])*cell_rect.width, (pos / map_bundle['width']*cell_rect.height))
               screen.blit(cell, pygame.Rect(pos[0],pos[1], cell_rect.width, cell_rect.height))
        pygame.display.flip()
        pygame.time.wait(1500)
        pygame.image.save(screen, "./images/iteration_{0}.png".format(map_idx))
        map_idx += 1

    pygame.quit()

if __name__ == "__main__":
    import sys

    if len(sys.argv) != 2:
        print "Useage: python pygame_test.py <input_file_path>"
    else:
        print sys.argv
        start_game(sys.argv[1]);
