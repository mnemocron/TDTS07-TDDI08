import random

def write_into_file(file, text):
    open_file = open(file, 'w')
    open_file.writelines(text)
    open_file.close()

def generate_random_traffic():
    seconds = input("How many seconds do you want to generate traffic for? ")
    traffic = []
    counter = 0
    stream_NS = str(random.randint(0,1))
    stream_SN = str(random.randint(0,1))
    stream_EW = str(random.randint(0,1))
    stream_WE = str(random.randint(0,1))

    for i in range(int(seconds)):
        if (counter >= 5):
            counter = 0
            stream_NS = str(random.randint(0,1))
            stream_SN = str(random.randint(0,1))
            stream_EW = str(random.randint(0,1))
            stream_WE = str(random.randint(0,1))

        traffic.append(" ".join([stream_NS, stream_SN, stream_EW, stream_WE]) + '\n')
        counter += 1
    return traffic

write_into_file('generated_traffic.txt', generate_random_traffic())

