import cs50

def main():

    card_number = get_card_number()
    length = len(str(card_number))
    
    if length != 13 and length != 15 and length !=16:
        print("Invalid")  
    
    num_array = []
    for i in range(length):
        num_array.append(card_number % 10)
        card_number = card_number // 10
        
    original_number = num_array.copy()
    temp_number = num_array
    
    for i in range(len(temp_number)):
        if i % 2 != 0:
            temp_number[i] *= 2
   
    total = 0
    if length == 13:
        for i in temp_number:
            total += ((i % 10) + (i // 10 % 10))
        if original_number[12] == 4 and total % 10 == 0:
            print("VISA")
        else:
            print("Invalid_1")
    
    if length == 15:
        for i in temp_number:
            total += ((i % 10) + (i // 10 % 10))
        if (original_number[14] == 3 and total % 10 == 0 and 
           (original_number[13] == 4 or original_number[13] == 7)):
            print("AMEX")
        else:
            print("Invalid_2")
        
    if length == 16:
        for i in temp_number:
            total += ((i % 10) + (i // 10 % 10))
            print(total, end = " ")
        if original_number[15] == 4 and total % 10 == 0:
            print("VISA")    
        elif (original_number[15] == 5 and total % 10 == 0 and 
             (original_number[14] == 1 or original_number[14] == 2 or
             original_number[14] == 3 or original_number[14] == 4 or
             original_number[14] == 5)):
            print("MASTERCARD")
        else:
            print("Invalid_3")
       
    
def get_card_number():
        while True:
            print("Enter card number:")
            card_number = cs50.get_int()
            if card_number > 0:
                break
        return card_number
    
if __name__ == "__main__":
    main()
    
    