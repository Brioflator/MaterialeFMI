def decrypt(input_file, output_file, password):
    input = open(input_file, 'rb').read()
    try:
        output = open(output_file, 'x')
    except:
        output = open(output_file, 'w')

    # Convertim fiecare caracter din PAROLA in cod ascii si bagam intr-un vector
    key_elements = [ord(x) for x in password]
    # Luam fiecare byte din fisierul binar, care va fi de tip int, si bagam intr-un vector
    input_elements = [x for x in input]

    # Repetam valorile din cheie de cate ori e nevoie pentru a acoperi toate elementele din input_elements
    key_elements = key_elements * \
        (len(input_elements) // len(key_elements) + 1)

    # Decriptam textul
    for i in range(len(input_elements)):
        character = chr(input_elements[i] ^ key_elements[i])
        output.write(character)

    # Afisare
    print('======= Deryption successful =======\n')
    print(f'{len(input_elements)} characters decrypted'.center(36))
    print(f'{input_file} => {output_file}\n'.center(36))
    print('=' * 36)
