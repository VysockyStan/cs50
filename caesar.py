import cs50
import sys

def main():
    if len(sys.argv) != 2:
        print("Wrong number of arguments")
    #return 1
    
    print("plaintext:", end = "")
    
    text = cs50.get_string()
    key = int(sys.argv[1])
   
    if key >= 26:
       key % 26
       
    print("ciphertext: ", end ="")
    
    for i in range(len(text)):
        encrypted_text = (ord(text[i]) + key)
        
        if text[i].isupper() and encrypted_text > ord('Z'):
            encrypted_text -= 26
        
        if text[i].islower() and encrypted_text > ord('z'):
            encrypted_text -= 26
        
        if text[i].isalpha():
            print("{}".format(chr(encrypted_text )))
        else:
            print("{}".format(text))
        
    
if __name__ == "__main__":
    main()