import random

def write_into_file(file, text):
    open_file = open(file, 'w')
    open_file.writelines(text)
    open_file.close()

def generate_four_directions():
    directions = ""
    for i in range(4):
        directions += str(random.randint(0,1)) + " "
    return directions


def generate_random_traffic():
    seconds = input("How many seconds do you want to generate traffic for? ")
    traffic = []
    for i in range(int(seconds)):
        traffic.append(generate_four_directions() + '\n')
    # print(traffic)
    return traffic

write_into_file('generated_traffic.txt', generate_random_traffic())
