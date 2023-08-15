import os

def is_directory(path):
    return os.path.isdir(path)

def identify_folders(folder_path):
    for entry in os.listdir(folder_path):
        if not entry.startswith('.'):
            full_path = os.path.join(folder_path, entry)
            if is_directory(full_path):
                print(f"{entry} este folder.")
            else:
                print(f"{entry} nu este folder.")

def main():
    folder_path = "P:/anatomie"  # Înlocuiește cu calea către directorul tău
    identify_folders(folder_path)

if __name__ == "__main__":
    main()
