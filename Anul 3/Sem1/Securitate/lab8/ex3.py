import hashlib
import requests


# Functia citeste un fisier in binar si ii returneaza hash-ul(sha-256)
def sha_hash(file):
    with open(file, "rb") as f:
        hash = hashlib.sha256(f.read()).hexdigest()
    return hash


def get_api_response(file):
    api_url = 'https://www.virustotal.com/api/v3/files'
    headers = {'x-apikey': '647a3b30adef76a10ec72cc72712fa6af4c4457c5580a3f312a80ae55264dab6'}

    # deschide fisierul in binar
    with open(file, 'rb') as f:
        # creaza un dictionar cu cheia 'file' si valoarea fisierului
        files = {'file': (file, f)}

        # trimite fisierul la API
        response_post = requests.post(api_url, headers=headers, files=files)

        # daca raspunsul este 200, inseamna ca fisierul a fost trimis cu succes
        if response_post.status_code == 200:
            sha_hashed = sha_hash(file)  # calculeaza hash-ul fisierului
            url = f"https://www.virustotal.com/api/v3/files/{sha_hashed}"  # creaza url-ul pentru a obtine raspunsul
            response_get = requests.request("GET", url, headers=headers)  # trimite cererea la API
            # daca raspunsul este 200, inseamna ca raspunsul a fost primit cu succes
            if response_get.status_code == 200:
                return response_get.json()  # returneaza raspunsul in format json
    return None


response = get_api_response("malware.png") # obtine raspunsul de la API
# daca raspunsul este None, inseamna ca a aparut o eroare
if response is None:
    print("An error occured")
else:
    print("Response: ")
    print(response['data']['attributes']['last_analysis_stats']['suspicious'])
