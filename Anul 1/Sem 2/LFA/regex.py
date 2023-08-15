import re

s = "Vand caine rasa pura pui 5 saptamani , are 5 zile si 7 ani saracutul"

dogBreeds = {
    "Labrador": 0,
    "Golden Retriever": 0,
    "Bulldog": 0,
    "Bichon": 0,
    "Ciobanesc": 0,
    "Mops": 0,
    "Beagle": 0,
    "Husky": 0,
    "Others/Nespecificat": 0,
}


catBreedsFilters = {
    "British shorthair": "british( |-)shorthair|briti(s|ș) (s|ș)orthair|briti(s|ș) (s|ș)ortair|briti(s|ș) (s|ș)ort( |-)hair",
    "Scottish fold": "scot[t]?ish fold|scot[t]?i(s|ș) fold",
    "Persana": "persan(a|ă)",
    "Sphinx": "sphinx|sfinx",
    "Siameza": "siamez(a|ă)",
    "Birmaneza": "birmanez(a|ă)",
    "Others/Nespecificat": "maidanez[(a|ă)]?|pisic[i]?[u]?[t|ț]?[a|ă]?",
}

parrotBreedsFilters = {
    "Peruși": "peru(s|ș)i",
    "Others/Nespecificat": "papagal(i)?|",
}

fishBreedsFilters = {
    "Discus": "dis(c)?us",
    "Koi": "(ck)oi",
    "Caras": "caras",
    "Others/Nespecificat": "pe(s|ș)t(i|e)",
}

pattern_pui = "pui|pisicu(t|ț)(a|ă|e)|c[aă][tț]e[la](u[sș]([aă]))|pe(s|ș)ti(s|ș)or"

pattern_mancare = "boabe|mancare(umeda)?|lapte|semin(t|ț)e|fulgi|hran(a|ă)"

pattern_obiecte = "cu(s|ș)c(a|ă)|acvariu|botni(t|ț)(a|ă)|bol|zgard(a|ă)|ham|culcu(s|ș)|co(s|ș)|litier(a|ă)"


print(dogBreeds)
