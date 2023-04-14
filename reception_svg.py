import sys
import subprocess

# Validation de l'argument
if len(sys.argv) != 2 or not 3 < len(sys.argv[1]) < 7 or not sys.argv[1].isdigit():		
	print("Utilisation: reception_svg.py NUM_EQUIPE\nNUM_EQUIPE:  Un numéro d'équipe composé de 4 à 6 chiffres.")	
	sys.exit(1)		
nomFichier = sys.argv[1] + ".svg"

# Lancer serieViaUSB et rediriger ses sorties vers le script.
process = subprocess.Popen(["serieViaUSB", "-l"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)

# Attendre l'octet de début de texte. Toute autre valeur reçue est ignorée.
print("En attente de transmission")
while process.stdout.read(1) != b'\x02':
    pass   

# Écrire les données reçues dans le fichier SVG jusqu'à ce que l'on reçoive l'octet de fin de texte.
print("Transmission en cours", end = '')
with open(nomFichier, "w") as fichier:
    octet = process.stdout.read(1)
    i = 0;
    while octet != b'\x03':
        if i == 10:
            print(".", flush = True, end = '')
            i = 0
        i += 1            
        fichier.write(octet.decode("utf-8"))
        octet = process.stdout.read(1)            

# Recevoir et afficher les octets de la somme de contrôle jusqu'à ce que l'on reçoive l'octet de fin de transmission.
print("\n\nSomme de contrôle reçue : ", end = '')
octet = process.stdout.read(1)
while octet != b'\x04':
    print(octet.decode("utf-8"), end = '')        
    octet = process.stdout.read(1)

# Calculer la somme de contrôle sur le fichier créé et l'afficher.
print("\nSomme de contrôle calc. : ", end = '')
process = subprocess.Popen(["crc32", nomFichier], stdout=subprocess.PIPE)
print(process.stdout.read(8).decode("utf-8"))

# Afficher le fichier SVG à l'écran.
input("\nAppuyer sur ENTER pour afficher le SVG...")
subprocess.run(["firefox", "--kiosk", nomFichier])
