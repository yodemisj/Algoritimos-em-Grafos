Descrição
Este projeto é uma solução para os problemas dos puzzles 8 e 15 usando o algoritmo A* (e potencialmente IDA*). O código implementa uma classe Graph que constrói o grafo de estados e uma classe FileUtils para lidar com operações de leitura e gravação de arquivos. O objetivo é resolver o puzzle e, opcionalmente, salvar a solução passo a passo em um arquivo.

Compilação
Para compular o código use o comando:
g++ -o puzzle_solver main.cpp

Execução
Para executar o programa, use o seguinte comando:
./puzzle_solver

Modo Passo a Passo
Se você escolher visualizar a solução passo a passo, o programa salvará a saída em um arquivo chamado saida.out. Este arquivo conterá cada passo da solução.

Arquivos de Entrada
Os arquivos de entrada para as instâncias dos puzzles devem estar localizados nos seguintes caminhos:

./ins/8puzzle_instances.txt: Contém instâncias para o puzzle 8.
./ins/15puzzle_instances.txt: Contém instâncias para o puzzle 15.

