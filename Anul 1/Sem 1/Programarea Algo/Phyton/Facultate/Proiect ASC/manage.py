import sys
import hashlib

from decrypt import decrypt
from encrypt import encrypt

input_file = ''
output_file = ''
password = '7d85b1ab9e759f6df2c6c79475dfe10ac7cdc8b58fa890124fd28d80'
logged_in = False
function_type = None

if __name__ == "__main__":
    for i, arg in enumerate(sys.argv):
        #parametru_1: encrypt/decrypt
        if i == 1:
            if arg == 'encrypt':
                function_type = 1
            elif arg == 'decrypt':
                function_type = 2

        # parametru_2 parola
        elif i == 2:
            if hashlib.sha224(arg.encode()).hexdigest() != password:
                print('Error: wrong password')
            else:
                logged_in = True
                key = arg

        # parametru_3: input file
        elif i == 3:
            input_file = arg

        # parametru_4: output file
        elif i == 4:
            output_file = arg

    # Daca a fost scrisa gresit comanda
    if not function_type or input_file == '' or output_file == '':
        print('Error: The correct format is: "encrypt/decrypt password input_file output_file"')
    elif not input_file.endswith('.txt') and function_type == 1:
        print("Error: Encryption input file must be a .txt file")
    elif not output_file.endswith('.txt') and function_type == 2:
        print("Error: Decryption output file must be a .txt file")
    # Verificam daca exista fiserele de input
    else:
        try:
            if logged_in:
                if function_type == 1:
                    encrypt(input_file, output_file, key)
                elif function_type == 2:
                    decrypt(input_file, output_file, key)
        except:
            print(f'Error: Can\'t find the input file "{input_file}"')
