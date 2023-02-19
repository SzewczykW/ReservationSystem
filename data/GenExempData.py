import random as rd
import os

room_prices = {'Single': 99.99, 'Double': 179.99, 'Triple': 249.99, 'Quad': 299.99, 'Suite': 499.99, 'Penthouse': 799.99, 'Presidential': 999.99}

def RandomRoom(room_id) -> str :
    room_num = room_id
    room_type = rd.choices( ['Single', 'Double', 'Triple', 'Quad', 'Suite', 'Penthouse', 'Presidential'], [0.2, 0.3, 0.2, 0.1, 0.1, 0.05, 0.05] )[0]
    room_price = room_prices[room_type]
    room_status = rd.choices( ['Available', 'Occupied', 'Reserved'], [0.5, 0.3, 0.2] )[0]
    if room_status != 'Available' :
        starting_date = rd.randint(1, 30)
        ending_date = rd.randint(starting_date, 30)
    else :
        starting_date = 0
        ending_date = 0
    return f'{room_num},{room_type},{room_price},{room_status},{starting_date},{ending_date}'

PATH = os.path.dirname(__file__)
PATH = os.path.join(PATH, 'ExempData.csv')


with open(PATH, 'wb') as f :
    for i in range(101, 201) :
        f.write(bytes(RandomRoom(i), encoding='utf-8'))
        f.write(bytes("\n", encoding='utf-8'))
    f.close()

print('Done!')