def encrypt(input_file, output_file, password):
    input = open(input_file, 'r').read()
    try:
        output = open(output_file, 'xb')
    except:
        output = open(output_file, 'wb')

    # Convertim fiecare caracter din PAROLA in cod ascii si bagam intr-un vector
    key_elements = [ord(x) for x in password]

    # Convertim fiecare caracter din INPUT in cod ascii si bagam intr-un vector
    input_elements = [ord(x) for x in input]

    # Repetam valorile din cheie de cate ori e nevoie pentru a acoperi toate elementele din input_elements
    key_elements = key_elements * (len(input_elements)//len(key_elements) + 1)

    # Criptam textul
    for i in range(len(input_elements)):
        xored_code = chr(input_elements[i] ^ key_elements[i])
        output.write(xored_code.encode())

    print('======= Ecryption successful =======\n')
    print(f'{len(input_elements)} characters encrypted'.center(36))
    print(f'{input_file} => {output_file}\n'.center(36))
    print('=' * 36)
