# 🕵️ Detective Quest — Estruturas de Dados em C

Este projeto implementa o jogo **Detective Quest** em linguagem C, utilizando estruturas de dados para simular a exploração de uma mansão e a resolução de um crime.

Durante o jogo, o jogador percorre os cômodos da mansão, coleta pistas, armazena essas pistas em uma árvore binária de busca (BST) e, ao final, acusa um suspeito com base nas evidências.

---

## 🧠 Estruturas de dados utilizadas

- Árvore Binária → mapa da mansão  
- BST → organização das pistas em ordem alfabética  
- Tabela Hash → associação pista → suspeito  
- Ponteiros e alocação dinâmica (`malloc`)  
- Recursividade e condicionais  

---

## 🎮 Funcionalidades por nível

### ✅ Nível Novato
- Mapa da mansão em árvore binária.
- Exploração interativa (esquerda, direita ou sair).

### ✅ Nível Aventureiro
- Cada sala pode conter uma pista.
- Pistas são armazenadas automaticamente em uma BST.
- Exibição das pistas em ordem alfabética no final.

### ✅ Nível Mestre
- Cada pista está relacionada a um suspeito (via tabela hash).
- Jogador acusa um suspeito no final.
- O sistema verifica se existem provas suficientes.

---

## 🎨 Sistema de Cores (ANSI)

O jogo usa cores no terminal:

| Cor | Significado |
|-----|-------------|
| 🟢 Verde | Pistas encontradas e vitória |
| 🔴 Vermelho | Erros ou acusação incorreta |
| 🟡 Amarelo | Avisos e pistas |
| 🔵 Azul | Informações do sistema |

---
👨‍💻 Autor: Rodrigo Gomes
---
Disciplina: Estruturas de Dados - Algoritmos Avançados
---
Professor: Fábio Henrique Silva
---
Faculdade: Estácio de Sá
---

---

## ⚙️ Compilação e execução

### Compilar:

```bash
gcc -Wall -Wextra -std=c99 DetectiveQuest.c -o detective
