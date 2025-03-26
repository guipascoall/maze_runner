#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <limits> 

// Representação do labirinto
using Maze = std::vector<std::vector<char>>;

// Estrutura para representar uma posição no labirinto
struct Position {
    int row;
    int col;
};

// Posição inicial
 Position initial_pos;

// Variáveis globais
Maze maze;
int num_rows;
int num_cols;
std::stack<Position> valid_positions;

// Função para carregar o labirinto de um arquivo
Position load_maze(const std::string& file_name) {
    // TODO: Implemente esta função seguindo estes passos:
    // 1. Abra o arquivo especificado por file_name usando std::ifstream
    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        exit(1);
    }

    // 2. Leia o número de linhas e colunas do labirinto
    std::cout<< "aquii";
	file >> num_rows >> num_cols;
    std::cout << "Labirinto " << num_rows << "x" << num_cols << ":\n";

    // 3. Redimensione a matriz 'maze' de acordo (use maze.resize())
    maze.resize(num_rows);
    for (int i = 0; i < num_rows; ++i) {
        maze[i].resize(num_cols);
    }

    // Descarte o caractere de nova linha restante após ler as dimensões
    //file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // 4. Leia o conteúdo do labirinto do arquivo, caractere por caractere
    // 5. Encontre e retorne a posição inicial ('e')
    bool found_initial = false;
    char c;
    for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j < num_cols; ++j) {
            file >> c;

            // Tratamento de erros na leitura de caracteres
            if (file.eof()) {
                std::cerr << "Erro: final do arquivo atingido antes do esperado na linha " << i << "." << std::endl;
                exit(1);
            }
            if (file.fail()) {
                std::cerr << "Erro durante a leitura do arquivo." << std::endl;
                exit(1);
            }

            maze[i][j] = c;
            if (c == 'e') {
                initial_pos = {i, j};
                found_initial = true;
            }
        }
        // Ignora o caractere de nova linha no final de cada linha do labirinto
        //file.ignore(1);
    }

    if (!found_initial) {
        std::cerr << "Erro: posição inicial ('e') não encontrada no labirinto!" << std::endl;
        exit(1);
    }

    // 7. Feche o arquivo após a leitura
    file.close();
    return initial_pos;
}

// Função para imprimir o labirinto
void print_maze() {
    // TODO: Implemente esta função
    // 1. Percorra a matriz 'maze' usando um loop aninhado
    // 2. Imprima cada caractere usando std::cout
    // 3. Adicione uma quebra de linha (std::cout << '\n') ao final de cada linha do labirinto
    // Percorre cada linha da matriz 'maze'
    system("clear");
    for (int i = 0; i < num_rows; ++i) {
        // Percorre cada caractere na linha
        for (int j = 0; j < num_cols; ++j) {
            std::cout << maze[i][j]; // Imprime o caractere
        }
        // Adiciona uma quebra de linha ao final de cada linha do labirinto
        std::cout << '\n';
    }
}

// Função para verificar se uma posição é válida
bool is_valid_position(int row, int col) {
    // TODO: Implemente esta função
    // 1. Verifique se a posição está dentro dos limites do labirinto
    //    (row >= 0 && row < num_rows && col >= 0 && col < num_cols)
    if (row >= 0 && row < num_rows && col >= 0 && col < num_cols) {
        // 2. Verifique se a posição é um caminho válido (maze[row][col] == 'x')
        if (maze[row][col] == 'x' || maze[row][col] == 's') {
            // 3. Retorne true se ambas as condições forem verdadeiras, false caso contrário
            return true;
        }
    }
    return false;
}

// Função principal para navegar pelo labirinto
bool walk(Position pos) {
    // TODO: Implemente a lógica de navegação aqui
    
    // 4. Verifique se a posição atual é a saída (maze[pos.row][pos.col] == 's')
    //    Se for, retorne true
    if (maze[pos.row][pos.col] == 's') {
        maze[pos.row][pos.col] = 'o'; // Marca a posição de saída como "o"
        print_maze();
        return true; // Encontramos a saída
    }
    
    // 1. Marque a posição atual como visitada (maze[pos.row][pos.col] = '.')
    maze[pos.row][pos.col] = 'o';

    // 2. Chame print_maze() para mostrar o estado atual do labirinto
    print_maze();

    // 3. Adicione um pequeno atraso para visualização:
    //    std::this_thread::sleep_for(std::chrono::milliseconds(50)); ERRO ERRO ERRO ERRO ERRO ERRO ERRO ERRO ERRO ERRO ERRO
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    

    // 5. Verifique as posições adjacentes (cima, baixo, esquerda, direita)
    Position adjacente[4] = {
        {pos.row - 1, pos.col}, // Cima
        {pos.row + 1, pos.col}, // Baixo
        {pos.row, pos.col - 1}, // Esquerda
        {pos.row, pos.col + 1}  // Direita
    };
    //    Para cada posição adjacente:
    for (int i = 0; i < 4; ++i) {
        Position adj = adjacente[i];
        //    a. Se for uma posição válida (use is_valid_position()), adicione-a à pilha valid_positions
        if (is_valid_position(adj.row, adj.col)) {
            valid_positions.push(adj); // Adiciona à pilha para explorar
        }
    }
    // 6. Enquanto houver posições válidas na pilha (!valid_positions.empty()):
    while (!valid_positions.empty()) {
        //    a. Remova a próxima posição da pilha (valid_positions.top() e valid_positions.pop())
        Position next_pos = valid_positions.top();
        valid_positions.pop();
        //    b. Chame walk recursivamente para esta posição

        //    c. Marque a posição anterior como "."
        maze[pos.row][pos.col] = '.'; // Marca a posição passada como "." para indicar que o jogador já passou por lá
        //    d. Se walk retornar true, propague o retorno (retorne true)
        if (walk(next_pos)) {
            return true; // Propaga o sucesso (encontrou a saída)
        }
    }
    
    // 7. Se todas as posições foram exploradas sem encontrar a saída, retorne false
    return false;
}

int main() {
    std::cout << "Iniciando o teste com o labirinto...\n";

    // Caminho fixo para o arquivo maze2.txt
    std::string file_name = "data/maze2.txt";
    
    // Carregar o labirinto diretamente do arquivo
    Position initial_pos = load_maze(file_name);
    if (initial_pos.row == -1 || initial_pos.col == -1) {
        std::cerr << "Posição inicial não encontrada no labirinto." << std::endl;
        return 1;
    }

    
    bool exit_found = walk(initial_pos);

    if (exit_found) {
        std::cout << "Saída encontrada!" << std::endl;
    } else {
        std::cout << "Não foi possível encontrar a saída." << std::endl;
    }

    return 0;
}

// Nota sobre o uso de std::this_thread::sleep_for:
// 
// A função std::this_thread::sleep_for é parte da biblioteca <thread> do C++11 e posteriores.
// Ela permite que você pause a execução do thread atual por um período especificado.
// 
// Para usar std::this_thread::sleep_for, você precisa:
// 1. Incluir as bibliotecas <thread> e <chrono>
// 2. Usar o namespace std::chrono para as unidades de tempo
// 
// Exemplo de uso:
// std::this_thread::sleep_for(std::chrono::milliseconds(50));
// 
// Isso pausará a execução por 50 milissegundos.
// 
// Você pode ajustar o tempo de pausa conforme necessário para uma melhor visualização
// do processo de exploração do labirinto.
