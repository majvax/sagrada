# 🎲 Sagrada

Ce projet est une implémentation en C du jeu de société Sagrada, où les joueurs doivent placer des dés colorés pour créer un vitrail, tout en respectant des règles spécifiques.

## 🚀 Fonctionnalités

- 🎨 **Création de vitraux** : Placez des dés colorés selon des règles spécifiques pour compléter votre vitrail.
- 🧩 **Règles fidèles** : Respect des règles présente dans [le sujet](https://github.com/majvax/sagrada/blob/main/projet.pdf)
- 🕹️ **Modes de jeu** :
  - Solo contre l'IA
  - Multijoueur, à tour de rôle
  - Spectateur: Observer 2 IA s'affronter
- 🧠 **Intelligence artificielle** : Utilisation de la méthode de Monte Carlo pour prendre des décisions stratégiques dans le jeu.

## 📦 Installation et Compilation

Pour construire et exécuter le projet, suivez les étapes ci-dessous :

1. **Installer les outils nécessaires** : 
   - **CMAKE** Téléchargez et installez CMake depuis son [site officiel](https://cmake.org/).
   - **COMPILATEUR C** Assurez-vous d'avoir un compilateur C installé sur votre système.
   - **DR. MEMORY** (optionnel) Téléchargez et installez Dr. Memory depuis son [site officiel](https://drmemory.org/).
   - **GIT** (optionnel) Téléchargez et installez Git depuis son [site officiel](https://git-scm.com/).

2. **Télécharger le projet** :
   - Clonez le dépôt GitHub sur votre machine :
   ```bash
   git clone https://github.com/majvax/sagrada
   cd sagrada
   ```
   - Vous pouvez également télécharger le projet en tant que fichier ZIP et l'extraire sur votre machine.


2. **Créer un répertoire de construction** :
    ```bash
    mkdir build
    cd build
    ```

3. **Configurer le projet avec CMake** :
   ```bash
   cmake ..
   ```
4. **Compiler le projet** :
   ```bash
   cmake --build .
   ```
5. **Vérifier les fuites de mémoire** (optionnel) :
   - Utilisez un outil comme **Dr. Memory** pour vérifier les fuites de mémoire :
     ```bash
     drmemory -quiet ./game.exe
     ```

## 🕹️ Comment jouer

1. Lancez le jeu après avoir suivi les étapes d'installation.
2. Suivez les règles du jeu pour placer vos dés et compléter votre vitrail.
3. Obtenez un meilleur score que votre adversaire pour gagner la partie !
