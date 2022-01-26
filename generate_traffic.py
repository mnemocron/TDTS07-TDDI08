from csv import writer
import random

def write_into_file(file, text):
    open_file = open(file, 'w')
    open_file.writelines(text)
    open_file.close()

def generate_random_direction():
    directions = ['NS', 'SN', 'EW', 'WE']
    return directions[random.randint(0,3)]


def generate_random_traffic():
    traffic = []
    for i in range(100):
        traffic.append(generate_random_direction() + '\n')
        if random.getrandbits(1): # generate random boolean
            traffic.append(str(random.randint(1,30)) + '\n')
    print(traffic)
    return traffic

write_into_file('generated_traffic.txt', generate_random_traffic())
