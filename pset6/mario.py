import cs50

def main():
    size = get_pyramid_size()
    
    for i in range(size):
        for j in range(size-i-1):
            print(" ", end="")
        for j in range(i+1):
            print("#", end="")
        print("  ", end="")
        for j in range(i+1):
            print("#", end="")
        print()

def get_pyramid_size():
    while True:
        print("Enter a pyramid size: ")
        size = cs50.get_int()
        if size > 0 or size < 23:
            break
    return size

if __name__ == "__main__":
    main()
    
