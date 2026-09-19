# Turing_Machine

Simulador de **Máquinas de Turing** (determinísticas e não-determinísticas), escrito em C.

Trabalho da disciplina de **Teoria da Computação (2023/2)**. O programa lê a descrição
de uma Máquina de Turing e, para cada palavra fornecida, decide se a máquina **aceita**
ou **rejeita** aquela palavra, imprimindo a fita final no caso de aceitação.

## Como compilar

O projeto usa apenas a biblioteca padrão de C. Para compilar com `gcc`:

```sh
gcc -o Turing_Machine main.c turing.c
```

Também é possível abrir o projeto no **Code::Blocks** através do arquivo
`Turing_Machine.cbp`.

## Como executar

O programa lê tudo da entrada padrão. O modo mais prático é redirecionar um arquivo
de entrada:

```sh
./Turing_Machine < entrada.txt
```

## Formato de entrada

1. A primeira linha contém dois inteiros: `N` (número de estados) e `T` (número de
   transições). Os estados são `q0, q1, ..., q(N-1)`, sendo `q0` o estado inicial.
2. As `T` linhas seguintes descrevem as transições, uma por linha, no formato:

   ```
   i X/Y,C j
   ```

   indicando uma transição de `qi` para `qj` que substitui o símbolo `X` por `Y` e
   move o cabeçote para a **esquerda** (`C = L`) ou para a **direita** (`C = R`).
3. A linha seguinte contém `F`, o número de estados finais, e a próxima linha contém
   os `F` estados finais.
4. Em seguida vêm as palavras a processar, uma por linha. A entrada termina com uma
   linha contendo apenas `*`.

O caractere `b` representa o símbolo especial de **branco**.

## Formato de saída

Para cada palavra `w`:

- Se aceita: `w aceita: [FF]`, onde `[FF]` é a fita ao final da execução, **sem** os
  símbolos de branco `b` após o último símbolo não-branco.
- Se rejeitada: `w rejeitada.`

### Exemplo

Entrada (linguagem `{0ⁿ1ⁿ0ⁿ | n > 0}`):

```
6 16
0 0/X,R 1
1 0/0,R 1
1 Y/Y,R 1
1 1/Y,R 2
2 1/1,R 2
2 Z/Z,R 2
2 0/Z,L 3
3 0/0,L 3
3 1/1,L 3
3 Y/Y,L 3
3 Z/Z,L 3
3 X/X,R 0
0 Y/Y,R 4
4 Y/Y,R 4
4 Z/Z,R 4
4 b/b,L 5
1
5
010
001100
0100
*
```

Saída:

```
010 aceita: XYZ
001100 aceita: XXYYZZ
0100 rejeitada.
```

## Estrutura do projeto

| Arquivo                | Descrição                                                        |
| ---------------------- | ---------------------------------------------------------------- |
| `main.c`               | Leitura da entrada, montagem da máquina e laço de processamento. |
| `turing.c`             | Estrutura de dados e algoritmos de simulação da máquina.         |
| `turing.h`             | Declarações da struct `nodo` e dos protótipos das funções.       |
| `Turing_Machine.cbp`   | Projeto do Code::Blocks.                                         |
| `enunciado.pdf`        | Enunciado completo do trabalho.                                  |
| `Anotações.txt`        | Notas sobre a implementação.                                     |

## Detalhes de implementação

As transições são armazenadas em uma **lista de adjacência**: um vetor indexado pelo
estado de origem, onde cada posição aponta para uma lista ligada (`struct nodo`) com
as transições que partem daquele estado. Cada nó guarda o campo `troca` (a string
`X/Y,C`) e o estado de destino.

A simulação é feita em `turing.c` por duas funções:

- **`turing`** — versão iterativa, usada como primeira abordagem. Percorre as
  transições de forma direta e só funciona corretamente para máquinas
  **determinísticas**.
- **`turingMachine`** — versão **recursiva**, que é a efetivamente usada em `main.c`.
  Ela trata máquinas **determinísticas e não-determinísticas** por meio de
  *backtracking*: para cada transição aplicável, faz uma **cópia da fita e da posição
  do cabeçote** (`strdup`) antes de tentar aquele caminho. Se o caminho não leva ao
  estado final, a cópia é descartada e o próximo caminho é testado, sem afetar as
  outras tentativas. Se algum caminho alcança um estado final, a fita resultante é
  retornada.

## Limitações conhecidas

- **Um único estado final:** embora a entrada informe `F` estados finais, o programa
  lê `F` e em seguida apenas **um** estado final. Funciona corretamente quando
  `F = 1` (caso de todos os exemplos do enunciado).
- **Tamanho da palavra:** o buffer da palavra é fixo (`char palavra[20]`) e são
  anexadas 5 células de branco (`"bbbbb"`). Isso limita o comprimento das entradas,
  ficando abaixo do limite de 1000 células citado no enunciado.
- **Sem impressão da computação:** não é impresso o passo a passo da execução
  (a pontuação extra do enunciado não foi implementada).
- **Loop infinito:** conforme permitido pelo enunciado, máquinas que entram em loop
  infinito podem fazer o programa não terminar.

## Licença

MIT. Ver [LICENSE](LICENSE).